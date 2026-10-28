$NetBSD$

Pass argv[0] to PHYSFS_init. Without /proc/self/exe (Linux, NetBSD) or
getexecname() (Solaris), physfs needs it to find the base directory:
on IRIX PHYSFS_init(NULL) failed ("Couldn't initialize physfs: no error").
Fall back to the installed data directory when SDL_GetBasePath() cannot
find the executable (no /proc/self/exe on IRIX; under revenir it names
the emulator, so it looked in /usr/local/share/games/supertux2).

--- src/supertux/main.cpp.orig
+++ src/supertux/main.cpp
@@ -243,6 +243,10 @@
       // the global install location
       m_datadir = basepath.substr(0, basepath.rfind(INSTALL_SUBDIR_BIN));
       m_datadir = FileSystem::join(m_datadir, INSTALL_SUBDIR_SHARE);
+      // SDL_GetBasePath() needs /proc/self/exe: IRIX has none (and under
+      // an emulator it names the emulator), so fall back to the prefix.
+      if (!FileSystem::exists(FileSystem::join(m_datadir, "credits.stxt")))
+        m_datadir = FileSystem::join("@PREFIX@", INSTALL_SUBDIR_SHARE);
     }
   }
 
@@ -793,7 +797,7 @@
 #ifdef __ANDROID__
     m_physfs_subsystem.reset(new PhysfsSubsystem(nullptr, args.datadir, SDL_AndroidGetExternalStoragePath()));
 #else
-    m_physfs_subsystem.reset(new PhysfsSubsystem(nullptr, args.datadir, args.userdir));
+    m_physfs_subsystem.reset(new PhysfsSubsystem(argv[0], args.datadir, args.userdir));
 #endif
     m_physfs_subsystem->print_search_path();
 
