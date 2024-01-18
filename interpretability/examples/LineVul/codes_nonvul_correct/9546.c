// commit message qemu@42a268c241 (target=0, prob=0.032370087, correct=True): tcg: Change translator-side labels to a pointer
/*0  */ static inline void gen_branch_a(DisasContext *dc, target_ulong pc1,  // (3) 0.1168
/*2  */                                 target_ulong pc2, TCGv r_cond)       // (0) 0.2284
/*4  */ {                                                                    // (8) 0.005076
/*6  */     int l1;                                                          // (7) 0.03553
/*10 */     l1 = gen_new_label();                                            // (5) 0.06091
/*14 */     tcg_gen_brcondi_tl(TCG_COND_EQ, r_cond, 0, l1);                  // (1) 0.1624
/*18 */     gen_goto_tb(dc, 0, pc2, pc1);                                    // (4) 0.1066
/*22 */     gen_set_label(l1);                                               // (6) 0.06091
/*24 */     gen_goto_tb(dc, 1, pc2 + 4, pc2 + 8);                            // (2) 0.1269
/*26 */ }                                                                    // (9) 0.005076
