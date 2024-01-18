// commit message qemu@e3e09d87c6 (target=0, prob=0.020944703, correct=True): s390x/mmu: Skip exceptions properly when translating addresses for debug
/*0  */ uint64_t HELPER(lra)(CPUS390XState *env, uint64_t addr)    // (2) 0.06452
/*2  */ {                                                          // (24) 0.002688
/*4  */     CPUState *cs = CPU(s390_env_get_cpu(env));             // (7) 0.05645
/*6  */     uint32_t cc = 0;                                       // (14) 0.02957
/*8  */     int old_exc = cs->exception_index;                     // (9) 0.04032
/*10 */     uint64_t asc = env->psw.mask & PSW_MASK_ASC;           // (3) 0.06452
/*12 */     uint64_t ret;                                          // (16) 0.02419
/*14 */     int flags;                                             // (18) 0.01613
/*18 */     /* XXX incomplete - has more corner cases */           // (12) 0.03226
/*20 */     if (!(env->psw.mask & PSW_MASK_64) && (addr >> 32)) {  // (0) 0.07527
/*22 */         program_interrupt(env, PGM_SPECIAL_OP, 2);         // (4) 0.06452
/*24 */     }                                                      // (20) 0.01075
/*28 */     cs->exception_index = old_exc;                         // (11) 0.03763
/*30 */     if (mmu_translate(env, addr, 0, asc, &ret, &flags)) {  // (1) 0.06989
/*32 */         cc = 3;                                            // (15) 0.02957
/*34 */     }                                                      // (21) 0.01075
/*36 */     if (cs->exception_index == EXCP_PGM) {                 // (8) 0.05108
/*38 */         ret = env->int_pgm_code | 0x80000000;              // (5) 0.06183
/*40 */     } else {                                               // (19) 0.01613
/*42 */         ret |= addr & ~TARGET_PAGE_MASK;                   // (6) 0.05914
/*44 */     }                                                      // (22) 0.01075
/*46 */     cs->exception_index = old_exc;                         // (10) 0.03763
/*50 */     env->cc_op = cc;                                       // (13) 0.02957
/*52 */     return ret;                                            // (17) 0.01613
/*54 */ }                                                          // (23) 0.002688
