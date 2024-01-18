// commit message qemu@42a268c241 (target=0, prob=0.24674867, correct=True): tcg: Change translator-side labels to a pointer
/*0  */ static void gen_store_v10_conditional(DisasContext *dc, TCGv addr, TCGv val,  // (8) 0.05469
/*2  */                        unsigned int size, int mem_index)                      // (1) 0.06055
/*4  */ {                                                                             // (25) 0.001953
/*6  */     int l1 = gen_new_label();                                                 // (14) 0.02539
/*8  */     TCGv taddr = tcg_temp_local_new();                                        // (9) 0.03516
/*10 */     TCGv tval = tcg_temp_local_new();                                         // (10) 0.03516
/*12 */     TCGv t1 = tcg_temp_local_new();                                           // (11) 0.03516
/*14 */     dc->postinc = 0;                                                          // (21) 0.01953
/*16 */     cris_evaluate_flags(dc);                                                  // (20) 0.02148
/*20 */     tcg_gen_mov_tl(taddr, addr);                                              // (12) 0.03516
/*22 */     tcg_gen_mov_tl(tval, val);                                                // (13) 0.03516
/*26 */     /* Store only if F flag isn't set */                                      // (15) 0.02539
/*28 */     tcg_gen_andi_tl(t1, cpu_PR[PR_CCS], F_FLAG_V10);                          // (2) 0.06055
/*30 */     tcg_gen_brcondi_tl(TCG_COND_NE, t1, 0, l1);                               // (3) 0.05859
/*32 */     if (size == 1) {                                                          // (22) 0.01953
/*34 */         tcg_gen_qemu_st8(tval, taddr, mem_index);                             // (4) 0.05664
/*36 */     } else if (size == 2) {                                                   // (18) 0.02344
/*38 */         tcg_gen_qemu_st16(tval, taddr, mem_index);                            // (5) 0.05664
/*40 */     } else {                                                                  // (23) 0.01172
/*42 */         tcg_gen_qemu_st32(tval, taddr, mem_index);                            // (6) 0.05664
/*44 */     }                                                                         // (24) 0.007812
/*46 */     gen_set_label(l1);                                                        // (19) 0.02344
/*48 */     tcg_gen_shri_tl(t1, t1, 1);  /* shift F to P position */                  // (7) 0.05664
/*50 */     tcg_gen_or_tl(cpu_PR[PR_CCS], cpu_PR[PR_CCS], t1); /*P=F*/                // (0) 0.07422
/*52 */     tcg_temp_free(t1);                                                        // (16) 0.02539
/*54 */     tcg_temp_free(tval);                                                      // (17) 0.02539
/*56 */     tcg_temp_free(taddr);                                                     // 0.0
/*58 */ }                                                                             // 0.0
