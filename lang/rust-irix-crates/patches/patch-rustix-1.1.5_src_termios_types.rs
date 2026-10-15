$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/termios/types.rs.orig
+++ rustix-1.1.5/src/termios/types.rs
@@ -36,6 +36,7 @@ pub struct Termios {
         target_env = "newlib",
         target_os = "fuchsia",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "redox"
     ))]
     pub line_discipline: u8,
@@ -230,6 +231,7 @@ impl core::fmt::Debug for Termios {
             target_env = "newlib",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "redox"
         ))]
         {
@@ -275,7 +277,7 @@ bitflags! {
         const ICRNL = c::ICRNL;
 
         /// `IUCLC`
-        #[cfg(any(linux_raw_dep, solarish, target_os = "aix", target_os = "haiku", target_os = "nto"))]
+        #[cfg(any(linux_raw_dep, solarish, target_os = "aix", target_os = "haiku", target_os = "irix", target_os = "nto"))]
         const IUCLC = c::IUCLC;
 
         /// `IXON`
@@ -289,7 +291,7 @@ bitflags! {
         const IXOFF = c::IXOFF;
 
         /// `IMAXBEL`
-        #[cfg(not(any(target_os = "haiku", target_os = "redox")))]
+        #[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "redox")))]
         const IMAXBEL = c::IMAXBEL;
 
         /// `IUTF8`
@@ -300,6 +302,7 @@ bitflags! {
             target_os = "aix",
             target_os = "emscripten",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "redox",
         )))]
@@ -459,6 +462,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "redox",
         )))]
         const XTABS = c::XTABS;
@@ -580,6 +584,7 @@ bitflags! {
             target_os = "aix",
             target_os = "emscripten",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -625,6 +630,7 @@ bitflags! {
             target_os = "aix",
             target_os = "cygwin",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "nto",
             target_os = "redox",
         )))]
@@ -743,16 +749,17 @@ pub mod speed {
         target_os = "aix",
         target_os = "dragonfly",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "openbsd"
     )))]
     pub const B460800: u32 = 460_800;
 
     /// `B500000`
-    #[cfg(not(any(bsd, solarish, target_os = "aix", target_os = "haiku")))]
+    #[cfg(not(any(bsd, solarish, target_os = "aix", target_os = "haiku", target_os = "irix")))]
     pub const B500000: u32 = 500_000;
 
     /// `B576000`
-    #[cfg(not(any(bsd, solarish, target_os = "aix", target_os = "haiku")))]
+    #[cfg(not(any(bsd, solarish, target_os = "aix", target_os = "haiku", target_os = "irix")))]
     pub const B576000: u32 = 576_000;
 
     /// `B921600`
@@ -761,24 +768,25 @@ pub mod speed {
         target_os = "aix",
         target_os = "dragonfly",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "openbsd"
     )))]
     pub const B921600: u32 = 921_600;
 
     /// `B1000000`
-    #[cfg(not(any(bsd, target_os = "aix", target_os = "haiku", target_os = "solaris")))]
+    #[cfg(not(any(bsd, target_os = "aix", target_os = "haiku", target_os = "irix", target_os = "solaris")))]
     pub const B1000000: u32 = 1_000_000;
 
     /// `B1152000`
-    #[cfg(not(any(bsd, target_os = "aix", target_os = "haiku", target_os = "solaris")))]
+    #[cfg(not(any(bsd, target_os = "aix", target_os = "haiku", target_os = "irix", target_os = "solaris")))]
     pub const B1152000: u32 = 1_152_000;
 
     /// `B1500000`
-    #[cfg(not(any(bsd, target_os = "aix", target_os = "haiku", target_os = "solaris")))]
+    #[cfg(not(any(bsd, target_os = "aix", target_os = "haiku", target_os = "irix", target_os = "solaris")))]
     pub const B1500000: u32 = 1_500_000;
 
     /// `B2000000`
-    #[cfg(not(any(bsd, target_os = "aix", target_os = "haiku", target_os = "solaris")))]
+    #[cfg(not(any(bsd, target_os = "aix", target_os = "haiku", target_os = "irix", target_os = "solaris")))]
     pub const B2000000: u32 = 2_000_000;
 
     /// `B2500000`
