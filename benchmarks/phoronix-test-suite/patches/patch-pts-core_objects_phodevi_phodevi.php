$NetBSD$

IRIX: hardware details from hinv(1) (processor, core count, frequency,
memory, graphics board, system board type).

--- pts-core/objects/phodevi/phodevi.php.orig
+++ pts-core/objects/phodevi/phodevi.php
@@ -1017,6 +1017,29 @@
 	{
 		return self::$operating_systems['windows'];
 	}
+	public static function is_irix()
+	{
+		return stripos(PHP_OS, 'IRIX') === 0;
+	}
+	public static function irix_hinv()
+	{
+		// IRIX: the hardware inventory, read once
+		static $hinv = null;
+		if($hinv === null)
+		{
+			$hinv = (string) shell_exec('/sbin/hinv 2>/dev/null');
+		}
+		return $hinv;
+	}
+	public static function irix_hinv_value($label)
+	{
+		// The rest of the first hinv line that starts with $label
+		if(preg_match('/^' . preg_quote($label, '/') . '(.+)$/m', self::irix_hinv(), $m))
+		{
+			return trim($m[1]);
+		}
+		return null;
+	}
 	public static function is_mesa_graphics()
 	{
 		self::detect_graphics();
