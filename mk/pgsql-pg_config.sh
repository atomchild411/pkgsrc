#!/bin/sh
# $NetBSD$
#
# pg_config for a cross build (mk/pgsql-pg_config.mk): the target's own
# cannot run here. Answers from the target's installed PGXS Makefile.global,
# evaluated with the build host's GNU make, as the real one would from the
# values compiled into it. --pgxs names the copy in the cross destdir.

pgxs=@PGXS@

# Without the calling make's MAKEFLAGS: PGXS=1 there would take
# Makefile.global's PGXS branch, which runs pg_config -- this script again.
v() {
	env -u MAKEFLAGS -u MFLAGS -u MAKELEVEL -u MAKEOVERRIDES -u PGXS \
	    -u USE_PGXS @GMAKE@ -s --no-print-directory -f - PGXS= USE_PGXS= \
	    top_builddir="$pgxs" top_srcdir="$pgxs" pg_config_cross <<EOT
include $pgxs/src/Makefile.global
pg_config_cross: ; @echo \$($1)
EOT
}

one() {
	case $1 in
	--bindir)		v bindir ;;
	--docdir)		v docdir ;;
	--htmldir)		v htmldir ;;
	--includedir)		v includedir ;;
	--pkgincludedir)	v pkgincludedir ;;
	--includedir-server)	v includedir_server ;;
	--libdir)		v libdir ;;
	--pkglibdir)		v pkglibdir ;;
	--localedir)		v localedir ;;
	--mandir)		v mandir ;;
	--sharedir)		v datadir ;;
	--sysconfdir)		v sysconfdir ;;
	--pgxs)			echo "$pgxs/src/makefiles/pgxs.mk" ;;
	--configure)		v configure_args ;;
	--cc)			v CC ;;
	--cppflags)		v CPPFLAGS ;;
	--cflags)		v CFLAGS ;;
	--cflags_sl)		v CFLAGS_SL ;;
	--ldflags)		v LDFLAGS ;;
	--ldflags_ex)		v LDFLAGS_EX ;;
	--ldflags_sl)		v LDFLAGS_SL ;;
	--libs)			v LIBS ;;
	--version)		echo "PostgreSQL $(v VERSION)" ;;
	*)	echo "pg_config: invalid argument: $1" >&2; exit 1 ;;
	esac
}

if [ $# -eq 0 ]; then
	for o in bindir docdir htmldir includedir pkgincludedir \
	    includedir-server libdir pkglibdir localedir mandir sharedir \
	    sysconfdir pgxs configure cc cppflags cflags cflags_sl ldflags \
	    ldflags_ex ldflags_sl libs version; do
		u=$(echo "$o" | tr a-z- A-Z_)
		echo "$u = $(one --$o)"
	done
	exit 0
fi
for a in "$@"; do
	one "$a" || exit 1
done
