// commit message qemu@c0f4af1719 (target=1, prob=0.9990339, correct=True): target-arm: Don't handle c15_cpar changes via tb_flush()
/*0  */ void HELPER(access_check_cp_reg)(CPUARMState *env, void *rip, uint32_t syndrome)  // (0) 0.1591
/*1  */ {                                                                                 // (11) 0.005682
/*2  */     const ARMCPRegInfo *ri = rip;                                                 // (5) 0.07955
/*3  */     switch (ri->accessfn(env, ri)) {                                              // (3) 0.09091
/*4  */     case CP_ACCESS_OK:                                                            // (7) 0.0625
/*5  */     case CP_ACCESS_TRAP:                                                          // (6) 0.06818
/*6  */         break;                                                                    // (8) 0.05114
/*7  */     case CP_ACCESS_TRAP_UNCATEGORIZED:                                            // (2) 0.1136
/*8  */         env->exception.syndrome = syn_uncategorized();                            // (1) 0.125
/*9  */         break;                                                                    // (9) 0.05114
/*10 */     default:                                                                      // (10) 0.02841
/*11 */         g_assert_not_reached();                                                   // (4) 0.09091
