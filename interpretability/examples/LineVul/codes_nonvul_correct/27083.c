// commit message qemu@42a268c241 (target=0, prob=0.055594422, correct=True): tcg: Change translator-side labels to a pointer
/*0  */ static void disas_fp_ccomp(DisasContext *s, uint32_t insn)       // (2) 0.04492
/*2  */ {                                                                // (30) 0.001953
/*4  */     unsigned int mos, type, rm, cond, rn, op, nzcv;              // (4) 0.04297
/*6  */     TCGv_i64 tcg_flags;                                          // (21) 0.02734
/*8  */     int label_continue = -1;                                     // (24) 0.02148
/*12 */     mos = extract32(insn, 29, 3);                                // (17) 0.0293
/*14 */     type = extract32(insn, 22, 2); /* 0 = single, 1 = double */  // (1) 0.04687
/*16 */     rm = extract32(insn, 16, 5);                                 // (18) 0.0293
/*18 */     cond = extract32(insn, 12, 4);                               // (16) 0.0293
/*20 */     rn = extract32(insn, 5, 5);                                  // (15) 0.03125
/*22 */     op = extract32(insn, 4, 1);                                  // (19) 0.0293
/*24 */     nzcv = extract32(insn, 0, 4);                                // (10) 0.0332
/*28 */     if (mos || type > 1) {                                       // (22) 0.02344
/*30 */         unallocated_encoding(s);                                 // (14) 0.03125
/*32 */         return;                                                  // (25) 0.01758
/*34 */     }                                                            // (27) 0.007812
/*38 */     if (!fp_access_check(s)) {                                   // (20) 0.02734
/*40 */         return;                                                  // (26) 0.01758
/*42 */     }                                                            // (28) 0.007812
/*46 */     if (cond < 0x0e) { /* not always */                          // (11) 0.0332
/*48 */         int label_match = gen_new_label();                       // (8) 0.03516
/*50 */         label_continue = gen_new_label();                        // (12) 0.0332
/*52 */         arm_gen_test_cc(cond, label_match);                      // (6) 0.04102
/*54 */         /* nomatch: */                                           // (23) 0.02344
/*56 */         tcg_flags = tcg_const_i64(nzcv << 28);                   // (0) 0.04883
/*58 */         gen_set_nzcv(tcg_flags);                                 // (7) 0.03711
/*60 */         tcg_temp_free_i64(tcg_flags);                            // (5) 0.04297
/*62 */         tcg_gen_br(label_continue);                              // (9) 0.03516
/*64 */         gen_set_label(label_match);                              // (13) 0.0332
/*66 */     }                                                            // (29) 0.007812
/*70 */     handle_fp_compare(s, type, rn, rm, false, op);               // (3) 0.04492
/*74 */     if (cond < 0x0e) {                                           // 0.0
/*76 */         gen_set_label(label_continue);                           // 0.0
/*78 */     }                                                            // 0.0
/*80 */ }                                                                // 0.0
