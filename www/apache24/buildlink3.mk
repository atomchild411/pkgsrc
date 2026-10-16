# $NetBSD: buildlink3.mk,v 1.18 2023/11/22 08:05:43 wiz Exp $

BUILDLINK_TREE+=	apache

.if !defined(APACHE_BUILDLINK3_MK)
APACHE_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.apache+=	apache>=2.4.7<2.5
BUILDLINK_ABI_DEPENDS.apache+=	apache>=2.4.58nb1
BUILDLINK_PKGSRCDIR.apache?=	../../www/apache24

BUILDLINK_FILES.apache+=	sbin/apxs
.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == yes
# apxs is a Perl script for the target's perl: run it with the build
# machine's (the target paths it reads are there in a cross build).
# (BUILDLINK_DIR is not set yet here: only the commands may use it.)
APXS?=			${BUILDLINK_DIR}/bin/apxs
buildlink-apache-cookie: buildlink-apache-apxs
.PHONY: buildlink-apache-apxs
buildlink-apache-apxs: buildlink-directories
	${MKDIR} ${BUILDLINK_DIR}/bin
	{ ${ECHO} '#!/bin/sh'; \
	  ${ECHO} '# Apache 2 apxs (STANDARD20): configures grep apxs for that.'; \
	  ${ECHO} 'exec ${TOOLS_PATH.perl} ${BUILDLINK_PREFIX.apache}/bin/apxs "$$@"'; \
	} > ${BUILDLINK_DIR}/bin/apxs
	${CHMOD} +x ${BUILDLINK_DIR}/bin/apxs
.else
${BUILDLINK_DIR}/bin/apxs: buildlink-directories
	${MKDIR} ${BUILDLINK_DIR}/bin && ${LN} -fs ../sbin/apxs ${BUILDLINK_DIR}/bin/apxs
buildlink-apache-cookie: ${BUILDLINK_DIR}/bin/apxs
.endif

USE_TOOLS+=		perl			# for "apxs"
CONFIGURE_ENV+=		APR_LIBTOOL=${LIBTOOL:Q}	# make apxs use the libtool we specify
MAKE_ENV+=		APR_LIBTOOL=${LIBTOOL:Q}
APXS?=			${BUILDLINK_PREFIX.apache}/bin/apxs
.if defined(GNU_CONFIGURE) && ${GNU_CONFIGURE_APXS2:Uyes} == yes
CONFIGURE_ARGS+=	${CONFIGURE_ARGS.apache:U--with-apxs2=${APXS:Q}}
.endif

.include "../../devel/apr/buildlink3.mk"
.include "../../devel/apr-util/buildlink3.mk"
.endif # APACHE_BUILDLINK3_MK

BUILDLINK_TREE+=	-apache
