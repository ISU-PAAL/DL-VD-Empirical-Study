// commit message qemu@210b580b10 (target=0, prob=0.039501857, correct=True): spapr-rtas: add CPU argument to RTAS calls
/*0  */ static void rtas_start_cpu(sPAPREnvironment *spapr,                    // (5) 0.04102
/*2  */                            uint32_t token, uint32_t nargs,             // (1) 0.07617
/*4  */                            target_ulong args,                          // (2) 0.0625
/*6  */                            uint32_t nret, target_ulong rets)           // (0) 0.07813
/*8  */ {                                                                      // (25) 0.001953
/*10 */     target_ulong id, start, r3;                                        // (17) 0.02734
/*12 */     CPUState *cs;                                                      // (22) 0.01562
/*16 */     if (nargs != 3 || nret != 1) {                                     // (11) 0.03125
/*18 */         rtas_st(rets, 0, -3);                                          // (7) 0.03906
/*20 */         return;                                                        // (21) 0.01758
/*22 */     }                                                                  // (24) 0.007812
/*26 */     id = rtas_ld(args, 0);                                             // (15) 0.0293
/*28 */     start = rtas_ld(args, 1);                                          // (16) 0.0293
/*30 */     r3 = rtas_ld(args, 2);                                             // (12) 0.03125
/*34 */     cs = qemu_get_cpu(id);                                             // (13) 0.0293
/*36 */     if (cs != NULL) {                                                  // (20) 0.01953
/*38 */         PowerPCCPU *cpu = POWERPC_CPU(cs);                             // (6) 0.04102
/*40 */         CPUPPCState *env = &cpu->env;                                  // (10) 0.03711
/*44 */         if (!cs->halted) {                                             // (14) 0.0293
/*46 */             rtas_st(rets, 0, -1);                                      // (4) 0.04688
/*48 */             return;                                                    // (19) 0.02539
/*50 */         }                                                              // (23) 0.01562
/*54 */         /* This will make sure qemu state is up to date with kvm, and  // (3) 0.04883
/*56 */          * mark it dirty so our changes get flushed back before the    // (9) 0.03906
/*58 */          * new cpu enters */                                           // (18) 0.02539
/*60 */         kvm_cpu_synchronize_state(cs);                                 // (8) 0.03906
/*64 */         env->msr = (1ULL << MSR_SF) | (1ULL << MSR_ME);                // 0.0
/*66 */         env->nip = start;                                              // 0.0
/*68 */         env->gpr[3] = r3;                                              // 0.0
/*70 */         cs->halted = 0;                                                // 0.0
/*74 */         qemu_cpu_kick(cs);                                             // 0.0
/*78 */         rtas_st(rets, 0, 0);                                           // 0.0
/*80 */         return;                                                        // 0.0
/*82 */     }                                                                  // 0.0
/*86 */     /* Didn't find a matching cpu */                                   // 0.0
/*88 */     rtas_st(rets, 0, -3);                                              // 0.0
/*90 */ }                                                                      // 0.0
