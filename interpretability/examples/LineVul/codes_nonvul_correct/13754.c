// commit message qemu@7d6250e3d1 (target=0, prob=0.4863166, correct=True): target/ppc: SDR1 is a hypervisor resource
/*0  */ void helper_store_sdr1(CPUPPCState *env, target_ulong val)  // (2) 0.1438
/*2  */ {                                                           // (8) 0.006536
/*4  */     PowerPCCPU *cpu = ppc_env_get_cpu(env);                 // (3) 0.1373
/*8  */     if (!env->external_htab) {                              // (5) 0.08497
/*10 */         if (env->spr[SPR_SDR1] != val) {                    // (1) 0.1569
/*12 */             ppc_store_sdr1(env, val);                       // (0) 0.1569
/*14 */             tlb_flush(CPU(cpu));                            // (4) 0.1307
/*16 */         }                                                   // (6) 0.05229
/*18 */     }                                                       // (7) 0.02614
/*20 */ }                                                           // (9) 0.006536
