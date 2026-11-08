$NetBSD$

IRIX: hardware details from hinv(1) (processor, core count, frequency,
memory, graphics board, system board type).

--- pts-core/objects/phodevi/components/phodevi_gpu.php.orig
+++ pts-core/objects/phodevi/components/phodevi_gpu.php
@@ -787,6 +787,10 @@
 	}
 	public static function gpu_string()
 	{
+		if(phodevi::is_irix() && ($board = phodevi::irix_hinv_value('Graphics board: ')))
+		{
+			return 'SGI ' . $board;
+		}
 		$info = phodevi_parser::read_glx_renderer();
 
 		if(stripos($info, 'llvmpipe'))
@@ -1122,6 +1126,10 @@
 	}
 	public static function gpu_model()
 	{
+		if(phodevi::is_irix() && ($board = phodevi::irix_hinv_value('Graphics board: ')))
+		{
+			return 'SGI ' . $board;
+		}
 		// Report graphics processor string
 		$info = str_replace('(R)', '', phodevi_parser::read_glx_renderer());
 		$video_ram = phodevi::read_property('gpu', 'memory-capacity');
