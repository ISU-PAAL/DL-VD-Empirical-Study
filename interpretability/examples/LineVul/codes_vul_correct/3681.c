// commit message qemu@7d1b0095bf (target=1, prob=0.987398, correct=True): target-arm: Remove ad-hoc leak checking code
/*0  */ static void gen_storeq_reg(DisasContext *s, int rlow, int rhigh, TCGv_i64 val)  // (0) 0.189
/*2  */ {                                                                               // (9) 0.006098
/*4  */     TCGv tmp;                                                                   // (8) 0.04878
/*6  */     tmp = new_tmp();                                                            // (6) 0.05488
/*8  */     tcg_gen_trunc_i64_i32(tmp, val);                                            // (1) 0.128
/*10 */     store_reg(s, rlow, tmp);                                                    // (5) 0.08537
/*12 */     tmp = new_tmp();                                                            // (7) 0.05488
/*14 */     tcg_gen_shri_i64(val, val, 32);                                             // (3) 0.122
/*16 */     tcg_gen_trunc_i64_i32(tmp, val);                                            // (2) 0.128
/*18 */     store_reg(s, rhigh, tmp);                                                   // (4) 0.08537
/*20 */ }                                                                               // (10) 0.006098
