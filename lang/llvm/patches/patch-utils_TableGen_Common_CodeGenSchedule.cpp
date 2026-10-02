$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Count ItinRW mappings in the schedule completeness check

--- utils/TableGen/Common/CodeGenSchedule.cpp.orig
+++ utils/TableGen/Common/CodeGenSchedule.cpp
@@ -1945,6 +1945,14 @@ void CodeGenSchedModels::checkCompleteness() {
       if (HasItineraries && SC.ItinClassDef != nullptr &&
           SC.ItinClassDef->getName() != "NoItinerary")
         continue;
+      // An ItinRW of this model may map the instruction's itinerary class.
+      if (SC.ItinClassDef != nullptr &&
+          SC.ItinClassDef->getName() != "NoItinerary" &&
+          any_of(ProcModel.ItinRWDefs, [&SC](const Record *RW) {
+            return is_contained(RW->getValueAsListOfDefs("MatchedItinClasses"),
+                                SC.ItinClassDef);
+          }))
+        continue;
 
       const ConstRecVec &InstRWs = SC.InstRWs;
       auto I = find_if(InstRWs, [&ProcModel](const Record *R) {
