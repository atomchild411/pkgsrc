$NetBSD$

IRIX has no SCM_TIMESTAMP: no receive time stamps (the warning and zero
that follow, as when the kernel sends none).

--- src/modules/rtp/rtp-native.c.orig
+++ src/modules/rtp/rtp-native.c
@@ -362,12 +362,14 @@
         pa_memchunk_reset(&c->memchunk);
     }
 
+#ifdef SCM_TIMESTAMP
     for (cm = CMSG_FIRSTHDR(&m); cm; cm = CMSG_NXTHDR(&m, cm))
         if (cm->cmsg_level == SOL_SOCKET && cm->cmsg_type == SCM_TIMESTAMP) {
             memcpy(tstamp, CMSG_DATA(cm), sizeof(struct timeval));
             found_tstamp = true;
             break;
         }
+#endif
 
     if (!found_tstamp) {
         pa_log_warn("Couldn't find SCM_TIMESTAMP data in auxiliary recvmsg() data!");
