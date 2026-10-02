$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Add the IRIX target: triple, ELF, EH encodings, n32 codegen

--- lib/TargetParser/Triple.cpp.orig
+++ lib/TargetParser/Triple.cpp
@@ -262,6 +262,7 @@ StringRef Triple::getVendorTypeName(VendorType Kind) {
   case Freescale: return "fsl";
   case IBM: return "ibm";
   case ImaginationTechnologies: return "img";
+  case SGI: return "sgi";
   case Intel:
     return "intel";
   case Mesa: return "mesa";
@@ -298,6 +299,7 @@ StringRef Triple::getOSTypeName(OSType Kind) {
   case IOS: return "ios";
   case KFreeBSD: return "kfreebsd";
   case Linux: return "linux";
+  case IRIX: return "irix";
   case Lv2: return "lv2";
   case MacOSX: return "macosx";
   case Managarm:
@@ -669,6 +671,7 @@ static Triple::VendorType parseVendor(StringRef VendorName) {
       .Case("suse", Triple::SUSE)
       .Case("oe", Triple::OpenEmbedded)
       .Case("intel", Triple::Intel)
+      .Case("sgi", Triple::SGI)
       .Default(Triple::UnknownVendor);
 }
 
@@ -681,6 +684,7 @@ static Triple::OSType parseOS(StringRef OSName) {
     .StartsWith("ios", Triple::IOS)
     .StartsWith("kfreebsd", Triple::KFreeBSD)
     .StartsWith("linux", Triple::Linux)
+    .StartsWith("irix", Triple::IRIX)
     .StartsWith("lv2", Triple::Lv2)
     .StartsWith("macos", Triple::MacOSX)
     .StartsWith("managarm", Triple::Managarm)
