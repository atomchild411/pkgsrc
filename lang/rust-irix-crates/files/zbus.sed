# zbus 5.16+: no MSG_NOSIGNAL on IRIX (as on Apple's systems and Redox).
s/^\( *\)target_os = "redox"$/\1target_os = "redox",\n\1target_os = "irix"/
# zbus 4.4 to 5.12: no peer credentials on IRIX (no SO_PEERCRED or
# getpeereid): return empty credentials.
s/^fn get_unix_peer_creds_blocking(fd: RawFd) -> io::Result<crate::fdo::ConnectionCredentials> {$/&\n    #[cfg(target_os = "irix")]\n    return Ok(crate::fdo::ConnectionCredentials::default());/
# zbus 5.14 and 5.15: the same, on one line.
s/any(target_os = "macos", target_os = "redox")/any(target_os = "macos", target_os = "redox", target_os = "irix")/g
