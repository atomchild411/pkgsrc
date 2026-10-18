# smithay-client-toolkit 0.19, 0.20: IRIX has no pipe2, so rustix has no
# pipe_with: pipe(), then close-on-exec on both ends.
s/use rustix::pipe::{pipe_with, PipeFlags};/use rustix::io::{fcntl_setfd, FdFlags}; use rustix::pipe::pipe;/
s/let (readfd, writefd) = pipe_with(PipeFlags::CLOEXEC)?;/let (readfd, writefd) = pipe()?; fcntl_setfd(\&readfd, FdFlags::CLOEXEC)?; fcntl_setfd(\&writefd, FdFlags::CLOEXEC)?;/
