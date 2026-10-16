#!/bin/sh
# $NetBSD$
#
# ./install for a cross build (mk/djbware.mk), which cannot run the one it
# compiles: hier.c's h(), d() and c() calls, as shell, run in the build
# directory. auto_home is conf-destdir's value where there is one (as the
# install program links it), else conf-home's; any other auto_NAME is
# conf-NAME's. Owners are left alone, as an unprivileged ./install leaves
# them. Any other call in hier.c stops it.

set -e
val() {
	case $1 in
	auto_home)
		if [ -f conf-destdir ]; then head -1 conf-destdir
		else head -1 conf-home; fi ;;
	auto_*)	head -1 "conf-${1#auto_}" ;;
	*)	echo "$1" ;;
	esac
}

awk '/^[ \t]*[a-z][a-z]*\(/ && !/^[ \t]*(void|int|char)/ {
	line = $0
	sub(/^[ \t]*/, "", line); sub(/\);.*$/, "", line)
	op = substr(line, 1, index(line, "(") - 1)
	args = substr(line, index(line, "(") + 1)
	gsub(/"/, "", args); gsub(/[ \t]/, "", args)
	print op, args
}' hier.c | while read op args; do
	oldifs=$IFS; IFS=,; set -- $args; IFS=$oldifs
	case $op in
	h)	home=$(val "$1"); mkdir -p "$home"; chmod "$4" "$home" ;;
	d)	home=$(val "$1"); mkdir -p "$home/$2"; chmod "$5" "$home/$2" ;;
	c)	home=$(val "$1"); cp "$3" "$home/$2/$3"; chmod "$6" "$home/$2/$3" ;;
	*)	echo "djbware-install.sh: hier.c calls $op(), which it does not know" >&2
		exit 1 ;;
	esac
done
