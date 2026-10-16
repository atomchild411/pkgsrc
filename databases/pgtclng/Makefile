# $NetBSD: Makefile,v 1.19 2026/08/04 20:28:49 wiz Exp $
#

VER=		1.5.3
DISTNAME=	pgtcl${VER}
PKGNAME=	pgtclng-${VER}
PKGREVISION=	8
CATEGORIES=	databases tcl
MASTER_SITES=	http://pgfoundry.org/frs/download.php/1075/

MAINTAINER=	pkgsrc-users@NetBSD.org
#HOMEPAGE=	http://pgtclng.projects.postgresql.org/
COMMENT=	Next Generation TCL interface to PostgreSQL

CONFLICTS+=	pgtcl-[0-9]*

USE_PKGLOCALEDIR=	yes
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--with-postgres-include=${PREFIX}/include
CONFIGURE_ARGS+=	--with-postgres-lib=${PREFIX}/lib
CPPFLAGS+=		-DUSE_INTERP_ERRORLINE
.include "../../mk/bsd.prefs.mk"
# TEA's tcl.m4 drops the dots from the library's version on the BSDs only.
.if ${OPSYS} == "IRIX"
PGTCLLIBNAME=		libpgtcl${VER}.so
.else
PGTCLLIBNAME=		libpgtcl${VER:C/\.//g}.so
.endif
PLIST_SUBST+=		PGTCLLIBNAME=${PGTCLLIBNAME}

post-install:
	cd ${DESTDIR}${PREFIX}/lib && ln -s pgtcl${VER}/${PGTCLLIBNAME} libpgtcl.so

# FIXME: replace by proper LDFLAGS handling
_WRAP_EXTRA_ARGS.CC+=	${_RELRO_LDFLAGS}
_WRAP_EXTRA_ARGS.CXX+=	${_RELRO_LDFLAGS}
CWRAPPERS_PREPEND.cc+=	${_RELRO_LDFLAGS}
CWRAPPERS_PREPEND.cxx+=	${_RELRO_LDFLAGS}

.include "../../lang/tcl/buildlink3.mk"
.include "../../mk/pgsql.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
