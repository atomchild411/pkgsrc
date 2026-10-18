$NetBSD$

IRIX: <sys/types.h> defines paddr_t; its uuid_create is DCE's.

--- src/partgptw.c.orig
+++ src/partgptw.c
@@ -65,6 +65,10 @@
   uuid_generate((unsigned char*)ent_uuid);
 #elif defined HAVE_UUIDGEN
   uuidgen((struct uuid*)ent_uuid,1);
+#elif defined(__sgi)
+  /* IRIX: the DCE uuid_create (<sys/uuid.h>), not OSSP's. */
+  uint_t status;
+  uuid_create((uuid_t *)ent_uuid, &status);
 #elif defined HAVE_UUID_CREATE
   uuid_t *uuid;
   char *data_ptr=(char*)&ent_uuid;
