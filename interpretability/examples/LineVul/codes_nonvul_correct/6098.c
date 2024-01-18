// commit message qemu@ec53b45bcd (target=0, prob=0.011569858, correct=True): exec.c: Drop TARGET_HAS_ICE define and checks
/*0  */ void cpu_breakpoint_remove_by_ref(CPUState *cpu, CPUBreakpoint *breakpoint)  // (0) 0.2286
/*2  */ {                                                                            // (7) 0.009524
/*4  */ #if defined(TARGET_HAS_ICE)                                                  // (3) 0.1143
/*6  */     QTAILQ_REMOVE(&cpu->breakpoints, breakpoint, entry);                     // (1) 0.2095
/*10 */     breakpoint_invalidate(cpu, breakpoint->pc);                              // (2) 0.1619
/*14 */     g_free(breakpoint);                                                      // (4) 0.09524
/*16 */ #endif                                                                       // (5) 0.01905
/*18 */ }                                                                            // (6) 0.009524
