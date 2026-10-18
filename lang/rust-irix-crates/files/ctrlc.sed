# ctrlc 3.4: no pipe2 on IRIX: the pipe()+fcntl() emulation, as on macOS,
# Haiku, AIX and QNX.
s/^    target_os = "nto",$/    target_os = "nto", target_os = "irix",/
