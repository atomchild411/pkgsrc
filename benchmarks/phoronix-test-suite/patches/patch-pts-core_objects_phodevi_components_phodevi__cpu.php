$NetBSD$

IRIX: hardware details from hinv(1) (processor, core count, frequency,
memory, graphics board, system board type).

--- pts-core/objects/phodevi/components/phodevi_cpu.php.orig
+++ pts-core/objects/phodevi/components/phodevi_cpu.php
@@ -106,6 +106,16 @@
 			// Should be used by Windows they have NUMBER_OF_PROCESSORS set and use this as an easy way to override CPUs exposed
 			$info = $n;
 		}
+		else if(phodevi::is_irix())
+		{
+			// "Processor 0: ..." for each CPU, or "4 600 MHZ IP35 Processors"
+			$hinv = phodevi::irix_hinv();
+			$info = preg_match_all('/^Processor \d+:/m', $hinv);
+			if($info == 0 && preg_match('/^(\d+) [0-9.]+ [GM]HZ .*Processors?$/mi', $hinv, $m))
+			{
+				$info = intval($m[1]);
+			}
+		}
 		else if(phodevi::is_linux())
 		{
 			$sl = phodevi::read_property('system', 'system-layer');
@@ -429,6 +439,11 @@
 	{
 		// Find out the processor frequency
 		$info = null;
+		if(phodevi::is_irix() && preg_match('/^(?:Processor \d+: |\d+ )([0-9.]+) (GHZ|MHZ)/mi', phodevi::irix_hinv(), $m))
+		{
+			// "Processor 0: 2.2 GHZ" or "4 600 MHZ IP35 Processors"
+			return round(strtoupper($m[2]) == 'GHZ' ? $m[1] : $m[1] / 1000, 2);
+		}
 		// First, the ideal way, with modern CPUs using CnQ or EIST and cpuinfo reporting the current
 		if(phodevi::is_linux())
 		{
@@ -527,6 +542,12 @@
 		// Returns the processor name / frequency information
 		$info = null;
 
+		if(phodevi::is_irix() && ($cpu = phodevi::irix_hinv_value('CPU: ')))
+		{
+			// "MIPS R16000 Processor Chip Revision: 2.2"
+			return trim(preg_replace('/ Processor Chip.*$/', '', $cpu));
+		}
+
 		if(isset(phodevi::$vfs->cpuinfo))
 		{
 			$physical_cpu_ids = phodevi_linux_parser::read_cpuinfo('physical id');
