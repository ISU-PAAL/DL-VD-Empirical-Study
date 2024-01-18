// commit message qemu@9c605cb135 (target=0, prob=0.2166042, correct=True): added cmpxchg8b, cpuid, bound, eflags support, vm86 mode, 16bit/override string ops
/*0  */ CPUX86State *cpu_x86_init(void)           // (4) 0.05405
/*2  */ {                                         // (21) 0.003861
/*4  */     CPUX86State *env;                     // (10) 0.03861
/*6  */     int i;                                // (19) 0.02317
/*8  */     static int inited;                    // (15) 0.03089
/*12 */     cpu_x86_tblocks_init();               // (5) 0.05019
/*16 */     env = malloc(sizeof(CPUX86State));    // (2) 0.06178
/*18 */     if (!env)                             // (16) 0.02703
/*20 */         return NULL;                      // (11) 0.03861
/*22 */     memset(env, 0, sizeof(CPUX86State));  // (1) 0.06564
/*24 */     /* basic FPU init */                  // (13) 0.03475
/*26 */     for(i = 0;i < 8; i++)                 // (3) 0.05792
/*28 */         env->fptags[i] = 1;               // (0) 0.0695
/*30 */     env->fpuc = 0x37f;                    // (6) 0.05019
/*32 */     /* flags setup */                     // (17) 0.02703
/*34 */     env->eflags = 0;                      // (9) 0.04247
/*38 */     /* init various static tables */      // (12) 0.03475
/*40 */     if (!inited) {                        // (14) 0.03475
/*42 */         inited = 1;                       // (8) 0.04633
/*44 */         optimize_flags_init();            // (7) 0.05019
/*46 */     }                                     // (20) 0.01544
/*48 */     return env;                           // (18) 0.02317
/*50 */ }                                         // (22) 0.003861
