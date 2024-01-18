// commit message qemu@42a268c241 (target=0, prob=0.5771602, correct=False): tcg: Change translator-side labels to a pointer
/*0  */ static void dec_modu(DisasContext *dc)                                          // (8) 0.04167
/*2  */ {                                                                               // (14) 0.003205
/*4  */     int l1;                                                                     // (12) 0.02244
/*8  */     LOG_DIS("modu r%d, r%d, %d\n", dc->r2, dc->r0, dc->r1);                     // (1) 0.1186
/*12 */     if (!(dc->features & LM32_FEATURE_DIVIDE)) {                                // (6) 0.0641
/*14 */         qemu_log_mask(LOG_GUEST_ERROR, "hardware divider is not available\n");  // (3) 0.1058
/*16 */         t_gen_illegal_insn(dc);                                                 // (7) 0.05769
/*18 */         return;                                                                 // (11) 0.02885
/*20 */     }                                                                           // (13) 0.01282
/*24 */     l1 = gen_new_label();                                                       // (9) 0.03846
/*26 */     tcg_gen_brcondi_tl(TCG_COND_NE, cpu_R[dc->r1], 0, l1);                      // (2) 0.1154
/*28 */     tcg_gen_movi_tl(cpu_pc, dc->pc);                                            // (5) 0.06731
/*30 */     t_gen_raise_exception(dc, EXCP_DIVIDE_BY_ZERO);                             // (4) 0.08013
/*32 */     gen_set_label(l1);                                                          // (10) 0.03846
/*34 */     tcg_gen_remu_tl(cpu_R[dc->r2], cpu_R[dc->r0], cpu_R[dc->r1]);               // (0) 0.1282
/*36 */ }                                                                               // (15) 0.003205
