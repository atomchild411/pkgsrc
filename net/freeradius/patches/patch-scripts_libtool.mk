$NetBSD$

Build jlibtool, which runs at build time, with JLIBTOOL_CC (default CC):
cross builds pass the native compiler.

--- scripts/libtool.mk.orig
+++ scripts/libtool.mk
@@ -30,6 +30,8 @@
 endif
 
 JLIBTOOL := ${BUILD_DIR}/make/jlibtool
+# jlibtool runs at build time: build it for the build machine.
+JLIBTOOL_CC ?= ${CC}
 
 # Add a rule to build jlibtool BEFORE any other targets.  This
 # means that we can use it to build the later targets.
@@ -41,7 +43,7 @@
 ${JLIBTOOL}: ${top_makedir}/jlibtool.c
 	$(Q)mkdir -p $(dir $@)
 	$(Q)echo CC jlibtool.c
-	$(Q)${CC} $< -o $@ ${JLIBTOOL_DEFS}
+	$(Q)${JLIBTOOL_CC} $< -o $@ ${JLIBTOOL_DEFS}
 
 clean: jlibtool_clean
 
