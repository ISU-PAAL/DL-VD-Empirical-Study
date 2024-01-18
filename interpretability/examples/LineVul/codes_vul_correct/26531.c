// commit message qemu@7d1b0095bf (target=1, prob=0.9960394, correct=True): target-arm: Remove ad-hoc leak checking code
/*0  */ static TCGv_i64 gen_addq_msw(TCGv_i64 a, TCGv b)  // (0) 0.1718
/*2  */ {                                                 // (8) 0.006135
/*4  */     TCGv_i64 tmp64 = tcg_temp_new_i64();          // (1) 0.135
/*8  */     tcg_gen_extu_i32_i64(tmp64, b);               // (2) 0.135
/*10 */     dead_tmp(b);                                  // (6) 0.05521
/*12 */     tcg_gen_shli_i64(tmp64, tmp64, 32);           // (3) 0.135
/*14 */     tcg_gen_add_i64(a, tmp64, a);                 // (4) 0.1227
/*18 */     tcg_temp_free_i64(tmp64);                     // (5) 0.09816
/*20 */     return a;                                     // (7) 0.03681
/*22 */ }                                                 // (9) 0.006135
