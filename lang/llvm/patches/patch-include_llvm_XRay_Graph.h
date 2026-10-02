$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Graph.h: no _G parameter

--- include/llvm/XRay/Graph.h.orig
+++ include/llvm/XRay/Graph.h
@@ -289,7 +289,7 @@ public:
     const_iterator end() const { return G.Vertices.end(); }
     size_type size() const { return G.Vertices.size(); }
     bool empty() const { return G.Vertices.empty(); }
-    VertexView(GraphT &_G) : G(_G) {}
+    VertexView(GraphT &TheG) : G(TheG) {}
   };
 
   /// A const iterator for iterating through the entire edge set of the graph.
@@ -326,7 +326,7 @@ public:
     const_iterator end() const { return G.Edges.end(); }
     size_type size() const { return G.Edges.size(); }
     bool empty() const { return G.Edges.empty(); }
-    EdgeView(GraphT &_G) : G(_G) {}
+    EdgeView(GraphT &TheG) : G(TheG) {}
   };
 
 public:
