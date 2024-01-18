// commit message qemu@577bf80895 (target=1, prob=0.1260745, correct=False): target-arm: Clean up DISAS_UPDATE usage in AArch32 translation code
/*0  */ static void gen_exception_return(DisasContext *s, TCGv_i32 pc)  // (0) 0.1783
/*2  */ {                                                               // (7) 0.007752
/*4  */     TCGv_i32 tmp;                                               // (6) 0.08527
/*6  */     store_reg(s, 15, pc);                                       // (5) 0.1008
/*8  */     tmp = load_cpu_field(spsr);                                 // (2) 0.1163
/*10 */     gen_set_cpsr(tmp, CPSR_ERET_MASK);                          // (1) 0.1705
/*12 */     tcg_temp_free_i32(tmp);                                     // (3) 0.1163
/*14 */     s->is_jmp = DISAS_UPDATE;                                   // (4) 0.1163
/*16 */ }                                                               // (8) 0.007752
