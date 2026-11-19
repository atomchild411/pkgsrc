#!/bin/sh
#
# $NetBSD$
#
# hollidance-1998: run the 1998 HolliDance (the version of the sgidepot.co.uk
# benchmark table) from ~/.hollidance-1998 (or $HOLLIDANCE_HOME), with links
# to its files in @PREFIX@/lib/hollidance-classic. It prints its frame rate
# ("Frames Per Sec") on standard output.
#
D=@PREFIX@/lib/hollidance-classic
U="${HOLLIDANCE_HOME:-$HOME/.hollidance-1998}"

lnk() {
	if [ -h "$2" ]; then rm -f "$2"; fi
	if [ ! -f "$2" ] && [ ! -d "$2" ]; then ln -s "$1" "$2"; fi
}

mkdir -p "$U" || exit 1
cd "$U" || exit 1
lnk "$D/Holli.dat" Holli.dat
lnk "$D/Club.dat" Club.dat
# NoStrobe keeps the strobe light effect off: strobing light can cause
# seizures in people with epilepsy. It is linked back on every start.
lnk "$D/NoStrobe" NoStrobe

exec "$D/HolliDance" "$@"
