# users (lla): IRIX's passwd and group are Solaris's: list IRIX where
# Solaris is.
s/target_os = "solaris"\([,)]\)/target_os = "solaris", target_os = "irix"\1/g
