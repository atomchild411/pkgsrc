# $NetBSD$
#
# Reads a project's meson_options.txt or meson.options and prints, for a
# cross file's [project options], its introspection, gir and vapi options
# turned off: introspection data cannot be made in a cross build (g-ir-scanner
# runs programs built for the target), and the Vala bindings come from it.

{ buf = buf " " $0 }

END {
	n = split("introspection gir vapi", names, " ")
	for (i = 1; i <= n; i++) {
		if (!match(buf, "option[ \t]*\\([ \t]*['\"]" names[i] "['\"]"))
			continue
		rest = substr(buf, RSTART + RLENGTH)
		if (match(rest, "option[ \t]*\\("))
			rest = substr(rest, 1, RSTART - 1)
		if (rest ~ /type[ \t]*:[ \t]*['"]feature['"]/)
			print names[i] " = 'disabled'"
		else if (rest ~ /type[ \t]*:[ \t]*['"]boolean['"]/)
			print names[i] " = false"
	}
}
