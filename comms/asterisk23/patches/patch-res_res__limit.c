$NetBSD: patch-res_res__limit.c,v 1.1 2025/10/27 06:58:40 jnemeth Exp $
IRIX: getifaddrs EID, endian.h, db1 pgno_t, qlog, RLIMIT_MEMLOCK, TCP keepalive names; GNU sed needs [[:space:]].

--- res/res_limit.c.orig
+++ res/res_limit.c
@@ -52,6 +52,8 @@
 	{ RLIMIT_CORE,    "-c", "core file size", "core" },
 #ifdef RLIMIT_RSS
 	{ RLIMIT_RSS,     "-m", "resident memory", "memory" },
+#endif
+#ifdef RLIMIT_MEMLOCK
 	{ RLIMIT_MEMLOCK, "-l", "amount of memory locked into RAM", "locked" },
 #endif
 #ifdef RLIMIT_NPROC
@@ -191,7 +193,7 @@
 				else
 					snprintf(printlimit, sizeof(printlimit), "limited to %d", (int) rlimit.rlim_cur);
 				desc = str2desc(a->argv[1]);
-				ast_cli(a->fd, "%c%s (%s) is %s.\n", toupper(desc[0]), desc + 1, a->argv[1], printlimit);
+				ast_cli(a->fd, "%c%s (%s) is %s.\n", toupper((unsigned char)desc[0]), desc + 1, a->argv[1], printlimit);
 			} else
 				ast_cli(a->fd, "Could not retrieve resource limits for %s: %s\n", str2desc(a->argv[1]), strerror(errno));
 			return CLI_SUCCESS;
