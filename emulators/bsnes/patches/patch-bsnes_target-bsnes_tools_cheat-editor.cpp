$NetBSD$

ILP32: string[int] is ambiguous with the built-in [] through const char*; index with unsigned.

--- bsnes/target-bsnes/tools/cheat-editor.cpp.orig
+++ bsnes/target-bsnes/tools/cheat-editor.cpp
@@ -296,7 +296,7 @@
 
 auto CheatEditor::decodeSNES(string& code) -> bool {
   //Game Genie
-  if(code.size() == 9 && code[4] == '-') {
+  if(code.size() == 9 && code[4u] == '-') {
     //strip '-'
     code = {code.slice(0, 4), code.slice(5, 4)};
     //validate
@@ -345,7 +345,7 @@
   }
 
   //higan: address=data
-  if(code.size() == 9 && code[6] == '=') {
+  if(code.size() == 9 && code[6u] == '=') {
     string nibbles = {code.slice(0, 6), code.slice(7, 2)};
     //validate
     for(uint n : nibbles) {
@@ -358,7 +358,7 @@
   }
 
   //higan: address=compare?data
-  if(code.size() == 12 && code[6] == '=' && code[9] == '?') {
+  if(code.size() == 12 && code[6u] == '=' && code[9u] == '?') {
     string nibbles = {code.slice(0, 6), code.slice(7, 2), code.slice(10, 2)};
     //validate
     for(uint n : nibbles) {
@@ -382,7 +382,7 @@
   };
 
   //Game Genie
-  if(code.size() == 7 && code[3] == '-') {
+  if(code.size() == 7 && code[3u] == '-') {
     code = {code.slice(0, 3), code.slice(4, 3)};
     //validate
     for(uint n : code) {
@@ -397,7 +397,7 @@
   }
 
   //Game Genie
-  if(code.size() == 11 && code[3] == '-' && code[7] == '-') {
+  if(code.size() == 11 && code[3u] == '-' && code[7u] == '-') {
     code = {code.slice(0, 3), code.slice(4, 3), code.slice(8, 3)};
     //validate
     for(uint n : code) {
@@ -424,8 +424,8 @@
     }
     //first two characters are the code type / VRAM bank, which is almost always 01.
     //other values are presumably supported, but I have no info on them, so they're not supported.
-    if(code[0] != '0') return false;
-    if(code[1] != '1') return false;
+    if(code[0u] != '0') return false;
+    if(code[1u] != '1') return false;
     uint data = toHex(code.slice(2, 2));
     uint16_t address = toHex(code.slice(4, 4));
     address = address >> 8 | address << 8;
@@ -434,7 +434,7 @@
   }
 
   //higan: address=data
-  if(code.size() == 7 && code[4] == '=') {
+  if(code.size() == 7 && code[4u] == '=') {
     string nibbles = {code.slice(0, 4), code.slice(5, 2)};
     //validate
     for(uint n : nibbles) {
@@ -447,7 +447,7 @@
   }
 
   //higan: address=compare?data
-  if(code.size() == 10 && code[4] == '=' && code[7] == '?') {
+  if(code.size() == 10 && code[4u] == '=' && code[7u] == '?') {
     string nibbles = {code.slice(0, 4), code.slice(5, 2), code.slice(8, 2)};
     //validate
     for(uint n : nibbles) {
