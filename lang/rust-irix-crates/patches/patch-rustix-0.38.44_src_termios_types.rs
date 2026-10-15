$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/termios/types.rs.orig
+++ rustix-0.38.44/src/termios/types.rs
@@ -33,6 +33,7 @@ pub struct Termios {
         target_env = "newlib",
         target_os = "fuchsia",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "redox"
     ))]
     pub line_discipline: c::cc_t,
@@ -219,6 +220,7 @@ impl core::fmt::Debug for Termios {
             target_env = "newlib",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "redox"
         ))]
         {
@@ -264,7 +266,7 @@ bitflags! {
         const ICRNL = c::ICRNL;
 
         /// `IUCLC`
-        #[cfg(any(linux_kernel, solarish, target_os = "aix", target_os = "haiku", target_os = "nto"))]
+        #[cfg(any(linux_kernel, solarish, target_os = "aix", target_os = "haiku", target_os = "irix", target_os = "nto"))]
         const IUCLC = c::IUCLC;
 
         /// `IXON`
@@ -278,7 +280,7 @@ bitflags! {
         const IXOFF = c::IXOFF;
 
         /// `IMAXBEL`
-        #[cfg(not(any(target_os = "haiku", target_os = "redox")))]
+        #[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "redox")))]
         const IMAXBEL = c::IMAXBEL;
 
         /// `IUTF8`
@@ -289,6 +291,7 @@ bitflags! {
             target_os = "aix",
             target_os = "emscripten",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "redox",
         )))]
@@ -448,6 +451,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "redox",
         )))]
         const XTABS = c::XTABS;
@@ -567,6 +571,7 @@ bitflags! {
             target_os = "aix",
             target_os = "emscripten",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -608,7 +613,7 @@ bitflags! {
         const PENDIN = c::PENDIN;
 
         /// `EXTPROC`
-        #[cfg(not(any(target_os = "aix", target_os = "haiku", target_os = "nto", target_os = "redox")))]
+        #[cfg(not(any(target_os = "aix", target_os = "haiku", target_os = "irix", target_os = "nto", target_os = "redox")))]
         const EXTPROC = c::EXTPROC;
 
         /// `ISIG`
@@ -724,16 +729,17 @@ pub mod speed {
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
@@ -742,24 +748,25 @@ pub mod speed {
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
@@ -769,6 +776,7 @@ pub mod speed {
         bsd,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "solaris",
     )))]
     pub const B2500000: u32 = 2_500_000;
@@ -780,6 +788,7 @@ pub mod speed {
         bsd,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "solaris",
     )))]
     pub const B3000000: u32 = 3_000_000;
@@ -791,6 +800,7 @@ pub mod speed {
         bsd,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "solaris",
     )))]
     pub const B3500000: u32 = 3_500_000;
@@ -802,6 +812,7 @@ pub mod speed {
         bsd,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "solaris",
     )))]
     pub const B4000000: u32 = 4_000_000;
@@ -844,13 +855,14 @@ pub mod speed {
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
@@ -860,6 +872,7 @@ pub mod speed {
                 solarish,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto"
             )))]
             c::B500000 => Some(500_000),
@@ -868,6 +881,7 @@ pub mod speed {
                 solarish,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto"
             )))]
             c::B576000 => Some(576_000),
@@ -876,6 +890,7 @@ pub mod speed {
                 target_os = "aix",
                 target_os = "dragonfly",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "openbsd"
             )))]
@@ -884,6 +899,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -892,6 +908,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -900,6 +917,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -908,6 +926,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -918,6 +937,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -928,6 +948,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -938,6 +959,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -948,6 +970,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -981,13 +1004,14 @@ pub mod speed {
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
@@ -997,6 +1021,7 @@ pub mod speed {
                 solarish,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto"
             )))]
             500_000 => Some(c::B500000),
@@ -1005,6 +1030,7 @@ pub mod speed {
                 solarish,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto"
             )))]
             576_000 => Some(c::B576000),
@@ -1013,6 +1039,7 @@ pub mod speed {
                 target_os = "aix",
                 target_os = "dragonfly",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "openbsd"
             )))]
@@ -1021,6 +1048,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -1029,6 +1057,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -1037,6 +1066,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -1045,6 +1075,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris"
             )))]
@@ -1055,6 +1086,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -1065,6 +1097,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -1075,6 +1108,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -1085,6 +1119,7 @@ pub mod speed {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "nto",
                 target_os = "solaris",
             )))]
@@ -1147,6 +1182,7 @@ impl SpecialCodeIndex {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
     )))]
@@ -1169,11 +1205,11 @@ impl SpecialCodeIndex {
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
@@ -1184,7 +1220,7 @@ impl SpecialCodeIndex {
     pub const VEOL2: Self = Self(c::VEOL2 as usize);
 
     /// `VSWTCH`
-    #[cfg(any(solarish, target_os = "haiku", target_os = "nto"))]
+    #[cfg(any(solarish, target_os = "haiku", target_os = "irix", target_os = "nto"))]
     pub const VSWTCH: Self = Self(c::VSWTCH as usize);
 
     /// `VDSUSP`
@@ -1241,6 +1277,7 @@ impl core::fmt::Debug for SpecialCodeIndex {
                 solarish,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "hurd",
                 target_os = "nto",
             )))]
@@ -1255,14 +1292,14 @@ impl core::fmt::Debug for SpecialCodeIndex {
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
@@ -1435,6 +1472,7 @@ fn termios_layouts() {
             target_env = "newlib",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "redox"
         ))]
         check_renamed_struct_renamed_field!(Termios, termios, line_discipline, c_line);
@@ -1466,6 +1504,7 @@ fn termios_layouts() {
     solarish,
     target_os = "emscripten",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox"
 )))]
 fn termios_legacy() {
