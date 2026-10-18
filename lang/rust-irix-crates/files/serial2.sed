# serial2: IRIX has no B230400 (sys/ttydev.h stops at B115200); list B76800 instead.
s/(libc::B230400, 230400),/(libc::B76800, 76800),/
