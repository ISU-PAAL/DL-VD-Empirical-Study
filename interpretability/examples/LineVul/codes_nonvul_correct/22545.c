// commit message qemu@6e0d8677cb (target=0, prob=0.0057051554, correct=True): converted string OPs and LOOP insns to TCG
/*0  */ static inline void gen_op_addl_ESP_im(int32_t val)                      // (4) 0.1207
/*2  */ {                                                                       // (7) 0.005747
/*4  */     tcg_gen_ld_tl(cpu_tmp0, cpu_env, offsetof(CPUState, regs[R_ESP]));  // (0) 0.2069
/*6  */     tcg_gen_addi_tl(cpu_tmp0, cpu_tmp0, val);                           // (3) 0.1437
/*8  */ #ifdef TARGET_X86_64                                                    // (5) 0.05747
/*10 */     tcg_gen_andi_tl(cpu_tmp0, cpu_tmp0, 0xffffffff);                    // (2) 0.1552
/*12 */ #endif                                                                  // (6) 0.01149
/*14 */     tcg_gen_st_tl(cpu_tmp0, cpu_env, offsetof(CPUState, regs[R_ESP]));  // (1) 0.2069
/*16 */ }                                                                       // (8) 0.005747
