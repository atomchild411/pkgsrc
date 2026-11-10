$NetBSD$

Align each scratch chunk to 16 bytes: packed, the arrays after the
bool array start misaligned, and the multithreaded solver's batching
dies with SIGBUS on strict-alignment CPUs (MIPS/IRIX).

--- src/BulletDynamics/ConstraintSolver/btBatchedConstraints.cpp.orig
+++ src/BulletDynamics/ConstraintSolver/btBatchedConstraints.cpp
@@ -614,6 +614,9 @@
 	};
 	Chunk m_chunks[N];
 	int m_numChunks;
+	// every chunk starts 16-byte aligned (btVector3; and the ints after a bool
+	// array would otherwise be misaligned, a SIGBUS on strict-alignment CPUs)
+	static size_t alignedSize(size_t sz) { return (sz + 15) & ~size_t(15); }
 
 public:
 	PreallocatedMemoryHelper() { m_numChunks = 0; }
@@ -633,7 +636,7 @@
 		size_t totalSize = 0;
 		for (int i = 0; i < m_numChunks; ++i)
 		{
-			totalSize += m_chunks[i].size;
+			totalSize += alignedSize(m_chunks[i].size);
 		}
 		return totalSize;
 	}
@@ -645,7 +648,7 @@
 			const Chunk& chunk = m_chunks[i];
 			char* chunkPtr = static_cast<char*>(mem) + totalSize;
 			*chunk.ptr = chunkPtr;
-			totalSize += chunk.size;
+			totalSize += alignedSize(chunk.size);
 		}
 	}
 };
