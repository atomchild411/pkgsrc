$NetBSD$

Without IPv6 (IRIX builds use --disable-ipv6) Socket::AF_INET6 is not defined:
loading socket.rb (and so openssl, net/http, rubygems' remote fetcher) raised
NameError. Leave IPv6 out of Happy Eyeballs and connect the Ruby 3.3 way (decided
when socket.rb loads: ipaddr.rb later defines a placeholder AF_INET6).

--- ext/socket/lib/socket.rb.orig
+++ ext/socket/lib/socket.rb
@@ -612,10 +612,12 @@
   CONNECTION_ATTEMPT_DELAY = 0.25
   private_constant :CONNECTION_ATTEMPT_DELAY
 
-  ADDRESS_FAMILIES = {
+  # Without IPv6 support (IRIX builds use --disable-ipv6) Socket::AF_INET6
+  # is not defined.
+  ADDRESS_FAMILIES = (defined?(Socket::AF_INET6) ? {
     ipv6: Socket::AF_INET6,
     ipv4: Socket::AF_INET
-  }.freeze
+  } : { ipv4: Socket::AF_INET }).freeze
   private_constant :ADDRESS_FAMILIES
 
   HOSTNAME_RESOLUTION_QUEUE_UPDATED = 0
@@ -664,7 +666,7 @@
   #     puts sock.read
   #   }
   def self.tcp(host, port, local_host = nil, local_port = nil, connect_timeout: nil, resolv_timeout: nil, fast_fallback: tcp_fast_fallback, &) # :yield: socket
-    sock = if fast_fallback && !(host && ip_address?(host))
+    sock = if fast_fallback && ADDRESS_FAMILIES.key?(:ipv6) && !(host && ip_address?(host))
       tcp_with_fast_fallback(host, port, local_host, local_port, connect_timeout:, resolv_timeout:)
     else
       tcp_without_fast_fallback(host, port, local_host, local_port, connect_timeout:, resolv_timeout:)
