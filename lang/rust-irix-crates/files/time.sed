# time 0.1 and early 0.3, and chrono 0.4.19 (which carries time 0.1's code):
# IRIX's struct tm has no tm_gmtoff (nor libc timegm); take the
# Solaris/illumos paths (timezone/altzone, TZ=UTC mktime; no local offset
# in time 0.3).
s/target_os = "illumos"/target_os = "illumos", target_os = "irix"/g
