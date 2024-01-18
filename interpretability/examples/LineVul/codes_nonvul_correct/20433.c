// commit message qemu@72cf2d4f0e (target=0, prob=0.011469105, correct=True): Fix sys-queue.h conflict for good
/*0  */ static void breakpoint_handler(CPUState *env)        // (15) 0.0281
/*2  */ {                                                    // (22) 0.002342
/*4  */     CPUBreakpoint *bp;                               // (18) 0.02108
/*8  */     if (env->watchpoint_hit) {                       // (14) 0.03044
/*10 */         if (env->watchpoint_hit->flags & BP_CPU) {   // (7) 0.05386
/*12 */             env->watchpoint_hit = NULL;              // (9) 0.04684
/*14 */             if (check_hw_breakpoints(env, 0))        // (5) 0.05621
/*16 */                 raise_exception(EXCP01_DB);          // (3) 0.06089
/*18 */             else                                     // (16) 0.0281
/*20 */                 cpu_resume_from_signal(env, NULL);   // (2) 0.06792
/*22 */         }                                            // (19) 0.01874
/*24 */     } else {                                         // (20) 0.01405
/*26 */         TAILQ_FOREACH(bp, &env->breakpoints, entry)  // (6) 0.05621
/*28 */             if (bp->pc == env->eip) {                // (8) 0.05386
/*30 */                 if (bp->flags & BP_CPU) {            // (4) 0.06089
/*32 */                     check_hw_breakpoints(env, 1);    // (0) 0.07026
/*34 */                     raise_exception(EXCP01_DB);      // (1) 0.07026
/*36 */                 }                                    // (12) 0.03747
/*38 */                 break;                               // (11) 0.03981
/*40 */             }                                        // (17) 0.0281
/*42 */     }                                                // (21) 0.009368
/*44 */     if (prev_debug_excp_handler)                     // (13) 0.03279
/*46 */         prev_debug_excp_handler(env);                // (10) 0.04215
/*48 */ }                                                    // (23) 0.002342
