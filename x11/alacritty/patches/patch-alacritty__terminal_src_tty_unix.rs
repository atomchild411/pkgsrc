$NetBSD$

IRIX has no TIOCSCTTY: open the terminal after setsid() to make it the controlling one, System V style.

--- alacritty_terminal/src/tty/unix.rs.orig
+++ alacritty_terminal/src/tty/unix.rs
@@ -15,7 +15,9 @@
 use std::sync::Arc;
 use std::{env, ptr};
 
-use libc::{F_GETFL, F_SETFL, O_NONBLOCK, TIOCSCTTY, c_int, fcntl};
+use libc::{F_GETFL, F_SETFL, O_NONBLOCK, c_int, fcntl};
+#[cfg(not(target_os = "irix"))]
+use libc::TIOCSCTTY;
 use log::error;
 use polling::{Event, PollMode, Poller};
 use rustix_openpty::openpty;
@@ -41,7 +43,30 @@
     }};
 }
 
+/// IRIX has no TIOCSCTTY: as in System V, a session leader's first open of a
+/// terminal makes it the controlling one.
+#[cfg(target_os = "irix")]
+fn set_controlling_terminal(fd: c_int) -> Result<()> {
+    let res = unsafe {
+        let name = libc::ttyname(fd);
+        if name.is_null() {
+            -1
+        } else {
+            let tty = libc::open(name, libc::O_RDWR);
+            if tty >= 0 {
+                libc::close(tty);
+                0
+            } else {
+                -1
+            }
+        }
+    };
+
+    if res == 0 { Ok(()) } else { Err(Error::last_os_error()) }
+}
+
 /// Really only needed on BSD, but should be fine elsewhere.
+#[cfg(not(target_os = "irix"))]
 fn set_controlling_terminal(fd: c_int) -> Result<()> {
     let res = unsafe {
         // TIOSCTTY changes based on platform and the `ioctl` call is different
