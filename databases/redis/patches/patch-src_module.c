$NetBSD$

Read the 64-bit version field of RedisModuleTypeMethods as 64 bits. Through
a long it reads 0 on 32-bit big-endian hosts, so every module data type was
refused and the built-in vector sets module made redis-server abort at
startup (module.c 'retval == C_OK' assertion).

--- src/module.c.orig
+++ src/module.c
@@ -7531,7 +7531,7 @@
     if (id == 0) return NULL;
     if (moduleTypeLookupModuleByName(name) != NULL) return NULL;
 
-    long typemethods_version = ((long*)typemethods_ptr)[0];
+    long typemethods_version = (long)((uint64_t*)typemethods_ptr)[0];
     if (typemethods_version == 0) return NULL;
 
     struct typemethods {
