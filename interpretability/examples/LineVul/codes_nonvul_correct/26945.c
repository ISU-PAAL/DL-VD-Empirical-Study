// commit message qemu@7e97cd8814 (target=0, prob=0.3844356, correct=True): Refactor kvm&tcg function names in cpus.c
/*0  */ static void kvm_start_vcpu(CPUState *env)                              // (5) 0.08772
/*2  */ {                                                                      // (7) 0.005848
/*4  */     env->thread = qemu_mallocz(sizeof(QemuThread));                    // (3) 0.1345
/*6  */     env->halt_cond = qemu_mallocz(sizeof(QemuCond));                   // (2) 0.152
/*8  */     qemu_cond_init(env->halt_cond);                                    // (4) 0.1053
/*10 */     qemu_thread_create(env->thread, kvm_cpu_thread_fn, env);           // (1) 0.152
/*12 */     while (env->created == 0)                                          // (6) 0.06433
/*14 */         qemu_cond_timedwait(&qemu_cpu_cond, &qemu_global_mutex, 100);  // (0) 0.2164
/*16 */ }                                                                      // (8) 0.005848
