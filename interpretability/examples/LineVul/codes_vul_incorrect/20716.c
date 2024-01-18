// commit message qemu@d9bce9d99f (target=1, prob=0.011170643, correct=False): Make it safe to use 64 bits GPR and/or 64 bits host registers. For "symetry", add 64 bits versions of all modified functions. As a side effect, add a lot of code provision for PowerPC 64 support. Move overflow and carry checks in common routines for simple cases. Add isel and popcntb instructions from PowerPC 2.03 specification. Remove remaining micro-operations helpers prototypes from op.c. Fix XER_BC field to be 7 bits long. Add power management support for PowerPC 603 & 604. Fix compilation warnings.
/*0  */ void ppc_store_xer (CPUPPCState *env, uint32_t value)  // (0) 0.1538
/*2  */ {                                                      // (6) 0.006993
/*4  */     xer_so = (value >> XER_SO) & 0x01;                 // (3) 0.1469
/*6  */     xer_ov = (value >> XER_OV) & 0x01;                 // (4) 0.1469
/*8  */     xer_ca = (value >> XER_CA) & 0x01;                 // (5) 0.1469
/*10 */     xer_cmp = (value >> XER_CMP) & 0xFF;               // (1) 0.1538
/*12 */     xer_bc = (value >> XER_BC) & 0x3F;                 // (2) 0.1538
/*14 */ }                                                      // (7) 0.006993
