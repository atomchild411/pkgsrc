/*
 * Copyright (c) 2009, Giampaolo Rodola'. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * IRIX 6.5 platform-specific module methods for _psutil_irix.
 *
 * Processes are read through procfs: /proc/pinfo/<pid> (anyone may open
 * it) answers PIOCPSINFO and PIOCCRED; the user and system times and the
 * context switches need /proc/<pid> itself (PIOCSTATUS, PIOCUSAGE), which
 * only the owner and root may open. procfs names processes with ten
 * digits, zero-padded. System-wide figures come from sysmp(MP_SAGET),
 * swapctl() and utmpx; struct sysinfo through arch/irix/sysinfo.c.
 */

#include <Python.h>

#include <sys/types.h>
#include <sys/procfs.h>
#include <sys/sysmp.h>
#include <sys/swap.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <mntent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <utmpx.h>

#include "arch/all/init.h"
#include "arch/irix/sysinfo.h"

#define PSUTIL_TS2DOUBLE(t) ((double)(t).tv_sec + (t).tv_nsec / 1000000000.0)


/*
 * Open procfs' file for pid (dir is "" for /proc/<pid>, "pinfo/" for
 * /proc/pinfo/<pid>) and run one ioctl on it. Sets the Python error
 * (NoSuchProcess / AccessDenied through the errno) and returns -1 on
 * failure.
 */
static int
psutil_proc_ioctl(const char *procfs_path, const char *dir, long pid,
                  int request, void *buf) {
    char path[PATH_MAX];
    int fd, ret;

    snprintf(path, sizeof(path), "%s/%s%010ld", procfs_path, dir, pid);
    fd = open(path, O_RDONLY);
    if (fd == -1) {
        PyErr_SetFromErrnoWithFilename(PyExc_OSError, path);
        return -1;
    }
    ret = ioctl(fd, request, buf);
    if (ret == -1)
        PyErr_SetFromErrnoWithFilename(PyExc_OSError, path);
    close(fd);
    return ret == -1 ? -1 : 0;
}


/*
 * Return process ppid, rss and vms (pages), create time, nice, number of
 * threads, state letter, tty device, name, the start of its argument
 * list and its total CPU time, from PIOCPSINFO.
 */
static PyObject *
psutil_proc_basic_info(PyObject *self, PyObject *args) {
    long pid;
    const char *procfs_path;
    prpsinfo_t info;

    if (!PyArg_ParseTuple(args, "ls", &pid, &procfs_path))
        return NULL;
    if (psutil_proc_ioctl(procfs_path, "pinfo/", pid, PIOCPSINFO, &info) == -1)
        return NULL;
    return Py_BuildValue(
        "lllddlcKyyd",
        (long)info.pr_ppid,
        (long)info.pr_rssize,
        (long)info.pr_size,
        PSUTIL_TS2DOUBLE(info.pr_start),
        (double)info.pr_nice,
        (long)(info.pr_thds > 0 ? info.pr_thds : 1),
        info.pr_sname,
        (unsigned long long)info.pr_ttydev,
        info.pr_fname,
        info.pr_psargs,
        PSUTIL_TS2DOUBLE(info.pr_time)
    );
}


/*
 * Return process real, effective and saved user and group IDs.
 */
static PyObject *
psutil_proc_cred(PyObject *self, PyObject *args) {
    long pid;
    const char *procfs_path;
    prcred_t cred;

    if (!PyArg_ParseTuple(args, "ls", &pid, &procfs_path))
        return NULL;
    if (psutil_proc_ioctl(procfs_path, "pinfo/", pid, PIOCCRED, &cred) == -1)
        return NULL;
    return Py_BuildValue(
        "kkkkkk",
        (unsigned long)cred.pr_ruid, (unsigned long)cred.pr_euid,
        (unsigned long)cred.pr_suid, (unsigned long)cred.pr_rgid,
        (unsigned long)cred.pr_egid, (unsigned long)cred.pr_sgid
    );
}


/*
 * Return process user, system, children's user and children's system
 * times.
 */
static PyObject *
psutil_proc_cpu_times(PyObject *self, PyObject *args) {
    long pid;
    const char *procfs_path;
    prstatus_t st;

    if (!PyArg_ParseTuple(args, "ls", &pid, &procfs_path))
        return NULL;
    if (psutil_proc_ioctl(procfs_path, "", pid, PIOCSTATUS, &st) == -1)
        return NULL;
    return Py_BuildValue(
        "dddd",
        PSUTIL_TS2DOUBLE(st.pr_utime), PSUTIL_TS2DOUBLE(st.pr_stime),
        PSUTIL_TS2DOUBLE(st.pr_cutime), PSUTIL_TS2DOUBLE(st.pr_cstime)
    );
}


