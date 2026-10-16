$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Ignore #pragma clang fp exceptions on targets without strict FP

--- lib/Parse/ParsePragma.cpp.orig
+++ lib/Parse/ParsePragma.cpp
@@ -3392,6 +3392,17 @@ void PragmaFPHandler::HandlePragma(Preprocessor &PP,
             << PP.getSpelling(Tok) << OptionInfo->getName() << *FlagKind;
         return;
       }
+      // As for the other pragmas that change the floating-point environment
+      // (FENV_ACCESS, float_control, FENV_ROUND): a target without strict FP
+      // support ignores them. Its backend cannot lower the constrained
+      // operations this would emit (MIPS: LegalizeDAG asserts on every
+      // strict comparison after "exceptions(strict)").
+      if (*AnnotValue->ExceptionsValue != LangOptions::FPE_Ignore &&
+          !PP.getTargetInfo().hasStrictFP() && !PP.getLangOpts().ExpStrictFP) {
+        PP.Diag(Tok.getLocation(), diag::warn_pragma_fp_ignored)
+            << "clang fp exceptions";
+        AnnotValue->ExceptionsValue = std::nullopt;
+      }
     } else if (FlagKind == PFK_EvalMethod) {
       AnnotValue->EvalMethodValue =
           llvm::StringSwitch<std::optional<LangOptions::FPEvalMethodKind>>(
