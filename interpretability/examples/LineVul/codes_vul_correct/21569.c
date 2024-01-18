// commit message qemu@d9bce9d99f (target=1, prob=0.9984388, correct=True): Make it safe to use 64 bits GPR and/or 64 bits host registers. For "symetry", add 64 bits versions of all modified functions. As a side effect, add a lot of code provision for PowerPC 64 support. Move overflow and carry checks in common routines for simple cases. Add isel and popcntb instructions from PowerPC 2.03 specification. Remove remaining micro-operations helpers prototypes from op.c. Fix XER_BC field to be 7 bits long. Add power management support for PowerPC 603 & 604. Fix compilation warnings.
/*0  */ void OPPROTO op_POWER_doz (void)  // (1) 0.1818
/*2  */ {                                 // (6) 0.01299
/*4  */     if (Ts1 > Ts0)                // (3) 0.1429
/*6  */         T0 = T1 - T0;             // (0) 0.2078
/*8  */     else                          // (5) 0.05195
/*10 */         T0 = 0;                   // (2) 0.1558
/*12 */     RETURN();                     // (4) 0.07792
/*14 */ }                                 // (7) 0.01299
