// commit message qemu@7d1b0095bf (target=1, prob=0.9581193, correct=True): target-arm: Remove ad-hoc leak checking code
/*0  */ static void gen_addq_lo(DisasContext *s, TCGv_i64 val, int rlow)  // (0) 0.1534
/*2  */ {                                                                 // (10) 0.005682
/*4  */     TCGv_i64 tmp;                                                 // (7) 0.0625
/*6  */     TCGv tmp2;                                                    // (9) 0.05114
/*10 */     /* Load value and extend to 64 bits.  */                      // (6) 0.07955
/*12 */     tmp = tcg_temp_new_i64();                                     // (4) 0.08523
/*14 */     tmp2 = load_reg(s, rlow);                                     // (3) 0.08523
/*16 */     tcg_gen_extu_i32_i64(tmp, tmp2);                              // (1) 0.125
/*18 */     dead_tmp(tmp2);                                               // (8) 0.05682
/*20 */     tcg_gen_add_i64(val, val, tmp);                               // (2) 0.108
/*22 */     tcg_temp_free_i64(tmp);                                       // (5) 0.08523
/*24 */ }                                                                 // (11) 0.005682
