$NetBSD$

IRIX port (n32, pthreads); NSS dropped its old one.

--- nss/coreconf/config.mk.orig
+++ nss/coreconf/config.mk
@@ -31,7 +31,7 @@
 #######################################################################
 
 TARGET_OSES = FreeBSD NetBSD OpenUNIX QNX Darwin OpenBSD \
-              AIX WINNT Linux Android
+              AIX WINNT Linux Android IRIX
 
 ifeq (,$(filter-out $(TARGET_OSES),$(OS_TARGET)))
 include $(CORE_DEPTH)/coreconf/$(OS_TARGET).mk
