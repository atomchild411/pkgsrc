$NetBSD$

IRIX support: psutil/_psirix.py, psutil/_psutil_irix.c and psutil/arch/irix/ (files/).

--- psutil/__init__.py.orig
+++ psutil/__init__.py
@@ -38,6 +38,7 @@
 from . import _common
 from . import _ntuples as _ntp
 from ._common import AIX
+from ._common import IRIX
 from ._common import BSD
 from ._common import CONN_CLOSE
 from ._common import CONN_CLOSE_WAIT
@@ -133,6 +134,13 @@
     # via sys.modules.
     PROCFS_PATH = "/proc"
 
+elif IRIX:
+    from . import _psirix as _psplatform
+
+    # This is public API and it will be retrieved from _psirix.py
+    # via sys.modules.
+    PROCFS_PATH = "/proc"
+
 else:  # pragma: no cover
     msg = f"platform {sys.platform} is not supported"
     raise NotImplementedError(msg)
@@ -163,7 +171,7 @@
     "POWER_TIME_UNKNOWN", "POWER_TIME_UNLIMITED",
 
     "BSD", "FREEBSD", "LINUX", "NETBSD", "OPENBSD", "MACOS", "OSX", "POSIX",
-    "SUNOS", "WINDOWS", "AIX",
+    "SUNOS", "WINDOWS", "AIX", "IRIX",
 
     # "RLIM_INFINITY", "RLIMIT_AS", "RLIMIT_CORE", "RLIMIT_CPU", "RLIMIT_DATA",
     # "RLIMIT_FSIZE", "RLIMIT_LOCKS", "RLIMIT_MEMLOCK", "RLIMIT_NOFILE",
