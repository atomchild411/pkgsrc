$NetBSD$

Set the "cmdline" cvar before the shareware check, which returns early:
with shareware data (no gfx/pop.lmp) it stayed empty, and every + command
on the command line (+map, +exec, +bind) was ignored.

--- Quake/common.c.orig
+++ Quake/common.c
@@ -1484,6 +1484,16 @@
 	unsigned short	check[128];
 	int		i;
 
+	for (i = 0; com_cmdline[i]; i++)
+	{
+		if (com_cmdline[i]!= ' ')
+			break;
+	}
+
+	// Before the shareware check, which returns early: stuffcmds
+	// reads the command line's + commands from this cvar.
+	Cvar_SetROM ("cmdline", &com_cmdline[i]);
+
 	COM_OpenFile("gfx/pop.lmp", &h, NULL);
 
 	if (h == -1)
@@ -1512,13 +1522,6 @@
 		}
 	}
 
-	for (i = 0; com_cmdline[i]; i++)
-	{
-		if (com_cmdline[i]!= ' ')
-			break;
-	}
-
-	Cvar_SetROM ("cmdline", &com_cmdline[i]);
 	Cvar_SetROM ("registered", "1");
 	Con_Printf ("Playing registered version.\n");
 }
