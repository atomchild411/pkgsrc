#!/bin/sh
# $NetBSD$
#
# auto-str for a cross build (mk/djbware.mk), which cannot run the one it
# compiles: the same C string, every byte in octal, declared as the
# package's own auto-str.c (in the build directory) declares it.
#
# usage: djbware-auto-str.sh name value

if grep -q 'puts("const char ")' auto-str.c 2>/dev/null; then
	type="const char"
else
	type="char"
fi
printf '%s %s[] = "\\\n' "$type" "$1"
printf '%s' "$2" | od -An -v -to1 | tr -d '\n' | sed -e 's/^ *//' \
    -e 's/  */\\/g' -e 's/^\(.\)/\\\1/'
printf '\\\n";\n'
