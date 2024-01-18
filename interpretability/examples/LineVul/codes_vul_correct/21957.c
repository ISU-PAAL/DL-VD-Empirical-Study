// commit message qemu@d9bce9d99f (target=1, prob=0.9984376, correct=True): Make it safe to use 64 bits GPR and/or 64 bits host registers. For "symetry", add 64 bits versions of all modified functions. As a side effect, add a lot of code provision for PowerPC 64 support. Move overflow and carry checks in common routines for simple cases. Add isel and popcntb instructions from PowerPC 2.03 specification. Remove remaining micro-operations helpers prototypes from op.c. Fix XER_BC field to be 7 bits long. Add power management support for PowerPC 603 & 604. Fix compilation warnings.
/*0  */ PPC_OP(divw)                                            // (3) 0.07407
/*2  */ {                                                       // (7) 0.009259
/*4  */     if ((Ts0 == INT32_MIN && Ts1 == -1) || Ts1 == 0) {  // (0) 0.2407
/*6  */         T0 = (int32_t)((-1) * (T0 >> 31));              // (1) 0.2407
/*8  */     } else {                                            // (4) 0.05556
/*10 */         T0 = (Ts0 / Ts1);                               // (2) 0.1574
/*12 */     }                                                   // (6) 0.03704
/*14 */     RETURN();                                           // (5) 0.05556
/*16 */ }                                                       // (8) 0.009259