@@ -788,6 +796,7 @@ pub mod speed {
         bsd,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "solaris",
     )))]
     pub const B2500000: u32 = 2_500_000;
@@ -799,6 +808,7 @@ pub mod speed {
         bsd,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "solaris",
     )))]
     pub const B3000000: u32 = 3_000_000;
@@ -810,6 +820,7 @@ pub mod speed {
         bsd,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "solaris",
     )))]
     pub const B3500000: u32 = 3_500_000;
@@ -821,6 +832,7 @@ pub mod speed {
         bsd,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "solaris",
     )))]
     pub const B4000000: u32 = 4_000_000;
@@ -863,13 +875,14 @@ pub mod speed {
             c::B57600 => Some(57600),
             #[cfg(not(target_os = "aix"))]
             c::B115200 => Some(115_200),
-            #[cfg(not(any(target_os = "aix", target_os = "nto")))]
+            #[cfg(not(any(target_os = "irix", target_os = "aix", target_os = "nto")))]
             c::B230400 => Some(230_400),
             #[cfg(not(any(
                 apple,
                 target_os = "aix",
                 target_os = "dragonfly",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "openbsd"
             )))]
@@ -879,6 +892,7 @@ pub mod speed {
                 solarish,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto"
             )))]
             c::B500000 => Some(500_000),
@@ -887,6 +901,7 @@ pub mod speed {
                 solarish,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto"
             )))]
             c::B576000 => Some(576_000),
@@ -895,6 +910,7 @@ pub mod speed {
                 target_os = "aix",
                 target_os = "dragonfly",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "openbsd"
             )))]
@@ -903,6 +919,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -911,6 +928,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -919,6 +937,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -927,6 +946,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -937,6 +957,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -947,6 +968,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -958,6 +980,7 @@ pub mod speed {
                 target_os = "aix",
                 target_os = "cygwin",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -969,6 +992,7 @@ pub mod speed {
                 target_os = "aix",
                 target_os = "cygwin",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -1002,13 +1026,14 @@ pub mod speed {
             57600 => Some(c::B57600),
             #[cfg(not(target_os = "aix"))]
             115_200 => Some(c::B115200),
-            #[cfg(not(any(target_os = "aix", target_os = "nto")))]
+            #[cfg(not(any(target_os = "irix", target_os = "aix", target_os = "nto")))]
             230_400 => Some(c::B230400),
             #[cfg(not(any(
                 apple,
                 target_os = "aix",
                 target_os = "dragonfly",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "openbsd",
             )))]
@@ -1018,6 +1043,7 @@ pub mod speed {
                 solarish,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto"
             )))]
             500_000 => Some(c::B500000),
@@ -1026,6 +1052,7 @@ pub mod speed {
                 solarish,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto"
             )))]
             576_000 => Some(c::B576000),
@@ -1034,6 +1061,7 @@ pub mod speed {
                 target_os = "aix",
                 target_os = "dragonfly",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "openbsd"
             )))]
@@ -1042,6 +1070,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -1050,6 +1079,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -1058,6 +1088,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -1066,6 +1097,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -1076,6 +1108,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -1086,6 +1119,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -1097,6 +1131,7 @@ pub mod speed {
                 target_os = "aix",
                 target_os = "cygwin",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -1108,6 +1143,7 @@ pub mod speed {
                 target_os = "aix",
                 target_os = "cygwin",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -1211,6 +1247,7 @@ impl SpecialCodeIndex {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
     )))]
