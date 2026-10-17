$NetBSD$

host_compile with HOST_CC when set (cross builds: the build host's compiler, not the cc in PATH).

--- cmake/HostCompile.cmake.orig
+++ cmake/HostCompile.cmake
@@ -15,7 +15,11 @@
 
     if(NOT MSVC)
         # assume cc foo.c -o foo # will work on most hosts
-        set(compile_command cc ${src} -o ${dst} ${link_flags})
+        # (HOST_CC: the build host's compiler, when cross-compiling)
+        if(NOT HOST_CC)
+            set(HOST_CC cc)
+        endif()
+        set(compile_command ${HOST_CC} ${src} -o ${dst} ${link_flags})
     else()
         # special case for Visual Studio
 	set(compile_command ${CMAKE_C_COMPILER} ${src} /link "/out:${dst}")
