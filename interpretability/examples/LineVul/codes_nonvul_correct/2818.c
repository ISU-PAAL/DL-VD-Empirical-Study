// commit message qemu@42a268c241 (target=0, prob=0.07910666, correct=True): tcg: Change translator-side labels to a pointer
/*0   */ static void gen_loongson_multimedia(DisasContext *ctx, int rd, int rs, int rt)  // (3) 0.05469
/*2   */ {                                                                               // (27) 0.001953
/*4   */     const char *opn = "loongson_cp2";                                           // (10) 0.0332
/*6   */     uint32_t opc, shift_max;                                                    // (15) 0.02734
/*8   */     TCGv_i64 t0, t1;                                                            // (13) 0.0293
/*12  */     opc = MASK_LMI(ctx->opcode);                                                // (11) 0.0332
/*14  */     switch (opc) {                                                              // (21) 0.01758
/*16  */     case OPC_ADD_CP2:                                                           // (20) 0.02344
/*18  */     case OPC_SUB_CP2:                                                           // (17) 0.02539
/*20  */     case OPC_DADD_CP2:                                                          // (18) 0.02539
/*22  */     case OPC_DSUB_CP2:                                                          // (19) 0.02539
/*24  */         t0 = tcg_temp_local_new_i64();                                          // (4) 0.04297
/*26  */         t1 = tcg_temp_local_new_i64();                                          // (5) 0.04297
/*28  */         break;                                                                  // (22) 0.01758
/*30  */     default:                                                                    // (25) 0.009766
/*32  */         t0 = tcg_temp_new_i64();                                                // (6) 0.03906
/*34  */         t1 = tcg_temp_new_i64();                                                // (7) 0.03906
/*36  */         break;                                                                  // (23) 0.01758
/*38  */     }                                                                           // (26) 0.007812
/*42  */     gen_load_fpr64(ctx, t0, rs);                                                // (9) 0.03516
/*44  */     gen_load_fpr64(ctx, t1, rt);                                                // (8) 0.03711
/*48  */ #define LMI_HELPER(UP, LO) \                                                    // (16) 0.02734
/*50  */     case OPC_##UP: gen_helper_##LO(t0, t0, t1); opn = #LO; break                // (1) 0.06641
/*52  */ #define LMI_HELPER_1(UP, LO) \                                                  // (12) 0.03125
/*54  */     case OPC_##UP: gen_helper_##LO(t0, t0); opn = #LO; break                    // (2) 0.06055
/*56  */ #define LMI_DIRECT(UP, LO, OP) \                                                // (14) 0.0293
/*58  */     case OPC_##UP: tcg_gen_##OP##_i64(t0, t0, t1); opn = #LO; break             // (0) 0.07422
/*62  */     switch (opc) {                                                              // (24) 0.01758
/*64  */     LMI_HELPER(PADDSH, paddsh);                                                 // 0.0
/*66  */     LMI_HELPER(PADDUSH, paddush);                                               // 0.0
/*68  */     LMI_HELPER(PADDH, paddh);                                                   // 0.0
/*70  */     LMI_HELPER(PADDW, paddw);                                                   // 0.0
/*72  */     LMI_HELPER(PADDSB, paddsb);                                                 // 0.0
/*74  */     LMI_HELPER(PADDUSB, paddusb);                                               // 0.0
/*76  */     LMI_HELPER(PADDB, paddb);                                                   // 0.0
/*80  */     LMI_HELPER(PSUBSH, psubsh);                                                 // 0.0
/*82  */     LMI_HELPER(PSUBUSH, psubush);                                               // 0.0
/*84  */     LMI_HELPER(PSUBH, psubh);                                                   // 0.0
/*86  */     LMI_HELPER(PSUBW, psubw);                                                   // 0.0
/*88  */     LMI_HELPER(PSUBSB, psubsb);                                                 // 0.0
/*90  */     LMI_HELPER(PSUBUSB, psubusb);                                               // 0.0
/*92  */     LMI_HELPER(PSUBB, psubb);                                                   // 0.0
/*96  */     LMI_HELPER(PSHUFH, pshufh);                                                 // 0.0
/*98  */     LMI_HELPER(PACKSSWH, packsswh);                                             // 0.0
/*100 */     LMI_HELPER(PACKSSHB, packsshb);                                             // 0.0
/*102 */     LMI_HELPER(PACKUSHB, packushb);                                             // 0.0
/*106 */     LMI_HELPER(PUNPCKLHW, punpcklhw);                                           // 0.0
/*108 */     LMI_HELPER(PUNPCKHHW, punpckhhw);                                           // 0.0
/*110 */     LMI_HELPER(PUNPCKLBH, punpcklbh);                                           // 0.0
/*112 */     LMI_HELPER(PUNPCKHBH, punpckhbh);                                           // 0.0
/*114 */     LMI_HELPER(PUNPCKLWD, punpcklwd);                                           // 0.0
/*116 */     LMI_HELPER(PUNPCKHWD, punpckhwd);                                           // 0.0
/*120 */     LMI_HELPER(PAVGH, pavgh);                                                   // 0.0
/*122 */     LMI_HELPER(PAVGB, pavgb);                                                   // 0.0
/*124 */     LMI_HELPER(PMAXSH, pmaxsh);                                                 // 0.0
/*126 */     LMI_HELPER(PMINSH, pminsh);                                                 // 0.0
/*128 */     LMI_HELPER(PMAXUB, pmaxub);                                                 // 0.0
/*130 */     LMI_HELPER(PMINUB, pminub);                                                 // 0.0
/*134 */     LMI_HELPER(PCMPEQW, pcmpeqw);                                               // 0.0
/*136 */     LMI_HELPER(PCMPGTW, pcmpgtw);                                               // 0.0
/*138 */     LMI_HELPER(PCMPEQH, pcmpeqh);                                               // 0.0
/*140 */     LMI_HELPER(PCMPGTH, pcmpgth);                                               // 0.0
/*142 */     LMI_HELPER(PCMPEQB, pcmpeqb);                                               // 0.0
/*144 */     LMI_HELPER(PCMPGTB, pcmpgtb);                                               // 0.0
/*148 */     LMI_HELPER(PSLLW, psllw);                                                   // 0.0
/*150 */     LMI_HELPER(PSLLH, psllh);                                                   // 0.0
/*152 */     LMI_HELPER(PSRLW, psrlw);                                                   // 0.0
/*154 */     LMI_HELPER(PSRLH, psrlh);                                                   // 0.0
/*156 */     LMI_HELPER(PSRAW, psraw);                                                   // 0.0
/*158 */     LMI_HELPER(PSRAH, psrah);                                                   // 0.0
/*162 */     LMI_HELPER(PMULLH, pmullh);                                                 // 0.0
/*164 */     LMI_HELPER(PMULHH, pmulhh);                                                 // 0.0
/*166 */     LMI_HELPER(PMULHUH, pmulhuh);                                               // 0.0
/*168 */     LMI_HELPER(PMADDHW, pmaddhw);                                               // 0.0
/*172 */     LMI_HELPER(PASUBUB, pasubub);                                               // 0.0
/*174 */     LMI_HELPER_1(BIADD, biadd);                                                 // 0.0
/*176 */     LMI_HELPER_1(PMOVMSKB, pmovmskb);                                           // 0.0
/*180 */     LMI_DIRECT(PADDD, paddd, add);                                              // 0.0
/*182 */     LMI_DIRECT(PSUBD, psubd, sub);                                              // 0.0
/*184 */     LMI_DIRECT(XOR_CP2, xor, xor);                                              // 0.0
/*186 */     LMI_DIRECT(NOR_CP2, nor, nor);                                              // 0.0
/*188 */     LMI_DIRECT(AND_CP2, and, and);                                              // 0.0
/*190 */     LMI_DIRECT(PANDN, pandn, andc);                                             // 0.0
/*192 */     LMI_DIRECT(OR, or, or);                                                     // 0.0
/*196 */     case OPC_PINSRH_0:                                                          // 0.0
/*198 */         tcg_gen_deposit_i64(t0, t0, t1, 0, 16);                                 // 0.0
/*200 */         opn = "pinsrh_0";                                                       // 0.0
/*202 */         break;                                                                  // 0.0
/*204 */     case OPC_PINSRH_1:                                                          // 0.0
/*206 */         tcg_gen_deposit_i64(t0, t0, t1, 16, 16);                                // 0.0
/*208 */         opn = "pinsrh_1";                                                       // 0.0
/*210 */         break;                                                                  // 0.0
/*212 */     case OPC_PINSRH_2:                                                          // 0.0
/*214 */         tcg_gen_deposit_i64(t0, t0, t1, 32, 16);                                // 0.0
/*216 */         opn = "pinsrh_2";                                                       // 0.0
/*218 */         break;                                                                  // 0.0
/*220 */     case OPC_PINSRH_3:                                                          // 0.0
/*222 */         tcg_gen_deposit_i64(t0, t0, t1, 48, 16);                                // 0.0
/*224 */         opn = "pinsrh_3";                                                       // 0.0
/*226 */         break;                                                                  // 0.0
/*230 */     case OPC_PEXTRH:                                                            // 0.0
/*232 */         tcg_gen_andi_i64(t1, t1, 3);                                            // 0.0
/*234 */         tcg_gen_shli_i64(t1, t1, 4);                                            // 0.0
/*236 */         tcg_gen_shr_i64(t0, t0, t1);                                            // 0.0
/*238 */         tcg_gen_ext16u_i64(t0, t0);                                             // 0.0
/*240 */         opn = "pextrh";                                                         // 0.0
/*242 */         break;                                                                  // 0.0
/*246 */     case OPC_ADDU_CP2:                                                          // 0.0
/*248 */         tcg_gen_add_i64(t0, t0, t1);                                            // 0.0
/*250 */         tcg_gen_ext32s_i64(t0, t0);                                             // 0.0
/*252 */         opn = "addu";                                                           // 0.0
/*254 */         break;                                                                  // 0.0
/*256 */     case OPC_SUBU_CP2:                                                          // 0.0
/*258 */         tcg_gen_sub_i64(t0, t0, t1);                                            // 0.0
/*260 */         tcg_gen_ext32s_i64(t0, t0);                                             // 0.0
/*262 */         opn = "addu";                                                           // 0.0
/*264 */         break;                                                                  // 0.0
/*268 */     case OPC_SLL_CP2:                                                           // 0.0
/*270 */         opn = "sll";                                                            // 0.0
/*272 */         shift_max = 32;                                                         // 0.0
/*274 */         goto do_shift;                                                          // 0.0
/*276 */     case OPC_SRL_CP2:                                                           // 0.0
/*278 */         opn = "srl";                                                            // 0.0
/*280 */         shift_max = 32;                                                         // 0.0
/*282 */         goto do_shift;                                                          // 0.0
/*284 */     case OPC_SRA_CP2:                                                           // 0.0
/*286 */         opn = "sra";                                                            // 0.0
/*288 */         shift_max = 32;                                                         // 0.0
/*290 */         goto do_shift;                                                          // 0.0
/*292 */     case OPC_DSLL_CP2:                                                          // 0.0
/*294 */         opn = "dsll";                                                           // 0.0
/*296 */         shift_max = 64;                                                         // 0.0
/*298 */         goto do_shift;                                                          // 0.0
/*300 */     case OPC_DSRL_CP2:                                                          // 0.0
/*302 */         opn = "dsrl";                                                           // 0.0
/*304 */         shift_max = 64;                                                         // 0.0
/*306 */         goto do_shift;                                                          // 0.0
/*308 */     case OPC_DSRA_CP2:                                                          // 0.0
/*310 */         opn = "dsra";                                                           // 0.0
/*312 */         shift_max = 64;                                                         // 0.0
/*314 */         goto do_shift;                                                          // 0.0
/*316 */     do_shift:                                                                   // 0.0
/*318 */         /* Make sure shift count isn't TCG undefined behaviour.  */             // 0.0
/*320 */         tcg_gen_andi_i64(t1, t1, shift_max - 1);                                // 0.0
/*324 */         switch (opc) {                                                          // 0.0
/*326 */         case OPC_SLL_CP2:                                                       // 0.0
/*328 */         case OPC_DSLL_CP2:                                                      // 0.0
/*330 */             tcg_gen_shl_i64(t0, t0, t1);                                        // 0.0
/*332 */             break;                                                              // 0.0
/*334 */         case OPC_SRA_CP2:                                                       // 0.0
/*336 */         case OPC_DSRA_CP2:                                                      // 0.0
/*338 */             /* Since SRA is UndefinedResult without sign-extended inputs,       // 0.0
/*340 */                we can treat SRA and DSRA the same.  */                          // 0.0
/*342 */             tcg_gen_sar_i64(t0, t0, t1);                                        // 0.0
/*344 */             break;                                                              // 0.0
/*346 */         case OPC_SRL_CP2:                                                       // 0.0
/*348 */             /* We want to shift in zeros for SRL; zero-extend first.  */        // 0.0
/*350 */             tcg_gen_ext32u_i64(t0, t0);                                         // 0.0
/*352 */             /* FALLTHRU */                                                      // 0.0
/*354 */         case OPC_DSRL_CP2:                                                      // 0.0
/*356 */             tcg_gen_shr_i64(t0, t0, t1);                                        // 0.0
/*358 */             break;                                                              // 0.0
/*360 */         }                                                                       // 0.0
/*364 */         if (shift_max == 32) {                                                  // 0.0
/*366 */             tcg_gen_ext32s_i64(t0, t0);                                         // 0.0
/*368 */         }                                                                       // 0.0
/*372 */         /* Shifts larger than MAX produce zero.  */                             // 0.0
/*374 */         tcg_gen_setcondi_i64(TCG_COND_LTU, t1, t1, shift_max);                  // 0.0
/*376 */         tcg_gen_neg_i64(t1, t1);                                                // 0.0
/*378 */         tcg_gen_and_i64(t0, t0, t1);                                            // 0.0
/*380 */         break;                                                                  // 0.0
/*384 */     case OPC_ADD_CP2:                                                           // 0.0
/*386 */     case OPC_DADD_CP2:                                                          // 0.0
/*388 */         {                                                                       // 0.0
/*390 */             TCGv_i64 t2 = tcg_temp_new_i64();                                   // 0.0
/*392 */             int lab = gen_new_label();                                          // 0.0
/*396 */             tcg_gen_mov_i64(t2, t0);                                            // 0.0
/*398 */             tcg_gen_add_i64(t0, t1, t2);                                        // 0.0
/*400 */             if (opc == OPC_ADD_CP2) {                                           // 0.0
/*402 */                 tcg_gen_ext32s_i64(t0, t0);                                     // 0.0
/*404 */             }                                                                   // 0.0
/*406 */             tcg_gen_xor_i64(t1, t1, t2);                                        // 0.0
/*408 */             tcg_gen_xor_i64(t2, t2, t0);                                        // 0.0
/*410 */             tcg_gen_andc_i64(t1, t2, t1);                                       // 0.0
/*412 */             tcg_temp_free_i64(t2);                                              // 0.0
/*414 */             tcg_gen_brcondi_i64(TCG_COND_GE, t1, 0, lab);                       // 0.0
/*416 */             generate_exception(ctx, EXCP_OVERFLOW);                             // 0.0
/*418 */             gen_set_label(lab);                                                 // 0.0
/*422 */             opn = (opc == OPC_ADD_CP2 ? "add" : "dadd");                        // 0.0
/*424 */             break;                                                              // 0.0
/*426 */         }                                                                       // 0.0
/*430 */     case OPC_SUB_CP2:                                                           // 0.0
/*432 */     case OPC_DSUB_CP2:                                                          // 0.0
/*434 */         {                                                                       // 0.0
/*436 */             TCGv_i64 t2 = tcg_temp_new_i64();                                   // 0.0
/*438 */             int lab = gen_new_label();                                          // 0.0
/*442 */             tcg_gen_mov_i64(t2, t0);                                            // 0.0
/*444 */             tcg_gen_sub_i64(t0, t1, t2);                                        // 0.0
/*446 */             if (opc == OPC_SUB_CP2) {                                           // 0.0
/*448 */                 tcg_gen_ext32s_i64(t0, t0);                                     // 0.0
/*450 */             }                                                                   // 0.0
/*452 */             tcg_gen_xor_i64(t1, t1, t2);                                        // 0.0
/*454 */             tcg_gen_xor_i64(t2, t2, t0);                                        // 0.0
/*456 */             tcg_gen_and_i64(t1, t1, t2);                                        // 0.0
/*458 */             tcg_temp_free_i64(t2);                                              // 0.0
/*460 */             tcg_gen_brcondi_i64(TCG_COND_GE, t1, 0, lab);                       // 0.0
/*462 */             generate_exception(ctx, EXCP_OVERFLOW);                             // 0.0
/*464 */             gen_set_label(lab);                                                 // 0.0
/*468 */             opn = (opc == OPC_SUB_CP2 ? "sub" : "dsub");                        // 0.0
/*470 */             break;                                                              // 0.0
/*472 */         }                                                                       // 0.0
/*476 */     case OPC_PMULUW:                                                            // 0.0
/*478 */         tcg_gen_ext32u_i64(t0, t0);                                             // 0.0
/*480 */         tcg_gen_ext32u_i64(t1, t1);                                             // 0.0
/*482 */         tcg_gen_mul_i64(t0, t0, t1);                                            // 0.0
/*484 */         opn = "pmuluw";                                                         // 0.0
/*486 */         break;                                                                  // 0.0
/*490 */     case OPC_SEQU_CP2:                                                          // 0.0
/*492 */     case OPC_SEQ_CP2:                                                           // 0.0
/*494 */     case OPC_SLTU_CP2:                                                          // 0.0
/*496 */     case OPC_SLT_CP2:                                                           // 0.0
/*498 */     case OPC_SLEU_CP2:                                                          // 0.0
/*500 */     case OPC_SLE_CP2:                                                           // 0.0
/*502 */         /* ??? Document is unclear: Set FCC[CC].  Does that mean the            // 0.0
/*504 */            FD field is the CC field?  */                                        // 0.0
/*506 */     default:                                                                    // 0.0
/*508 */         MIPS_INVAL(opn);                                                        // 0.0
/*510 */         generate_exception(ctx, EXCP_RI);                                       // 0.0
/*512 */         return;                                                                 // 0.0
/*514 */     }                                                                           // 0.0
/*518 */ #undef LMI_HELPER                                                               // 0.0
/*520 */ #undef LMI_DIRECT                                                               // 0.0
/*524 */     gen_store_fpr64(ctx, t0, rd);                                               // 0.0
/*528 */     (void)opn; /* avoid a compiler warning */                                   // 0.0
/*530 */     MIPS_DEBUG("%s %s, %s, %s", opn,                                            // 0.0
/*532 */                fregnames[rd], fregnames[rs], fregnames[rt]);                    // 0.0
/*534 */     tcg_temp_free_i64(t0);                                                      // 0.0
/*536 */     tcg_temp_free_i64(t1);                                                      // 0.0
/*538 */ }                                                                               // 0.0
