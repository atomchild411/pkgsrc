# $NetBSD: vars.mk,v 1.5 2011/10/28 07:41:52 obache Exp $
#
# This Makefile fragment exposes several Perl configuration variables
# to the package Makefiles.  The variables are only defined if the
# ${PERL5} executable exists.

.include "../../mk/bsd.prefs.mk"

_PERL5_VARS=	INSTALLARCHLIB INSTALLSCRIPT				\
		INSTALLVENDORBIN INSTALLVENDORSCRIPT			\
		INSTALLVENDORARCH INSTALLVENDORLIB			\
		INSTALLVENDORMAN1DIR INSTALLVENDORMAN3DIR

# In a cross build the target's perl cannot run here.  Ask the build
# host's (the same lang/perl5, a tool of every module package) with the
# target's archlib, from the cross destdir, first in @INC: -V reads only
# its Config.pm.
.if ${USE_CROSS_COMPILE:tl} == "yes" && !defined(_PERL5_CROSS_ARCHLIB)
_PERL5_CROSS_ARCHLIB_CMD=	\
	for f in ${_CROSS_DESTDIR}${LOCALBASE}/lib/perl5/[0-9]*/*/Config.pm; do \
		[ -f "$$f" ] && echo "$${f%/Config.pm}" && break;	\
	done; true
_PERL5_CROSS_ARCHLIB:=	${_PERL5_CROSS_ARCHLIB_CMD:sh}
MAKEVARS+=		_PERL5_CROSS_ARCHLIB
.endif

.if (defined(PERL5) && exists(${PERL5:Q})) || !empty(_PERL5_CROSS_ARCHLIB)
#
# Locate some of the installation prefixes for ${PERL5} that are used to
# define later variables.
#
.  if !defined(_PERL5_VARS_OUT)
.    if !empty(_PERL5_CROSS_ARCHLIB)
_PERL5_VARS_CMD=	${TOOLBASE}/bin/perl -I${_PERL5_CROSS_ARCHLIB:Q} \
			-V:prefix ${_PERL5_VARS:tl:S/^/-V:/}
.    else
_PERL5_VARS_CMD=	${PERL5:Q} -V:prefix ${_PERL5_VARS:tl:S/^/-V:/}
.    endif
_PERL5_VARS_OUT:=	${_PERL5_VARS_CMD:sh:ts,:S/'//g:S/;//g:Q:S/,/ /g}
MAKEVARS+=		_PERL5_VARS_OUT
.  endif

.  if !defined(_PERL5_PREFIX)
_PERL5_PREFIX:=		${_PERL5_VARS_OUT:Mprefix=*:C/^prefix=//}
MAKEVARS+=		_PERL5_PREFIX
.  endif
#
# Define PERL5_SUB_* as the vendor variables minus the installation prefix
# define later variables.
#
.  for _var_ in ${_PERL5_VARS}
.    if !defined(PERL5_SUB_${_var_})
PERL5_SUB_${_var_}:=	${_PERL5_VARS_OUT:M${_var_:tl}=*:S/^${_var_:tl}=${_PERL5_PREFIX:=/}//}
.    endif
PERL5_${_var_}?=	${PREFIX}/${PERL5_SUB_${_var_}}
MAKEVARS+=		PERL5_SUB_${_var_}
PLIST_SUBST+=		PERL5_SUB_${_var_}=${PERL5_SUB_${_var_}:Q}
PRINT_PLIST_AWK+=	/^${PERL5_SUB_${_var_}:S|/|\\/|g}/ \
			{ gsub(/${PERL5_SUB_${_var_}:S|/|\\/|g}/, \
			  "$${PERL5_SUB_${_var_}}") }
.  endfor
.endif	# PERL5
