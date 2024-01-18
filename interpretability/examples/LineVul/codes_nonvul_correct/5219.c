// commit message qemu@42a268c241 (target=0, prob=0.033653777, correct=True): tcg: Change translator-side labels to a pointer
/*0  */ static void gen_srlq(DisasContext *ctx)                   // (15) 0.02734
/*2  */ {                                                         // (24) 0.001953
/*4  */     int l1 = gen_new_label();                             // (16) 0.02539
/*6  */     int l2 = gen_new_label();                             // (17) 0.02539
/*8  */     TCGv t0 = tcg_temp_local_new();                       // (10) 0.03516
/*10 */     TCGv t1 = tcg_temp_local_new();                       // (11) 0.03516
/*12 */     TCGv t2 = tcg_temp_local_new();                       // (12) 0.03516
/*14 */     tcg_gen_andi_tl(t2, cpu_gpr[rB(ctx->opcode)], 0x1F);  // (0) 0.06641
/*16 */     tcg_gen_movi_tl(t1, 0xFFFFFFFF);                      // (7) 0.04102
/*18 */     tcg_gen_shr_tl(t2, t1, t2);                           // (8) 0.04102
/*20 */     tcg_gen_andi_tl(t0, cpu_gpr[rB(ctx->opcode)], 0x20);  // (1) 0.06445
/*22 */     tcg_gen_brcondi_tl(TCG_COND_EQ, t0, 0, l1);           // (5) 0.06055
/*24 */     gen_load_spr(t0, SPR_MQ);                             // (14) 0.03125
/*26 */     tcg_gen_and_tl(cpu_gpr[rA(ctx->opcode)], t0, t2);     // (2) 0.0625
/*28 */     tcg_gen_br(l2);                                       // (18) 0.02539
/*30 */     gen_set_label(l1);                                    // (22) 0.02344
/*32 */     tcg_gen_shr_tl(t0, cpu_gpr[rS(ctx->opcode)], t2);     // (3) 0.0625
/*34 */     tcg_gen_and_tl(t0, t0, t2);                           // (9) 0.04102
/*36 */     gen_load_spr(t1, SPR_MQ);                             // (13) 0.03125
/*38 */     tcg_gen_andc_tl(t1, t1, t2);                          // (6) 0.04297
/*40 */     tcg_gen_or_tl(cpu_gpr[rA(ctx->opcode)], t0, t1);      // (4) 0.0625
/*42 */     gen_set_label(l2);                                    // (23) 0.02344
/*44 */     tcg_temp_free(t0);                                    // (19) 0.02539
/*46 */     tcg_temp_free(t1);                                    // (20) 0.02539
/*48 */     tcg_temp_free(t2);                                    // (21) 0.02539
/*50 */     if (unlikely(Rc(ctx->opcode) != 0))                   // 0.0
/*52 */         gen_set_Rc0(ctx, cpu_gpr[rA(ctx->opcode)]);       // 0.0
/*54 */ }                                                         // 0.0
