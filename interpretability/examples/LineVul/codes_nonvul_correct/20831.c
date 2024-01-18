// commit message qemu@54ca9095f0 (target=0, prob=0.03099532, correct=True): generate GPF if non canonical addresses
/*0  */ void tlb_fill(target_ulong addr, int is_write, int is_user, void *retaddr)      // (5) 0.05579
/*2  */ {                                                                               // (27) 0.002066
/*4  */     TranslationBlock *tb;                                                       // (18) 0.0186
/*6  */     int ret;                                                                    // (25) 0.0124
/*8  */     unsigned long pc;                                                           // (24) 0.01446
/*10 */     CPUX86State *saved_env;                                                     // (12) 0.02686
/*14 */     /* XXX: hack to restore env in all cases, even if not called from           // (10) 0.03926
/*16 */        generated code */                                                        // (17) 0.0186
/*18 */     saved_env = env;                                                            // (19) 0.0186
/*20 */     env = cpu_single_env;                                                       // (16) 0.02273
/*24 */     ret = cpu_x86_handle_mmu_fault(env, addr, is_write, is_user, 1);            // (1) 0.06612
/*26 */     if (ret) {                                                                  // (21) 0.01653
/*28 */         if (retaddr) {                                                          // (13) 0.02686
/*30 */             /* now we have a real cpu fault */                                  // (8) 0.04132
/*32 */             pc = (unsigned long)retaddr;                                        // (9) 0.04132
/*34 */             tb = tb_find_pc(pc);                                                // (7) 0.04752
/*36 */             if (tb) {                                                           // (11) 0.03512
/*38 */                 /* the PC is inside the translated code. It means that we have  // (4) 0.05992
/*40 */                    a virtual CPU fault */                                       // (6) 0.04752
/*42 */                 cpu_restore_state(tb, env, pc, NULL);                           // (3) 0.06405
/*44 */             }                                                                   // (14) 0.02479
/*46 */         }                                                                       // (22) 0.01653
/*48 */         if (retaddr)                                                            // (15) 0.02479
/*50 */             raise_exception_err(EXCP0E_PAGE, env->error_code);                  // (2) 0.06612
/*52 */         else                                                                    // (23) 0.01653
/*54 */             raise_exception_err_norestore(EXCP0E_PAGE, env->error_code);        // (0) 0.07438
/*56 */     }                                                                           // (26) 0.008264
/*58 */     env = saved_env;                                                            // (20) 0.0186
/*60 */ }                                                                               // (28) 0.002066
