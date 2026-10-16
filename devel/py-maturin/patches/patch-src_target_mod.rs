$NetBSD$

IRIX 6.5 (mips64-sgi-irix) as a target: sys.platform irix, wheel tag irix_mipseb (pkgsrc's IRIX Python: _PYTHON_HOST_PLATFORM=irix-mipseb).

--- src/target/mod.rs.orig
+++ src/target/mod.rs
@@ -50,6 +50,7 @@
     Aix,
     Hurd,
     Cygwin,
+    Irix,
     Android,
 }
 
@@ -72,6 +73,7 @@
             Os::Aix => write!(f, "AIX"),
             Os::Hurd => write!(f, "Hurd"),
             Os::Cygwin => write!(f, "Cygwin"),
+            Os::Irix => write!(f, "IRIX"),
             Os::Android => write!(f, "Android"),
         }
     }
@@ -234,6 +236,8 @@
         Os::Aix => &[Arch::Powerpc64],
         Os::Hurd => &[Arch::X86, Arch::X86_64],
         Os::Cygwin => &[Arch::X86, Arch::X86_64],
+        // mips64-sgi-irix: MIPS IV, the N32 ABI
+        Os::Irix => &[Arch::Mips64],
     }
 }
 
@@ -312,6 +316,7 @@
             OperatingSystem::Aix => Os::Aix,
             OperatingSystem::Hurd => Os::Hurd,
             OperatingSystem::Cygwin => Os::Cygwin,
+            OperatingSystem::Irix => Os::Irix,
             unsupported => bail!("The operating system {:?} is not supported", unsupported),
         };
 
@@ -494,6 +499,7 @@
             Os::Aix => "aix",
             Os::Hurd => "gnu",
             Os::Cygwin => "cygwin",
+            Os::Irix => "irix",
         }
     }
 
@@ -591,6 +597,7 @@
             | Os::Aix
             | Os::Hurd
             | Os::Cygwin
+            | Os::Irix
             | Os::Android => true,
         }
     }
