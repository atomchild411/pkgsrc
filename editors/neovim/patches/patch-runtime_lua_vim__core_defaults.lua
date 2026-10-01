$NetBSD$

TERM=iris-*: no OSC 9;4 progress bars (xwsh/winterm print them).

--- runtime/lua/vim/_core/defaults.lua.orig
+++ runtime/lua/vim/_core/defaults.lua
@@ -1090,7 +1090,8 @@ do
     end
   end
 
-  if tty then
+  -- (Not on IRIX's xwsh/winterm, TERM=iris-*: they print the sequence.)
+  if tty and not (os.getenv('TERM') or ''):match('^iris%f[-%z]') then
     -- Show progress bars in supporting terminals
     vim.api.nvim_create_autocmd('Progress', {
       group = vim.api.nvim_create_augroup('nvim.progress', {}),
