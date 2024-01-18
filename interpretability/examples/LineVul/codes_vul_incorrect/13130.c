// commit message qemu@f3c75d42ad (target=1, prob=0.07319722, correct=False): target-ppc: Fix htab_mask calculation
/*0   */ static int cpu_load_old(QEMUFile *f, void *opaque, int version_id)  // (4) 0.04883
/*2   */ {                                                                   // (29) 0.001953
/*4   */     PowerPCCPU *cpu = opaque;                                       // (20) 0.02344
/*6   */     CPUPPCState *env = &cpu->env;                                   // (13) 0.0293
/*8   */     unsigned int i, j;                                              // (26) 0.01758
/*10  */     target_ulong sdr1;                                              // (22) 0.02148
/*12  */     uint32_t fpscr;                                                 // (23) 0.01953
/*14  */     target_ulong xer;                                               // (24) 0.01953
/*18  */     for (i = 0; i < 32; i++)                                        // (16) 0.0293
/*20  */         qemu_get_betls(f, &env->gpr[i]);                            // (3) 0.05078
/*22  */ #if !defined(TARGET_PPC64)                                          // (21) 0.02344
/*24  */     for (i = 0; i < 32; i++)                                        // (18) 0.0293
/*26  */         qemu_get_betls(f, &env->gprh[i]);                           // (1) 0.05273
/*28  */ #endif                                                              // (28) 0.003906
/*30  */     qemu_get_betls(f, &env->lr);                                    // (8) 0.03711
/*32  */     qemu_get_betls(f, &env->ctr);                                   // (9) 0.03711
/*34  */     for (i = 0; i < 8; i++)                                         // (14) 0.0293
/*36  */         qemu_get_be32s(f, &env->crf[i]);                            // (0) 0.05273
/*38  */     qemu_get_betls(f, &xer);                                        // (10) 0.03516
/*40  */     cpu_write_xer(env, xer);                                        // (15) 0.0293
/*42  */     qemu_get_betls(f, &env->reserve_addr);                          // (6) 0.04297
/*44  */     qemu_get_betls(f, &env->msr);                                   // (7) 0.03906
/*46  */     for (i = 0; i < 4; i++)                                         // (19) 0.0293
/*48  */         qemu_get_betls(f, &env->tgpr[i]);                           // (2) 0.05078
/*50  */     for (i = 0; i < 32; i++) {                                      // (12) 0.03125
/*52  */         union {                                                     // (27) 0.01758
/*54  */             float64 d;                                              // (17) 0.0293
/*56  */             uint64_t l;                                             // (11) 0.0332
/*58  */         } u;                                                        // (25) 0.01953
/*60  */         u.l = qemu_get_be64(f);                                     // (5) 0.04297
/*62  */         env->fpr[i] = u.d;                                          // 0.0
/*64  */     }                                                               // 0.0
/*66  */     qemu_get_be32s(f, &fpscr);                                      // 0.0
/*68  */     env->fpscr = fpscr;                                             // 0.0
/*70  */     qemu_get_sbe32s(f, &env->access_type);                          // 0.0
/*72  */ #if defined(TARGET_PPC64)                                           // 0.0
/*74  */     qemu_get_betls(f, &env->spr[SPR_ASR]);                          // 0.0
/*76  */     qemu_get_sbe32s(f, &env->slb_nr);                               // 0.0
/*78  */ #endif                                                              // 0.0
/*80  */     qemu_get_betls(f, &sdr1);                                       // 0.0
/*82  */     for (i = 0; i < 32; i++)                                        // 0.0
/*84  */         qemu_get_betls(f, &env->sr[i]);                             // 0.0
/*86  */     for (i = 0; i < 2; i++)                                         // 0.0
/*88  */         for (j = 0; j < 8; j++)                                     // 0.0
/*90  */             qemu_get_betls(f, &env->DBAT[i][j]);                    // 0.0
/*92  */     for (i = 0; i < 2; i++)                                         // 0.0
/*94  */         for (j = 0; j < 8; j++)                                     // 0.0
/*96  */             qemu_get_betls(f, &env->IBAT[i][j]);                    // 0.0
/*98  */     qemu_get_sbe32s(f, &env->nb_tlb);                               // 0.0
/*100 */     qemu_get_sbe32s(f, &env->tlb_per_way);                          // 0.0
/*102 */     qemu_get_sbe32s(f, &env->nb_ways);                              // 0.0
/*104 */     qemu_get_sbe32s(f, &env->last_way);                             // 0.0
/*106 */     qemu_get_sbe32s(f, &env->id_tlbs);                              // 0.0
/*108 */     qemu_get_sbe32s(f, &env->nb_pids);                              // 0.0
/*110 */     if (env->tlb.tlb6) {                                            // 0.0
/*112 */         // XXX assumes 6xx                                          // 0.0
/*114 */         for (i = 0; i < env->nb_tlb; i++) {                         // 0.0
/*116 */             qemu_get_betls(f, &env->tlb.tlb6[i].pte0);              // 0.0
/*118 */             qemu_get_betls(f, &env->tlb.tlb6[i].pte1);              // 0.0
/*120 */             qemu_get_betls(f, &env->tlb.tlb6[i].EPN);               // 0.0
/*122 */         }                                                           // 0.0
/*124 */     }                                                               // 0.0
/*126 */     for (i = 0; i < 4; i++)                                         // 0.0
/*128 */         qemu_get_betls(f, &env->pb[i]);                             // 0.0
/*130 */     for (i = 0; i < 1024; i++)                                      // 0.0
/*132 */         qemu_get_betls(f, &env->spr[i]);                            // 0.0
/*134 */     ppc_store_sdr1(env, sdr1);                                      // 0.0
/*136 */     qemu_get_be32s(f, &env->vscr);                                  // 0.0
/*138 */     qemu_get_be64s(f, &env->spe_acc);                               // 0.0
/*140 */     qemu_get_be32s(f, &env->spe_fscr);                              // 0.0
/*142 */     qemu_get_betls(f, &env->msr_mask);                              // 0.0
/*144 */     qemu_get_be32s(f, &env->flags);                                 // 0.0
/*146 */     qemu_get_sbe32s(f, &env->error_code);                           // 0.0
/*148 */     qemu_get_be32s(f, &env->pending_interrupts);                    // 0.0
/*150 */     qemu_get_be32s(f, &env->irq_input_state);                       // 0.0
/*152 */     for (i = 0; i < POWERPC_EXCP_NB; i++)                           // 0.0
/*154 */         qemu_get_betls(f, &env->excp_vectors[i]);                   // 0.0
/*156 */     qemu_get_betls(f, &env->excp_prefix);                           // 0.0
/*158 */     qemu_get_betls(f, &env->ivor_mask);                             // 0.0
/*160 */     qemu_get_betls(f, &env->ivpr_mask);                             // 0.0
/*162 */     qemu_get_betls(f, &env->hreset_vector);                         // 0.0
/*164 */     qemu_get_betls(f, &env->nip);                                   // 0.0
/*166 */     qemu_get_betls(f, &env->hflags);                                // 0.0
/*168 */     qemu_get_betls(f, &env->hflags_nmsr);                           // 0.0
/*170 */     qemu_get_sbe32s(f, &env->mmu_idx);                              // 0.0
/*172 */     qemu_get_sbe32(f); /* Discard unused power_mode */              // 0.0
/*176 */     return 0;                                                       // 0.0
/*178 */ }                                                                   // 0.0
