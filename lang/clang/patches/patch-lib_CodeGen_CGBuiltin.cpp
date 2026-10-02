$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- long double is a double

--- lib/CodeGen/CGBuiltin.cpp.orig
+++ lib/CodeGen/CGBuiltin.cpp
@@ -239,6 +239,26 @@ llvm::Constant *CodeGenModule::getBuiltinLibFunction(const FunctionDecl *FD,
       Name = AIXLongDouble64Builtins[BuiltinID];
     else
       Name = Context.BuiltinInfo.getName(BuiltinID).substr(10);
+
+    // IRIX's *l functions take MIPSpro's long double, a pair of doubles;
+    // clang's is a double there, so call the double function instead
+    // (nexttoward, whose second argument is a long double, is nextafter).
+    auto IsLongDouble = [](QualType T) {
+      if (const auto *CT = T->getAs<ComplexType>())
+        T = CT->getElementType();
+      return T->isSpecificBuiltinType(BuiltinType::LongDouble);
+    };
+    const auto *FPT = FD->getType()->getAs<FunctionProtoType>();
+    if (getTriple().isOSIRIX() &&
+        &getTarget().getLongDoubleFormat() == &llvm::APFloat::IEEEdouble() &&
+        FPT &&
+        (IsLongDouble(FPT->getReturnType()) ||
+         llvm::any_of(FPT->getParamTypes(), IsLongDouble))) {
+      if (Name == "nexttoward" || Name == "nexttowardl")
+        Name = "nextafter";
+      else if (Name.ends_with("l"))
+        Name.pop_back();
+    }
   }
 
   llvm::FunctionType *Ty =
