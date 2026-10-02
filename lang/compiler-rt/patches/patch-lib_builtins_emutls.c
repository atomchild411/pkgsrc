$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- compiler-rt: emulated TLS without libpthread

--- lib/builtins/emutls.c.orig
+++ lib/builtins/emutls.c
@@ -53,6 +53,20 @@ static pthread_mutex_t emutls_mutex = PTHREAD_MUTEX_INITIALIZER;
 static pthread_key_t emutls_pthread_key;
 static bool emutls_key_created = false;
 
+#if defined(__sgi)
+// IRIX's libc has ENOSYS stubs for part of the pthread API (the mutex calls
+// among them) but not these four, which only libpthread has: referencing
+// them strongly made every object using thread-locals link libpthread. Take
+// them weakly instead. A program without libpthread is single-threaded, so
+// one pointer holds its array; with libpthread, keys work as elsewhere.
+#pragma weak pthread_once
+#pragma weak pthread_key_create
+#pragma weak pthread_getspecific
+#pragma weak pthread_setspecific
+#define EMUTLS_HAVE_PTHREAD_KEYS (&pthread_key_create != NULL)
+static emutls_address_array *emutls_single_thread_array;
+#endif
+
 typedef unsigned int gcc_word __attribute__((mode(word)));
 typedef unsigned int gcc_pointer __attribute__((mode(pointer)));
 
@@ -90,10 +104,20 @@ static __inline void emutls_memalign_free(void *base) {
 }
 
 static __inline void emutls_setspecific(emutls_address_array *value) {
+#if defined(__sgi)
+  if (!EMUTLS_HAVE_PTHREAD_KEYS) {
+    emutls_single_thread_array = value;
+    return;
+  }
+#endif
   pthread_setspecific(emutls_pthread_key, (void *)value);
 }
 
 static __inline emutls_address_array *emutls_getspecific(void) {
+#if defined(__sgi)
+  if (!EMUTLS_HAVE_PTHREAD_KEYS)
+    return emutls_single_thread_array;
+#endif
   return (emutls_address_array *)pthread_getspecific(emutls_pthread_key);
 }
 
@@ -115,12 +139,26 @@ static void emutls_key_destructor(void *ptr) {
 }
 
 static __inline void emutls_init(void) {
+#if defined(__sgi)
+  if (!EMUTLS_HAVE_PTHREAD_KEYS)
+    return;
+#endif
   if (pthread_key_create(&emutls_pthread_key, emutls_key_destructor) != 0)
     abort();
   emutls_key_created = true;
 }
 
 static __inline void emutls_init_once(void) {
+#if defined(__sgi)
+  if (&pthread_once == NULL) {
+    static bool done = false;
+    if (!done) {
+      done = true;
+      emutls_init();
+    }
+    return;
+  }
+#endif
   static pthread_once_t once = PTHREAD_ONCE_INIT;
   pthread_once(&once, emutls_init);
 }
