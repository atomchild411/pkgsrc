$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/net/types.rs.orig
+++ rustix-1.1.5/src/net/types.rs
@@ -34,6 +34,7 @@ impl SocketType {
     #[cfg(not(any(
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox"
     )))]
@@ -98,6 +99,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -117,6 +119,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -125,7 +128,7 @@ impl AddressFamily {
     )))]
     pub const AX25: Self = Self(c::AF_AX25 as _);
     /// `AF_IPX`
-    #[cfg(not(any(
+    #[cfg(not(any(target_os = "irix", 
         target_os = "aix",
         target_os = "cygwin",
         target_os = "espidf",
@@ -151,6 +154,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -167,6 +171,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -183,6 +188,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -198,6 +204,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -214,6 +221,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -225,6 +233,7 @@ impl AddressFamily {
     #[cfg(not(any(
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita"
@@ -239,6 +248,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -255,6 +265,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -270,6 +281,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -290,6 +302,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -306,6 +319,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -322,6 +336,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -338,6 +353,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -354,6 +370,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -365,6 +382,7 @@ impl AddressFamily {
     #[cfg(not(any(
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita"
@@ -378,6 +396,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -394,6 +413,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -410,6 +430,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -426,6 +447,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -442,6 +464,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -458,6 +481,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -466,7 +490,7 @@ impl AddressFamily {
     )))]
     pub const TIPC: Self = Self(c::AF_TIPC as _);
     /// `AF_BLUETOOTH`
-    #[cfg(not(any(
+    #[cfg(not(any(target_os = "irix", 
         apple,
         solarish,
         windows,
@@ -488,6 +512,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -504,6 +529,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -519,6 +545,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "redox",
@@ -534,6 +561,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -550,6 +578,7 @@ impl AddressFamily {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -593,6 +622,7 @@ impl AddressFamily {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto"
     ))]
     pub const DLI: Self = Self(c::AF_DLI as _);
@@ -654,6 +684,7 @@ impl AddressFamily {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto"
     ))]
     pub const LINK: Self = Self(c::AF_LINK as _);
@@ -727,6 +758,7 @@ impl AddressFamily {
         target_os = "emscripten",
         target_os = "fuchsia",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto"
     ))]
     pub const ROUTE: Self = Self(c::AF_ROUTE as _);
@@ -813,6 +845,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "vita"
     )))]
@@ -823,6 +856,7 @@ pub mod ipproto {
         windows,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita"
@@ -835,6 +869,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita"
@@ -845,6 +880,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "vita"
     )))]
@@ -856,6 +892,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "vita"
     )))]
@@ -867,6 +904,7 @@ pub mod ipproto {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita",
@@ -882,6 +920,7 @@ pub mod ipproto {
         target_os = "dragonfly",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "nto",
         target_os = "openbsd",
@@ -898,6 +937,7 @@ pub mod ipproto {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita",
@@ -910,6 +950,7 @@ pub mod ipproto {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita",
@@ -920,6 +961,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita"
@@ -930,6 +972,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita"
@@ -944,6 +987,7 @@ pub mod ipproto {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "nto",
         target_os = "redox",
@@ -959,6 +1003,7 @@ pub mod ipproto {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "nto",
         target_os = "redox",
@@ -973,6 +1018,7 @@ pub mod ipproto {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita",
@@ -985,6 +1031,7 @@ pub mod ipproto {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita",
@@ -999,6 +1046,7 @@ pub mod ipproto {
         target_os = "cygwin",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "nto",
         target_os = "redox",
@@ -1012,6 +1060,7 @@ pub mod ipproto {
         target_os = "dragonfly",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "openbsd",
         target_os = "redox",
@@ -1029,6 +1078,7 @@ pub mod ipproto {
         target_os = "dragonfly",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "nto",
         target_os = "redox",
@@ -1045,6 +1095,7 @@ pub mod ipproto {
         target_os = "dragonfly",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "netbsd",
         target_os = "nto",
@@ -1069,6 +1120,7 @@ pub mod ipproto {
         target_os = "espidf",
         target_os = "fuchsia",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "nto",
         target_os = "redox",
@@ -1080,6 +1132,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita"
@@ -1097,6 +1150,7 @@ pub mod ipproto {
         target_os = "dragonfly",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "nto",
         target_os = "redox",
@@ -1108,6 +1162,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "redox",
         target_os = "vita"
@@ -1705,6 +1760,7 @@ bitflags! {
             target_os = "aix",
             target_os = "espidf",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "horizon",
             target_os = "nto",
             target_os = "vita",
@@ -1712,7 +1768,7 @@ bitflags! {
         const NONBLOCK = bitcast!(c::SOCK_NONBLOCK);
 
         /// `SOCK_CLOEXEC`
-        #[cfg(not(any(apple, windows, target_os = "aix", target_os = "haiku")))]
+        #[cfg(not(any(apple, windows, target_os = "aix", target_os = "haiku", target_os = "irix")))]
         const CLOEXEC = bitcast!(c::SOCK_CLOEXEC);
 
         // This deliberately lacks a `const _ = !0`, so that users can use
