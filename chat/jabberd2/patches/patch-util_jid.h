$NetBSD$

IRIX <sys/types.h> defines a jid_t (job ID) of its own.

--- util/jid.h.orig
+++ util/jid.h
@@ -39,6 +39,12 @@
 #define MAXLEN_JID_COMP  1023    /* XMPP (RFC3920) 3.1 */
 #define MAXLEN_JID       3071    /* nodename (1023) + '@' + domain (1023) + '/' + resource (1023) = 3071 */
 
+#ifdef __sgi
+/* IRIX's <sys/types.h> has a jid_t (job ID) of its own. */
+#include <sys/types.h>
+#define jid_t jabberd_jid_t
+#endif
+
 typedef struct jid_st {
     /* basic components of the jid */
     char   *node;
