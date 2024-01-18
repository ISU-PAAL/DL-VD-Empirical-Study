// commit message qemu@d9bce9d99f (target=1, prob=0.9985398, correct=True): Make it safe to use 64 bits GPR and/or 64 bits host registers. For "symetry", add 64 bits versions of all modified functions. As a side effect, add a lot of code provision for PowerPC 64 support. Move overflow and carry checks in common routines for simple cases. Add isel and popcntb instructions from PowerPC 2.03 specification. Remove remaining micro-operations helpers prototypes from op.c. Fix XER_BC field to be 7 bits long. Add power management support for PowerPC 603 & 604. Fix compilation warnings.
/*0  */ PPC_OP(srawi)                                // (4) 0.07692
/*2  */ {                                            // (9) 0.008547
/*4  */     T1 = T0;                                 // (5) 0.07692
/*6  */     T0 = (Ts0 >> PARAM(1));                  // (1) 0.1282
/*8  */     if (Ts1 < 0 && (Ts1 & PARAM(2)) != 0) {  // (0) 0.1966
/*10 */         xer_ca = 1;                          // (2) 0.1197
/*12 */     } else {                                 // (6) 0.05128
/*14 */         xer_ca = 0;                          // (3) 0.1197
/*16 */     }                                        // (8) 0.03419
/*18 */     RETURN();                                // (7) 0.05128
/*20 */ }                                            // (10) 0.008547
