$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as an operating system, so that build scripts and tools that parse the target (system-deps, maturin, pyo3-build-config) know it: Unix, SystemV calling convention, ELF, and 32-bit pointers (the N32 ABI).

--- target-lexicon-0.12.16/src/triple.rs.orig
+++ target-lexicon-0.12.16/src/triple.rs
@@ -114,6 +114,10 @@
             Environment::Gnux32 | Environment::GnuIlp32 => return Ok(PointerWidth::U32),
             _ => {}
         }
+        // IRIX: mips64-sgi-irix is the N32 ABI, 32-bit pointers on a 64-bit CPU.
+        if self.operating_system == OperatingSystem::Irix {
+            return Ok(PointerWidth::U32);
+        }
 
         self.architecture.pointer_width()
     }
@@ -138,6 +142,7 @@
             | OperatingSystem::Haiku
             | OperatingSystem::Hermit
             | OperatingSystem::Hurd
+            | OperatingSystem::Irix
             | OperatingSystem::L4re
             | OperatingSystem::Linux
             | OperatingSystem::Netbsd
