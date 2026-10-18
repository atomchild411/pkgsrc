# if-addrs: IRIX's getifaddrs is the BSD one (ifa_dstaddr; no netlink):
# list IRIX where the multi-line cfg lists have illumos.
s/^\( *\)not(target_os = "illumos")$/\1not(target_os = "illumos"), not(target_os = "irix")/
s/^\( *\)target_os = "illumos"$/\1target_os = "illumos", target_os = "irix"/
s/^\( *\)target_os = "illumos",$/\1target_os = "illumos", target_os = "irix",/
