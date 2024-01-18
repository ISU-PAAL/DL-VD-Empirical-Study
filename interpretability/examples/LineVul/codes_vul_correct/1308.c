// commit message qemu@7d1b0095bf (target=1, prob=0.9977652, correct=True): target-arm: Remove ad-hoc leak checking code
/*0  */ static void gen_set_CF_bit31(TCGv var)  // (1) 0.1975
/*2  */ {                                       // (5) 0.01235
/*4  */     TCGv tmp = new_tmp();               // (2) 0.1481
/*6  */     tcg_gen_shri_i32(tmp, var, 31);     // (0) 0.2469
/*8  */     gen_set_CF(tmp);                    // (3) 0.1358
/*10 */     dead_tmp(tmp);                      // (4) 0.1111
/*12 */ }                                       // (6) 0.01235
