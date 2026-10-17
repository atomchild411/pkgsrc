$NetBSD$

IRIX support: psutil/_psirix.py, psutil/_psutil_irix.c and psutil/arch/irix/ (files/).

--- setup.py.orig
+++ setup.py
@@ -56,6 +56,7 @@
 sys.path.insert(0, os.path.join(HERE, "psutil"))
 
 from _common import AIX  # noqa: E402
+from _common import IRIX  # noqa: E402
 from _common import BSD  # noqa: E402
 from _common import FREEBSD  # noqa: E402
 from _common import LINUX  # noqa: E402
@@ -452,6 +453,23 @@
         define_macros=macros,
         # fmt: off
         # python 2.7 compatibility requires no comma
+        **py_limited_api
+        # fmt: on
+    )
+
+elif IRIX:
+    macros.append(("PSUTIL_IRIX", 1))
+
+    ext = Extension(
+        'psutil._psutil_irix',
+        sources=(
+            sources
+            + ["psutil/_psutil_irix.c"]
+            + glob.glob("psutil/arch/irix/*.c")
+        ),
+        define_macros=macros,
+        # fmt: off
+        # python 2.7 compatibility requires no comma
         **py_limited_api
         # fmt: on
     )
