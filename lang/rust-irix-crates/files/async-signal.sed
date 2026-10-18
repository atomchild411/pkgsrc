# async-signal 0.2.14: rustix has no Signal::IO on IRIX (SIGIO is SIGPOLL), as on Haiku.
s/cfg(not(target_os = "haiku"))/cfg(not(any(target_os = "haiku", target_os = "irix")))/g
