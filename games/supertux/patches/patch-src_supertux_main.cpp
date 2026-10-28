$NetBSD$

Pass argv[0] to PHYSFS_init. Without /proc/self/exe (Linux, NetBSD) or
getexecname() (Solaris), physfs needs it to find the base directory:
on IRIX PHYSFS_init(NULL) failed ("Couldn't initialize physfs: no error").

--- src/supertux/main.cpp.orig
+++ src/supertux/main.cpp
@@ -793,7 +793,7 @@
 #ifdef __ANDROID__
     m_physfs_subsystem.reset(new PhysfsSubsystem(nullptr, args.datadir, SDL_AndroidGetExternalStoragePath()));
 #else
-    m_physfs_subsystem.reset(new PhysfsSubsystem(nullptr, args.datadir, args.userdir));
+    m_physfs_subsystem.reset(new PhysfsSubsystem(argv[0], args.datadir, args.userdir));
 #endif
     m_physfs_subsystem->print_search_path();
 
