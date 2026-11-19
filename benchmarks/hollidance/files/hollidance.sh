#!/bin/sh
#
# $NetBSD$
#
# hollidance: run HolliDance 1.6 from a directory of your own.
#
# HolliDance reads Models/, Images/ and NoStrobe from the current directory
# and keeps your settings there in HolliDance.ini. This runs it from
# ~/.hollidance (or $HOLLIDANCE_HOME), with links to the shared files in
# @PREFIX@/lib/hollidance.
#
#   hollidance          the standard models, plus Holli's friends and her
#                       new outfit if hollidance-models is installed
#   hollidance -large   the large models from hollidance-models
#
D=@PREFIX@/lib/hollidance
U="${HOLLIDANCE_HOME:-$HOME/.hollidance}"

large=no
case "$1" in
-large)	large=yes; shift ;;
esac

# lnk TARGET NAME: NAME becomes a link to TARGET, unless it is a file or
# directory of your own.
lnk() {
	if [ -h "$2" ]; then rm -f "$2"; fi
	if [ ! -f "$2" ] && [ ! -d "$2" ]; then ln -s "$1" "$2"; fi
}

# kits DIR...: link the model files of these directories into Models/.
kits() {
	for k in "$@"; do
		[ -d "$k" ] || continue
		for f in "$k"/*; do
			case "$f" in
			*/Readme.txt)	continue ;;
			esac
			[ -f "$f" ] || continue
			b=`basename "$f"`
			lnk "$f" "Models/$b"
		done
	done
}

mkdir -p "$U/Models" || exit 1
cd "$U" || exit 1
for f in Images Docs HolliDance.icon; do
	lnk "$D/$f" "$f"
done
# NoStrobe keeps the strobe light effect off: strobing light can cause
# seizures in people with epilepsy. It is linked back on every start.
lnk "$D/NoStrobe" NoStrobe

# Models/: links to the shared models (your own files there are kept).
for f in Models/*; do
	if [ -h "$f" ]; then rm -f "$f"; fi
done
kits "$D/Models" "$D"/models/[!L]*
if [ $large = yes ]; then
	if [ -d "$D/models/LargeModels" ]; then
		kits "$D"/models/Large*
	else
		echo "hollidance: -large needs the hollidance-models package" >&2
	fi
fi

exec "$D/HolliDance" "$@"
