$NetBSD$

IRIX: no musttail (LLVM cannot lower it on MIPS), and no reentrant resolver for SRV lookups.

--- cdk/foundation/socket_detail.cc.orig
+++ cdk/foundation/socket_detail.cc
@@ -1116,6 +1116,13 @@
   }
   return srv;
 }
+#elif defined(__sgi)
+
+// IRIX's resolver has no res_ninit()/res_nsearch(): no DNS SRV lookups.
+std::forward_list<Srv_host_detail> srv_list(const std::string &)
+{
+  return std::forward_list<Srv_host_detail>();
+}
 #else
 
 std::forward_list<Srv_host_detail> srv_list(const std::string &hostname)
