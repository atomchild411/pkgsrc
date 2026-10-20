# $NetBSD$
#
# For packages whose build runs programs it has just built for the target
# (table generators, dictionary compilers, self-hosting languages,
# introspection dumpers), which a cross build cannot otherwise do.
#
# In the IRIX cross build, xbulk's irix-exec bridge (a binfmt_misc entry on
# the build host, bin/irix-exec in the overlay) runs such programs on an
# emulated IRIX machine (IRIS) that sees the build's work directory. It
# acts only for packages that include this file; elsewhere, and on other
# systems, this file does nothing.
#
# Consequence: GNU configure scripts find that they can run what they
# compile, and run their tests on the target, as in a native build
# (correct answers, but slow under emulation).
#
# Keywords: cross emulator irix-exec

.if !defined(IRIX_EXEC_BRIDGE_MK)
IRIX_EXEC_BRIDGE_MK=	defined

.include "../../mk/bsd.fast.prefs.mk"

.if ${OPSYS} == "IRIX" && ${USE_CROSS_COMPILE:U:tl} == "yes"
CONFIGURE_ENV+=		IRIX_EXEC_BRIDGE=yes
MAKE_ENV+=		IRIX_EXEC_BRIDGE=yes
INSTALL_ENV+=		IRIX_EXEC_BRIDGE=yes
.endif

.endif	# IRIX_EXEC_BRIDGE_MK
