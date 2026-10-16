$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/sys/signal.rs.orig
+++ nix-0.29.0/src/sys/signal.rs
@@ -102,7 +102,8 @@
         #[cfg(not(target_os = "haiku"))]
         SIGIO,
         #[cfg(any(linux_android, target_os = "emscripten",
-                  target_os = "fuchsia", target_os = "aix"))]
+                  target_os = "fuchsia", target_os = "aix",
+                  target_os = "irix"))]
         /// Power failure imminent.
         SIGPWR,
         /// Bad system call
@@ -114,7 +115,8 @@
         SIGEMT,
         #[cfg(not(any(linux_android, target_os = "emscripten",
                       target_os = "fuchsia", target_os = "redox",
-                      target_os = "haiku", target_os = "aix")))]
+                      target_os = "haiku", target_os = "aix",
+                      target_os = "irix")))]
         /// Information request
         SIGINFO,
     }
@@ -174,6 +176,7 @@
                 linux_android,
                 target_os = "emscripten",
                 target_os = "fuchsia",
+                target_os = "irix",
             ))]
             "SIGPWR" => Signal::SIGPWR,
             "SIGSYS" => Signal::SIGSYS,
@@ -191,7 +194,8 @@
                 target_os = "fuchsia",
                 target_os = "redox",
                 target_os = "aix",
-                target_os = "haiku"
+                target_os = "haiku",
+                target_os = "irix",
             )))]
             "SIGINFO" => Signal::SIGINFO,
             _ => return Err(Errno::EINVAL),
@@ -257,6 +261,7 @@
                 target_os = "emscripten",
                 target_os = "fuchsia",
                 target_os = "aix",
+                target_os = "irix",
             ))]
             Signal::SIGPWR => "SIGPWR",
             Signal::SIGSYS => "SIGSYS",
@@ -274,7 +279,8 @@
                 target_os = "fuchsia",
                 target_os = "redox",
                 target_os = "aix",
-                target_os = "haiku"
+                target_os = "haiku",
+                target_os = "irix",
             )))]
             Signal::SIGINFO => "SIGINFO",
         }
@@ -356,13 +362,22 @@
     SIGURG, SIGPOLL, SIGIO, SIGSTOP, SIGTSTP, SIGCONT, SIGTTIN, SIGTTOU,
     SIGVTALRM, SIGPROF, SIGXCPU, SIGXFSZ, SIGTRAP,
 ];
+#[cfg(target_os = "irix")]
+#[cfg(feature = "signal")]
+const SIGNALS: [Signal; 31] = [
+    SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGTRAP, SIGABRT, SIGBUS, SIGFPE, SIGKILL,
+    SIGUSR1, SIGSEGV, SIGUSR2, SIGPIPE, SIGALRM, SIGTERM, SIGCHLD, SIGCONT,
+    SIGSTOP, SIGTSTP, SIGTTIN, SIGTTOU, SIGURG, SIGXCPU, SIGXFSZ, SIGVTALRM,
+    SIGPROF, SIGWINCH, SIGIO, SIGPWR, SIGSYS, SIGEMT,
+];
 #[cfg(not(any(
     linux_android,
     target_os = "fuchsia",
     target_os = "emscripten",
     target_os = "aix",
     target_os = "redox",
-    target_os = "haiku"
+    target_os = "haiku",
+    target_os = "irix"
 )))]
 #[cfg(feature = "signal")]
 const SIGNALS: [Signal; 31] = [
