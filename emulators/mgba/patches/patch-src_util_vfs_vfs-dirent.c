$NetBSD$

Where struct dirent has no d_type (IRIX), use the existing stat() fallback.

--- src/util/vfs/vfs-dirent.c.orig
+++ src/util/vfs/vfs-dirent.c
@@ -148,7 +148,7 @@ const char* _vdeName(struct VDirEntry* v
 
 static enum VFSType _vdeType(struct VDirEntry* vde) {
 	struct VDirEntryDE* vdede = (struct VDirEntryDE*) vde;
-#if !defined(WIN32) && !defined(__HAIKU__)
+#if !defined(WIN32) && !defined(__HAIKU__) && defined(DT_DIR)
 	if (vdede->ent->d_type == DT_DIR) {
 		return VFS_DIRECTORY;
 	} else if (vdede->ent->d_type == DT_REG) {
