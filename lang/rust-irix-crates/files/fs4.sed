# fs4: IRIX has no fallocate in rustix; use the set_len fallback, as on Hurd.
s/target_os = "hurd",/target_os = "hurd", target_os = "irix",/
