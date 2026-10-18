# $NetBSD: module.mk,v 1.6 2023/06/06 12:41:41 riastradh Exp $
#
# Simple Erlang module package framework
#

PKGNAME?=	erlang-${DISTNAME}

.if defined(REBAR3_BUILD)
TOOL_DEPENDS+=	rebar3-[0-9]*:../../devel/rebar3
REBAR=		${TOOLBASE}/bin/rebar3
.else
TOOL_DEPENDS+=	rebar-[0-9]*:../../devel/rebar
.endif

USE_TOOLS+=	gmake pax

.include "../../mk/bsd.prefs.mk"
REBAR?=		${TOOLBASE}/bin/rebar
MAKE_FLAGS+=	REBAR=${REBAR}

# Used by some Erlang packages to use system deps
MAKE_ENV+=	USE_GLOBAL_DEPS=true

.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# The build machine's erl runs rebar: let it find the Erlang packages
# installed for the target (the "system deps"; not the target's OTP
# applications, whose NIFs it cannot load), and compile NIFs against the
# target's erts and ei (erl_int_sizes_config.h is the target's).
_ERL_CROSS_LIBS=	${WRKDIR}/.erl_libs
MAKE_ENV+=	ERL_LIBS=${_ERL_CROSS_LIBS}
MAKE_ENV+=	ERL_CFLAGS="-I${PREFIX}/lib/erlang/usr/include"
# rebar.config port_env often names the erl_interface of the erl running
# rebar: map the build machine's Erlang tree to the target's (same release).
BUILDLINK_TRANSFORM+=	I:${TOOLBASE}/lib/erlang:${BUILDLINK_DIR}/lib/erlang
BUILDLINK_TRANSFORM+=	L:${TOOLBASE}/lib/erlang:${BUILDLINK_DIR}/lib/erlang
pre-configure: erlang-cross-libs
.PHONY: erlang-cross-libs
erlang-cross-libs:
	${RUN}${MKDIR} ${_ERL_CROSS_LIBS};					\
	for d in ${CROSS_DESTDIR}${PREFIX}/lib/erlang/lib/*; do		\
		[ -d "$$d" ] || continue;					\
		[ -d ${TOOLBASE}/lib/erlang/lib/$${d##*/} ] ||		\
		    ${LN} -sf "$$d" ${_ERL_CROSS_LIBS}/;			\
	done
.endif

ERL_MOD_NAME?=		${DISTNAME:C/-.*//}
ERL_MOD_DIR?=		lib/erlang/lib/${ERL_MOD_NAME}-${PKGVERSION_NOREV}
INSTALLATION_DIRS+=	${ERL_MOD_DIR}

do-install:
	cd ${WRKSRC} && ${FIND} . \( \
		-name bin -o -name ebin -o -name include -o -name priv \) \
		-exec ${PAX} -rw -pp "{}" ${DESTDIR}${PREFIX}/${ERL_MOD_DIR} ";"

.include "../../lang/erlang/buildlink3.mk"
