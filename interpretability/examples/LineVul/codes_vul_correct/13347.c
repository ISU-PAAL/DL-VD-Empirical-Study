// commit message qemu@f678f671ba (target=1, prob=0.92277724, correct=True): target-tricore: add illegal opcode trap generation
/*0  */ static void decode_abs_store(CPUTriCoreState *env, DisasContext *ctx)    // (6) 0.04481
/*2  */ {                                                                        // (24) 0.002037
/*4  */     int32_t op2;                                                         // (14) 0.02037
/*6  */     int32_t r1;                                                          // (15) 0.02037
/*8  */     uint32_t address;                                                    // (16) 0.01833
/*10 */     TCGv temp;                                                           // (22) 0.01629
/*14 */     r1 = MASK_OP_ABS_S1D(ctx->opcode);                                   // (4) 0.04684
/*16 */     address = MASK_OP_ABS_OFF18(ctx->opcode);                            // (8) 0.04277
/*18 */     op2 = MASK_OP_ABS_OP2(ctx->opcode);                                  // (7) 0.04481
/*22 */     temp = tcg_const_i32(EA_ABS_FORMAT(address));                        // (5) 0.04684
/*26 */     switch (op2) {                                                       // (17) 0.01833
/*28 */     case OPC2_32_ABS_ST_A:                                               // (9) 0.03462
/*30 */         tcg_gen_qemu_st_tl(cpu_gpr_a[r1], temp, ctx->mem_idx, MO_LESL);  // (0) 0.09165
/*32 */         break;                                                           // (18) 0.01833
/*34 */     case OPC2_32_ABS_ST_D:                                               // (10) 0.03462
/*36 */         gen_st_2regs_64(cpu_gpr_d[r1+1], cpu_gpr_d[r1], temp, ctx);      // (2) 0.08961
/*38 */         break;                                                           // (19) 0.01833
/*40 */     case OPC2_32_ABS_ST_DA:                                              // (11) 0.03462
/*42 */         gen_st_2regs_64(cpu_gpr_a[r1+1], cpu_gpr_a[r1], temp, ctx);      // (3) 0.08961
/*44 */         break;                                                           // (20) 0.01833
/*46 */     case OPC2_32_ABS_ST_W:                                               // (12) 0.03462
/*48 */         tcg_gen_qemu_st_tl(cpu_gpr_d[r1], temp, ctx->mem_idx, MO_LESL);  // (1) 0.09165
/*50 */         break;                                                           // (21) 0.01833
/*54 */     }                                                                    // (23) 0.008147
/*56 */     tcg_temp_free(temp);                                                 // (13) 0.02444
/*58 */ }                                                                        // (25) 0.002037
