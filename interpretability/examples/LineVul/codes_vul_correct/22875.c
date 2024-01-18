// commit message qemu@4cb88c3c37 (target=1, prob=0.99904054, correct=True): s390x/kvm: enable/reset cmma via vm attributes
/*0  */ static int load_normal_reset(S390CPU *cpu)        // (3) 0.08696
/*2  */ {                                                 // (11) 0.006211
/*4  */     S390CPUClass *scc = S390_CPU_GET_CLASS(cpu);  // (0) 0.1366
/*8  */     pause_all_vcpus();                            // (6) 0.06832
/*10 */     cpu_synchronize_all_states();                 // (5) 0.08075
/*12 */     cpu_reset_all();                              // (9) 0.0559
/*15 */     io_subsystem_reset();                         // (8) 0.06211
/*17 */     scc->initial_cpu_reset(CPU(cpu));             // (1) 0.09938
/*19 */     scc->load_normal(CPU(cpu));                   // (4) 0.08696
/*21 */     cpu_synchronize_all_post_reset();             // (2) 0.09317
/*23 */     resume_all_vcpus();                           // (7) 0.06832
/*25 */     return 0;                                     // (10) 0.03727
/*27 */ }                                                 // (12) 0.006211
