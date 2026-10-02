# $NetBSD$
#
# Cross builds cannot make GObject introspection data: g-ir-scanner runs
# programs built for the target. The packages build without it
# (devel/gobject-introspection/buildlink3.mk adds no dependency there), and
# their .gir and .typelib files are dropped from the PLIST.

/^share\/gir-1\.0\/[^\/]*\.gir$/ { next }
/^lib\/girepository-1\.0\/[^\/]*\.typelib$/ { next }
