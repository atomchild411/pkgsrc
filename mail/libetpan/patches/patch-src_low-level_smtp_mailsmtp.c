$NetBSD$

IRIX has no sa_len either.

--- src/low-level/smtp/mailsmtp.c.orig
+++ src/low-level/smtp/mailsmtp.c
@@ -276,7 +276,7 @@
     if (r != 0)
       return MAILSMTP_ERROR_HOSTNAME;
 
-#if (defined __linux__ || defined WIN32 || defined __sun)
+#if (defined __linux__ || defined WIN32 || defined __sun || defined __sgi)
     r = getnameinfo(&addr, sizeof(addr), hostname, HOSTNAME_SIZE, NULL, 0, NI_NUMERICHOST);
 #else
     r = getnameinfo(&addr, addr.sa_len, hostname, HOSTNAME_SIZE, NULL, 0, NI_NUMERICHOST);
