$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2.

--- mio-1.2.3/src/poll.rs.orig
+++ mio-1.2.3/src/poll.rs
@@ -10,6 +10,7 @@
         target_os = "hermit",
         target_os = "hurd",
         target_os = "nto",
+        target_os = "irix",
         target_os = "vita",
         target_os = "cygwin",
         target_os = "horizon"
@@ -452,6 +453,7 @@ impl Poll {
         target_os = "hermit",
         target_os = "hurd",
         target_os = "nto",
+        target_os = "irix",
         target_os = "vita",
         target_os = "cygwin",
         target_os = "horizon"
@@ -756,6 +758,7 @@ impl fmt::Debug for Registry {
         target_os = "hermit",
         target_os = "hurd",
         target_os = "nto",
+        target_os = "irix",
         target_os = "vita",
         target_os = "cygwin",
         target_os = "horizon"
@@ -779,6 +782,7 @@ impl AsFd for Registry {
         target_os = "hermit",
         target_os = "hurd",
         target_os = "nto",
+        target_os = "irix",
         target_os = "vita",
         target_os = "cygwin",
         target_os = "horizon"
@@ -801,6 +805,7 @@ cfg_os_poll! {
             target_os = "hermit",
             target_os = "hurd",
             target_os = "nto",
+            target_os = "irix",
             target_os = "vita",
             target_os = "cygwin",
             target_os = "horizon"
