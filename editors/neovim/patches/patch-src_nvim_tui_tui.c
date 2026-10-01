$NetBSD$

IRIX's xwsh/winterm (TERM=iris-*) answer none of the TUI's terminal queries (DECRQM, DECRQSS, kitty keyboard, OSC 11, DA1) and print the ones they do not know: send them only what their terminfo describes, and do not wait for a DA1 reply when stopping. xwsh wraps immediately at the right margin (am without xenl), like the terminals already listed for that. On 8-colour terminals, fold colours 8-15 onto 0-7 as Vim does: a plain setaf (IRIX's \E[3%p1%dm) turns colour 10 into \E[310m.

--- src/nvim/tui/tui.c.orig
+++ src/nvim/tui/tui.c
@@ -138,6 +138,9 @@ struct TUIData {
   int height;
   bool rgb;
   bool screen_or_tmux;
+  // IRIX's xwsh/winterm (TERM=iris-*): they answer none of the queries and
+  // print the sequences they do not know, so send them only terminfo's.
+  bool iris;
   int url;  ///< Index of URL currently being printed, if any
   StringBuilder urlbuf;  ///< Re-usable buffer for writing OSC 8 control sequences
   Arena ti_arena;
@@ -350,6 +353,9 @@ static void tui_query_bg_color_noflush(TUIData *tui)
 void tui_query_bg_color(TUIData *tui)
   FUNC_ATTR_NONNULL_ALL
 {
+  if (tui->iris) {
+    return;
+  }
   tui_query_bg_color_noflush(tui);
   flush_buf(tui);
 }
@@ -430,12 +436,18 @@ static void terminfo_start(TUIData *tui)
   bool screen = terminfo_is_term_family(term, "screen");
   bool tmux = terminfo_is_term_family(term, "tmux") || os_env_exists("TMUX", true);
   tui->screen_or_tmux = screen || tmux;
+  tui->iris = terminfo_is_term_family(term, "iris");
 
   // truecolor support must be checked before patching/augmenting terminfo
   tui->rgb = term_has_truecolor(tui, colorterm);
 
   patch_terminfo_bugs(tui, term, colorterm, vtev, konsolev, iterm_env, nsterm);
   augment_terminfo(tui, term, vtev, konsolev, weztermv, iterm_env, nsterm);
+  if (tui->iris) {
+    tui->terminfo_ext.enable_focus_reporting = NULL;
+    tui->terminfo_ext.disable_focus_reporting = NULL;
+    tui->input.key_encoding = kKeyEncodingLegacy;
+  }
 
 #define TI_HAS(name) (tui->ti.defs[name] != NULL)
   tui->can_change_scroll_region = TI_HAS(kTerm_change_scroll_region);
@@ -451,7 +463,10 @@ static void terminfo_start(TUIData *tui)
     terminfo_is_term_family(term, "conemu")
     || terminfo_is_term_family(term, "cygwin")
     || terminfo_is_term_family(term, "win32con")
-    || terminfo_is_term_family(term, "interix");
+    || terminfo_is_term_family(term, "interix")
+    // IRIX's xwsh wraps at once (am without xenl), whatever the TERM's
+    // terminfo says (iris-color-tmux leaves out am for tmux's sake).
+    || terminfo_is_term_family(term, "iris");
   tui->bce = tui->ti.bce;
   // Set 't_Co' from the result of terminfo & fix_terminfo.
   t_colors = tui->ti.max_colors;
@@ -464,14 +479,16 @@ static void terminfo_start(TUIData *tui)
   /// Terminals usually ignore unrecognized private modes, and there is no
   /// known ambiguity with these. So we just set them unconditionally.
   // Enable bracketed paste
-  tui_set_term_mode(tui, kTermModeBracketedPaste, true);
+  if (!tui->iris) {
+    tui_set_term_mode(tui, kTermModeBracketedPaste, true);
+  }
 
   tui->has_left_and_right_margin_mode = false;
   tui->has_sync_mode = false;
 
   // Query support for private DEC modes that Nvim can take advantage of.
   // Some terminals (such as Terminal.app) do not support DECRQM, so skip the query.
-  if (!nsterm) {
+  if (!nsterm && !tui->iris) {
     tui_request_term_mode(tui, kTermModeLeftAndRightMargins);
     tui_request_term_mode(tui, kTermModeSynchronizedOutput);
     tui_request_term_mode(tui, kTermModeGraphemeClusters);
@@ -481,18 +498,22 @@ static void terminfo_start(TUIData *tui)
 
   // Don't use DECRQSS in screen or tmux, as they behave strangely when receiving it.
   // Terminal.app also doesn't support DECRQSS.
-  if (!TI_HAS(kTerm_set_underline_style) && !(screen || tmux || nsterm)) {
+  if (!TI_HAS(kTerm_set_underline_style) && !(screen || tmux || nsterm || tui->iris)) {
     // Query the terminal to see if it supports extended underline.
     tui_query_extended_underline(tui);
   }
 
   // Query the terminal to see if it supports Kitty's keyboard protocol
-  tui_query_kitty_keyboard(tui);
+  if (!tui->iris) {
+    tui_query_kitty_keyboard(tui);
+  }
 
   // Query the terminal's background color. We normally get it via continuous reporting (set via
   // `kTermModeThemeUpdates` above), but if we were backgrounded while the light/dark mode changed,
   // we won't have received the report, so we also query it on resume.
-  tui_query_bg_color_noflush(tui);
+  if (!tui->iris) {
+    tui_query_bg_color_noflush(tui);
+  }
 
   int ret;
   uv_loop_init(&tui->write_loop);
@@ -570,10 +591,23 @@ static void terminfo_disable(TUIData *tui)
     terminfo_out(tui, kTerm_reset_cursor_color);
   }
   // Disable bracketed paste
-  tui_set_term_mode(tui, kTermModeBracketedPaste, false);
+  if (!tui->iris) {
+    tui_set_term_mode(tui, kTermModeBracketedPaste, false);
+  }
   // Disable focus reporting
   out_len(tui, tui->terminfo_ext.disable_focus_reporting);
 
+  if (tui->iris) {
+    // No DA1 request: finish now instead of waiting for a reply.
+    void (*cb)(TUIData *) = tui->input.callbacks.primary_device_attr;
+    tui->input.callbacks.primary_device_attr = NULL;
+    flush_buf(tui);
+    if (cb) {
+      cb(tui);
+    }
+    return;
+  }
+
   // Send a DA1 request. When the terminal responds we know that it has
   // processed all of our requests and won't be emitting anymore sequences.
   out(tui, S_LEN("\x1b[c"));
@@ -886,6 +920,12 @@ static void update_attrs(TUIData *tui, int attr_id)
     fg = (attrs.cterm_fg_color
           ? attrs.cterm_fg_color - 1 : (tui->clear_attrs.cterm_fg_color - 1));
     if (fg != -1) {
+      // An 8-colour terminal: fold the bright colours onto the basic eight,
+      // as Vim does. (A plain setaf such as IRIX's "\E[3%p1%dm" would send
+      // "\E[310m" for colour 10.)
+      if (tui->ti.max_colors <= 8 && fg >= 8 && fg < 16) {
+        fg -= 8;
+      }
       terminfo_print_num1(tui, kTerm_set_a_foreground, fg);
     }
   }
@@ -903,6 +943,9 @@ static void update_attrs(TUIData *tui, int attr_id)
     bg = (attrs.cterm_bg_color
           ? attrs.cterm_bg_color - 1 : (tui->clear_attrs.cterm_bg_color - 1));
     if (bg != -1) {
+      if (tui->ti.max_colors <= 8 && bg >= 8 && bg < 16) {
+        bg -= 8;
+      }
       terminfo_print_num1(tui, kTerm_set_a_background, bg);
     }
   }
