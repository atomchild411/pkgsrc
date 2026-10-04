$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the target's module, IRIX as the IRIX toolchain (clang with its IRIX
header wrappers and builtins) sees it.

--- libc-0.2.189/src/unix/irix/mod.rs.orig
+++ libc-0.2.189/src/unix/irix/mod.rs
@@ -0,0 +1,999 @@
+//! IRIX 6.5, N32 ABI.
+//!
+//! The types, structures and constants are IRIX 6.5.22's, as its headers declare them for the
+//! N32 ABI with no feature-test macros (the default `_SGIAPI` namespace), together with what the
+//! IRIX toolchain this target links with (clang with IRIX header wrappers, compiler-rt's IRIX
+//! builtins) adds where IRIX falls short: `socklen_t`, `sockaddr_storage`, `getaddrinfo`,
+//! `CLOCK_MONOTONIC`, `O_CLOEXEC` and the like. Functions that toolchain replaces are linked by
+//! the replacement's name (`__irix_*`), as its headers do for C programs.
+//!
+//! IRIX has no IPv6: the IPv6 types exist so code compiles, and fail at run time.
+
+use crate::prelude::*;
+use crate::{gid_t, uid_t};
+
+pub type wchar_t = i32;
+
+pub type dev_t = u32;
+pub type ino_t = u64;
+pub type ino64_t = u64;
+pub type off_t = i64;
+pub type off64_t = i64;
+pub type mode_t = u32;
+pub type nlink_t = u32;
+pub type pid_t = i32;
+pub type id_t = i32;
+pub type key_t = c_int;
+pub type time_t = c_long;
+pub type clock_t = c_int;
+pub type clockid_t = c_int;
+pub type timer_t = c_int;
+pub type suseconds_t = c_long;
+pub type useconds_t = c_uint;
+pub type blksize_t = c_long;
+pub type blkcnt_t = i64;
+pub type blkcnt64_t = i64;
+pub type fsblkcnt_t = u64;
+pub type fsfilcnt_t = u64;
+pub type rlim_t = u64;
+pub type socklen_t = c_int;
+pub type sa_family_t = u16;
+pub type in_port_t = u16;
+pub type in_addr_t = u32;
+pub type speed_t = u32;
+pub type tcflag_t = u32;
+pub type cc_t = c_uchar;
+pub type nfds_t = c_ulong;
+pub type nl_item = c_int;
+pub type pthread_t = c_uint;
+pub type pthread_key_t = c_int;
+pub type pthread_once_t = c_int;
+pub type sighandler_t = size_t;
+pub type caddr_t = *mut c_char;
+pub type iconv_t = *mut c_void;
+
+s! {
+    pub struct stat {
+        pub st_dev: dev_t,
+        st_pad1: [c_long; 3],
+        pub st_ino: ino_t,
+        pub st_mode: mode_t,
+        pub st_nlink: nlink_t,
+        pub st_uid: uid_t,
+        pub st_gid: gid_t,
+        pub st_rdev: dev_t,
+        st_pad2: [c_long; 2],
+        pub st_size: off_t,
+        st_pad3: c_long,
+        pub st_atime: time_t,
+        pub st_atime_nsec: c_long,
+        pub st_mtime: time_t,
+        pub st_mtime_nsec: c_long,
+        pub st_ctime: time_t,
+        pub st_ctime_nsec: c_long,
+        pub st_blksize: blksize_t,
+        pub st_blocks: blkcnt_t,
+        pub st_fstype: [c_char; 16],
+        pub st_projid: c_long,
+        st_pad4: [c_long; 7],
+    }
+
+    pub struct dirent {
+        pub d_ino: ino_t,
+        pub d_off: off_t,
+        pub d_reclen: c_ushort,
+        pub d_name: [c_char; 1],
+    }
+
+    pub struct sockaddr {
+        pub sa_family: sa_family_t,
+        pub sa_data: [c_char; 14],
+    }
+
+    pub struct sockaddr_in {
+        pub sin_family: sa_family_t,
+        pub sin_port: in_port_t,
+        pub sin_addr: crate::in_addr,
+        pub sin_zero: [c_uchar; 8],
+    }
+
+    pub struct sockaddr_in6 {
+        pub sin6_family: sa_family_t,
+        pub sin6_port: in_port_t,
+        pub sin6_flowinfo: u32,
+        pub sin6_addr: crate::in6_addr,
+        pub sin6_scope_id: u32,
+    }
+
+    pub struct sockaddr_un {
+        pub sun_family: sa_family_t,
+        pub sun_path: [c_char; 108],
+    }
+
+    pub struct sockaddr_storage {
+        pub ss_family: sa_family_t,
+        __ss_pad1: [c_char; 6],
+        __ss_align: i64,
+        __ss_pad2: [c_char; 112],
+    }
+
+    pub struct addrinfo {
+        pub ai_flags: c_int,
+        pub ai_family: c_int,
+        pub ai_socktype: c_int,
+        pub ai_protocol: c_int,
+        pub ai_addrlen: socklen_t,
+        pub ai_addr: *mut crate::sockaddr,
+        pub ai_canonname: *mut c_char,
+        pub ai_next: *mut addrinfo,
+    }
+
+    pub struct msghdr {
+        pub msg_name: *mut c_void,
+        pub msg_namelen: socklen_t,
+        pub msg_iov: *mut crate::iovec,
+        pub msg_iovlen: c_int,
+        pub msg_control: *mut c_void,
+        pub msg_controllen: size_t,
+        pub msg_flags: c_int,
+    }
+
+    pub struct cmsghdr {
+        pub cmsg_len: size_t,
+        pub cmsg_level: c_int,
+        pub cmsg_type: c_int,
+    }
+
+    pub struct ip_mreq {
+        pub imr_multiaddr: crate::in_addr,
+        pub imr_interface: crate::in_addr,
+    }
+
+    pub struct in_addr {
+        pub s_addr: in_addr_t,
+    }
+
+    pub struct sigset_t {
+        __sigbits: [u32; 4],
+    }
+
+    pub struct sigaction {
+        pub sa_flags: c_int,
+        pub sa_sigaction: sighandler_t,
+        pub sa_mask: sigset_t,
+        sa_resv: [c_int; 2],
+    }
+
+    pub struct siginfo_t {
+        pub si_signo: c_int,
+        pub si_code: c_int,
+        pub si_errno: c_int,
+        __data: [c_int; 29],
+    }
+
+    pub struct stack_t {
+        pub ss_sp: *mut c_void,
+        pub ss_size: size_t,
+        pub ss_flags: c_int,
+    }
+
+    pub struct sched_param {
+        pub sched_priority: c_int,
+    }
+
+    pub struct passwd {
+        pub pw_name: *mut c_char,
+        pub pw_passwd: *mut c_char,
+        pub pw_uid: uid_t,
+        pub pw_gid: gid_t,
+        pub pw_age: *mut c_char,
+        pub pw_comment: *mut c_char,
+        pub pw_gecos: *mut c_char,
+        pub pw_dir: *mut c_char,
+        pub pw_shell: *mut c_char,
+    }
+
+    pub struct utsname {
+        pub sysname: [c_char; 257],
+        pub nodename: [c_char; 257],
+        pub release: [c_char; 257],
+        pub version: [c_char; 257],
+        pub machine: [c_char; 257],
+        pub m_type: [c_char; 257],
+        pub base_rel: [c_char; 257],
+        __reserve: [[c_char; 257]; 6],
+    }
+
+    pub struct tm {
+        pub tm_sec: c_int,
+        pub tm_min: c_int,
+        pub tm_hour: c_int,
+        pub tm_mday: c_int,
+        pub tm_mon: c_int,
+        pub tm_year: c_int,
+        pub tm_wday: c_int,
+        pub tm_yday: c_int,
+        pub tm_isdst: c_int,
+    }
+
+    pub struct termios {
+        pub c_iflag: tcflag_t,
+        pub c_oflag: tcflag_t,
+        pub c_cflag: tcflag_t,
+        pub c_lflag: tcflag_t,
+        pub c_ospeed: speed_t,
+        pub c_ispeed: speed_t,
+        pub c_cc: [cc_t; crate::NCCS],
+    }
+
+    pub struct statvfs {
+        pub f_bsize: c_ulong,
+        pub f_frsize: c_ulong,
+        pub f_blocks: fsblkcnt_t,
+        pub f_bfree: fsblkcnt_t,
+        pub f_bavail: fsblkcnt_t,
+        pub f_files: fsfilcnt_t,
+        pub f_ffree: fsfilcnt_t,
+        pub f_favail: fsfilcnt_t,
+        pub f_fsid: c_ulong,
+        pub f_basetype: [c_char; 16],
+        pub f_flag: c_ulong,
+        pub f_namemax: c_ulong,
+        pub f_fstr: [c_char; 32],
+        f_filler: [c_ulong; 16],
+    }
+
+    pub struct fd_set {
+        fds_bits: [c_int; 32],
+    }
+
+    pub struct Dl_info {
+        pub dli_fname: *const c_char,
+        pub dli_fbase: *mut c_void,
+        pub dli_sname: *const c_char,
+        pub dli_saddr: *mut c_void,
+        pub dli_version: c_int,
+        dli_reserved1: c_int,
+        dli_reserved: [c_long; 4],
+    }
+
+    pub struct lconv {
+        pub decimal_point: *mut c_char,
+        pub thousands_sep: *mut c_char,
+        pub grouping: *mut c_char,
+        pub int_curr_symbol: *mut c_char,
+        pub currency_symbol: *mut c_char,
+        pub mon_decimal_point: *mut c_char,
+        pub mon_thousands_sep: *mut c_char,
+        pub mon_grouping: *mut c_char,
+        pub positive_sign: *mut c_char,
+        pub negative_sign: *mut c_char,
+        pub int_frac_digits: c_char,
+        pub frac_digits: c_char,
+        pub p_cs_precedes: c_char,
+        pub p_sep_by_space: c_char,
+        pub n_cs_precedes: c_char,
+        pub n_sep_by_space: c_char,
+        pub p_sign_posn: c_char,
+        pub n_sign_posn: c_char,
+    }
+
+    pub struct timezone {
+        pub tz_minuteswest: c_int,
+        pub tz_dsttime: c_int,
+    }
+
+    pub struct posix_spawnattr_t {
+        __flags: c_short,
+        __pgroup: pid_t,
+        __sigdefault: sigset_t,
+        __sigmask: sigset_t,
+        __policy: c_int,
+        __param: sched_param,
+    }
+
+    pub struct posix_spawn_file_actions_t {
+        __used: c_int,
+        __allocated: c_int,
+        __actions: *mut c_void,
+    }
+
+    pub struct pthread_attr_t {
+        __D: [c_long; 5],
+    }
+
+    pub struct pthread_mutex_t {
+        __D: [c_long; 8],
+    }
+
+    pub struct pthread_mutexattr_t {
+        __D: [c_long; 2],
+    }
+
+    pub struct pthread_cond_t {
+        __D: [c_long; 8],
+    }
+
+    pub struct pthread_condattr_t {
+        __D: [c_long; 2],
+    }
+
+    pub struct pthread_rwlock_t {
+        __D: [c_long; 16],
+    }
+
+    pub struct pthread_rwlockattr_t {
+        __D: [c_long; 4],
+    }
+
+    // 8-aligned, as IRIX's, by its u64s.
+    pub struct sem_t {
+        sem_reserved: [u64; 8],
+    }
+
+    pub struct itimerspec {
+        pub it_interval: crate::timespec,
+        pub it_value: crate::timespec,
+    }
+
+    pub struct sigevent {
+        pub sigev_notify: c_int,
+        /// A union in IRIX's header with the notification function, which `sigev_notify_function`
+        /// also holds.
+        pub sigev_signo: c_int,
+        pub sigev_value: crate::sigval,
+        pub sigev_notify_function: Option<extern "C" fn(crate::sigval)>,
+        pub sigev_notify_attributes: *mut crate::pthread_attr_t,
+        sigev_reserved: [c_ulong; 11],
+        sigev_pad: [c_ulong; 6],
+    }
+
+    pub struct sembuf {
+        pub sem_num: c_ushort,
+        pub sem_op: c_short,
+        pub sem_flg: c_short,
+    }
+
+    pub struct mntent {
+        pub mnt_fsname: *mut c_char,
+        pub mnt_dir: *mut c_char,
+        pub mnt_type: *mut c_char,
+        pub mnt_opts: *mut c_char,
+        pub mnt_freq: c_int,
+        pub mnt_passno: c_int,
+    }
+
+    /// The toolchain's `<ifaddrs.h>` (IRIX has none).
+    pub struct ifaddrs {
+        pub ifa_next: *mut ifaddrs,
+        pub ifa_name: *mut c_char,
+        pub ifa_flags: c_uint,
+        pub ifa_addr: *mut crate::sockaddr,
+        pub ifa_netmask: *mut crate::sockaddr,
+        pub ifa_dstaddr: *mut crate::sockaddr,
+        pub ifa_data: *mut c_void,
+    }
+
+    /// The toolchain's `<getopt.h>`.
+    pub struct option {
+        pub name: *const c_char,
+        pub has_arg: c_int,
+        pub flag: *mut c_int,
+        pub val: c_int,
+    }
+}
+
+impl siginfo_t {
+    pub unsafe fn si_addr(&self) -> *mut c_void {
+        *(self.__data.as_ptr() as *const *mut c_void)
+    }
+
+    pub unsafe fn si_pid(&self) -> pid_t {
+        self.__data[0]
+    }
+
+    pub unsafe fn si_uid(&self) -> uid_t {
+        self.__data[1]
+    }
+
+    pub unsafe fn si_status(&self) -> c_int {
+        self.__data[2]
+    }
+
+    pub unsafe fn si_value(&self) -> crate::sigval {
+        *(self.__data.as_ptr() as *const crate::sigval)
+    }
+}
+
+pub const PTHREAD_MUTEX_INITIALIZER: pthread_mutex_t = pthread_mutex_t { __D: [0; 8] };
+pub const PTHREAD_COND_INITIALIZER: pthread_cond_t = pthread_cond_t { __D: [0; 8] };
+pub const PTHREAD_RWLOCK_INITIALIZER: pthread_rwlock_t = pthread_rwlock_t { __D: [0; 16] };
+
+
+mod consts;
+pub use self::consts::*;
+
+f! {
+    pub unsafe fn FD_CLR(fd: c_int, set: *mut fd_set) -> () {
+        let fd = fd as usize;
+        (*set).fds_bits[fd / 32] &= !(1 << (fd % 32));
+    }
+
+    pub unsafe fn FD_ISSET(fd: c_int, set: *const fd_set) -> bool {
+        let fd = fd as usize;
+        (*set).fds_bits[fd / 32] & (1 << (fd % 32)) != 0
+    }
+
+    pub unsafe fn FD_SET(fd: c_int, set: *mut fd_set) -> () {
+        let fd = fd as usize;
+        (*set).fds_bits[fd / 32] |= 1 << (fd % 32);
+    }
+
+    pub unsafe fn FD_ZERO(set: *mut fd_set) -> () {
+        for slot in (*set).fds_bits.iter_mut() {
+            *slot = 0;
+        }
+    }
+
+    pub unsafe fn CMSG_FIRSTHDR(mhdr: *const msghdr) -> *mut cmsghdr {
+        if ((*mhdr).msg_controllen as usize) < size_of::<cmsghdr>() {
+            core::ptr::null_mut()
+        } else {
+            (*mhdr).msg_control as *mut cmsghdr
+        }
+    }
+
+    pub unsafe fn CMSG_DATA(cmsg: *const cmsghdr) -> *mut c_uchar {
+        (cmsg as *mut c_uchar).add(CMSG_ALIGN(size_of::<cmsghdr>()))
+    }
+
+    pub const unsafe fn CMSG_ALIGN(len: usize) -> usize {
+        (len + size_of::<c_long>() - 1) & !(size_of::<c_long>() - 1)
+    }
+
+    pub const unsafe fn CMSG_SPACE(length: c_uint) -> c_uint {
+        (CMSG_ALIGN(size_of::<cmsghdr>()) + CMSG_ALIGN(length as usize)) as c_uint
+    }
+
+    pub const unsafe fn CMSG_LEN(length: c_uint) -> c_uint {
+        (CMSG_ALIGN(size_of::<cmsghdr>()) + length as usize) as c_uint
+    }
+
+    pub unsafe fn CMSG_NXTHDR(mhdr: *const msghdr, cmsg: *const cmsghdr) -> *mut cmsghdr {
+        let next = (cmsg as usize) + CMSG_ALIGN((*cmsg).cmsg_len as usize);
+        let max = ((*mhdr).msg_control as usize) + (*mhdr).msg_controllen as usize;
+        if next + CMSG_ALIGN(size_of::<cmsghdr>()) > max {
+            core::ptr::null_mut()
+        } else {
+            next as *mut cmsghdr
+        }
+    }
+}
+
+safe_f! {
+    pub const safe fn WIFEXITED(status: c_int) -> bool {
+        (status & 0xff) == 0
+    }
+
+    pub const safe fn WEXITSTATUS(status: c_int) -> c_int {
+        (status >> 8) & 0xff
+    }
+
+    pub const safe fn WIFSIGNALED(status: c_int) -> bool {
+        (status & 0xff) > 0 && (status & 0xff00) == 0
+    }
+
+    pub const safe fn WTERMSIG(status: c_int) -> c_int {
+        status & 0x7f
+    }
+
+    pub const safe fn WIFSTOPPED(status: c_int) -> bool {
+        (status & 0xff) == 0o177 && (status & 0xff00) != 0
+    }
+
+    pub const safe fn WSTOPSIG(status: c_int) -> c_int {
+        (status >> 8) & 0xff
+    }
+
+    pub const safe fn WIFCONTINUED(status: c_int) -> bool {
+        (status & 0xffff) == 0xffff
+    }
+
+    pub const safe fn WCOREDUMP(status: c_int) -> bool {
+        (status & 0x80) != 0
+    }
+}
+
+/// One page: IRIX's `sysconf(_SC_THREAD_STACK_MIN)` answers 0.
+pub const PTHREAD_STACK_MIN: size_t = 16384;
+pub const F_DUPFD_CLOEXEC: c_int = 1030;
+pub const PTHREAD_ONCE_INIT: pthread_once_t = 0;
+/// The POSIX names for IRIX's `_SC_NPROC_*`.
+pub const _SC_NPROCESSORS_CONF: c_int = _SC_NPROC_CONF;
+pub const _SC_NPROCESSORS_ONLN: c_int = _SC_NPROC_ONLN;
+
+extern "C" {
+    /// The calling thread's `errno` (IRIX's libc keeps a per-thread copy here, and one global).
+    pub fn __oserror() -> *mut c_int;
+
+    #[link_name = "__irix_clock_gettime"]
+    pub fn clock_gettime(clk_id: clockid_t, tp: *mut crate::timespec) -> c_int;
+    #[link_name = "__irix_clock_getres"]
+    pub fn clock_getres(clk_id: clockid_t, tp: *mut crate::timespec) -> c_int;
+    pub fn clock_settime(clk_id: clockid_t, tp: *const crate::timespec) -> c_int;
+
+    pub fn getnameinfo(
+        sa: *const crate::sockaddr,
+        salen: socklen_t,
+        host: *mut c_char,
+        hostlen: socklen_t,
+        serv: *mut c_char,
+        servlen: socklen_t,
+        flags: c_int,
+    ) -> c_int;
+
+    #[link_name = "__irix_recvmsg"]
+    pub fn recvmsg(fd: c_int, msg: *mut msghdr, flags: c_int) -> ssize_t;
+    // The plain symbol takes the BSD msghdr (msg_accrights); this one the XPG one.
+    #[link_name = "__xpg4_sendmsg"]
+    pub fn sendmsg(fd: c_int, msg: *const msghdr, flags: c_int) -> ssize_t;
+
+    // IRIX's own socket calls: their lengths are int, the same size as socklen_t on N32.
+    pub fn bind(socket: c_int, address: *const crate::sockaddr, address_len: socklen_t) -> c_int;
+    pub fn recvfrom(
+        socket: c_int,
+        buf: *mut c_void,
+        len: size_t,
+        flags: c_int,
+        addr: *mut crate::sockaddr,
+        addrlen: *mut socklen_t,
+    ) -> ssize_t;
+    pub fn readv(fd: c_int, iov: *const crate::iovec, iovcnt: c_int) -> ssize_t;
+    pub fn writev(fd: c_int, iov: *const crate::iovec, iovcnt: c_int) -> ssize_t;
+    pub fn setgroups(ngroups: c_int, ptr: *const crate::gid_t) -> c_int;
+
+    pub fn pthread_create(
+        native: *mut crate::pthread_t,
+        attr: *const crate::pthread_attr_t,
+        f: extern "C" fn(*mut c_void) -> *mut c_void,
+        value: *mut c_void,
+    ) -> c_int;
+    pub fn pthread_sigmask(how: c_int, set: *const sigset_t, oldset: *mut sigset_t) -> c_int;
+    pub fn pthread_kill(thread: crate::pthread_t, sig: c_int) -> c_int;
+    pub fn pthread_atfork(
+        prepare: Option<unsafe extern "C" fn()>,
+        parent: Option<unsafe extern "C" fn()>,
+        child: Option<unsafe extern "C" fn()>,
+    ) -> c_int;
+
+    // POSIX 2008 calls IRIX lacks, from our compiler-rt's IRIX builtins.
+    pub fn dirfd(dirp: *mut crate::DIR) -> c_int;
+    pub fn utimensat(
+        dirfd: c_int,
+        path: *const c_char,
+        times: *const crate::timespec,
+        flag: c_int,
+    ) -> c_int;
+
+
+    pub fn sem_timedwait(sem: *mut sem_t, abstime: *const crate::timespec) -> c_int;
+    pub fn getentropy(buf: *mut c_void, buflen: size_t) -> c_int;
+    pub fn arc4random_buf(buf: *mut c_void, nbytes: size_t);
+
+    pub fn posix_spawn(
+        pid: *mut pid_t,
+        path: *const c_char,
+        file_actions: *const posix_spawn_file_actions_t,
+        attrp: *const posix_spawnattr_t,
+        argv: *const *mut c_char,
+        envp: *const *mut c_char,
+    ) -> c_int;
+    pub fn posix_spawnp(
+        pid: *mut pid_t,
+        file: *const c_char,
+        file_actions: *const posix_spawn_file_actions_t,
+        attrp: *const posix_spawnattr_t,
+        argv: *const *mut c_char,
+        envp: *const *mut c_char,
+    ) -> c_int;
+    pub fn posix_spawnattr_init(attr: *mut posix_spawnattr_t) -> c_int;
+    pub fn posix_spawnattr_destroy(attr: *mut posix_spawnattr_t) -> c_int;
+    pub fn posix_spawnattr_setflags(attr: *mut posix_spawnattr_t, flags: c_short) -> c_int;
+    pub fn posix_spawnattr_setsigdefault(attr: *mut posix_spawnattr_t, default: *const sigset_t) -> c_int;
+    pub fn posix_spawnattr_setsigmask(attr: *mut posix_spawnattr_t, default: *const sigset_t) -> c_int;
+    pub fn posix_spawnattr_setpgroup(attr: *mut posix_spawnattr_t, flags: pid_t) -> c_int;
+    pub fn posix_spawn_file_actions_init(actions: *mut posix_spawn_file_actions_t) -> c_int;
+    pub fn posix_spawn_file_actions_destroy(actions: *mut posix_spawn_file_actions_t) -> c_int;
+    pub fn posix_spawn_file_actions_addopen(
+        actions: *mut posix_spawn_file_actions_t,
+        fd: c_int,
+        path: *const c_char,
+        oflag: c_int,
+        mode: mode_t,
+    ) -> c_int;
+    pub fn posix_spawn_file_actions_addclose(actions: *mut posix_spawn_file_actions_t, fd: c_int) -> c_int;
+    pub fn posix_spawn_file_actions_adddup2(
+        actions: *mut posix_spawn_file_actions_t,
+        fd: c_int,
+        newfd: c_int,
+    ) -> c_int;
+
+    pub fn sigaltstack(ss: *const stack_t, oss: *mut stack_t) -> c_int;
+    pub fn ioctl(fd: c_int, request: c_int, ...) -> c_int;
+    pub fn getpwuid_r(
+        uid: uid_t,
+        pwd: *mut passwd,
+        buf: *mut c_char,
+        buflen: size_t,
+        result: *mut *mut passwd,
+    ) -> c_int;
+    pub fn strerror_r(errnum: c_int, buf: *mut c_char, buflen: size_t) -> c_int;
+    pub fn memalign(align: size_t, size: size_t) -> *mut c_void;
+    pub fn madvise(addr: *mut c_void, len: size_t, advice: c_int) -> c_int;
+    pub fn settimeofday(tp: *const crate::timeval, tz: *const c_void) -> c_int;
+}
+
+// Generated from clang's AST of the IRIX headers as this target's C toolchain sees them (header
+// wrappers included), with parameter names borrowed from libc's other platforms.
+extern "C" {
+    pub fn abs(i: c_int) -> c_int;
+    pub fn acct(filename: *const c_char) -> c_int;
+    pub fn arc4random() -> c_uint;
+    pub fn arc4random_uniform(l: c_uint) -> c_uint;
+    pub fn basename(path: *mut c_char) -> *mut c_char;
+    pub fn brk(addr: *mut c_void) -> c_int;
+    pub fn ctermid(s: *mut c_char) -> *mut c_char;
+    pub fn daemon(nochdir: c_int, noclose: c_int) -> c_int;
+    pub fn dirname(path: *mut c_char) -> *mut c_char;
+    pub fn drand48() -> c_double;
+    pub fn duplocale(base: crate::locale_t) -> crate::locale_t;
+    pub fn endgrent();
+    pub fn endmntent(streamp: *mut crate::FILE) -> c_int;
+    pub fn endpwent();
+    pub fn erand48(arg1: *mut c_ushort) -> c_double;
+    pub fn faccessat(dirfd: c_int, pathname: *const c_char, mode: c_int, flags: c_int) -> c_int;
+    pub fn fdatasync(fd: c_int) -> c_int;
+    pub fn ffs(arg1: c_int) -> c_int;
+    pub fn fgetgrent(file: *mut crate::FILE) -> *mut crate::group;
+    pub fn fgetpwent(file: *mut crate::FILE) -> *mut crate::passwd;
+    pub fn freeifaddrs(ifa: *mut crate::ifaddrs);
+    pub fn freelocale(loc: crate::locale_t);
+    pub fn ftok(pathname: *const c_char, proj_id: c_int) -> crate::key_t;
+    pub fn getdomainname(name: *mut c_char, len: c_int) -> c_int;
+    pub fn getdtablesize() -> c_int;
+    pub fn getgrent() -> *mut crate::group;
+    pub fn getgrgid(gid: crate::gid_t) -> *mut crate::group;
+    pub fn getgrgid_r(
+        gid: crate::gid_t,
+        grp: *mut crate::group,
+        buf: *mut c_char,
+        buflen: size_t,
+        result: *mut *mut crate::group,
+    ) -> c_int;
+    pub fn getgrnam(name: *const c_char) -> *mut crate::group;
+    pub fn getgrnam_r(
+        name: *const c_char,
+        grp: *mut crate::group,
+        buf: *mut c_char,
+        buflen: size_t,
+        result: *mut *mut crate::group,
+    ) -> c_int;
+    pub fn getgrouplist(
+        user: *const c_char,
+        group: crate::gid_t,
+        groups: *mut crate::gid_t,
+        ngroups: *mut c_int,
+    ) -> c_int;
+    pub fn gethostid() -> c_long;
+    pub fn getifaddrs(ifap: *mut *mut crate::ifaddrs) -> c_int;
+    pub fn getitimer(which: c_int, curr_value: *mut crate::itimerval) -> c_int;
+    pub fn getmntent(stream: *mut crate::FILE) -> *mut crate::mntent;
+    pub fn getopt_long(
+        argc: c_int,
+        argv: *const *mut c_char,
+        optstring: *const c_char,
+        longopts: *const crate::option,
+        longindex: *mut c_int,
+    ) -> c_int;
+    pub fn getpagesize() -> c_int;
+    pub fn getpriority(which: c_int, who: crate::id_t) -> c_int;
+    pub fn getprogname() -> *const c_char;
+    pub fn getpwent() -> *mut crate::passwd;
+    pub fn getpwnam_r(
+        name: *const c_char,
+        pwd: *mut crate::passwd,
+        buf: *mut c_char,
+        buflen: size_t,
+        result: *mut *mut crate::passwd,
+    ) -> c_int;
+    pub fn getrlimit(resource: c_int, rlim: *mut crate::rlimit) -> c_int;
+    pub fn hasmntopt(mnt: *const crate::mntent, opt: *const c_char) -> *mut c_char;
+    pub fn iconv(
+        cd: crate::iconv_t,
+        inbuf: *mut *mut c_char,
+        inbytesleft: *mut size_t,
+        outbuf: *mut *mut c_char,
+        outbytesleft: *mut size_t,
+    ) -> size_t;
+    pub fn iconv_close(cd: crate::iconv_t) -> c_int;
+    pub fn iconv_open(tocode: *const c_char, fromcode: *const c_char) -> crate::iconv_t;
+    pub fn initgroups(user: *const c_char, group: crate::gid_t) -> c_int;
+    pub fn jrand48(arg1: *mut c_ushort) -> c_long;
+    pub fn labs(i: c_long) -> c_long;
+    pub fn lcong48(arg1: *mut c_ushort);
+    pub fn lrand48() -> c_long;
+    pub fn memmem(
+        arg1: *const c_void,
+        arg2: size_t,
+        arg3: *const c_void,
+        arg4: size_t,
+    ) -> *mut c_void;
+    pub fn memrchr(cx: *const c_void, c: c_int, n: size_t) -> *mut c_void;
+    pub fn mincore(addr: crate::caddr_t, len: size_t, vec: *mut c_char) -> c_int;
+    pub fn mkfifoat(dirfd: c_int, pathname: *const c_char, mode: crate::mode_t) -> c_int;
+    pub fn mknodat(
+        dirfd: c_int,
+        pathname: *const c_char,
+        mode: crate::mode_t,
+        dev: crate::dev_t,
+    ) -> c_int;
+    pub fn mkostemp(template: *mut c_char, flags: c_int) -> c_int;
+    pub fn mount(device: *const c_char, path: *const c_char, flags: c_int, ...) -> c_int;
+    pub fn mprotect(addr: *mut c_void, len: size_t, prot: c_int) -> c_int;
+    pub fn mrand48() -> c_long;
+    pub fn msgctl(arg0: c_int, arg1: c_int, ...) -> c_int;
+    pub fn msgget(key: crate::key_t, msgflg: c_int) -> c_int;
+    pub fn msgrcv(
+        msqid: c_int,
+        msgp: *mut c_void,
+        msgsz: size_t,
+        msgtyp: c_long,
+        msgflg: c_int,
+    ) -> c_int;
+    pub fn msgsnd(msqid: c_int, msgp: *const c_void, msgsz: size_t, msgflg: c_int) -> c_int;
+    pub fn msync(addr: *mut c_void, len: size_t, flags: c_int) -> c_int;
+    pub fn newlocale(mask: c_int, locale: *const c_char, base: crate::locale_t) -> crate::locale_t;
+    pub fn nl_langinfo(item: crate::nl_item) -> *mut c_char;
+    pub fn nrand48(arg1: *mut c_ushort) -> c_long;
+    pub fn popen(command: *const c_char, mode: *const c_char) -> *mut crate::FILE;
+    pub fn posix_spawn_file_actions_addchdir(
+        actions: *mut crate::posix_spawn_file_actions_t,
+        path: *const c_char,
+    ) -> c_int;
+    pub fn posix_spawn_file_actions_addfchdir(
+        actions: *mut crate::posix_spawn_file_actions_t,
+        fd: c_int,
+    ) -> c_int;
+    pub fn posix_spawnattr_getflags(
+        attr: *const crate::posix_spawnattr_t,
+        flags: *mut c_short,
+    ) -> c_int;
+    pub fn posix_spawnattr_getpgroup(
+        attr: *const crate::posix_spawnattr_t,
+        flags: *mut crate::pid_t,
+    ) -> c_int;
+    pub fn posix_spawnattr_getschedparam(
+        attr: *const crate::posix_spawnattr_t,
+        param: *mut crate::sched_param,
+    ) -> c_int;
+    pub fn posix_spawnattr_getschedpolicy(
+        attr: *const crate::posix_spawnattr_t,
+        flags: *mut c_int,
+    ) -> c_int;
+    pub fn posix_spawnattr_getsigdefault(
+        attr: *const crate::posix_spawnattr_t,
+        default: *mut crate::sigset_t,
+    ) -> c_int;
+    pub fn posix_spawnattr_getsigmask(
+        attr: *const crate::posix_spawnattr_t,
+        default: *mut crate::sigset_t,
+    ) -> c_int;
+    pub fn posix_spawnattr_setschedparam(
+        attr: *mut crate::posix_spawnattr_t,
+        param: *const crate::sched_param,
+    ) -> c_int;
+    pub fn posix_spawnattr_setschedpolicy(
+        attr: *mut crate::posix_spawnattr_t,
+        flags: c_int,
+    ) -> c_int;
+    pub fn pthread_attr_getdetachstate(
+        attr: *const crate::pthread_attr_t,
+        detachstate: *mut c_int,
+    ) -> c_int;
+    pub fn pthread_attr_getguardsize(
+        attr: *const crate::pthread_attr_t,
+        guardsize: *mut size_t,
+    ) -> c_int;
+    pub fn pthread_attr_getinheritsched(
+        attr: *const crate::pthread_attr_t,
+        inheritsched: *mut c_int,
+    ) -> c_int;
+    pub fn pthread_attr_getschedparam(
+        attr: *const crate::pthread_attr_t,
+        param: *mut crate::sched_param,
+    ) -> c_int;
+    pub fn pthread_attr_getschedpolicy(
+        attr: *const crate::pthread_attr_t,
+        policy: *mut c_int,
+    ) -> c_int;
+    pub fn pthread_attr_getscope(attr: *const crate::pthread_attr_t, scope: *mut c_int) -> c_int;
+    pub fn pthread_attr_getstackaddr(
+        attr: *const crate::pthread_attr_t,
+        stackaddr: *mut *mut c_void,
+    ) -> c_int;
+    pub fn pthread_attr_setguardsize(attr: *mut crate::pthread_attr_t, guardsize: size_t) -> c_int;
+    pub fn pthread_attr_setinheritsched(
+        attr: *mut crate::pthread_attr_t,
+        inheritsched: c_int,
+    ) -> c_int;
+    pub fn pthread_attr_setschedparam(
+        attr: *mut crate::pthread_attr_t,
+        param: *const crate::sched_param,
+    ) -> c_int;
+    pub fn pthread_attr_setschedpolicy(attr: *mut crate::pthread_attr_t, policy: c_int) -> c_int;
+    pub fn pthread_attr_setscope(attr: *mut crate::pthread_attr_t, scope: c_int) -> c_int;
+    pub fn pthread_attr_setstackaddr(
+        attr: *mut crate::pthread_attr_t,
+        stackaddr: *mut c_void,
+    ) -> c_int;
+    pub fn pthread_cancel(thread: crate::pthread_t) -> c_int;
+    pub fn pthread_condattr_getpshared(
+        attr: *const crate::pthread_condattr_t,
+        pshared: *mut c_int,
+    ) -> c_int;
+    pub fn pthread_condattr_setpshared(
+        attr: *mut crate::pthread_condattr_t,
+        pshared: c_int,
+    ) -> c_int;
+    pub fn pthread_getconcurrency() -> c_int;
+    pub fn pthread_getschedparam(
+        native: crate::pthread_t,
+        policy: *mut c_int,
+        param: *mut crate::sched_param,
+    ) -> c_int;
+    pub fn pthread_mutex_getprioceiling(
+        mutex: *const crate::pthread_mutex_t,
+        prioceiling: *mut c_int,
+    ) -> c_int;
+    pub fn pthread_mutex_setprioceiling(
+        mutex: *mut crate::pthread_mutex_t,
+        prioceiling: c_int,
+        old_ceiling: *mut c_int,
+    ) -> c_int;
+    pub fn pthread_mutexattr_getprioceiling(
+        attr: *const crate::pthread_mutexattr_t,
+        prioceiling: *mut c_int,
+    ) -> c_int;
+    pub fn pthread_mutexattr_getprotocol(
+        attr: *const crate::pthread_mutexattr_t,
+        protocol: *mut c_int,
+    ) -> c_int;
+    pub fn pthread_mutexattr_getpshared(
+        attr: *const crate::pthread_mutexattr_t,
+        pshared: *mut c_int,
+    ) -> c_int;
+    pub fn pthread_mutexattr_gettype(
+        attr: *const crate::pthread_mutexattr_t,
+        kind: *mut c_int,
+    ) -> c_int;
+    pub fn pthread_mutexattr_setprioceiling(
+        attr: *mut crate::pthread_mutexattr_t,
+        prioceiling: c_int,
+    ) -> c_int;
+    pub fn pthread_mutexattr_setprotocol(
+        attr: *mut crate::pthread_mutexattr_t,
+        protocol: c_int,
+    ) -> c_int;
+    pub fn pthread_mutexattr_setpshared(
+        attr: *mut crate::pthread_mutexattr_t,
+        pshared: c_int,
+    ) -> c_int;
+    pub fn pthread_rwlockattr_getpshared(
+        attr: *const crate::pthread_rwlockattr_t,
+        val: *mut c_int,
+    ) -> c_int;
+    pub fn pthread_rwlockattr_setpshared(
+        attr: *mut crate::pthread_rwlockattr_t,
+        val: c_int,
+    ) -> c_int;
+    pub fn pthread_setcancelstate(state: c_int, oldstate: *mut c_int) -> c_int;
+    pub fn pthread_setcanceltype(r#type: c_int, oldtype: *mut c_int) -> c_int;
+    pub fn pthread_setconcurrency(new_level: c_int) -> c_int;
+    pub fn pthread_setschedparam(
+        native: crate::pthread_t,
+        policy: c_int,
+        param: *const crate::sched_param,
+    ) -> c_int;
+    pub fn pthread_testcancel();
+    pub fn rand() -> c_int;
+    pub fn sbrk(increment: ssize_t) -> *mut c_void;
+    pub fn sched_get_priority_max(policy: c_int) -> c_int;
+    pub fn sched_get_priority_min(policy: c_int) -> c_int;
+    pub fn sched_getparam(pid: crate::pid_t, param: *mut crate::sched_param) -> c_int;
+    pub fn sched_getscheduler(pid: crate::pid_t) -> c_int;
+    pub fn sched_rr_get_interval(pid: crate::pid_t, tp: *mut crate::timespec) -> c_int;
+    pub fn sched_setparam(pid: crate::pid_t, param: *const crate::sched_param) -> c_int;
+    pub fn sched_setscheduler(
+        pid: crate::pid_t,
+        policy: c_int,
+        param: *const crate::sched_param,
+    ) -> c_int;
+    pub fn seed48(arg1: *mut c_ushort) -> *mut c_ushort;
+    pub fn seekdir(dirp: *mut crate::DIR, loc: crate::off_t);
+    pub fn sem_close(sem: *mut crate::sem_t) -> c_int;
+    pub fn sem_destroy(sem: *mut crate::sem_t) -> c_int;
+    pub fn sem_getvalue(sem: *mut crate::sem_t, sval: *mut c_int) -> c_int;
+    pub fn sem_init(sem: *mut crate::sem_t, pshared: c_int, value: c_uint) -> c_int;
+    pub fn sem_open(name: *const c_char, oflag: c_int, ...) -> *mut crate::sem_t;
+    pub fn sem_unlink(name: *const c_char) -> c_int;
+    pub fn semctl(semid: c_int, semnum: c_int, cmd: c_int, ...) -> c_int;
+    pub fn semget(key: crate::key_t, nsems: c_int, semflag: c_int) -> c_int;
+    pub fn semop(semid: c_int, sops: *mut crate::sembuf, nsops: size_t) -> c_int;
+    pub fn setdomainname(name: *const c_char, len: c_int) -> c_int;
+    pub fn setgrent();
+    pub fn sethostid(hostid: c_int) -> c_int;
+    pub fn sethostname(name: *const c_char, len: c_int) -> c_int;
+    pub fn setitimer(
+        which: c_int,
+        new_value: *const crate::itimerval,
+        old_value: *mut crate::itimerval,
+    ) -> c_int;
+    pub fn setmntent(filename: *const c_char, ty: *const c_char) -> *mut crate::FILE;
+    pub fn setpriority(which: c_int, who: crate::id_t, priority: c_int) -> c_int;
+    pub fn setprogname(arg1: *const c_char);
+    pub fn setpwent();
+    pub fn setrlimit(resource: c_int, rlim: *const crate::rlimit) -> c_int;
+    pub fn shm_open(name: *const c_char, oflag: c_int, mode: crate::mode_t) -> c_int;
+    pub fn shm_unlink(name: *const c_char) -> c_int;
+    pub fn shmat(shmid: c_int, shmaddr: *const c_void, shmflg: c_int) -> *mut c_void;
+    pub fn shmctl(arg0: c_int, arg1: c_int, ...) -> c_int;
+    pub fn shmdt(shmaddr: *const c_void) -> c_int;
+    pub fn shmget(key: crate::key_t, size: size_t, shmflg: c_int) -> c_int;
+    pub fn sigsuspend(mask: *const crate::sigset_t) -> c_int;
+    pub fn sigtimedwait(
+        set: *const crate::sigset_t,
+        info: *mut crate::siginfo_t,
+        timeout: *const crate::timespec,
+    ) -> c_int;
+    pub fn sigwait(set: *const crate::sigset_t, sig: *mut c_int) -> c_int;
+    pub fn sigwaitinfo(set: *const crate::sigset_t, info: *mut crate::siginfo_t) -> c_int;
+    pub fn srand(seed: c_uint);
+    pub fn srand48(arg1: c_long);
+    pub fn strftime(
+        s: *mut c_char,
+        maxsize: size_t,
+        format: *const c_char,
+        timeptr: *const crate::tm,
+    ) -> size_t;
+    pub fn strptime(s: *const c_char, format: *const c_char, tm: *mut crate::tm) -> *mut c_char;
+    pub fn strsep(arg1: *mut *mut c_char, arg2: *const c_char) -> *mut c_char;
+    pub fn sync();
+    pub fn sysinfo(command: c_int, buf: *mut c_char, count: c_long) -> c_int;
+    pub fn telldir(dirp: *mut crate::DIR) -> crate::off_t;
+    pub fn timer_create(
+        clockid: crate::clockid_t,
+        evp: *mut crate::sigevent,
+        timerid: *mut crate::timer_t,
+    ) -> c_int;
+    pub fn timer_delete(timerid: crate::timer_t) -> c_int;
+    pub fn timer_getoverrun(timerid: crate::timer_t) -> c_int;
+    pub fn timer_gettime(timerid: crate::timer_t, value: *mut crate::itimerspec) -> c_int;
+    pub fn timer_settime(
+        timerid: crate::timer_t,
+        flags: c_int,
+        value: *const crate::itimerspec,
+        ovalue: *mut crate::itimerspec,
+    ) -> c_int;
+    pub fn uname(buf: *mut crate::utsname) -> c_int;
+    pub fn uselocale(loc: crate::locale_t) -> crate::locale_t;
+    pub fn vfork() -> crate::pid_t;
+    pub fn waitid(
+        idtype: c_int,
+        id: crate::id_t,
+        infop: *mut crate::siginfo_t,
+        options: c_int,
+    ) -> c_int;
+
+    pub fn gettimeofday(tp: *mut crate::timeval, tz: *mut c_void) -> c_int;
+    pub fn pthread_once(control: *mut pthread_once_t, routine: extern "C" fn()) -> c_int;
+}