/*
 * Return process voluntary and involuntary context switches.
 */
static PyObject *
psutil_proc_num_ctx_switches(PyObject *self, PyObject *args) {
    long pid;
    const char *procfs_path;
    prusage_t usage;

    if (!PyArg_ParseTuple(args, "ls", &pid, &procfs_path))
        return NULL;
    if (psutil_proc_ioctl(procfs_path, "", pid, PIOCUSAGE, &usage) == -1)
        return NULL;
    return Py_BuildValue(
        "kk", (unsigned long)usage.pu_vctx, (unsigned long)usage.pu_ictx
    );
}


/*
 * Return physical memory: total, free, available, buffers (bytes).
 */
static PyObject *
psutil_virtual_mem(PyObject *self, PyObject *args) {
    struct rminfo rmi;
    unsigned long long pagesize = (unsigned long long)getpagesize();

    if (sysmp(MP_SAGET, MPSA_RMINFO, &rmi, sizeof(rmi)) == -1)
        return PyErr_SetFromErrno(PyExc_OSError);
    return Py_BuildValue(
        "KKKK",
        (unsigned long long)rmi.physmem * pagesize,
        (unsigned long long)rmi.freemem * pagesize,
        (unsigned long long)rmi.availrmem * pagesize,
        (unsigned long long)rmi.bufmem * pagesize
    );
}


/*
 * Return swap: total and free (bytes), and pages swapped in and out.
 */
static PyObject *
psutil_swap_mem(PyObject *self, PyObject *args) {
    off_t total = 0, freeb = 0;
    struct psutil_irix_si si;

    // In 512-byte blocks.
    if (swapctl(SC_GETSWAPTOT, &total) == -1)
        return PyErr_SetFromErrno(PyExc_OSError);
    if (swapctl(SC_GETFREESWAP, &freeb) == -1)
        return PyErr_SetFromErrno(PyExc_OSError);
    if (psutil_irix_sysinfo(-1, &si) == -1)
        return PyErr_SetFromErrno(PyExc_OSError);
    return Py_BuildValue(
        "KKKK",
        (unsigned long long)total * 512,
        (unsigned long long)freeb * 512,
        si.bswapin * 512,
        si.bswapout * 512
    );
}


/*
 * Return a list of (user, system, idle, iowait) tuples, one per CPU, in
 * seconds. Interrupt time counts as system time, as IRIX's sar does.
 */
static PyObject *
psutil_per_cpu_times(PyObject *self, PyObject *args) {
    int ncpus, i;
    double ticks = (double)sysconf(_SC_CLK_TCK);
    struct psutil_irix_si si;
    PyObject *py_retlist = PyList_New(0);
    PyObject *py_tuple = NULL;

    if (py_retlist == NULL)
        return NULL;
    ncpus = sysmp(MP_NPROCS);
    if (ncpus == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        goto error;
    }
    for (i = 0; i < ncpus; i++) {
        if (psutil_irix_sysinfo(i, &si) == -1) {
            // A CPU that is not there or is disabled.
            if (errno == EINVAL)
                continue;
            PyErr_SetFromErrno(PyExc_OSError);
            goto error;
        }
        py_tuple = Py_BuildValue(
            "dddd",
            si.user / ticks,
            (si.kernel + si.intr + si.sxbrk) / ticks,
            si.idle / ticks,
            si.wait / ticks
        );
        if (!py_tuple)
            goto error;
        if (PyList_Append(py_retlist, py_tuple))
            goto error;
        Py_CLEAR(py_tuple);
    }
    return py_retlist;

error:
    Py_XDECREF(py_tuple);
    Py_DECREF(py_retlist);
    return NULL;
}


/*
 * Return the number of CPUs (configured, and active).
 */
static PyObject *
psutil_cpu_count(PyObject *self, PyObject *args) {
    int n = sysmp(MP_NPROCS), active = sysmp(MP_NAPROCS);

    if (n == -1 || active == -1)
        return PyErr_SetFromErrno(PyExc_OSError);
    return Py_BuildValue("ii", n, active);
}


/*
 * Return context switches, interrupts, soft interrupts (0) and syscalls.
 */
