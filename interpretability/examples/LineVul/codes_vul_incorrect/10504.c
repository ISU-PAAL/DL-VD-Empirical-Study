// commit message qemu@240ce26a05 (target=1, prob=0.31976664, correct=False): target-mips: fix branch in likely delay slot tcg assert
/*0   */ static int decode_micromips_opc (CPUMIPSState *env, DisasContext *ctx, int *is_branch)  // (0) 0.06055
/*2   */ {                                                                                       // (32) 0.001953
/*4   */     uint32_t op;                                                                        // (30) 0.01758
/*8   */     /* make sure instructions are on a halfword boundary */                             // (8) 0.02734
/*10  */     if (ctx->pc & 0x1) {                                                                // (9) 0.02734
/*12  */         env->CP0_BadVAddr = ctx->pc;                                                    // (2) 0.04297
/*14  */         generate_exception(ctx, EXCP_AdEL);                                             // (4) 0.03906
/*16  */         ctx->bstate = BS_STOP;                                                          // (6) 0.03516
/*18  */         return 2;                                                                       // (29) 0.01953
/*20  */     }                                                                                   // (31) 0.007812
/*24  */     op = (ctx->opcode >> 10) & 0x3f;                                                    // (5) 0.03711
/*26  */     /* Enforce properly-sized instructions in a delay slot */                           // (7) 0.0293
/*28  */     if (ctx->hflags & MIPS_HFLAG_BMASK) {                                               // (3) 0.04102
/*30  */         int bits = ctx->hflags & MIPS_HFLAG_BMASK_EXT;                                  // (1) 0.05469
/*34  */         switch (op) {                                                                   // (20) 0.02344
/*36  */         case POOL32A:                                                                   // (10) 0.02539
/*38  */         case POOL32B:                                                                   // (11) 0.02539
/*40  */         case POOL32I:                                                                   // (12) 0.02539
/*42  */         case POOL32C:                                                                   // (13) 0.02539
/*44  */         case ADDI32:                                                                    // (21) 0.02344
/*46  */         case ADDIU32:                                                                   // (14) 0.02539
/*48  */         case ORI32:                                                                     // (22) 0.02344
/*50  */         case XORI32:                                                                    // (15) 0.02539
/*52  */         case SLTI32:                                                                    // (23) 0.02344
/*54  */         case SLTIU32:                                                                   // (16) 0.02539
/*56  */         case ANDI32:                                                                    // (24) 0.02344
/*58  */         case JALX32:                                                                    // (17) 0.02539
/*60  */         case LBU32:                                                                     // (25) 0.02344
/*62  */         case LHU32:                                                                     // (26) 0.02344
/*64  */         case POOL32F:                                                                   // (18) 0.02539
/*66  */         case JALS32:                                                                    // (19) 0.02344
/*68  */         case BEQ32:                                                                     // (27) 0.02344
/*70  */         case BNE32:                                                                     // (28) 0.02344
/*72  */         case J32:                                                                       // 0.0
/*74  */         case JAL32:                                                                     // 0.0
/*76  */         case SB32:                                                                      // 0.0
/*78  */         case SH32:                                                                      // 0.0
/*80  */         case POOL32S:                                                                   // 0.0
/*82  */         case ADDIUPC:                                                                   // 0.0
/*84  */         case SWC132:                                                                    // 0.0
/*86  */         case SDC132:                                                                    // 0.0
/*88  */         case SD32:                                                                      // 0.0
/*90  */         case SW32:                                                                      // 0.0
/*92  */         case LB32:                                                                      // 0.0
/*94  */         case LH32:                                                                      // 0.0
/*96  */         case DADDIU32:                                                                  // 0.0
/*98  */         case LWC132:                                                                    // 0.0
/*100 */         case LDC132:                                                                    // 0.0
/*102 */         case LD32:                                                                      // 0.0
/*104 */         case LW32:                                                                      // 0.0
/*106 */             if (bits & MIPS_HFLAG_BDS16) {                                              // 0.0
/*108 */                 generate_exception(ctx, EXCP_RI);                                       // 0.0
/*110 */                 /* Just stop translation; the user is confused.  */                     // 0.0
/*112 */                 ctx->bstate = BS_STOP;                                                  // 0.0
/*114 */                 return 2;                                                               // 0.0
/*116 */             }                                                                           // 0.0
/*118 */             break;                                                                      // 0.0
/*120 */         case POOL16A:                                                                   // 0.0
/*122 */         case POOL16B:                                                                   // 0.0
/*124 */         case POOL16C:                                                                   // 0.0
/*126 */         case LWGP16:                                                                    // 0.0
/*128 */         case POOL16F:                                                                   // 0.0
/*130 */         case LBU16:                                                                     // 0.0
/*132 */         case LHU16:                                                                     // 0.0
/*134 */         case LWSP16:                                                                    // 0.0
/*136 */         case LW16:                                                                      // 0.0
/*138 */         case SB16:                                                                      // 0.0
/*140 */         case SH16:                                                                      // 0.0
/*142 */         case SWSP16:                                                                    // 0.0
/*144 */         case SW16:                                                                      // 0.0
/*146 */         case MOVE16:                                                                    // 0.0
/*148 */         case ANDI16:                                                                    // 0.0
/*150 */         case POOL16D:                                                                   // 0.0
/*152 */         case POOL16E:                                                                   // 0.0
/*154 */         case BEQZ16:                                                                    // 0.0
/*156 */         case BNEZ16:                                                                    // 0.0
/*158 */         case B16:                                                                       // 0.0
/*160 */         case LI16:                                                                      // 0.0
/*162 */             if (bits & MIPS_HFLAG_BDS32) {                                              // 0.0
/*164 */                 generate_exception(ctx, EXCP_RI);                                       // 0.0
/*166 */                 /* Just stop translation; the user is confused.  */                     // 0.0
/*168 */                 ctx->bstate = BS_STOP;                                                  // 0.0
/*170 */                 return 2;                                                               // 0.0
/*172 */             }                                                                           // 0.0
/*174 */             break;                                                                      // 0.0
/*176 */         default:                                                                        // 0.0
/*178 */             break;                                                                      // 0.0
/*180 */         }                                                                               // 0.0
/*182 */     }                                                                                   // 0.0
/*184 */     switch (op) {                                                                       // 0.0
/*186 */     case POOL16A:                                                                       // 0.0
/*188 */         {                                                                               // 0.0
/*190 */             int rd = mmreg(uMIPS_RD(ctx->opcode));                                      // 0.0
/*192 */             int rs1 = mmreg(uMIPS_RS1(ctx->opcode));                                    // 0.0
/*194 */             int rs2 = mmreg(uMIPS_RS2(ctx->opcode));                                    // 0.0
/*196 */             uint32_t opc = 0;                                                           // 0.0
/*200 */             switch (ctx->opcode & 0x1) {                                                // 0.0
/*202 */             case ADDU16:                                                                // 0.0
/*204 */                 opc = OPC_ADDU;                                                         // 0.0
/*206 */                 break;                                                                  // 0.0
/*208 */             case SUBU16:                                                                // 0.0
/*210 */                 opc = OPC_SUBU;                                                         // 0.0
/*212 */                 break;                                                                  // 0.0
/*214 */             }                                                                           // 0.0
/*218 */             gen_arith(ctx, opc, rd, rs1, rs2);                                          // 0.0
/*220 */         }                                                                               // 0.0
/*222 */         break;                                                                          // 0.0
/*224 */     case POOL16B:                                                                       // 0.0
/*226 */         {                                                                               // 0.0
/*228 */             int rd = mmreg(uMIPS_RD(ctx->opcode));                                      // 0.0
/*230 */             int rs = mmreg(uMIPS_RS(ctx->opcode));                                      // 0.0
/*232 */             int amount = (ctx->opcode >> 1) & 0x7;                                      // 0.0
/*234 */             uint32_t opc = 0;                                                           // 0.0
/*236 */             amount = amount == 0 ? 8 : amount;                                          // 0.0
/*240 */             switch (ctx->opcode & 0x1) {                                                // 0.0
/*242 */             case SLL16:                                                                 // 0.0
/*244 */                 opc = OPC_SLL;                                                          // 0.0
/*246 */                 break;                                                                  // 0.0
/*248 */             case SRL16:                                                                 // 0.0
/*250 */                 opc = OPC_SRL;                                                          // 0.0
/*252 */                 break;                                                                  // 0.0
/*254 */             }                                                                           // 0.0
/*258 */             gen_shift_imm(ctx, opc, rd, rs, amount);                                    // 0.0
/*260 */         }                                                                               // 0.0
/*262 */         break;                                                                          // 0.0
/*264 */     case POOL16C:                                                                       // 0.0
/*266 */         gen_pool16c_insn(ctx, is_branch);                                               // 0.0
/*268 */         break;                                                                          // 0.0
/*270 */     case LWGP16:                                                                        // 0.0
/*272 */         {                                                                               // 0.0
/*274 */             int rd = mmreg(uMIPS_RD(ctx->opcode));                                      // 0.0
/*276 */             int rb = 28;            /* GP */                                            // 0.0
/*278 */             int16_t offset = SIMM(ctx->opcode, 0, 7) << 2;                              // 0.0
/*282 */             gen_ld(ctx, OPC_LW, rd, rb, offset);                                        // 0.0
/*284 */         }                                                                               // 0.0
/*286 */         break;                                                                          // 0.0
/*288 */     case POOL16F:                                                                       // 0.0
/*290 */         if (ctx->opcode & 1) {                                                          // 0.0
/*292 */             generate_exception(ctx, EXCP_RI);                                           // 0.0
/*294 */         } else {                                                                        // 0.0
/*296 */             /* MOVEP */                                                                 // 0.0
/*298 */             int enc_dest = uMIPS_RD(ctx->opcode);                                       // 0.0
/*300 */             int enc_rt = uMIPS_RS2(ctx->opcode);                                        // 0.0
/*302 */             int enc_rs = uMIPS_RS1(ctx->opcode);                                        // 0.0
/*304 */             int rd, rs, re, rt;                                                         // 0.0
/*306 */             static const int rd_enc[] = { 5, 5, 6, 4, 4, 4, 4, 4 };                     // 0.0
/*308 */             static const int re_enc[] = { 6, 7, 7, 21, 22, 5, 6, 7 };                   // 0.0
/*310 */             static const int rs_rt_enc[] = { 0, 17, 2, 3, 16, 18, 19, 20 };             // 0.0
/*314 */             rd = rd_enc[enc_dest];                                                      // 0.0
/*316 */             re = re_enc[enc_dest];                                                      // 0.0
/*318 */             rs = rs_rt_enc[enc_rs];                                                     // 0.0
/*320 */             rt = rs_rt_enc[enc_rt];                                                     // 0.0
/*324 */             gen_arith_imm(ctx, OPC_ADDIU, rd, rs, 0);                                   // 0.0
/*326 */             gen_arith_imm(ctx, OPC_ADDIU, re, rt, 0);                                   // 0.0
/*328 */         }                                                                               // 0.0
/*330 */         break;                                                                          // 0.0
/*332 */     case LBU16:                                                                         // 0.0
/*334 */         {                                                                               // 0.0
/*336 */             int rd = mmreg(uMIPS_RD(ctx->opcode));                                      // 0.0
/*338 */             int rb = mmreg(uMIPS_RS(ctx->opcode));                                      // 0.0
/*340 */             int16_t offset = ZIMM(ctx->opcode, 0, 4);                                   // 0.0
/*342 */             offset = (offset == 0xf ? -1 : offset);                                     // 0.0
/*346 */             gen_ld(ctx, OPC_LBU, rd, rb, offset);                                       // 0.0
/*348 */         }                                                                               // 0.0
/*350 */         break;                                                                          // 0.0
/*352 */     case LHU16:                                                                         // 0.0
/*354 */         {                                                                               // 0.0
/*356 */             int rd = mmreg(uMIPS_RD(ctx->opcode));                                      // 0.0
/*358 */             int rb = mmreg(uMIPS_RS(ctx->opcode));                                      // 0.0
/*360 */             int16_t offset = ZIMM(ctx->opcode, 0, 4) << 1;                              // 0.0
/*364 */             gen_ld(ctx, OPC_LHU, rd, rb, offset);                                       // 0.0
/*366 */         }                                                                               // 0.0
/*368 */         break;                                                                          // 0.0
/*370 */     case LWSP16:                                                                        // 0.0
/*372 */         {                                                                               // 0.0
/*374 */             int rd = (ctx->opcode >> 5) & 0x1f;                                         // 0.0
/*376 */             int rb = 29;            /* SP */                                            // 0.0
/*378 */             int16_t offset = ZIMM(ctx->opcode, 0, 5) << 2;                              // 0.0
/*382 */             gen_ld(ctx, OPC_LW, rd, rb, offset);                                        // 0.0
/*384 */         }                                                                               // 0.0
/*386 */         break;                                                                          // 0.0
/*388 */     case LW16:                                                                          // 0.0
/*390 */         {                                                                               // 0.0
/*392 */             int rd = mmreg(uMIPS_RD(ctx->opcode));                                      // 0.0
/*394 */             int rb = mmreg(uMIPS_RS(ctx->opcode));                                      // 0.0
/*396 */             int16_t offset = ZIMM(ctx->opcode, 0, 4) << 2;                              // 0.0
/*400 */             gen_ld(ctx, OPC_LW, rd, rb, offset);                                        // 0.0
/*402 */         }                                                                               // 0.0
/*404 */         break;                                                                          // 0.0
/*406 */     case SB16:                                                                          // 0.0
/*408 */         {                                                                               // 0.0
/*410 */             int rd = mmreg2(uMIPS_RD(ctx->opcode));                                     // 0.0
/*412 */             int rb = mmreg(uMIPS_RS(ctx->opcode));                                      // 0.0
/*414 */             int16_t offset = ZIMM(ctx->opcode, 0, 4);                                   // 0.0
/*418 */             gen_st(ctx, OPC_SB, rd, rb, offset);                                        // 0.0
/*420 */         }                                                                               // 0.0
/*422 */         break;                                                                          // 0.0
/*424 */     case SH16:                                                                          // 0.0
/*426 */         {                                                                               // 0.0
/*428 */             int rd = mmreg2(uMIPS_RD(ctx->opcode));                                     // 0.0
/*430 */             int rb = mmreg(uMIPS_RS(ctx->opcode));                                      // 0.0
/*432 */             int16_t offset = ZIMM(ctx->opcode, 0, 4) << 1;                              // 0.0
/*436 */             gen_st(ctx, OPC_SH, rd, rb, offset);                                        // 0.0
/*438 */         }                                                                               // 0.0
/*440 */         break;                                                                          // 0.0
/*442 */     case SWSP16:                                                                        // 0.0
/*444 */         {                                                                               // 0.0
/*446 */             int rd = (ctx->opcode >> 5) & 0x1f;                                         // 0.0
/*448 */             int rb = 29;            /* SP */                                            // 0.0
/*450 */             int16_t offset = ZIMM(ctx->opcode, 0, 5) << 2;                              // 0.0
/*454 */             gen_st(ctx, OPC_SW, rd, rb, offset);                                        // 0.0
/*456 */         }                                                                               // 0.0
/*458 */         break;                                                                          // 0.0
/*460 */     case SW16:                                                                          // 0.0
/*462 */         {                                                                               // 0.0
/*464 */             int rd = mmreg2(uMIPS_RD(ctx->opcode));                                     // 0.0
/*466 */             int rb = mmreg(uMIPS_RS(ctx->opcode));                                      // 0.0
/*468 */             int16_t offset = ZIMM(ctx->opcode, 0, 4) << 2;                              // 0.0
/*472 */             gen_st(ctx, OPC_SW, rd, rb, offset);                                        // 0.0
/*474 */         }                                                                               // 0.0
/*476 */         break;                                                                          // 0.0
/*478 */     case MOVE16:                                                                        // 0.0
/*480 */         {                                                                               // 0.0
/*482 */             int rd = uMIPS_RD5(ctx->opcode);                                            // 0.0
/*484 */             int rs = uMIPS_RS5(ctx->opcode);                                            // 0.0
/*488 */             gen_arith_imm(ctx, OPC_ADDIU, rd, rs, 0);                                   // 0.0
/*490 */         }                                                                               // 0.0
/*492 */         break;                                                                          // 0.0
/*494 */     case ANDI16:                                                                        // 0.0
/*496 */         gen_andi16(ctx);                                                                // 0.0
/*498 */         break;                                                                          // 0.0
/*500 */     case POOL16D:                                                                       // 0.0
/*502 */         switch (ctx->opcode & 0x1) {                                                    // 0.0
/*504 */         case ADDIUS5:                                                                   // 0.0
/*506 */             gen_addius5(ctx);                                                           // 0.0
/*508 */             break;                                                                      // 0.0
/*510 */         case ADDIUSP:                                                                   // 0.0
/*512 */             gen_addiusp(ctx);                                                           // 0.0
/*514 */             break;                                                                      // 0.0
/*516 */         }                                                                               // 0.0
/*518 */         break;                                                                          // 0.0
/*520 */     case POOL16E:                                                                       // 0.0
/*522 */         switch (ctx->opcode & 0x1) {                                                    // 0.0
/*524 */         case ADDIUR2:                                                                   // 0.0
/*526 */             gen_addiur2(ctx);                                                           // 0.0
/*528 */             break;                                                                      // 0.0
/*530 */         case ADDIUR1SP:                                                                 // 0.0
/*532 */             gen_addiur1sp(ctx);                                                         // 0.0
/*534 */             break;                                                                      // 0.0
/*536 */         }                                                                               // 0.0
/*538 */         break;                                                                          // 0.0
/*540 */     case B16:                                                                           // 0.0
/*542 */         gen_compute_branch(ctx, OPC_BEQ, 2, 0, 0,                                       // 0.0
/*544 */                            SIMM(ctx->opcode, 0, 10) << 1);                              // 0.0
/*546 */         *is_branch = 1;                                                                 // 0.0
/*548 */         break;                                                                          // 0.0
/*550 */     case BNEZ16:                                                                        // 0.0
/*552 */     case BEQZ16:                                                                        // 0.0
/*554 */         gen_compute_branch(ctx, op == BNEZ16 ? OPC_BNE : OPC_BEQ, 2,                    // 0.0
/*556 */                            mmreg(uMIPS_RD(ctx->opcode)),                                // 0.0
/*558 */                            0, SIMM(ctx->opcode, 0, 7) << 1);                            // 0.0
/*560 */         *is_branch = 1;                                                                 // 0.0
/*562 */         break;                                                                          // 0.0
/*564 */     case LI16:                                                                          // 0.0
/*566 */         {                                                                               // 0.0
/*568 */             int reg = mmreg(uMIPS_RD(ctx->opcode));                                     // 0.0
/*570 */             int imm = ZIMM(ctx->opcode, 0, 7);                                          // 0.0
/*574 */             imm = (imm == 0x7f ? -1 : imm);                                             // 0.0
/*576 */             tcg_gen_movi_tl(cpu_gpr[reg], imm);                                         // 0.0
/*578 */         }                                                                               // 0.0
/*580 */         break;                                                                          // 0.0
/*582 */     case RES_20:                                                                        // 0.0
/*584 */     case RES_28:                                                                        // 0.0
/*586 */     case RES_29:                                                                        // 0.0
/*588 */     case RES_30:                                                                        // 0.0
/*590 */     case RES_31:                                                                        // 0.0
/*592 */     case RES_38:                                                                        // 0.0
/*594 */     case RES_39:                                                                        // 0.0
/*596 */         generate_exception(ctx, EXCP_RI);                                               // 0.0
/*598 */         break;                                                                          // 0.0
/*600 */     default:                                                                            // 0.0
/*602 */         decode_micromips32_opc (env, ctx, op, is_branch);                               // 0.0
/*604 */         return 4;                                                                       // 0.0
/*606 */     }                                                                                   // 0.0
/*610 */     return 2;                                                                           // 0.0
/*612 */ }                                                                                       // 0.0
