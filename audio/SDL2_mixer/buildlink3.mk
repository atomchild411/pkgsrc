# $NetBSD: buildlink3.mk,v 1.21 2026/09/02 19:00:43 wiz Exp $

BUILDLINK_TREE+=	SDL2_mixer

.include "../../mk/bsd.fast.prefs.mk"
.if ${MACHINE_PLATFORM:MDarwin-*-powerpc*}
# This defines SDL2_MIXER_BUILDLINK3_MK.
.  include "../../audio/SDL2_mixer-legacy/buildlink3.mk"
.endif

.if !defined(SDL2_MIXER_BUILDLINK3_MK)
SDL2_MIXER_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.SDL2_mixer+=	SDL2_mixer>=2.0.0
BUILDLINK_ABI_DEPENDS.SDL2_mixer+=	SDL2_mixer>=2.8.2nb2
BUILDLINK_PKGSRCDIR.SDL2_mixer?=	../../audio/SDL2_mixer

# SDL2_mixer.pc requires these (Requires.private), which pkg-config resolves
# for --cflags too (crossfire-client, sais, lightspark).
.include "../../audio/flac/buildlink3.mk"
.include "../../audio/game-music-emu/buildlink3.mk"
.include "../../audio/libvorbis/buildlink3.mk"
.include "../../audio/libxmp/buildlink3.mk"
.include "../../audio/mpg123/buildlink3.mk"
.include "../../audio/opusfile/buildlink3.mk"
.include "../../audio/wavpack/buildlink3.mk"
.include "../../devel/SDL2/buildlink3.mk"
.endif	# SDL2_MIXER_BUILDLINK3_MK

BUILDLINK_TREE+=	-SDL2_mixer
