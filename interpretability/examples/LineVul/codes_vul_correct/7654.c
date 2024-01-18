// commit message qemu@d5de7839d7 (target=1, prob=0.9990884, correct=True): target-tricore: Add instructions of RR opcode format, that have 0xb as the first opcode
/*0   */ static void decode_32Bit_opc(CPUTriCoreState *env, DisasContext *ctx)    // (2) 0.04688
/*2   */ {                                                                        // (28) 0.001953
/*4   */     int op1;                                                             // (25) 0.01367
/*6   */     int32_t r1, r2, r3;                                                  // (16) 0.03125
/*8   */     int32_t address, const16;                                            // (21) 0.02344
/*10  */     int8_t b, const4;                                                    // (22) 0.02344
/*12  */     int32_t bpos;                                                        // (23) 0.01953
/*14  */     TCGv temp, temp2, temp3;                                             // (20) 0.02734
/*18  */     op1 = MASK_OP_MAJOR(ctx->opcode);                                    // (7) 0.03906
/*22  */     /* handle JNZ.T opcode only being 7 bit long */                      // (14) 0.0332
/*24  */     if (unlikely((op1 & 0x7f) == OPCM_32_BRN_JTT)) {                     // (0) 0.05859
/*26  */         op1 = OPCM_32_BRN_JTT;                                           // (3) 0.04297
/*28  */     }                                                                    // (27) 0.007812
/*32  */     switch (op1) {                                                       // (24) 0.01758
/*34  */ /* ABS-format */                                                         // (26) 0.009766
/*36  */     case OPCM_32_ABS_LDW:                                                // (17) 0.03125
/*38  */         decode_abs_ldw(env, ctx);                                        // (9) 0.03711
/*41  */     case OPCM_32_ABS_LDB:                                                // (18) 0.03125
/*43  */         decode_abs_ldb(env, ctx);                                        // (10) 0.03711
/*46  */     case OPCM_32_ABS_LDMST_SWAP:                                         // (8) 0.03906
/*48  */         decode_abs_ldst_swap(env, ctx);                                  // (4) 0.04297
/*51  */     case OPCM_32_ABS_LDST_CONTEXT:                                       // (11) 0.03711
/*53  */         decode_abs_ldst_context(env, ctx);                               // (5) 0.04102
/*56  */     case OPCM_32_ABS_STORE:                                              // (19) 0.03125
/*58  */         decode_abs_store(env, ctx);                                      // (13) 0.03516
/*61  */     case OPCM_32_ABS_STOREB_H:                                           // (12) 0.03711
/*63  */         decode_abs_storeb_h(env, ctx);                                   // (6) 0.04102
/*66  */     case OPC1_32_ABS_STOREQ:                                             // (15) 0.0332
/*68  */         address = MASK_OP_ABS_OFF18(ctx->opcode);                        // (1) 0.04883
/*70  */         r1 = MASK_OP_ABS_S1D(ctx->opcode);                               // 0.0
/*72  */         temp = tcg_const_i32(EA_ABS_FORMAT(address));                    // 0.0
/*74  */         temp2 = tcg_temp_new();                                          // 0.0
/*78  */         tcg_gen_shri_tl(temp2, cpu_gpr_d[r1], 16);                       // 0.0
/*80  */         tcg_gen_qemu_st_tl(temp2, temp, ctx->mem_idx, MO_LEUW);          // 0.0
/*84  */         tcg_temp_free(temp2);                                            // 0.0
/*86  */         tcg_temp_free(temp);                                             // 0.0
/*89  */     case OPC1_32_ABS_LD_Q:                                               // 0.0
/*91  */         address = MASK_OP_ABS_OFF18(ctx->opcode);                        // 0.0
/*93  */         r1 = MASK_OP_ABS_S1D(ctx->opcode);                               // 0.0
/*95  */         temp = tcg_const_i32(EA_ABS_FORMAT(address));                    // 0.0
/*99  */         tcg_gen_qemu_ld_tl(cpu_gpr_d[r1], temp, ctx->mem_idx, MO_LEUW);  // 0.0
/*101 */         tcg_gen_shli_tl(cpu_gpr_d[r1], cpu_gpr_d[r1], 16);               // 0.0
/*105 */         tcg_temp_free(temp);                                             // 0.0
/*108 */     case OPC1_32_ABS_LEA:                                                // 0.0
/*110 */         address = MASK_OP_ABS_OFF18(ctx->opcode);                        // 0.0
/*112 */         r1 = MASK_OP_ABS_S1D(ctx->opcode);                               // 0.0
/*114 */         tcg_gen_movi_tl(cpu_gpr_a[r1], EA_ABS_FORMAT(address));          // 0.0
/*117 */ /* ABSB-format */                                                        // 0.0
/*119 */     case OPC1_32_ABSB_ST_T:                                              // 0.0
/*121 */         address = MASK_OP_ABS_OFF18(ctx->opcode);                        // 0.0
/*123 */         b = MASK_OP_ABSB_B(ctx->opcode);                                 // 0.0
/*125 */         bpos = MASK_OP_ABSB_BPOS(ctx->opcode);                           // 0.0
/*129 */         temp = tcg_const_i32(EA_ABS_FORMAT(address));                    // 0.0
/*131 */         temp2 = tcg_temp_new();                                          // 0.0
/*135 */         tcg_gen_qemu_ld_tl(temp2, temp, ctx->mem_idx, MO_UB);            // 0.0
/*137 */         tcg_gen_andi_tl(temp2, temp2, ~(0x1u << bpos));                  // 0.0
/*139 */         tcg_gen_ori_tl(temp2, temp2, (b << bpos));                       // 0.0
/*141 */         tcg_gen_qemu_st_tl(temp2, temp, ctx->mem_idx, MO_UB);            // 0.0
/*145 */         tcg_temp_free(temp);                                             // 0.0
/*147 */         tcg_temp_free(temp2);                                            // 0.0
/*150 */ /* B-format */                                                           // 0.0
/*152 */     case OPC1_32_B_CALL:                                                 // 0.0
/*154 */     case OPC1_32_B_CALLA:                                                // 0.0
/*156 */     case OPC1_32_B_J:                                                    // 0.0
/*158 */     case OPC1_32_B_JA:                                                   // 0.0
/*160 */     case OPC1_32_B_JL:                                                   // 0.0
/*162 */     case OPC1_32_B_JLA:                                                  // 0.0
/*164 */         address = MASK_OP_B_DISP24(ctx->opcode);                         // 0.0
/*166 */         gen_compute_branch(ctx, op1, 0, 0, 0, address);                  // 0.0
/*169 */ /* Bit-format */                                                         // 0.0
/*171 */     case OPCM_32_BIT_ANDACC:                                             // 0.0
/*173 */         decode_bit_andacc(env, ctx);                                     // 0.0
/*176 */     case OPCM_32_BIT_LOGICAL_T1:                                         // 0.0
/*178 */         decode_bit_logical_t(env, ctx);                                  // 0.0
/*181 */     case OPCM_32_BIT_INSERT:                                             // 0.0
/*183 */         decode_bit_insert(env, ctx);                                     // 0.0
/*186 */     case OPCM_32_BIT_LOGICAL_T2:                                         // 0.0
/*188 */         decode_bit_logical_t2(env, ctx);                                 // 0.0
/*191 */     case OPCM_32_BIT_ORAND:                                              // 0.0
/*193 */         decode_bit_orand(env, ctx);                                      // 0.0
/*196 */     case OPCM_32_BIT_SH_LOGIC1:                                          // 0.0
/*198 */         decode_bit_sh_logic1(env, ctx);                                  // 0.0
/*201 */     case OPCM_32_BIT_SH_LOGIC2:                                          // 0.0
/*203 */         decode_bit_sh_logic2(env, ctx);                                  // 0.0
/*206 */     /* BO Format */                                                      // 0.0
/*208 */     case OPCM_32_BO_ADDRMODE_POST_PRE_BASE:                              // 0.0
/*210 */         decode_bo_addrmode_post_pre_base(env, ctx);                      // 0.0
/*213 */     case OPCM_32_BO_ADDRMODE_BITREVERSE_CIRCULAR:                        // 0.0
/*215 */         decode_bo_addrmode_bitreverse_circular(env, ctx);                // 0.0
/*218 */     case OPCM_32_BO_ADDRMODE_LD_POST_PRE_BASE:                           // 0.0
/*220 */         decode_bo_addrmode_ld_post_pre_base(env, ctx);                   // 0.0
/*223 */     case OPCM_32_BO_ADDRMODE_LD_BITREVERSE_CIRCULAR:                     // 0.0
/*225 */         decode_bo_addrmode_ld_bitreverse_circular(env, ctx);             // 0.0
/*228 */     case OPCM_32_BO_ADDRMODE_STCTX_POST_PRE_BASE:                        // 0.0
/*230 */         decode_bo_addrmode_stctx_post_pre_base(env, ctx);                // 0.0
/*233 */     case OPCM_32_BO_ADDRMODE_LDMST_BITREVERSE_CIRCULAR:                  // 0.0
/*235 */         decode_bo_addrmode_ldmst_bitreverse_circular(env, ctx);          // 0.0
/*238 */ /* BOL-format */                                                         // 0.0
/*240 */     case OPC1_32_BOL_LD_A_LONGOFF:                                       // 0.0
/*242 */     case OPC1_32_BOL_LD_W_LONGOFF:                                       // 0.0
/*244 */     case OPC1_32_BOL_LEA_LONGOFF:                                        // 0.0
/*246 */     case OPC1_32_BOL_ST_W_LONGOFF:                                       // 0.0
/*248 */     case OPC1_32_BOL_ST_A_LONGOFF:                                       // 0.0
/*250 */         decode_bol_opc(env, ctx, op1);                                   // 0.0
/*253 */ /* BRC Format */                                                         // 0.0
/*255 */     case OPCM_32_BRC_EQ_NEQ:                                             // 0.0
/*257 */     case OPCM_32_BRC_GE:                                                 // 0.0
/*259 */     case OPCM_32_BRC_JLT:                                                // 0.0
/*261 */     case OPCM_32_BRC_JNE:                                                // 0.0
/*263 */         const4 = MASK_OP_BRC_CONST4_SEXT(ctx->opcode);                   // 0.0
/*265 */         address = MASK_OP_BRC_DISP15_SEXT(ctx->opcode);                  // 0.0
/*267 */         r1 = MASK_OP_BRC_S1(ctx->opcode);                                // 0.0
/*269 */         gen_compute_branch(ctx, op1, r1, 0, const4, address);            // 0.0
/*272 */ /* BRN Format */                                                         // 0.0
/*274 */     case OPCM_32_BRN_JTT:                                                // 0.0
/*276 */         address = MASK_OP_BRN_DISP15_SEXT(ctx->opcode);                  // 0.0
/*278 */         r1 = MASK_OP_BRN_S1(ctx->opcode);                                // 0.0
/*280 */         gen_compute_branch(ctx, op1, r1, 0, 0, address);                 // 0.0
/*283 */ /* BRR Format */                                                         // 0.0
/*285 */     case OPCM_32_BRR_EQ_NEQ:                                             // 0.0
/*287 */     case OPCM_32_BRR_ADDR_EQ_NEQ:                                        // 0.0
/*289 */     case OPCM_32_BRR_GE:                                                 // 0.0
/*291 */     case OPCM_32_BRR_JLT:                                                // 0.0
/*293 */     case OPCM_32_BRR_JNE:                                                // 0.0
/*295 */     case OPCM_32_BRR_JNZ:                                                // 0.0
/*297 */     case OPCM_32_BRR_LOOP:                                               // 0.0
/*299 */         address = MASK_OP_BRR_DISP15_SEXT(ctx->opcode);                  // 0.0
/*301 */         r2 = MASK_OP_BRR_S2(ctx->opcode);                                // 0.0
/*303 */         r1 = MASK_OP_BRR_S1(ctx->opcode);                                // 0.0
/*305 */         gen_compute_branch(ctx, op1, r1, r2, 0, address);                // 0.0
/*308 */ /* RC Format */                                                          // 0.0
/*310 */     case OPCM_32_RC_LOGICAL_SHIFT:                                       // 0.0
/*312 */         decode_rc_logical_shift(env, ctx);                               // 0.0
/*315 */     case OPCM_32_RC_ACCUMULATOR:                                         // 0.0
/*317 */         decode_rc_accumulator(env, ctx);                                 // 0.0
/*320 */     case OPCM_32_RC_SERVICEROUTINE:                                      // 0.0
/*322 */         decode_rc_serviceroutine(env, ctx);                              // 0.0
/*325 */     case OPCM_32_RC_MUL:                                                 // 0.0
/*327 */         decode_rc_mul(env, ctx);                                         // 0.0
/*330 */ /* RCPW Format */                                                        // 0.0
/*332 */     case OPCM_32_RCPW_MASK_INSERT:                                       // 0.0
/*334 */         decode_rcpw_insert(env, ctx);                                    // 0.0
/*337 */ /* RCRR Format */                                                        // 0.0
/*339 */     case OPC1_32_RCRR_INSERT:                                            // 0.0
/*341 */         r1 = MASK_OP_RCRR_S1(ctx->opcode);                               // 0.0
/*343 */         r2 = MASK_OP_RCRR_S3(ctx->opcode);                               // 0.0
/*345 */         r3 = MASK_OP_RCRR_D(ctx->opcode);                                // 0.0
/*347 */         const16 = MASK_OP_RCRR_CONST4(ctx->opcode);                      // 0.0
/*349 */         temp = tcg_const_i32(const16);                                   // 0.0
/*351 */         temp2 = tcg_temp_new(); /* width*/                               // 0.0
/*353 */         temp3 = tcg_temp_new(); /* pos */                                // 0.0
/*357 */         tcg_gen_andi_tl(temp2, cpu_gpr_d[r3+1], 0x1f);                   // 0.0
/*359 */         tcg_gen_andi_tl(temp3, cpu_gpr_d[r3], 0x1f);                     // 0.0
/*363 */         gen_insert(cpu_gpr_d[r2], cpu_gpr_d[r1], temp, temp2, temp3);    // 0.0
/*367 */         tcg_temp_free(temp);                                             // 0.0
/*369 */         tcg_temp_free(temp2);                                            // 0.0
/*371 */         tcg_temp_free(temp3);                                            // 0.0
/*374 */ /* RCRW Format */                                                        // 0.0
/*376 */     case OPCM_32_RCRW_MASK_INSERT:                                       // 0.0
/*378 */         decode_rcrw_insert(env, ctx);                                    // 0.0
/*381 */ /* RCR Format */                                                         // 0.0
/*383 */     case OPCM_32_RCR_COND_SELECT:                                        // 0.0
/*385 */         decode_rcr_cond_select(env, ctx);                                // 0.0
/*388 */     case OPCM_32_RCR_MADD:                                               // 0.0
/*390 */         decode_rcr_madd(env, ctx);                                       // 0.0
/*393 */     case OPCM_32_RCR_MSUB:                                               // 0.0
/*395 */         decode_rcr_msub(env, ctx);                                       // 0.0
/*398 */ /* RLC Format */                                                         // 0.0
/*400 */     case OPC1_32_RLC_ADDI:                                               // 0.0
/*402 */     case OPC1_32_RLC_ADDIH:                                              // 0.0
/*404 */     case OPC1_32_RLC_ADDIH_A:                                            // 0.0
/*406 */     case OPC1_32_RLC_MFCR:                                               // 0.0
/*408 */     case OPC1_32_RLC_MOV:                                                // 0.0
/*410 */     case OPC1_32_RLC_MOV_64:                                             // 0.0
/*412 */     case OPC1_32_RLC_MOV_U:                                              // 0.0
/*414 */     case OPC1_32_RLC_MOV_H:                                              // 0.0
/*416 */     case OPC1_32_RLC_MOVH_A:                                             // 0.0
/*418 */     case OPC1_32_RLC_MTCR:                                               // 0.0
/*420 */         decode_rlc_opc(env, ctx, op1);                                   // 0.0
/*427 */     }                                                                    // 0.0
/*429 */ }                                                                        // 0.0
