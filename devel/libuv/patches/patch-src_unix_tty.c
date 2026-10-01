$NetBSD$

Apply MacPorts patch-libuv-legacy.diff for pre-10.7 platforms.

IRIX has no cfmakeraw(): use the Solaris implementation.

--- src/unix/tty.c.orig
+++ src/unix/tty.c
@@ -85,7 +85,7 @@ static int uv__tty_is_slave(const int fd) {
   int dummy;
 
   result = ioctl(fd, TIOCGPTN, &dummy) != 0;
-#elif defined(__APPLE__)
+#elif defined(__APPLE__) && MAC_OS_X_VERSION_MAX_ALLOWED >= 1050
   char dummy[256];
 
   result = ioctl(fd, TIOCPTYGNAME, &dummy) != 0;
@@ -244,7 +244,7 @@ skip:
 static void uv__tty_make_raw(struct termios* tio) {
   assert(tio != NULL);
 
-#if defined __sun || defined __MVS__
+#if defined __sun || defined __MVS__ || defined __sgi
   /*
    * This implementation of cfmakeraw for Solaris and derivatives is taken from
    * http://www.perkin.org.uk/posts/solaris-portability-cfmakeraw.html.