static PyObject *
psutil_cpu_stats(PyObject *self, PyObject *args) {
    struct psutil_irix_si si;

    if (psutil_irix_sysinfo(-1, &si) == -1)
        return PyErr_SetFromErrno(PyExc_OSError);
    return Py_BuildValue(
        "KKKK", si.pswitch, si.intr_svcd, 0ULL, si.syscall
    );
}


/*
 * Return the system boot time, from utmpx's BOOT_TIME record.
 */
static PyObject *
psutil_boot_time(PyObject *self, PyObject *args) {
    struct utmpx *ut;
    double boot = 0;

    setutxent();
    while ((ut = getutxent()) != NULL) {
        if (ut->ut_type == BOOT_TIME) {
            boot = (double)ut->ut_tv.tv_sec;
            break;
        }
    }
    endutxent();
    if (boot == 0) {
        PyErr_SetString(PyExc_RuntimeError, "no BOOT_TIME record in utmpx");
        return NULL;
    }
    return Py_BuildValue("d", boot);
}


/*
 * Return mounted file systems: (device, mount point, type, options).
 */
static PyObject *
psutil_disk_partitions(PyObject *self, PyObject *args) {
    FILE *fp;
    struct mntent *mt;
    PyObject *py_retlist = PyList_New(0);
    PyObject *py_tuple = NULL;

    if (py_retlist == NULL)
        return NULL;
    fp = setmntent(MOUNTED, "r");
    if (fp == NULL) {
        PyErr_SetFromErrnoWithFilename(PyExc_OSError, MOUNTED);
        goto error;
    }
    while ((mt = getmntent(fp)) != NULL) {
        py_tuple = Py_BuildValue(
            "(ssss)", mt->mnt_fsname, mt->mnt_dir, mt->mnt_type, mt->mnt_opts
        );
        if (!py_tuple)
            goto error;
        if (PyList_Append(py_retlist, py_tuple))
            goto error;
        Py_CLEAR(py_tuple);
    }
    endmntent(fp);
    return py_retlist;

error:
    if (fp != NULL)
        endmntent(fp);
    Py_XDECREF(py_tuple);
    Py_DECREF(py_retlist);
    return NULL;
}


/*
 * define the psutil C module methods and initialize the module.
 */
static PyMethodDef PsutilMethods[] = {
    // --- process-related functions
    {"proc_basic_info", psutil_proc_basic_info, METH_VARARGS},
    {"proc_cred", psutil_proc_cred, METH_VARARGS},
    {"proc_cpu_times", psutil_proc_cpu_times, METH_VARARGS},
    {"proc_num_ctx_switches", psutil_proc_num_ctx_switches, METH_VARARGS},

    // --- system-related functions
    {"boot_time", psutil_boot_time, METH_VARARGS},
    {"cpu_count", psutil_cpu_count, METH_VARARGS},
    {"cpu_stats", psutil_cpu_stats, METH_VARARGS},
    {"disk_partitions", psutil_disk_partitions, METH_VARARGS},
    {"per_cpu_times", psutil_per_cpu_times, METH_VARARGS},
    {"swap_mem", psutil_swap_mem, METH_VARARGS},
    {"virtual_mem", psutil_virtual_mem, METH_VARARGS},

    // --- others
    {"check_pid_range", psutil_check_pid_range, METH_VARARGS},
    {"set_debug", psutil_set_debug, METH_VARARGS},

    {NULL, NULL, 0, NULL}
};


struct module_state {
    PyObject *error;
};

#define GETSTATE(m) ((struct module_state *)PyModule_GetState(m))

#ifdef __cplusplus
extern "C" {
#endif

static int
psutil_irix_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int
psutil_irix_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "psutil_irix",
    NULL,
    sizeof(struct module_state),
    PsutilMethods,
    NULL,
    psutil_irix_traverse,
    psutil_irix_clear,
    NULL
};


PyMODINIT_FUNC
PyInit__psutil_irix(void) {
    PyObject *mod = PyModule_Create(&moduledef);
    if (mod == NULL)
        return NULL;

#ifdef Py_GIL_DISABLED
    if (PyUnstable_Module_SetGIL(mod, Py_MOD_GIL_NOT_USED))
        return NULL;
#endif

    if (psutil_setup() != 0)
        return NULL;
    if (psutil_posix_add_constants(mod) != 0)
        return NULL;
    if (psutil_posix_add_methods(mod) != 0)
        return NULL;

    if (PyModule_AddIntConstant(mod, "version", PSUTIL_VERSION))
        return NULL;

    return mod;
}

#ifdef __cplusplus
}
#endif
