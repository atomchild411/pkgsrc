$NetBSD$

IRIX: <unistd.h> is visible here (through IRIX's headers) and declares
close(); a static function of that name conflicts. Rename it.

--- libavcodec/apv_parser.c.orig
+++ libavcodec/apv_parser.c
@@ -194,7 +194,7 @@
     return 0;
 }
 
-static av_cold void close(AVCodecParserContext *s)
+static av_cold void apv_close(AVCodecParserContext *s)
 {
     APVParseContext *p = s->priv_data;
     ParseContext *pc = &p->pc;
@@ -209,5 +209,5 @@
     .priv_data_size = sizeof(APVParseContext),
     .init           = init,
     .parse          = parse,
-    .close          = close,
+    .close          = apv_close,
 };
