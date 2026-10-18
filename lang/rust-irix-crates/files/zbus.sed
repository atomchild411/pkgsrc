# zbus 5.16+: no MSG_NOSIGNAL on IRIX (as on Apple's systems and Redox).
s/^\( *\)target_os = "redox"$/\1target_os = "redox",\n\1target_os = "irix"/
