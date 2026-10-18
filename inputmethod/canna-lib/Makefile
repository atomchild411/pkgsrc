# $NetBSD: Makefile,v 1.20 2026/08/04 20:29:02 wiz Exp $

CANNA_MODULE=	lib

.include "../../inputmethod/canna/Makefile.common"

# (1) Change SUBDIRS.
# (2) Don't install `forcpp', `kpdic'.
#
post-patch:
	@${MV} ${WRKSRC}/Imakefile ${WRKSRC}/Imakefile.orig
	@${SED}	-e 's|\(SUBDIRS = lib canna\).*\( misc\)|\1 cmd/forcpp cmd/kpdic dic/phono\2|' \
		-e 's|\(SGSDIR = \).*|\1 lib canna dic/phono misc doc|'	\
		${WRKSRC}/Imakefile.orig > ${WRKSRC}/Imakefile

MAKE_ENV+=	AWK=${AWK:Q}

.include "../../mk/bsd.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# dic/phono runs forcpp and kpdic, built for the target: build them for the
# build host as well (kpdic writes its numbers big-endian either way).
MAKE_FLAGS+=	FORCPP=${WRKDIR}/host-forcpp KPDIC=${WRKDIR}/host-kpdic
pre-build: canna-host-tools
.PHONY: canna-host-tools
canna-host-tools:
.  for t in forcpp kpdic
	${NATIVE_CC} -I${WRKSRC}/include -I${WRKSRC} -I${WRKSRC}/canna \
	    -I${WRKSRC}/lib -o ${WRKDIR}/host-${t} ${WRKSRC}/cmd/${t}/${t}.c
.  endfor
.endif

post-extract:
	${CP} ${FILESDIR}/dic-phono-filter.awk ${WRKSRC}/dic/phono/

post-configure:
	# prepare necessary symlinks to build without configure in server dir
	@${LN} -s ${WRKSRC}/server/*.h ${WRKSRC}/include

post-install:
	${RM} ${DESTDIR}${PREFIX}/bin/forcpp ${DESTDIR}${PREFIX}/bin/kpdic
.if ${OPSYS} == "IRIX"
# IRIX's imake rules make no major-version link.
.  for l in RKC RKC16 canna canna16
	${LN} -sf lib${l}.so.1.2 ${DESTDIR}${PREFIX}/lib/lib${l}.so.1
.  endfor
.endif

# FIXME: replace by proper LDFLAGS handling
_WRAP_EXTRA_ARGS.CC+=	${_RELRO_LDFLAGS}
_WRAP_EXTRA_ARGS.CXX+=	${_RELRO_LDFLAGS}
CWRAPPERS_PREPEND.cc+=	${_RELRO_LDFLAGS}
CWRAPPERS_PREPEND.cxx+=	${_RELRO_LDFLAGS}

.include "../../mk/bsd.pkg.mk"
