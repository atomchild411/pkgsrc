$NetBSD$

The socket bind(), not std::bind: where bind() takes a const void * (IRIX), the template is the better match.

--- nxcomp/src/Loop.cpp.orig
+++ nxcomp/src/Loop.cpp
@@ -4221,7 +4221,7 @@
       goto SetupSocketError;
     }
 
-  if (bind(newFD, addr, addrlen) == -1)
+  if (::bind(newFD, addr, addrlen) == -1)
   {
     nxfatal << "Loop: PANIC! Call to bind failed for " << label
             << ". Error is " << EGET()
