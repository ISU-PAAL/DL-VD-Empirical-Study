// commit message qemu@2af3da9183 (target=0, prob=0.13835002, correct=True): target-xtensa: add special and user registers
/*0  */ void cpu_dump_state(CPUState *env, FILE *f, fprintf_function cpu_fprintf,  // (2) 0.1479
/*2  */         int flags)                                                         // (5) 0.05917
/*4  */ {                                                                          // (8) 0.005917
/*6  */     int i;                                                                 // (6) 0.0355
/*10 */     cpu_fprintf(f, "PC=%08x\n", env->pc);                                  // (3) 0.1361
/*14 */     for (i = 0; i < 16; ++i) {                                             // (4) 0.1006
/*16 */         cpu_fprintf(f, "A%02d=%08x%c", i, env->regs[i],                    // (0) 0.2071
/*18 */                 (i % 4) == 3 ? '\n' : ' ');                                // (1) 0.1834
/*20 */     }                                                                      // (7) 0.02367
/*22 */ }                                                                          // (9) 0.005917
