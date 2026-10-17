# Copyright (c) 2009, Giampaolo Rodola'
# All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""IRIX 6.5 platform implementation.

Processes come from procfs: /proc/pinfo/<pid> (PIOCPSINFO, PIOCCRED)
for everything anyone may read, /proc/<pid> (PIOCSTATUS, PIOCUSAGE;
the owner and root only) for the user/system CPU split and context
switches. procfs names processes with ten zero-padded digits.

Not available on IRIX: per-process cwd, open files, file descriptors,
environment, threads, I/O counters and memory maps; system-wide
network and disk I/O counters and socket connections.
"""

import functools
import glob
import os

from . import _common
from . import _ntuples as ntp
from . import _psposix
from . import _psutil_irix as cext
from ._common import NIC_DUPLEX_UNKNOWN
from ._common import AccessDenied
from ._common import NoSuchProcess
from ._common import ZombieProcess
from ._common import get_procfs_path
from ._common import memoize_when_activated
from ._common import usage_percent

__extra__all__ = ["PROCFS_PATH"]


# =====================================================================
# --- globals
# =====================================================================


PAGE_SIZE = cext.getpagesize()
AF_LINK = cext.AF_LINK

# pr_sname, the letter ps(1) shows.
PROC_STATUSES = {
    b"R": _common.STATUS_RUNNING,
    b"S": _common.STATUS_SLEEPING,
    b"Z": _common.STATUS_ZOMBIE,
    b"T": _common.STATUS_STOPPED,
    b"I": _common.STATUS_IDLE,
    b"X": _common.STATUS_WAITING,  # SXBRK: waiting for memory
    b"0": _common.STATUS_RUNNING,  # on a processor
}

proc_info_map = dict(
    ppid=0,
    rss=1,
    vms=2,
    create_time=3,
    nice=4,
    num_threads=5,
    status=6,
    ttynr=7,
    name=8,
    psargs=9,
    cpu_time=10,
)

# File systems that hold no files of their own (df leaves them out).
PSEUDO_FSTYPES = {"proc", "hwgfs", "fd", "dbg"}

# PRNODEV: no controlling terminal.
PRNODEV = 0xFFFFFFFF


# =====================================================================
# --- memory
# =====================================================================


def virtual_memory():
    total, free, avail, _buffers = cext.virtual_mem()
    used = total - free
    percent = usage_percent((total - avail), total, round_=1)
    return ntp.svmem(total, avail, percent, used, free)


def swap_memory():
    """Swap system memory as a (total, used, free, sin, sout) tuple."""
    total, free, sin, sout = cext.swap_mem()
    used = total - free
    percent = usage_percent(used, total, round_=1)
    return ntp.sswap(total, used, free, percent, sin, sout)


# =====================================================================
# --- CPU
# =====================================================================


def cpu_times():
    """Return system-wide CPU times as a named tuple."""
    ret = cext.per_cpu_times()
    return ntp.scputimes(*[sum(x) for x in zip(*ret)])


def per_cpu_times():
    """Return system per-CPU times as a list of named tuples."""
    return [ntp.scputimes(*x) for x in cext.per_cpu_times()]


def cpu_count_logical():
    """Return the number of logical CPUs in the system."""
    return cext.cpu_count()[1] or None


def cpu_count_cores():
    """IRIX's CPUs have one core and one thread each."""
    return cext.cpu_count()[1] or None


def cpu_stats():
    """Return various CPU stats as a named tuple."""
    ctx_switches, interrupts, soft_interrupts, syscalls = cext.cpu_stats()
    return ntp.scpustats(ctx_switches, interrupts, soft_interrupts, syscalls)


# =====================================================================
# --- disks
# =====================================================================


disk_usage = _psposix.disk_usage


def disk_io_counters():
    """Not available on IRIX."""
    return {}


def disk_partitions(all=False):
    """Return mounted disk partitions."""
    retlist = []
    for device, mountpoint, fstype, opts in cext.disk_partitions():
        if device == 'none':
            device = ''
        if not all:
            # Like df: leave out pseudo file systems and those that
            # report no size.
            if fstype in PSEUDO_FSTYPES:
                continue
            try:
                if not disk_usage(mountpoint).total:
                    continue
            except OSError:
                continue
        retlist.append(ntp.sdiskpart(device, mountpoint, fstype, opts))
    return retlist


# =====================================================================
# --- network
# =====================================================================


net_if_addrs = cext.net_if_addrs


def net_io_counters():
    """Not available on IRIX."""
    return {}


def net_connections(kind, _pid=-1):
    msg = "net_connections() is not available on IRIX"
    raise NotImplementedError(msg)


def net_if_stats():
    """Get NIC stats (isup, duplex, speed, mtu)."""
    names = {x[0] for x in net_if_addrs()}
    ret = {}
    for name in names:
        mtu = cext.net_if_mtu(name)
        flags = cext.net_if_flags(name)
        isup = cext.net_if_is_running(name)
        ret[name] = ntp.snicstats(
            isup, NIC_DUPLEX_UNKNOWN, 0, mtu, ','.join(flags)
        )
    return ret


# =====================================================================
# --- other system functions
# =====================================================================


def boot_time():
    """The system boot time expressed in seconds since the epoch."""
    return cext.boot_time()


def users():
    """Return currently connected users as a list of namedtuples."""
    retlist = []
    for item in cext.users():
        name, tty, hostname, tstamp, pid = item
        retlist.append(ntp.suser(name, tty, hostname, tstamp, pid))
    return retlist


