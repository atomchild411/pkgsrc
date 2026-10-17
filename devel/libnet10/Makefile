# $NetBSD: Makefile,v 1.11 2026/08/04 20:28:51 wiz Exp $

DISTNAME=	libnet-1.0.2a
PKGNAME=	${DISTNAME:S/libnet/libnet10/}
PKGREVISION=	3
CATEGORIES=	devel net
#MASTER_SITES=	http://www.packetfactory.net/libnet/dist/deprecated/

MAINTAINER=	pkgsrc-users@NetBSD.org
#HOMEPAGE=	http://www.packetfactory.net/libnet/
COMMENT=	C library for portable packet creation and injection
LICENSE=	2-clause-bsd

WRKSRC=		${WRKDIR}/${DISTNAME:C/l/L/}

USE_LIBTOOL=	yes
GNU_CONFIGURE=	yes
CONFIGURE_ENV+=	LIBNET_CONFIG_CFLAGS="-I${PREFIX}/include/libnet10" \
		LIBNET_CONFIG_LIBS=${LDFLAGS:M*:Q}

SUBST_CLASSES+=		vars
SUBST_STAGE.vars=	pre-configure
SUBST_FILES.vars=	Makefile.in libnet-config.in
SUBST_SED.vars=		-e 's,@MAN_PREFIX@,${PREFIX}/${PKGMANDIR}/man3,g'
SUBST_VARS.vars=	COMPILER_RPATH_FLAG

INSTALLATION_DIRS=	bin lib share/examples ${PKGMANDIR}/man3

post-extract:
	${CHMOD} -R a+r ${WRKSRC}/doc

post-install:
	${CHMOD} ${SHAREMODE} ${DESTDIR}${PREFIX}/include/libnet10/libnet.h
	${CHMOD} ${SHAREMODE} ${DESTDIR}${PREFIX}/include/libnet10/libnet/*.h
	${CHMOD} ${MANMODE} ${DESTDIR}${PREFIX}/${PKGMANDIR}/man3/libnet10.3

# FIXME: replace by proper LDFLAGS handling
_WRAP_EXTRA_ARGS.CC+=	${_RELRO_LDFLAGS}
_WRAP_EXTRA_ARGS.CXX+=	${_RELRO_LDFLAGS}
CWRAPPERS_PREPEND.cc+=	${_RELRO_LDFLAGS}
CWRAPPERS_PREPEND.cxx+=	${_RELRO_LDFLAGS}

.include "../../mk/bsd.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == yes
# configure runs a program for the byte order; answer it.
.  include "../../mk/endian.mk"
.  if ${MACHINE_ENDIAN} == "big"
CONFIGURE_ENV+=		libnet_cv_endianess_result=B
.  else
CONFIGURE_ENV+=		libnet_cv_endianess_result=L
.  endif
# The packet interface is looked up in the build machine's /usr/include.
CONFIGURE_ENV.IRIX+=	libnet_cv_ll_int_type=snoop
# MIPS faults on unaligned access.
CONFIGURE_ENV.IRIX+=	ac_cv_lbl_unaligned_fail=yes
.endif

.include "../../mk/bsd.pkg.mk"
