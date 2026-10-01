$NetBSD: patch-src_mips_ffi.c,v 1.3 2024/02/18 20:55:51 adam Exp $

Fixes to support the various NetBSD mips ports.

IRIX n32: long double is double (FFI_TYPE_LONGDOUBLE == FFI_TYPE_DOUBLE),
so the long double cases would duplicate the double ones; leave them out.

--- src/mips/ffi.c.orig
+++ src/mips/ffi.c
@@ -532,6 +532,8 @@
               cif->flags += t->type << (arg_reg * FFI_FLAG_BITS);
 	    arg_reg++;
 	    break;
+#ifdef __mips64
+#if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE /* IRIX n32: long double is double */
           case FFI_TYPE_LONGDOUBLE:
             /* Align it.  */
             arg_reg = FFI_ALIGN(arg_reg, 2);
@@ -553,9 +555,11 @@
 	      }
             break;
 
+#endif
 	  case FFI_TYPE_COMPLEX:
 	    switch (t->elements[0]->type)
 	      {
+#if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE /* IRIX n32: long double is double */
 	      case FFI_TYPE_LONGDOUBLE:
 		arg_reg = FFI_ALIGN(arg_reg, 2);
 		if (soft_float || index >= nfixedargs)
@@ -576,6 +580,7 @@
 		        continue;
 		  }
 		/* passthrough */
+#endif
 	      case FFI_TYPE_FLOAT:
 		// one fpr can only holds one arg even it is single
 		cif->bytes += 16;
@@ -605,6 +610,7 @@
 		break;
 	      }
 	    break;
+#endif
 
 	  case FFI_TYPE_STRUCT:
             loc = arg_reg * FFI_SIZEOF_ARG;
@@ -666,6 +672,8 @@
 	  cif->flags += cif->rtype->type << (FFI_FLAG_BITS * 8);
 	break;
 
+#ifdef __mips64
+#if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE /* IRIX n32: long double is double */
       case FFI_TYPE_LONGDOUBLE:
 	/* Long double is returned as if it were a struct containing
 	   two doubles.  */
@@ -683,6 +691,7 @@
 					      << (4 + (FFI_FLAG_BITS * 8));
 	  }
 	break;
+#endif
       case FFI_TYPE_COMPLEX:
 	{
 	  int type = cif->rtype->elements[0]->type;
@@ -698,9 +707,11 @@
 		case FFI_TYPE_INT:
 		  type = FFI_TYPE_SMALLSTRUCT2;
 		  break;
+#if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE /* IRIX n32: long double is double */
 		case FFI_TYPE_LONGDOUBLE:
 		  type = FFI_TYPE_LONGDOUBLE;
 		  break;
+#endif
 		case FFI_TYPE_FLOAT:
 		default:
 		  type = FFI_TYPE_SMALLSTRUCT;
@@ -723,6 +734,7 @@
       case FFI_TYPE_SINT64:
 	cif->flags += FFI_TYPE_UINT64 << (FFI_FLAG_BITS * 8);
 	break;
+#endif
       default:
 	cif->flags += cif->rtype->type << (FFI_FLAG_BITS * 8);
 	break;
