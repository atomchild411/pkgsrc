# $NetBSD$
#
# Cross builds cannot make GObject introspection data: g-ir-scanner runs
# programs built for the target. The packages build without it
# (devel/gobject-introspection/buildlink3.mk adds no dependency there, and
# devel/meson/build.mk turns the projects' options off), so their .gir and
# .typelib files, and the Vala bindings made from them, are not installed:
# drop those that are missing from the PLIST.

BEGIN {
	PREFIX = ENVIRON["PREFIX"]
	TEST = ENVIRON["TEST"] ? ENVIRON["TEST"] : "test"
}

/^share\/gir-1\.0\/[^\/]*\.gir$/ ||
/^lib\/girepository-1\.0\/[^\/]*\.typelib$/ ||
/^share\/vala\/vapi\/[^\/]*\.(vapi|deps)$/ {
	if (system(TEST " -f \"" PREFIX "/" $0 "\"") != 0)
		next
}
