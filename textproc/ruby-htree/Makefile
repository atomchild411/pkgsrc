# $NetBSD: Makefile,v 1.12 2015/03/15 19:31:45 hiramatsu Exp $

DISTNAME=	htree-0.8
CATEGORIES=	textproc ruby
MASTER_SITES=	http://www.a-k-r.org/htree/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.a-k-r.org/htree/
COMMENT=	Tree data structure which represent HTML and XML data for Ruby
LICENSE=	ruby-license

NO_BUILD=		yes
USE_RUBY_INSTALL=	yes

INSTALL_TARGET=		--destdir=${DESTDIR}

do-test:
	${RUN} cd ${WRKSRC}; ${SETENV} ${TEST_ENV} ${RUBY} -I. test-all.rb

# install.rb looks for vendor_ruby on the running ruby's load path, which
# cross-compiling is the build host's: take RbConfig's vendorlibdir, the
# target's then (lang/ruby/modules.mk) and the same directory otherwise.
SUBST_CLASSES+=		vendordir
SUBST_STAGE.vendordir=	pre-install
SUBST_MESSAGE.vendordir=	Taking the install directory from RbConfig.
SUBST_FILES.vendordir=	install.rb
SUBST_SED.vendordir=	-e 's|^def target_directory$$|def target_directory; require "rbconfig"; return RbConfig::CONFIG["vendorlibdir"]|'

.include "../../lang/ruby/modules.mk"
.include "../../mk/bsd.pkg.mk"
