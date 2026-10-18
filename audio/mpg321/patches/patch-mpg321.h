$NetBSD: patch-mpg321.h,v 1.1 2025/10/07 03:56:02 mrg Exp $

Add / uncomment missing prototypes for GCC 14.
IRIX <sys/sem.h> defines union semun (outside X/Open modes).

--- mpg321.h.orig
+++ mpg321.h
@@ -242,7 +242,7 @@
 } fft_state;
 
 typedef short int sound_sample;
-//void fft_perform(const sound_sample *input, double *output, fft_state *state);
+void fft_perform(const sound_sample *input, double *output, fft_state *state);
 
 fft_state *fft_init(void);
 
@@ -290,7 +290,8 @@
 /* Shared total decoded frames */
 decoded_frames *Decoded_Frames;
 
-#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
+#if (defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)) || \
+    (defined(__sgi) && _NO_XOPEN4)
 /* */
 #else
 union semun {
@@ -303,4 +304,9 @@
 /* Get the next encoding/decoding place in the frame buffer */
 int getnext_place(int position);
 
+int calc_http_length(buffer *buf);
+void do_basicauth(void);
+ao_device *open_ao_playdevice_buffer(struct mad_header const *header);
+int check_default_play_device_buffer(void);
+
 #endif /* _MPG321_H_ */
