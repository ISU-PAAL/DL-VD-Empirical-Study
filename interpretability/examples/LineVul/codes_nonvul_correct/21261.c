// commit message qemu@1e39d97af0 (target=0, prob=0.21167399, correct=True): target/i386: Use generic DISAS_* enumerators
/*0  */ static void gen_movl_seg_T0(DisasContext *s, int seg_reg)                    // (4) 0.07202
/*2  */ {                                                                            // (15) 0.00277
/*4  */     if (s->pe && !s->vm86) {                                                 // (12) 0.04432
/*6  */         tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_T0);                          // (1) 0.09141
/*8  */         gen_helper_load_seg(cpu_env, tcg_const_i32(seg_reg), cpu_tmp2_i32);  // (0) 0.1163
/*10 */         /* abort translation because the addseg value may change or          // (9) 0.05263
/*12 */            because ss32 may change. For R_SS, translation must always        // (7) 0.06648
/*14 */            stop as a special handling must be done to disable hardware       // (8) 0.05817
/*16 */            interrupts for the next instruction */                            // (11) 0.04432
/*18 */         if (seg_reg == R_SS || (s->code32 && seg_reg < R_FS))                // (2) 0.09141
/*20 */             s->is_jmp = DISAS_TB_JUMP;                                       // (5) 0.07202
/*22 */     } else {                                                                 // (13) 0.01662
/*24 */         gen_op_movl_seg_T0_vm(seg_reg);                                      // (3) 0.07756
/*26 */         if (seg_reg == R_SS)                                                 // (10) 0.04986
/*28 */             s->is_jmp = DISAS_TB_JUMP;                                       // (6) 0.07202
/*30 */     }                                                                        // (14) 0.01108
/*32 */ }                                                                            // (16) 0.00277
