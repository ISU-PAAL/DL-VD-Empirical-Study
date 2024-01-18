// commit message qemu@eabb7b91b3 (target=0, prob=0.012023715, correct=True): tcg: use tcg_debug_assert instead of assert (fix performance regression)
/*0  */ static inline void tcg_out_ld(TCGContext *s, TCGType type, TCGReg ret,  // (3) 0.1204
/*2  */                               TCGReg arg1, intptr_t arg2)               // (0) 0.1944
/*4  */ {                                                                       // (10) 0.00463
/*6  */     int opi, opx;                                                       // (7) 0.0463
/*10 */     assert(TCG_TARGET_REG_BITS == 64 || type == TCG_TYPE_I32);          // (1) 0.1296
/*12 */     if (type == TCG_TYPE_I32) {                                         // (6) 0.07407
/*14 */         opi = LWZ, opx = LWZX;                                          // (4) 0.08796
/*16 */     } else {                                                            // (8) 0.02778
/*18 */         opi = LD, opx = LDX;                                            // (5) 0.08333
/*20 */     }                                                                   // (9) 0.01852
/*22 */     tcg_out_mem_long(s, opi, opx, ret, arg1, arg2);                     // (2) 0.1296
/*24 */ }                                                                       // (11) 0.00463
