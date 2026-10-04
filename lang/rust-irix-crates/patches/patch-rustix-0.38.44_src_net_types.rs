$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/net/types.rs.orig
+++ rustix-0.38.44/src/net/types.rs
@@ -30,7 +30,7 @@ impl SocketType {
     pub const RAW: Self = Self(c::SOCK_RAW as _);
 
     /// `SOCK_RDM`
-    #[cfg(not(any(target_os = "espidf", target_os = "haiku")))]
+    #[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "irix")))]
     pub const RDM: Self = Self(c::SOCK_RDM as _);
 
     /// Constructs a `SocketType` from a raw integer.
@@ -91,6 +91,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -107,13 +108,14 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
     )))]
     pub const AX25: Self = Self(c::AF_AX25 as _);
     /// `AF_IPX`
-    #[cfg(not(any(
+    #[cfg(not(any(target_os = "irix", 
         target_os = "aix",
         target_os = "espidf",
         target_os = "vita",
@@ -130,6 +132,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -143,6 +146,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -156,6 +160,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -168,6 +173,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -181,13 +187,14 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
     )))]
     pub const ROSE: Self = Self(c::AF_ROSE as _);
     /// `AF_DECnet`
-    #[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "vita")))]
+    #[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "irix", target_os = "vita")))]
     pub const DECnet: Self = Self(c::AF_DECnet as _);
     /// `AF_NETBEUI`
     #[cfg(not(any(
@@ -197,6 +204,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -210,6 +218,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -222,6 +231,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -239,6 +249,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -252,6 +263,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -265,6 +277,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -278,6 +291,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -291,13 +305,14 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
     )))]
     pub const RDS: Self = Self(c::AF_RDS as _);
     /// `AF_SNA`
-    #[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "vita")))]
+    #[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "irix", target_os = "vita")))]
     pub const SNA: Self = Self(c::AF_SNA as _);
     /// `AF_IRDA`
     #[cfg(not(any(
@@ -306,6 +321,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -319,6 +335,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -332,6 +349,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -345,6 +363,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -358,6 +377,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -371,13 +391,14 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
     )))]
     pub const TIPC: Self = Self(c::AF_TIPC as _);
     /// `AF_BLUETOOTH`
-    #[cfg(not(any(
+    #[cfg(not(any(target_os = "irix", 
         apple,
         solarish,
         windows,
@@ -395,6 +416,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -408,6 +430,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -420,6 +443,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "vita",
     )))]
