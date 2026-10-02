$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- libc++: support IRIX 6.5

--- src/locale.cpp.orig
+++ src/locale.cpp
@@ -5390,7 +5390,7 @@ void moneypunct_byname<char, true>::init(const char* nm) {
     __frac_digits_ = lc->int_frac_digits;
   else
     __frac_digits_ = base::do_frac_digits();
-#if defined(_LIBCPP_MSVCRT) || defined(__MINGW32__)
+#if defined(_LIBCPP_MSVCRT) || defined(__MINGW32__) || defined(__sgi) // no C99 int_* in lconv
   if (lc->p_sign_posn == 0)
 #else  // _LIBCPP_MSVCRT
   if (lc->int_p_sign_posn == 0)
@@ -5398,7 +5398,7 @@ void moneypunct_byname<char, true>::init(const char* nm) {
     __positive_sign_ = "()";
   else
     __positive_sign_ = lc->positive_sign;
-#if defined(_LIBCPP_MSVCRT) || defined(__MINGW32__)
+#if defined(_LIBCPP_MSVCRT) || defined(__MINGW32__) || defined(__sgi) // no C99 int_* in lconv
   if (lc->n_sign_posn == 0)
 #else  // _LIBCPP_MSVCRT
   if (lc->int_n_sign_posn == 0)
@@ -5410,7 +5410,7 @@ void moneypunct_byname<char, true>::init(const char* nm) {
   // the same places in curr_symbol since there's no way to
   // represent anything else.
   string_type __dummy_curr_symbol = __curr_symbol_;
-#if defined(_LIBCPP_MSVCRT) || defined(__MINGW32__)
+#if defined(_LIBCPP_MSVCRT) || defined(__MINGW32__) || defined(__sgi) // no C99 int_* in lconv
   __init_pat(__pos_format_, __dummy_curr_symbol, true, lc->p_cs_precedes, lc->p_sep_by_space, lc->p_sign_posn, ' ');
   __init_pat(__neg_format_, __curr_symbol_, true, lc->n_cs_precedes, lc->n_sep_by_space, lc->n_sign_posn, ' ');
 #else  // _LIBCPP_MSVCRT
@@ -5507,7 +5507,7 @@ void moneypunct_byname<wchar_t, true>::init(const char* nm) {
     __frac_digits_ = lc->int_frac_digits;
   else
     __frac_digits_ = base::do_frac_digits();
-#  if defined(_LIBCPP_MSVCRT) || defined(__MINGW32__)
+#  if defined(_LIBCPP_MSVCRT) || defined(__MINGW32__) || defined(__sgi) // no C99 int_* in lconv
   if (lc->p_sign_posn == 0)
 #  else  // _LIBCPP_MSVCRT
   if (lc->int_p_sign_posn == 0)
@@ -5522,7 +5522,7 @@ void moneypunct_byname<wchar_t, true>::init(const char* nm) {
     wbe = wbuf + j;
     __positive_sign_.assign(wbuf, wbe);
   }
-#  if defined(_LIBCPP_MSVCRT) || defined(__MINGW32__)
+#  if defined(_LIBCPP_MSVCRT) || defined(__MINGW32__) || defined(__sgi) // no C99 int_* in lconv
   if (lc->n_sign_posn == 0)
 #  else  // _LIBCPP_MSVCRT
   if (lc->int_n_sign_posn == 0)
@@ -5541,7 +5541,7 @@ void moneypunct_byname<wchar_t, true>::init(const char* nm) {
   // the same places in curr_symbol since there's no way to
   // represent anything else.
   string_type __dummy_curr_symbol = __curr_symbol_;
-#  if defined(_LIBCPP_MSVCRT) || defined(__MINGW32__)
+#  if defined(_LIBCPP_MSVCRT) || defined(__MINGW32__) || defined(__sgi) // no C99 int_* in lconv
   __init_pat(__pos_format_, __dummy_curr_symbol, true, lc->p_cs_precedes, lc->p_sep_by_space, lc->p_sign_posn, L' ');
   __init_pat(__neg_format_, __curr_symbol_, true, lc->n_cs_precedes, lc->n_sep_by_space, lc->n_sign_posn, L' ');
 #  else  // _LIBCPP_MSVCRT
