$NetBSD$

__LOCALE_H__ is <locale.h>'s own include guard on IRIX: with it defined, <locale.h> declares nothing.

--- include/bz_Locale.h.orig
+++ include/bz_Locale.h
@@ -10,8 +10,8 @@
  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
  */
 
-#ifndef __LOCALE_H__
-#define __LOCALE_H__
+#ifndef __BZ_LOCALE_H__
+#define __BZ_LOCALE_H__
 
 #include "common.h"
 
