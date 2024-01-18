// commit message qemu@a7812ae412 (target=0, prob=0.9965044, correct=False): TCG variable type checking.
/*0  */ static void gen_storeq_reg(DisasContext *s, int rlow, int rhigh, TCGv val)  // (0) 0.1739
/*2  */ {                                                                           // (9) 0.006211
/*4  */     TCGv tmp;                                                               // (8) 0.04969
/*6  */     tmp = new_tmp();                                                        // (6) 0.0559
/*8  */     tcg_gen_trunc_i64_i32(tmp, val);                                        // (1) 0.1304
/*10 */     store_reg(s, rlow, tmp);                                                // (5) 0.08696
/*12 */     tmp = new_tmp();                                                        // (7) 0.0559
/*14 */     tcg_gen_shri_i64(val, val, 32);                                         // (3) 0.1242
/*16 */     tcg_gen_trunc_i64_i32(tmp, val);                                        // (2) 0.1304
/*18 */     store_reg(s, rhigh, tmp);                                               // (4) 0.08696
/*20 */ }                                                                           // (10) 0.006211
