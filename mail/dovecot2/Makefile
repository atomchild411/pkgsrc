# $NetBSD: Makefile,v 1.112 2024/08/19 09:29:56 adam Exp $

.include "../../mail/dovecot2/Makefile.common"

RCD_SCRIPTS=		dovecot
SMF_NAME=		dovecot

DOVECOT_USER?=		dovecot
DOVECOT_GROUP?=		dovecot
DOVENULL_USER?=		dovenull
DOVENULL_GROUP?=	dovenull
PKG_GROUPS=		${DOVECOT_GROUP} ${DOVENULL_GROUP}
PKG_USERS=		${DOVECOT_USER}:${DOVECOT_GROUP}	\
			${DOVENULL_USER}:${DOVENULL_GROUP}
PKG_GROUPS_VARS=	DOVECOT_GROUP DOVENULL_GROUP
PKG_USERS_VARS=		DOVECOT_USER DOVENULL_USER

PKG_GECOS.${DOVECOT_USER}=	Dovecot IMAP/POP3 user
PKG_GECOS.${DOVENULL_USER}=	Dovecot login user

EGDIR=			${PREFIX}/share/examples/dovecot

CNFS_cmd=		${SED} -ne "s,^share/examples/dovecot/,,p" PLIST
CNFS=			${CNFS_cmd:sh}
CONF_FILES=		${EGDIR}/dovecot.conf ${PKG_SYSCONFDIR}/dovecot/dovecot.conf
.for file in ${CNFS}
CONF_FILES+=		${EGDIR}/${file:Q} ${PKG_SYSCONFDIR}/dovecot/${file:Q}
.endfor

INSTALLATION_DIRS+=	libexec/dovecot sbin share/doc/dovecot
INSTALLATION_DIRS+=	share/examples/dovecot share/examples/dovecot/conf.d
OWN_DIRS=		${PKG_SYSCONFDIR}/dovecot/
OWN_DIRS+=		${PKG_SYSCONFDIR}/dovecot/conf.d

# configure's run tests stop a cross build; IRIX's answers. time_t is a
# signed 32-bit long; no epoll or posix_fallocate; fd passing (SCM_RIGHTS)
# and coherent mmap/write; C99 vsnprintf through clang's IRIX runtime;
# va_list is a pointer (n32), so it copies by value.
CONFIGURE_ENV.IRIX+=	i_cv_epoll_works=no
CONFIGURE_ENV.IRIX+=	i_cv_posix_fallocate_works=no
CONFIGURE_ENV.IRIX+=	i_cv_gmtime_max_time_t=31
CONFIGURE_ENV.IRIX+=	i_cv_mmap_plays_with_write=yes
CONFIGURE_ENV.IRIX+=	i_cv_fd_passing=yes
CONFIGURE_ENV.IRIX+=	i_cv_c99_vsnprintf=yes
CONFIGURE_ENV.IRIX+=	lib_cv_va_copy=yes
CONFIGURE_ENV.IRIX+=	lib_cv___va_copy=yes
CONFIGURE_ENV.IRIX+=	lib_cv_va_val_copy=yes
# IRIX's quotactl() and <sys/quota.h> are not Linux's, which quota-fs.c
# then assumes; build the quota plugin without the fs backend.
CONFIGURE_ENV.IRIX+=	ac_cv_func_quotactl=no

REPLACE_BASH+=		src/util/dovecot-sysreport
REPLACE_BASH+=		src/util/health-check.sh

.PHONY: enable-manz-by-replacing-roff-includes-with-symlinks
enable-manz-by-replacing-roff-includes-with-symlinks:
	cd ${DESTDIR}${PREFIX}/${PKGMANDIR} && \
	for i in $$(${GREP} -lr ^\\.so .); do \
		j=$$(${SED} -e 's|^\.so |../|' < $${i}); \
		${RM} -f $${i} && ${LN} -s $${j} $${i}; \
	done

post-install: enable-manz-by-replacing-roff-includes-with-symlinks
	${INSTALL_DATA} ${WRKSRC}/doc/dovecot-openssl.cnf ${DESTDIR}${EGDIR}
	${INSTALL_SCRIPT} ${WRKSRC}/doc/mkcert.sh ${DESTDIR}${EGDIR}

.include "../../mk/bsd.pkg.mk"
