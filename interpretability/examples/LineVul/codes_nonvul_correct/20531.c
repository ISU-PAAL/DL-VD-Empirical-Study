// commit message qemu@a7812ae412 (target=0, prob=0.027110437, correct=True): TCG variable type checking.
/*0  */ static always_inline void gen_ext_h(void (*tcg_gen_ext_i64)(TCGv t0, TCGv t1),   // (4) 0.06836
/*2  */                                     int ra, int rb, int rc,                      // (1) 0.08789
/*4  */                                     int islit, uint8_t lit)                      // (2) 0.08789
/*6  */ {                                                                                // (19) 0.001953
/*8  */     if (unlikely(rc == 31))                                                      // (14) 0.02344
/*10 */         return;                                                                  // (18) 0.01758
/*14 */     if (ra != 31) {                                                              // (16) 0.01953
/*16 */         if (islit) {                                                             // (13) 0.02539
/*18 */             if (lit != 0)                                                        // (12) 0.0332
/*20 */                 tcg_gen_shli_i64(cpu_ir[rc], cpu_ir[ra], 64 - ((lit & 7) * 8));  // (0) 0.09375
/*22 */             else                                                                 // (15) 0.02344
/*24 */                 tcg_gen_mov_i64(cpu_ir[rc], cpu_ir[ra]);                         // (3) 0.07422
/*26 */         } else {                                                                 // (17) 0.01953
/*28 */             TCGv tmp1, tmp2;                                                     // (11) 0.03906
/*30 */             tmp1 = tcg_temp_new(TCG_TYPE_I64);                                   // (8) 0.05664
/*32 */             tcg_gen_andi_i64(tmp1, cpu_ir[rb], 7);                               // (5) 0.0625
/*34 */             tcg_gen_shli_i64(tmp1, tmp1, 3);                                     // (6) 0.05859
/*36 */             tmp2 = tcg_const_i64(64);                                            // (9) 0.04688
/*38 */             tcg_gen_sub_i64(tmp1, tmp2, tmp1);                                   // (7) 0.05859
/*40 */             tcg_temp_free(tmp2);                                                 // (10) 0.04102
/*42 */             tcg_gen_shl_i64(cpu_ir[rc], cpu_ir[ra], tmp1);                       // 0.0
/*44 */             tcg_temp_free(tmp1);                                                 // 0.0
/*46 */         }                                                                        // 0.0
/*48 */         if (tcg_gen_ext_i64)                                                     // 0.0
/*50 */             tcg_gen_ext_i64(cpu_ir[rc], cpu_ir[rc]);                             // 0.0
/*52 */     } else                                                                       // 0.0
/*54 */         tcg_gen_movi_i64(cpu_ir[rc], 0);                                         // 0.0
/*56 */ }                                                                                // 0.0
