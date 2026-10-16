$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/errno.rs.orig
+++ nix-0.29.0/src/errno.rs
@@ -48,6 +48,10 @@
         unsafe fn errno_location() -> *mut c_int {
             unsafe { libc::_Errno() }
         }
+    } else if #[cfg(target_os = "irix")] {
+        unsafe fn errno_location() -> *mut c_int {
+            unsafe { libc::__oserror() }
+        }
     }
 }
 
@@ -277,7 +281,8 @@
             linux_android,
             solarish,
             target_os = "aix",
-            target_os = "fuchsia"
+            target_os = "fuchsia",
+            target_os = "irix",
         ))]
         ECHRNG => "Channel number out of range",
 
@@ -285,7 +290,8 @@
             linux_android,
             solarish,
             target_os = "aix",
-            target_os = "fuchsia"
+            target_os = "fuchsia",
+            target_os = "irix",
         ))]
         EL2NSYNC => "Level 2 not synchronized",
 
@@ -293,7 +299,8 @@
             linux_android,
             solarish,
             target_os = "aix",
-            target_os = "fuchsia"
+            target_os = "fuchsia",
+            target_os = "irix",
         ))]
         EL3HLT => "Level 3 halted",
 
@@ -301,7 +308,8 @@
             linux_android,
             solarish,
             target_os = "aix",
-            target_os = "fuchsia"
+            target_os = "fuchsia",
+            target_os = "irix",
         ))]
         EL3RST => "Level 3 reset",
 
@@ -309,7 +317,8 @@
             linux_android,
             solarish,
             target_os = "aix",
-            target_os = "fuchsia"
+            target_os = "fuchsia",
+            target_os = "irix",
         ))]
         ELNRNG => "Link number out of range",
 
@@ -317,7 +326,8 @@
             linux_android,
             solarish,
             target_os = "aix",
-            target_os = "fuchsia"
+            target_os = "fuchsia",
+            target_os = "irix",
         ))]
         EUNATCH => "Protocol driver not attached",
 
@@ -325,7 +335,8 @@
             linux_android,
             solarish,
             target_os = "aix",
-            target_os = "fuchsia"
+            target_os = "fuchsia",
+            target_os = "irix",
         ))]
         ENOCSI => "No CSI structure available",
 
@@ -333,36 +344,38 @@
             linux_android,
             solarish,
             target_os = "aix",
-            target_os = "fuchsia"
+            target_os = "fuchsia",
+            target_os = "irix",
         ))]
         EL2HLT => "Level 2 halted",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         EBADE => "Invalid exchange",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         EBADR => "Invalid request descriptor",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         EXFULL => "Exchange full",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         ENOANO => "No anode",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         EBADRQC => "Invalid request code",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         EBADSLT => "Invalid slot",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         EBFONT => "Bad font file format",
 
         #[cfg(any(
             linux_android,
             solarish,
             target_os = "fuchsia",
-            target_os = "hurd"
+            target_os = "hurd",
+            target_os = "irix",
         ))]
         ENOSTR => "Device not a stream",
 
@@ -370,7 +383,8 @@
             linux_android,
             solarish,
             target_os = "fuchsia",
-            target_os = "hurd"
+            target_os = "hurd",
+            target_os = "irix",
         ))]
         ENODATA => "No data available",
 
@@ -378,7 +392,8 @@
             linux_android,
             solarish,
             target_os = "fuchsia",
-            target_os = "hurd"
+            target_os = "hurd",
+            target_os = "irix",
         ))]
         ETIME => "Timer expired",
 
@@ -386,21 +401,23 @@
             linux_android,
             solarish,
             target_os = "fuchsia",
-            target_os = "hurd"
+            target_os = "hurd",
+            target_os = "irix",
         ))]
         ENOSR => "Out of streams resources",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         ENONET => "Machine is not on the network",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         ENOPKG => "Package not installed",
 
         #[cfg(any(
             linux_android,
             solarish,
             target_os = "fuchsia",
-            target_os = "hurd"
+            target_os = "hurd",
+            target_os = "irix",
         ))]
         EREMOTE => "Object is remote",
 
@@ -408,17 +425,18 @@
             linux_android,
             solarish,
             target_os = "aix",
-            target_os = "fuchsia"
+            target_os = "fuchsia",
+            target_os = "irix",
         ))]
         ENOLINK => "Link has been severed",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         EADV => "Advertise error",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         ESRMNT => "Srmount error",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         ECOMM => "Communication error on send",
 
         #[cfg(any(
