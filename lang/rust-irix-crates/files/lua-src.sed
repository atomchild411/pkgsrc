# lua-src (mlua): build Lua for IRIX as a POSIX system.
s/^\( *\)_ if target\.contains("windows") => {$/\1_ if target.contains("irix") => {\n\1    config.define("LUA_USE_POSIX", None);\n\1}\n&/
