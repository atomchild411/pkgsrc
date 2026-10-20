$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- libc++: a generic char_traits again, for IRIX

--- include/__string/char_traits.h.orig
+++ include/__string/char_traits.h
@@ -230,6 +230,43 @@ struct __char_traits_base {
   }
 };
 
+#if defined(__sgi) && !defined(_LIBCPP_IRIX_NO_GENERIC_CHAR_TRAITS)
+// IRIX: the generic char_traits libc++ 18 still had (int_type int, the
+// members as loops), which LLVM 19 removed. libstdc++ has one, and code
+// written against it -- basic_string<unsigned char>, <unsigned short>, of
+// a struct -- builds on Linux and the BSDs but not here (pbzip2, xsd,
+// libpqxx, mygui, pdf2djvu, blackbox). Define _LIBCPP_IRIX_NO_GENERIC_CHAR_TRAITS
+// for the standard behaviour.
+template <class _CharT>
+struct char_traits : __char_traits_base<_CharT, int, EOF> {
+  using char_type = _CharT;
+  _LIBCPP_HIDE_FROM_ABI static _LIBCPP_CONSTEXPR_SINCE_CXX17 int
+  compare(const char_type* __s1, const char_type* __s2, size_t __n) _NOEXCEPT {
+    for (; __n; --__n, ++__s1, ++__s2) {
+      if (*__s1 < *__s2)
+        return -1;
+      if (*__s2 < *__s1)
+        return 1;
+    }
+    return 0;
+  }
+  _LIBCPP_HIDE_FROM_ABI static _LIBCPP_CONSTEXPR_SINCE_CXX17 size_t length(const char_type* __s) _NOEXCEPT {
+    size_t __len = 0;
+    for (; !(*__s == char_type(0)); ++__s)
+      ++__len;
+    return __len;
+  }
+  _LIBCPP_HIDE_FROM_ABI static _LIBCPP_CONSTEXPR_SINCE_CXX17 const char_type*
+  find(const char_type* __s, size_t __n, const char_type& __a) _NOEXCEPT {
+    for (; __n; --__n, ++__s)
+      if (*__s == __a)
+        return __s;
+    return nullptr;
+  }
+};
+#endif
+
+
 // char_traits<wchar_t>
 
 #if _LIBCPP_HAS_WIDE_CHARACTERS
