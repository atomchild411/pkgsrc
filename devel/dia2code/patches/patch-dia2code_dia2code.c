$NetBSD$

2 <= len <= strlen(name) compared a boolean with the length; check that name is at least len long (clang rejects the chained comparison).

--- dia2code/dia2code.c.orig
+++ dia2code/dia2code.c
@@ -111,7 +111,7 @@
         if ( ! strcmp(list->name, name) ) {
             return 1;
         }
-        if ( (len = strlen(list->name)) && (2 <= len <= strlen(name))
+        if ( (len = strlen(list->name)) && (2 <= len && len <= strlen(name))
                 && (mask = strchr(list->name, '*')) != NULL
                 && mask == strrchr(list->name, '*') ) {
             len--;
