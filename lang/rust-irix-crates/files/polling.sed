# polling 3: IRIX has no pipe2 (pipe_with), like Haiku (and QNX).
s/any(target_os = "haiku", target_os = "nto")/any(target_os = "haiku", target_os = "nto", target_os = "irix")/g
s/cfg(not(target_os = "haiku"))/cfg(not(any(target_os = "haiku", target_os = "irix")))/g
s/cfg(target_os = "haiku")/cfg(any(target_os = "haiku", target_os = "irix"))/g
