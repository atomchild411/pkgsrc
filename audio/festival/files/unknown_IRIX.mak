 ###########################################################################
 ## Settings for IRIX 6.5 (pkgsrc cross builds: uname -s says IRIX).     ##
 ###########################################################################

include $(EST)/config/systems/default.mak

## the native audio module for this type of system
NATIVE_AUDIO_MODULE = IRIX

## echo -n doesn't work (well only sometimes ?)
ECHO_N = /bin/printf "%s"
