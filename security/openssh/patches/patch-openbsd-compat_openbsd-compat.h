$NetBSD$

IRIX: with BROKEN_SNPRINTF (set in config.h for IRIX, whose printf has no
%zu), rename OpenSSH's snprintf/vsnprintf so they do not collide with
IRIX's pre-C99 prototypes.  (As in the hand-built 9.8p1 proven on IRIX.)

--- openbsd-compat/openbsd-compat.h.orig
+++ openbsd-compat/openbsd-compat.h
@@ -386,4 +386,19 @@
 # endif /* __GNU_LIBRARY__ && __GLIBC_PREREQ */
 #endif /* HAVE_FEATURES_H && _FORTIFY_SOURCE */
 
+#if defined(__sgi) && defined(BROKEN_SNPRINTF)
+/*
+ * IRIX: libc's snprintf/vsnprintf predate C99 (no %zu), so OpenSSH's own are
+ * used -- but those names are taken by IRIX's pre-C99 prototypes (or our
+ * compiler's C99 wrapper macros), so rename definitions and callers alike.
+ */
+# include <stdarg.h>
+# undef snprintf
+# undef vsnprintf
+int ssh_compat_snprintf(char *, size_t, SNPRINTF_CONST char *, ...);
+int ssh_compat_vsnprintf(char *, size_t, const char *, va_list);
+# define snprintf  ssh_compat_snprintf
+# define vsnprintf ssh_compat_vsnprintf
+#endif
+
 #endif /* _OPENBSD_COMPAT_H */
