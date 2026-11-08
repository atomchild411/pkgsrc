$NetBSD$

IRIX: hardware details from hinv(1) (processor, core count, frequency,
memory, graphics board, system board type).

--- pts-core/objects/phodevi/components/phodevi_motherboard.php.orig
+++ pts-core/objects/phodevi/components/phodevi_motherboard.php
@@ -464,6 +464,12 @@
 		// Returns the motherboard / system model name or number
 		$info = null;
 
+		if(phodevi::is_irix())
+		{
+			// The board type, e.g. "IP35"
+			return 'SGI ' . php_uname('m');
+		}
+
 		if(phodevi::is_macos())
 		{
 			$info = phodevi_osx_parser::read_osx_system_profiler('SPHardwareDataType', 'ModelName');
