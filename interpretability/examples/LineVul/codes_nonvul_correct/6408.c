// commit message qemu@6476615d38 (target=0, prob=0.010489091, correct=True): target/s390x: check CF_PARALLEL instead of parallel_cpus
/*0  */ void HELPER(stpq)(CPUS390XState *env, uint64_t addr,                     // (7) 0.06395
/*2  */                   uint64_t low, uint64_t high)                           // (2) 0.0843
/*4  */ {                                                                        // (17) 0.002907
/*6  */     uintptr_t ra = GETPC();                                              // (11) 0.03488
/*10 */     if (parallel_cpus) {                                                 // (10) 0.03488
/*12 */ #ifndef CONFIG_ATOMIC128                                                 // (12) 0.02907
/*14 */         cpu_loop_exit_atomic(ENV_GET_CPU(env), ra);                      // (3) 0.07558
/*16 */ #else                                                                    // (15) 0.005814
/*18 */         int mem_idx = cpu_mmu_index(env, false);                         // (6) 0.06977
/*20 */         TCGMemOpIdx oi = make_memop_idx(MO_TEQ | MO_ALIGN_16, mem_idx);  // (0) 0.1192
/*24 */         Int128 v = int128_make128(low, high);                            // (8) 0.06105
/*26 */         helper_atomic_sto_be_mmu(env, addr, v, oi, ra);                  // (1) 0.08721
/*28 */ #endif                                                                   // (16) 0.005814
/*30 */     } else {                                                             // (13) 0.01744
/*32 */         check_alignment(env, addr, 16, ra);                              // (9) 0.05814
/*36 */         cpu_stq_data_ra(env, addr + 0, high, ra);                        // (4) 0.07558
/*38 */         cpu_stq_data_ra(env, addr + 8, low, ra);                         // (5) 0.07558
/*40 */     }                                                                    // (14) 0.01163
/*42 */ }                                                                        // (18) 0.002907
