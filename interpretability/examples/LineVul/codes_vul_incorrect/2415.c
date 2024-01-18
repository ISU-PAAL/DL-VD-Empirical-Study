// commit message qemu@fae38221e7 (target=1, prob=0.17664878, correct=False): target-cris/translate.c: fix out of bounds read
/*0  */ static inline void t_gen_mov_preg_TN(DisasContext *dc, int r, TCGv tn)  // (0) 0.08
/*2  */ {                                                                       // (19) 0.002667
/*4  */     if (r < 0 || r > 15) {                                              // (12) 0.03733
/*6  */         fprintf(stderr, "wrong register write $p%d\n", r);              // (4) 0.072
/*8  */     }                                                                   // (17) 0.01067
/*10 */     if (r == PR_BZ || r == PR_WZ || r == PR_DZ) {                       // (6) 0.072
/*12 */         return;                                                         // (13) 0.024
/*14 */     } else if (r == PR_SRS) {                                           // (11) 0.04
/*16 */         tcg_gen_andi_tl(cpu_PR[r], tn, 3);                              // (5) 0.072
/*18 */     } else {                                                            // (16) 0.016
/*20 */         if (r == PR_PID) {                                              // (10) 0.04533
/*22 */             gen_helper_tlb_flush_pid(cpu_env, tn);                      // (1) 0.08
/*24 */         }                                                               // (14) 0.02133
/*26 */         if (dc->tb_flags & S_FLAG && r == PR_SPC) {                     // (2) 0.07467
/*28 */             gen_helper_spc_write(cpu_env, tn);                          // (3) 0.07467
/*30 */         } else if (r == PR_CCS) {                                       // (9) 0.05067
/*32 */             dc->cpustate_changed = 1;                                   // (8) 0.056
/*34 */         }                                                               // (15) 0.02133
/*36 */         tcg_gen_mov_tl(cpu_PR[r], tn);                                  // (7) 0.06933
/*38 */     }                                                                   // (18) 0.01067
/*40 */ }                                                                       // (20) 0.002667
