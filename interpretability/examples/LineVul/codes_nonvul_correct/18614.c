// commit message qemu@cea5f9a28f (target=0, prob=0.0140043255, correct=True): cpu-exec.c: avoid AREG0 use
/*0 */ void cpu_loop_exit(CPUState *env1)  // (1) 0.2407
/*2 */ {                                   // (3) 0.01852
/*4 */     env1->current_tb = NULL;        // (2) 0.2407
/*6 */     longjmp(env1->jmp_env, 1);      // (0) 0.3148
/*8 */ }                                   // (4) 0.01852