# =====================================================================
# --- processes
# =====================================================================


def pids():
    """Returns a list of PIDs currently running on the system."""
    path = os.path.join(get_procfs_path(), "pinfo")
    return [int(x) for x in os.listdir(path) if x.isdigit()]


pid_exists = _psposix.pid_exists


def wrap_exceptions(fun):
    """Call callable into a try/except clause and translate ENOENT,
    EACCES and EPERM in NoSuchProcess or AccessDenied exceptions.
    """

    @functools.wraps(fun)
    def wrapper(self, *args, **kwargs):
        pid, ppid, name = self.pid, self._ppid, self._name
        try:
            return fun(self, *args, **kwargs)
        except (FileNotFoundError, ProcessLookupError) as err:
            if not pid_exists(pid):
                raise NoSuchProcess(pid, name) from err
            raise ZombieProcess(pid, name, ppid) from err
        except PermissionError as err:
            raise AccessDenied(pid, name) from err

    return wrapper


class Process:
    """Wrapper class around underlying C implementation."""

    __slots__ = ["_cache", "_name", "_ppid", "_procfs_path", "pid"]

    def __init__(self, pid):
        self.pid = pid
        self._name = None
        self._ppid = None
        self._procfs_path = get_procfs_path()

    def oneshot_enter(self):
        self._proc_basic_info.cache_activate(self)
        self._proc_cred.cache_activate(self)

    def oneshot_exit(self):
        self._proc_basic_info.cache_deactivate(self)
        self._proc_cred.cache_deactivate(self)

    @wrap_exceptions
    @memoize_when_activated
    def _proc_basic_info(self):
        return cext.proc_basic_info(self.pid, self._procfs_path)

    @wrap_exceptions
    @memoize_when_activated
    def _proc_cred(self):
        return cext.proc_cred(self.pid, self._procfs_path)

    @wrap_exceptions
    def name(self):
        if self.pid == 0:
            return "sched"
        # note: max 32 characters (PRCOMSIZ)
        name = self._proc_basic_info()[proc_info_map['name']]
        return os.fsdecode(name)

    @wrap_exceptions
    def exe(self):
        # IRIX keeps no executable path for a process: find the first
        # argument as the shell would.
        cmdline = self.cmdline()
        if not cmdline:
            return ''
        exe = cmdline[0]
        if os.path.sep in exe:
            if os.path.isabs(exe) and os.path.isfile(exe):
                return exe
            exe = os.path.basename(exe)
        for path in os.environ.get("PATH", "").split(":"):
            possible_exe = os.path.abspath(os.path.join(path, exe))
            if os.path.isfile(possible_exe) and os.access(
                possible_exe, os.X_OK
            ):
                return possible_exe
        return ''

    @wrap_exceptions
    def cmdline(self):
        # The start of the argument list (PRARGSZ, 80 bytes), as ps shows.
        psargs = self._proc_basic_info()[proc_info_map['psargs']]
        return os.fsdecode(psargs).split()

    @wrap_exceptions
    def create_time(self):
        return self._proc_basic_info()[proc_info_map['create_time']]

    @wrap_exceptions
    def num_threads(self):
        return self._proc_basic_info()[proc_info_map['num_threads']]

    @wrap_exceptions
    def nice_get(self):
        return cext.proc_priority_get(self.pid)

    @wrap_exceptions
    def nice_set(self, value):
        return cext.proc_priority_set(self.pid, value)

    @wrap_exceptions
    def ppid(self):
        self._ppid = self._proc_basic_info()[proc_info_map['ppid']]
        return self._ppid

    @wrap_exceptions
    def uids(self):
        real, effective, saved, _, _, _ = self._proc_cred()
        return ntp.puids(real, effective, saved)

    @wrap_exceptions
    def gids(self):
        _, _, _, real, effective, saved = self._proc_cred()
        return ntp.pgids(real, effective, saved)

    @wrap_exceptions
    def cpu_times(self):
        t = cext.proc_cpu_times(self.pid, self._procfs_path)
        return ntp.pcputimes(*t)

    @wrap_exceptions
    def terminal(self):
        ttydev = self._proc_basic_info()[proc_info_map['ttynr']]
        if ttydev == PRNODEV:
            return None
        for dev in glob.glob("/dev/tty*") + glob.glob("/dev/pts/*"):
            try:
                if os.stat(dev).st_rdev == ttydev:
                    return dev
            except OSError:
                pass
        return None

    @wrap_exceptions
    def cwd(self):
        msg = "Process.cwd() is not available on IRIX"
        raise NotImplementedError(msg)

    @wrap_exceptions
    def memory_info(self):
        ret = self._proc_basic_info()
        rss = ret[proc_info_map['rss']] * PAGE_SIZE
        vms = ret[proc_info_map['vms']] * PAGE_SIZE
        return ntp.pmem(rss, vms)

    memory_full_info = memory_info

    @wrap_exceptions
    def status(self):
        code = self._proc_basic_info()[proc_info_map['status']]
        return PROC_STATUSES.get(code, '?')

    def open_files(self):
        msg = "Process.open_files() is not available on IRIX"
        raise NotImplementedError(msg)

    def num_fds(self):
        msg = "Process.num_fds() is not available on IRIX"
        raise NotImplementedError(msg)

    @wrap_exceptions
    def num_ctx_switches(self):
        return ntp.pctxsw(
            *cext.proc_num_ctx_switches(self.pid, self._procfs_path)
        )

    @wrap_exceptions
    def wait(self, timeout=None):
        return _psposix.wait_pid(self.pid, timeout)
