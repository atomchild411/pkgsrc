# $NetBSD: builtin.mk,v 1.25 2025/03/07 07:00:33 wiz Exp $

BUILTIN_PKG:=	MesaLib

# IRIX: GL is always IRIX's own libGL.so (with libGLcore.so): hardware
# OpenGL on accelerated boards, SGI's software OpenGL on REX3. Mesa is not
# built for it.
.if ${OPSYS} == "IRIX"
IS_BUILTIN.MesaLib=	yes
BUILTIN_PKG.MesaLib=	MesaLib-1.2
USE_BUILTIN.MesaLib=	yes
BUILDLINK_PREFIX.MesaLib=	/usr
.endif

BUILTIN_FIND_FILES_VAR:=	H_MESALIB PC_GL
BUILTIN_FIND_FILES.H_MESALIB=	${X11BASE}/include/GL/glx.h
BUILTIN_FIND_FILES.PC_GL=	${X11BASE}/lib/pkgconfig/gl.pc
BUILTIN_FIND_FILES.PC_GL+=	${X11BASE}/lib${LIBABISUFFIX}/pkgconfig/gl.pc

.include "../../mk/buildlink3/bsd.builtin.mk"

###
### Determine if there is a built-in implementation of the package and
### set IS_BUILTIN.<pkg> appropriately ("yes" or "no").
###
.if !defined(IS_BUILTIN.MesaLib)
.  if empty(PC_GL:M__nonexistent__)
IS_BUILTIN.MesaLib=	yes
.  elif empty(H_MESALIB:M__nonexistent__)
IS_BUILTIN.MesaLib=	yes
.  else
IS_BUILTIN.MesaLib=	no
.  endif
.endif

MAKEVARS+=	IS_BUILTIN.MesaLib

###
### If there is a built-in implementation, then set BUILTIN_PKG.<pkg> to
### a package name to represent the built-in package.
###
.if !defined(BUILTIN_PKG.MesaLib) && \
    ${IS_BUILTIN.MesaLib:tl} == yes
.  if empty(PC_GL:M__nonexistent__)
BUILTIN_VERSION.Mesa!= \
	${SED} -n -e 's/Version: //p' ${_CROSS_DESTDIR:U:Q}${PC_GL:Q}
.  elif empty(H_MESALIB:M__nonexistent__)
.    include "version.mk"
.  else # ?
BUILTIN_VERSION.Mesa:= 0.something-weird-happened
.  endif
BUILTIN_PKG.MesaLib=	MesaLib-${BUILTIN_VERSION.Mesa}
MAKEVARS+=	BUILTIN_VERSION.Mesa
.endif
MAKEVARS+=	BUILTIN_PKG.MesaLib

###
### Determine whether we should use the built-in implementation if it
### exists, and set USE_BUILTIN.<pkg> appropriate ("yes" or "no").
###
.if !defined(USE_BUILTIN.MesaLib)
.  if ${PREFER.MesaLib} == "pkgsrc"
USE_BUILTIN.MesaLib=	no
.  else
USE_BUILTIN.MesaLib=	${IS_BUILTIN.MesaLib}
.    if defined(BUILTIN_PKG.MesaLib) && \
        ${IS_BUILTIN.MesaLib:tl} == yes
USE_BUILTIN.MesaLib=	yes
.      for dep in ${BUILDLINK_API_DEPENDS.MesaLib}
.        if ${USE_BUILTIN.MesaLib:tl} == yes
USE_BUILTIN.MesaLib!=							\
	if ${PKG_ADMIN} pmatch ${dep:Q} ${BUILTIN_PKG.MesaLib}; then \
		${ECHO} yes;						\
	else								\
		${ECHO} no;						\
	fi
.        endif
.      endfor
.    endif
.  endif  # PREFER.MesaLib
.endif

MAKEVARS+=	USE_BUILTIN.MesaLib

###
### The section below only applies if we are not including this file
### solely to determine whether a built-in implementation exists.
###
CHECK_BUILTIN.MesaLib?=	no
.if ${CHECK_BUILTIN.MesaLib:tl} == no

.  if ${USE_BUILTIN.MesaLib:tl} == no
.    include "../../mk/pthread.buildlink3.mk"
.    include "../../mk/pthread.builtin.mk"
BUILTIN_PKG:=	MesaLib
.  endif

.  if ${OPSYS} != "IRIX"
.    include "../../mk/x11.builtin.mk"
.  else
# IRIX's GL has no pkg-config file: write one for the build.
BUILDLINK_TARGETS+=	irix-gl-pc
.    if !defined(HAS_IRIX_GL_PC)
HAS_IRIX_GL_PC=
.PHONY: irix-gl-pc
irix-gl-pc:
	${RUN}${MKDIR} ${BUILDLINK_DIR}/lib/pkgconfig;			\
	{ ${ECHO} 'prefix=/usr';						\
	  ${ECHO} 'includedir=$${prefix}/include';				\
	  ${ECHO};								\
	  ${ECHO} 'Name: gl';						\
	  ${ECHO} 'Description: IRIX OpenGL';					\
	  ${ECHO} 'Version: 1.2';						\
	  ${ECHO} 'Libs: -lGL';						\
	  ${ECHO} 'Cflags:';							\
	} > ${BUILDLINK_DIR}/lib/pkgconfig/gl.pc
.    endif
.  endif

.endif	# CHECK_BUILTIN.MesaLib
