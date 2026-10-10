$NetBSD$

CVE-2026-95512: limit subroutine overlaps in cid_read_subrs.
Upstream commit f3ca71c9900fe860849b3163a6e2c1e765b291d9.

--- src/cid/cidload.c.orig
+++ src/cid/cidload.c
@@ -517,6 +517,7 @@
     CID_Subrs      subr;
     FT_UInt        max_offsets = 0;
     FT_ULong*      offsets = NULL;
+    FT_ULong       cum_len = 0;
     PSAux_Service  psaux = (PSAux_Service)face->psaux;
 
 
@@ -584,6 +585,14 @@
       /* now, compute the size of subrs charstrings, */
       /* allocate, and read them                     */
       data_len = offsets[num_subrs] - offsets[0];
+      cum_len += data_len;
+
+      if ( cum_len / 4 > stream->size )
+      {
+        FT_ERROR(( "cid_read_subrs: excessive overlaps\n" ));
+        error = FT_THROW( Invalid_File_Format );
+        goto Fail;
+      }
 
       if ( FT_QNEW_ARRAY( subr->code, num_subrs + 1 ) ||
            FT_QALLOC( subr->code[0], data_len )       )
