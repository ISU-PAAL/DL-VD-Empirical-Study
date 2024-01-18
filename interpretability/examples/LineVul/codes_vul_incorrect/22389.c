// commit message qemu@d9bce9d99f (target=1, prob=0.008609518, correct=False): Make it safe to use 64 bits GPR and/or 64 bits host registers. For "symetry", add 64 bits versions of all modified functions. As a side effect, add a lot of code provision for PowerPC 64 support. Move overflow and carry checks in common routines for simple cases. Add isel and popcntb instructions from PowerPC 2.03 specification. Remove remaining micro-operations helpers prototypes from op.c. Fix XER_BC field to be 7 bits long. Add power management support for PowerPC 603 & 604. Fix compilation warnings.
/*0 */ static inline void RET_STOP (DisasContext *ctx)  // (2) 0.2373
/*2 */ {                                                // (3) 0.01695
/*4 */     gen_op_update_nip((ctx)->nip);               // (0) 0.3051
/*6 */     ctx->exception = EXCP_MTMSR;                 // (1) 0.2712
/*8 */ }                                                // (4) 0.01695