@@ -426,6 +444,7 @@
             solarish,
             target_os = "aix",
             target_os = "fuchsia",
+            target_os = "irix",
         ))]
         EPROTO => "Protocol error",
 
@@ -433,7 +452,8 @@
             linux_android,
             solarish,
             target_os = "aix",
-            target_os = "fuchsia"
+            target_os = "fuchsia",
+            target_os = "irix",
         ))]
         EMULTIHOP => "Multihop attempted",
 
@@ -443,7 +463,7 @@
         #[cfg(any(linux_android, target_os = "aix", target_os = "fuchsia"))]
         EBADMSG => "Not a data message",
 
-        #[cfg(solarish)]
+        #[cfg(any(solarish, target_os = "irix"))]
         EBADMSG => "Trying to read unreadable message",
 
         #[cfg(any(
@@ -455,32 +475,33 @@
         ))]
         EOVERFLOW => "Value too large for defined data type",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         ENOTUNIQ => "Name not unique on network",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         EBADFD => "File descriptor in bad state",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         EREMCHG => "Remote address changed",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         ELIBACC => "Can not access a needed shared library",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         ELIBBAD => "Accessing a corrupted shared library",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         ELIBSCN => ".lib section in a.out corrupted",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         ELIBMAX => "Attempting to link in too many shared libraries",
 
         #[cfg(any(
             linux_android,
             solarish,
             target_os = "fuchsia",
-            target_os = "hurd"
+            target_os = "hurd",
+            target_os = "irix",
         ))]
         ELIBEXEC => "Cannot exec a shared library directly",
 
@@ -489,7 +510,8 @@
             solarish,
             target_os = "aix",
             target_os = "fuchsia",
-            target_os = "openbsd"
+            target_os = "openbsd",
+            target_os = "irix",
         ))]
         EILSEQ => "Illegal byte sequence",
 
@@ -497,14 +519,15 @@
             linux_android,
             solarish,
             target_os = "aix",
-            target_os = "fuchsia"
+            target_os = "fuchsia",
+            target_os = "irix",
         ))]
         ERESTART => "Interrupted system call should be restarted",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         ESTRPIPE => "Streams pipe error",
 
-        #[cfg(any(linux_android, solarish, target_os = "fuchsia"))]
+        #[cfg(any(linux_android, solarish, target_os = "fuchsia", target_os = "irix"))]
         EUSERS => "Too many users",
 
         #[cfg(any(
@@ -555,7 +578,8 @@
             linux_android,
             solarish,
             target_os = "fuchsia",
-            target_os = "haiku"
+            target_os = "haiku",
+            target_os = "irix",
         ))]
         ECANCELED => "Operation canceled",
 
@@ -618,7 +642,7 @@
         #[cfg(any(bsd, target_os = "hurd"))]
         ENEEDAUTH => "Need authenticator",
 
-        #[cfg(any(bsd, target_os = "redox", solarish))]
+        #[cfg(any(bsd, target_os = "redox", solarish, target_os = "irix"))]
         EOVERFLOW => "Value too large to be stored in data type",
 
         #[cfg(any(
@@ -666,7 +690,8 @@
             target_os = "aix",
             solarish,
             target_os = "haiku",
-            target_os = "hurd"
+            target_os = "hurd",
+            target_os = "irix",
         ))]
         ENOTSUP => "Operation not supported",
 
@@ -687,7 +712,8 @@
             target_os = "redox",
             target_os = "aix",
             target_os = "haiku",
-            target_os = "hurd"
+            target_os = "hurd",
+            target_os = "irix",
         ))]
         EDQUOT => "Disc quota exceeded",
 
@@ -696,7 +722,8 @@
             solarish,
             target_os = "redox",
             target_os = "aix",
-            target_os = "haiku"
+            target_os = "haiku",
+            target_os = "irix",
         ))]
         ESTALE => "Stale NFS file handle",
 
@@ -788,7 +815,7 @@
         ))]
         ETIME => "STREAM ioctl timeout",
 
-        #[cfg(any(apple_targets, solarish, target_os = "aix"))]
+        #[cfg(any(apple_targets, solarish, target_os = "aix", target_os = "irix"))]
         EOPNOTSUPP => "Operation not supported on socket",
 
         #[cfg(apple_targets)]
@@ -806,7 +833,7 @@
         #[cfg(target_os = "dragonfly")]
         EASYNC => "Async",
 
