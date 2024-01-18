// commit message qemu@601b9a9008 (target=0, prob=0.033613198, correct=True): target-s390x: Mask the SIGP order_code to 8bit.
/*0  */ uint32_t HELPER(sigp)(CPUS390XState *env, uint64_t order_code, uint32_t r1,  // (0) 0.06641
/*2  */                       uint64_t cpu_addr)                                     // (3) 0.05664
/*4  */ {                                                                            // (27) 0.001953
/*6  */     int cc = SIGP_CC_ORDER_CODE_ACCEPTED;                                    // (8) 0.04102
/*10 */     HELPER_LOG("%s: %016" PRIx64 " %08x %016" PRIx64 "\n",                   // (1) 0.0625
/*12 */                __func__, order_code, r1, cpu_addr);                          // (2) 0.05664
/*16 */     /* Remember: Use "R1 or R1 + 1, whichever is the odd-numbered register"  // (5) 0.04687
/*18 */        as parameter (input). Status (output) is always R1. */                // (7) 0.04102
/*22 */     switch (order_code) {                                                    // (22) 0.01953
/*24 */     case SIGP_SET_ARCH:                                                      // (16) 0.02148
/*26 */         /* switch arch */                                                    // (17) 0.02148
/*28 */         break;                                                               // (25) 0.01758
/*30 */     case SIGP_SENSE:                                                         // (21) 0.01953
/*32 */         /* enumerate CPU status */                                           // (15) 0.02539
/*34 */         if (cpu_addr) {                                                      // (13) 0.02734
/*36 */             /* XXX implement when SMP comes */                               // (9) 0.03711
/*38 */             return 3;                                                        // (12) 0.02734
/*40 */         }                                                                    // (26) 0.01562
/*42 */         env->regs[r1] &= 0xffffffff00000000ULL;                              // (6) 0.04687
/*44 */         cc = 1;                                                              // (19) 0.02148
/*46 */         break;                                                               // (24) 0.01758
/*48 */ #if !defined(CONFIG_USER_ONLY)                                               // (14) 0.02539
/*50 */     case SIGP_RESTART:                                                       // (18) 0.02148
/*52 */         qemu_system_reset_request();                                         // (11) 0.0332
/*54 */         cpu_loop_exit(CPU(s390_env_get_cpu(env)));                           // (4) 0.05273
/*56 */         break;                                                               // (23) 0.01758
/*58 */     case SIGP_STOP:                                                          // (20) 0.01953
/*60 */         qemu_system_shutdown_request();                                      // (10) 0.03516
/*62 */         cpu_loop_exit(CPU(s390_env_get_cpu(env)));                           // 0.0
/*64 */         break;                                                               // 0.0
/*66 */ #endif                                                                       // 0.0
/*68 */     default:                                                                 // 0.0
/*70 */         /* unknown sigp */                                                   // 0.0
/*72 */         fprintf(stderr, "XXX unknown sigp: 0x%" PRIx64 "\n", order_code);    // 0.0
/*74 */         cc = SIGP_CC_NOT_OPERATIONAL;                                        // 0.0
/*76 */     }                                                                        // 0.0
/*80 */     return cc;                                                               // 0.0
/*82 */ }                                                                            // 0.0
