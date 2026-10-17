#!/bin/sh
# $NetBSD$
#
# CONFIG_RMTCALL for cross builds for IRIX: the schilytools build runs its
# inc/ probes (align_test, avoffset) to write align.h and avoffset.h, and when
# one cannot run here it runs it again through this. Print what the probe
# prints on IRIX: its output from a native run on IRIX 6.5.22 with the same
# toolchain (clang 21, n32), kept beside this script.
d=`dirname "$0"`
case `basename "$1"` in
align_test*)	exec cat "$d/irix-align.h" ;;
avoffset*)	exec cat "$d/irix-avoffset.h" ;;
*)		echo "irix-rmtcall.sh: no IRIX answer for $1" >&2; exit 1 ;;
esac
