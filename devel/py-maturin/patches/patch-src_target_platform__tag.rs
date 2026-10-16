$NetBSD$

IRIX 6.5 (mips64-sgi-irix) as a target: sys.platform irix, wheel tag irix_mipseb (pkgsrc's IRIX Python: _PYTHON_HOST_PLATFORM=irix-mipseb).

--- src/target/platform_tag.rs.orig
+++ src/target/platform_tag.rs
@@ -173,6 +173,8 @@
         }
         // AIX
         (Os::Aix, _) => aix_platform_tag(target)?,
+        // IRIX: what pkgsrc's IRIX Python reports (_PYTHON_HOST_PLATFORM irix-mipseb)
+        (Os::Irix, _) => "irix_mipseb".to_string(),
         // osname_release_machine fallback for any POSIX system
         (_, _) => {
             let info = PlatformInfo::new()
