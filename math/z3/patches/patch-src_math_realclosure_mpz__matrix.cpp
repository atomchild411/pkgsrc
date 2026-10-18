$NetBSD$

IRIX's <ctype.h> defines _A.

--- src/math/realclosure/mpz_matrix.cpp.orig
+++ src/math/realclosure/mpz_matrix.cpp
@@ -213,10 +213,10 @@
     return true;
 }
 
-bool mpz_matrix_manager::solve_core(mpz_matrix const & _A, mpz * b, bool int_solver) {
-    SASSERT(_A.n == _A.m);
+bool mpz_matrix_manager::solve_core(mpz_matrix const & A0, mpz * b, bool int_solver) {
+    SASSERT(A0.n == A0.m);
     scoped_mpz_matrix A(*this);
-    set(A, _A);
+    set(A, A0);
     for (unsigned k = 0; k < A.m(); k++) {
         TRACE("mpz_matrix", 
               tout << "k: " << k << "\n" << A;
@@ -347,13 +347,13 @@
     B.swap(C);
 }
 
-unsigned mpz_matrix_manager::linear_independent_rows(mpz_matrix const & _A, unsigned * r, mpz_matrix & B) {
+unsigned mpz_matrix_manager::linear_independent_rows(mpz_matrix const & A0, unsigned * r, mpz_matrix & B) {
     unsigned r_sz = 0;
     scoped_mpz_matrix A(*this);
     scoped_mpz g(nm());
     scoped_mpz t1(nm()), t2(nm());
     scoped_mpz a_ik_prime(nm()), a_kk_prime(nm()), lcm_a_kk_a_ik(nm());
-    set(A, _A);
+    set(A, A0);
     sbuffer<unsigned, 128> rows;
     rows.resize(A.m(), 0);
     for (unsigned i = 0; i < A.m(); i++)
@@ -389,10 +389,10 @@
     std::sort(r, r + r_sz);
     // Copy linear independent rows to B
     mpz_matrix & C = A;
-    mk(r_sz, _A.n, C);
+    mk(r_sz, A0.n, C);
     for (unsigned i = 0; i < r_sz; i++ ) {
-        for (unsigned j = 0; j < _A.n; j++) {
-            nm().set(C(i, j), _A(r[i], j));
+        for (unsigned j = 0; j < A0.n; j++) {
+            nm().set(C(i, j), A0(r[i], j));
         }
     }
     B.swap(C);
