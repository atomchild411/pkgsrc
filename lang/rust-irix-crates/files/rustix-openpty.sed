# rustix-openpty 0.2: IRIX has no openpty(): get the pair from _getpty().
s/libc::openpty(/sys_openpty(/
/^\/\/\/ Open a pseudoterminal, without setting `OFlags::CLOEXEC`\.$/i #[cfg(not(target_os = "irix"))] use libc::openpty as sys_openpty;
/^\/\/\/ Open a pseudoterminal, without setting `OFlags::CLOEXEC`\.$/i #[cfg(target_os = "irix")] unsafe fn sys_openpty(m: *mut libc::c_int, s: *mut libc::c_int, _n: *mut libc::c_char, t: *const libc::termios, w: *mut libc::winsize) -> libc::c_int { extern "C" { fn _getpty(f: *mut libc::c_int, o: libc::c_int, mode: libc::mode_t, nofork: libc::c_int) -> *mut libc::c_char; } let name = _getpty(m, libc::O_RDWR | libc::O_NOCTTY, 0o600, 0); if name.is_null() { return -1; } *s = libc::open(name, libc::O_RDWR | libc::O_NOCTTY); if *s == -1 { libc::close(*m); return -1; } if !t.is_null() { libc::tcsetattr(*s, libc::TCSANOW, t); } if !w.is_null() { libc::ioctl(*s, libc::TIOCSWINSZ as _, w); } 0 }
# No login_tty() either, as on Solaris.
s/target_os = "illumos", target_os = "solaris")))\]/target_os = "illumos", target_os = "solaris", target_os = "irix")))]/
