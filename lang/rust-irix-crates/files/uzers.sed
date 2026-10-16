# uzers: IRIX's passwd and group are Solaris's: list IRIX where Solaris is.
s/^\( *\)target_os = "solaris",$/&\n\1target_os = "irix",/
