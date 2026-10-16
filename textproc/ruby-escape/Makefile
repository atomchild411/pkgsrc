# $NetBSD: Makefile,v 1.3 2015/03/15 19:42:34 hiramatsu Exp $
#

DISTNAME=	escape-0.2
CATEGORIES=	textproc
MASTER_SITES=	http://www.a-k-r.org/escape/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.a-k-r.org/escape/
COMMENT=	HTML/URI/shell escaping utilities for Ruby
LICENSE=	modified-bsd

USE_LANGUAGES=		# none
USE_RUBY_INSTALL=	yes
NO_BUILD=		yes

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
