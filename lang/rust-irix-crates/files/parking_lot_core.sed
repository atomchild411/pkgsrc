# parking_lot_core 0.2-0.8: IRIX has no pthread_condattr_setclock; use
# CLOCK_REALTIME condvars as on Android (0.9 is the parking_lot_core-0.9.12 port).
s/target_os = "ios", target_os = "android")/target_os = "ios", target_os = "android", target_os = "irix")/g
s/let clock = if cfg!(target_os = "android")/let clock = if cfg!(any(target_os = "android", target_os = "irix"))/
