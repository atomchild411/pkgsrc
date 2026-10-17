$NetBSD$

Each element as a T: with libc++, vector<bool> gives a bit reference, for which there is no xml::write.

--- source/dynv/Xml.cpp.orig
+++ source/dynv/Xml.cpp
@@ -72,7 +72,7 @@
 		using namespace std::string_literals;
 		if (!writeListStart(stream, name, dynv::types::typeHandler<T>().name))
 			return false;
-		for (const auto &i: values) {
+		for (const T &i: values) {
 			if (!writeStart(stream, "li"s))
 				return false;
 			if (!types::xml::write(stream, i))
