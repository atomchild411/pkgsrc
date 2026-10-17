#!/usr/bin/env python3
"""mkglcompat-extra.py GLEXT_H GLCOMPAT_DEF SYSROOT NM > glcompat-extra.def

The OpenGL 1.5, 2.0 and 3.0 entry points (and ARB_vertex_buffer_object's
and EXT_framebuffer_object's) from Khronos' GLEXT_H that neither IRIX's
libGL.so, libGLcore.so and libGLU.so (SYSROOT/usr/lib32) export nor
GLCOMPAT_DEF (mkglcompat.py's list) already has, as GLC_VOID/GLC_RET lines
for glcompat.c, each with its twin: glFooARB or glFooEXT for a core glFoo,
glFoo for glFooARB/EXT. NM is an llvm-nm that reads IRIX n32 objects.
A maintainer's tool: the package builds from the glcompat-extra.def it made.
"""
import re
import subprocess
import sys

glext_h, base_def, sysroot, nm = sys.argv[1:5]
SECTIONS = ("GL_VERSION_1_5", "GL_VERSION_2_0", "GL_VERSION_3_0",
            "GL_ARB_vertex_buffer_object", "GL_EXT_framebuffer_object")

g = open(glext_h).read()
protos = {}
for m in re.finditer(r"GLAPI\s+([\w\s\*]+?)\s*APIENTRY\s+(gl\w+)\s*\(([^)]*)\)\s*;", g):
    protos[m.group(2)] = (" ".join(m.group(1).split()), " ".join(m.group(3).split()))
wanted = []
for sec in SECTIONS:
    m = re.search(r"#ifndef %s\n(.*?)#endif /\* %s \*/" % (sec, sec), g, re.S)
    if m:
        wanted += re.findall(r"GLAPI\s+[\w\s\*]+?\s*APIENTRY\s+(gl\w+)\s*\(", m.group(1))

have = set()
for lib in ("libGL.so", "libGLcore.so", "libGLU.so"):
    out = subprocess.run([nm, "-D", "--defined-only", "%s/usr/lib32/%s" % (sysroot, lib)],
                         capture_output=True, text=True, check=True).stdout
    have |= {l.split()[-1] for l in out.splitlines() if l.strip()}
have |= set(re.findall(r"^GLC_(?:VOID\(|RET\([^,]*,\s*)(gl\w+)", open(base_def).read(), re.M))

for n in sorted(set(wanted) - have):
    ret, params = protos[n]
    alt = "0"
    for suf in ("ARB", "EXT"):
        if n.endswith(suf) and n[:-len(suf)] in protos:
            alt = '"%s"' % n[:-len(suf)]
            break
        if n + suf in protos:
            alt = '"%s%s"' % (n, suf)
            break
    if params in ("void", ""):
        params, args = "void", "()"
    else:
        args = "(" + ", ".join(re.search(r"(\w+)\s*(\[\d*\])?$", p.strip()).group(1)
                               for p in params.split(",")) + ")"
    if ret == "void":
        print("GLC_VOID(%s, (%s), %s, %s)" % (n, params, args, alt))
    else:
        print("GLC_RET(%s, %s, (%s), %s, %s)" % (ret, n, params, args, alt))
