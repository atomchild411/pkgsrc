# fs2: no posix_fallocate on IRIX: allocate() as on Solaris.
s/^\( *\)target_os = "solaris",$/&\n\1target_os = "irix",/
