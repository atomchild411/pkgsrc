$NetBSD$

IRIX support: psutil/_psirix.py, psutil/_psutil_irix.c and psutil/arch/irix/ (files/).

--- psutil/_common.py.orig
+++ psutil/_common.py
@@ -80,6 +80,7 @@
 BSD = FREEBSD or OPENBSD or NETBSD
 SUNOS = sys.platform.startswith(("sunos", "solaris"))
 AIX = sys.platform.startswith("aix")
+IRIX = sys.platform.startswith("irix")
 
 
 # ===================================================================
