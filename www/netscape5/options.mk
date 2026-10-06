# $NetBSD$

PKG_OPTIONS_VAR=	PKG_OPTIONS.netscape5
PKG_SUPPORTED_OPTIONS=	irix-motif

.include "../../mk/bsd.options.mk"

# The tree's makefiles take neither CPPFLAGS nor LDFLAGS (they link with
# CFLAGS), so include and library directories and the run path go in
# XCFLAGS.

.if !empty(PKG_OPTIONS:Mirix-motif)
# IRIX's own Motif 1.2 (the SGI look, with libSgm) and X instead of
# pkgsrc's, as SGI's Netscape 4 linked them, with OpenSSL and the C++
# runtime linked in: the program needs nothing but IRIX.  This is how the
# IRIX tardist is built.  SGI's headers and link libraries (motif_dev,
# x_dev) come from NETSCAPE_IRIX_X, laid out as /usr/include and
# /usr/lib32.  The roots of trust go with the program: NETSCAPE_CA_FILE.
NETSCAPE_IRIX_X?=	${IRIX_SCRATCH}/irix-x-native
NETSCAPE_CA_FILE?=	/usr/local/lib/netscape5/cacert.pem
MAKE_FLAGS+=	NS_IRIX_MOTIF=1 NS_CA_FILE=${NETSCAPE_CA_FILE:Q}
# The compiler wrappers drop -I/-L outside buildlink unless told otherwise.
BUILDLINK_PASSTHRU_DIRS+=	${NETSCAPE_IRIX_X}
MAKE_FLAGS+=	XCFLAGS=-I${NETSCAPE_IRIX_X}/usr/include\ -L${NETSCAPE_IRIX_X}/usr/lib32\ -L${BUILDLINK_PREFIX.openssl}/lib
.else
# pkgsrc's Motif and X.  Xft.h (from Motif) needs FreeType's headers.
MAKE_FLAGS+=	XCFLAGS=-I${BUILDLINK_PREFIX.freetype2}/include/freetype2\ -L${PREFIX}/lib\ ${COMPILER_RPATH_FLAG}${PREFIX}/lib
# WebP images (libwebp is built shared only: not for the tardist yet)
MAKE_FLAGS+=	NS_WEBP=1
.include "../../graphics/libwebp/buildlink3.mk"
# Today's image libraries for PNG, JPEG and zlib (NS_SYSTEM_IMGLIBS), and
# HTTP/2 by nghttp2 (NS_HTTP2): config/config.mk turns both on without
# irix-motif.
.include "../../graphics/png/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../www/nghttp2/buildlink3.mk"
# Page text by FreeType in Arimo, Tinos and Cousine (cmd/xfe/ftfonts.c),
# with DejaVu for what they lack.
DEPENDS+=	croscorefonts-[0-9]*:../../fonts/croscorefonts
DEPENDS+=	dejavu-ttf-[0-9]*:../../fonts/dejavu-ttf
.include "../../graphics/freetype2/buildlink3.mk"
.include "../../x11/motif/buildlink3.mk"
.include "../../x11/libXt/buildlink3.mk"
.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/libXmu/buildlink3.mk"
.include "../../x11/libX11/buildlink3.mk"
.endif
