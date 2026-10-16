$NetBSD$

Where usize is 32 bits, 10^12 overflows it: compute in u64.

--- crates/tui/src/view/util.rs.orig
+++ crates/tui/src/view/util.rs
@@ -254,10 +254,12 @@ pub fn format_duration(duration: &Durati
 
 /// Format a byte total, e.g. 1_000_000 -> 1 MB
 pub fn format_byte_size(size: usize) -> String {
-    const K: usize = 10usize.pow(3);
-    const M: usize = 10usize.pow(6);
-    const G: usize = 10usize.pow(9);
-    const T: usize = 10usize.pow(12);
+    // u64: 10^12 does not fit a 32-bit usize
+    let size = size as u64;
+    const K: u64 = 10u64.pow(3);
+    const M: u64 = 10u64.pow(6);
+    const G: u64 = 10u64.pow(9);
+    const T: u64 = 10u64.pow(12);
     let (denom, suffix) = match size {
         ..K => return format!("{size} B"),
         K..M => (K, "K"),
