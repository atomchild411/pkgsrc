# $NetBSD$
#
# A cross build cannot run the target's pg_config, which PGXS and many
# PostgreSQL client packages ask for directories and flags. Put a script in
# the buildlink directory instead (mk/pgsql-pg_config.sh) that answers from
# the target's installed PGXS Makefile.global.
#
# Included in cross builds by the postgresqlNN-client buildlink3.mk files,
# which set _PG_CONFIG_PKG to their package name and leave bin/pg_config out
# of their BUILDLINK_FILES.

.if !defined(PGSQL_PG_CONFIG_MK)
PGSQL_PG_CONFIG_MK:=

_PG_CONFIG_PGXS=	${_CROSS_DESTDIR}${BUILDLINK_PREFIX.${_PG_CONFIG_PKG}}/lib/postgresql/pgxs
_PG_CONFIG_SCRIPT=	${BUILDLINK_DIR}/bin/pg_config

BUILDLINK_TARGETS+=	pgsql-pg_config-cross

.PHONY: pgsql-pg_config-cross
pgsql-pg_config-cross:
	${RUN} ${MKDIR} ${_PG_CONFIG_SCRIPT:H}
	${RUN} ${SED} -e 's,@PGXS@,${_PG_CONFIG_PGXS},g'			\
		-e 's,@GMAKE@,${TOOLBASE}/bin/gmake,g'			\
		${PKGSRCDIR}/mk/pgsql-pg_config.sh > ${_PG_CONFIG_SCRIPT}
	${RUN} ${CHMOD} +x ${_PG_CONFIG_SCRIPT}

.endif # PGSQL_PG_CONFIG_MK
