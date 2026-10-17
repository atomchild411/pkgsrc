/*
 * IRIX: <GL/glx.h> is IRIX's, with what Mesa's adds that code written for it
 * uses.
 *
 * IRIX's (with <GL/glxtokens.h>) declares GLX 1.1 to 1.4 and the extensions
 * it has with prototypes but without their PFNGLX...PROC pointer types, and
 * lacks a few tokens of them. Mesa's defines the GLX_INTEL_swap_event
 * event and structure and ends by including <GL/glxext.h>, which declares
 * the rest; but it skips each extension a <GL/glx.h> already defines, so the
 * types and tokens of IRIX's own are added here first, from Mesa 21.3.9's
 * <GL/glxext.h>, each under the macro IRIX defines for it.
 * GLX_GLXEXT_LEGACY leaves <GL/glxext.h> out, as in Mesa.
 */
#ifndef _PKGSRC_IRIX_GLX_H
#define _PKGSRC_IRIX_GLX_H

#include_next <GL/glx.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef GLX_VERSION_1_4
typedef void ( *__GLXextFuncPtr)(void);
#endif
#ifdef GLX_VERSION_1_3
typedef GLXFBConfig *( *PFNGLXGETFBCONFIGSPROC) (Display *dpy, int screen, int *nelements);
typedef GLXFBConfig *( *PFNGLXCHOOSEFBCONFIGPROC) (Display *dpy, int screen, const int *attrib_list, int *nelements);
typedef int ( *PFNGLXGETFBCONFIGATTRIBPROC) (Display *dpy, GLXFBConfig config, int attribute, int *value);
typedef XVisualInfo *( *PFNGLXGETVISUALFROMFBCONFIGPROC) (Display *dpy, GLXFBConfig config);
typedef GLXWindow ( *PFNGLXCREATEWINDOWPROC) (Display *dpy, GLXFBConfig config, Window win, const int *attrib_list);
typedef void ( *PFNGLXDESTROYWINDOWPROC) (Display *dpy, GLXWindow win);
typedef GLXPixmap ( *PFNGLXCREATEPIXMAPPROC) (Display *dpy, GLXFBConfig config, Pixmap pixmap, const int *attrib_list);
typedef void ( *PFNGLXDESTROYPIXMAPPROC) (Display *dpy, GLXPixmap pixmap);
typedef GLXPbuffer ( *PFNGLXCREATEPBUFFERPROC) (Display *dpy, GLXFBConfig config, const int *attrib_list);
typedef void ( *PFNGLXDESTROYPBUFFERPROC) (Display *dpy, GLXPbuffer pbuf);
typedef void ( *PFNGLXQUERYDRAWABLEPROC) (Display *dpy, GLXDrawable draw, int attribute, unsigned int *value);
typedef GLXContext ( *PFNGLXCREATENEWCONTEXTPROC) (Display *dpy, GLXFBConfig config, int render_type, GLXContext share_list, Bool direct);
typedef Bool ( *PFNGLXMAKECONTEXTCURRENTPROC) (Display *dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx);
typedef GLXDrawable ( *PFNGLXGETCURRENTREADDRAWABLEPROC) (void);
typedef int ( *PFNGLXQUERYCONTEXTPROC) (Display *dpy, GLXContext ctx, int attribute, int *value);
typedef void ( *PFNGLXSELECTEVENTPROC) (Display *dpy, GLXDrawable draw, unsigned long event_mask);
typedef void ( *PFNGLXGETSELECTEDEVENTPROC) (Display *dpy, GLXDrawable draw, unsigned long *event_mask);
#endif
#ifdef GLX_VERSION_1_4
#ifndef GLX_SAMPLE_BUFFERS
#define GLX_SAMPLE_BUFFERS                100000
#endif
#ifndef GLX_SAMPLES
#define GLX_SAMPLES                       100001
#endif
typedef __GLXextFuncPtr ( *PFNGLXGETPROCADDRESSPROC) (const GLubyte *procName);
#endif
#ifdef GLX_EXT_import_context
typedef Display *( *PFNGLXGETCURRENTDISPLAYEXTPROC) (void);
typedef int ( *PFNGLXQUERYCONTEXTINFOEXTPROC) (Display *dpy, GLXContext context, int attribute, int *value);
typedef GLXContextID ( *PFNGLXGETCONTEXTIDEXTPROC) (const GLXContext context);
typedef GLXContext ( *PFNGLXIMPORTCONTEXTEXTPROC) (Display *dpy, GLXContextID contextID);
typedef void ( *PFNGLXFREECONTEXTEXTPROC) (Display *dpy, GLXContext context);
#endif
#ifdef GLX_SGIX_fbconfig
typedef int ( *PFNGLXGETFBCONFIGATTRIBSGIXPROC) (Display *dpy, GLXFBConfigSGIX config, int attribute, int *value);
typedef GLXFBConfigSGIX *( *PFNGLXCHOOSEFBCONFIGSGIXPROC) (Display *dpy, int screen, int *attrib_list, int *nelements);
typedef GLXPixmap ( *PFNGLXCREATEGLXPIXMAPWITHCONFIGSGIXPROC) (Display *dpy, GLXFBConfigSGIX config, Pixmap pixmap);
typedef GLXContext ( *PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC) (Display *dpy, GLXFBConfigSGIX config, int render_type, GLXContext share_list, Bool direct);
typedef XVisualInfo *( *PFNGLXGETVISUALFROMFBCONFIGSGIXPROC) (Display *dpy, GLXFBConfigSGIX config);
typedef GLXFBConfigSGIX ( *PFNGLXGETFBCONFIGFROMVISUALSGIXPROC) (Display *dpy, XVisualInfo *vis);
#endif
#ifdef GLX_SGIX_hyperpipe
typedef GLXHyperpipeNetworkSGIX *( *PFNGLXQUERYHYPERPIPENETWORKSGIXPROC) (Display *dpy, int *npipes);
typedef int ( *PFNGLXHYPERPIPECONFIGSGIXPROC) (Display *dpy, int networkId, int npipes, GLXHyperpipeConfigSGIX *cfg, int *hpId);
typedef GLXHyperpipeConfigSGIX *( *PFNGLXQUERYHYPERPIPECONFIGSGIXPROC) (Display *dpy, int hpId, int *npipes);
typedef int ( *PFNGLXDESTROYHYPERPIPECONFIGSGIXPROC) (Display *dpy, int hpId);
typedef int ( *PFNGLXBINDHYPERPIPESGIXPROC) (Display *dpy, int hpId);
typedef int ( *PFNGLXQUERYHYPERPIPEBESTATTRIBSGIXPROC) (Display *dpy, int timeSlice, int attrib, int size, void *attribList, void *returnAttribList);
typedef int ( *PFNGLXHYPERPIPEATTRIBSGIXPROC) (Display *dpy, int timeSlice, int attrib, int size, void *attribList);
typedef int ( *PFNGLXQUERYHYPERPIPEATTRIBSGIXPROC) (Display *dpy, int timeSlice, int attrib, int size, void *returnAttribList);
#endif
#ifdef GLX_SGIX_pbuffer
typedef GLXPbufferSGIX ( *PFNGLXCREATEGLXPBUFFERSGIXPROC) (Display *dpy, GLXFBConfigSGIX config, unsigned int width, unsigned int height, int *attrib_list);
typedef void ( *PFNGLXDESTROYGLXPBUFFERSGIXPROC) (Display *dpy, GLXPbufferSGIX pbuf);
typedef void ( *PFNGLXQUERYGLXPBUFFERSGIXPROC) (Display *dpy, GLXPbufferSGIX pbuf, int attribute, unsigned int *value);
typedef void ( *PFNGLXSELECTEVENTSGIXPROC) (Display *dpy, GLXDrawable drawable, unsigned long mask);
typedef void ( *PFNGLXGETSELECTEDEVENTSGIXPROC) (Display *dpy, GLXDrawable drawable, unsigned long *mask);
#endif
#ifdef GLX_SGIX_swap_barrier
typedef void ( *PFNGLXBINDSWAPBARRIERSGIXPROC) (Display *dpy, GLXDrawable drawable, int barrier);
typedef Bool ( *PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC) (Display *dpy, int screen, int *max);
#endif
#ifdef GLX_SGIX_swap_group
typedef void ( *PFNGLXJOINSWAPGROUPSGIXPROC) (Display *dpy, GLXDrawable drawable, GLXDrawable member);
#endif
#ifdef GLX_SGIX_video_resize
typedef int ( *PFNGLXBINDCHANNELTOWINDOWSGIXPROC) (Display *display, int screen, int channel, Window window);
typedef int ( *PFNGLXCHANNELRECTSGIXPROC) (Display *display, int screen, int channel, int x, int y, int w, int h);
typedef int ( *PFNGLXQUERYCHANNELRECTSGIXPROC) (Display *display, int screen, int channel, int *dx, int *dy, int *dw, int *dh);
typedef int ( *PFNGLXQUERYCHANNELDELTASSGIXPROC) (Display *display, int screen, int channel, int *x, int *y, int *w, int *h);
typedef int ( *PFNGLXCHANNELRECTSYNCSGIXPROC) (Display *display, int screen, int channel, GLenum synctype);
#endif
#ifdef GLX_SGIX_video_source
#if defined(_VL_H) || defined(_VL_H_)
typedef GLXVideoSourceSGIX ( *PFNGLXCREATEGLXVIDEOSOURCESGIXPROC) (Display *display, int screen, VLServer server, VLPath path, int nodeClass, VLNode drainNode);
typedef void ( *PFNGLXDESTROYGLXVIDEOSOURCESGIXPROC) (Display *dpy, GLXVideoSourceSGIX glxvideosource);
#endif
#endif
#ifdef GLX_SGI_make_current_read
typedef Bool ( *PFNGLXMAKECURRENTREADSGIPROC) (Display *dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx);
typedef GLXDrawable ( *PFNGLXGETCURRENTREADDRAWABLESGIPROC) (void);
#endif
#ifdef GLX_SGI_swap_control
typedef int ( *PFNGLXSWAPINTERVALSGIPROC) (int interval);
#endif
#ifdef GLX_SGI_video_sync
typedef int ( *PFNGLXGETVIDEOSYNCSGIPROC) (unsigned int *count);
typedef int ( *PFNGLXWAITVIDEOSYNCSGIPROC) (int divisor, int remainder, unsigned int *count);
#endif

#ifndef GLX_BufferSwapComplete
#define GLX_BufferSwapComplete	1
#endif

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	GLXDrawable drawable;	/* drawable on which event was requested */
	int event_type;
	int64_t ust;
	int64_t msc;
	int64_t sbc;
} GLXBufferSwapComplete;

#ifdef __cplusplus
}
#endif

#ifndef GLX_GLXEXT_LEGACY
#include <GL/glxext.h>
#endif

#endif /* _PKGSRC_IRIX_GLX_H */
