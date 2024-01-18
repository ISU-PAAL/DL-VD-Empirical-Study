// commit message qemu@90e496386f (target=0, prob=0.09443116, correct=True): target-arm: A64: Add assertion that FP access was checked
/*0  */ static void write_vec_element(DisasContext *s, TCGv_i64 tcg_src, int destidx,  // (5) 0.08499
/*2  */                               int element, TCGMemOp memop)                     // (0) 0.1105
/*4  */ {                                                                              // (19) 0.002833
/*6  */     int vect_off = vec_reg_offset(destidx, element, memop & MO_SIZE);          // (6) 0.07932
/*8  */     switch (memop) {                                                           // (8) 0.0255
/*10 */     case MO_8:                                                                 // (13) 0.02266
/*12 */         tcg_gen_st8_i64(tcg_src, cpu_env, vect_off);                           // (1) 0.09065
/*14 */         break;                                                                 // (9) 0.0255
/*16 */     case MO_16:                                                                // (14) 0.02266
/*18 */         tcg_gen_st16_i64(tcg_src, cpu_env, vect_off);                          // (2) 0.09065
/*20 */         break;                                                                 // (10) 0.0255
/*22 */     case MO_32:                                                                // (15) 0.02266
/*24 */         tcg_gen_st32_i64(tcg_src, cpu_env, vect_off);                          // (3) 0.09065
/*26 */         break;                                                                 // (11) 0.0255
/*28 */     case MO_64:                                                                // (16) 0.02266
/*30 */         tcg_gen_st_i64(tcg_src, cpu_env, vect_off);                            // (4) 0.08782
/*32 */         break;                                                                 // (12) 0.0255
/*34 */     default:                                                                   // (17) 0.01416
/*36 */         g_assert_not_reached();                                                // (7) 0.04533
/*38 */     }                                                                          // (18) 0.01133
/*40 */ }                                                                              // (20) 0.002833
