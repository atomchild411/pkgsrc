$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- compiler-rt: crtbegin for rld's DT_INIT/DT_FINI, and __cxa_atexit

--- lib/builtins/crtbegin.c.orig
+++ lib/builtins/crtbegin.c
@@ -8,6 +8,10 @@
 
 #include <stddef.h>
 
+#ifdef __sgi
+#include <pthread.h>
+#endif
+
 #ifndef __has_feature
 # define __has_feature(x) 0
 #endif
@@ -34,7 +38,9 @@ static fp __CTOR_LIST__[]
 extern fp __CTOR_LIST_END__[];
 #endif
 
+#ifndef __sgi
 extern void __cxa_finalize(void *) __attribute__((weak));
+#endif
 
 static void __attribute__((used)) __do_init(void) {
   static _Bool __initialized;
@@ -81,6 +87,12 @@ __asm__(".pushsection .init_array,\"aw\",@init_array\n\t"
 __attribute__((section(".init_array"),
                used)) static void (*__init)(void) = __do_init;
 # endif
+#elif defined(__sgi)
+// IRIX: rld calls DT_INIT and DT_FINI -- the linker points them at _init
+// and _fini -- for executables and shared objects alike. crt1.o's .init
+// (the __istart it builds) runs for executables only. Hidden, so one
+// object's _init cannot interpose on another's.
+__attribute__((visibility("hidden"), used)) void _init(void) { __do_init(); }
 #elif defined(__i386__) || defined(__x86_64__)
 __asm__(".pushsection .init,\"ax\",@progbits\n\t"
         "call __do_init\n\t"
@@ -116,14 +128,91 @@ static fp __DTOR_LIST__[]
 extern fp __DTOR_LIST_END__[];
 #endif
 
+#ifdef __sgi
+// IRIX's libc has no __cxa_atexit (C++ registers static destructors with it)
+// and its atexit holds only 32 entries. This one keeps a list in chunks,
+// shared by every object: rld binds all of them to the first definition.
+typedef void (*__cxa_atexit_fn)(void *);
+
+#define __CXA_ATEXIT_CHUNK 256
+struct __cxa_atexit_chunk {
+  int count;
+  struct __cxa_atexit_chunk *next;
+  __cxa_atexit_fn funs[__CXA_ATEXIT_CHUNK];
+  void *args[__CXA_ATEXIT_CHUNK];
+  void *dsos[__CXA_ATEXIT_CHUNK];
+};
+
+// Weak: a program need not link malloc or pthreads for this to work.
+void *malloc(size_t) __attribute__((weak));
+int pthread_mutex_lock(pthread_mutex_t *) __attribute__((weak));
+int pthread_mutex_unlock(pthread_mutex_t *) __attribute__((weak));
+
+static struct __cxa_atexit_chunk __cxa_atexit_first;
+static struct __cxa_atexit_chunk *__cxa_atexit_list = &__cxa_atexit_first;
+static pthread_mutex_t __cxa_atexit_mutex = PTHREAD_MUTEX_INITIALIZER;
+
+static void __cxa_atexit_lock(void) {
+  if (pthread_mutex_lock)
+    pthread_mutex_lock(&__cxa_atexit_mutex);
+}
+
+static void __cxa_atexit_unlock(void) {
+  if (pthread_mutex_unlock)
+    pthread_mutex_unlock(&__cxa_atexit_mutex);
+}
+
+int __cxa_atexit(__cxa_atexit_fn func, void *arg, void *dso) {
+  __cxa_atexit_lock();
+  if (__cxa_atexit_list->count == __CXA_ATEXIT_CHUNK) {
+    struct __cxa_atexit_chunk *chunk =
+        malloc ? (struct __cxa_atexit_chunk *)malloc(sizeof *chunk) : NULL;
+    if (!chunk) {
+      __cxa_atexit_unlock();
+      return -1;
+    }
+    chunk->count = 0;
+    chunk->next = __cxa_atexit_list;
+    __cxa_atexit_list = chunk;
+  }
+  int i = __cxa_atexit_list->count++;
+  __cxa_atexit_list->funs[i] = func;
+  __cxa_atexit_list->args[i] = arg;
+  __cxa_atexit_list->dsos[i] = dso;
+  __cxa_atexit_unlock();
+  return 0;
+}
+
+// Runs, newest first, the handlers registered for `dso` (all of them if it
+// is NULL), each once.
+void __cxa_finalize(void *dso) {
+  __cxa_atexit_lock();
+  for (struct __cxa_atexit_chunk *c = __cxa_atexit_list; c; c = c->next)
+    for (int i = c->count - 1; i >= 0; i--) {
+      if (!c->funs[i] || (dso && c->dsos[i] != dso))
+        continue;
+      __cxa_atexit_fn f = c->funs[i];
+      c->funs[i] = NULL;
+      __cxa_atexit_unlock();
+      f(c->args[i]);
+      __cxa_atexit_lock();
+    }
+  __cxa_atexit_unlock();
+}
+#endif
+
 static void __attribute__((used)) __do_fini(void) {
   static _Bool __finalized;
   if (__builtin_expect(__finalized, 0))
     return;
   __finalized = 1;
 
+#ifdef __sgi
+  __cxa_finalize(__dso_handle); // defined above, never absent
+#else
   if (__cxa_finalize)
     __cxa_finalize(__dso_handle);
+#endif
 
 #ifndef CRT_HAS_INITFINI_ARRAY
   const size_t n = __DTOR_LIST_END__ - __DTOR_LIST__ - 1;
@@ -163,6 +252,8 @@ __asm__(".pushsection .fini_array,\"aw\",@fini_array\n\t"
 __attribute__((section(".fini_array"),
                used)) static void (*__fini)(void) = __do_fini;
 # endif
+#elif defined(__sgi)
+__attribute__((visibility("hidden"), used)) void _fini(void) { __do_fini(); }
 #elif defined(__i386__) || defined(__x86_64__)
 __asm__(".pushsection .fini,\"ax\",@progbits\n\t"
         "call __do_fini\n\t"
