// commit message qemu@599d64f6dc (target=1, prob=0.08417005, correct=False): target-arm: Fix potential buffer overflow
/*0  */ static int arm946_prbs_write(CPUARMState *env, const ARMCPRegInfo *ri,  // (1) 0.1955
/*2  */                              uint64_t value)                            // (0) 0.2556
/*4  */ {                                                                       // (7) 0.007519
/*6  */     if (ri->crm > 8) {                                                  // (4) 0.09774
/*8  */         return EXCP_UDEF;                                               // (3) 0.1053
/*10 */     }                                                                   // (6) 0.03008
/*12 */     env->cp15.c6_region[ri->crm] = value;                               // (2) 0.1579
/*14 */     return 0;                                                           // (5) 0.04511
/*16 */ }                                                                       // (8) 0.007519
