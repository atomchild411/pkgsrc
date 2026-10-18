# $NetBSD: Makefile,v 1.69 2026/09/02 19:04:16 wiz Exp $

CONFIGURE_ENV+=		INKSCAPE=/bin/false
CONFIGURE_ARGS+=	--disable-python
CONFIGURE_ARGS+=	--disable-php5
CONFIGURE_ARGS+=	--disable-php7
CONFIGURE_ARGS+=	--disable-perl
.include "../../mk/bsd.prefs.mk"
PLIST_VARS+=		gtkdocgen
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# gtkdoc-scangobj runs a program built for the target: install the HTML
# the release tarball has (less two indexes gtk-doc makes).
CONFIGURE_ARGS+=	--disable-gtk-doc
INSTALLATION_DIRS+=	share/gtk-doc/html/lasso
post-install:
	${INSTALL_DATA} ${WRKSRC}/docs/reference/lasso/html/* \
	    ${DESTDIR}${PREFIX}/share/gtk-doc/html/lasso
.else
CONFIGURE_ARGS+=	--enable-gtk-doc
PLIST.gtkdocgen=	yes
.endif

EXTRACT_USING=		bsdtar

BUILDLINK_API_DEPENDS.gtk-doc+=	gtk-doc>=1.32nb9
PKGREVISION= 3
.include "../../textproc/gtk-doc/buildlink3.mk"
.include "../../security/lasso/Makefile.common"
.include "../../mk/bsd.pkg.mk"
