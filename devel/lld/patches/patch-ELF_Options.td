$NetBSD: patch-ELF_Options.td,v 1.5 2022/08/12 08:52:51 pin Exp $

Add dummy option for an AArch64 erratum.

IRIX (merged by hand from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main): accept and ignore MIPSpro ld's registry, version and ABI
options, which libtool and IRIX build recipes pass.

--- ELF/Options.td.orig	2022-06-22 16:46:24.000000000 +0000
+++ ELF/Options.td
@@ -217,6 +217,9 @@ defm filter: Eq<"filter", "Set DT_FILTER
 
 defm fini: Eq<"fini", "Specify a finalizer function">, MetaVarName<"<symbol>">;
 
+def fix_cortex_a53_835769: F<"fix-cortex-a53-835769">,
+  HelpText<"Apply fixes for AArch64 Cortex-A53 erratum 835769">;
+
 def fix_cortex_a53_843419: F<"fix-cortex-a53-843419">,
   HelpText<"Apply fixes for AArch64 Cortex-A53 erratum 843419">;
 
@@ -825,6 +828,25 @@ def: F<"warn-once">;
 def: F<"warn-shared-textrel">;
 def: JoinedOrSeparate<["-"], "G">;
 
+// MIPSpro ld's shared-object registry and version options, which libtool
+// passes on IRIX. Accepted and ignored.
+def: Separate<["-"], "set_version">;
+def: Joined<["-"], "set_version=">;
+def: Separate<["-"], "check_registry">;
+def: Joined<["-"], "check_registry=">;
+def: Separate<["-"], "update_registry">;
+def: Joined<["-"], "update_registry=">;
+def: Separate<["-"], "create_registry">;
+def: Joined<["-"], "create_registry=">;
+
+// And the ABI and layout options that build systems' IRIX recipes put on
+// "ld -n32 -shared -rdata_shared" lines (Tcl's, imake's): the ABI comes from
+// the objects, and read-only data is always shared.
+def: Flag<["-"], "n32">;
+def: Flag<["-"], "64">;
+def: Flag<["-"], "rdata_shared">;
+def: Flag<["-"], "elf">;
+
 // Hidden option used for testing MIPS multi-GOT implementation.
 defm mips_got_size:
   Eq<"mips-got-size", "Max size of a single MIPS GOT. 0x10000 by default.">,
