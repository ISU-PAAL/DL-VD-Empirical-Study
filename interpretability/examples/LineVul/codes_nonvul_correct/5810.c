// commit message qemu@40f860cd6c (target=0, prob=0.17793202, correct=True): target-arm: Split A64 from A32/T32 gen_intermediate_code_internal()
/*0  */ static void gen_exception_insn(DisasContext *s, int offset, int excp)  // (0) 0.2805
/*2  */ {                                                                      // (4) 0.0122
/*4  */     gen_a64_set_pc_im(s->pc - offset);                                 // (1) 0.2439
/*6  */     gen_exception(excp);                                               // (3) 0.1341
/*8  */     s->is_jmp = DISAS_JUMP;                                            // (2) 0.1951
/*10 */ }                                                                      // (5) 0.0122
