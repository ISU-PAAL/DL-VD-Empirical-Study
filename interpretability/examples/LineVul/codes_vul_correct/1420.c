// commit message qemu@09b9418c6d (target=1, prob=0.9808116, correct=True): monitor: Don't check for mon_get_cpu() failure
/*0  */ static target_long monitor_get_reg(const struct MonitorDef *md, int val)  // (0) 0.2632
/*2  */ {                                                                         // (5) 0.01316
/*4  */     CPUState *env = mon_get_cpu();                                        // (1) 0.1842
/*6  */     if (!env)                                                             // (4) 0.09211
/*8  */         return 0;                                                         // (3) 0.1316
/*10 */     return env->regwptr[val];                                             // (2) 0.1579
/*12 */ }                                                                         // (6) 0.01316
