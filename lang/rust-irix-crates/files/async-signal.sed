# async-signal 0.2.14: rustix has no Signal::IO on IRIX (SIGIO is SIGPOLL), as on Haiku.
s/cfg(not(target_os = "haiku"))/cfg(not(any(target_os = "haiku", target_os = "irix")))/g
# async-signal 0.2.13 has no such cfg: rustix names no SIGIO on IRIX, whose
# SIGIO (SIGPOLL) is 22.
s/pub const SIGIO: c_int = sig!(IO, 29);/pub const SIGIO: c_int = 22;/
