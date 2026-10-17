# $NetBSD$
#
# Cross builds cannot make GObject introspection data: g-ir-scanner runs
# programs built for the target. The packages build without it
# (devel/gobject-introspection/buildlink3.mk adds no dependency there, and
# devel/meson/build.mk turns the projects' options off), so their .gir and
# .typelib files, the Vala bindings made from them, and the PyGObject
# overrides that go with them (gom, gexiv2, ...) are not installed: drop
# those that are missing from the PLIST.

BEGIN {
	PREFIX = ENVIRON["PREFIX"]
	TEST = ENVIRON["TEST"] ? ENVIRON["TEST"] : "test"
}

/^share\/gir-1\.0\/[^\/]*\.gir$/ ||
/^lib\/girepository-1\.0\/[^\/]*\.typelib$/ ||
/^share\/vala\/vapi\/[^\/]*\.(vapi|deps)$/ ||
/^lib\/python[0-9.]*\/site-packages\/gi\/overrides\/[^\/]*\.py$/ {
	if (system(TEST " -f \"" PREFIX "/" $0 "\"") != 0)
		next
}

# An override's compiled forms (Gom.pyc here, or __pycache__ names) go
# with its source: python's PLIST step, later, renames them.
/^lib\/python[0-9.]*\/site-packages\/gi\/overrides\/(__pycache__\/)?[^\/]*\.py[co]$/ {
	src = $0
	sub(/__pycache__\//, "", src)
	sub(/\.cpython-[0-9]*(\.opt-[0-9])?\.py[co]$/, ".py", src)
	sub(/\.py[co]$/, ".py", src)
	if (system(TEST " -f \"" PREFIX "/" src "\"") != 0)
		next
}