@@ -1233,11 +1270,11 @@ impl SpecialCodeIndex {
     pub const VREPRINT: Self = Self(c::VREPRINT as usize);
 
     /// `VDISCARD`
-    #[cfg(not(any(target_os = "aix", target_os = "haiku")))]
+    #[cfg(not(any(target_os = "aix", target_os = "haiku", target_os = "irix")))]
     pub const VDISCARD: Self = Self(c::VDISCARD as usize);
 
     /// `VWERASE`
-    #[cfg(not(any(target_os = "aix", target_os = "haiku")))]
+    #[cfg(not(any(target_os = "aix", target_os = "haiku", target_os = "irix")))]
     pub const VWERASE: Self = Self(c::VWERASE as usize);
 
     /// `VLNEXT`
@@ -1248,7 +1285,7 @@ impl SpecialCodeIndex {
     pub const VEOL2: Self = Self(c::VEOL2 as usize);
 
     /// `VSWTCH`
-    #[cfg(any(solarish, target_os = "haiku", target_os = "nto"))]
+    #[cfg(any(solarish, target_os = "haiku", target_os = "irix", target_os = "nto"))]
     pub const VSWTCH: Self = Self(c::VSWTCH as usize);
 
     /// `VDSUSP`
@@ -1282,6 +1319,7 @@ impl core::fmt::Debug for SpecialCodeIndex {
                 all(linux_kernel, any(target_arch = "sparc", target_arch = "sparc64")),
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
             )))]
             Self::VEOF => write!(f, "VEOF"),
             #[cfg(not(any(
@@ -1289,6 +1327,7 @@ impl core::fmt::Debug for SpecialCodeIndex {
                 all(linux_kernel, any(target_arch = "sparc", target_arch = "sparc64")),
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
             )))]
             Self::VTIME => write!(f, "VTIME"),
             #[cfg(not(any(
@@ -1296,6 +1335,7 @@ impl core::fmt::Debug for SpecialCodeIndex {
                 all(linux_kernel, any(target_arch = "sparc", target_arch = "sparc64")),
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
             )))]
             Self::VMIN => write!(f, "VMIN"),
 
@@ -1306,6 +1346,7 @@ impl core::fmt::Debug for SpecialCodeIndex {
                 all(linux_kernel, any(target_arch = "sparc", target_arch = "sparc64")),
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
             ))]
             Self::VMIN => write!(f, "VMIN/VEOF"),
             #[cfg(any(
@@ -1313,6 +1354,7 @@ impl core::fmt::Debug for SpecialCodeIndex {
                 all(linux_kernel, any(target_arch = "sparc", target_arch = "sparc64")),
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
             ))]
             Self::VTIME => write!(f, "VTIME/VEOL"),
 
@@ -1321,6 +1363,7 @@ impl core::fmt::Debug for SpecialCodeIndex {
                 solarish,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "hurd",
                 target_os = "nto",
             )))]
@@ -1333,18 +1376,19 @@ impl core::fmt::Debug for SpecialCodeIndex {
                 all(linux_kernel, any(target_arch = "sparc", target_arch = "sparc64")),
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
             )))]
             Self::VEOL => write!(f, "VEOL"),
             #[cfg(not(target_os = "haiku"))]
             Self::VREPRINT => write!(f, "VREPRINT"),
-            #[cfg(not(any(target_os = "aix", target_os = "haiku")))]
+            #[cfg(not(any(target_os = "aix", target_os = "haiku", target_os = "irix")))]
             Self::VDISCARD => write!(f, "VDISCARD"),
-            #[cfg(not(any(target_os = "aix", target_os = "haiku")))]
+            #[cfg(not(any(target_os = "aix", target_os = "haiku", target_os = "irix")))]
             Self::VWERASE => write!(f, "VWERASE"),
             #[cfg(not(target_os = "haiku"))]
             Self::VLNEXT => write!(f, "VLNEXT"),
             Self::VEOL2 => write!(f, "VEOL2"),
-            #[cfg(any(solarish, target_os = "haiku", target_os = "nto"))]
+            #[cfg(any(solarish, target_os = "haiku", target_os = "irix", target_os = "nto"))]
             Self::VSWTCH => write!(f, "VSWTCH"),
             #[cfg(any(
                 bsd,
@@ -1538,6 +1582,7 @@ mod tests {
                 target_env = "newlib",
                 target_os = "fuchsia",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "redox"
             ))]
             check_renamed_struct_renamed_field!(Termios, termios, line_discipline, c_line);
@@ -1570,6 +1615,7 @@ mod tests {
         target_os = "cygwin",
         target_os = "emscripten",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "redox",
     )))]
     fn termios_legacy() {
