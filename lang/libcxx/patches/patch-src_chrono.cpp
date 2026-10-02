$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- libc++: support IRIX 6.5

--- src/chrono.cpp.orig
+++ src/chrono.cpp
@@ -55,6 +55,15 @@
 #  include <zircon/syscalls.h>
 #endif
 
+#if defined(__sgi)
+#  include <cstdint>
+#  include <fcntl.h>
+#  include <mutex>
+#  include <sys/mman.h>
+#  include <sys/syssgi.h>
+#  include <sys/times.h>
+#endif
+
 #if __has_include(<mach/mach_time.h>)
 #  include <mach/mach_time.h>
 #endif
@@ -229,6 +238,98 @@ static steady_clock::time_point __libcpp_steady_clock_now() noexcept {
   return steady_clock::time_point(nanoseconds(_zx_clock_get_monotonic()));
 }
 
+#  elif defined(__sgi)
+
+// IRIX has no CLOCK_MONOTONIC. What it has that never goes back is the
+// machine's free-running counter, which CLOCK_SGI_CYCLE reads by mapping it
+// from /dev/mmem -- but leaves its wraps to the caller, and the counter is
+// 32 bits on many machines (an Indigo2's wraps every 44 seconds); and
+// clock_gettime rounds its period down to whole nanoseconds (10.256 ns to 10
+// there). So map the counter here, keep its exact period, in picoseconds,
+// and count the wraps with times(), whose clock ticks since boot are coarse
+// but last over a year at 32 bits: of the whole wraps the counter may have
+// made since the last reading, the one nearest what times() says has
+// passed. Each reading is the reference for the next, so the two clocks,
+// which run off different oscillators, only need to agree to half a wrap
+// between readings, not over the life of the process. Without the counter,
+// times() alone serves.
+namespace {
+class __irix_steady_clock {
+  volatile uint32_t* __addr32_ = nullptr;
+  volatile uint64_t* __addr64_ = nullptr;
+  uint64_t __period_ps_        = 0;
+  uint64_t __tick_ns_          = 0;
+  uint64_t __boot_ns_          = 0; // times() at the first reading
+
+  // The last reading of a 32-bit counter.
+  mutex __mutex_;
+  uint32_t __last_count_ = 0;
+  clock_t __last_ticks_  = 0;
+  uint64_t __counts_     = 0; // since the first reading
+
+  // Counts to nanoseconds, without overflow for centuries of counts.
+  uint64_t __ns(uint64_t __n) const { return __n * (__period_ps_ / 1000) + __n * (__period_ps_ % 1000) / 1000; }
+
+public:
+  __irix_steady_clock() {
+    long __hz  = sysconf(_SC_CLK_TCK);
+    __tick_ns_ = 1000000000 / (__hz > 0 ? __hz : 100);
+    struct tms __tms;
+    __last_ticks_ = times(&__tms);
+    __boot_ns_    = static_cast<uint64_t>(static_cast<uint32_t>(__last_ticks_)) * __tick_ns_;
+
+    unsigned __period = 0;
+    ptrdiff_t __bits  = syssgi(SGI_CYCLECNTR_SIZE);
+    ptrdiff_t __phys  = syssgi(SGI_QUERY_CYCLECNTR, &__period);
+    if ((__bits != 32 && __bits != 64) || __phys == -1 || __period == 0)
+      return;
+    ptrdiff_t __page = getpagesize();
+    int __fd         = open("/dev/mmem", O_RDONLY);
+    if (__fd < 0)
+      return;
+    void* __map = mmap(nullptr, __page, PROT_READ, MAP_PRIVATE, __fd, __phys & ~(__page - 1));
+    close(__fd);
+    if (__map == MAP_FAILED)
+      return;
+    auto* __at   = static_cast<volatile char*>(__map) + (__phys & (__page - 1));
+    __period_ps_ = __period;
+    if (__bits == 64)
+      __addr64_ = reinterpret_cast<volatile uint64_t*>(__at);
+    else {
+      __addr32_     = reinterpret_cast<volatile uint32_t*>(__at);
+      __last_count_ = *__addr32_;
+    }
+  }
+
+  nanoseconds __now() {
+    if (__addr64_)
+      return nanoseconds(__ns(*__addr64_));
+    struct tms __tms;
+    lock_guard<mutex> __lock(__mutex_);
+    clock_t __ticks = times(&__tms);
+    uint64_t __since = static_cast<uint64_t>(static_cast<uint32_t>(__ticks - __last_ticks_)) * __tick_ns_;
+    __last_ticks_    = __ticks;
+    if (!__addr32_) {
+      __counts_ += __since; // in nanoseconds, then
+      return nanoseconds(__boot_ns_ + __counts_);
+    }
+    uint32_t __count   = *__addr32_;
+    uint64_t __fine    = static_cast<uint32_t>(__count - __last_count_);
+    __last_count_      = __count;
+    uint64_t __wrap_ns = __ns(uint64_t(1) << 32);
+    uint64_t __fine_ns = __ns(__fine);
+    uint64_t __wraps   = __since + __wrap_ns / 2 > __fine_ns ? (__since + __wrap_ns / 2 - __fine_ns) / __wrap_ns : 0;
+    __counts_ += __fine + (__wraps << 32);
+    return nanoseconds(__boot_ns_ + __ns(__counts_));
+  }
+};
+} // namespace
+
+static steady_clock::time_point __libcpp_steady_clock_now() {
+  static __irix_steady_clock __clock;
+  return steady_clock::time_point(__clock.__now());
+}
+
 #  elif defined(_LIBCPP_HAS_TIMESPEC_GET)
 
 static steady_clock::time_point __libcpp_steady_clock_now() {