@@ -432,6 +456,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -445,6 +470,7 @@ impl AddressFamily {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -481,7 +507,7 @@ impl AddressFamily {
     #[cfg(any(bsd, solarish, target_os = "aix", target_os = "nto"))]
     pub const DATAKIT: Self = Self(c::AF_DATAKIT as _);
     /// `AF_DLI`
-    #[cfg(any(bsd, solarish, target_os = "aix", target_os = "haiku", target_os = "nto"))]
+    #[cfg(any(bsd, solarish, target_os = "aix", target_os = "haiku", target_os = "irix", target_os = "nto"))]
     pub const DLI: Self = Self(c::AF_DLI as _);
     /// `AF_E164`
     #[cfg(any(bsd, target_os = "nto"))]
@@ -529,7 +555,7 @@ impl AddressFamily {
     #[cfg(any(bsd, solarish, target_os = "aix", target_os = "nto"))]
     pub const LAT: Self = Self(c::AF_LAT as _);
     /// `AF_LINK`
-    #[cfg(any(bsd, solarish, target_os = "aix", target_os = "haiku", target_os = "nto"))]
+    #[cfg(any(bsd, solarish, target_os = "aix", target_os = "haiku", target_os = "irix", target_os = "nto"))]
     pub const LINK: Self = Self(c::AF_LINK as _);
     /// `AF_MPLS`
     #[cfg(any(netbsdlike, target_os = "dragonfly", target_os = "emscripten", target_os = "fuchsia"))]
@@ -589,7 +615,7 @@ impl AddressFamily {
     #[cfg(target_os = "aix")]
     pub const RIF: Self = Self(c::AF_RIF as _);
     /// `AF_ROUTE`
-    #[cfg(any(bsd, solarish, target_os = "android", target_os = "emscripten", target_os = "fuchsia", target_os = "haiku", target_os = "nto"))]
+    #[cfg(any(bsd, solarish, target_os = "android", target_os = "emscripten", target_os = "fuchsia", target_os = "haiku", target_os = "irix", target_os = "nto"))]
     pub const ROUTE: Self = Self(c::AF_ROUTE as _);
     /// `AF_SCLUSTER`
     #[cfg(target_os = "freebsd")]
@@ -674,6 +700,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const IGMP: Protocol = Protocol(new_raw_protocol(c::IPPROTO_IGMP as _));
@@ -683,6 +710,7 @@ pub mod ipproto {
         windows,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const IPIP: Protocol = Protocol(new_raw_protocol(c::IPPROTO_IPIP as _));
@@ -693,6 +721,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const EGP: Protocol = Protocol(new_raw_protocol(c::IPPROTO_EGP as _));
@@ -701,6 +730,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const PUP: Protocol = Protocol(new_raw_protocol(c::IPPROTO_PUP as _));
@@ -711,6 +741,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const IDP: Protocol = Protocol(new_raw_protocol(c::IPPROTO_IDP as _));
@@ -720,6 +751,7 @@ pub mod ipproto {
         windows,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const TP: Protocol = Protocol(new_raw_protocol(c::IPPROTO_TP as _));
@@ -732,6 +764,7 @@ pub mod ipproto {
         target_os = "dragonfly",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "openbsd",
         target_os = "vita",
@@ -745,6 +778,7 @@ pub mod ipproto {
         windows,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const RSVP: Protocol = Protocol(new_raw_protocol(c::IPPROTO_RSVP as _));
@@ -754,6 +788,7 @@ pub mod ipproto {
         windows,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const GRE: Protocol = Protocol(new_raw_protocol(c::IPPROTO_GRE as _));
@@ -762,6 +797,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const ESP: Protocol = Protocol(new_raw_protocol(c::IPPROTO_ESP as _));
@@ -770,6 +806,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const AH: Protocol = Protocol(new_raw_protocol(c::IPPROTO_AH as _));
@@ -781,6 +818,7 @@ pub mod ipproto {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita",
     )))]
@@ -793,6 +831,7 @@ pub mod ipproto {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita",
     )))]
@@ -804,6 +843,7 @@ pub mod ipproto {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita",
     )))]
     pub const ENCAP: Protocol = Protocol(new_raw_protocol(c::IPPROTO_ENCAP as _));
@@ -813,6 +853,7 @@ pub mod ipproto {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const PIM: Protocol = Protocol(new_raw_protocol(c::IPPROTO_PIM as _));
@@ -824,6 +865,7 @@ pub mod ipproto {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita",
     )))]
@@ -834,6 +876,7 @@ pub mod ipproto {
         target_os = "dragonfly",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "openbsd",
         target_os = "vita",
     )))]
@@ -848,6 +891,7 @@ pub mod ipproto {
         target_os = "dragonfly",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita",
     )))]
@@ -861,6 +905,7 @@ pub mod ipproto {
         target_os = "dragonfly",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "netbsd",
         target_os = "nto",
         target_os = "vita",
@@ -882,6 +927,7 @@ pub mod ipproto {
         target_os = "espidf",
         target_os = "fuchsia",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita",
     )))]
@@ -891,6 +937,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const FRAGMENT: Protocol = Protocol(new_raw_protocol(c::IPPROTO_FRAGMENT as _));
@@ -905,6 +952,7 @@ pub mod ipproto {
         target_os = "dragonfly",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita",
     )))]
@@ -914,6 +962,7 @@ pub mod ipproto {
         solarish,
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "vita"
     )))]
     pub const ROUTING: Protocol = Protocol(new_raw_protocol(c::IPPROTO_ROUTING as _));
@@ -1462,13 +1511,14 @@ bitflags! {
             target_os = "aix",
             target_os = "espidf",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "nto",
             target_os = "vita",
         )))]
         const NONBLOCK = bitcast!(c::SOCK_NONBLOCK);
 
         /// `SOCK_CLOEXEC`
-        #[cfg(not(any(apple, windows, target_os = "aix", target_os = "haiku")))]
+        #[cfg(not(any(apple, windows, target_os = "aix", target_os = "haiku", target_os = "irix")))]
         const CLOEXEC = bitcast!(c::SOCK_CLOEXEC);
 
         // This deliberately lacks a `const _ = !0`, so that users can use
