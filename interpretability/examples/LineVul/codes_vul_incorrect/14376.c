// commit message qemu@7d1b0095bf (target=1, prob=0.27876407, correct=False): target-arm: Remove ad-hoc leak checking code
/*0  */ static inline void gen_arm_shift_im(TCGv var, int shiftop, int shift, int flags)  // (5) 0.05078
/*2  */ {                                                                                 // (29) 0.001953
/*4  */     switch (shiftop) {                                                            // (24) 0.01758
/*6  */     case 0: /* LSL */                                                             // (20) 0.01953
/*8  */         if (shift != 0) {                                                         // (13) 0.02734
/*10 */             if (flags)                                                            // (10) 0.0293
/*12 */                 shifter_out_im(var, 32 - shift);                                  // (2) 0.05469
/*14 */             tcg_gen_shli_i32(var, var, shift);                                    // (3) 0.05469
/*16 */         }                                                                         // (27) 0.01562
/*18 */         break;                                                                    // (25) 0.01758
/*20 */     case 1: /* LSR */                                                             // (21) 0.01953
/*22 */         if (shift == 0) {                                                         // (14) 0.02734
/*24 */             if (flags) {                                                          // (9) 0.03125
/*26 */                 tcg_gen_shri_i32(var, var, 31);                                   // (0) 0.0625
/*28 */                 gen_set_CF(var);                                                  // (8) 0.04492
/*30 */             }                                                                     // (18) 0.02344
/*32 */             tcg_gen_movi_i32(var, 0);                                             // (6) 0.05078
/*34 */         } else {                                                                  // (22) 0.01953
/*36 */             if (flags)                                                            // (11) 0.0293
/*38 */                 shifter_out_im(var, shift - 1);                                   // (1) 0.05469
/*40 */             tcg_gen_shri_i32(var, var, shift);                                    // (4) 0.05469
/*42 */         }                                                                         // (28) 0.01562
/*44 */         break;                                                                    // (26) 0.01758
/*46 */     case 2: /* ASR */                                                             // (23) 0.01953
/*48 */         if (shift == 0)                                                           // (15) 0.02539
/*50 */             shift = 32;                                                           // (12) 0.0293
/*52 */         if (flags)                                                                // (19) 0.02148
/*54 */             shifter_out_im(var, shift - 1);                                       // (7) 0.04688
/*56 */         if (shift == 32)                                                          // (16) 0.02539
/*58 */           shift = 31;                                                             // (17) 0.02539
/*60 */         tcg_gen_sari_i32(var, var, shift);                                        // 0.0
/*62 */         break;                                                                    // 0.0
/*64 */     case 3: /* ROR/RRX */                                                         // 0.0
/*66 */         if (shift != 0) {                                                         // 0.0
/*68 */             if (flags)                                                            // 0.0
/*70 */                 shifter_out_im(var, shift - 1);                                   // 0.0
/*72 */             tcg_gen_rotri_i32(var, var, shift); break;                            // 0.0
/*74 */         } else {                                                                  // 0.0
/*76 */             TCGv tmp = load_cpu_field(CF);                                        // 0.0
/*78 */             if (flags)                                                            // 0.0
/*80 */                 shifter_out_im(var, 0);                                           // 0.0
/*82 */             tcg_gen_shri_i32(var, var, 1);                                        // 0.0
/*84 */             tcg_gen_shli_i32(tmp, tmp, 31);                                       // 0.0
/*86 */             tcg_gen_or_i32(var, var, tmp);                                        // 0.0
/*88 */             dead_tmp(tmp);                                                        // 0.0
/*90 */         }                                                                         // 0.0
/*92 */     }                                                                             // 0.0
/*94 */ };                                                                                // 0.0
