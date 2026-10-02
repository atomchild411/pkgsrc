$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts

--- ELF/InputSection.cpp.orig
+++ ELF/InputSection.cpp
@@ -1150,7 +1150,15 @@ void InputSection::relocateNonAlloc(Ctx &ctx, uint8_t *buf,
     // 2017 (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82630), but we need to
     // keep this bug-compatible code for a while.
     bool isErr = expr != R_PC && !(emachine == EM_386 && type == R_386_GOTPC);
-    {
+    // IRIX's crt1.o, which every program links, has PC-relative and GOT-call
+    // (R_MIPS_CALL_HI16/LO16) relocations in its .MIPS.events sections. Only
+    // IRIX's performance tools read those sections; the PC-relative ones are
+    // resolved zero-based below as usual, the rest are left as they are.
+    bool irixEvents = ctx.arg.osabi == ELFOSABI_IRIX &&
+                      name.starts_with(".MIPS.events");
+    if (irixEvents && isErr)
+      continue;
+    if (!irixEvents) {
       ELFSyncStream diag(ctx, isErr && !ctx.arg.noinhibitExec
                                   ? DiagLevel::Err
                                   : DiagLevel::Warn);
