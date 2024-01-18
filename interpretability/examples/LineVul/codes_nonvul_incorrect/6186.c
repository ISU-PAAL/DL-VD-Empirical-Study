// commit message qemu@47e04430ed (target=0, prob=0.7994286, correct=False): target-tricore: Make TRICORE_FEATURES implying others.
/*0   */ static void decode_bo_addrmode_post_pre_base(CPUTriCoreState *env,            // (3) 0.04492
/*2   */                                              DisasContext *ctx)               // (0) 0.09766
/*4   */ {                                                                             // (24) 0.001953
/*6   */     uint32_t op2;                                                             // (18) 0.01953
/*8   */     uint32_t off10;                                                           // (19) 0.01953
/*10  */     int32_t r1, r2;                                                           // (17) 0.02539
/*12  */     TCGv temp;                                                                // (23) 0.01563
/*16  */     r1 = MASK_OP_BO_S1D(ctx->opcode);                                         // (8) 0.04297
/*18  */     r2  = MASK_OP_BO_S2(ctx->opcode);                                         // (9) 0.04297
/*20  */     off10 = MASK_OP_BO_OFF10_SEXT(ctx->opcode);                               // (2) 0.04688
/*22  */     op2 = MASK_OP_BO_OP2(ctx->opcode);                                        // (13) 0.04102
/*26  */     switch (op2) {                                                            // (20) 0.01758
/*28  */     case OPC2_32_BO_CACHEA_WI_SHORTOFF:                                       // (5) 0.04492
/*30  */     case OPC2_32_BO_CACHEA_W_SHORTOFF:                                        // (4) 0.04492
/*32  */     case OPC2_32_BO_CACHEA_I_SHORTOFF:                                        // (6) 0.04492
/*34  */         /* instruction to access the cache */                                 // (16) 0.02734
/*36  */         break;                                                                // (21) 0.01758
/*38  */     case OPC2_32_BO_CACHEA_WI_POSTINC:                                        // (10) 0.04297
/*40  */     case OPC2_32_BO_CACHEA_W_POSTINC:                                         // (11) 0.04297
/*42  */     case OPC2_32_BO_CACHEA_I_POSTINC:                                         // (12) 0.04297
/*44  */         /* instruction to access the cache, but we still need to handle       // (14) 0.03906
/*46  */            the addressing mode */                                             // (15) 0.02734
/*48  */         tcg_gen_addi_tl(cpu_gpr_d[r2], cpu_gpr_d[r2], off10);                 // (1) 0.07813
/*50  */         break;                                                                // (22) 0.01758
/*52  */     case OPC2_32_BO_CACHEA_WI_PREINC:                                         // (7) 0.04297
/*54  */     case OPC2_32_BO_CACHEA_W_PREINC:                                          // 0.0
/*56  */     case OPC2_32_BO_CACHEA_I_PREINC:                                          // 0.0
/*58  */         /* instruction to access the cache, but we still need to handle       // 0.0
/*60  */            the addressing mode */                                             // 0.0
/*62  */         tcg_gen_addi_tl(cpu_gpr_d[r2], cpu_gpr_d[r2], off10);                 // 0.0
/*64  */         break;                                                                // 0.0
/*66  */     case OPC2_32_BO_CACHEI_WI_SHORTOFF:                                       // 0.0
/*68  */     case OPC2_32_BO_CACHEI_W_SHORTOFF:                                        // 0.0
/*70  */         /* TODO: Raise illegal opcode trap,                                   // 0.0
/*72  */                  if tricore_feature(TRICORE_FEATURE_13) */                    // 0.0
/*74  */         break;                                                                // 0.0
/*76  */     case OPC2_32_BO_CACHEI_W_POSTINC:                                         // 0.0
/*78  */     case OPC2_32_BO_CACHEI_WI_POSTINC:                                        // 0.0
/*80  */         if (!tricore_feature(env, TRICORE_FEATURE_13)) {                      // 0.0
/*82  */             tcg_gen_addi_tl(cpu_gpr_d[r2], cpu_gpr_d[r2], off10);             // 0.0
/*84  */         } /* TODO: else raise illegal opcode trap */                          // 0.0
/*86  */         break;                                                                // 0.0
/*88  */     case OPC2_32_BO_CACHEI_W_PREINC:                                          // 0.0
/*90  */     case OPC2_32_BO_CACHEI_WI_PREINC:                                         // 0.0
/*92  */         if (!tricore_feature(env, TRICORE_FEATURE_13)) {                      // 0.0
/*94  */             tcg_gen_addi_tl(cpu_gpr_d[r2], cpu_gpr_d[r2], off10);             // 0.0
/*96  */         } /* TODO: else raise illegal opcode trap */                          // 0.0
/*98  */         break;                                                                // 0.0
/*100 */     case OPC2_32_BO_ST_A_SHORTOFF:                                            // 0.0
/*102 */         gen_offset_st(ctx, cpu_gpr_a[r1], cpu_gpr_a[r2], off10, MO_LESL);     // 0.0
/*104 */         break;                                                                // 0.0
/*106 */     case OPC2_32_BO_ST_A_POSTINC:                                             // 0.0
/*108 */         tcg_gen_qemu_st_tl(cpu_gpr_a[r1], cpu_gpr_a[r2], ctx->mem_idx,        // 0.0
/*110 */                            MO_LESL);                                          // 0.0
/*112 */         tcg_gen_addi_tl(cpu_gpr_a[r2], cpu_gpr_a[r2], off10);                 // 0.0
/*114 */         break;                                                                // 0.0
/*116 */     case OPC2_32_BO_ST_A_PREINC:                                              // 0.0
/*118 */         gen_st_preincr(ctx, cpu_gpr_a[r1], cpu_gpr_a[r2], off10, MO_LESL);    // 0.0
/*120 */         break;                                                                // 0.0
/*122 */     case OPC2_32_BO_ST_B_SHORTOFF:                                            // 0.0
/*124 */         gen_offset_st(ctx, cpu_gpr_d[r1], cpu_gpr_a[r2], off10, MO_UB);       // 0.0
/*126 */         break;                                                                // 0.0
/*128 */     case OPC2_32_BO_ST_B_POSTINC:                                             // 0.0
/*130 */         tcg_gen_qemu_st_tl(cpu_gpr_d[r1], cpu_gpr_a[r2], ctx->mem_idx,        // 0.0
/*132 */                            MO_UB);                                            // 0.0
/*134 */         tcg_gen_addi_tl(cpu_gpr_a[r2], cpu_gpr_a[r2], off10);                 // 0.0
/*136 */         break;                                                                // 0.0
/*138 */     case OPC2_32_BO_ST_B_PREINC:                                              // 0.0
/*140 */         gen_st_preincr(ctx, cpu_gpr_d[r1], cpu_gpr_a[r2], off10, MO_UB);      // 0.0
/*142 */         break;                                                                // 0.0
/*144 */     case OPC2_32_BO_ST_D_SHORTOFF:                                            // 0.0
/*146 */         gen_offset_st_2regs(cpu_gpr_d[r1+1], cpu_gpr_d[r1], cpu_gpr_a[r2],    // 0.0
/*148 */                             off10, ctx);                                      // 0.0
/*150 */         break;                                                                // 0.0
/*152 */     case OPC2_32_BO_ST_D_POSTINC:                                             // 0.0
/*154 */         gen_st_2regs_64(cpu_gpr_d[r1+1], cpu_gpr_d[r1], cpu_gpr_a[r2], ctx);  // 0.0
/*156 */         tcg_gen_addi_tl(cpu_gpr_a[r2], cpu_gpr_a[r2], off10);                 // 0.0
/*158 */         break;                                                                // 0.0
/*160 */     case OPC2_32_BO_ST_D_PREINC:                                              // 0.0
/*162 */         temp = tcg_temp_new();                                                // 0.0
/*164 */         tcg_gen_addi_tl(temp, cpu_gpr_a[r2], off10);                          // 0.0
/*166 */         gen_st_2regs_64(cpu_gpr_d[r1+1], cpu_gpr_d[r1], temp, ctx);           // 0.0
/*168 */         tcg_gen_mov_tl(cpu_gpr_a[r2], temp);                                  // 0.0
/*170 */         tcg_temp_free(temp);                                                  // 0.0
/*172 */         break;                                                                // 0.0
/*174 */     case OPC2_32_BO_ST_DA_SHORTOFF:                                           // 0.0
/*176 */         gen_offset_st_2regs(cpu_gpr_a[r1+1], cpu_gpr_a[r1], cpu_gpr_a[r2],    // 0.0
/*178 */                             off10, ctx);                                      // 0.0
/*180 */         break;                                                                // 0.0
/*182 */     case OPC2_32_BO_ST_DA_POSTINC:                                            // 0.0
/*184 */         gen_st_2regs_64(cpu_gpr_a[r1+1], cpu_gpr_a[r1], cpu_gpr_a[r2], ctx);  // 0.0
/*186 */         tcg_gen_addi_tl(cpu_gpr_a[r2], cpu_gpr_a[r2], off10);                 // 0.0
/*188 */         break;                                                                // 0.0
/*190 */     case OPC2_32_BO_ST_DA_PREINC:                                             // 0.0
/*192 */         temp = tcg_temp_new();                                                // 0.0
/*194 */         tcg_gen_addi_tl(temp, cpu_gpr_a[r2], off10);                          // 0.0
/*196 */         gen_st_2regs_64(cpu_gpr_a[r1+1], cpu_gpr_a[r1], temp, ctx);           // 0.0
/*198 */         tcg_gen_mov_tl(cpu_gpr_a[r2], temp);                                  // 0.0
/*200 */         tcg_temp_free(temp);                                                  // 0.0
/*202 */         break;                                                                // 0.0
/*204 */     case OPC2_32_BO_ST_H_SHORTOFF:                                            // 0.0
/*206 */         gen_offset_st(ctx, cpu_gpr_d[r1], cpu_gpr_a[r2], off10, MO_LEUW);     // 0.0
/*208 */         break;                                                                // 0.0
/*210 */     case OPC2_32_BO_ST_H_POSTINC:                                             // 0.0
/*212 */         tcg_gen_qemu_st_tl(cpu_gpr_d[r1], cpu_gpr_a[r2], ctx->mem_idx,        // 0.0
/*214 */                            MO_LEUW);                                          // 0.0
/*216 */         tcg_gen_addi_tl(cpu_gpr_a[r2], cpu_gpr_a[r2], off10);                 // 0.0
/*218 */         break;                                                                // 0.0
/*220 */     case OPC2_32_BO_ST_H_PREINC:                                              // 0.0
/*222 */         gen_st_preincr(ctx, cpu_gpr_d[r1], cpu_gpr_a[r2], off10, MO_LEUW);    // 0.0
/*224 */         break;                                                                // 0.0
/*226 */     case OPC2_32_BO_ST_Q_SHORTOFF:                                            // 0.0
/*228 */         temp = tcg_temp_new();                                                // 0.0
/*230 */         tcg_gen_shri_tl(temp, cpu_gpr_d[r1], 16);                             // 0.0
/*232 */         gen_offset_st(ctx, temp, cpu_gpr_a[r2], off10, MO_LEUW);              // 0.0
/*234 */         tcg_temp_free(temp);                                                  // 0.0
/*236 */         break;                                                                // 0.0
/*238 */     case OPC2_32_BO_ST_Q_POSTINC:                                             // 0.0
/*240 */         temp = tcg_temp_new();                                                // 0.0
/*242 */         tcg_gen_shri_tl(temp, cpu_gpr_d[r1], 16);                             // 0.0
/*244 */         tcg_gen_qemu_st_tl(temp, cpu_gpr_a[r2], ctx->mem_idx,                 // 0.0
/*246 */                            MO_LEUW);                                          // 0.0
/*248 */         tcg_gen_addi_tl(cpu_gpr_a[r2], cpu_gpr_a[r2], off10);                 // 0.0
/*250 */         tcg_temp_free(temp);                                                  // 0.0
/*252 */         break;                                                                // 0.0
/*254 */     case OPC2_32_BO_ST_Q_PREINC:                                              // 0.0
/*256 */         temp = tcg_temp_new();                                                // 0.0
/*258 */         tcg_gen_shri_tl(temp, cpu_gpr_d[r1], 16);                             // 0.0
/*260 */         gen_st_preincr(ctx, temp, cpu_gpr_a[r2], off10, MO_LEUW);             // 0.0
/*262 */         tcg_temp_free(temp);                                                  // 0.0
/*264 */         break;                                                                // 0.0
/*266 */     case OPC2_32_BO_ST_W_SHORTOFF:                                            // 0.0
/*268 */         gen_offset_st(ctx, cpu_gpr_d[r1], cpu_gpr_a[r2], off10, MO_LEUL);     // 0.0
/*270 */         break;                                                                // 0.0
/*272 */     case OPC2_32_BO_ST_W_POSTINC:                                             // 0.0
/*274 */         tcg_gen_qemu_st_tl(cpu_gpr_d[r1], cpu_gpr_a[r2], ctx->mem_idx,        // 0.0
/*276 */                            MO_LEUL);                                          // 0.0
/*278 */         tcg_gen_addi_tl(cpu_gpr_a[r2], cpu_gpr_a[r2], off10);                 // 0.0
/*280 */         break;                                                                // 0.0
/*282 */     case OPC2_32_BO_ST_W_PREINC:                                              // 0.0
/*284 */         gen_st_preincr(ctx, cpu_gpr_d[r1], cpu_gpr_a[r2], off10, MO_LEUL);    // 0.0
/*286 */         break;                                                                // 0.0
/*288 */     }                                                                         // 0.0
/*290 */ }                                                                             // 0.0
