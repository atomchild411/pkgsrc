#!/bin/sh
# $NetBSD$
#
# Build runtime/grammars/*.so as `hx --grammar build` does
# (helix-loader/src/grammar.rs), for cross builds, where hx cannot run.
# Run in WRKSRC with CC, CXX, CFLAGS and CXXFLAGS set.

set -e
out=runtime/grammars

# Grammar names and subpaths from languages.toml, less use-grammars' except.
awk '
/^use-grammars *=/ {
	s = $0; sub(/.*except *= *\[/, "", s); sub(/\].*/, "", s)
	n = split(s, a, ",")
	for (i = 1; i <= n; i++) { gsub(/[ "]/, "", a[i]); skip[a[i]] = 1 }
}
function flush() { if (name != "" && !(name in skip)) print name, sp; name = ""; sp = "" }
/^\[\[grammar\]\]/ { flush(); g = 1; next }
/^\[/ { flush(); g = 0; next }
g && /^name *=/ { s = $0; sub(/^name *= *"/, "", s); sub(/".*/, "", s); name = s }
g && /subpath *=/ { s = $0; sub(/.*subpath *= *"/, "", s); sub(/".*/, "", s); sp = s }
END { flush() }
' languages.toml |
while read name sp; do
	src=$out/sources/$name${sp:+/$sp}/src
	lib=$out/$name.so
	if [ -f $src/scanner.c ]; then
		${CC} ${CFLAGS} -fPIC -shared -fno-exceptions -I $src -o $lib \
		    -xc -std=c11 $src/scanner.c $src/parser.c
	elif [ -f $src/scanner.cc ]; then
		${CXX} ${CXXFLAGS} -fPIC -fno-exceptions -I $src \
		    -o $out/${name}_scanner.o -std=c++14 -c $src/scanner.cc
		${CXX} ${CFLAGS} -fPIC -shared -fno-exceptions -I $src -o $lib \
		    $out/${name}_scanner.o -xc $src/parser.c
		rm -f $out/${name}_scanner.o
	else
		${CC} ${CFLAGS} -fPIC -shared -fno-exceptions -I $src -o $lib \
		    $src/parser.c
	fi
done
