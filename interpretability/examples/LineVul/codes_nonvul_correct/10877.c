// commit message qemu@a9321a4d49 (target=0, prob=0.0101752905, correct=True): x86: Implement SMEP and SMAP
/*0  */ void cpu_x86_update_cr4(CPUX86State *env, uint32_t new_cr4)             // (3) 0.08108
/*2  */ {                                                                       // (16) 0.003003
/*4  */ #if defined(DEBUG_MMU)                                                  // (11) 0.02703
/*6  */     printf("CR4 update: CR4=%08x\n", (uint32_t)env->cr[4]);             // (2) 0.09009
/*8  */ #endif                                                                  // (15) 0.006006
/*10 */     if ((new_cr4 & (CR4_PGE_MASK | CR4_PAE_MASK | CR4_PSE_MASK)) !=     // (1) 0.1171
/*12 */         (env->cr[4] & (CR4_PGE_MASK | CR4_PAE_MASK | CR4_PSE_MASK))) {  // (0) 0.1321
/*14 */         tlb_flush(env, 1);                                              // (9) 0.04805
/*16 */     }                                                                   // (13) 0.01201
/*18 */     /* SSE handling */                                                  // (12) 0.02402
/*20 */     if (!(env->cpuid_features & CPUID_SSE))                             // (8) 0.05706
/*22 */         new_cr4 &= ~CR4_OSFXSR_MASK;                                    // (4) 0.07207
/*24 */     if (new_cr4 & CR4_OSFXSR_MASK)                                      // (7) 0.06006
/*26 */         env->hflags |= HF_OSFXSR_MASK;                                  // (6) 0.06607
/*28 */     else                                                                // (14) 0.01201
/*30 */         env->hflags &= ~HF_OSFXSR_MASK;                                 // (5) 0.06907
/*34 */     env->cr[4] = new_cr4;                                               // (10) 0.04505
/*36 */ }                                                                       // (17) 0.003003
