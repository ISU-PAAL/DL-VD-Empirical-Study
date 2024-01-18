// commit message qemu@a7812ae412 (target=0, prob=0.99592566, correct=False): TCG variable type checking.
/*0  */ static inline void gen_neon_widen(TCGv dest, TCGv src, int size, int u)  // (6) 0.08438
/*2  */ {                                                                        // (17) 0.003125
/*4  */     if (u) {                                                             // (12) 0.025
/*6  */         switch (size) {                                                  // (7) 0.0375
/*8  */         case 0: gen_helper_neon_widen_u8(dest, src); break;              // (0) 0.09375
/*10 */         case 1: gen_helper_neon_widen_u16(dest, src); break;             // (2) 0.09375
/*12 */         case 2: tcg_gen_extu_i32_i64(dest, src); break;                  // (1) 0.09375
/*14 */         default: abort();                                                // (9) 0.03438
/*16 */         }                                                                // (13) 0.025
/*18 */     } else {                                                             // (15) 0.01875
/*20 */         switch (size) {                                                  // (8) 0.0375
/*22 */         case 0: gen_helper_neon_widen_s8(dest, src); break;              // (3) 0.09375
/*24 */         case 1: gen_helper_neon_widen_s16(dest, src); break;             // (4) 0.09375
/*26 */         case 2: tcg_gen_ext_i32_i64(dest, src); break;                   // (5) 0.09063
/*28 */         default: abort();                                                // (10) 0.03438
/*30 */         }                                                                // (14) 0.025
/*32 */     }                                                                    // (16) 0.0125
/*34 */     dead_tmp(src);                                                       // (11) 0.02813
/*36 */ }                                                                        // (18) 0.003125
