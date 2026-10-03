# $NetBSD$
#
# Cross builds of Samba's waf projects (talloc, tdb, tevent, ldb, samba):
# waf cannot run the programs its checks build, so it reads their results
# from a file of answers, one for each target system (files/), which it
# also writes the questions it has no answer for into (as UNKNOWN).

.include "../../mk/bsd.fast.prefs.mk"

.if ${USE_CROSS_COMPILE:U:tl} == "yes"
WAF_CROSS_ANSWERS=	${WRKSRC}/bin/cross-answers.txt
CONFIGURE_ARGS+=	--cross-compile --cross-answers=${WAF_CROSS_ANSWERS}

pre-configure: waf-cross-answers
.PHONY: waf-cross-answers
waf-cross-answers:
	${RUN}${MKDIR} ${WRKSRC}/bin
	${RUN}${CP} ${.CURDIR}/../../devel/talloc/files/waf-cross-answers.${OPSYS} \
		${WAF_CROSS_ANSWERS}
.endif
