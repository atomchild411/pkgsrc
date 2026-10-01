$NetBSD$

TERM=iris-*: no DA1/XTGETTCAP query for OSC 52 (xwsh/winterm have no OSC 52 and print unknown sequences).

--- runtime/plugin/osc52.lua.orig
+++ runtime/plugin/osc52.lua
@@ -11,6 +11,12 @@ vim.api.nvim_create_autocmd('UIEnter', {
       return
     end
 
+    -- IRIX's xwsh/winterm (TERM=iris-*) have no OSC 52, answer no queries
+    -- and print the ones they do not know.
+    if (vim.env.TERM or ''):match('^iris%f[-%z]') then
+      return
+    end
+
     local tty = false
     for _, ui in ipairs(vim.api.nvim_list_uis()) do
       if ui.stdout_tty then
