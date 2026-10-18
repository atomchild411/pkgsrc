$NetBSD: patch-external_duckdb_src_include_duckdb_common_platform.hpp,v 1.1 2026/02/09 16:23:29 ryoon Exp $
IRIX: no glibc <features.h>; re2 can use its POSIX reader/writer locks.

--- external/duckdb/src/include/duckdb/common/platform.hpp.orig
+++ external/duckdb/src/include/duckdb/common/platform.hpp
@@ -15,7 +15,7 @@
 #define DUCKDB_QUOTE_DEFINE(x)      DUCKDB_QUOTE_DEFINE_IMPL(x)
 #endif
 
-#if defined(_WIN32) || defined(__APPLE__) || defined(__FreeBSD__)
+#if defined(_WIN32) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__sgi)
 #else
 #if !defined(_GNU_SOURCE)
 #define _GNU_SOURCE
@@ -58,6 +58,10 @@
 	os = "osx";
 #elif defined(__FreeBSD__)
 	os = "freebsd";
+#elif defined(__NetBSD__)
+	os = "netbsd";
+#elif defined(__sgi)
+	os = "irix";
 #endif
 #if defined(__aarch64__) || defined(__ARM_ARCH_ISA_A64)
 	arch = "arm64";
