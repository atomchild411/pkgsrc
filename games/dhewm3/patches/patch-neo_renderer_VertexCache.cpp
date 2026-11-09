$NetBSD$

UnbindIndex() called qglBindBufferARB() also when the GL has no
ARB_vertex_buffer_object, where the pointer is NULL (a crash). Bind only
with it, as the other unbinds do.

--- neo/renderer/VertexCache.cpp.orig
+++ neo/renderer/VertexCache.cpp
@@ -139,7 +139,10 @@
 }
 
 void idVertexCache::UnbindIndex() {
-	qglBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
+	// qglBindBufferARB is NULL without ARB_vertex_buffer_object
+	if ( glConfig.ARBVertexBufferObjectAvailable ) {
+		qglBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
+	}
 }
 
 
