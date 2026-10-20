$NetBSD$

IRIX: <sys/param.h>'s roundup(x, y) macro; no d_type in struct dirent (as Solaris and Haiku).

--- port/cpl_vsil_unix_stdio_64.cpp.orig
+++ port/cpl_vsil_unix_stdio_64.cpp
@@ -1457,7 +1457,7 @@
                 osCurFile += '/';
             osCurFile += entry.pszName;
 
-#if !defined(__sun) && !defined(__HAIKU__)
+#if !defined(__sun) && !defined(__HAIKU__) && !defined(__sgi)
             if (psEntry->d_type == DT_REG)
                 entry.nMode = S_IFREG;
             else if (psEntry->d_type == DT_DIR)
@@ -1486,7 +1486,7 @@
                 if (STARTS_WITH(m_osFilterPrefix.c_str(), osName.c_str()) &&
                     m_osFilterPrefix[osName.size()] == '/')
                 {
-#if !defined(__sun) && !defined(__HAIKU__)
+#if !defined(__sun) && !defined(__HAIKU__) && !defined(__sgi)
                     if (psEntry->d_type == DT_UNKNOWN)
 #endif
                     {
@@ -1506,7 +1506,7 @@
             }
 
             if (!m_bNameAndTypeOnly
-#if !defined(__sun) && !defined(__HAIKU__)
+#if !defined(__sun) && !defined(__HAIKU__) && !defined(__sgi)
                 || psEntry->d_type == DT_UNKNOWN
 #endif
             )
