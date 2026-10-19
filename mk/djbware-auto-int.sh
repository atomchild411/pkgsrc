#!/bin/sh
# $NetBSD$
#
# auto-int and auto-int8 for a cross build (mk/djbware.mk), which cannot
# run the ones it compiles: the same declaration, with the value read as
# decimal (auto-int) or octal (auto-int8, given -8) and written in decimal.
#
# usage: djbware-auto-int.sh [-8] name value

src=auto-int.c
if [ "$1" = "-8" ]; then
	src=auto-int8.c
	shift
	value=$(printf '%d' "0$2")
else
	value=$(expr "$2" + 0)
fi
if grep -q 'puts("const int ")' $src 2>/dev/null; then
	type="const int"
else
	type="int"
fi
printf '%s %s = %s;\n' "$type" "$1" "$value"
