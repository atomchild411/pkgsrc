$NetBSD$

choose: take a preset answer (CHOOSE_<name>=0 or 1) for probes a cross build
cannot run.

--- choose.sh.orig
+++ choose.sh
@@ -4,6 +4,13 @@
 result="${h}1"
 shift 2
 
+# A preset answer (CHOOSE_<name>=0 or 1), for a cross build, which
+# cannot run the try program.
+eval preset=\${CHOOSE_${try#sys/try}-}
+case "$preset" in
+  0|1) rm -f "$try".o "$try"; exec cat "${h}${preset}" ;;
+esac
+
 case "$mode" in
   *c*) ./compile "$try".c >/dev/null 2>&1 || result="${h}0" ;;
 esac
