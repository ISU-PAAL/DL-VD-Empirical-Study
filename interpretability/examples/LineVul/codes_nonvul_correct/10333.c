// commit message qemu@bd79255d25 (target=0, prob=0.31202382, correct=True): translate: check cflags instead of use_icount global
/*0  */ static inline void gen_outs(DisasContext *s, TCGMemOp ot)  // (6) 0.06271
/*2  */ {                                                          // (13) 0.0033
/*4  */     if (use_icount)                                        // (11) 0.033
/*6  */         gen_io_start();                                    // (9) 0.0429
/*8  */     gen_string_movl_A0_ESI(s);                             // (8) 0.06271
/*10 */     gen_op_ld_v(s, ot, cpu_T[0], cpu_A0);                  // (4) 0.08581
/*14 */     tcg_gen_trunc_tl_i32(cpu_tmp2_i32, cpu_regs[R_EDX]);   // (0) 0.1122
/*16 */     tcg_gen_andi_i32(cpu_tmp2_i32, cpu_tmp2_i32, 0xffff);  // (1) 0.1089
/*18 */     tcg_gen_trunc_tl_i32(cpu_tmp3_i32, cpu_T[0]);          // (3) 0.09901
/*20 */     gen_helper_out_func(ot, cpu_tmp2_i32, cpu_tmp3_i32);   // (2) 0.09901
/*24 */     gen_op_movl_T0_Dshift(ot);                             // (7) 0.06271
/*26 */     gen_op_add_reg_T0(s->aflag, R_ESI);                    // (5) 0.07921
/*28 */     if (use_icount)                                        // (12) 0.033
/*30 */         gen_io_end();                                      // (10) 0.0429
/*32 */ }                                                          // (14) 0.0033
