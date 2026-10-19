$NetBSD$

Swap() assigns to its argument: not a const reference (current clang checks templates).

--- src/tmemory.h.orig
+++ src/tmemory.h
@@ -469,7 +469,7 @@
 		Reference();
 	}
 
-	void Swap(const Self &other)
+	void Swap(Self &other)	/* assigns to other: not const */
 	{
 		T *oldptr = p;
 		TSharedPtrRef *oldref = r;
