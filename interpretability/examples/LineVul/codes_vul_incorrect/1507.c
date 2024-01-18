// commit message qemu@ffe30937c8 (target=1, prob=0.37573564, correct=False): target-ppc: Compute addition overflow without branches
/*0   */ static inline void gen_op_arith_add(DisasContext *ctx, TCGv ret, TCGv arg1,  // (3) 0.05664
/*2   */                                     TCGv arg2, int add_ca, int compute_ca,   // (0) 0.09961
/*4   */                                     int compute_ov)                          // (1) 0.07812
/*6   */ {                                                                            // (26) 0.001953
/*8   */     TCGv t0, t1;                                                             // (14) 0.02344
/*12  */     if ((!compute_ca && !compute_ov) ||                                      // (12) 0.03516
/*14  */         (!TCGV_EQUAL(ret,arg1) && !TCGV_EQUAL(ret, arg2)))  {                // (2) 0.07031
/*16  */         t0 = ret;                                                            // (15) 0.02344
/*18  */     } else {                                                                 // (20) 0.01172
/*20  */         t0 = tcg_temp_local_new();                                           // (10) 0.03711
/*22  */     }                                                                        // (22) 0.007812
/*26  */     if (add_ca) {                                                            // (19) 0.01953
/*28  */         t1 = tcg_temp_local_new();                                           // (11) 0.03711
/*30  */         tcg_gen_mov_tl(t1, cpu_ca);                                          // (4) 0.04688
/*32  */     } else {                                                                 // (21) 0.01172
/*34  */         TCGV_UNUSED(t1);                                                     // (13) 0.0332
/*36  */     }                                                                        // (23) 0.007812
/*40  */     if (compute_ca) {                                                        // (16) 0.02148
/*42  */         /* Start with XER CA disabled, the most likely case */               // (9) 0.03906
/*44  */         tcg_gen_movi_tl(cpu_ca, 0);                                          // (5) 0.04492
/*46  */     }                                                                        // (24) 0.007812
/*48  */     if (compute_ov) {                                                        // (17) 0.02148
/*50  */         /* Start with XER OV disabled, the most likely case */               // (7) 0.04102
/*52  */         tcg_gen_movi_tl(cpu_ov, 0);                                          // (6) 0.04492
/*54  */     }                                                                        // (25) 0.007812
/*58  */     tcg_gen_add_tl(t0, arg1, arg2);                                          // (8) 0.04102
/*62  */     if (compute_ca) {                                                        // (18) 0.02148
/*64  */         gen_op_arith_compute_ca(ctx, t0, arg1, 0);                           // 0.0
/*66  */     }                                                                        // 0.0
/*68  */     if (add_ca) {                                                            // 0.0
/*70  */         tcg_gen_add_tl(t0, t0, t1);                                          // 0.0
/*72  */         gen_op_arith_compute_ca(ctx, t0, t1, 0);                             // 0.0
/*74  */         tcg_temp_free(t1);                                                   // 0.0
/*76  */     }                                                                        // 0.0
/*78  */     if (compute_ov) {                                                        // 0.0
/*80  */         gen_op_arith_compute_ov(ctx, t0, arg1, arg2, 0);                     // 0.0
/*82  */     }                                                                        // 0.0
/*86  */     if (unlikely(Rc(ctx->opcode) != 0))                                      // 0.0
/*88  */         gen_set_Rc0(ctx, t0);                                                // 0.0
/*92  */     if (!TCGV_EQUAL(t0, ret)) {                                              // 0.0
/*94  */         tcg_gen_mov_tl(ret, t0);                                             // 0.0
/*96  */         tcg_temp_free(t0);                                                   // 0.0
/*98  */     }                                                                        // 0.0
/*100 */ }                                                                            // 0.0
