/*
 * libGLcompat: OpenGL entry points that IRIX's <GL/gl.h> declares but its
 * libGL.so and libGLcore.so do not export.
 *
 * IRIX's headers declare OpenGL 1.3 and 1.4 (glActiveTexture,
 * glMultiTexCoord*, glCompressedTexImage*, glWindowPos*, ...) and the ARB,
 * EXT, ATI and NV extensions SGI's later systems drive, but IRIX 6.5's
 * libraries (6.5.7, the oldest supported, through at least 6.5.22) export
 * none of them, so programs that call them do not link.
 *
 * Each function here asks IRIX's glXGetProcAddressARB for the driver's own
 * implementation, under its name and then its core or ARB/EXT twin, and
 * calls that. Where the driver has none (an Impact reports OpenGL 1.1 and
 * no multitexture), the call does nothing and returns 0: programs check the
 * extension string or version before they use these. A failed lookup is
 * kept only once a context is current, as a driver answers for its context.
 * IRIX's glXGetProcAddressARB returns NULL for what libGL lacks, and never
 * the program's (or this library's) own functions.
 *
 * Programs link it after libGL (pkgsrc: MesaLib's buildlink3.mk on IRIX),
 * so a libGL that exports a function itself still provides it.
 * glcompat.def lists the functions; mkglcompat.py makes it from IRIX's
 * <GL/gl.h> and the libraries' exported symbols.
 */

#include <GL/gl.h>
#include <GL/glx.h>
#include <stddef.h>

typedef void (*glc_fn)(void);

static glc_fn
glc_lookup(const char *name, const char *alt)
{
	glc_fn f;

	f = glXGetProcAddressARB((const GLubyte *)name);
	if (f == NULL && alt != NULL)
		f = glXGetProcAddressARB((const GLubyte *)alt);
	return f;
}

#define GLC_RESOLVE(R, N, P, ALT)						\
	if (!N##_r) {							\
		N##_p = (R (*)P)glc_lookup(#N, ALT);			\
		N##_r = N##_p != NULL || glXGetCurrentContext() != NULL; \
	}

#define GLC_VOID(N, P, A, ALT)						\
	static void (*N##_p)P;						\
	static int N##_r;						\
	void N P							\
	{								\
		GLC_RESOLVE(void, N, P, ALT)				\
		if (N##_p != NULL)					\
			N##_p A;					\
	}

#define GLC_RET(R, N, P, A, ALT)					\
	static R (*N##_p)P;						\
	static int N##_r;						\
	R N P								\
	{								\
		GLC_RESOLVE(R, N, P, ALT)				\
		return N##_p != NULL ? N##_p A : (R)0;			\
	}

#include "glcompat.def"
