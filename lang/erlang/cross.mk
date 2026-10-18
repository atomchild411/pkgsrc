# $NetBSD$
#
# Cross builds of Erlang packages, included by module.mk (and by packages
# that run rebar themselves, like ejabberd).
#
# The build machine's erl runs rebar: let it find the Erlang packages
# installed for the target, the "system deps" (ERL_LIBS: links to those of
# the target's applications the build machine's Erlang does not have, so not
# the target's OTP with its NIFs); compile NIFs against the target's erts
# headers (ERL_CFLAGS; erl_int_sizes_config.h is the target's); and map the
# build machine's Erlang tree, which rebar.config port_env often names for
# erl_interface, to the target's of the same release.

.include "../../mk/bsd.fast.prefs.mk"

.if ${USE_CROSS_COMPILE:U:tl} == "yes" && !defined(ERLANG_CROSS_MK)
ERLANG_CROSS_MK=	# defined

_ERL_CROSS_LIBS=	${WRKDIR}/.erl_libs
CONFIGURE_ENV+=		ERL_LIBS=${_ERL_CROSS_LIBS}
MAKE_ENV+=		ERL_LIBS=${_ERL_CROSS_LIBS}
MAKE_ENV+=		ERL_CFLAGS="-I${PREFIX}/lib/erlang/usr/include"
BUILDLINK_TRANSFORM+=	I:${TOOLBASE}/lib/erlang:${BUILDLINK_DIR}/lib/erlang
BUILDLINK_TRANSFORM+=	L:${TOOLBASE}/lib/erlang:${BUILDLINK_DIR}/lib/erlang

pre-configure: erlang-cross-libs
.PHONY: erlang-cross-libs
erlang-cross-libs:
	${RUN}${MKDIR} ${_ERL_CROSS_LIBS};				\
	for d in ${CROSS_DESTDIR}${PREFIX}/lib/erlang/lib/*; do		\
		[ -d "$$d" ] || continue;				\
		[ -d ${TOOLBASE}/lib/erlang/lib/$${d##*/} ] ||		\
		    ${LN} -sf "$$d" ${_ERL_CROSS_LIBS}/;		\
	done
.endif
