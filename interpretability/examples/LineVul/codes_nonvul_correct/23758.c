// commit message qemu@f9f46db444 (target=0, prob=0.035258994, correct=True): target/hppa: check CF_PARALLEL instead of parallel_cpus
/*0  */ void HELPER(stby_b)(CPUHPPAState *env, target_ulong addr, target_ulong val)  // (3) 0.07778
/*2  */ {                                                                            // (22) 0.002778
/*4  */     uintptr_t ra = GETPC();                                                  // (9) 0.03333
/*8  */     switch (addr & 3) {                                                      // (10) 0.02778
/*10 */     case 3:                                                                  // (17) 0.01667
/*12 */         cpu_stb_data_ra(env, addr, val, ra);                                 // (4) 0.06667
/*14 */         break;                                                               // (12) 0.025
/*16 */     case 2:                                                                  // (18) 0.01667
/*18 */         cpu_stw_data_ra(env, addr, val, ra);                                 // (5) 0.06667
/*20 */         break;                                                               // (13) 0.025
/*22 */     case 1:                                                                  // (19) 0.01667
/*24 */         /* The 3 byte store must appear atomic.  */                          // (7) 0.05
/*26 */         if (parallel_cpus) {                                                 // (8) 0.04444
/*28 */             atomic_store_3(env, addr, val, 0x00ffffffu, ra);                 // (0) 0.08889
/*30 */         } else {                                                             // (11) 0.02778
/*32 */             cpu_stb_data_ra(env, addr, val >> 16, ra);                       // (1) 0.08333
/*34 */             cpu_stw_data_ra(env, addr + 1, val, ra);                         // (2) 0.08333
/*36 */         }                                                                    // (16) 0.02222
/*38 */         break;                                                               // (14) 0.025
/*40 */     default:                                                                 // (20) 0.01389
/*42 */         cpu_stl_data_ra(env, addr, val, ra);                                 // (6) 0.06667
/*44 */         break;                                                               // (15) 0.025
/*46 */     }                                                                        // (21) 0.01111
/*48 */ }                                                                            // (23) 0.002778
