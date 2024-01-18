// commit message qemu@425532d71d (target=0, prob=0.14857961, correct=True): tcg-sparc: Tidy check_fit_* tests
/*0   */ static inline void tcg_out_op(TCGContext *s, TCGOpcode opc, const TCGArg *args,  // (8) 0.05859
/*2   */                               const int *const_args)                             // (6) 0.07031
/*4   */ {                                                                                // (19) 0.001953
/*6   */     int c;                                                                       // (18) 0.01172
/*10  */     switch (opc) {                                                               // (15) 0.01758
/*12  */     case INDEX_op_exit_tb:                                                       // (13) 0.02734
/*14  */         if (check_fit_tl(args[0], 13)) {                                         // (9) 0.04297
/*16  */             tcg_out_arithi(s, TCG_REG_G0, TCG_REG_I7, 8, RETURN);                // (1) 0.08398
/*18  */             tcg_out_movi_imm13(s, TCG_REG_O0, args[0]);                          // (5) 0.07031
/*20  */         } else {                                                                 // (14) 0.01953
/*22  */             tcg_out_movi(s, TCG_TYPE_PTR, TCG_REG_I0, args[0] & ~0x3ff);         // (0) 0.09375
/*24  */             tcg_out_arithi(s, TCG_REG_G0, TCG_REG_I7, 8, RETURN);                // (2) 0.08398
/*26  */             tcg_out_arithi(s, TCG_REG_O0, TCG_REG_O0,                            // (4) 0.07422
/*28  */                            args[0] & 0x3ff, ARITH_OR);                           // (3) 0.08008
/*30  */         }                                                                        // (17) 0.01562
/*32  */         break;                                                                   // (16) 0.01758
/*34  */     case INDEX_op_goto_tb:                                                       // (12) 0.0293
/*36  */         if (s->tb_jmp_offset) {                                                  // (10) 0.03906
/*38  */             /* direct jump method */                                             // (11) 0.03125
/*40  */             uint32_t old_insn = *(uint32_t *)s->code_ptr;                        // (7) 0.06445
/*42  */             s->tb_jmp_offset[args[0]] = s->code_ptr - s->code_buf;               // 0.0
/*44  */             /* Make sure to preserve links during retranslation.  */             // 0.0
/*46  */             tcg_out32(s, CALL | (old_insn & ~INSN_OP(-1)));                      // 0.0
/*48  */         } else {                                                                 // 0.0
/*50  */             /* indirect jump method */                                           // 0.0
/*52  */             tcg_out_ld_ptr(s, TCG_REG_T1, (uintptr_t)(s->tb_next + args[0]));    // 0.0
/*54  */             tcg_out_arithi(s, TCG_REG_G0, TCG_REG_T1, 0, JMPL);                  // 0.0
/*56  */         }                                                                        // 0.0
/*58  */         tcg_out_nop(s);                                                          // 0.0
/*60  */         s->tb_next_offset[args[0]] = s->code_ptr - s->code_buf;                  // 0.0
/*62  */         break;                                                                   // 0.0
/*64  */     case INDEX_op_call:                                                          // 0.0
/*66  */         if (const_args[0]) {                                                     // 0.0
/*68  */             tcg_out_calli(s, args[0]);                                           // 0.0
/*70  */         } else {                                                                 // 0.0
/*72  */             tcg_out_arithi(s, TCG_REG_O7, args[0], 0, JMPL);                     // 0.0
/*74  */         }                                                                        // 0.0
/*76  */         /* delay slot */                                                         // 0.0
/*78  */         tcg_out_nop(s);                                                          // 0.0
/*80  */         break;                                                                   // 0.0
/*82  */     case INDEX_op_br:                                                            // 0.0
/*84  */         tcg_out_bpcc(s, COND_A, BPCC_PT, args[0]);                               // 0.0
/*86  */         tcg_out_nop(s);                                                          // 0.0
/*88  */         break;                                                                   // 0.0
/*90  */     case INDEX_op_movi_i32:                                                      // 0.0
/*92  */         tcg_out_movi(s, TCG_TYPE_I32, args[0], (uint32_t)args[1]);               // 0.0
/*94  */         break;                                                                   // 0.0
/*98  */ #define OP_32_64(x)                             \                                // 0.0
/*100 */         glue(glue(case INDEX_op_, x), _i32):    \                                // 0.0
/*102 */         glue(glue(case INDEX_op_, x), _i64)                                      // 0.0
/*106 */     OP_32_64(ld8u):                                                              // 0.0
/*108 */         tcg_out_ldst(s, args[0], args[1], args[2], LDUB);                        // 0.0
/*110 */         break;                                                                   // 0.0
/*112 */     OP_32_64(ld8s):                                                              // 0.0
/*114 */         tcg_out_ldst(s, args[0], args[1], args[2], LDSB);                        // 0.0
/*116 */         break;                                                                   // 0.0
/*118 */     OP_32_64(ld16u):                                                             // 0.0
/*120 */         tcg_out_ldst(s, args[0], args[1], args[2], LDUH);                        // 0.0
/*122 */         break;                                                                   // 0.0
/*124 */     OP_32_64(ld16s):                                                             // 0.0
/*126 */         tcg_out_ldst(s, args[0], args[1], args[2], LDSH);                        // 0.0
/*128 */         break;                                                                   // 0.0
/*130 */     case INDEX_op_ld_i32:                                                        // 0.0
/*132 */     case INDEX_op_ld32u_i64:                                                     // 0.0
/*134 */         tcg_out_ldst(s, args[0], args[1], args[2], LDUW);                        // 0.0
/*136 */         break;                                                                   // 0.0
/*138 */     OP_32_64(st8):                                                               // 0.0
/*140 */         tcg_out_ldst(s, args[0], args[1], args[2], STB);                         // 0.0
/*142 */         break;                                                                   // 0.0
/*144 */     OP_32_64(st16):                                                              // 0.0
/*146 */         tcg_out_ldst(s, args[0], args[1], args[2], STH);                         // 0.0
/*148 */         break;                                                                   // 0.0
/*150 */     case INDEX_op_st_i32:                                                        // 0.0
/*152 */     case INDEX_op_st32_i64:                                                      // 0.0
/*154 */         tcg_out_ldst(s, args[0], args[1], args[2], STW);                         // 0.0
/*156 */         break;                                                                   // 0.0
/*158 */     OP_32_64(add):                                                               // 0.0
/*160 */         c = ARITH_ADD;                                                           // 0.0
/*162 */         goto gen_arith;                                                          // 0.0
/*164 */     OP_32_64(sub):                                                               // 0.0
/*166 */         c = ARITH_SUB;                                                           // 0.0
/*168 */         goto gen_arith;                                                          // 0.0
/*170 */     OP_32_64(and):                                                               // 0.0
/*172 */         c = ARITH_AND;                                                           // 0.0
/*174 */         goto gen_arith;                                                          // 0.0
/*176 */     OP_32_64(andc):                                                              // 0.0
/*178 */         c = ARITH_ANDN;                                                          // 0.0
/*180 */         goto gen_arith;                                                          // 0.0
/*182 */     OP_32_64(or):                                                                // 0.0
/*184 */         c = ARITH_OR;                                                            // 0.0
/*186 */         goto gen_arith;                                                          // 0.0
/*188 */     OP_32_64(orc):                                                               // 0.0
/*190 */         c = ARITH_ORN;                                                           // 0.0
/*192 */         goto gen_arith;                                                          // 0.0
/*194 */     OP_32_64(xor):                                                               // 0.0
/*196 */         c = ARITH_XOR;                                                           // 0.0
/*198 */         goto gen_arith;                                                          // 0.0
/*200 */     case INDEX_op_shl_i32:                                                       // 0.0
/*202 */         c = SHIFT_SLL;                                                           // 0.0
/*204 */     do_shift32:                                                                  // 0.0
/*206 */         /* Limit immediate shift count lest we create an illegal insn.  */       // 0.0
/*208 */         tcg_out_arithc(s, args[0], args[1], args[2] & 31, const_args[2], c);     // 0.0
/*210 */         break;                                                                   // 0.0
/*212 */     case INDEX_op_shr_i32:                                                       // 0.0
/*214 */         c = SHIFT_SRL;                                                           // 0.0
/*216 */         goto do_shift32;                                                         // 0.0
/*218 */     case INDEX_op_sar_i32:                                                       // 0.0
/*220 */         c = SHIFT_SRA;                                                           // 0.0
/*222 */         goto do_shift32;                                                         // 0.0
/*224 */     case INDEX_op_mul_i32:                                                       // 0.0
/*226 */         c = ARITH_UMUL;                                                          // 0.0
/*228 */         goto gen_arith;                                                          // 0.0
/*232 */     OP_32_64(neg):                                                               // 0.0
/*234 */ 	c = ARITH_SUB;                                                                  // 0.0
/*236 */ 	goto gen_arith1;                                                                // 0.0
/*238 */     OP_32_64(not):                                                               // 0.0
/*240 */ 	c = ARITH_ORN;                                                                  // 0.0
/*242 */ 	goto gen_arith1;                                                                // 0.0
/*246 */     case INDEX_op_div_i32:                                                       // 0.0
/*248 */         tcg_out_div32(s, args[0], args[1], args[2], const_args[2], 0);           // 0.0
/*250 */         break;                                                                   // 0.0
/*252 */     case INDEX_op_divu_i32:                                                      // 0.0
/*254 */         tcg_out_div32(s, args[0], args[1], args[2], const_args[2], 1);           // 0.0
/*256 */         break;                                                                   // 0.0
/*260 */     case INDEX_op_brcond_i32:                                                    // 0.0
/*262 */         tcg_out_brcond_i32(s, args[2], args[0], args[1], const_args[1],          // 0.0
/*264 */                            args[3]);                                             // 0.0
/*266 */         break;                                                                   // 0.0
/*268 */     case INDEX_op_setcond_i32:                                                   // 0.0
/*270 */         tcg_out_setcond_i32(s, args[3], args[0], args[1],                        // 0.0
/*272 */                             args[2], const_args[2]);                             // 0.0
/*274 */         break;                                                                   // 0.0
/*276 */     case INDEX_op_movcond_i32:                                                   // 0.0
/*278 */         tcg_out_movcond_i32(s, args[5], args[0], args[1],                        // 0.0
/*280 */                             args[2], const_args[2], args[3], const_args[3]);     // 0.0
/*282 */         break;                                                                   // 0.0
/*286 */     case INDEX_op_add2_i32:                                                      // 0.0
/*288 */         tcg_out_addsub2(s, args[0], args[1], args[2], args[3],                   // 0.0
/*290 */                         args[4], const_args[4], args[5], const_args[5],          // 0.0
/*292 */                         ARITH_ADDCC, ARITH_ADDX);                                // 0.0
/*294 */         break;                                                                   // 0.0
/*296 */     case INDEX_op_sub2_i32:                                                      // 0.0
/*298 */         tcg_out_addsub2(s, args[0], args[1], args[2], args[3],                   // 0.0
/*300 */                         args[4], const_args[4], args[5], const_args[5],          // 0.0
/*302 */                         ARITH_SUBCC, ARITH_SUBX);                                // 0.0
/*304 */         break;                                                                   // 0.0
/*306 */     case INDEX_op_mulu2_i32:                                                     // 0.0
/*308 */         c = ARITH_UMUL;                                                          // 0.0
/*310 */         goto do_mul2;                                                            // 0.0
/*312 */     case INDEX_op_muls2_i32:                                                     // 0.0
/*314 */         c = ARITH_SMUL;                                                          // 0.0
/*316 */     do_mul2:                                                                     // 0.0
/*318 */         /* The 32-bit multiply insns produce a full 64-bit result.  If the       // 0.0
/*320 */            destination register can hold it, we can avoid the slower RDY.  */    // 0.0
/*322 */         tcg_out_arithc(s, args[0], args[2], args[3], const_args[3], c);          // 0.0
/*324 */         if (SPARC64 || args[0] <= TCG_REG_O7) {                                  // 0.0
/*326 */             tcg_out_arithi(s, args[1], args[0], 32, SHIFT_SRLX);                 // 0.0
/*328 */         } else {                                                                 // 0.0
/*330 */             tcg_out_rdy(s, args[1]);                                             // 0.0
/*332 */         }                                                                        // 0.0
/*334 */         break;                                                                   // 0.0
/*338 */     case INDEX_op_qemu_ld_i32:                                                   // 0.0
/*340 */         tcg_out_qemu_ld(s, args[0], args[1], args[2], args[3], false);           // 0.0
/*342 */         break;                                                                   // 0.0
/*344 */     case INDEX_op_qemu_ld_i64:                                                   // 0.0
/*346 */         tcg_out_qemu_ld(s, args[0], args[1], args[2], args[3], true);            // 0.0
/*348 */         break;                                                                   // 0.0
/*350 */     case INDEX_op_qemu_st_i32:                                                   // 0.0
/*352 */         tcg_out_qemu_st(s, args[0], args[1], args[2], args[3]);                  // 0.0
/*354 */         break;                                                                   // 0.0
/*356 */     case INDEX_op_qemu_st_i64:                                                   // 0.0
/*358 */         tcg_out_qemu_st(s, args[0], args[1], args[2], args[3]);                  // 0.0
/*360 */         break;                                                                   // 0.0
/*364 */     case INDEX_op_movi_i64:                                                      // 0.0
/*366 */         tcg_out_movi(s, TCG_TYPE_I64, args[0], args[1]);                         // 0.0
/*368 */         break;                                                                   // 0.0
/*370 */     case INDEX_op_ld32s_i64:                                                     // 0.0
/*372 */         tcg_out_ldst(s, args[0], args[1], args[2], LDSW);                        // 0.0
/*374 */         break;                                                                   // 0.0
/*376 */     case INDEX_op_ld_i64:                                                        // 0.0
/*378 */         tcg_out_ldst(s, args[0], args[1], args[2], LDX);                         // 0.0
/*380 */         break;                                                                   // 0.0
/*382 */     case INDEX_op_st_i64:                                                        // 0.0
/*384 */         tcg_out_ldst(s, args[0], args[1], args[2], STX);                         // 0.0
/*386 */         break;                                                                   // 0.0
/*388 */     case INDEX_op_shl_i64:                                                       // 0.0
/*390 */         c = SHIFT_SLLX;                                                          // 0.0
/*392 */     do_shift64:                                                                  // 0.0
/*394 */         /* Limit immediate shift count lest we create an illegal insn.  */       // 0.0
/*396 */         tcg_out_arithc(s, args[0], args[1], args[2] & 63, const_args[2], c);     // 0.0
/*398 */         break;                                                                   // 0.0
/*400 */     case INDEX_op_shr_i64:                                                       // 0.0
/*402 */         c = SHIFT_SRLX;                                                          // 0.0
/*404 */         goto do_shift64;                                                         // 0.0
/*406 */     case INDEX_op_sar_i64:                                                       // 0.0
/*408 */         c = SHIFT_SRAX;                                                          // 0.0
/*410 */         goto do_shift64;                                                         // 0.0
/*412 */     case INDEX_op_mul_i64:                                                       // 0.0
/*414 */         c = ARITH_MULX;                                                          // 0.0
/*416 */         goto gen_arith;                                                          // 0.0
/*418 */     case INDEX_op_div_i64:                                                       // 0.0
/*420 */         c = ARITH_SDIVX;                                                         // 0.0
/*422 */         goto gen_arith;                                                          // 0.0
/*424 */     case INDEX_op_divu_i64:                                                      // 0.0
/*426 */         c = ARITH_UDIVX;                                                         // 0.0
/*428 */         goto gen_arith;                                                          // 0.0
/*430 */     case INDEX_op_ext32s_i64:                                                    // 0.0
/*432 */         tcg_out_arithi(s, args[0], args[1], 0, SHIFT_SRA);                       // 0.0
/*434 */         break;                                                                   // 0.0
/*436 */     case INDEX_op_ext32u_i64:                                                    // 0.0
/*438 */         tcg_out_arithi(s, args[0], args[1], 0, SHIFT_SRL);                       // 0.0
/*440 */         break;                                                                   // 0.0
/*442 */     case INDEX_op_trunc_shr_i32:                                                 // 0.0
/*444 */         if (args[2] == 0) {                                                      // 0.0
/*446 */             tcg_out_mov(s, TCG_TYPE_I32, args[0], args[1]);                      // 0.0
/*448 */         } else {                                                                 // 0.0
/*450 */             tcg_out_arithi(s, args[0], args[1], args[2], SHIFT_SRLX);            // 0.0
/*452 */         }                                                                        // 0.0
/*454 */         break;                                                                   // 0.0
/*458 */     case INDEX_op_brcond_i64:                                                    // 0.0
/*460 */         tcg_out_brcond_i64(s, args[2], args[0], args[1], const_args[1],          // 0.0
/*462 */                            args[3]);                                             // 0.0
/*464 */         break;                                                                   // 0.0
/*466 */     case INDEX_op_setcond_i64:                                                   // 0.0
/*468 */         tcg_out_setcond_i64(s, args[3], args[0], args[1],                        // 0.0
/*470 */                             args[2], const_args[2]);                             // 0.0
/*472 */         break;                                                                   // 0.0
/*474 */     case INDEX_op_movcond_i64:                                                   // 0.0
/*476 */         tcg_out_movcond_i64(s, args[5], args[0], args[1],                        // 0.0
/*478 */                             args[2], const_args[2], args[3], const_args[3]);     // 0.0
/*480 */         break;                                                                   // 0.0
/*484 */     gen_arith:                                                                   // 0.0
/*486 */         tcg_out_arithc(s, args[0], args[1], args[2], const_args[2], c);          // 0.0
/*488 */         break;                                                                   // 0.0
/*492 */     gen_arith1:                                                                  // 0.0
/*494 */ 	tcg_out_arithc(s, args[0], TCG_REG_G0, args[1], const_args[1], c);              // 0.0
/*496 */ 	break;                                                                          // 0.0
/*500 */     default:                                                                     // 0.0
/*502 */         fprintf(stderr, "unknown opcode 0x%x\n", opc);                           // 0.0
/*504 */         tcg_abort();                                                             // 0.0
/*506 */     }                                                                            // 0.0
/*508 */ }                                                                                // 0.0
