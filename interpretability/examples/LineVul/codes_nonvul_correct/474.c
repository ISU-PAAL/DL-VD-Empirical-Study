// commit message qemu@932e71cd57 (target=0, prob=0.18322319, correct=True): target-mips: get rid of tests on env->user_mode_only
/*0  */ static void fpu_init (CPUMIPSState *env, const mips_def_t *def)        // (6) 0.08824
/*2  */ {                                                                      // (13) 0.003676
/*4  */     int i;                                                             // (10) 0.02206
/*8  */     for (i = 0; i < MIPS_FPU_MAX; i++)                                 // (7) 0.07721
/*10 */         env->fpus[i].fcr0 = def->CP1_fcr0;                             // (2) 0.09926
/*14 */     memcpy(&env->active_fpu, &env->fpus[0], sizeof(env->active_fpu));  // (0) 0.114
/*16 */     if (env->user_mode_only) {                                         // (8) 0.05147
/*18 */         if (env->CP0_Config1 & (1 << CP0C1_FP))                        // (3) 0.09926
/*20 */             env->hflags |= MIPS_HFLAG_FPU;                             // (4) 0.09559
/*22 */ #ifdef TARGET_MIPS64                                                   // (9) 0.03309
/*24 */         if (env->active_fpu.fcr0 & (1 << FCR0_F64))                    // (1) 0.1103
/*26 */             env->hflags |= MIPS_HFLAG_F64;                             // (5) 0.09559
/*28 */ #endif                                                                 // (12) 0.007353
/*30 */     }                                                                  // (11) 0.01471
/*32 */ }                                                                      // (14) 0.003676
