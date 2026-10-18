$NetBSD$

IRIX: no sin_len either.
IRIX: no sin_len or sa_len, fixed-size ifreqs: as on Solaris.

--- rootprobe.c.orig
+++ rootprobe.c
@@ -80,7 +80,7 @@
 #include <arpa/nameser_compat.h>
 #endif
 
-#if defined(__linux__) || defined(__sun__) || defined(__CYGWIN__)
+#if defined(__linux__) || defined(__sun__) || defined(__CYGWIN__) || defined(__sgi)
 #include <sys/time.h>
 #define	FD_COPY(f, t)	bcopy(f, t, sizeof(*(f)))
 #endif
@@ -258,7 +258,7 @@
 	for (i = 0; i < nservers; i++) {
 		sp = &servers[i];
 		sp->dst.sin_family = AF_INET;
-#if !defined(__linux__) && !defined(__sun__) && !defined(__CYGWIN__)
+#if !defined(__linux__) && !defined(__sun__) && !defined(__CYGWIN__) && !defined(__sgi)
 		sp->dst.sin_len = sizeof(struct sockaddr_in);
 #endif
 		sp->dst.sin_port = htons(DNSPORT);
@@ -318,7 +318,7 @@
 			printf("hostname to look up: %s\n", hostname);
 	}
 	bzero(&rasin, sizeof(struct sockaddr_in));
-#if !defined(__linux__) && !defined(__sun__) && !defined(__CYGWIN__)
+#if !defined(__linux__) && !defined(__sun__) && !defined(__CYGWIN__) && !defined(__sgi)
 	rasin.sin_len = sizeof(struct sockaddr_in);
 #endif
 	rasin.sin_family = AF_INET;
@@ -714,7 +714,7 @@
 	ifrp = NULL;
 	for (p = ifbuf; p < &ifbuf[ifconf.ifc_len]; ) {
 		ifrp = (struct ifreq *)p;
-#if defined(__linux__) || defined(__sun__) || defined(__CYGWIN__)
+#if defined(__linux__) || defined(__sun__) || defined(__CYGWIN__) || defined(__sgi)
 		p += sizeof(struct ifreq);
 #else
 		p += IFNAMSIZ + ifrp->ifr_addr.sa_len;
