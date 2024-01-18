// commit message qemu@eabb7b91b3 (target=0, prob=0.012585034, correct=True): tcg: use tcg_debug_assert instead of assert (fix performance regression)
/*0  */ static void tcg_out_mov(TCGContext *s, TCGType type, TCGReg ret, TCGReg arg)  // (0) 0.1535
/*2  */ {                                                                             // (11) 0.00495
/*4  */     uint8_t *old_code_ptr = s->code_ptr;                                      // (4) 0.09901
/*6  */     assert(ret != arg);                                                       // (8) 0.04455
/*8  */ #if TCG_TARGET_REG_BITS == 32                                                 // (5) 0.06931
/*10 */     tcg_out_op_t(s, INDEX_op_mov_i32);                                        // (1) 0.1238
/*12 */ #else                                                                         // (10) 0.009901
/*14 */     tcg_out_op_t(s, INDEX_op_mov_i64);                                        // (2) 0.1238
/*16 */ #endif                                                                        // (9) 0.009901
/*18 */     tcg_out_r(s, ret);                                                        // (6) 0.06931
/*20 */     tcg_out_r(s, arg);                                                        // (7) 0.06931
/*22 */     old_code_ptr[1] = s->code_ptr - old_code_ptr;                             // (3) 0.1188
/*24 */ }                                                                             // (12) 0.00495
