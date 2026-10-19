$NetBSD$

IRIX: no malloc_usable_size (as for EMSCRIPTEN), no tm_gmtoff, and <unistd.h> declares crypt().

--- applications/mp4box/mp4box.c.orig
+++ applications/mp4box/mp4box.c
@@ -226,6 +226,8 @@
 Bool strict_cues, use_url_template, seg_at_rap, frag_at_rap, memory_frags, keep_utc, has_next_arg, no_cache, no_loop;
 Bool conv_type_from_ext;
 
+/* IRIX's <unistd.h> declares crypt(): rename this variable. */
+#define crypt mp4box_crypt
 u32 stat_level, hint_flags, import_flags, nb_add, nb_cat, crypt, agg_samples, nb_sdp_ex, max_ptime, split_size, nb_meta_act;
 u32 nb_track_act, rtp_rate, major_brand, nb_alt_brand_add, nb_alt_brand_rem, old_interleave, minor_version, conv_type, nb_tsel_acts;
 u32 program_number, time_shift_depth, initial_moof_sn, dump_std, import_subtitle, dump_saps_mode, force_new, compress_moov;
