$NetBSD$

timeDemoQuit takes timeDemo's second argument: play the demo through
once untimed first, to load everything it shows, then time the second
pass and quit. Unattended runs then measure drawing, not loading.

com_timeDemoSound 1 plays the timed pass with its sound; the precache
pass stays silent.

--- neo/framework/Session.cpp.orig
+++ neo/framework/Session.cpp
@@ -698,7 +698,7 @@
 ================
 */
 static void Session_TimeDemoQuit_f( const idCmdArgs &args ) {
-	sessLocal.TimeRenderDemo( va( "demos/%s", args.Argv(1) ) );
+	sessLocal.TimeRenderDemo( va( "demos/%s", args.Argv(1) ), ( args.Argc() > 2 ) );
 	if ( sessLocal.timeDemo == TD_YES ) {
 		// this allows hardware vendors to automate some testing
 		sessLocal.timeDemo = TD_YES_THEN_QUIT;
@@ -976,6 +976,8 @@
 idSessionLocal::TimeRenderDemo
 ================
 */
+static idCVar com_timeDemoSound( "com_timeDemoSound", "0", CVAR_SYSTEM | CVAR_BOOL, "play the timed pass of a timedemo with its sound (the precache pass stays silent)" );
+
 void idSessionLocal::TimeRenderDemo( const char *demoName, bool twice ) {
 	idStr demo = demoName;
 
@@ -1001,6 +1003,10 @@
 
 	if ( !readDemo ) {
 		return;
+	}
+
+	if ( com_timeDemoSound.GetBool() ) {
+		soundSystem->SetMute( false );
 	}
 
 	timeDemo = TD_YES;
