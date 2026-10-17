$NetBSD$

32-bit MIPS: the small object class is SmallObjectClasses[0] (there is
no SmallIntClass any more), loaded through its GOT address as the 64-bit
path does.

--- objc_msgSend.mips.S.orig
+++ objc_msgSend.mips.S
@@ -189,8 +189,9 @@
 	b      1b                               # Return to the normal path
 	LP     $t0, ($t0)                       # Load the class (in delay slot)
 #else
-	b      1b
-	LP     $t0, %got_disp(CDECL(SmallIntClass))($t8)
+	LP     $t0, %got_disp(CDECL(SmallObjectClasses))($t8) # Load small object classes array address
+	b      1b                               # Return to the normal path
+	LP     $t0, ($t0)                       # Load the one 32-bit class (in delay slot)
 #endif
 	.cfi_endproc
 .endm
