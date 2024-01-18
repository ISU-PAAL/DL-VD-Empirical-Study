// commit message qemu@d9bce9d99f (target=1, prob=0.99850094, correct=True): Make it safe to use 64 bits GPR and/or 64 bits host registers. For "symetry", add 64 bits versions of all modified functions. As a side effect, add a lot of code provision for PowerPC 64 support. Move overflow and carry checks in common routines for simple cases. Add isel and popcntb instructions from PowerPC 2.03 specification. Remove remaining micro-operations helpers prototypes from op.c. Fix XER_BC field to be 7 bits long. Add power management support for PowerPC 603 & 604. Fix compilation warnings.
/*0  */ PPC_OP(slw)             // (3) 0.1
/*2  */ {                       // (7) 0.0125
/*4  */     if (T1 & 0x20) {    // (1) 0.1625
/*6  */         T0 = 0;         // (2) 0.15
/*8  */     } else {            // (5) 0.075
/*10 */         T0 = T0 << T1;  // (0) 0.2
/*12 */     }                   // (6) 0.05
/*14 */     RETURN();           // (4) 0.075
/*16 */ }                       // (8) 0.0125
