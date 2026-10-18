$NetBSD$

IRIX: <sys/types.h> already defines pgno_t (as in databases/lmdb).

--- lib/mdb.c.orig
+++ lib/mdb.c
@@ -475,6 +475,10 @@
 	 *	@note In the #MDB_node structure, we only store 48 bits of this value,
 	 *	which thus limits us to only 60 bits of addressable data.
 	 */
+#ifdef __sgi
+	/* IRIX's <sys/types.h> has a pgno_t of its own. */
+#define pgno_t	mdb_pgno_t
+#endif
 typedef MDB_ID	pgno_t;
 
 	/** A transaction ID.
