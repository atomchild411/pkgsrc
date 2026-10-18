# async-process: uid_t and gid_t are signed on IRIX (std takes i32 there).
s/self\.inner\.uid(id);/self.inner.uid(id as _);/
s/self\.inner\.gid(id);/self.inner.gid(id as _);/
