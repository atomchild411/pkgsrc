$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts

--- ELF/MarkLive.cpp.orig
+++ ELF/MarkLive.cpp
@@ -221,7 +221,9 @@ static bool isReserved(InputSectionBase *sec) {
     // while.
     StringRef s = sec->name;
     return s == ".init" || s == ".fini" || s.starts_with(".init_array") ||
-           s == ".jcr" || s.starts_with(".ctors") || s.starts_with(".dtors");
+           s == ".jcr" || s.starts_with(".ctors") || s.starts_with(".dtors") ||
+           // IRIX's .MIPS.events sections, read by its tools.
+           s.starts_with(".MIPS.events");
   }
 }
 
