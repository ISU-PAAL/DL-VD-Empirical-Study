// commit message qemu@5238c88657 (target=0, prob=0.6396255, correct=False): target-alpha: Introduce REQUIRE_TB_FLAG
/*0    */ static ExitStatus translate_one(DisasContext *ctx, uint32_t insn)                 // (4) 0.03906
/*2    */ {                                                                                 // (31) 0.001953
/*4    */     uint32_t palcode;                                                             // (23) 0.01953
/*6    */     int32_t disp21, disp16;                                                       // (15) 0.02539
/*8    */ #ifndef CONFIG_USER_ONLY                                                          // (22) 0.01953
/*10   */     int32_t disp12;                                                               // (20) 0.01953
/*12   */ #endif                                                                            // (29) 0.003906
/*14   */     uint16_t fn11;                                                                // (24) 0.01953
/*16   */     uint8_t opc, ra, rb, rc, fpfn, fn7, islit, real_islit;                        // (1) 0.0625
/*18   */     uint8_t lit;                                                                  // (26) 0.01758
/*20   */     ExitStatus ret;                                                               // (27) 0.01367
/*24   */     /* Decode all instruction fields */                                           // (21) 0.01953
/*26   */     opc = insn >> 26;                                                             // (18) 0.02148
/*28   */     ra = (insn >> 21) & 0x1F;                                                     // (11) 0.0332
/*30   */     rb = (insn >> 16) & 0x1F;                                                     // (10) 0.03516
/*32   */     rc = insn & 0x1F;                                                             // (16) 0.02539
/*34   */     real_islit = islit = (insn >> 12) & 1;                                        // (6) 0.03906
/*36   */     if (rb == 31 && !islit) {                                                     // (14) 0.02734
/*38   */         islit = 1;                                                                // (17) 0.02344
/*40   */         lit = 0;                                                                  // (19) 0.02148
/*42   */     } else                                                                        // (28) 0.009766
/*44   */         lit = (insn >> 13) & 0xFF;                                                // (7) 0.03906
/*46   */     palcode = insn & 0x03FFFFFF;                                                  // (12) 0.0293
/*48   */     disp21 = ((int32_t)((insn & 0x001FFFFF) << 11)) >> 11;                        // (3) 0.05469
/*50   */     disp16 = (int16_t)(insn & 0x0000FFFF);                                        // (5) 0.03906
/*52   */ #ifndef CONFIG_USER_ONLY                                                          // (25) 0.01953
/*54   */     disp12 = (int32_t)((insn & 0x00000FFF) << 20) >> 20;                          // (2) 0.05469
/*56   */ #endif                                                                            // (30) 0.003906
/*58   */     fn11 = (insn >> 5) & 0x000007FF;                                              // (8) 0.03711
/*60   */     fpfn = fn11 & 0x3F;                                                           // (13) 0.0293
/*62   */     fn7 = (insn >> 5) & 0x0000007F;                                               // (9) 0.03711
/*64   */     LOG_DISAS("opc %02x ra %2d rb %2d rc %2d disp16 %6d\n",                       // (0) 0.06641
/*66   */               opc, ra, rb, rc, disp16);                                           // 0.0
/*70   */     ret = NO_EXIT;                                                                // 0.0
/*72   */     switch (opc) {                                                                // 0.0
/*74   */     case 0x00:                                                                    // 0.0
/*76   */         /* CALL_PAL */                                                            // 0.0
/*78   */         ret = gen_call_pal(ctx, palcode);                                         // 0.0
/*80   */         break;                                                                    // 0.0
/*82   */     case 0x01:                                                                    // 0.0
/*84   */         /* OPC01 */                                                               // 0.0
/*86   */         goto invalid_opc;                                                         // 0.0
/*88   */     case 0x02:                                                                    // 0.0
/*90   */         /* OPC02 */                                                               // 0.0
/*92   */         goto invalid_opc;                                                         // 0.0
/*94   */     case 0x03:                                                                    // 0.0
/*96   */         /* OPC03 */                                                               // 0.0
/*98   */         goto invalid_opc;                                                         // 0.0
/*100  */     case 0x04:                                                                    // 0.0
/*102  */         /* OPC04 */                                                               // 0.0
/*104  */         goto invalid_opc;                                                         // 0.0
/*106  */     case 0x05:                                                                    // 0.0
/*108  */         /* OPC05 */                                                               // 0.0
/*110  */         goto invalid_opc;                                                         // 0.0
/*112  */     case 0x06:                                                                    // 0.0
/*114  */         /* OPC06 */                                                               // 0.0
/*116  */         goto invalid_opc;                                                         // 0.0
/*118  */     case 0x07:                                                                    // 0.0
/*120  */         /* OPC07 */                                                               // 0.0
/*122  */         goto invalid_opc;                                                         // 0.0
/*124  */     case 0x08:                                                                    // 0.0
/*126  */         /* LDA */                                                                 // 0.0
/*128  */         if (likely(ra != 31)) {                                                   // 0.0
/*130  */             if (rb != 31) {                                                       // 0.0
/*132  */                 tcg_gen_addi_i64(cpu_ir[ra], cpu_ir[rb], disp16);                 // 0.0
/*134  */             } else {                                                              // 0.0
/*136  */                 tcg_gen_movi_i64(cpu_ir[ra], disp16);                             // 0.0
/*138  */             }                                                                     // 0.0
/*140  */         }                                                                         // 0.0
/*142  */         break;                                                                    // 0.0
/*144  */     case 0x09:                                                                    // 0.0
/*146  */         /* LDAH */                                                                // 0.0
/*148  */         if (likely(ra != 31)) {                                                   // 0.0
/*150  */             if (rb != 31) {                                                       // 0.0
/*152  */                 tcg_gen_addi_i64(cpu_ir[ra], cpu_ir[rb], disp16 << 16);           // 0.0
/*154  */             } else {                                                              // 0.0
/*156  */                 tcg_gen_movi_i64(cpu_ir[ra], disp16 << 16);                       // 0.0
/*158  */             }                                                                     // 0.0
/*160  */         }                                                                         // 0.0
/*162  */         break;                                                                    // 0.0
/*164  */     case 0x0A:                                                                    // 0.0
/*166  */         /* LDBU */                                                                // 0.0
/*168  */         if (ctx->tb->flags & TB_FLAGS_AMASK_BWX) {                                // 0.0
/*170  */             gen_load_mem(ctx, &tcg_gen_qemu_ld8u, ra, rb, disp16, 0, 0);          // 0.0
/*172  */             break;                                                                // 0.0
/*174  */         }                                                                         // 0.0
/*176  */         goto invalid_opc;                                                         // 0.0
/*178  */     case 0x0B:                                                                    // 0.0
/*180  */         /* LDQ_U */                                                               // 0.0
/*182  */         gen_load_mem(ctx, &tcg_gen_qemu_ld64, ra, rb, disp16, 0, 1);              // 0.0
/*184  */         break;                                                                    // 0.0
/*186  */     case 0x0C:                                                                    // 0.0
/*188  */         /* LDWU */                                                                // 0.0
/*190  */         if (ctx->tb->flags & TB_FLAGS_AMASK_BWX) {                                // 0.0
/*192  */             gen_load_mem(ctx, &tcg_gen_qemu_ld16u, ra, rb, disp16, 0, 0);         // 0.0
/*194  */             break;                                                                // 0.0
/*196  */         }                                                                         // 0.0
/*198  */         goto invalid_opc;                                                         // 0.0
/*200  */     case 0x0D:                                                                    // 0.0
/*202  */         /* STW */                                                                 // 0.0
/*204  */         gen_store_mem(ctx, &tcg_gen_qemu_st16, ra, rb, disp16, 0, 0);             // 0.0
/*206  */         break;                                                                    // 0.0
/*208  */     case 0x0E:                                                                    // 0.0
/*210  */         /* STB */                                                                 // 0.0
/*212  */         gen_store_mem(ctx, &tcg_gen_qemu_st8, ra, rb, disp16, 0, 0);              // 0.0
/*214  */         break;                                                                    // 0.0
/*216  */     case 0x0F:                                                                    // 0.0
/*218  */         /* STQ_U */                                                               // 0.0
/*220  */         gen_store_mem(ctx, &tcg_gen_qemu_st64, ra, rb, disp16, 0, 1);             // 0.0
/*222  */         break;                                                                    // 0.0
/*224  */     case 0x10:                                                                    // 0.0
/*226  */         switch (fn7) {                                                            // 0.0
/*228  */         case 0x00:                                                                // 0.0
/*230  */             /* ADDL */                                                            // 0.0
/*232  */             if (likely(rc != 31)) {                                               // 0.0
/*234  */                 if (ra != 31) {                                                   // 0.0
/*236  */                     if (islit) {                                                  // 0.0
/*238  */                         tcg_gen_addi_i64(cpu_ir[rc], cpu_ir[ra], lit);            // 0.0
/*240  */                         tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);               // 0.0
/*242  */                     } else {                                                      // 0.0
/*244  */                         tcg_gen_add_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);      // 0.0
/*246  */                         tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);               // 0.0
/*248  */                     }                                                             // 0.0
/*250  */                 } else {                                                          // 0.0
/*252  */                     if (islit) {                                                  // 0.0
/*254  */                         tcg_gen_movi_i64(cpu_ir[rc], lit);                        // 0.0
/*256  */                     } else {                                                      // 0.0
/*258  */                         tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rb]);               // 0.0
/*260  */                     }                                                             // 0.0
/*262  */                 }                                                                 // 0.0
/*264  */             }                                                                     // 0.0
/*266  */             break;                                                                // 0.0
/*268  */         case 0x02:                                                                // 0.0
/*270  */             /* S4ADDL */                                                          // 0.0
/*272  */             if (likely(rc != 31)) {                                               // 0.0
/*274  */                 if (ra != 31) {                                                   // 0.0
/*276  */                     TCGv tmp = tcg_temp_new();                                    // 0.0
/*278  */                     tcg_gen_shli_i64(tmp, cpu_ir[ra], 2);                         // 0.0
/*280  */                     if (islit) {                                                  // 0.0
/*282  */                         tcg_gen_addi_i64(tmp, tmp, lit);                          // 0.0
/*284  */                     } else {                                                      // 0.0
/*286  */                         tcg_gen_add_i64(tmp, tmp, cpu_ir[rb]);                    // 0.0
/*288  */                     }                                                             // 0.0
/*290  */                     tcg_gen_ext32s_i64(cpu_ir[rc], tmp);                          // 0.0
/*292  */                     tcg_temp_free(tmp);                                           // 0.0
/*294  */                 } else {                                                          // 0.0
/*296  */                     if (islit) {                                                  // 0.0
/*298  */                         tcg_gen_movi_i64(cpu_ir[rc], lit);                        // 0.0
/*300  */                     } else {                                                      // 0.0
/*302  */                         tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rb]);               // 0.0
/*304  */                     }                                                             // 0.0
/*306  */                 }                                                                 // 0.0
/*308  */             }                                                                     // 0.0
/*310  */             break;                                                                // 0.0
/*312  */         case 0x09:                                                                // 0.0
/*314  */             /* SUBL */                                                            // 0.0
/*316  */             if (likely(rc != 31)) {                                               // 0.0
/*318  */                 if (ra != 31) {                                                   // 0.0
/*320  */                     if (islit) {                                                  // 0.0
/*322  */                         tcg_gen_subi_i64(cpu_ir[rc], cpu_ir[ra], lit);            // 0.0
/*324  */                     } else {                                                      // 0.0
/*326  */                         tcg_gen_sub_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);      // 0.0
/*328  */                     }                                                             // 0.0
/*330  */                     tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);                   // 0.0
/*332  */                 } else {                                                          // 0.0
/*334  */                     if (islit) {                                                  // 0.0
/*336  */                         tcg_gen_movi_i64(cpu_ir[rc], -lit);                       // 0.0
/*338  */                     } else {                                                      // 0.0
/*340  */                         tcg_gen_neg_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*342  */                         tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);               // 0.0
/*344  */                     }                                                             // 0.0
/*346  */                 }                                                                 // 0.0
/*348  */             }                                                                     // 0.0
/*350  */             break;                                                                // 0.0
/*352  */         case 0x0B:                                                                // 0.0
/*354  */             /* S4SUBL */                                                          // 0.0
/*356  */             if (likely(rc != 31)) {                                               // 0.0
/*358  */                 if (ra != 31) {                                                   // 0.0
/*360  */                     TCGv tmp = tcg_temp_new();                                    // 0.0
/*362  */                     tcg_gen_shli_i64(tmp, cpu_ir[ra], 2);                         // 0.0
/*364  */                     if (islit) {                                                  // 0.0
/*366  */                         tcg_gen_subi_i64(tmp, tmp, lit);                          // 0.0
/*368  */                     } else {                                                      // 0.0
/*370  */                         tcg_gen_sub_i64(tmp, tmp, cpu_ir[rb]);                    // 0.0
/*372  */                     }                                                             // 0.0
/*374  */                     tcg_gen_ext32s_i64(cpu_ir[rc], tmp);                          // 0.0
/*376  */                     tcg_temp_free(tmp);                                           // 0.0
/*378  */                 } else {                                                          // 0.0
/*380  */                     if (islit) {                                                  // 0.0
/*382  */                         tcg_gen_movi_i64(cpu_ir[rc], -lit);                       // 0.0
/*384  */                     } else {                                                      // 0.0
/*386  */                         tcg_gen_neg_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*388  */                         tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);               // 0.0
/*390  */                     }                                                             // 0.0
/*392  */                 }                                                                 // 0.0
/*394  */             }                                                                     // 0.0
/*396  */             break;                                                                // 0.0
/*398  */         case 0x0F:                                                                // 0.0
/*400  */             /* CMPBGE */                                                          // 0.0
/*402  */             gen_cmpbge(ra, rb, rc, islit, lit);                                   // 0.0
/*404  */             break;                                                                // 0.0
/*406  */         case 0x12:                                                                // 0.0
/*408  */             /* S8ADDL */                                                          // 0.0
/*410  */             if (likely(rc != 31)) {                                               // 0.0
/*412  */                 if (ra != 31) {                                                   // 0.0
/*414  */                     TCGv tmp = tcg_temp_new();                                    // 0.0
/*416  */                     tcg_gen_shli_i64(tmp, cpu_ir[ra], 3);                         // 0.0
/*418  */                     if (islit) {                                                  // 0.0
/*420  */                         tcg_gen_addi_i64(tmp, tmp, lit);                          // 0.0
/*422  */                     } else {                                                      // 0.0
/*424  */                         tcg_gen_add_i64(tmp, tmp, cpu_ir[rb]);                    // 0.0
/*426  */                     }                                                             // 0.0
/*428  */                     tcg_gen_ext32s_i64(cpu_ir[rc], tmp);                          // 0.0
/*430  */                     tcg_temp_free(tmp);                                           // 0.0
/*432  */                 } else {                                                          // 0.0
/*434  */                     if (islit) {                                                  // 0.0
/*436  */                         tcg_gen_movi_i64(cpu_ir[rc], lit);                        // 0.0
/*438  */                     } else {                                                      // 0.0
/*440  */                         tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rb]);               // 0.0
/*442  */                     }                                                             // 0.0
/*444  */                 }                                                                 // 0.0
/*446  */             }                                                                     // 0.0
/*448  */             break;                                                                // 0.0
/*450  */         case 0x1B:                                                                // 0.0
/*452  */             /* S8SUBL */                                                          // 0.0
/*454  */             if (likely(rc != 31)) {                                               // 0.0
/*456  */                 if (ra != 31) {                                                   // 0.0
/*458  */                     TCGv tmp = tcg_temp_new();                                    // 0.0
/*460  */                     tcg_gen_shli_i64(tmp, cpu_ir[ra], 3);                         // 0.0
/*462  */                     if (islit) {                                                  // 0.0
/*464  */                         tcg_gen_subi_i64(tmp, tmp, lit);                          // 0.0
/*466  */                     } else {                                                      // 0.0
/*468  */                        tcg_gen_sub_i64(tmp, tmp, cpu_ir[rb]);                     // 0.0
/*470  */                     }                                                             // 0.0
/*472  */                     tcg_gen_ext32s_i64(cpu_ir[rc], tmp);                          // 0.0
/*474  */                     tcg_temp_free(tmp);                                           // 0.0
/*476  */                 } else {                                                          // 0.0
/*478  */                     if (islit) {                                                  // 0.0
/*480  */                         tcg_gen_movi_i64(cpu_ir[rc], -lit);                       // 0.0
/*482  */                     } else {                                                      // 0.0
/*484  */                         tcg_gen_neg_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*486  */                         tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);               // 0.0
/*488  */                     }                                                             // 0.0
/*490  */                 }                                                                 // 0.0
/*492  */             }                                                                     // 0.0
/*494  */             break;                                                                // 0.0
/*496  */         case 0x1D:                                                                // 0.0
/*498  */             /* CMPULT */                                                          // 0.0
/*500  */             gen_cmp(TCG_COND_LTU, ra, rb, rc, islit, lit);                        // 0.0
/*502  */             break;                                                                // 0.0
/*504  */         case 0x20:                                                                // 0.0
/*506  */             /* ADDQ */                                                            // 0.0
/*508  */             if (likely(rc != 31)) {                                               // 0.0
/*510  */                 if (ra != 31) {                                                   // 0.0
/*512  */                     if (islit) {                                                  // 0.0
/*514  */                         tcg_gen_addi_i64(cpu_ir[rc], cpu_ir[ra], lit);            // 0.0
/*516  */                     } else {                                                      // 0.0
/*518  */                         tcg_gen_add_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);      // 0.0
/*520  */                     }                                                             // 0.0
/*522  */                 } else {                                                          // 0.0
/*524  */                     if (islit) {                                                  // 0.0
/*526  */                         tcg_gen_movi_i64(cpu_ir[rc], lit);                        // 0.0
/*528  */                     } else {                                                      // 0.0
/*530  */                         tcg_gen_mov_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*532  */                     }                                                             // 0.0
/*534  */                 }                                                                 // 0.0
/*536  */             }                                                                     // 0.0
/*538  */             break;                                                                // 0.0
/*540  */         case 0x22:                                                                // 0.0
/*542  */             /* S4ADDQ */                                                          // 0.0
/*544  */             if (likely(rc != 31)) {                                               // 0.0
/*546  */                 if (ra != 31) {                                                   // 0.0
/*548  */                     TCGv tmp = tcg_temp_new();                                    // 0.0
/*550  */                     tcg_gen_shli_i64(tmp, cpu_ir[ra], 2);                         // 0.0
/*552  */                     if (islit) {                                                  // 0.0
/*554  */                         tcg_gen_addi_i64(cpu_ir[rc], tmp, lit);                   // 0.0
/*556  */                     } else {                                                      // 0.0
/*558  */                         tcg_gen_add_i64(cpu_ir[rc], tmp, cpu_ir[rb]);             // 0.0
/*560  */                     }                                                             // 0.0
/*562  */                     tcg_temp_free(tmp);                                           // 0.0
/*564  */                 } else {                                                          // 0.0
/*566  */                     if (islit) {                                                  // 0.0
/*568  */                         tcg_gen_movi_i64(cpu_ir[rc], lit);                        // 0.0
/*570  */                     } else {                                                      // 0.0
/*572  */                         tcg_gen_mov_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*574  */                     }                                                             // 0.0
/*576  */                 }                                                                 // 0.0
/*578  */             }                                                                     // 0.0
/*580  */             break;                                                                // 0.0
/*582  */         case 0x29:                                                                // 0.0
/*584  */             /* SUBQ */                                                            // 0.0
/*586  */             if (likely(rc != 31)) {                                               // 0.0
/*588  */                 if (ra != 31) {                                                   // 0.0
/*590  */                     if (islit) {                                                  // 0.0
/*592  */                         tcg_gen_subi_i64(cpu_ir[rc], cpu_ir[ra], lit);            // 0.0
/*594  */                     } else {                                                      // 0.0
/*596  */                         tcg_gen_sub_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);      // 0.0
/*598  */                     }                                                             // 0.0
/*600  */                 } else {                                                          // 0.0
/*602  */                     if (islit) {                                                  // 0.0
/*604  */                         tcg_gen_movi_i64(cpu_ir[rc], -lit);                       // 0.0
/*606  */                     } else {                                                      // 0.0
/*608  */                         tcg_gen_neg_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*610  */                     }                                                             // 0.0
/*612  */                 }                                                                 // 0.0
/*614  */             }                                                                     // 0.0
/*616  */             break;                                                                // 0.0
/*618  */         case 0x2B:                                                                // 0.0
/*620  */             /* S4SUBQ */                                                          // 0.0
/*622  */             if (likely(rc != 31)) {                                               // 0.0
/*624  */                 if (ra != 31) {                                                   // 0.0
/*626  */                     TCGv tmp = tcg_temp_new();                                    // 0.0
/*628  */                     tcg_gen_shli_i64(tmp, cpu_ir[ra], 2);                         // 0.0
/*630  */                     if (islit) {                                                  // 0.0
/*632  */                         tcg_gen_subi_i64(cpu_ir[rc], tmp, lit);                   // 0.0
/*634  */                     } else {                                                      // 0.0
/*636  */                         tcg_gen_sub_i64(cpu_ir[rc], tmp, cpu_ir[rb]);             // 0.0
/*638  */                     }                                                             // 0.0
/*640  */                     tcg_temp_free(tmp);                                           // 0.0
/*642  */                 } else {                                                          // 0.0
/*644  */                     if (islit) {                                                  // 0.0
/*646  */                         tcg_gen_movi_i64(cpu_ir[rc], -lit);                       // 0.0
/*648  */                     } else {                                                      // 0.0
/*650  */                         tcg_gen_neg_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*652  */                     }                                                             // 0.0
/*654  */                 }                                                                 // 0.0
/*656  */             }                                                                     // 0.0
/*658  */             break;                                                                // 0.0
/*660  */         case 0x2D:                                                                // 0.0
/*662  */             /* CMPEQ */                                                           // 0.0
/*664  */             gen_cmp(TCG_COND_EQ, ra, rb, rc, islit, lit);                         // 0.0
/*666  */             break;                                                                // 0.0
/*668  */         case 0x32:                                                                // 0.0
/*670  */             /* S8ADDQ */                                                          // 0.0
/*672  */             if (likely(rc != 31)) {                                               // 0.0
/*674  */                 if (ra != 31) {                                                   // 0.0
/*676  */                     TCGv tmp = tcg_temp_new();                                    // 0.0
/*678  */                     tcg_gen_shli_i64(tmp, cpu_ir[ra], 3);                         // 0.0
/*680  */                     if (islit) {                                                  // 0.0
/*682  */                         tcg_gen_addi_i64(cpu_ir[rc], tmp, lit);                   // 0.0
/*684  */                     } else {                                                      // 0.0
/*686  */                         tcg_gen_add_i64(cpu_ir[rc], tmp, cpu_ir[rb]);             // 0.0
/*688  */                     }                                                             // 0.0
/*690  */                     tcg_temp_free(tmp);                                           // 0.0
/*692  */                 } else {                                                          // 0.0
/*694  */                     if (islit) {                                                  // 0.0
/*696  */                         tcg_gen_movi_i64(cpu_ir[rc], lit);                        // 0.0
/*698  */                     } else {                                                      // 0.0
/*700  */                         tcg_gen_mov_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*702  */                     }                                                             // 0.0
/*704  */                 }                                                                 // 0.0
/*706  */             }                                                                     // 0.0
/*708  */             break;                                                                // 0.0
/*710  */         case 0x3B:                                                                // 0.0
/*712  */             /* S8SUBQ */                                                          // 0.0
/*714  */             if (likely(rc != 31)) {                                               // 0.0
/*716  */                 if (ra != 31) {                                                   // 0.0
/*718  */                     TCGv tmp = tcg_temp_new();                                    // 0.0
/*720  */                     tcg_gen_shli_i64(tmp, cpu_ir[ra], 3);                         // 0.0
/*722  */                     if (islit) {                                                  // 0.0
/*724  */                         tcg_gen_subi_i64(cpu_ir[rc], tmp, lit);                   // 0.0
/*726  */                     } else {                                                      // 0.0
/*728  */                         tcg_gen_sub_i64(cpu_ir[rc], tmp, cpu_ir[rb]);             // 0.0
/*730  */                     }                                                             // 0.0
/*732  */                     tcg_temp_free(tmp);                                           // 0.0
/*734  */                 } else {                                                          // 0.0
/*736  */                     if (islit) {                                                  // 0.0
/*738  */                         tcg_gen_movi_i64(cpu_ir[rc], -lit);                       // 0.0
/*740  */                     } else {                                                      // 0.0
/*742  */                         tcg_gen_neg_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*744  */                     }                                                             // 0.0
/*746  */                 }                                                                 // 0.0
/*748  */             }                                                                     // 0.0
/*750  */             break;                                                                // 0.0
/*752  */         case 0x3D:                                                                // 0.0
/*754  */             /* CMPULE */                                                          // 0.0
/*756  */             gen_cmp(TCG_COND_LEU, ra, rb, rc, islit, lit);                        // 0.0
/*758  */             break;                                                                // 0.0
/*760  */         case 0x40:                                                                // 0.0
/*762  */             /* ADDL/V */                                                          // 0.0
/*764  */             gen_addlv(ra, rb, rc, islit, lit);                                    // 0.0
/*766  */             break;                                                                // 0.0
/*768  */         case 0x49:                                                                // 0.0
/*770  */             /* SUBL/V */                                                          // 0.0
/*772  */             gen_sublv(ra, rb, rc, islit, lit);                                    // 0.0
/*774  */             break;                                                                // 0.0
/*776  */         case 0x4D:                                                                // 0.0
/*778  */             /* CMPLT */                                                           // 0.0
/*780  */             gen_cmp(TCG_COND_LT, ra, rb, rc, islit, lit);                         // 0.0
/*782  */             break;                                                                // 0.0
/*784  */         case 0x60:                                                                // 0.0
/*786  */             /* ADDQ/V */                                                          // 0.0
/*788  */             gen_addqv(ra, rb, rc, islit, lit);                                    // 0.0
/*790  */             break;                                                                // 0.0
/*792  */         case 0x69:                                                                // 0.0
/*794  */             /* SUBQ/V */                                                          // 0.0
/*796  */             gen_subqv(ra, rb, rc, islit, lit);                                    // 0.0
/*798  */             break;                                                                // 0.0
/*800  */         case 0x6D:                                                                // 0.0
/*802  */             /* CMPLE */                                                           // 0.0
/*804  */             gen_cmp(TCG_COND_LE, ra, rb, rc, islit, lit);                         // 0.0
/*806  */             break;                                                                // 0.0
/*808  */         default:                                                                  // 0.0
/*810  */             goto invalid_opc;                                                     // 0.0
/*812  */         }                                                                         // 0.0
/*814  */         break;                                                                    // 0.0
/*816  */     case 0x11:                                                                    // 0.0
/*818  */         switch (fn7) {                                                            // 0.0
/*820  */         case 0x00:                                                                // 0.0
/*822  */             /* AND */                                                             // 0.0
/*824  */             if (likely(rc != 31)) {                                               // 0.0
/*826  */                 if (ra == 31) {                                                   // 0.0
/*828  */                     tcg_gen_movi_i64(cpu_ir[rc], 0);                              // 0.0
/*830  */                 } else if (islit) {                                               // 0.0
/*832  */                     tcg_gen_andi_i64(cpu_ir[rc], cpu_ir[ra], lit);                // 0.0
/*834  */                 } else {                                                          // 0.0
/*836  */                     tcg_gen_and_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);          // 0.0
/*838  */                 }                                                                 // 0.0
/*840  */             }                                                                     // 0.0
/*842  */             break;                                                                // 0.0
/*844  */         case 0x08:                                                                // 0.0
/*846  */             /* BIC */                                                             // 0.0
/*848  */             if (likely(rc != 31)) {                                               // 0.0
/*850  */                 if (ra != 31) {                                                   // 0.0
/*852  */                     if (islit) {                                                  // 0.0
/*854  */                         tcg_gen_andi_i64(cpu_ir[rc], cpu_ir[ra], ~lit);           // 0.0
/*856  */                     } else {                                                      // 0.0
/*858  */                         tcg_gen_andc_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);     // 0.0
/*860  */                     }                                                             // 0.0
/*862  */                 } else                                                            // 0.0
/*864  */                     tcg_gen_movi_i64(cpu_ir[rc], 0);                              // 0.0
/*866  */             }                                                                     // 0.0
/*868  */             break;                                                                // 0.0
/*870  */         case 0x14:                                                                // 0.0
/*872  */             /* CMOVLBS */                                                         // 0.0
/*874  */             gen_cmov(TCG_COND_NE, ra, rb, rc, islit, lit, 1);                     // 0.0
/*876  */             break;                                                                // 0.0
/*878  */         case 0x16:                                                                // 0.0
/*880  */             /* CMOVLBC */                                                         // 0.0
/*882  */             gen_cmov(TCG_COND_EQ, ra, rb, rc, islit, lit, 1);                     // 0.0
/*884  */             break;                                                                // 0.0
/*886  */         case 0x20:                                                                // 0.0
/*888  */             /* BIS */                                                             // 0.0
/*890  */             if (likely(rc != 31)) {                                               // 0.0
/*892  */                 if (ra != 31) {                                                   // 0.0
/*894  */                     if (islit) {                                                  // 0.0
/*896  */                         tcg_gen_ori_i64(cpu_ir[rc], cpu_ir[ra], lit);             // 0.0
/*898  */                     } else {                                                      // 0.0
/*900  */                         tcg_gen_or_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);       // 0.0
/*902  */                     }                                                             // 0.0
/*904  */                 } else {                                                          // 0.0
/*906  */                     if (islit) {                                                  // 0.0
/*908  */                         tcg_gen_movi_i64(cpu_ir[rc], lit);                        // 0.0
/*910  */                     } else {                                                      // 0.0
/*912  */                         tcg_gen_mov_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*914  */                     }                                                             // 0.0
/*916  */                 }                                                                 // 0.0
/*918  */             }                                                                     // 0.0
/*920  */             break;                                                                // 0.0
/*922  */         case 0x24:                                                                // 0.0
/*924  */             /* CMOVEQ */                                                          // 0.0
/*926  */             gen_cmov(TCG_COND_EQ, ra, rb, rc, islit, lit, 0);                     // 0.0
/*928  */             break;                                                                // 0.0
/*930  */         case 0x26:                                                                // 0.0
/*932  */             /* CMOVNE */                                                          // 0.0
/*934  */             gen_cmov(TCG_COND_NE, ra, rb, rc, islit, lit, 0);                     // 0.0
/*936  */             break;                                                                // 0.0
/*938  */         case 0x28:                                                                // 0.0
/*940  */             /* ORNOT */                                                           // 0.0
/*942  */             if (likely(rc != 31)) {                                               // 0.0
/*944  */                 if (ra != 31) {                                                   // 0.0
/*946  */                     if (islit) {                                                  // 0.0
/*948  */                         tcg_gen_ori_i64(cpu_ir[rc], cpu_ir[ra], ~lit);            // 0.0
/*950  */                     } else {                                                      // 0.0
/*952  */                         tcg_gen_orc_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);      // 0.0
/*954  */                     }                                                             // 0.0
/*956  */                 } else {                                                          // 0.0
/*958  */                     if (islit) {                                                  // 0.0
/*960  */                         tcg_gen_movi_i64(cpu_ir[rc], ~lit);                       // 0.0
/*962  */                     } else {                                                      // 0.0
/*964  */                         tcg_gen_not_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*966  */                     }                                                             // 0.0
/*968  */                 }                                                                 // 0.0
/*970  */             }                                                                     // 0.0
/*972  */             break;                                                                // 0.0
/*974  */         case 0x40:                                                                // 0.0
/*976  */             /* XOR */                                                             // 0.0
/*978  */             if (likely(rc != 31)) {                                               // 0.0
/*980  */                 if (ra != 31) {                                                   // 0.0
/*982  */                     if (islit) {                                                  // 0.0
/*984  */                         tcg_gen_xori_i64(cpu_ir[rc], cpu_ir[ra], lit);            // 0.0
/*986  */                     } else {                                                      // 0.0
/*988  */                         tcg_gen_xor_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);      // 0.0
/*990  */                     }                                                             // 0.0
/*992  */                 } else {                                                          // 0.0
/*994  */                     if (islit) {                                                  // 0.0
/*996  */                         tcg_gen_movi_i64(cpu_ir[rc], lit);                        // 0.0
/*998  */                     } else {                                                      // 0.0
/*1000 */                         tcg_gen_mov_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*1002 */                     }                                                             // 0.0
/*1004 */                 }                                                                 // 0.0
/*1006 */             }                                                                     // 0.0
/*1008 */             break;                                                                // 0.0
/*1010 */         case 0x44:                                                                // 0.0
/*1012 */             /* CMOVLT */                                                          // 0.0
/*1014 */             gen_cmov(TCG_COND_LT, ra, rb, rc, islit, lit, 0);                     // 0.0
/*1016 */             break;                                                                // 0.0
/*1018 */         case 0x46:                                                                // 0.0
/*1020 */             /* CMOVGE */                                                          // 0.0
/*1022 */             gen_cmov(TCG_COND_GE, ra, rb, rc, islit, lit, 0);                     // 0.0
/*1024 */             break;                                                                // 0.0
/*1026 */         case 0x48:                                                                // 0.0
/*1028 */             /* EQV */                                                             // 0.0
/*1030 */             if (likely(rc != 31)) {                                               // 0.0
/*1032 */                 if (ra != 31) {                                                   // 0.0
/*1034 */                     if (islit) {                                                  // 0.0
/*1036 */                         tcg_gen_xori_i64(cpu_ir[rc], cpu_ir[ra], ~lit);           // 0.0
/*1038 */                     } else {                                                      // 0.0
/*1040 */                         tcg_gen_eqv_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);      // 0.0
/*1042 */                     }                                                             // 0.0
/*1044 */                 } else {                                                          // 0.0
/*1046 */                     if (islit) {                                                  // 0.0
/*1048 */                         tcg_gen_movi_i64(cpu_ir[rc], ~lit);                       // 0.0
/*1050 */                     } else {                                                      // 0.0
/*1052 */                         tcg_gen_not_i64(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*1054 */                     }                                                             // 0.0
/*1056 */                 }                                                                 // 0.0
/*1058 */             }                                                                     // 0.0
/*1060 */             break;                                                                // 0.0
/*1062 */         case 0x61:                                                                // 0.0
/*1064 */             /* AMASK */                                                           // 0.0
/*1066 */             if (likely(rc != 31)) {                                               // 0.0
/*1068 */                 uint64_t amask = ctx->tb->flags >> TB_FLAGS_AMASK_SHIFT;          // 0.0
/*1072 */                 if (islit) {                                                      // 0.0
/*1074 */                     tcg_gen_movi_i64(cpu_ir[rc], lit & ~amask);                   // 0.0
/*1076 */                 } else {                                                          // 0.0
/*1078 */                     tcg_gen_andi_i64(cpu_ir[rc], cpu_ir[rb], ~amask);             // 0.0
/*1080 */                 }                                                                 // 0.0
/*1082 */             }                                                                     // 0.0
/*1084 */             break;                                                                // 0.0
/*1086 */         case 0x64:                                                                // 0.0
/*1088 */             /* CMOVLE */                                                          // 0.0
/*1090 */             gen_cmov(TCG_COND_LE, ra, rb, rc, islit, lit, 0);                     // 0.0
/*1092 */             break;                                                                // 0.0
/*1094 */         case 0x66:                                                                // 0.0
/*1096 */             /* CMOVGT */                                                          // 0.0
/*1098 */             gen_cmov(TCG_COND_GT, ra, rb, rc, islit, lit, 0);                     // 0.0
/*1100 */             break;                                                                // 0.0
/*1102 */         case 0x6C:                                                                // 0.0
/*1104 */             /* IMPLVER */                                                         // 0.0
/*1106 */             if (rc != 31) {                                                       // 0.0
/*1108 */                 tcg_gen_movi_i64(cpu_ir[rc], ctx->implver);                       // 0.0
/*1110 */             }                                                                     // 0.0
/*1112 */             break;                                                                // 0.0
/*1114 */         default:                                                                  // 0.0
/*1116 */             goto invalid_opc;                                                     // 0.0
/*1118 */         }                                                                         // 0.0
/*1120 */         break;                                                                    // 0.0
/*1122 */     case 0x12:                                                                    // 0.0
/*1124 */         switch (fn7) {                                                            // 0.0
/*1126 */         case 0x02:                                                                // 0.0
/*1128 */             /* MSKBL */                                                           // 0.0
/*1130 */             gen_msk_l(ra, rb, rc, islit, lit, 0x01);                              // 0.0
/*1132 */             break;                                                                // 0.0
/*1134 */         case 0x06:                                                                // 0.0
/*1136 */             /* EXTBL */                                                           // 0.0
/*1138 */             gen_ext_l(ra, rb, rc, islit, lit, 0x01);                              // 0.0
/*1140 */             break;                                                                // 0.0
/*1142 */         case 0x0B:                                                                // 0.0
/*1144 */             /* INSBL */                                                           // 0.0
/*1146 */             gen_ins_l(ra, rb, rc, islit, lit, 0x01);                              // 0.0
/*1148 */             break;                                                                // 0.0
/*1150 */         case 0x12:                                                                // 0.0
/*1152 */             /* MSKWL */                                                           // 0.0
/*1154 */             gen_msk_l(ra, rb, rc, islit, lit, 0x03);                              // 0.0
/*1156 */             break;                                                                // 0.0
/*1158 */         case 0x16:                                                                // 0.0
/*1160 */             /* EXTWL */                                                           // 0.0
/*1162 */             gen_ext_l(ra, rb, rc, islit, lit, 0x03);                              // 0.0
/*1164 */             break;                                                                // 0.0
/*1166 */         case 0x1B:                                                                // 0.0
/*1168 */             /* INSWL */                                                           // 0.0
/*1170 */             gen_ins_l(ra, rb, rc, islit, lit, 0x03);                              // 0.0
/*1172 */             break;                                                                // 0.0
/*1174 */         case 0x22:                                                                // 0.0
/*1176 */             /* MSKLL */                                                           // 0.0
/*1178 */             gen_msk_l(ra, rb, rc, islit, lit, 0x0f);                              // 0.0
/*1180 */             break;                                                                // 0.0
/*1182 */         case 0x26:                                                                // 0.0
/*1184 */             /* EXTLL */                                                           // 0.0
/*1186 */             gen_ext_l(ra, rb, rc, islit, lit, 0x0f);                              // 0.0
/*1188 */             break;                                                                // 0.0
/*1190 */         case 0x2B:                                                                // 0.0
/*1192 */             /* INSLL */                                                           // 0.0
/*1194 */             gen_ins_l(ra, rb, rc, islit, lit, 0x0f);                              // 0.0
/*1196 */             break;                                                                // 0.0
/*1198 */         case 0x30:                                                                // 0.0
/*1200 */             /* ZAP */                                                             // 0.0
/*1202 */             gen_zap(ra, rb, rc, islit, lit);                                      // 0.0
/*1204 */             break;                                                                // 0.0
/*1206 */         case 0x31:                                                                // 0.0
/*1208 */             /* ZAPNOT */                                                          // 0.0
/*1210 */             gen_zapnot(ra, rb, rc, islit, lit);                                   // 0.0
/*1212 */             break;                                                                // 0.0
/*1214 */         case 0x32:                                                                // 0.0
/*1216 */             /* MSKQL */                                                           // 0.0
/*1218 */             gen_msk_l(ra, rb, rc, islit, lit, 0xff);                              // 0.0
/*1220 */             break;                                                                // 0.0
/*1222 */         case 0x34:                                                                // 0.0
/*1224 */             /* SRL */                                                             // 0.0
/*1226 */             if (likely(rc != 31)) {                                               // 0.0
/*1228 */                 if (ra != 31) {                                                   // 0.0
/*1230 */                     if (islit) {                                                  // 0.0
/*1232 */                         tcg_gen_shri_i64(cpu_ir[rc], cpu_ir[ra], lit & 0x3f);     // 0.0
/*1234 */                     } else {                                                      // 0.0
/*1236 */                         TCGv shift = tcg_temp_new();                              // 0.0
/*1238 */                         tcg_gen_andi_i64(shift, cpu_ir[rb], 0x3f);                // 0.0
/*1240 */                         tcg_gen_shr_i64(cpu_ir[rc], cpu_ir[ra], shift);           // 0.0
/*1242 */                         tcg_temp_free(shift);                                     // 0.0
/*1244 */                     }                                                             // 0.0
/*1246 */                 } else                                                            // 0.0
/*1248 */                     tcg_gen_movi_i64(cpu_ir[rc], 0);                              // 0.0
/*1250 */             }                                                                     // 0.0
/*1252 */             break;                                                                // 0.0
/*1254 */         case 0x36:                                                                // 0.0
/*1256 */             /* EXTQL */                                                           // 0.0
/*1258 */             gen_ext_l(ra, rb, rc, islit, lit, 0xff);                              // 0.0
/*1260 */             break;                                                                // 0.0
/*1262 */         case 0x39:                                                                // 0.0
/*1264 */             /* SLL */                                                             // 0.0
/*1266 */             if (likely(rc != 31)) {                                               // 0.0
/*1268 */                 if (ra != 31) {                                                   // 0.0
/*1270 */                     if (islit) {                                                  // 0.0
/*1272 */                         tcg_gen_shli_i64(cpu_ir[rc], cpu_ir[ra], lit & 0x3f);     // 0.0
/*1274 */                     } else {                                                      // 0.0
/*1276 */                         TCGv shift = tcg_temp_new();                              // 0.0
/*1278 */                         tcg_gen_andi_i64(shift, cpu_ir[rb], 0x3f);                // 0.0
/*1280 */                         tcg_gen_shl_i64(cpu_ir[rc], cpu_ir[ra], shift);           // 0.0
/*1282 */                         tcg_temp_free(shift);                                     // 0.0
/*1284 */                     }                                                             // 0.0
/*1286 */                 } else                                                            // 0.0
/*1288 */                     tcg_gen_movi_i64(cpu_ir[rc], 0);                              // 0.0
/*1290 */             }                                                                     // 0.0
/*1292 */             break;                                                                // 0.0
/*1294 */         case 0x3B:                                                                // 0.0
/*1296 */             /* INSQL */                                                           // 0.0
/*1298 */             gen_ins_l(ra, rb, rc, islit, lit, 0xff);                              // 0.0
/*1300 */             break;                                                                // 0.0
/*1302 */         case 0x3C:                                                                // 0.0
/*1304 */             /* SRA */                                                             // 0.0
/*1306 */             if (likely(rc != 31)) {                                               // 0.0
/*1308 */                 if (ra != 31) {                                                   // 0.0
/*1310 */                     if (islit) {                                                  // 0.0
/*1312 */                         tcg_gen_sari_i64(cpu_ir[rc], cpu_ir[ra], lit & 0x3f);     // 0.0
/*1314 */                     } else {                                                      // 0.0
/*1316 */                         TCGv shift = tcg_temp_new();                              // 0.0
/*1318 */                         tcg_gen_andi_i64(shift, cpu_ir[rb], 0x3f);                // 0.0
/*1320 */                         tcg_gen_sar_i64(cpu_ir[rc], cpu_ir[ra], shift);           // 0.0
/*1322 */                         tcg_temp_free(shift);                                     // 0.0
/*1324 */                     }                                                             // 0.0
/*1326 */                 } else                                                            // 0.0
/*1328 */                     tcg_gen_movi_i64(cpu_ir[rc], 0);                              // 0.0
/*1330 */             }                                                                     // 0.0
/*1332 */             break;                                                                // 0.0
/*1334 */         case 0x52:                                                                // 0.0
/*1336 */             /* MSKWH */                                                           // 0.0
/*1338 */             gen_msk_h(ra, rb, rc, islit, lit, 0x03);                              // 0.0
/*1340 */             break;                                                                // 0.0
/*1342 */         case 0x57:                                                                // 0.0
/*1344 */             /* INSWH */                                                           // 0.0
/*1346 */             gen_ins_h(ra, rb, rc, islit, lit, 0x03);                              // 0.0
/*1348 */             break;                                                                // 0.0
/*1350 */         case 0x5A:                                                                // 0.0
/*1352 */             /* EXTWH */                                                           // 0.0
/*1354 */             gen_ext_h(ra, rb, rc, islit, lit, 0x03);                              // 0.0
/*1356 */             break;                                                                // 0.0
/*1358 */         case 0x62:                                                                // 0.0
/*1360 */             /* MSKLH */                                                           // 0.0
/*1362 */             gen_msk_h(ra, rb, rc, islit, lit, 0x0f);                              // 0.0
/*1364 */             break;                                                                // 0.0
/*1366 */         case 0x67:                                                                // 0.0
/*1368 */             /* INSLH */                                                           // 0.0
/*1370 */             gen_ins_h(ra, rb, rc, islit, lit, 0x0f);                              // 0.0
/*1372 */             break;                                                                // 0.0
/*1374 */         case 0x6A:                                                                // 0.0
/*1376 */             /* EXTLH */                                                           // 0.0
/*1378 */             gen_ext_h(ra, rb, rc, islit, lit, 0x0f);                              // 0.0
/*1380 */             break;                                                                // 0.0
/*1382 */         case 0x72:                                                                // 0.0
/*1384 */             /* MSKQH */                                                           // 0.0
/*1386 */             gen_msk_h(ra, rb, rc, islit, lit, 0xff);                              // 0.0
/*1388 */             break;                                                                // 0.0
/*1390 */         case 0x77:                                                                // 0.0
/*1392 */             /* INSQH */                                                           // 0.0
/*1394 */             gen_ins_h(ra, rb, rc, islit, lit, 0xff);                              // 0.0
/*1396 */             break;                                                                // 0.0
/*1398 */         case 0x7A:                                                                // 0.0
/*1400 */             /* EXTQH */                                                           // 0.0
/*1402 */             gen_ext_h(ra, rb, rc, islit, lit, 0xff);                              // 0.0
/*1404 */             break;                                                                // 0.0
/*1406 */         default:                                                                  // 0.0
/*1408 */             goto invalid_opc;                                                     // 0.0
/*1410 */         }                                                                         // 0.0
/*1412 */         break;                                                                    // 0.0
/*1414 */     case 0x13:                                                                    // 0.0
/*1416 */         switch (fn7) {                                                            // 0.0
/*1418 */         case 0x00:                                                                // 0.0
/*1420 */             /* MULL */                                                            // 0.0
/*1422 */             if (likely(rc != 31)) {                                               // 0.0
/*1424 */                 if (ra == 31) {                                                   // 0.0
/*1426 */                     tcg_gen_movi_i64(cpu_ir[rc], 0);                              // 0.0
/*1428 */                 } else {                                                          // 0.0
/*1430 */                     if (islit) {                                                  // 0.0
/*1432 */                         tcg_gen_muli_i64(cpu_ir[rc], cpu_ir[ra], lit);            // 0.0
/*1434 */                     } else {                                                      // 0.0
/*1436 */                         tcg_gen_mul_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);      // 0.0
/*1438 */                     }                                                             // 0.0
/*1440 */                     tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);                   // 0.0
/*1442 */                 }                                                                 // 0.0
/*1444 */             }                                                                     // 0.0
/*1446 */             break;                                                                // 0.0
/*1448 */         case 0x20:                                                                // 0.0
/*1450 */             /* MULQ */                                                            // 0.0
/*1452 */             if (likely(rc != 31)) {                                               // 0.0
/*1454 */                 if (ra == 31) {                                                   // 0.0
/*1456 */                     tcg_gen_movi_i64(cpu_ir[rc], 0);                              // 0.0
/*1458 */                 } else if (islit) {                                               // 0.0
/*1460 */                     tcg_gen_muli_i64(cpu_ir[rc], cpu_ir[ra], lit);                // 0.0
/*1462 */                 } else {                                                          // 0.0
/*1464 */                     tcg_gen_mul_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);          // 0.0
/*1466 */                 }                                                                 // 0.0
/*1468 */             }                                                                     // 0.0
/*1470 */             break;                                                                // 0.0
/*1472 */         case 0x30:                                                                // 0.0
/*1474 */             /* UMULH */                                                           // 0.0
/*1476 */             {                                                                     // 0.0
/*1478 */                 TCGv low;                                                         // 0.0
/*1480 */                 if (unlikely(rc == 31)){                                          // 0.0
/*1482 */                     break;                                                        // 0.0
/*1484 */                 }                                                                 // 0.0
/*1486 */                 if (ra == 31) {                                                   // 0.0
/*1488 */                     tcg_gen_movi_i64(cpu_ir[rc], 0);                              // 0.0
/*1490 */                     break;                                                        // 0.0
/*1492 */                 }                                                                 // 0.0
/*1494 */                 low = tcg_temp_new();                                             // 0.0
/*1496 */                 if (islit) {                                                      // 0.0
/*1498 */                     tcg_gen_movi_tl(low, lit);                                    // 0.0
/*1500 */                     tcg_gen_mulu2_i64(low, cpu_ir[rc], cpu_ir[ra], low);          // 0.0
/*1502 */                 } else {                                                          // 0.0
/*1504 */                     tcg_gen_mulu2_i64(low, cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);   // 0.0
/*1506 */                 }                                                                 // 0.0
/*1508 */                 tcg_temp_free(low);                                               // 0.0
/*1510 */             }                                                                     // 0.0
/*1512 */             break;                                                                // 0.0
/*1514 */         case 0x40:                                                                // 0.0
/*1516 */             /* MULL/V */                                                          // 0.0
/*1518 */             gen_mullv(ra, rb, rc, islit, lit);                                    // 0.0
/*1520 */             break;                                                                // 0.0
/*1522 */         case 0x60:                                                                // 0.0
/*1524 */             /* MULQ/V */                                                          // 0.0
/*1526 */             gen_mulqv(ra, rb, rc, islit, lit);                                    // 0.0
/*1528 */             break;                                                                // 0.0
/*1530 */         default:                                                                  // 0.0
/*1532 */             goto invalid_opc;                                                     // 0.0
/*1534 */         }                                                                         // 0.0
/*1536 */         break;                                                                    // 0.0
/*1538 */     case 0x14:                                                                    // 0.0
/*1540 */         switch (fpfn) { /* fn11 & 0x3F */                                         // 0.0
/*1542 */         case 0x04:                                                                // 0.0
/*1544 */             /* ITOFS */                                                           // 0.0
/*1546 */             if ((ctx->tb->flags & TB_FLAGS_AMASK_FIX) == 0) {                     // 0.0
/*1548 */                 goto invalid_opc;                                                 // 0.0
/*1550 */             }                                                                     // 0.0
/*1552 */             if (likely(rc != 31)) {                                               // 0.0
/*1554 */                 if (ra != 31) {                                                   // 0.0
/*1556 */                     TCGv_i32 tmp = tcg_temp_new_i32();                            // 0.0
/*1558 */                     tcg_gen_trunc_i64_i32(tmp, cpu_ir[ra]);                       // 0.0
/*1560 */                     gen_helper_memory_to_s(cpu_fir[rc], tmp);                     // 0.0
/*1562 */                     tcg_temp_free_i32(tmp);                                       // 0.0
/*1564 */                 } else                                                            // 0.0
/*1566 */                     tcg_gen_movi_i64(cpu_fir[rc], 0);                             // 0.0
/*1568 */             }                                                                     // 0.0
/*1570 */             break;                                                                // 0.0
/*1572 */         case 0x0A:                                                                // 0.0
/*1574 */             /* SQRTF */                                                           // 0.0
/*1576 */             if (ctx->tb->flags & TB_FLAGS_AMASK_FIX) {                            // 0.0
/*1578 */                 gen_fsqrtf(rb, rc);                                               // 0.0
/*1580 */                 break;                                                            // 0.0
/*1582 */             }                                                                     // 0.0
/*1584 */             goto invalid_opc;                                                     // 0.0
/*1586 */         case 0x0B:                                                                // 0.0
/*1588 */             /* SQRTS */                                                           // 0.0
/*1590 */             if (ctx->tb->flags & TB_FLAGS_AMASK_FIX) {                            // 0.0
/*1592 */                 gen_fsqrts(ctx, rb, rc, fn11);                                    // 0.0
/*1594 */                 break;                                                            // 0.0
/*1596 */             }                                                                     // 0.0
/*1598 */             goto invalid_opc;                                                     // 0.0
/*1600 */         case 0x14:                                                                // 0.0
/*1602 */             /* ITOFF */                                                           // 0.0
/*1604 */             if ((ctx->tb->flags & TB_FLAGS_AMASK_FIX) == 0) {                     // 0.0
/*1606 */                 goto invalid_opc;                                                 // 0.0
/*1608 */             }                                                                     // 0.0
/*1610 */             if (likely(rc != 31)) {                                               // 0.0
/*1612 */                 if (ra != 31) {                                                   // 0.0
/*1614 */                     TCGv_i32 tmp = tcg_temp_new_i32();                            // 0.0
/*1616 */                     tcg_gen_trunc_i64_i32(tmp, cpu_ir[ra]);                       // 0.0
/*1618 */                     gen_helper_memory_to_f(cpu_fir[rc], tmp);                     // 0.0
/*1620 */                     tcg_temp_free_i32(tmp);                                       // 0.0
/*1622 */                 } else                                                            // 0.0
/*1624 */                     tcg_gen_movi_i64(cpu_fir[rc], 0);                             // 0.0
/*1626 */             }                                                                     // 0.0
/*1628 */             break;                                                                // 0.0
/*1630 */         case 0x24:                                                                // 0.0
/*1632 */             /* ITOFT */                                                           // 0.0
/*1634 */             if ((ctx->tb->flags & TB_FLAGS_AMASK_FIX) == 0) {                     // 0.0
/*1636 */                 goto invalid_opc;                                                 // 0.0
/*1638 */             }                                                                     // 0.0
/*1640 */             if (likely(rc != 31)) {                                               // 0.0
/*1642 */                 if (ra != 31) {                                                   // 0.0
/*1644 */                     tcg_gen_mov_i64(cpu_fir[rc], cpu_ir[ra]);                     // 0.0
/*1646 */                 } else {                                                          // 0.0
/*1648 */                     tcg_gen_movi_i64(cpu_fir[rc], 0);                             // 0.0
/*1650 */                 }                                                                 // 0.0
/*1652 */             }                                                                     // 0.0
/*1654 */             break;                                                                // 0.0
/*1656 */         case 0x2A:                                                                // 0.0
/*1658 */             /* SQRTG */                                                           // 0.0
/*1660 */             if (ctx->tb->flags & TB_FLAGS_AMASK_FIX) {                            // 0.0
/*1662 */                 gen_fsqrtg(rb, rc);                                               // 0.0
/*1664 */                 break;                                                            // 0.0
/*1666 */             }                                                                     // 0.0
/*1668 */             goto invalid_opc;                                                     // 0.0
/*1670 */         case 0x02B:                                                               // 0.0
/*1672 */             /* SQRTT */                                                           // 0.0
/*1674 */             if (ctx->tb->flags & TB_FLAGS_AMASK_FIX) {                            // 0.0
/*1676 */                 gen_fsqrtt(ctx, rb, rc, fn11);                                    // 0.0
/*1678 */                 break;                                                            // 0.0
/*1680 */             }                                                                     // 0.0
/*1682 */             goto invalid_opc;                                                     // 0.0
/*1684 */         default:                                                                  // 0.0
/*1686 */             goto invalid_opc;                                                     // 0.0
/*1688 */         }                                                                         // 0.0
/*1690 */         break;                                                                    // 0.0
/*1692 */     case 0x15:                                                                    // 0.0
/*1694 */         /* VAX floating point */                                                  // 0.0
/*1696 */         /* XXX: rounding mode and trap are ignored (!) */                         // 0.0
/*1698 */         switch (fpfn) { /* fn11 & 0x3F */                                         // 0.0
/*1700 */         case 0x00:                                                                // 0.0
/*1702 */             /* ADDF */                                                            // 0.0
/*1704 */             gen_faddf(ra, rb, rc);                                                // 0.0
/*1706 */             break;                                                                // 0.0
/*1708 */         case 0x01:                                                                // 0.0
/*1710 */             /* SUBF */                                                            // 0.0
/*1712 */             gen_fsubf(ra, rb, rc);                                                // 0.0
/*1714 */             break;                                                                // 0.0
/*1716 */         case 0x02:                                                                // 0.0
/*1718 */             /* MULF */                                                            // 0.0
/*1720 */             gen_fmulf(ra, rb, rc);                                                // 0.0
/*1722 */             break;                                                                // 0.0
/*1724 */         case 0x03:                                                                // 0.0
/*1726 */             /* DIVF */                                                            // 0.0
/*1728 */             gen_fdivf(ra, rb, rc);                                                // 0.0
/*1730 */             break;                                                                // 0.0
/*1732 */         case 0x1E:                                                                // 0.0
/*1734 */             /* CVTDG */                                                           // 0.0
/*1736 */ #if 0 // TODO                                                                     // 0.0
/*1738 */             gen_fcvtdg(rb, rc);                                                   // 0.0
/*1740 */ #else                                                                             // 0.0
/*1742 */             goto invalid_opc;                                                     // 0.0
/*1744 */ #endif                                                                            // 0.0
/*1746 */             break;                                                                // 0.0
/*1748 */         case 0x20:                                                                // 0.0
/*1750 */             /* ADDG */                                                            // 0.0
/*1752 */             gen_faddg(ra, rb, rc);                                                // 0.0
/*1754 */             break;                                                                // 0.0
/*1756 */         case 0x21:                                                                // 0.0
/*1758 */             /* SUBG */                                                            // 0.0
/*1760 */             gen_fsubg(ra, rb, rc);                                                // 0.0
/*1762 */             break;                                                                // 0.0
/*1764 */         case 0x22:                                                                // 0.0
/*1766 */             /* MULG */                                                            // 0.0
/*1768 */             gen_fmulg(ra, rb, rc);                                                // 0.0
/*1770 */             break;                                                                // 0.0
/*1772 */         case 0x23:                                                                // 0.0
/*1774 */             /* DIVG */                                                            // 0.0
/*1776 */             gen_fdivg(ra, rb, rc);                                                // 0.0
/*1778 */             break;                                                                // 0.0
/*1780 */         case 0x25:                                                                // 0.0
/*1782 */             /* CMPGEQ */                                                          // 0.0
/*1784 */             gen_fcmpgeq(ra, rb, rc);                                              // 0.0
/*1786 */             break;                                                                // 0.0
/*1788 */         case 0x26:                                                                // 0.0
/*1790 */             /* CMPGLT */                                                          // 0.0
/*1792 */             gen_fcmpglt(ra, rb, rc);                                              // 0.0
/*1794 */             break;                                                                // 0.0
/*1796 */         case 0x27:                                                                // 0.0
/*1798 */             /* CMPGLE */                                                          // 0.0
/*1800 */             gen_fcmpgle(ra, rb, rc);                                              // 0.0
/*1802 */             break;                                                                // 0.0
/*1804 */         case 0x2C:                                                                // 0.0
/*1806 */             /* CVTGF */                                                           // 0.0
/*1808 */             gen_fcvtgf(rb, rc);                                                   // 0.0
/*1810 */             break;                                                                // 0.0
/*1812 */         case 0x2D:                                                                // 0.0
/*1814 */             /* CVTGD */                                                           // 0.0
/*1816 */ #if 0 // TODO                                                                     // 0.0
/*1818 */             gen_fcvtgd(rb, rc);                                                   // 0.0
/*1820 */ #else                                                                             // 0.0
/*1822 */             goto invalid_opc;                                                     // 0.0
/*1824 */ #endif                                                                            // 0.0
/*1826 */             break;                                                                // 0.0
/*1828 */         case 0x2F:                                                                // 0.0
/*1830 */             /* CVTGQ */                                                           // 0.0
/*1832 */             gen_fcvtgq(rb, rc);                                                   // 0.0
/*1834 */             break;                                                                // 0.0
/*1836 */         case 0x3C:                                                                // 0.0
/*1838 */             /* CVTQF */                                                           // 0.0
/*1840 */             gen_fcvtqf(rb, rc);                                                   // 0.0
/*1842 */             break;                                                                // 0.0
/*1844 */         case 0x3E:                                                                // 0.0
/*1846 */             /* CVTQG */                                                           // 0.0
/*1848 */             gen_fcvtqg(rb, rc);                                                   // 0.0
/*1850 */             break;                                                                // 0.0
/*1852 */         default:                                                                  // 0.0
/*1854 */             goto invalid_opc;                                                     // 0.0
/*1856 */         }                                                                         // 0.0
/*1858 */         break;                                                                    // 0.0
/*1860 */     case 0x16:                                                                    // 0.0
/*1862 */         /* IEEE floating-point */                                                 // 0.0
/*1864 */         switch (fpfn) { /* fn11 & 0x3F */                                         // 0.0
/*1866 */         case 0x00:                                                                // 0.0
/*1868 */             /* ADDS */                                                            // 0.0
/*1870 */             gen_fadds(ctx, ra, rb, rc, fn11);                                     // 0.0
/*1872 */             break;                                                                // 0.0
/*1874 */         case 0x01:                                                                // 0.0
/*1876 */             /* SUBS */                                                            // 0.0
/*1878 */             gen_fsubs(ctx, ra, rb, rc, fn11);                                     // 0.0
/*1880 */             break;                                                                // 0.0
/*1882 */         case 0x02:                                                                // 0.0
/*1884 */             /* MULS */                                                            // 0.0
/*1886 */             gen_fmuls(ctx, ra, rb, rc, fn11);                                     // 0.0
/*1888 */             break;                                                                // 0.0
/*1890 */         case 0x03:                                                                // 0.0
/*1892 */             /* DIVS */                                                            // 0.0
/*1894 */             gen_fdivs(ctx, ra, rb, rc, fn11);                                     // 0.0
/*1896 */             break;                                                                // 0.0
/*1898 */         case 0x20:                                                                // 0.0
/*1900 */             /* ADDT */                                                            // 0.0
/*1902 */             gen_faddt(ctx, ra, rb, rc, fn11);                                     // 0.0
/*1904 */             break;                                                                // 0.0
/*1906 */         case 0x21:                                                                // 0.0
/*1908 */             /* SUBT */                                                            // 0.0
/*1910 */             gen_fsubt(ctx, ra, rb, rc, fn11);                                     // 0.0
/*1912 */             break;                                                                // 0.0
/*1914 */         case 0x22:                                                                // 0.0
/*1916 */             /* MULT */                                                            // 0.0
/*1918 */             gen_fmult(ctx, ra, rb, rc, fn11);                                     // 0.0
/*1920 */             break;                                                                // 0.0
/*1922 */         case 0x23:                                                                // 0.0
/*1924 */             /* DIVT */                                                            // 0.0
/*1926 */             gen_fdivt(ctx, ra, rb, rc, fn11);                                     // 0.0
/*1928 */             break;                                                                // 0.0
/*1930 */         case 0x24:                                                                // 0.0
/*1932 */             /* CMPTUN */                                                          // 0.0
/*1934 */             gen_fcmptun(ctx, ra, rb, rc, fn11);                                   // 0.0
/*1936 */             break;                                                                // 0.0
/*1938 */         case 0x25:                                                                // 0.0
/*1940 */             /* CMPTEQ */                                                          // 0.0
/*1942 */             gen_fcmpteq(ctx, ra, rb, rc, fn11);                                   // 0.0
/*1944 */             break;                                                                // 0.0
/*1946 */         case 0x26:                                                                // 0.0
/*1948 */             /* CMPTLT */                                                          // 0.0
/*1950 */             gen_fcmptlt(ctx, ra, rb, rc, fn11);                                   // 0.0
/*1952 */             break;                                                                // 0.0
/*1954 */         case 0x27:                                                                // 0.0
/*1956 */             /* CMPTLE */                                                          // 0.0
/*1958 */             gen_fcmptle(ctx, ra, rb, rc, fn11);                                   // 0.0
/*1960 */             break;                                                                // 0.0
/*1962 */         case 0x2C:                                                                // 0.0
/*1964 */             if (fn11 == 0x2AC || fn11 == 0x6AC) {                                 // 0.0
/*1966 */                 /* CVTST */                                                       // 0.0
/*1968 */                 gen_fcvtst(ctx, rb, rc, fn11);                                    // 0.0
/*1970 */             } else {                                                              // 0.0
/*1972 */                 /* CVTTS */                                                       // 0.0
/*1974 */                 gen_fcvtts(ctx, rb, rc, fn11);                                    // 0.0
/*1976 */             }                                                                     // 0.0
/*1978 */             break;                                                                // 0.0
/*1980 */         case 0x2F:                                                                // 0.0
/*1982 */             /* CVTTQ */                                                           // 0.0
/*1984 */             gen_fcvttq(ctx, rb, rc, fn11);                                        // 0.0
/*1986 */             break;                                                                // 0.0
/*1988 */         case 0x3C:                                                                // 0.0
/*1990 */             /* CVTQS */                                                           // 0.0
/*1992 */             gen_fcvtqs(ctx, rb, rc, fn11);                                        // 0.0
/*1994 */             break;                                                                // 0.0
/*1996 */         case 0x3E:                                                                // 0.0
/*1998 */             /* CVTQT */                                                           // 0.0
/*2000 */             gen_fcvtqt(ctx, rb, rc, fn11);                                        // 0.0
/*2002 */             break;                                                                // 0.0
/*2004 */         default:                                                                  // 0.0
/*2006 */             goto invalid_opc;                                                     // 0.0
/*2008 */         }                                                                         // 0.0
/*2010 */         break;                                                                    // 0.0
/*2012 */     case 0x17:                                                                    // 0.0
/*2014 */         switch (fn11) {                                                           // 0.0
/*2016 */         case 0x010:                                                               // 0.0
/*2018 */             /* CVTLQ */                                                           // 0.0
/*2020 */             gen_fcvtlq(rb, rc);                                                   // 0.0
/*2022 */             break;                                                                // 0.0
/*2024 */         case 0x020:                                                               // 0.0
/*2026 */             if (likely(rc != 31)) {                                               // 0.0
/*2028 */                 if (ra == rb) {                                                   // 0.0
/*2030 */                     /* FMOV */                                                    // 0.0
/*2032 */                     if (ra == 31) {                                               // 0.0
/*2034 */                         tcg_gen_movi_i64(cpu_fir[rc], 0);                         // 0.0
/*2036 */                     } else {                                                      // 0.0
/*2038 */                         tcg_gen_mov_i64(cpu_fir[rc], cpu_fir[ra]);                // 0.0
/*2040 */                     }                                                             // 0.0
/*2042 */                 } else {                                                          // 0.0
/*2044 */                     /* CPYS */                                                    // 0.0
/*2046 */                     gen_fcpys(ra, rb, rc);                                        // 0.0
/*2048 */                 }                                                                 // 0.0
/*2050 */             }                                                                     // 0.0
/*2052 */             break;                                                                // 0.0
/*2054 */         case 0x021:                                                               // 0.0
/*2056 */             /* CPYSN */                                                           // 0.0
/*2058 */             gen_fcpysn(ra, rb, rc);                                               // 0.0
/*2060 */             break;                                                                // 0.0
/*2062 */         case 0x022:                                                               // 0.0
/*2064 */             /* CPYSE */                                                           // 0.0
/*2066 */             gen_fcpyse(ra, rb, rc);                                               // 0.0
/*2068 */             break;                                                                // 0.0
/*2070 */         case 0x024:                                                               // 0.0
/*2072 */             /* MT_FPCR */                                                         // 0.0
/*2074 */             if (likely(ra != 31)) {                                               // 0.0
/*2076 */                 gen_helper_store_fpcr(cpu_env, cpu_fir[ra]);                      // 0.0
/*2078 */             } else {                                                              // 0.0
/*2080 */                 TCGv tmp = tcg_const_i64(0);                                      // 0.0
/*2082 */                 gen_helper_store_fpcr(cpu_env, tmp);                              // 0.0
/*2084 */                 tcg_temp_free(tmp);                                               // 0.0
/*2086 */             }                                                                     // 0.0
/*2088 */             break;                                                                // 0.0
/*2090 */         case 0x025:                                                               // 0.0
/*2092 */             /* MF_FPCR */                                                         // 0.0
/*2094 */             if (likely(ra != 31)) {                                               // 0.0
/*2096 */                 gen_helper_load_fpcr(cpu_fir[ra], cpu_env);                       // 0.0
/*2098 */             }                                                                     // 0.0
/*2100 */             break;                                                                // 0.0
/*2102 */         case 0x02A:                                                               // 0.0
/*2104 */             /* FCMOVEQ */                                                         // 0.0
/*2106 */             gen_fcmov(TCG_COND_EQ, ra, rb, rc);                                   // 0.0
/*2108 */             break;                                                                // 0.0
/*2110 */         case 0x02B:                                                               // 0.0
/*2112 */             /* FCMOVNE */                                                         // 0.0
/*2114 */             gen_fcmov(TCG_COND_NE, ra, rb, rc);                                   // 0.0
/*2116 */             break;                                                                // 0.0
/*2118 */         case 0x02C:                                                               // 0.0
/*2120 */             /* FCMOVLT */                                                         // 0.0
/*2122 */             gen_fcmov(TCG_COND_LT, ra, rb, rc);                                   // 0.0
/*2124 */             break;                                                                // 0.0
/*2126 */         case 0x02D:                                                               // 0.0
/*2128 */             /* FCMOVGE */                                                         // 0.0
/*2130 */             gen_fcmov(TCG_COND_GE, ra, rb, rc);                                   // 0.0
/*2132 */             break;                                                                // 0.0
/*2134 */         case 0x02E:                                                               // 0.0
/*2136 */             /* FCMOVLE */                                                         // 0.0
/*2138 */             gen_fcmov(TCG_COND_LE, ra, rb, rc);                                   // 0.0
/*2140 */             break;                                                                // 0.0
/*2142 */         case 0x02F:                                                               // 0.0
/*2144 */             /* FCMOVGT */                                                         // 0.0
/*2146 */             gen_fcmov(TCG_COND_GT, ra, rb, rc);                                   // 0.0
/*2148 */             break;                                                                // 0.0
/*2150 */         case 0x030:                                                               // 0.0
/*2152 */             /* CVTQL */                                                           // 0.0
/*2154 */             gen_fcvtql(rb, rc);                                                   // 0.0
/*2156 */             break;                                                                // 0.0
/*2158 */         case 0x130:                                                               // 0.0
/*2160 */             /* CVTQL/V */                                                         // 0.0
/*2162 */         case 0x530:                                                               // 0.0
/*2164 */             /* CVTQL/SV */                                                        // 0.0
/*2166 */             /* ??? I'm pretty sure there's nothing that /sv needs to do that      // 0.0
/*2168 */                /v doesn't do.  The only thing I can think is that /sv is a        // 0.0
/*2170 */                valid instruction merely for completeness in the ISA.  */          // 0.0
/*2172 */             gen_fcvtql_v(ctx, rb, rc);                                            // 0.0
/*2174 */             break;                                                                // 0.0
/*2176 */         default:                                                                  // 0.0
/*2178 */             goto invalid_opc;                                                     // 0.0
/*2180 */         }                                                                         // 0.0
/*2182 */         break;                                                                    // 0.0
/*2184 */     case 0x18:                                                                    // 0.0
/*2186 */         switch ((uint16_t)disp16) {                                               // 0.0
/*2188 */         case 0x0000:                                                              // 0.0
/*2190 */             /* TRAPB */                                                           // 0.0
/*2192 */             /* No-op.  */                                                         // 0.0
/*2194 */             break;                                                                // 0.0
/*2196 */         case 0x0400:                                                              // 0.0
/*2198 */             /* EXCB */                                                            // 0.0
/*2200 */             /* No-op.  */                                                         // 0.0
/*2202 */             break;                                                                // 0.0
/*2204 */         case 0x4000:                                                              // 0.0
/*2206 */             /* MB */                                                              // 0.0
/*2208 */             /* No-op */                                                           // 0.0
/*2210 */             break;                                                                // 0.0
/*2212 */         case 0x4400:                                                              // 0.0
/*2214 */             /* WMB */                                                             // 0.0
/*2216 */             /* No-op */                                                           // 0.0
/*2218 */             break;                                                                // 0.0
/*2220 */         case 0x8000:                                                              // 0.0
/*2222 */             /* FETCH */                                                           // 0.0
/*2224 */             /* No-op */                                                           // 0.0
/*2226 */             break;                                                                // 0.0
/*2228 */         case 0xA000:                                                              // 0.0
/*2230 */             /* FETCH_M */                                                         // 0.0
/*2232 */             /* No-op */                                                           // 0.0
/*2234 */             break;                                                                // 0.0
/*2236 */         case 0xC000:                                                              // 0.0
/*2238 */             /* RPCC */                                                            // 0.0
/*2240 */             if (ra != 31) {                                                       // 0.0
/*2242 */                 if (use_icount) {                                                 // 0.0
/*2244 */                     gen_io_start();                                               // 0.0
/*2246 */                     gen_helper_load_pcc(cpu_ir[ra], cpu_env);                     // 0.0
/*2248 */                     gen_io_end();                                                 // 0.0
/*2250 */                     ret = EXIT_PC_STALE;                                          // 0.0
/*2252 */                 } else {                                                          // 0.0
/*2254 */                     gen_helper_load_pcc(cpu_ir[ra], cpu_env);                     // 0.0
/*2256 */                 }                                                                 // 0.0
/*2258 */             }                                                                     // 0.0
/*2260 */             break;                                                                // 0.0
/*2262 */         case 0xE000:                                                              // 0.0
/*2264 */             /* RC */                                                              // 0.0
/*2266 */             gen_rx(ra, 0);                                                        // 0.0
/*2268 */             break;                                                                // 0.0
/*2270 */         case 0xE800:                                                              // 0.0
/*2272 */             /* ECB */                                                             // 0.0
/*2274 */             break;                                                                // 0.0
/*2276 */         case 0xF000:                                                              // 0.0
/*2278 */             /* RS */                                                              // 0.0
/*2280 */             gen_rx(ra, 1);                                                        // 0.0
/*2282 */             break;                                                                // 0.0
/*2284 */         case 0xF800:                                                              // 0.0
/*2286 */             /* WH64 */                                                            // 0.0
/*2288 */             /* No-op */                                                           // 0.0
/*2290 */             break;                                                                // 0.0
/*2292 */         default:                                                                  // 0.0
/*2294 */             goto invalid_opc;                                                     // 0.0
/*2296 */         }                                                                         // 0.0
/*2298 */         break;                                                                    // 0.0
/*2300 */     case 0x19:                                                                    // 0.0
/*2302 */         /* HW_MFPR (PALcode) */                                                   // 0.0
/*2304 */ #ifndef CONFIG_USER_ONLY                                                          // 0.0
/*2306 */         if (ctx->tb->flags & TB_FLAGS_PAL_MODE) {                                 // 0.0
/*2308 */             return gen_mfpr(ra, insn & 0xffff);                                   // 0.0
/*2310 */         }                                                                         // 0.0
/*2312 */ #endif                                                                            // 0.0
/*2314 */         goto invalid_opc;                                                         // 0.0
/*2316 */     case 0x1A:                                                                    // 0.0
/*2318 */         /* JMP, JSR, RET, JSR_COROUTINE.  These only differ by the branch         // 0.0
/*2320 */            prediction stack action, which of course we don't implement.  */       // 0.0
/*2322 */         if (rb != 31) {                                                           // 0.0
/*2324 */             tcg_gen_andi_i64(cpu_pc, cpu_ir[rb], ~3);                             // 0.0
/*2326 */         } else {                                                                  // 0.0
/*2328 */             tcg_gen_movi_i64(cpu_pc, 0);                                          // 0.0
/*2330 */         }                                                                         // 0.0
/*2332 */         if (ra != 31) {                                                           // 0.0
/*2334 */             tcg_gen_movi_i64(cpu_ir[ra], ctx->pc);                                // 0.0
/*2336 */         }                                                                         // 0.0
/*2338 */         ret = EXIT_PC_UPDATED;                                                    // 0.0
/*2340 */         break;                                                                    // 0.0
/*2342 */     case 0x1B:                                                                    // 0.0
/*2344 */         /* HW_LD (PALcode) */                                                     // 0.0
/*2346 */ #ifndef CONFIG_USER_ONLY                                                          // 0.0
/*2348 */         if (ctx->tb->flags & TB_FLAGS_PAL_MODE) {                                 // 0.0
/*2350 */             TCGv addr;                                                            // 0.0
/*2354 */             if (ra == 31) {                                                       // 0.0
/*2356 */                 break;                                                            // 0.0
/*2358 */             }                                                                     // 0.0
/*2362 */             addr = tcg_temp_new();                                                // 0.0
/*2364 */             if (rb != 31) {                                                       // 0.0
/*2366 */                 tcg_gen_addi_i64(addr, cpu_ir[rb], disp12);                       // 0.0
/*2368 */             } else {                                                              // 0.0
/*2370 */                 tcg_gen_movi_i64(addr, disp12);                                   // 0.0
/*2372 */             }                                                                     // 0.0
/*2374 */             switch ((insn >> 12) & 0xF) {                                         // 0.0
/*2376 */             case 0x0:                                                             // 0.0
/*2378 */                 /* Longword physical access (hw_ldl/p) */                         // 0.0
/*2380 */                 gen_helper_ldl_phys(cpu_ir[ra], cpu_env, addr);                   // 0.0
/*2382 */                 break;                                                            // 0.0
/*2384 */             case 0x1:                                                             // 0.0
/*2386 */                 /* Quadword physical access (hw_ldq/p) */                         // 0.0
/*2388 */                 gen_helper_ldq_phys(cpu_ir[ra], cpu_env, addr);                   // 0.0
/*2390 */                 break;                                                            // 0.0
/*2392 */             case 0x2:                                                             // 0.0
/*2394 */                 /* Longword physical access with lock (hw_ldl_l/p) */             // 0.0
/*2396 */                 gen_helper_ldl_l_phys(cpu_ir[ra], cpu_env, addr);                 // 0.0
/*2398 */                 break;                                                            // 0.0
/*2400 */             case 0x3:                                                             // 0.0
/*2402 */                 /* Quadword physical access with lock (hw_ldq_l/p) */             // 0.0
/*2404 */                 gen_helper_ldq_l_phys(cpu_ir[ra], cpu_env, addr);                 // 0.0
/*2406 */                 break;                                                            // 0.0
/*2408 */             case 0x4:                                                             // 0.0
/*2410 */                 /* Longword virtual PTE fetch (hw_ldl/v) */                       // 0.0
/*2412 */                 goto invalid_opc;                                                 // 0.0
/*2414 */             case 0x5:                                                             // 0.0
/*2416 */                 /* Quadword virtual PTE fetch (hw_ldq/v) */                       // 0.0
/*2418 */                 goto invalid_opc;                                                 // 0.0
/*2420 */                 break;                                                            // 0.0
/*2422 */             case 0x6:                                                             // 0.0
/*2424 */                 /* Incpu_ir[ra]id */                                              // 0.0
/*2426 */                 goto invalid_opc;                                                 // 0.0
/*2428 */             case 0x7:                                                             // 0.0
/*2430 */                 /* Incpu_ir[ra]id */                                              // 0.0
/*2432 */                 goto invalid_opc;                                                 // 0.0
/*2434 */             case 0x8:                                                             // 0.0
/*2436 */                 /* Longword virtual access (hw_ldl) */                            // 0.0
/*2438 */                 goto invalid_opc;                                                 // 0.0
/*2440 */             case 0x9:                                                             // 0.0
/*2442 */                 /* Quadword virtual access (hw_ldq) */                            // 0.0
/*2444 */                 goto invalid_opc;                                                 // 0.0
/*2446 */             case 0xA:                                                             // 0.0
/*2448 */                 /* Longword virtual access with protection check (hw_ldl/w) */    // 0.0
/*2450 */                 tcg_gen_qemu_ld_i64(cpu_ir[ra], addr, MMU_KERNEL_IDX, MO_LESL);   // 0.0
/*2452 */                 break;                                                            // 0.0
/*2454 */             case 0xB:                                                             // 0.0
/*2456 */                 /* Quadword virtual access with protection check (hw_ldq/w) */    // 0.0
/*2458 */                 tcg_gen_qemu_ld_i64(cpu_ir[ra], addr, MMU_KERNEL_IDX, MO_LEQ);    // 0.0
/*2460 */                 break;                                                            // 0.0
/*2462 */             case 0xC:                                                             // 0.0
/*2464 */                 /* Longword virtual access with alt access mode (hw_ldl/a)*/      // 0.0
/*2466 */                 goto invalid_opc;                                                 // 0.0
/*2468 */             case 0xD:                                                             // 0.0
/*2470 */                 /* Quadword virtual access with alt access mode (hw_ldq/a) */     // 0.0
/*2472 */                 goto invalid_opc;                                                 // 0.0
/*2474 */             case 0xE:                                                             // 0.0
/*2476 */                 /* Longword virtual access with alternate access mode and         // 0.0
/*2478 */                    protection checks (hw_ldl/wa) */                               // 0.0
/*2480 */                 tcg_gen_qemu_ld_i64(cpu_ir[ra], addr, MMU_USER_IDX, MO_LESL);     // 0.0
/*2482 */                 break;                                                            // 0.0
/*2484 */             case 0xF:                                                             // 0.0
/*2486 */                 /* Quadword virtual access with alternate access mode and         // 0.0
/*2488 */                    protection checks (hw_ldq/wa) */                               // 0.0
/*2490 */                 tcg_gen_qemu_ld_i64(cpu_ir[ra], addr, MMU_USER_IDX, MO_LEQ);      // 0.0
/*2492 */                 break;                                                            // 0.0
/*2494 */             }                                                                     // 0.0
/*2496 */             tcg_temp_free(addr);                                                  // 0.0
/*2498 */             break;                                                                // 0.0
/*2500 */         }                                                                         // 0.0
/*2502 */ #endif                                                                            // 0.0
/*2504 */         goto invalid_opc;                                                         // 0.0
/*2506 */     case 0x1C:                                                                    // 0.0
/*2508 */         switch (fn7) {                                                            // 0.0
/*2510 */         case 0x00:                                                                // 0.0
/*2512 */             /* SEXTB */                                                           // 0.0
/*2514 */             if ((ctx->tb->flags & TB_FLAGS_AMASK_BWX) == 0) {                     // 0.0
/*2516 */                 goto invalid_opc;                                                 // 0.0
/*2518 */             }                                                                     // 0.0
/*2520 */             if (likely(rc != 31)) {                                               // 0.0
/*2522 */                 if (islit) {                                                      // 0.0
/*2524 */                     tcg_gen_movi_i64(cpu_ir[rc], (int64_t)((int8_t)lit));         // 0.0
/*2526 */                 } else {                                                          // 0.0
/*2528 */                     tcg_gen_ext8s_i64(cpu_ir[rc], cpu_ir[rb]);                    // 0.0
/*2530 */                 }                                                                 // 0.0
/*2532 */             }                                                                     // 0.0
/*2534 */             break;                                                                // 0.0
/*2536 */         case 0x01:                                                                // 0.0
/*2538 */             /* SEXTW */                                                           // 0.0
/*2540 */             if (ctx->tb->flags & TB_FLAGS_AMASK_BWX) {                            // 0.0
/*2542 */                 if (likely(rc != 31)) {                                           // 0.0
/*2544 */                     if (islit) {                                                  // 0.0
/*2546 */                         tcg_gen_movi_i64(cpu_ir[rc], (int64_t)((int16_t)lit));    // 0.0
/*2548 */                     } else {                                                      // 0.0
/*2550 */                         tcg_gen_ext16s_i64(cpu_ir[rc], cpu_ir[rb]);               // 0.0
/*2552 */                     }                                                             // 0.0
/*2554 */                 }                                                                 // 0.0
/*2556 */                 break;                                                            // 0.0
/*2558 */             }                                                                     // 0.0
/*2560 */             goto invalid_opc;                                                     // 0.0
/*2562 */         case 0x30:                                                                // 0.0
/*2564 */             /* CTPOP */                                                           // 0.0
/*2566 */             if (ctx->tb->flags & TB_FLAGS_AMASK_CIX) {                            // 0.0
/*2568 */                 if (likely(rc != 31)) {                                           // 0.0
/*2570 */                     if (islit) {                                                  // 0.0
/*2572 */                         tcg_gen_movi_i64(cpu_ir[rc], ctpop64(lit));               // 0.0
/*2574 */                     } else {                                                      // 0.0
/*2576 */                         gen_helper_ctpop(cpu_ir[rc], cpu_ir[rb]);                 // 0.0
/*2578 */                     }                                                             // 0.0
/*2580 */                 }                                                                 // 0.0
/*2582 */                 break;                                                            // 0.0
/*2584 */             }                                                                     // 0.0
/*2586 */             goto invalid_opc;                                                     // 0.0
/*2588 */         case 0x31:                                                                // 0.0
/*2590 */             /* PERR */                                                            // 0.0
/*2592 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2594 */                 gen_perr(ra, rb, rc, islit, lit);                                 // 0.0
/*2596 */                 break;                                                            // 0.0
/*2598 */             }                                                                     // 0.0
/*2600 */             goto invalid_opc;                                                     // 0.0
/*2602 */         case 0x32:                                                                // 0.0
/*2604 */             /* CTLZ */                                                            // 0.0
/*2606 */             if (ctx->tb->flags & TB_FLAGS_AMASK_CIX) {                            // 0.0
/*2608 */                 if (likely(rc != 31)) {                                           // 0.0
/*2610 */                     if (islit) {                                                  // 0.0
/*2612 */                         tcg_gen_movi_i64(cpu_ir[rc], clz64(lit));                 // 0.0
/*2614 */                     } else {                                                      // 0.0
/*2616 */                         gen_helper_ctlz(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*2618 */                     }                                                             // 0.0
/*2620 */                 }                                                                 // 0.0
/*2622 */                 break;                                                            // 0.0
/*2624 */             }                                                                     // 0.0
/*2626 */             goto invalid_opc;                                                     // 0.0
/*2628 */         case 0x33:                                                                // 0.0
/*2630 */             /* CTTZ */                                                            // 0.0
/*2632 */             if (ctx->tb->flags & TB_FLAGS_AMASK_CIX) {                            // 0.0
/*2634 */                 if (likely(rc != 31)) {                                           // 0.0
/*2636 */                     if (islit) {                                                  // 0.0
/*2638 */                         tcg_gen_movi_i64(cpu_ir[rc], ctz64(lit));                 // 0.0
/*2640 */                     } else {                                                      // 0.0
/*2642 */                         gen_helper_cttz(cpu_ir[rc], cpu_ir[rb]);                  // 0.0
/*2644 */                     }                                                             // 0.0
/*2646 */                 }                                                                 // 0.0
/*2648 */                 break;                                                            // 0.0
/*2650 */             }                                                                     // 0.0
/*2652 */             goto invalid_opc;                                                     // 0.0
/*2654 */         case 0x34:                                                                // 0.0
/*2656 */             /* UNPKBW */                                                          // 0.0
/*2658 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2660 */                 if (real_islit || ra != 31) {                                     // 0.0
/*2662 */                     goto invalid_opc;                                             // 0.0
/*2664 */                 }                                                                 // 0.0
/*2666 */                 gen_unpkbw(rb, rc);                                               // 0.0
/*2668 */                 break;                                                            // 0.0
/*2670 */             }                                                                     // 0.0
/*2672 */             goto invalid_opc;                                                     // 0.0
/*2674 */         case 0x35:                                                                // 0.0
/*2676 */             /* UNPKBL */                                                          // 0.0
/*2678 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2680 */                 if (real_islit || ra != 31) {                                     // 0.0
/*2682 */                     goto invalid_opc;                                             // 0.0
/*2684 */                 }                                                                 // 0.0
/*2686 */                 gen_unpkbl(rb, rc);                                               // 0.0
/*2688 */                 break;                                                            // 0.0
/*2690 */             }                                                                     // 0.0
/*2692 */             goto invalid_opc;                                                     // 0.0
/*2694 */         case 0x36:                                                                // 0.0
/*2696 */             /* PKWB */                                                            // 0.0
/*2698 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2700 */                 if (real_islit || ra != 31) {                                     // 0.0
/*2702 */                     goto invalid_opc;                                             // 0.0
/*2704 */                 }                                                                 // 0.0
/*2706 */                 gen_pkwb(rb, rc);                                                 // 0.0
/*2708 */                 break;                                                            // 0.0
/*2710 */             }                                                                     // 0.0
/*2712 */             goto invalid_opc;                                                     // 0.0
/*2714 */         case 0x37:                                                                // 0.0
/*2716 */             /* PKLB */                                                            // 0.0
/*2718 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2720 */                 if (real_islit || ra != 31) {                                     // 0.0
/*2722 */                     goto invalid_opc;                                             // 0.0
/*2724 */                 }                                                                 // 0.0
/*2726 */                 gen_pklb(rb, rc);                                                 // 0.0
/*2728 */                 break;                                                            // 0.0
/*2730 */             }                                                                     // 0.0
/*2732 */             goto invalid_opc;                                                     // 0.0
/*2734 */         case 0x38:                                                                // 0.0
/*2736 */             /* MINSB8 */                                                          // 0.0
/*2738 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2740 */                 gen_minsb8(ra, rb, rc, islit, lit);                               // 0.0
/*2742 */                 break;                                                            // 0.0
/*2744 */             }                                                                     // 0.0
/*2746 */             goto invalid_opc;                                                     // 0.0
/*2748 */         case 0x39:                                                                // 0.0
/*2750 */             /* MINSW4 */                                                          // 0.0
/*2752 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2754 */                 gen_minsw4(ra, rb, rc, islit, lit);                               // 0.0
/*2756 */                 break;                                                            // 0.0
/*2758 */             }                                                                     // 0.0
/*2760 */             goto invalid_opc;                                                     // 0.0
/*2762 */         case 0x3A:                                                                // 0.0
/*2764 */             /* MINUB8 */                                                          // 0.0
/*2766 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2768 */                 gen_minub8(ra, rb, rc, islit, lit);                               // 0.0
/*2770 */                 break;                                                            // 0.0
/*2772 */             }                                                                     // 0.0
/*2774 */             goto invalid_opc;                                                     // 0.0
/*2776 */         case 0x3B:                                                                // 0.0
/*2778 */             /* MINUW4 */                                                          // 0.0
/*2780 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2782 */                 gen_minuw4(ra, rb, rc, islit, lit);                               // 0.0
/*2784 */                 break;                                                            // 0.0
/*2786 */             }                                                                     // 0.0
/*2788 */             goto invalid_opc;                                                     // 0.0
/*2790 */         case 0x3C:                                                                // 0.0
/*2792 */             /* MAXUB8 */                                                          // 0.0
/*2794 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2796 */                 gen_maxub8(ra, rb, rc, islit, lit);                               // 0.0
/*2798 */                 break;                                                            // 0.0
/*2800 */             }                                                                     // 0.0
/*2802 */             goto invalid_opc;                                                     // 0.0
/*2804 */         case 0x3D:                                                                // 0.0
/*2806 */             /* MAXUW4 */                                                          // 0.0
/*2808 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2810 */                 gen_maxuw4(ra, rb, rc, islit, lit);                               // 0.0
/*2812 */                 break;                                                            // 0.0
/*2814 */             }                                                                     // 0.0
/*2816 */             goto invalid_opc;                                                     // 0.0
/*2818 */         case 0x3E:                                                                // 0.0
/*2820 */             /* MAXSB8 */                                                          // 0.0
/*2822 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2824 */                 gen_maxsb8(ra, rb, rc, islit, lit);                               // 0.0
/*2826 */                 break;                                                            // 0.0
/*2828 */             }                                                                     // 0.0
/*2830 */             goto invalid_opc;                                                     // 0.0
/*2832 */         case 0x3F:                                                                // 0.0
/*2834 */             /* MAXSW4 */                                                          // 0.0
/*2836 */             if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {                            // 0.0
/*2838 */                 gen_maxsw4(ra, rb, rc, islit, lit);                               // 0.0
/*2840 */                 break;                                                            // 0.0
/*2842 */             }                                                                     // 0.0
/*2844 */             goto invalid_opc;                                                     // 0.0
/*2846 */         case 0x70:                                                                // 0.0
/*2848 */             /* FTOIT */                                                           // 0.0
/*2850 */             if ((ctx->tb->flags & TB_FLAGS_AMASK_FIX) == 0) {                     // 0.0
/*2852 */                 goto invalid_opc;                                                 // 0.0
/*2854 */             }                                                                     // 0.0
/*2856 */             if (likely(rc != 31)) {                                               // 0.0
/*2858 */                 if (ra != 31) {                                                   // 0.0
/*2860 */                     tcg_gen_mov_i64(cpu_ir[rc], cpu_fir[ra]);                     // 0.0
/*2862 */                 } else {                                                          // 0.0
/*2864 */                     tcg_gen_movi_i64(cpu_ir[rc], 0);                              // 0.0
/*2866 */                 }                                                                 // 0.0
/*2868 */             }                                                                     // 0.0
/*2870 */             break;                                                                // 0.0
/*2872 */         case 0x78:                                                                // 0.0
/*2874 */             /* FTOIS */                                                           // 0.0
/*2876 */             if ((ctx->tb->flags & TB_FLAGS_AMASK_FIX) == 0) {                     // 0.0
/*2878 */                 goto invalid_opc;                                                 // 0.0
/*2880 */             }                                                                     // 0.0
/*2882 */             if (rc != 31) {                                                       // 0.0
/*2884 */                 TCGv_i32 tmp1 = tcg_temp_new_i32();                               // 0.0
/*2886 */                 if (ra != 31) {                                                   // 0.0
/*2888 */                     gen_helper_s_to_memory(tmp1, cpu_fir[ra]);                    // 0.0
/*2890 */                 } else {                                                          // 0.0
/*2892 */                     TCGv tmp2 = tcg_const_i64(0);                                 // 0.0
/*2894 */                     gen_helper_s_to_memory(tmp1, tmp2);                           // 0.0
/*2896 */                     tcg_temp_free(tmp2);                                          // 0.0
/*2898 */                 }                                                                 // 0.0
/*2900 */                 tcg_gen_ext_i32_i64(cpu_ir[rc], tmp1);                            // 0.0
/*2902 */                 tcg_temp_free_i32(tmp1);                                          // 0.0
/*2904 */             }                                                                     // 0.0
/*2906 */             break;                                                                // 0.0
/*2908 */         default:                                                                  // 0.0
/*2910 */             goto invalid_opc;                                                     // 0.0
/*2912 */         }                                                                         // 0.0
/*2914 */         break;                                                                    // 0.0
/*2916 */     case 0x1D:                                                                    // 0.0
/*2918 */         /* HW_MTPR (PALcode) */                                                   // 0.0
/*2920 */ #ifndef CONFIG_USER_ONLY                                                          // 0.0
/*2922 */         if (ctx->tb->flags & TB_FLAGS_PAL_MODE) {                                 // 0.0
/*2924 */             return gen_mtpr(ctx, rb, insn & 0xffff);                              // 0.0
/*2926 */         }                                                                         // 0.0
/*2928 */ #endif                                                                            // 0.0
/*2930 */         goto invalid_opc;                                                         // 0.0
/*2932 */     case 0x1E:                                                                    // 0.0
/*2934 */         /* HW_RET (PALcode) */                                                    // 0.0
/*2936 */ #ifndef CONFIG_USER_ONLY                                                          // 0.0
/*2938 */         if (ctx->tb->flags & TB_FLAGS_PAL_MODE) {                                 // 0.0
/*2940 */             if (rb == 31) {                                                       // 0.0
/*2942 */                 /* Pre-EV6 CPUs interpreted this as HW_REI, loading the return    // 0.0
/*2944 */                    address from EXC_ADDR.  This turns out to be useful for our    // 0.0
/*2946 */                    emulation PALcode, so continue to accept it.  */               // 0.0
/*2948 */                 TCGv tmp = tcg_temp_new();                                        // 0.0
/*2950 */                 tcg_gen_ld_i64(tmp, cpu_env, offsetof(CPUAlphaState, exc_addr));  // 0.0
/*2952 */                 gen_helper_hw_ret(cpu_env, tmp);                                  // 0.0
/*2954 */                 tcg_temp_free(tmp);                                               // 0.0
/*2956 */             } else {                                                              // 0.0
/*2958 */                 gen_helper_hw_ret(cpu_env, cpu_ir[rb]);                           // 0.0
/*2960 */             }                                                                     // 0.0
/*2962 */             ret = EXIT_PC_UPDATED;                                                // 0.0
/*2964 */             break;                                                                // 0.0
/*2966 */         }                                                                         // 0.0
/*2968 */ #endif                                                                            // 0.0
/*2970 */         goto invalid_opc;                                                         // 0.0
/*2972 */     case 0x1F:                                                                    // 0.0
/*2974 */         /* HW_ST (PALcode) */                                                     // 0.0
/*2976 */ #ifndef CONFIG_USER_ONLY                                                          // 0.0
/*2978 */         if (ctx->tb->flags & TB_FLAGS_PAL_MODE) {                                 // 0.0
/*2980 */             TCGv addr, val;                                                       // 0.0
/*2982 */             addr = tcg_temp_new();                                                // 0.0
/*2984 */             if (rb != 31) {                                                       // 0.0
/*2986 */                 tcg_gen_addi_i64(addr, cpu_ir[rb], disp12);                       // 0.0
/*2988 */             } else {                                                              // 0.0
/*2990 */                 tcg_gen_movi_i64(addr, disp12);                                   // 0.0
/*2992 */             }                                                                     // 0.0
/*2994 */             if (ra != 31) {                                                       // 0.0
/*2996 */                 val = cpu_ir[ra];                                                 // 0.0
/*2998 */             } else {                                                              // 0.0
/*3000 */                 val = tcg_temp_new();                                             // 0.0
/*3002 */                 tcg_gen_movi_i64(val, 0);                                         // 0.0
/*3004 */             }                                                                     // 0.0
/*3006 */             switch ((insn >> 12) & 0xF) {                                         // 0.0
/*3008 */             case 0x0:                                                             // 0.0
/*3010 */                 /* Longword physical access */                                    // 0.0
/*3012 */                 gen_helper_stl_phys(cpu_env, addr, val);                          // 0.0
/*3014 */                 break;                                                            // 0.0
/*3016 */             case 0x1:                                                             // 0.0
/*3018 */                 /* Quadword physical access */                                    // 0.0
/*3020 */                 gen_helper_stq_phys(cpu_env, addr, val);                          // 0.0
/*3022 */                 break;                                                            // 0.0
/*3024 */             case 0x2:                                                             // 0.0
/*3026 */                 /* Longword physical access with lock */                          // 0.0
/*3028 */                 gen_helper_stl_c_phys(val, cpu_env, addr, val);                   // 0.0
/*3030 */                 break;                                                            // 0.0
/*3032 */             case 0x3:                                                             // 0.0
/*3034 */                 /* Quadword physical access with lock */                          // 0.0
/*3036 */                 gen_helper_stq_c_phys(val, cpu_env, addr, val);                   // 0.0
/*3038 */                 break;                                                            // 0.0
/*3040 */             case 0x4:                                                             // 0.0
/*3042 */                 /* Longword virtual access */                                     // 0.0
/*3044 */                 goto invalid_opc;                                                 // 0.0
/*3046 */             case 0x5:                                                             // 0.0
/*3048 */                 /* Quadword virtual access */                                     // 0.0
/*3050 */                 goto invalid_opc;                                                 // 0.0
/*3052 */             case 0x6:                                                             // 0.0
/*3054 */                 /* Invalid */                                                     // 0.0
/*3056 */                 goto invalid_opc;                                                 // 0.0
/*3058 */             case 0x7:                                                             // 0.0
/*3060 */                 /* Invalid */                                                     // 0.0
/*3062 */                 goto invalid_opc;                                                 // 0.0
/*3064 */             case 0x8:                                                             // 0.0
/*3066 */                 /* Invalid */                                                     // 0.0
/*3068 */                 goto invalid_opc;                                                 // 0.0
/*3070 */             case 0x9:                                                             // 0.0
/*3072 */                 /* Invalid */                                                     // 0.0
/*3074 */                 goto invalid_opc;                                                 // 0.0
/*3076 */             case 0xA:                                                             // 0.0
/*3078 */                 /* Invalid */                                                     // 0.0
/*3080 */                 goto invalid_opc;                                                 // 0.0
/*3082 */             case 0xB:                                                             // 0.0
/*3084 */                 /* Invalid */                                                     // 0.0
/*3086 */                 goto invalid_opc;                                                 // 0.0
/*3088 */             case 0xC:                                                             // 0.0
/*3090 */                 /* Longword virtual access with alternate access mode */          // 0.0
/*3092 */                 goto invalid_opc;                                                 // 0.0
/*3094 */             case 0xD:                                                             // 0.0
/*3096 */                 /* Quadword virtual access with alternate access mode */          // 0.0
/*3098 */                 goto invalid_opc;                                                 // 0.0
/*3100 */             case 0xE:                                                             // 0.0
/*3102 */                 /* Invalid */                                                     // 0.0
/*3104 */                 goto invalid_opc;                                                 // 0.0
/*3106 */             case 0xF:                                                             // 0.0
/*3108 */                 /* Invalid */                                                     // 0.0
/*3110 */                 goto invalid_opc;                                                 // 0.0
/*3112 */             }                                                                     // 0.0
/*3114 */             if (ra == 31) {                                                       // 0.0
/*3116 */                 tcg_temp_free(val);                                               // 0.0
/*3118 */             }                                                                     // 0.0
/*3120 */             tcg_temp_free(addr);                                                  // 0.0
/*3122 */             break;                                                                // 0.0
/*3124 */         }                                                                         // 0.0
/*3126 */ #endif                                                                            // 0.0
/*3128 */         goto invalid_opc;                                                         // 0.0
/*3130 */     case 0x20:                                                                    // 0.0
/*3132 */         /* LDF */                                                                 // 0.0
/*3134 */         gen_load_mem(ctx, &gen_qemu_ldf, ra, rb, disp16, 1, 0);                   // 0.0
/*3136 */         break;                                                                    // 0.0
/*3138 */     case 0x21:                                                                    // 0.0
/*3140 */         /* LDG */                                                                 // 0.0
/*3142 */         gen_load_mem(ctx, &gen_qemu_ldg, ra, rb, disp16, 1, 0);                   // 0.0
/*3144 */         break;                                                                    // 0.0
/*3146 */     case 0x22:                                                                    // 0.0
/*3148 */         /* LDS */                                                                 // 0.0
/*3150 */         gen_load_mem(ctx, &gen_qemu_lds, ra, rb, disp16, 1, 0);                   // 0.0
/*3152 */         break;                                                                    // 0.0
/*3154 */     case 0x23:                                                                    // 0.0
/*3156 */         /* LDT */                                                                 // 0.0
/*3158 */         gen_load_mem(ctx, &tcg_gen_qemu_ld64, ra, rb, disp16, 1, 0);              // 0.0
/*3160 */         break;                                                                    // 0.0
/*3162 */     case 0x24:                                                                    // 0.0
/*3164 */         /* STF */                                                                 // 0.0
/*3166 */         gen_store_mem(ctx, &gen_qemu_stf, ra, rb, disp16, 1, 0);                  // 0.0
/*3168 */         break;                                                                    // 0.0
/*3170 */     case 0x25:                                                                    // 0.0
/*3172 */         /* STG */                                                                 // 0.0
/*3174 */         gen_store_mem(ctx, &gen_qemu_stg, ra, rb, disp16, 1, 0);                  // 0.0
/*3176 */         break;                                                                    // 0.0
/*3178 */     case 0x26:                                                                    // 0.0
/*3180 */         /* STS */                                                                 // 0.0
/*3182 */         gen_store_mem(ctx, &gen_qemu_sts, ra, rb, disp16, 1, 0);                  // 0.0
/*3184 */         break;                                                                    // 0.0
/*3186 */     case 0x27:                                                                    // 0.0
/*3188 */         /* STT */                                                                 // 0.0
/*3190 */         gen_store_mem(ctx, &tcg_gen_qemu_st64, ra, rb, disp16, 1, 0);             // 0.0
/*3192 */         break;                                                                    // 0.0
/*3194 */     case 0x28:                                                                    // 0.0
/*3196 */         /* LDL */                                                                 // 0.0
/*3198 */         gen_load_mem(ctx, &tcg_gen_qemu_ld32s, ra, rb, disp16, 0, 0);             // 0.0
/*3200 */         break;                                                                    // 0.0
/*3202 */     case 0x29:                                                                    // 0.0
/*3204 */         /* LDQ */                                                                 // 0.0
/*3206 */         gen_load_mem(ctx, &tcg_gen_qemu_ld64, ra, rb, disp16, 0, 0);              // 0.0
/*3208 */         break;                                                                    // 0.0
/*3210 */     case 0x2A:                                                                    // 0.0
/*3212 */         /* LDL_L */                                                               // 0.0
/*3214 */         gen_load_mem(ctx, &gen_qemu_ldl_l, ra, rb, disp16, 0, 0);                 // 0.0
/*3216 */         break;                                                                    // 0.0
/*3218 */     case 0x2B:                                                                    // 0.0
/*3220 */         /* LDQ_L */                                                               // 0.0
/*3222 */         gen_load_mem(ctx, &gen_qemu_ldq_l, ra, rb, disp16, 0, 0);                 // 0.0
/*3224 */         break;                                                                    // 0.0
/*3226 */     case 0x2C:                                                                    // 0.0
/*3228 */         /* STL */                                                                 // 0.0
/*3230 */         gen_store_mem(ctx, &tcg_gen_qemu_st32, ra, rb, disp16, 0, 0);             // 0.0
/*3232 */         break;                                                                    // 0.0
/*3234 */     case 0x2D:                                                                    // 0.0
/*3236 */         /* STQ */                                                                 // 0.0
/*3238 */         gen_store_mem(ctx, &tcg_gen_qemu_st64, ra, rb, disp16, 0, 0);             // 0.0
/*3240 */         break;                                                                    // 0.0
/*3242 */     case 0x2E:                                                                    // 0.0
/*3244 */         /* STL_C */                                                               // 0.0
/*3246 */         ret = gen_store_conditional(ctx, ra, rb, disp16, 0);                      // 0.0
/*3248 */         break;                                                                    // 0.0
/*3250 */     case 0x2F:                                                                    // 0.0
/*3252 */         /* STQ_C */                                                               // 0.0
/*3254 */         ret = gen_store_conditional(ctx, ra, rb, disp16, 1);                      // 0.0
/*3256 */         break;                                                                    // 0.0
/*3258 */     case 0x30:                                                                    // 0.0
/*3260 */         /* BR */                                                                  // 0.0
/*3262 */         ret = gen_bdirect(ctx, ra, disp21);                                       // 0.0
/*3264 */         break;                                                                    // 0.0
/*3266 */     case 0x31: /* FBEQ */                                                         // 0.0
/*3268 */         ret = gen_fbcond(ctx, TCG_COND_EQ, ra, disp21);                           // 0.0
/*3270 */         break;                                                                    // 0.0
/*3272 */     case 0x32: /* FBLT */                                                         // 0.0
/*3274 */         ret = gen_fbcond(ctx, TCG_COND_LT, ra, disp21);                           // 0.0
/*3276 */         break;                                                                    // 0.0
/*3278 */     case 0x33: /* FBLE */                                                         // 0.0
/*3280 */         ret = gen_fbcond(ctx, TCG_COND_LE, ra, disp21);                           // 0.0
/*3282 */         break;                                                                    // 0.0
/*3284 */     case 0x34:                                                                    // 0.0
/*3286 */         /* BSR */                                                                 // 0.0
/*3288 */         ret = gen_bdirect(ctx, ra, disp21);                                       // 0.0
/*3290 */         break;                                                                    // 0.0
/*3292 */     case 0x35: /* FBNE */                                                         // 0.0
/*3294 */         ret = gen_fbcond(ctx, TCG_COND_NE, ra, disp21);                           // 0.0
/*3296 */         break;                                                                    // 0.0
/*3298 */     case 0x36: /* FBGE */                                                         // 0.0
/*3300 */         ret = gen_fbcond(ctx, TCG_COND_GE, ra, disp21);                           // 0.0
/*3302 */         break;                                                                    // 0.0
/*3304 */     case 0x37: /* FBGT */                                                         // 0.0
/*3306 */         ret = gen_fbcond(ctx, TCG_COND_GT, ra, disp21);                           // 0.0
/*3308 */         break;                                                                    // 0.0
/*3310 */     case 0x38:                                                                    // 0.0
/*3312 */         /* BLBC */                                                                // 0.0
/*3314 */         ret = gen_bcond(ctx, TCG_COND_EQ, ra, disp21, 1);                         // 0.0
/*3316 */         break;                                                                    // 0.0
/*3318 */     case 0x39:                                                                    // 0.0
/*3320 */         /* BEQ */                                                                 // 0.0
/*3322 */         ret = gen_bcond(ctx, TCG_COND_EQ, ra, disp21, 0);                         // 0.0
/*3324 */         break;                                                                    // 0.0
/*3326 */     case 0x3A:                                                                    // 0.0
/*3328 */         /* BLT */                                                                 // 0.0
/*3330 */         ret = gen_bcond(ctx, TCG_COND_LT, ra, disp21, 0);                         // 0.0
/*3332 */         break;                                                                    // 0.0
/*3334 */     case 0x3B:                                                                    // 0.0
/*3336 */         /* BLE */                                                                 // 0.0
/*3338 */         ret = gen_bcond(ctx, TCG_COND_LE, ra, disp21, 0);                         // 0.0
/*3340 */         break;                                                                    // 0.0
/*3342 */     case 0x3C:                                                                    // 0.0
/*3344 */         /* BLBS */                                                                // 0.0
/*3346 */         ret = gen_bcond(ctx, TCG_COND_NE, ra, disp21, 1);                         // 0.0
/*3348 */         break;                                                                    // 0.0
/*3350 */     case 0x3D:                                                                    // 0.0
/*3352 */         /* BNE */                                                                 // 0.0
/*3354 */         ret = gen_bcond(ctx, TCG_COND_NE, ra, disp21, 0);                         // 0.0
/*3356 */         break;                                                                    // 0.0
/*3358 */     case 0x3E:                                                                    // 0.0
/*3360 */         /* BGE */                                                                 // 0.0
/*3362 */         ret = gen_bcond(ctx, TCG_COND_GE, ra, disp21, 0);                         // 0.0
/*3364 */         break;                                                                    // 0.0
/*3366 */     case 0x3F:                                                                    // 0.0
/*3368 */         /* BGT */                                                                 // 0.0
/*3370 */         ret = gen_bcond(ctx, TCG_COND_GT, ra, disp21, 0);                         // 0.0
/*3372 */         break;                                                                    // 0.0
/*3374 */     invalid_opc:                                                                  // 0.0
/*3376 */         ret = gen_invalid(ctx);                                                   // 0.0
/*3378 */         break;                                                                    // 0.0
/*3380 */     }                                                                             // 0.0
/*3384 */     return ret;                                                                   // 0.0
/*3386 */ }                                                                                 // 0.0
