$NetBSD$

IRIX: hardware details from hinv(1) (processor, core count, frequency,
memory, graphics board, system board type).

--- pts-core/objects/phodevi/components/phodevi_memory.php.orig
+++ pts-core/objects/phodevi/components/phodevi_memory.php
@@ -271,6 +271,10 @@
 	public static function memory_capacity()
 	{
 		// Returns physical memory capacity
+		if(phodevi::is_irix() && preg_match('/^Main memory size: (\d+) Mbytes/m', phodevi::irix_hinv(), $m))
+		{
+			return intval($m[1]);
+		}
 		if(isset(phodevi::$vfs->meminfo))
 		{
 			$info = phodevi::$vfs->meminfo;
