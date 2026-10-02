$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Add the IRIX target: triple, ELF, EH encodings, n32 codegen
- clang: IRIX target info and toolchain driver

--- include/llvm/TargetParser/Triple.h.orig
+++ include/llvm/TargetParser/Triple.h
@@ -197,7 +197,8 @@ public:
     SUSE,
     OpenEmbedded,
     Intel,
-    LastVendorType = Intel
+    SGI,
+    LastVendorType = SGI
   };
   enum OSType {
     UnknownOS,
@@ -243,7 +244,8 @@ public:
     LiteOS,
     Serenity,
     Vulkan, // Vulkan SPIR-V
-    LastOSType = Vulkan
+    IRIX,   // SGI IRIX
+    LastOSType = IRIX
   };
   enum EnvironmentType {
     UnknownEnvironment,
@@ -729,6 +731,11 @@ public:
     return getOS() == Triple::Linux;
   }
 
+  /// Tests whether the OS is IRIX.
+  bool isOSIRIX() const {
+    return getOS() == Triple::IRIX;
+  }
+
   /// Tests whether the OS is kFreeBSD.
   bool isOSKFreeBSD() const {
     return getOS() == Triple::KFreeBSD;
@@ -1164,7 +1171,7 @@ public:
   /// Note: Android API level 29 (10) introduced ELF TLS.
   bool hasDefaultEmulatedTLS() const {
     return (isAndroid() && isAndroidVersionLT(29)) || isOSOpenBSD() ||
-           isWindowsCygwinEnvironment() || isOHOSFamily();
+           isWindowsCygwinEnvironment() || isOHOSFamily() || isOSIRIX();
   }
 
   /// True if the target uses TLSDESC by default.
