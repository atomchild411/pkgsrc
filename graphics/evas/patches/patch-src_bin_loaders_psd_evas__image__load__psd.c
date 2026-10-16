$NetBSD: patch-src_bin_loaders_psd_evas__image__load__psd.c,v 1.1 2016/02/14 13:14:06 jperkin Exp $

Don't redefine _XOPEN_SOURCE on SunOS.
IRIX too: a bare _XOPEN_SOURCE (XPG4) hides struct timespec, which eina uses.

--- src/bin/loaders/psd/evas_image_load_psd.c.orig	2012-11-23 16:35:06.000000000 +0000
+++ src/bin/loaders/psd/evas_image_load_psd.c
@@ -1,4 +1,6 @@
+#if !defined(__sun) && !defined(__sgi)
 #define _XOPEN_SOURCE
+#endif
 
 #ifdef HAVE_CONFIG_H
 # include <config.h>
