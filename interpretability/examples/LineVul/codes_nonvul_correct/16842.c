// commit message qemu@83e6813a93 (target=0, prob=0.1775514, correct=True): target-arm: Switch ARMCPUInfo arrays to use terminator entries
/*0  */ static void aarch64_cpu_register_types(void)          // (3) 0.1296
/*2  */ {                                                     // (7) 0.009259
/*4  */     int i;                                            // (4) 0.05556
/*8  */     type_register_static(&aarch64_cpu_type_info);     // (2) 0.1759
/*10 */     for (i = 0; i < ARRAY_SIZE(aarch64_cpus); i++) {  // (0) 0.2407
/*12 */         aarch64_cpu_register(&aarch64_cpus[i]);       // (1) 0.2222
/*14 */     }                                                 // (5) 0.03704
/*16 */ }                                                     // (6) 0.009259
