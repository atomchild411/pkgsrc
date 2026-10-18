# gix-sec 0.10-0.13: uid_t is signed on IRIX (0.14 has the cast upstream-style
# in the gix-sec-0.14.2 port).
s/let uid = unsafe { libc::geteuid() };/let uid = unsafe { libc::geteuid() } as u32; \/\/ uid_t is signed on IRIX/
