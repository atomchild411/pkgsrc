# hyper-util versions the 0.1.6 diff does not fit (0.1.3: gleam): no TCP
# keepalive interval or retries on IRIX, as on OpenBSD, Redox and Solaris.
s/target_os = "redox",/target_os = "redox", target_os = "irix",/g
