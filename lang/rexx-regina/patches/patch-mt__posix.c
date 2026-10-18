$NetBSD$

Close the if block in the five-argument gethostbyname_r() branch (Solaris, IRIX).

--- mt_posix.c.orig
+++ mt_posix.c
@@ -509,6 +509,7 @@
                            g_mt_tsd.gethbyn_buf,
                            sizeof(g_mt_tsd.gethbyn_buf),
                            &herr);
+   }
    else
    {
       mt_tsd_t *mt = (mt_tsd_t *)__regina_get_tsd()->mt_tsd;
