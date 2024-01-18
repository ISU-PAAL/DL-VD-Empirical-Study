// commit message qemu@d9bce9d99f (target=1, prob=0.99846256, correct=True): Make it safe to use 64 bits GPR and/or 64 bits host registers. For "symetry", add 64 bits versions of all modified functions. As a side effect, add a lot of code provision for PowerPC 64 support. Move overflow and carry checks in common routines for simple cases. Add isel and popcntb instructions from PowerPC 2.03 specification. Remove remaining micro-operations helpers prototypes from op.c. Fix XER_BC field to be 7 bits long. Add power management support for PowerPC 603 & 604. Fix compilation warnings.
/*0 */ PPC_OP(extsh)                        // (1) 0.1739
/*2 */ {                                    // (3) 0.02174
/*4 */     T0 = (int32_t)((int16_t)(Ts0));  // (0) 0.4565
/*6 */     RETURN();                        // (2) 0.1304
/*8 */ }                                    // (4) 0.02174
