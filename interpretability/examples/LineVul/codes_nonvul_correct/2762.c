// commit message qemu@9b990ee5a3 (target=0, prob=0.24405938, correct=True): tcg: Add CPUState cflags_next_tb
/*0  */ static inline bool cpu_handle_exception(CPUState *cpu, int *ret)        // (15) 0.03711
/*2  */ {                                                                       // (26) 0.001953
/*4  */     if (cpu->exception_index >= 0) {                                    // (17) 0.0293
/*6  */         if (cpu->exception_index >= EXCP_INTERRUPT) {                   // (3) 0.04883
/*8  */             /* exit request from the cpu execution loop */              // (12) 0.03906
/*10 */             *ret = cpu->exception_index;                                // (8) 0.04102
/*12 */             if (*ret == EXCP_DEBUG) {                                   // (7) 0.04102
/*14 */                 cpu_handle_debug_exception(cpu);                        // (2) 0.05078
/*16 */             }                                                           // (20) 0.02344
/*18 */             cpu->exception_index = -1;                                  // (9) 0.04102
/*20 */             return true;                                                // (19) 0.02734
/*22 */         } else {                                                        // (23) 0.01953
/*24 */ #if defined(CONFIG_USER_ONLY)                                           // (21) 0.02344
/*26 */             /* if user mode only, we simulate a fake exception          // (6) 0.04297
/*28 */                which will be handled outside the cpu execution          // (5) 0.04297
/*30 */                loop */                                                  // (16) 0.03125
/*32 */ #if defined(TARGET_I386)                                                // (22) 0.01953
/*34 */             CPUClass *cc = CPU_GET_CLASS(cpu);                          // (4) 0.04688
/*36 */             cc->do_interrupt(cpu);                                      // (13) 0.03906
/*38 */ #endif                                                                  // (25) 0.003906
/*40 */             *ret = cpu->exception_index;                                // (10) 0.04102
/*42 */             cpu->exception_index = -1;                                  // (11) 0.04102
/*44 */             return true;                                                // (18) 0.02734
/*46 */ #else                                                                   // (24) 0.003906
/*48 */             if (replay_exception()) {                                   // (14) 0.03906
/*50 */                 CPUClass *cc = CPU_GET_CLASS(cpu);                      // (1) 0.05469
/*52 */                 qemu_mutex_lock_iothread();                             // (0) 0.05469
/*54 */                 cc->do_interrupt(cpu);                                  // 0.0
/*56 */                 qemu_mutex_unlock_iothread();                           // 0.0
/*58 */                 cpu->exception_index = -1;                              // 0.0
/*60 */             } else if (!replay_has_interrupt()) {                       // 0.0
/*62 */                 /* give a chance to iothread in replay mode */          // 0.0
/*64 */                 *ret = EXCP_INTERRUPT;                                  // 0.0
/*66 */                 return true;                                            // 0.0
/*68 */             }                                                           // 0.0
/*70 */ #endif                                                                  // 0.0
/*72 */         }                                                               // 0.0
/*74 */ #ifndef CONFIG_USER_ONLY                                                // 0.0
/*76 */     } else if (replay_has_exception()                                   // 0.0
/*78 */                && cpu->icount_decr.u16.low + cpu->icount_extra == 0) {  // 0.0
/*80 */         /* try to cause an exception pending in the log */              // 0.0
/*82 */         cpu_exec_nocache(cpu, 1, tb_find(cpu, NULL, 0), true);          // 0.0
/*84 */         *ret = -1;                                                      // 0.0
/*86 */         return true;                                                    // 0.0
/*88 */ #endif                                                                  // 0.0
/*90 */     }                                                                   // 0.0
/*94 */     return false;                                                       // 0.0
/*96 */ }                                                                       // 0.0