-        #[cfg(solarish)]
+        #[cfg(any(solarish, target_os = "irix"))]
         EDEADLOCK => "Resource deadlock would occur",
 
         #[cfg(solarish)]
@@ -2657,6 +2684,266 @@
             libc::EMULTIHOP => EMULTIHOP,
             libc::EBADMSG => EBADMSG,
             libc::ENAMETOOLONG => ENAMETOOLONG,
+            libc::EOVERFLOW => EOVERFLOW,
+            libc::ENOTUNIQ => ENOTUNIQ,
+            libc::EBADFD => EBADFD,
+            libc::EREMCHG => EREMCHG,
+            libc::ELIBACC => ELIBACC,
+            libc::ELIBBAD => ELIBBAD,
+            libc::ELIBSCN => ELIBSCN,
+            libc::ELIBMAX => ELIBMAX,
+            libc::ELIBEXEC => ELIBEXEC,
+            libc::EILSEQ => EILSEQ,
+            libc::ENOSYS => ENOSYS,
+            libc::ELOOP => ELOOP,
+            libc::ERESTART => ERESTART,
+            libc::ESTRPIPE => ESTRPIPE,
+            libc::ENOTEMPTY => ENOTEMPTY,
+            libc::EUSERS => EUSERS,
+            libc::ENOTSOCK => ENOTSOCK,
+            libc::EDESTADDRREQ => EDESTADDRREQ,
+            libc::EMSGSIZE => EMSGSIZE,
+            libc::EPROTOTYPE => EPROTOTYPE,
+            libc::ENOPROTOOPT => ENOPROTOOPT,
+            libc::EPROTONOSUPPORT => EPROTONOSUPPORT,
+            libc::ESOCKTNOSUPPORT => ESOCKTNOSUPPORT,
+            libc::EOPNOTSUPP => EOPNOTSUPP,
+            libc::EPFNOSUPPORT => EPFNOSUPPORT,
+            libc::EAFNOSUPPORT => EAFNOSUPPORT,
+            libc::EADDRINUSE => EADDRINUSE,
+            libc::EADDRNOTAVAIL => EADDRNOTAVAIL,
+            libc::ENETDOWN => ENETDOWN,
+            libc::ENETUNREACH => ENETUNREACH,
+            libc::ENETRESET => ENETRESET,
+            libc::ECONNABORTED => ECONNABORTED,
+            libc::ECONNRESET => ECONNRESET,
+            libc::ENOBUFS => ENOBUFS,
+            libc::EISCONN => EISCONN,
+            libc::ENOTCONN => ENOTCONN,
+            libc::ESHUTDOWN => ESHUTDOWN,
+            libc::ETOOMANYREFS => ETOOMANYREFS,
+            libc::ETIMEDOUT => ETIMEDOUT,
+            libc::ECONNREFUSED => ECONNREFUSED,
+            libc::EHOSTDOWN => EHOSTDOWN,
+            libc::EHOSTUNREACH => EHOSTUNREACH,
+            libc::EALREADY => EALREADY,
+            libc::EINPROGRESS => EINPROGRESS,
+            libc::ESTALE => ESTALE,
+            _ => UnknownErrno,
+        }
+    }
+}
+
+#[cfg(target_os = "irix")]
+mod consts {
+    #[derive(Clone, Copy, Debug, Eq, PartialEq)]
+    #[repr(i32)]
+    #[non_exhaustive]
+    pub enum Errno {
+        UnknownErrno = 0,
+        EPERM = libc::EPERM,
+        ENOENT = libc::ENOENT,
+        ESRCH = libc::ESRCH,
+        EINTR = libc::EINTR,
+        EIO = libc::EIO,
+        ENXIO = libc::ENXIO,
+        E2BIG = libc::E2BIG,
+        ENOEXEC = libc::ENOEXEC,
+        EBADF = libc::EBADF,
+        ECHILD = libc::ECHILD,
+        EAGAIN = libc::EAGAIN,
+        ENOMEM = libc::ENOMEM,
+        EACCES = libc::EACCES,
+        EFAULT = libc::EFAULT,
+        ENOTBLK = libc::ENOTBLK,
+        EBUSY = libc::EBUSY,
+        EEXIST = libc::EEXIST,
+        EXDEV = libc::EXDEV,
+        ENODEV = libc::ENODEV,
+        ENOTDIR = libc::ENOTDIR,
+        EISDIR = libc::EISDIR,
+        EINVAL = libc::EINVAL,
+        ENFILE = libc::ENFILE,
+        EMFILE = libc::EMFILE,
+        ENOTTY = libc::ENOTTY,
+        ETXTBSY = libc::ETXTBSY,
+        EFBIG = libc::EFBIG,
+        ENOSPC = libc::ENOSPC,
+        ESPIPE = libc::ESPIPE,
+        EROFS = libc::EROFS,
+        EMLINK = libc::EMLINK,
+        EPIPE = libc::EPIPE,
+        EDOM = libc::EDOM,
+        ERANGE = libc::ERANGE,
+        ENOMSG = libc::ENOMSG,
+        EIDRM = libc::EIDRM,
+        ECHRNG = libc::ECHRNG,
+        EL2NSYNC = libc::EL2NSYNC,
+        EL3HLT = libc::EL3HLT,
+        EL3RST = libc::EL3RST,
+        ELNRNG = libc::ELNRNG,
+        EUNATCH = libc::EUNATCH,
+        ENOCSI = libc::ENOCSI,
+        EL2HLT = libc::EL2HLT,
+        EDEADLK = libc::EDEADLK,
+        ENOLCK = libc::ENOLCK,
+        ECANCELED = libc::ECANCELED,
+        ENOTSUP = libc::ENOTSUP,
+        EDQUOT = libc::EDQUOT,
+        EBADE = libc::EBADE,
+        EBADR = libc::EBADR,
+        EXFULL = libc::EXFULL,
+        ENOANO = libc::ENOANO,
+        EBADRQC = libc::EBADRQC,
+        EBADSLT = libc::EBADSLT,
+        EDEADLOCK = libc::EDEADLOCK,
+        EBFONT = libc::EBFONT,
+        ENOSTR = libc::ENOSTR,
+        ENODATA = libc::ENODATA,
+        ETIME = libc::ETIME,
+        ENOSR = libc::ENOSR,
+        ENONET = libc::ENONET,
+        ENOPKG = libc::ENOPKG,
+        EREMOTE = libc::EREMOTE,
+        ENOLINK = libc::ENOLINK,
+        EADV = libc::EADV,
+        ESRMNT = libc::ESRMNT,
+        ECOMM = libc::ECOMM,
+        EPROTO = libc::EPROTO,
+        EMULTIHOP = libc::EMULTIHOP,
+        EBADMSG = libc::EBADMSG,
+        ENAMETOOLONG = libc::ENAMETOOLONG,
+        EOVERFLOW = libc::EOVERFLOW,
+        ENOTUNIQ = libc::ENOTUNIQ,
+        EBADFD = libc::EBADFD,
+        EREMCHG = libc::EREMCHG,
+        ELIBACC = libc::ELIBACC,
+        ELIBBAD = libc::ELIBBAD,
+        ELIBSCN = libc::ELIBSCN,
+        ELIBMAX = libc::ELIBMAX,
+        ELIBEXEC = libc::ELIBEXEC,
+        EILSEQ = libc::EILSEQ,
+        ENOSYS = libc::ENOSYS,
+        ELOOP = libc::ELOOP,
+        ERESTART = libc::ERESTART,
+        ESTRPIPE = libc::ESTRPIPE,
+        ENOTEMPTY = libc::ENOTEMPTY,
+        EUSERS = libc::EUSERS,
+        ENOTSOCK = libc::ENOTSOCK,
+        EDESTADDRREQ = libc::EDESTADDRREQ,
+        EMSGSIZE = libc::EMSGSIZE,
+        EPROTOTYPE = libc::EPROTOTYPE,
+        ENOPROTOOPT = libc::ENOPROTOOPT,
+        EPROTONOSUPPORT = libc::EPROTONOSUPPORT,
+        ESOCKTNOSUPPORT = libc::ESOCKTNOSUPPORT,
+        EOPNOTSUPP = libc::EOPNOTSUPP,
+        EPFNOSUPPORT = libc::EPFNOSUPPORT,
+        EAFNOSUPPORT = libc::EAFNOSUPPORT,
+        EADDRINUSE = libc::EADDRINUSE,
+        EADDRNOTAVAIL = libc::EADDRNOTAVAIL,
+        ENETDOWN = libc::ENETDOWN,
+        ENETUNREACH = libc::ENETUNREACH,
+        ENETRESET = libc::ENETRESET,
+        ECONNABORTED = libc::ECONNABORTED,
+        ECONNRESET = libc::ECONNRESET,
+        ENOBUFS = libc::ENOBUFS,
+        EISCONN = libc::EISCONN,
+        ENOTCONN = libc::ENOTCONN,
+        ESHUTDOWN = libc::ESHUTDOWN,
+        ETOOMANYREFS = libc::ETOOMANYREFS,
+        ETIMEDOUT = libc::ETIMEDOUT,
+        ECONNREFUSED = libc::ECONNREFUSED,
+        EHOSTDOWN = libc::EHOSTDOWN,
+        EHOSTUNREACH = libc::EHOSTUNREACH,
+        EALREADY = libc::EALREADY,
+        EINPROGRESS = libc::EINPROGRESS,
+        ESTALE = libc::ESTALE,
+    }
+
+    impl Errno {
+        pub const EWOULDBLOCK: Errno = Errno::EAGAIN;
+    }
+
+    #[deprecated(
+        since = "0.28.0",
+        note = "please use `Errno::from_raw()` instead"
+    )]
+    pub const fn from_i32(e: i32) -> Errno {
+        use self::Errno::*;
+
+        match e {
+            libc::EPERM => EPERM,
+            libc::ENOENT => ENOENT,
+            libc::ESRCH => ESRCH,
+            libc::EINTR => EINTR,
+            libc::EIO => EIO,
+            libc::ENXIO => ENXIO,
+            libc::E2BIG => E2BIG,
+            libc::ENOEXEC => ENOEXEC,
+            libc::EBADF => EBADF,
+            libc::ECHILD => ECHILD,
+            libc::EAGAIN => EAGAIN,
+            libc::ENOMEM => ENOMEM,
+            libc::EACCES => EACCES,
+            libc::EFAULT => EFAULT,
+            libc::ENOTBLK => ENOTBLK,
+            libc::EBUSY => EBUSY,
+            libc::EEXIST => EEXIST,
+            libc::EXDEV => EXDEV,
+            libc::ENODEV => ENODEV,
+            libc::ENOTDIR => ENOTDIR,
+            libc::EISDIR => EISDIR,
+            libc::EINVAL => EINVAL,
+            libc::ENFILE => ENFILE,
+            libc::EMFILE => EMFILE,
+            libc::ENOTTY => ENOTTY,
+            libc::ETXTBSY => ETXTBSY,
+            libc::EFBIG => EFBIG,
+            libc::ENOSPC => ENOSPC,
+            libc::ESPIPE => ESPIPE,
+            libc::EROFS => EROFS,
+            libc::EMLINK => EMLINK,
+            libc::EPIPE => EPIPE,
+            libc::EDOM => EDOM,
+            libc::ERANGE => ERANGE,
+            libc::ENOMSG => ENOMSG,
+            libc::EIDRM => EIDRM,
+            libc::ECHRNG => ECHRNG,
+            libc::EL2NSYNC => EL2NSYNC,
+            libc::EL3HLT => EL3HLT,
+            libc::EL3RST => EL3RST,
+            libc::ELNRNG => ELNRNG,
+            libc::EUNATCH => EUNATCH,
+            libc::ENOCSI => ENOCSI,
+            libc::EL2HLT => EL2HLT,
+            libc::EDEADLK => EDEADLK,
+            libc::ENOLCK => ENOLCK,
+            libc::ECANCELED => ECANCELED,
+            libc::ENOTSUP => ENOTSUP,
+            libc::EDQUOT => EDQUOT,
+            libc::EBADE => EBADE,
+            libc::EBADR => EBADR,
+            libc::EXFULL => EXFULL,
+            libc::ENOANO => ENOANO,
+            libc::EBADRQC => EBADRQC,
+            libc::EBADSLT => EBADSLT,
+            libc::EDEADLOCK => EDEADLOCK,
+            libc::EBFONT => EBFONT,
+            libc::ENOSTR => ENOSTR,
+            libc::ENODATA => ENODATA,
+            libc::ETIME => ETIME,
+            libc::ENOSR => ENOSR,
+            libc::ENONET => ENONET,
+            libc::ENOPKG => ENOPKG,
+            libc::EREMOTE => EREMOTE,
+            libc::ENOLINK => ENOLINK,
+            libc::EADV => EADV,
+            libc::ESRMNT => ESRMNT,
+            libc::ECOMM => ECOMM,
+            libc::EPROTO => EPROTO,
+            libc::EMULTIHOP => EMULTIHOP,
+            libc::EBADMSG => EBADMSG,
+            libc::ENAMETOOLONG => ENAMETOOLONG,
             libc::EOVERFLOW => EOVERFLOW,
             libc::ENOTUNIQ => ENOTUNIQ,
             libc::EBADFD => EBADFD,
