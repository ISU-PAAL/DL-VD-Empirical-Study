// commit message qemu@becf8217de (target=0, prob=0.019272149, correct=True): target/s390x: rework PGM interrupt psw.addr handling
/*0  */ void QEMU_NORETURN runtime_exception(CPUS390XState *env, int excp,            // (1) 0.09398
/*2  */                                      uintptr_t retaddr)                       // (0) 0.1617
/*4  */ {                                                                             // (13) 0.003759
/*6  */     CPUState *cs = CPU(s390_env_get_cpu(env));                                // (4) 0.07895
/*8  */     int t;                                                                    // (12) 0.02256
/*12 */     cs->exception_index = EXCP_PGM;                                           // (6) 0.06015
/*14 */     env->int_pgm_code = excp;                                                 // (7) 0.05639
/*18 */     /* Use the (ultimate) callers address to find the insn that trapped.  */  // (2) 0.08271
/*20 */     cpu_restore_state(cs, retaddr);                                           // (8) 0.05639
/*24 */     /* Advance past the insn.  */                                             // (9) 0.04511
/*26 */     t = cpu_ldub_code(env, env->psw.addr);                                    // (5) 0.07895
/*28 */     env->int_pgm_ilen = t = get_ilen(t);                                      // (3) 0.08271
/*30 */     env->psw.addr += t;                                                       // (10) 0.04511
/*34 */     cpu_loop_exit(cs);                                                        // (11) 0.04135
/*36 */ }                                                                             // (14) 0.003759
