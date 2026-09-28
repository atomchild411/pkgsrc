$NetBSD$

The data table of contents in C: let the compiler of the data library fill
in the byte order, character set family and UChar size. Written as numbers,
they were the build machine's, and a cross build for a big-endian target
from a little-endian one got a library ICU refuses (U_INVALID_FORMAT_ERROR).

--- tools/toolutil/pkg_gencmn.cpp.orig
+++ tools/toolutil/pkg_gencmn.cpp
@@ -373,7 +373,7 @@
             "} U_EXPORT2 %s_dat = {\n"
             "    32, 0xda, 0x27, {\n"
             "        %lu, 0,\n"
-            "        %u, %u, %u, 0,\n"
+            "        U_IS_BIG_ENDIAN, U_CHARSET_FAMILY, U_SIZEOF_UCHAR, 0,\n"
             "        {0x54, 0x6f, 0x43, 0x50},\n"
             "        {1, 0, 0, 0},\n"
             "        {0, 0, 0, 0}\n"
@@ -383,9 +383,6 @@
             static_cast<unsigned long>(fileCount),
             entrypointName,
             static_cast<unsigned long>(sizeof(UDataInfo)),
-            U_IS_BIG_ENDIAN,
-            U_CHARSET_FAMILY,
-            U_SIZEOF_UCHAR,
             static_cast<unsigned long>(fileCount)
         );
         T_FileStream_writeLine(out, buffer);
