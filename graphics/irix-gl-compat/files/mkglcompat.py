#!/usr/bin/env python3
"""mkglcompat.py SYSROOT NM > glcompat.def

The functions IRIX's <GL/gl.h> (in SYSROOT/usr/include) declares that its
libGL.so, libGLcore.so and libGLU.so (SYSROOT/usr/lib32) do not export, as
GLC_VOID/GLC_RET lines for glcompat.c: name, parameters, arguments, and the
twin name to try too (glFoo for glFooARB/EXT, glFooARB or glFooEXT for a
core glFoo), or 0. NM is an llvm-nm that reads IRIX n32 objects.
A maintainer's tool: the package builds from the glcompat.def it made.
"""
import re
import subprocess
import sys

sysroot, nm = sys.argv[1], sys.argv[2]
exported = set()
for lib in ("libGL.so", "libGLcore.so", "libGLU.so"):
    out = subprocess.run([nm, "-D", "%s/usr/lib32/%s" % (sysroot, lib)],
                         capture_output=True, text=True, check=True).stdout
    exported |= {l.split()[-1] for l in out.splitlines() if l.strip()}

src = open(sysroot + "/usr/include/GL/gl.h", errors="replace").read()
src = re.sub(r"/\*.*?\*/", "", src, flags=re.S)
decls = re.findall(r"extern\s+([A-Za-z_][A-Za-z0-9_ \*]*?)\s*\b(gl[A-Z]\w*)"
                   r"\s*\(([^;]*?)\)\s*;", src, flags=re.S)
missing = [(r.strip(), n, " ".join(p.split())) for r, n, p in decls
           if n not in exported]
names = {n for r, n, p in missing}
typeonly = re.compile(r"^(const\s+)?(GL\w+|void|GLvoid)\s*\**$")


def twin(n):
    for suf in ("ARB", "EXT"):
        if n.endswith(suf):
            return n[:-3]
    for suf in ("ARB", "EXT"):
        if n + suf in names:
            return n + suf
    return None


for ret, n, params in missing:
    if params in ("", "void"):
        decl, args = "(void)", "()"
    else:
        ds, an = [], []
        for i, prm in enumerate(x.strip() for x in params.split(",")):
            m = re.match(r"^(.*?)\b([A-Za-z_]\w*)\s*(\[[^\]]*\])?$", prm)
            if (not m or typeonly.match(prm) or m.group(2).startswith("GL")
                    or m.group(2) in ("const", "void")):
                ds.append("%s a%d" % (prm, i))
                an.append("a%d" % i)
            else:
                ds.append(prm)
                an.append(m.group(2))
        decl, args = "(%s)" % ", ".join(ds), "(%s)" % ", ".join(an)
    t = twin(n)
    t = '"%s"' % t if t else "0"
    if ret == "void":
        print("GLC_VOID(%s, %s, %s, %s)" % (n, decl, args, t))
    else:
        print("GLC_RET(%s, %s, %s, %s, %s)" % (ret, n, decl, args, t))
