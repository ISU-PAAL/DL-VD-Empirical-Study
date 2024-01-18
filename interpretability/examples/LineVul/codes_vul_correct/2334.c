// commit message qemu@6658ffb81e (target=1, prob=0.9989814, correct=True): Watchpoint support (previous commit got eaten by Savannah server crash).
/*0  */ void cpu_exec_init(CPUState *env)                // (4) 0.05505
/*2  */ {                                                // (17) 0.004587
/*4  */     CPUState **penv;                             // (11) 0.04128
/*6  */     int cpu_index;                               // (14) 0.0367
/*10 */     if (!code_gen_ptr) {                         // (5) 0.05505
/*12 */         code_gen_ptr = code_gen_buffer;          // (1) 0.08716
/*14 */         page_init();                             // (6) 0.05046
/*16 */         io_mem_init();                           // (2) 0.05963
/*18 */     }                                            // (15) 0.01835
/*20 */     env->next_cpu = NULL;                        // (7) 0.05046
/*22 */     penv = &first_cpu;                           // (8) 0.05046
/*24 */     cpu_index = 0;                               // (12) 0.04128
/*26 */     while (*penv != NULL) {                      // (9) 0.05046
/*28 */         penv = (CPUState **)&(*penv)->next_cpu;  // (0) 0.1147
/*30 */         cpu_index++;                             // (10) 0.05046
/*32 */     }                                            // (16) 0.01835
/*34 */     env->cpu_index = cpu_index;                  // (3) 0.05963
/*37 */     *penv = env;                                 // (13) 0.04128
/*39 */ }                                                // (18) 0.004587
