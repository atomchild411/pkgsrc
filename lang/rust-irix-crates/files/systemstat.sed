# systemstat: IRIX as illumos/Solaris (load average and interfaces through
# compiler-rt's getloadavg/getifaddrs, the rest "Not supported").
s/target_os = "solaris"/target_os = "solaris", target_os = "irix"/g
