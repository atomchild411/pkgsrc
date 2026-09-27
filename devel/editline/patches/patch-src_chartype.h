$NetBSD$

IRIX: accept its wchar_t like Solaris' and Tru64's (32-bit; ASCII in the C
locale, which is all IRIX 6.5 offers here).

--- src/chartype.h.orig
+++ src/chartype.h
@@ -36,6 +36,7 @@
 #if	!defined(__NetBSD__) && \
 	!defined(__sun) && \
 	!defined(__osf__) && \
+	!defined(__sgi) && \
 	!(defined(__APPLE__) && defined(__MACH__)) && \
 	!defined(__OpenBSD__) && \
 	!defined(__FreeBSD__) && \
