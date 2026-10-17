$NetBSD: patch-src_lib_fcitx-utils_library.cpp,v 1.1 2022/03/27 12:45:04 tnn Exp $

Fix build on SunOS
RTLD_NODELETE only where dlopen has it (not IRIX).

--- src/lib/fcitx-utils/library.cpp.orig
+++ src/lib/fcitx-utils/library.cpp
@@ -56,15 +56,17 @@
         flag |= RTLD_LAZY;
     }
 
+#ifdef RTLD_NODELETE
     if (hint & LibraryLoadHint::PreventUnloadHint) {
         flag |= RTLD_NODELETE;
     }
+#endif
 
     if (hint & LibraryLoadHint::ExportExternalSymbolsHint) {
         flag |= RTLD_GLOBAL;
     }
 
-#ifdef HAS_DLMOPEN
+#if defined(HAS_DLMOPEN) && defined(LM_ID_NEWLM)
     if (hint & LibraryLoadHint::NewNameSpace) {
         // allow dlopen self
         d->handle_ = dlmopen(
@@ -173,7 +175,7 @@
 }
 
 bool Library::isNewNamespaceSupported() {
-#ifdef HAS_DLMOPEN
+#if defined(HAS_DLMOPEN) && defined(LM_ID_NEWLM)
     return true;
 #else
     return false;
