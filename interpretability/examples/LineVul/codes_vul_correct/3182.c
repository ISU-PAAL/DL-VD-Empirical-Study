// commit message qemu@e41029b378 (target=1, prob=0.5037726, correct=True): ppc: Don't update NIP in lswi/lswx/stswi/stswx
/*0  */ static void gen_lswi(DisasContext *ctx)                                        // (11) 0.03431
/*2  */ {                                                                              // (25) 0.002451
/*4  */     TCGv t0;                                                                   // (20) 0.02206
/*6  */     TCGv_i32 t1, t2;                                                           // (10) 0.03676
/*8  */     int nb = NB(ctx->opcode);                                                  // (12) 0.03431
/*10 */     int start = rD(ctx->opcode);                                               // (13) 0.03431
/*12 */     int ra = rA(ctx->opcode);                                                  // (14) 0.03431
/*14 */     int nr;                                                                    // (23) 0.01716
/*18 */     if (nb == 0)                                                               // (21) 0.02206
/*20 */         nb = 32;                                                               // (19) 0.02941
/*22 */     nr = (nb + 3) / 4;                                                         // (15) 0.03431
/*24 */     if (unlikely(lsw_reg_in_range(start, nr, ra))) {                           // (1) 0.06127
/*26 */         gen_inval_exception(ctx, POWERPC_EXCP_INVAL_LSWX);                     // (0) 0.07353
/*28 */         return;                                                                // (22) 0.02206
/*30 */     }                                                                          // (24) 0.009804
/*32 */     gen_set_access_type(ctx, ACCESS_INT);                                      // (4) 0.04412
/*34 */     /* NIP cannot be restored if the memory exception comes from an helper */  // (5) 0.04412
/*36 */     gen_update_nip(ctx, ctx->nip - 4);                                         // (3) 0.04902
/*38 */     t0 = tcg_temp_new();                                                       // (17) 0.03186
/*40 */     gen_addr_register(ctx, t0);                                                // (16) 0.03431
/*42 */     t1 = tcg_const_i32(nb);                                                    // (6) 0.03922
/*44 */     t2 = tcg_const_i32(start);                                                 // (7) 0.03922
/*46 */     gen_helper_lsw(cpu_env, t0, t1, t2);                                       // (2) 0.05882
/*48 */     tcg_temp_free(t0);                                                         // (18) 0.03186
/*50 */     tcg_temp_free_i32(t1);                                                     // (8) 0.03922
/*52 */     tcg_temp_free_i32(t2);                                                     // (9) 0.03922
/*54 */ }                                                                              // (26) 0.002451
