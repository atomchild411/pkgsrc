$NetBSD$

IRIX declares inet_aton() only in SGI mode, which _XOPEN_SOURCE=500 leaves: inet_addr().

--- Net/src/IPAddressImpl.cpp.orig
+++ Net/src/IPAddressImpl.cpp
@@ -270,7 +270,7 @@
 	else
 		return IPv4AddressImpl(&ia);
 #else
-#if __GNUC__ < 3 || defined(POCO_VXWORKS)
+#if __GNUC__ < 3 || defined(POCO_VXWORKS) || defined(__sgi)
 	struct in_addr ia;
 	ia.s_addr = inet_addr(const_cast<char*>(addr.c_str()));
 	if (ia.s_addr == INADDR_NONE && addr != "255.255.255.255")
