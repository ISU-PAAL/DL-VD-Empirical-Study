// commit message qemu@7d1b0095bf (target=1, prob=0.3225505, correct=False): target-arm: Remove ad-hoc leak checking code
/*0  */ static void gen_neon_trn_u16(TCGv t0, TCGv t1)  // (0) 0.1016
/*2  */ {                                               // (13) 0.004065
/*4  */     TCGv rd, tmp;                               // (8) 0.04472
/*8  */     rd = new_tmp();                             // (9) 0.04065
/*10 */     tmp = new_tmp();                            // (10) 0.03659
/*14 */     tcg_gen_shli_i32(rd, t0, 16);               // (5) 0.08537
/*16 */     tcg_gen_andi_i32(tmp, t1, 0xffff);          // (2) 0.08943
/*18 */     tcg_gen_or_i32(rd, rd, tmp);                // (6) 0.0813
/*20 */     tcg_gen_shri_i32(t1, t1, 16);               // (3) 0.08943
/*22 */     tcg_gen_andi_i32(tmp, t0, 0xffff0000);      // (1) 0.0935
/*24 */     tcg_gen_or_i32(t1, t1, tmp);                // (4) 0.08537
/*26 */     tcg_gen_mov_i32(t0, rd);                    // (7) 0.0813
/*30 */     dead_tmp(tmp);                              // (11) 0.03659
/*32 */     dead_tmp(rd);                               // (12) 0.03659
/*34 */ }                                               // (14) 0.004065
