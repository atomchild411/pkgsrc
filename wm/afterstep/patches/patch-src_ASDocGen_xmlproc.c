$NetBSD: patch-src_ASDocGen_xmlproc.c,v 1.1 2025/09/11 21:35:01 gutteridge Exp $

Use ctype.h correctly.
Drop a comparison with a UTF-8 multi-character constant, which clang rejects
(never true with gcc).

--- src/ASDocGen/xmlproc.c.orig
+++ src/ASDocGen/xmlproc.c
@@ -111,7 +111,7 @@
 		Bool special = False ;
 		for( i = 0 ; i < len ; ++i ) 
 		{
-			if( (!isalnum(cdata[i]) && cdata[i] != '_'  && cdata[i] != '(' && cdata[i] != ')') || special )
+			if( (!isalnum((unsigned char)cdata[i]) && cdata[i] != '_'  && cdata[i] != '(' && cdata[i] != ')') || special )
 			{
 				if( token_start < i )
 				{	
@@ -179,7 +179,7 @@
 				fputs( "\\&", state->dest_fp );	
 			else if ( c == '\\' && state->doc_type == DocType_NROFF ) 
 				fputc( '\\', state->dest_fp );	
-			else if ( c == '' && state->doc_type == DocType_NROFF ) 
+			else if ( 0 /* c == U+0098 in UTF-8: a multi-character constant no char equals (gcc); clang rejects it */ && state->doc_type == DocType_NROFF ) 
 				c = '~';
 			fputc( c, state->dest_fp );
 		}		   
@@ -243,7 +243,7 @@
 					--len ;
 				/* we want to skip as much whitespace as possible in NROFF */
 				for( i = 0 ; i < len ; ++i ) 
-					if( !isspace(data_ptr[i]) )
+					if( !isspace((unsigned char)data_ptr[i]) )
 						break;
 				if( i == len ) 
 					len = 0 ;
@@ -253,9 +253,9 @@
 					Bool written = 0 ;
 					for( i = 0 ; i < len ; ++i ) 
 					{
-						while( isspace(data_ptr[i]) && i < len ) ++i ;
+						while( isspace((unsigned char)data_ptr[i]) && i < len ) ++i ;
 						from = i ; 
-						while( !isspace(data_ptr[i]) && i < len ) ++i ;
+						while( !isspace((unsigned char)data_ptr[i]) && i < len ) ++i ;
 						to = i ; 
 						if( to > from  ) 
 						{	
@@ -501,12 +501,12 @@
 	LOCAL_DEBUG_OUT( "term_text = \"%s\"", term_text );
 	while(*term_text)
 	{	
-		if( isalnum(*term_text) )
+		if( isalnum((unsigned char)*term_text) )
 			break;
 		++term_text ;
 	}
 	i = 0 ;
-	while( isalnum(term_text[i]) ) ++i ;
+	while( isalnum((unsigned char)term_text[i]) ) ++i ;
 	term_text[i] = '\0' ;
 
 	if( term_text[0] != '\0' ) /* need to add glossary term */
