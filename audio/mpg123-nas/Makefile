# $NetBSD: Makefile,v 1.29 2021/04/17 09:20:47 nia Exp $

MPG123_MODULE=	nas

.include "../../audio/mpg123/Makefile.common"

# IRIX: no audio/nas there (it would shadow IRIX's libaudio).
NOT_FOR_PLATFORM+=	IRIX-*-*

.include "../../audio/mpg123/buildlink3.mk"
.include "../../audio/nas/buildlink3.mk"
.include "../../x11/libXt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
