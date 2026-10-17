$NetBSD$

IRIX is ELF but has no <link.h> (dl_iterate_phdr, ElfW): leave it out, as Linux without USE_DL.

--- src/tools.c.orig
+++ src/tools.c
@@ -10,7 +10,7 @@
  *
  */
 
-#if (defined(__ELF__) && !defined(__linux__)) || defined(USE_DL)
+#if (defined(__ELF__) && !defined(__linux__) && !defined(__sgi)) || defined(USE_DL)
 #define _GNU_SOURCE
 #include <dlfcn.h>
 #include <link.h>
@@ -5487,7 +5487,7 @@
 	return ret;
 }
 
-#if (defined(__ELF__) && !defined(__linux__)) || defined(USE_DL)
+#if (defined(__ELF__) && !defined(__linux__) && !defined(__sgi)) || defined(USE_DL)
 /* calls dladdr() or dladdr1() on <addr> and <dli>. If dladdr1 is available,
  * also returns the symbol size in <size>, otherwise returns 0 there.
  */
@@ -5633,7 +5633,7 @@
 #undef DEF_SYM
 	};
 
-#if (defined(__ELF__) && !defined(__linux__)) || defined(USE_DL)
+#if (defined(__ELF__) && !defined(__linux__) && !defined(__sgi)) || defined(USE_DL)
 	static Dl_info dli_main;
 	static int dli_main_done; // 0 = not resolved, 1 = resolve in progress, 2 = done
 	__decl_thread_var(static HA_SPINLOCK_T dladdr_lock);
@@ -5668,7 +5668,7 @@
 	if (!best_dist)
 		goto use_array;
 
-#if (defined(__ELF__) && !defined(__linux__)) || defined(USE_DL)
+#if (defined(__ELF__) && !defined(__linux__) && !defined(__sgi)) || defined(USE_DL)
 	/* Now let's try to be smarter */
 
 	/* dladdr_and_size() can be super expensive and will often rely on a
@@ -5793,7 +5793,7 @@
  */
 const void *resolve_dso_name(struct buffer *buf, const char *pfx, const void *addr)
 {
-#if (defined(__ELF__) && !defined(__linux__)) || defined(USE_DL)
+#if (defined(__ELF__) && !defined(__linux__) && !defined(__sgi)) || defined(USE_DL)
 	Dl_info dli;
 	size_t size;
 	const char *fname, *p;
