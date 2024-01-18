// commit message qemu@42a268c241 (target=0, prob=0.24496545, correct=True): tcg: Change translator-side labels to a pointer
/*0   */ static void dec_calc(DisasContext *dc, uint32_t insn)                        // (8) 0.03906
/*2   */ {                                                                            // (22) 0.001953
/*4   */     uint32_t op0, op1, op2;                                                  // (10) 0.03125
/*6   */     uint32_t ra, rb, rd;                                                     // (16) 0.0293
/*8   */     op0 = extract32(insn, 0, 4);                                             // (11) 0.03125
/*10  */     op1 = extract32(insn, 8, 2);                                             // (12) 0.03125
/*12  */     op2 = extract32(insn, 6, 2);                                             // (13) 0.03125
/*14  */     ra = extract32(insn, 16, 5);                                             // (17) 0.0293
/*16  */     rb = extract32(insn, 11, 5);                                             // (14) 0.03125
/*18  */     rd = extract32(insn, 21, 5);                                             // (15) 0.03125
/*22  */     switch (op0) {                                                           // (20) 0.01758
/*24  */     case 0x0000:                                                             // (21) 0.01562
/*26  */         switch (op1) {                                                       // (18) 0.02539
/*28  */         case 0x00:    /* l.add */                                            // (9) 0.03906
/*30  */             LOG_DIS("l.add r%d, r%d, r%d\n", rd, ra, rb);                    // (0) 0.07812
/*32  */             {                                                                // (19) 0.02344
/*34  */                 int lab = gen_new_label();                                   // (7) 0.04688
/*36  */                 TCGv_i64 ta = tcg_temp_new_i64();                            // (6) 0.06445
/*38  */                 TCGv_i64 tb = tcg_temp_new_i64();                            // (5) 0.06641
/*40  */                 TCGv_i64 td = tcg_temp_local_new_i64();                      // (3) 0.06836
/*42  */                 TCGv_i32 res = tcg_temp_local_new_i32();                     // (4) 0.06836
/*44  */                 TCGv_i32 sr_ove = tcg_temp_local_new_i32();                  // (1) 0.07227
/*46  */                 tcg_gen_extu_i32_i64(ta, cpu_R[ra]);                         // (2) 0.07227
/*48  */                 tcg_gen_extu_i32_i64(tb, cpu_R[rb]);                         // 0.0
/*50  */                 tcg_gen_add_i64(td, ta, tb);                                 // 0.0
/*52  */                 tcg_gen_trunc_i64_i32(res, td);                              // 0.0
/*54  */                 tcg_gen_shri_i64(td, td, 31);                                // 0.0
/*56  */                 tcg_gen_andi_i64(td, td, 0x3);                               // 0.0
/*58  */                 /* Jump to lab when no overflow.  */                         // 0.0
/*60  */                 tcg_gen_brcondi_i64(TCG_COND_EQ, td, 0x0, lab);              // 0.0
/*62  */                 tcg_gen_brcondi_i64(TCG_COND_EQ, td, 0x3, lab);              // 0.0
/*64  */                 tcg_gen_ori_i32(cpu_sr, cpu_sr, (SR_OV | SR_CY));            // 0.0
/*66  */                 tcg_gen_andi_i32(sr_ove, cpu_sr, SR_OVE);                    // 0.0
/*68  */                 tcg_gen_brcondi_i32(TCG_COND_NE, sr_ove, SR_OVE, lab);       // 0.0
/*70  */                 gen_exception(dc, EXCP_RANGE);                               // 0.0
/*72  */                 gen_set_label(lab);                                          // 0.0
/*74  */                 tcg_gen_mov_i32(cpu_R[rd], res);                             // 0.0
/*76  */                 tcg_temp_free_i64(ta);                                       // 0.0
/*78  */                 tcg_temp_free_i64(tb);                                       // 0.0
/*80  */                 tcg_temp_free_i64(td);                                       // 0.0
/*82  */                 tcg_temp_free_i32(res);                                      // 0.0
/*84  */                 tcg_temp_free_i32(sr_ove);                                   // 0.0
/*86  */             }                                                                // 0.0
/*88  */             break;                                                           // 0.0
/*90  */         default:                                                             // 0.0
/*92  */             gen_illegal_exception(dc);                                       // 0.0
/*94  */             break;                                                           // 0.0
/*96  */         }                                                                    // 0.0
/*98  */         break;                                                               // 0.0
/*102 */     case 0x0001:    /* l.addc */                                             // 0.0
/*104 */         switch (op1) {                                                       // 0.0
/*106 */         case 0x00:                                                           // 0.0
/*108 */             LOG_DIS("l.addc r%d, r%d, r%d\n", rd, ra, rb);                   // 0.0
/*110 */             {                                                                // 0.0
/*112 */                 int lab = gen_new_label();                                   // 0.0
/*114 */                 TCGv_i64 ta = tcg_temp_new_i64();                            // 0.0
/*116 */                 TCGv_i64 tb = tcg_temp_new_i64();                            // 0.0
/*118 */                 TCGv_i64 tcy = tcg_temp_local_new_i64();                     // 0.0
/*120 */                 TCGv_i64 td = tcg_temp_local_new_i64();                      // 0.0
/*122 */                 TCGv_i32 res = tcg_temp_local_new_i32();                     // 0.0
/*124 */                 TCGv_i32 sr_cy = tcg_temp_local_new_i32();                   // 0.0
/*126 */                 TCGv_i32 sr_ove = tcg_temp_local_new_i32();                  // 0.0
/*128 */                 tcg_gen_extu_i32_i64(ta, cpu_R[ra]);                         // 0.0
/*130 */                 tcg_gen_extu_i32_i64(tb, cpu_R[rb]);                         // 0.0
/*132 */                 tcg_gen_andi_i32(sr_cy, cpu_sr, SR_CY);                      // 0.0
/*134 */                 tcg_gen_extu_i32_i64(tcy, sr_cy);                            // 0.0
/*136 */                 tcg_gen_shri_i64(tcy, tcy, 10);                              // 0.0
/*138 */                 tcg_gen_add_i64(td, ta, tb);                                 // 0.0
/*140 */                 tcg_gen_add_i64(td, td, tcy);                                // 0.0
/*142 */                 tcg_gen_trunc_i64_i32(res, td);                              // 0.0
/*144 */                 tcg_gen_shri_i64(td, td, 32);                                // 0.0
/*146 */                 tcg_gen_andi_i64(td, td, 0x3);                               // 0.0
/*148 */                 /* Jump to lab when no overflow.  */                         // 0.0
/*150 */                 tcg_gen_brcondi_i64(TCG_COND_EQ, td, 0x0, lab);              // 0.0
/*152 */                 tcg_gen_brcondi_i64(TCG_COND_EQ, td, 0x3, lab);              // 0.0
/*154 */                 tcg_gen_ori_i32(cpu_sr, cpu_sr, (SR_OV | SR_CY));            // 0.0
/*156 */                 tcg_gen_andi_i32(sr_ove, cpu_sr, SR_OVE);                    // 0.0
/*158 */                 tcg_gen_brcondi_i32(TCG_COND_NE, sr_ove, SR_OVE, lab);       // 0.0
/*160 */                 gen_exception(dc, EXCP_RANGE);                               // 0.0
/*162 */                 gen_set_label(lab);                                          // 0.0
/*164 */                 tcg_gen_mov_i32(cpu_R[rd], res);                             // 0.0
/*166 */                 tcg_temp_free_i64(ta);                                       // 0.0
/*168 */                 tcg_temp_free_i64(tb);                                       // 0.0
/*170 */                 tcg_temp_free_i64(tcy);                                      // 0.0
/*172 */                 tcg_temp_free_i64(td);                                       // 0.0
/*174 */                 tcg_temp_free_i32(res);                                      // 0.0
/*176 */                 tcg_temp_free_i32(sr_cy);                                    // 0.0
/*178 */                 tcg_temp_free_i32(sr_ove);                                   // 0.0
/*180 */             }                                                                // 0.0
/*182 */             break;                                                           // 0.0
/*184 */         default:                                                             // 0.0
/*186 */             gen_illegal_exception(dc);                                       // 0.0
/*188 */             break;                                                           // 0.0
/*190 */         }                                                                    // 0.0
/*192 */         break;                                                               // 0.0
/*196 */     case 0x0002:    /* l.sub */                                              // 0.0
/*198 */         switch (op1) {                                                       // 0.0
/*200 */         case 0x00:                                                           // 0.0
/*202 */             LOG_DIS("l.sub r%d, r%d, r%d\n", rd, ra, rb);                    // 0.0
/*204 */             {                                                                // 0.0
/*206 */                 int lab = gen_new_label();                                   // 0.0
/*208 */                 TCGv_i64 ta = tcg_temp_new_i64();                            // 0.0
/*210 */                 TCGv_i64 tb = tcg_temp_new_i64();                            // 0.0
/*212 */                 TCGv_i64 td = tcg_temp_local_new_i64();                      // 0.0
/*214 */                 TCGv_i32 res = tcg_temp_local_new_i32();                     // 0.0
/*216 */                 TCGv_i32 sr_ove = tcg_temp_local_new_i32();                  // 0.0
/*220 */                 tcg_gen_extu_i32_i64(ta, cpu_R[ra]);                         // 0.0
/*222 */                 tcg_gen_extu_i32_i64(tb, cpu_R[rb]);                         // 0.0
/*224 */                 tcg_gen_sub_i64(td, ta, tb);                                 // 0.0
/*226 */                 tcg_gen_trunc_i64_i32(res, td);                              // 0.0
/*228 */                 tcg_gen_shri_i64(td, td, 31);                                // 0.0
/*230 */                 tcg_gen_andi_i64(td, td, 0x3);                               // 0.0
/*232 */                 /* Jump to lab when no overflow.  */                         // 0.0
/*234 */                 tcg_gen_brcondi_i64(TCG_COND_EQ, td, 0x0, lab);              // 0.0
/*236 */                 tcg_gen_brcondi_i64(TCG_COND_EQ, td, 0x3, lab);              // 0.0
/*238 */                 tcg_gen_ori_i32(cpu_sr, cpu_sr, (SR_OV | SR_CY));            // 0.0
/*240 */                 tcg_gen_andi_i32(sr_ove, cpu_sr, SR_OVE);                    // 0.0
/*242 */                 tcg_gen_brcondi_i32(TCG_COND_NE, sr_ove, SR_OVE, lab);       // 0.0
/*244 */                 gen_exception(dc, EXCP_RANGE);                               // 0.0
/*246 */                 gen_set_label(lab);                                          // 0.0
/*248 */                 tcg_gen_mov_i32(cpu_R[rd], res);                             // 0.0
/*250 */                 tcg_temp_free_i64(ta);                                       // 0.0
/*252 */                 tcg_temp_free_i64(tb);                                       // 0.0
/*254 */                 tcg_temp_free_i64(td);                                       // 0.0
/*256 */                 tcg_temp_free_i32(res);                                      // 0.0
/*258 */                 tcg_temp_free_i32(sr_ove);                                   // 0.0
/*260 */             }                                                                // 0.0
/*262 */             break;                                                           // 0.0
/*264 */         default:                                                             // 0.0
/*266 */             gen_illegal_exception(dc);                                       // 0.0
/*268 */             break;                                                           // 0.0
/*270 */         }                                                                    // 0.0
/*272 */         break;                                                               // 0.0
/*276 */     case 0x0003:    /* l.and */                                              // 0.0
/*278 */         switch (op1) {                                                       // 0.0
/*280 */         case 0x00:                                                           // 0.0
/*282 */             LOG_DIS("l.and r%d, r%d, r%d\n", rd, ra, rb);                    // 0.0
/*284 */             tcg_gen_and_tl(cpu_R[rd], cpu_R[ra], cpu_R[rb]);                 // 0.0
/*286 */             break;                                                           // 0.0
/*288 */         default:                                                             // 0.0
/*290 */             gen_illegal_exception(dc);                                       // 0.0
/*292 */             break;                                                           // 0.0
/*294 */         }                                                                    // 0.0
/*296 */         break;                                                               // 0.0
/*300 */     case 0x0004:    /* l.or */                                               // 0.0
/*302 */         switch (op1) {                                                       // 0.0
/*304 */         case 0x00:                                                           // 0.0
/*306 */             LOG_DIS("l.or r%d, r%d, r%d\n", rd, ra, rb);                     // 0.0
/*308 */             tcg_gen_or_tl(cpu_R[rd], cpu_R[ra], cpu_R[rb]);                  // 0.0
/*310 */             break;                                                           // 0.0
/*312 */         default:                                                             // 0.0
/*314 */             gen_illegal_exception(dc);                                       // 0.0
/*316 */             break;                                                           // 0.0
/*318 */         }                                                                    // 0.0
/*320 */         break;                                                               // 0.0
/*324 */     case 0x0005:                                                             // 0.0
/*326 */         switch (op1) {                                                       // 0.0
/*328 */         case 0x00:    /* l.xor */                                            // 0.0
/*330 */             LOG_DIS("l.xor r%d, r%d, r%d\n", rd, ra, rb);                    // 0.0
/*332 */             tcg_gen_xor_tl(cpu_R[rd], cpu_R[ra], cpu_R[rb]);                 // 0.0
/*334 */             break;                                                           // 0.0
/*336 */         default:                                                             // 0.0
/*338 */             gen_illegal_exception(dc);                                       // 0.0
/*340 */             break;                                                           // 0.0
/*342 */         }                                                                    // 0.0
/*344 */         break;                                                               // 0.0
/*348 */     case 0x0006:                                                             // 0.0
/*350 */         switch (op1) {                                                       // 0.0
/*352 */         case 0x03:    /* l.mul */                                            // 0.0
/*354 */             LOG_DIS("l.mul r%d, r%d, r%d\n", rd, ra, rb);                    // 0.0
/*356 */             if (ra != 0 && rb != 0) {                                        // 0.0
/*358 */                 gen_helper_mul32(cpu_R[rd], cpu_env, cpu_R[ra], cpu_R[rb]);  // 0.0
/*360 */             } else {                                                         // 0.0
/*362 */                 tcg_gen_movi_tl(cpu_R[rd], 0x0);                             // 0.0
/*364 */             }                                                                // 0.0
/*366 */             break;                                                           // 0.0
/*368 */         default:                                                             // 0.0
/*370 */             gen_illegal_exception(dc);                                       // 0.0
/*372 */             break;                                                           // 0.0
/*374 */         }                                                                    // 0.0
/*376 */         break;                                                               // 0.0
/*380 */     case 0x0009:                                                             // 0.0
/*382 */         switch (op1) {                                                       // 0.0
/*384 */         case 0x03:    /* l.div */                                            // 0.0
/*386 */             LOG_DIS("l.div r%d, r%d, r%d\n", rd, ra, rb);                    // 0.0
/*388 */             {                                                                // 0.0
/*390 */                 int lab0 = gen_new_label();                                  // 0.0
/*392 */                 int lab1 = gen_new_label();                                  // 0.0
/*394 */                 int lab2 = gen_new_label();                                  // 0.0
/*396 */                 int lab3 = gen_new_label();                                  // 0.0
/*398 */                 TCGv_i32 sr_ove = tcg_temp_local_new_i32();                  // 0.0
/*400 */                 if (rb == 0) {                                               // 0.0
/*402 */                     tcg_gen_ori_tl(cpu_sr, cpu_sr, (SR_OV | SR_CY));         // 0.0
/*404 */                     tcg_gen_andi_tl(sr_ove, cpu_sr, SR_OVE);                 // 0.0
/*406 */                     tcg_gen_brcondi_tl(TCG_COND_NE, sr_ove, SR_OVE, lab0);   // 0.0
/*408 */                     gen_exception(dc, EXCP_RANGE);                           // 0.0
/*410 */                     gen_set_label(lab0);                                     // 0.0
/*412 */                 } else {                                                     // 0.0
/*414 */                     tcg_gen_brcondi_tl(TCG_COND_EQ, cpu_R[rb],               // 0.0
/*416 */                                        0x00000000, lab1);                    // 0.0
/*418 */                     tcg_gen_brcondi_tl(TCG_COND_NE, cpu_R[ra],               // 0.0
/*420 */                                        0x80000000, lab2);                    // 0.0
/*422 */                     tcg_gen_brcondi_tl(TCG_COND_NE, cpu_R[rb],               // 0.0
/*424 */                                        0xffffffff, lab2);                    // 0.0
/*426 */                     gen_set_label(lab1);                                     // 0.0
/*428 */                     tcg_gen_ori_tl(cpu_sr, cpu_sr, (SR_OV | SR_CY));         // 0.0
/*430 */                     tcg_gen_andi_tl(sr_ove, cpu_sr, SR_OVE);                 // 0.0
/*432 */                     tcg_gen_brcondi_tl(TCG_COND_NE, sr_ove, SR_OVE, lab3);   // 0.0
/*434 */                     gen_exception(dc, EXCP_RANGE);                           // 0.0
/*436 */                     gen_set_label(lab2);                                     // 0.0
/*438 */                     tcg_gen_div_tl(cpu_R[rd], cpu_R[ra], cpu_R[rb]);         // 0.0
/*440 */                     gen_set_label(lab3);                                     // 0.0
/*442 */                 }                                                            // 0.0
/*444 */                 tcg_temp_free_i32(sr_ove);                                   // 0.0
/*446 */             }                                                                // 0.0
/*448 */             break;                                                           // 0.0
/*452 */         default:                                                             // 0.0
/*454 */             gen_illegal_exception(dc);                                       // 0.0
/*456 */             break;                                                           // 0.0
/*458 */         }                                                                    // 0.0
/*460 */         break;                                                               // 0.0
/*464 */     case 0x000a:                                                             // 0.0
/*466 */         switch (op1) {                                                       // 0.0
/*468 */         case 0x03:    /* l.divu */                                           // 0.0
/*470 */             LOG_DIS("l.divu r%d, r%d, r%d\n", rd, ra, rb);                   // 0.0
/*472 */             {                                                                // 0.0
/*474 */                 int lab0 = gen_new_label();                                  // 0.0
/*476 */                 int lab1 = gen_new_label();                                  // 0.0
/*478 */                 int lab2 = gen_new_label();                                  // 0.0
/*480 */                 TCGv_i32 sr_ove = tcg_temp_local_new_i32();                  // 0.0
/*482 */                 if (rb == 0) {                                               // 0.0
/*484 */                     tcg_gen_ori_tl(cpu_sr, cpu_sr, (SR_OV | SR_CY));         // 0.0
/*486 */                     tcg_gen_andi_tl(sr_ove, cpu_sr, SR_OVE);                 // 0.0
/*488 */                     tcg_gen_brcondi_tl(TCG_COND_NE, sr_ove, SR_OVE, lab0);   // 0.0
/*490 */                     gen_exception(dc, EXCP_RANGE);                           // 0.0
/*492 */                     gen_set_label(lab0);                                     // 0.0
/*494 */                 } else {                                                     // 0.0
/*496 */                     tcg_gen_brcondi_tl(TCG_COND_NE, cpu_R[rb],               // 0.0
/*498 */                                        0x00000000, lab1);                    // 0.0
/*500 */                     tcg_gen_ori_tl(cpu_sr, cpu_sr, (SR_OV | SR_CY));         // 0.0
/*502 */                     tcg_gen_andi_tl(sr_ove, cpu_sr, SR_OVE);                 // 0.0
/*504 */                     tcg_gen_brcondi_tl(TCG_COND_NE, sr_ove, SR_OVE, lab2);   // 0.0
/*506 */                     gen_exception(dc, EXCP_RANGE);                           // 0.0
/*508 */                     gen_set_label(lab1);                                     // 0.0
/*510 */                     tcg_gen_divu_tl(cpu_R[rd], cpu_R[ra], cpu_R[rb]);        // 0.0
/*512 */                     gen_set_label(lab2);                                     // 0.0
/*514 */                 }                                                            // 0.0
/*516 */                 tcg_temp_free_i32(sr_ove);                                   // 0.0
/*518 */             }                                                                // 0.0
/*520 */             break;                                                           // 0.0
/*524 */         default:                                                             // 0.0
/*526 */             gen_illegal_exception(dc);                                       // 0.0
/*528 */             break;                                                           // 0.0
/*530 */         }                                                                    // 0.0
/*532 */         break;                                                               // 0.0
/*536 */     case 0x000b:                                                             // 0.0
/*538 */         switch (op1) {                                                       // 0.0
/*540 */         case 0x03:    /* l.mulu */                                           // 0.0
/*542 */             LOG_DIS("l.mulu r%d, r%d, r%d\n", rd, ra, rb);                   // 0.0
/*544 */             if (rb != 0 && ra != 0) {                                        // 0.0
/*546 */                 TCGv_i64 result = tcg_temp_local_new_i64();                  // 0.0
/*548 */                 TCGv_i64 tra = tcg_temp_local_new_i64();                     // 0.0
/*550 */                 TCGv_i64 trb = tcg_temp_local_new_i64();                     // 0.0
/*552 */                 TCGv_i64 high = tcg_temp_new_i64();                          // 0.0
/*554 */                 TCGv_i32 sr_ove = tcg_temp_local_new_i32();                  // 0.0
/*556 */                 int lab = gen_new_label();                                   // 0.0
/*558 */                 /* Calculate each result. */                                 // 0.0
/*560 */                 tcg_gen_extu_i32_i64(tra, cpu_R[ra]);                        // 0.0
/*562 */                 tcg_gen_extu_i32_i64(trb, cpu_R[rb]);                        // 0.0
/*564 */                 tcg_gen_mul_i64(result, tra, trb);                           // 0.0
/*566 */                 tcg_temp_free_i64(tra);                                      // 0.0
/*568 */                 tcg_temp_free_i64(trb);                                      // 0.0
/*570 */                 tcg_gen_shri_i64(high, result, TARGET_LONG_BITS);            // 0.0
/*572 */                 /* Overflow or not. */                                       // 0.0
/*574 */                 tcg_gen_brcondi_i64(TCG_COND_EQ, high, 0x00000000, lab);     // 0.0
/*576 */                 tcg_gen_ori_tl(cpu_sr, cpu_sr, (SR_OV | SR_CY));             // 0.0
/*578 */                 tcg_gen_andi_tl(sr_ove, cpu_sr, SR_OVE);                     // 0.0
/*580 */                 tcg_gen_brcondi_tl(TCG_COND_NE, sr_ove, SR_OVE, lab);        // 0.0
/*582 */                 gen_exception(dc, EXCP_RANGE);                               // 0.0
/*584 */                 gen_set_label(lab);                                          // 0.0
/*586 */                 tcg_temp_free_i64(high);                                     // 0.0
/*588 */                 tcg_gen_trunc_i64_tl(cpu_R[rd], result);                     // 0.0
/*590 */                 tcg_temp_free_i64(result);                                   // 0.0
/*592 */                 tcg_temp_free_i32(sr_ove);                                   // 0.0
/*594 */             } else {                                                         // 0.0
/*596 */                 tcg_gen_movi_tl(cpu_R[rd], 0);                               // 0.0
/*598 */             }                                                                // 0.0
/*600 */             break;                                                           // 0.0
/*604 */         default:                                                             // 0.0
/*606 */             gen_illegal_exception(dc);                                       // 0.0
/*608 */             break;                                                           // 0.0
/*610 */         }                                                                    // 0.0
/*612 */         break;                                                               // 0.0
/*616 */     case 0x000e:                                                             // 0.0
/*618 */         switch (op1) {                                                       // 0.0
/*620 */         case 0x00:    /* l.cmov */                                           // 0.0
/*622 */             LOG_DIS("l.cmov r%d, r%d, r%d\n", rd, ra, rb);                   // 0.0
/*624 */             {                                                                // 0.0
/*626 */                 int lab = gen_new_label();                                   // 0.0
/*628 */                 TCGv res = tcg_temp_local_new();                             // 0.0
/*630 */                 TCGv sr_f = tcg_temp_new();                                  // 0.0
/*632 */                 tcg_gen_andi_tl(sr_f, cpu_sr, SR_F);                         // 0.0
/*634 */                 tcg_gen_mov_tl(res, cpu_R[rb]);                              // 0.0
/*636 */                 tcg_gen_brcondi_tl(TCG_COND_NE, sr_f, SR_F, lab);            // 0.0
/*638 */                 tcg_gen_mov_tl(res, cpu_R[ra]);                              // 0.0
/*640 */                 gen_set_label(lab);                                          // 0.0
/*642 */                 tcg_gen_mov_tl(cpu_R[rd], res);                              // 0.0
/*644 */                 tcg_temp_free(sr_f);                                         // 0.0
/*646 */                 tcg_temp_free(res);                                          // 0.0
/*648 */             }                                                                // 0.0
/*650 */             break;                                                           // 0.0
/*654 */         default:                                                             // 0.0
/*656 */             gen_illegal_exception(dc);                                       // 0.0
/*658 */             break;                                                           // 0.0
/*660 */         }                                                                    // 0.0
/*662 */         break;                                                               // 0.0
/*666 */     case 0x000f:                                                             // 0.0
/*668 */         switch (op1) {                                                       // 0.0
/*670 */         case 0x00:    /* l.ff1 */                                            // 0.0
/*672 */             LOG_DIS("l.ff1 r%d, r%d, r%d\n", rd, ra, rb);                    // 0.0
/*674 */             gen_helper_ff1(cpu_R[rd], cpu_R[ra]);                            // 0.0
/*676 */             break;                                                           // 0.0
/*678 */         case 0x01:    /* l.fl1 */                                            // 0.0
/*680 */             LOG_DIS("l.fl1 r%d, r%d, r%d\n", rd, ra, rb);                    // 0.0
/*682 */             gen_helper_fl1(cpu_R[rd], cpu_R[ra]);                            // 0.0
/*684 */             break;                                                           // 0.0
/*688 */         default:                                                             // 0.0
/*690 */             gen_illegal_exception(dc);                                       // 0.0
/*692 */             break;                                                           // 0.0
/*694 */         }                                                                    // 0.0
/*696 */         break;                                                               // 0.0
/*700 */     case 0x0008:                                                             // 0.0
/*702 */         switch (op1) {                                                       // 0.0
/*704 */         case 0x00:                                                           // 0.0
/*706 */             switch (op2) {                                                   // 0.0
/*708 */             case 0x00:    /* l.sll */                                        // 0.0
/*710 */                 LOG_DIS("l.sll r%d, r%d, r%d\n", rd, ra, rb);                // 0.0
/*712 */                 tcg_gen_shl_tl(cpu_R[rd], cpu_R[ra], cpu_R[rb]);             // 0.0
/*714 */                 break;                                                       // 0.0
/*716 */             case 0x01:    /* l.srl */                                        // 0.0
/*718 */                 LOG_DIS("l.srl r%d, r%d, r%d\n", rd, ra, rb);                // 0.0
/*720 */                 tcg_gen_shr_tl(cpu_R[rd], cpu_R[ra], cpu_R[rb]);             // 0.0
/*722 */                 break;                                                       // 0.0
/*724 */             case 0x02:    /* l.sra */                                        // 0.0
/*726 */                 LOG_DIS("l.sra r%d, r%d, r%d\n", rd, ra, rb);                // 0.0
/*728 */                 tcg_gen_sar_tl(cpu_R[rd], cpu_R[ra], cpu_R[rb]);             // 0.0
/*730 */                 break;                                                       // 0.0
/*732 */             case 0x03:    /* l.ror */                                        // 0.0
/*734 */                 LOG_DIS("l.ror r%d, r%d, r%d\n", rd, ra, rb);                // 0.0
/*736 */                 tcg_gen_rotr_tl(cpu_R[rd], cpu_R[ra], cpu_R[rb]);            // 0.0
/*738 */                 break;                                                       // 0.0
/*742 */             default:                                                         // 0.0
/*744 */                 gen_illegal_exception(dc);                                   // 0.0
/*746 */                 break;                                                       // 0.0
/*748 */             }                                                                // 0.0
/*750 */             break;                                                           // 0.0
/*754 */         default:                                                             // 0.0
/*756 */             gen_illegal_exception(dc);                                       // 0.0
/*758 */             break;                                                           // 0.0
/*760 */         }                                                                    // 0.0
/*762 */         break;                                                               // 0.0
/*766 */     case 0x000c:                                                             // 0.0
/*768 */         switch (op1) {                                                       // 0.0
/*770 */         case 0x00:                                                           // 0.0
/*772 */             switch (op2) {                                                   // 0.0
/*774 */             case 0x00:    /* l.exths */                                      // 0.0
/*776 */                 LOG_DIS("l.exths r%d, r%d\n", rd, ra);                       // 0.0
/*778 */                 tcg_gen_ext16s_tl(cpu_R[rd], cpu_R[ra]);                     // 0.0
/*780 */                 break;                                                       // 0.0
/*782 */             case 0x01:    /* l.extbs */                                      // 0.0
/*784 */                 LOG_DIS("l.extbs r%d, r%d\n", rd, ra);                       // 0.0
/*786 */                 tcg_gen_ext8s_tl(cpu_R[rd], cpu_R[ra]);                      // 0.0
/*788 */                 break;                                                       // 0.0
/*790 */             case 0x02:    /* l.exthz */                                      // 0.0
/*792 */                 LOG_DIS("l.exthz r%d, r%d\n", rd, ra);                       // 0.0
/*794 */                 tcg_gen_ext16u_tl(cpu_R[rd], cpu_R[ra]);                     // 0.0
/*796 */                 break;                                                       // 0.0
/*798 */             case 0x03:    /* l.extbz */                                      // 0.0
/*800 */                 LOG_DIS("l.extbz r%d, r%d\n", rd, ra);                       // 0.0
/*802 */                 tcg_gen_ext8u_tl(cpu_R[rd], cpu_R[ra]);                      // 0.0
/*804 */                 break;                                                       // 0.0
/*808 */             default:                                                         // 0.0
/*810 */                 gen_illegal_exception(dc);                                   // 0.0
/*812 */                 break;                                                       // 0.0
/*814 */             }                                                                // 0.0
/*816 */             break;                                                           // 0.0
/*820 */         default:                                                             // 0.0
/*822 */             gen_illegal_exception(dc);                                       // 0.0
/*824 */             break;                                                           // 0.0
/*826 */         }                                                                    // 0.0
/*828 */         break;                                                               // 0.0
/*832 */     case 0x000d:                                                             // 0.0
/*834 */         switch (op1) {                                                       // 0.0
/*836 */         case 0x00:                                                           // 0.0
/*838 */             switch (op2) {                                                   // 0.0
/*840 */             case 0x00:    /* l.extws */                                      // 0.0
/*842 */                 LOG_DIS("l.extws r%d, r%d\n", rd, ra);                       // 0.0
/*844 */                 tcg_gen_ext32s_tl(cpu_R[rd], cpu_R[ra]);                     // 0.0
/*846 */                 break;                                                       // 0.0
/*848 */             case 0x01:    /* l.extwz */                                      // 0.0
/*850 */                 LOG_DIS("l.extwz r%d, r%d\n", rd, ra);                       // 0.0
/*852 */                 tcg_gen_ext32u_tl(cpu_R[rd], cpu_R[ra]);                     // 0.0
/*854 */                 break;                                                       // 0.0
/*858 */             default:                                                         // 0.0
/*860 */                 gen_illegal_exception(dc);                                   // 0.0
/*862 */                 break;                                                       // 0.0
/*864 */             }                                                                // 0.0
/*866 */             break;                                                           // 0.0
/*870 */         default:                                                             // 0.0
/*872 */             gen_illegal_exception(dc);                                       // 0.0
/*874 */             break;                                                           // 0.0
/*876 */         }                                                                    // 0.0
/*878 */         break;                                                               // 0.0
/*882 */     default:                                                                 // 0.0
/*884 */         gen_illegal_exception(dc);                                           // 0.0
/*886 */         break;                                                               // 0.0
/*888 */     }                                                                        // 0.0
/*890 */ }                                                                            // 0.0
