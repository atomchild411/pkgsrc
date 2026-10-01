/* Copyright libuv contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/* IRIX 6.5: the platform functions the poll(2) backend leaves to us. */

#include "uv.h"
#include "internal.h"

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <utmpx.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/procfs.h>
#include <sys/sysinfo.h>
#include <sys/sysmp.h>

/* crt1.o keeps the program's arguments here. */
extern char** __Argv;

/* IRIX has no way to ask for the running executable's path, so resolve
 * argv[0] as the shell did: as a path if it has a slash, else along PATH.
 */
int uv_exepath(char* buffer, size_t* size) {
  char candidate[PATH_MAX];
  char resolved[PATH_MAX];
  const char* argv0;
  const char* path;
  const char* end;
  size_t len;

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;
  if (__Argv == NULL || __Argv[0] == NULL || __Argv[0][0] == '\0')
    return UV_ENOENT;
  argv0 = __Argv[0];

  if (strchr(argv0, '/') != NULL) {
    if (realpath(argv0, resolved) == NULL)
      return UV__ERR(errno);
  } else {
    path = getenv("PATH");
    if (path == NULL)
      path = "/usr/sbin:/usr/bsd:/sbin:/usr/bin:/bin";
    resolved[0] = '\0';
    for (;;) {
      end = strchr(path, ':');
      len = end ? (size_t) (end - path) : strlen(path);
      if (len == 0)
        snprintf(candidate, sizeof(candidate), "./%s", argv0);
      else
        snprintf(candidate, sizeof(candidate), "%.*s/%s", (int) len, path,
                 argv0);
      if (access(candidate, X_OK) == 0 && realpath(candidate, resolved) != NULL)
        break;
      resolved[0] = '\0';
      if (end == NULL)
        break;
      path = end + 1;
    }
    if (resolved[0] == '\0')
      return UV_ENOENT;
  }

  len = strlen(resolved);
  if (len >= *size)
    len = *size - 1;
  memcpy(buffer, resolved, len);
  buffer[len] = '\0';
  *size = len;
  return 0;
}


int uv_resident_set_memory(size_t* rss) {
  char path[32];
  prpsinfo_t info;
  int fd;
  int r;

  snprintf(path, sizeof(path), "/proc/pinfo/%d", (int) getpid());
  fd = open(path, O_RDONLY);
  if (fd == -1)
    return UV__ERR(errno);
  r = ioctl(fd, PIOCPSINFO, &info);
  uv__close(fd);
  if (r == -1)
    return UV__ERR(errno);
  *rss = (size_t) info.pr_rssize * getpagesize();
  return 0;
}


static int uv__irix_rminfo(struct rminfo* info) {
  return sysmp(MP_SAGET, MPSA_RMINFO, info, sizeof(*info));
}


uint64_t uv_get_free_memory(void) {
  struct rminfo info;

  if (uv__irix_rminfo(&info) == -1)
    return 0;
  return (uint64_t) info.freemem * getpagesize();
}


uint64_t uv_get_total_memory(void) {
  struct rminfo info;

  if (uv__irix_rminfo(&info) == -1)
    return 0;
  return (uint64_t) info.physmem * getpagesize();
}


uint64_t uv_get_constrained_memory(void) {
  return 0;  /* Memory is not constrained. */
}


uint64_t uv_get_available_memory(void) {
  return uv_get_free_memory();
}


/* The boot time is in utmpx. */
int uv_uptime(double* uptime) {
  struct utmpx id;
  struct utmpx* boot;
  time_t booted;

  memset(&id, 0, sizeof(id));
  id.ut_type = BOOT_TIME;
  setutxent();
  boot = getutxid(&id);
  booted = boot != NULL ? boot->ut_tv.tv_sec : 0;
  endutxent();
  if (booted == 0)
    return UV_ENOSYS;
  *uptime = difftime(time(NULL), booted);
  return 0;
}


/* The load average is only in kernel memory. */
void uv_loadavg(double avg[3]) {
  avg[0] = avg[1] = avg[2] = 0;
}


int uv_cpu_info(uv_cpu_info_t** cpu_infos, int* count) {
  uv_cpu_info_t* cpus;
  struct sysinfo si;
  uint64_t ms_per_tick;
  int n;
  int i;

  n = sysmp(MP_NPROCS);
  if (n < 1)
    return UV__ERR(errno);
  cpus = uv__calloc(n, sizeof(*cpus));
  if (cpus == NULL)
    return UV_ENOMEM;
  ms_per_tick = 1000 / sysconf(_SC_CLK_TCK);

  for (i = 0; i < n; i++) {
    cpus[i].model = uv__strdup("MIPS");
    if (cpus[i].model == NULL) {
      uv_free_cpu_info(cpus, i);
      return UV_ENOMEM;
    }
    cpus[i].speed = 0;
    if (sysmp(MP_SAGET1, MPSA_SINFO, &si, sizeof(si), i) != -1) {
      cpus[i].cpu_times.user = (uint64_t) si.cpu[CPU_USER] * ms_per_tick;
      cpus[i].cpu_times.sys = (uint64_t) si.cpu[CPU_KERNEL] * ms_per_tick;
      cpus[i].cpu_times.idle = (uint64_t) si.cpu[CPU_IDLE] * ms_per_tick;
      cpus[i].cpu_times.irq = (uint64_t) si.cpu[CPU_INTR] * ms_per_tick;
      cpus[i].cpu_times.nice = 0;
    }
  }

  *cpu_infos = cpus;
  *count = n;
  return 0;
}


/* No getifaddrs(): IRIX lists interfaces only through SIOCGIFCONF. */
int uv_interface_addresses(uv_interface_address_t** addresses, int* count) {
  *addresses = NULL;
  *count = 0;
  return UV_ENOSYS;
}

