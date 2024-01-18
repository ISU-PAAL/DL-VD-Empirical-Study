// commit message qemu@36c6711bbe (target=1, prob=0.24608831, correct=False): target-mips: allow microMIPS SWP and SDP to have RD equal to BASE
/*0   */ static void gen_ldst_pair (DisasContext *ctx, uint32_t opc, int rd,           // (2) 0.05078
/*2   */                            int base, int16_t offset)                          // (0) 0.06836
/*4   */ {                                                                             // (27) 0.001953
/*6   */     const char *opn = "ldst_pair";                                            // (16) 0.0293
/*8   */     TCGv t0, t1;                                                              // (20) 0.02344
/*12  */     if (ctx->hflags & MIPS_HFLAG_BMASK || rd == 31 || rd == base) {           // (1) 0.06055
/*14  */         generate_exception(ctx, EXCP_RI);                                     // (13) 0.03711
/*16  */         return;                                                               // (21) 0.01758
/*18  */     }                                                                         // (26) 0.007812
/*22  */     t0 = tcg_temp_new();                                                      // (18) 0.02539
/*24  */     t1 = tcg_temp_new();                                                      // (19) 0.02539
/*28  */     gen_base_offset_addr(ctx, t0, base, offset);                              // (10) 0.03906
/*32  */     switch (opc) {                                                            // (22) 0.01758
/*34  */     case LWP:                                                                 // (24) 0.01367
/*36  */         save_cpu_state(ctx, 0);                                               // (14) 0.0332
/*38  */         op_ld_lw(t1, t0, ctx);                                                // (4) 0.04492
/*40  */         gen_store_gpr(t1, rd);                                                // (11) 0.03906
/*42  */         tcg_gen_movi_tl(t1, 4);                                               // (6) 0.04297
/*44  */         gen_op_addr_add(ctx, t0, t0, t1);                                     // (3) 0.05078
/*46  */         op_ld_lw(t1, t0, ctx);                                                // (5) 0.04492
/*48  */         gen_store_gpr(t1, rd+1);                                              // (7) 0.04297
/*50  */         opn = "lwp";                                                          // (17) 0.02734
/*52  */         break;                                                                // (23) 0.01758
/*54  */     case SWP:                                                                 // (25) 0.01367
/*56  */         save_cpu_state(ctx, 0);                                               // (15) 0.0332
/*58  */         gen_load_gpr(t1, rd);                                                 // (12) 0.03906
/*60  */         op_st_sw(t1, t0, ctx);                                                // (8) 0.04297
/*62  */         tcg_gen_movi_tl(t1, 4);                                               // (9) 0.04297
/*64  */         gen_op_addr_add(ctx, t0, t0, t1);                                     // 0.0
/*66  */         gen_load_gpr(t1, rd+1);                                               // 0.0
/*68  */         op_st_sw(t1, t0, ctx);                                                // 0.0
/*70  */         opn = "swp";                                                          // 0.0
/*72  */         break;                                                                // 0.0
/*74  */ #ifdef TARGET_MIPS64                                                          // 0.0
/*76  */     case LDP:                                                                 // 0.0
/*78  */         save_cpu_state(ctx, 0);                                               // 0.0
/*80  */         op_ld_ld(t1, t0, ctx);                                                // 0.0
/*82  */         gen_store_gpr(t1, rd);                                                // 0.0
/*84  */         tcg_gen_movi_tl(t1, 8);                                               // 0.0
/*86  */         gen_op_addr_add(ctx, t0, t0, t1);                                     // 0.0
/*88  */         op_ld_ld(t1, t0, ctx);                                                // 0.0
/*90  */         gen_store_gpr(t1, rd+1);                                              // 0.0
/*92  */         opn = "ldp";                                                          // 0.0
/*94  */         break;                                                                // 0.0
/*96  */     case SDP:                                                                 // 0.0
/*98  */         save_cpu_state(ctx, 0);                                               // 0.0
/*100 */         gen_load_gpr(t1, rd);                                                 // 0.0
/*102 */         op_st_sd(t1, t0, ctx);                                                // 0.0
/*104 */         tcg_gen_movi_tl(t1, 8);                                               // 0.0
/*106 */         gen_op_addr_add(ctx, t0, t0, t1);                                     // 0.0
/*108 */         gen_load_gpr(t1, rd+1);                                               // 0.0
/*110 */         op_st_sd(t1, t0, ctx);                                                // 0.0
/*112 */         opn = "sdp";                                                          // 0.0
/*114 */         break;                                                                // 0.0
/*116 */ #endif                                                                        // 0.0
/*118 */     }                                                                         // 0.0
/*120 */     (void)opn; /* avoid a compiler warning */                                 // 0.0
/*122 */     MIPS_DEBUG("%s, %s, %d(%s)", opn, regnames[rd], offset, regnames[base]);  // 0.0
/*124 */     tcg_temp_free(t0);                                                        // 0.0
/*126 */     tcg_temp_free(t1);                                                        // 0.0
/*128 */ }                                                                             // 0.0
