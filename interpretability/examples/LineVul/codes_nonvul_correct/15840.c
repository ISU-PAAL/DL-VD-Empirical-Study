// commit message qemu@a7812ae412 (target=0, prob=0.020252407, correct=True): TCG variable type checking.
/*0  */ static always_inline void gen_cmp(TCGCond cond,            // (9) 0.03256
/*2  */                                   int ra, int rb, int rc,  // (1) 0.1
/*4  */                                   int islit, uint8_t lit)  // (0) 0.1
/*6  */ {                                                          // (23) 0.002326
/*8  */     int l1, l2;                                            // (16) 0.02326
/*10 */     TCGv tmp;                                              // (18) 0.0186
/*14 */     if (unlikely(rc == 31))                                // (11) 0.02791
/*16 */     return;                                                // (20) 0.01163
/*20 */     l1 = gen_new_label();                                  // (12) 0.02791
/*22 */     l2 = gen_new_label();                                  // (13) 0.02791
/*26 */     if (ra != 31) {                                        // (17) 0.02326
/*28 */         tmp = tcg_temp_new(TCG_TYPE_I64);                  // (5) 0.05581
/*30 */         tcg_gen_mov_i64(tmp, cpu_ir[ra]);                  // (4) 0.06047
/*32 */     } else                                                 // (21) 0.01163
/*34 */         tmp = tcg_const_i64(0);                            // (8) 0.04419
/*36 */     if (islit)                                             // (19) 0.0186
/*38 */         tcg_gen_brcondi_i64(cond, tmp, lit, l1);           // (3) 0.06512
/*40 */     else                                                   // (22) 0.009302
/*42 */         tcg_gen_brcond_i64(cond, tmp, cpu_ir[rb], l1);     // (2) 0.07209
/*46 */     tcg_gen_movi_i64(cpu_ir[rc], 0);                       // (6) 0.05116
/*48 */     tcg_gen_br(l2);                                        // (10) 0.03023
/*50 */     gen_set_label(l1);                                     // (14) 0.02791
/*52 */     tcg_gen_movi_i64(cpu_ir[rc], 1);                       // (7) 0.05116
/*54 */     gen_set_label(l2);                                     // (15) 0.02791
/*56 */ }                                                          // (24) 0.002326
