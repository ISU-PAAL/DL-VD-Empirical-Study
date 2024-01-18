// commit message qemu@d9bce9d99f (target=1, prob=0.99856514, correct=True): Make it safe to use 64 bits GPR and/or 64 bits host registers. For "symetry", add 64 bits versions of all modified functions. As a side effect, add a lot of code provision for PowerPC 64 support. Move overflow and carry checks in common routines for simple cases. Add isel and popcntb instructions from PowerPC 2.03 specification. Remove remaining micro-operations helpers prototypes from op.c. Fix XER_BC field to be 7 bits long. Add power management support for PowerPC 603 & 604. Fix compilation warnings.
/*0  */ PPC_OP(cmpl)               // (5) 0.07339
/*2  */ {                          // (9) 0.009174
/*4  */     if (T0 < T1) {         // (4) 0.1101
/*6  */         T0 = 0x08;         // (0) 0.1284
/*8  */     } else if (T0 > T1) {  // (1) 0.1284
/*10 */         T0 = 0x04;         // (2) 0.1284
/*12 */     } else {               // (6) 0.05505
/*14 */         T0 = 0x02;         // (3) 0.1284
/*16 */     }                      // (8) 0.0367
/*18 */     RETURN();              // (7) 0.05505
/*20 */ }                          // (10) 0.009174
