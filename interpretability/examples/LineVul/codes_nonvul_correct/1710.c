// commit message qemu@42a268c241 (target=0, prob=0.029325338, correct=True): tcg: Change translator-side labels to a pointer
/*0  */ static void gen_isel(DisasContext *ctx)                                      // (11) 0.03023
/*2  */ {                                                                            // (20) 0.002519
/*4  */     int l1, l2;                                                              // (17) 0.02519
/*6  */     uint32_t bi = rC(ctx->opcode);                                           // (5) 0.04282
/*8  */     uint32_t mask;                                                           // (18) 0.02267
/*10 */     TCGv_i32 t0;                                                             // (12) 0.03023
/*14 */     l1 = gen_new_label();                                                    // (13) 0.03023
/*16 */     l2 = gen_new_label();                                                    // (14) 0.03023
/*20 */     mask = 0x08 >> (bi & 0x03);                                              // (6) 0.0403
/*22 */     t0 = tcg_temp_new_i32();                                                 // (7) 0.0403
/*24 */     tcg_gen_andi_i32(t0, cpu_crf[bi >> 2], mask);                            // (4) 0.06801
/*26 */     tcg_gen_brcondi_i32(TCG_COND_EQ, t0, 0, l1);                             // (3) 0.0806
/*28 */     if (rA(ctx->opcode) == 0)                                                // (8) 0.0403
/*30 */         tcg_gen_movi_tl(cpu_gpr[rD(ctx->opcode)], 0);                        // (2) 0.08312
/*32 */     else                                                                     // (19) 0.01008
/*34 */         tcg_gen_mov_tl(cpu_gpr[rD(ctx->opcode)], cpu_gpr[rA(ctx->opcode)]);  // (0) 0.1134
/*36 */     tcg_gen_br(l2);                                                          // (10) 0.03275
/*38 */     gen_set_label(l1);                                                       // (15) 0.03023
/*40 */     tcg_gen_mov_tl(cpu_gpr[rD(ctx->opcode)], cpu_gpr[rB(ctx->opcode)]);      // (1) 0.1033
/*42 */     gen_set_label(l2);                                                       // (16) 0.03023
/*44 */     tcg_temp_free_i32(t0);                                                   // (9) 0.0403
/*46 */ }                                                                            // (21) 0.002519
