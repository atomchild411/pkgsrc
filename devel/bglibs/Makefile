# $NetBSD: Makefile,v 1.42 2022/06/28 11:31:40 wiz Exp $
#

DISTNAME=		bglibs-2.04
PKGREVISION=		5
CATEGORIES=		devel
MASTER_SITES=		${HOMEPAGE}

MAINTAINER=		schmonz@NetBSD.org
HOMEPAGE=		https://untroubled.org/bglibs/
COMMENT=		Collection of libraries by Bruce Guenter
LICENSE=		gnu-gpl-v2

USE_TOOLS+=		perl:run gmake
MAKE_ENV+=		PERL5=${TOOLS_PERL5:Q}
INSTALL_ENV+=		install_prefix=${DESTDIR:Q}
USE_LIBTOOL=		yes

DJB_MAKE_TARGETS=	NO
TEST_TARGET=		selftests

DJB_CONFIG_CMDS= \
	${ECHO} ${DJB_CONFIG_PREFIX:Q}/include > conf-include;	\
	${ECHO} ${DJB_CONFIG_PREFIX:Q}/lib > conf-lib;

CFLAGS.SunOS+=		-DSOL_TCP=SOL_SOCKET

.include "../../mk/djbware.mk"

# The sys/try*.c probes declare "main()": implicit int, an error in clang.
CFLAGS+=		-Wno-error=implicit-int

.if ${USE_CROSS_COMPILE:U:tl} == yes
# choose runs some probes, which a cross build cannot: answer them.
.  include "../../mk/endian.mk"
.  if ${MACHINE_ENDIAN} == "big"
MAKE_ENV+=		CHOOSE_endian=1
.  else
MAKE_ENV+=		CHOOSE_endian=0
.  endif
.  if ${OPSYS} == "IRIX"
# n32: 32-bit long; poll; MIPS faults on unaligned access.
MAKE_ENV+=		CHOOSE_ulong32=1 CHOOSE_ulong64=0
MAKE_ENV+=		CHOOSE_poll=1 CHOOSE_unaligned=0
.  endif
.endif

.if ${USE_CROSS_COMPILE:U:tl} == yes
# crc-gentab writes the CRC tables at build time, and bg-installer installs:
# build them for the build machine, in a copy of the sources, and run those.
SUBST_CLASSES+=		crcgentab
SUBST_STAGE.crcgentab=	pre-build
SUBST_MESSAGE.crcgentab=	Running the build machine's crc-gentab.
SUBST_FILES.crcgentab=	Makefile
SUBST_SED.crcgentab=	-e 's|\./crc-gentab |${WRKDIR}/native-crc/crc-gentab |'
SUBST_SED.crcgentab+=	-e 's|\./bg-installer -|${WRKDIR}/native-crc/bg-installer -|'
pre-build: bglibs-native-crc-gentab
.PHONY: bglibs-native-crc-gentab
bglibs-native-crc-gentab:
	${RUN} rm -rf ${WRKDIR}/native-crc
	${RUN} cp -R ${WRKSRC} ${WRKDIR}/native-crc
	${RUN} cd ${WRKDIR}/native-crc && \
	    ${ECHO} ${NATIVE_CC:Q} -O -Wno-error=implicit-int > conf-cc && \
	    ${ECHO} ${NATIVE_CC:Q} > conf-ld && \
	    env PATH=${TOOLBASE}/bin:/usr/bin:/bin PERL5=${TOOLS_PERL5:Q} ${GMAKE} crc-gentab bg-installer
.endif
.include "../../mk/bsd.pkg.mk"
