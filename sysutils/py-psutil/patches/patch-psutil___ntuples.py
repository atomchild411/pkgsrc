$NetBSD$

IRIX support: psutil/_psirix.py, psutil/_psutil_irix.c and psutil/arch/irix/ (files/).

--- psutil/_ntuples.py.orig
+++ psutil/_ntuples.py
@@ -5,6 +5,7 @@
 from collections import namedtuple as nt
 
 from ._common import AIX
+from ._common import IRIX
 from ._common import BSD
 from ._common import FREEBSD
 from ._common import LINUX
@@ -414,7 +415,7 @@
 # --- AIX
 # ===================================================================
 
-elif AIX:
+elif AIX or IRIX:
 
     # psutil.Process.memory_info()
     pmem = nt("pmem", ("rss", "vms"))
