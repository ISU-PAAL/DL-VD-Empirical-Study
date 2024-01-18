// commit message qemu@09b9418c6d (target=1, prob=0.6449738, correct=True): monitor: Don't check for mon_get_cpu() failure
/*0  */ static int get_monitor_def(target_long *pval, const char *name)  // (15) 0.03906
/*2  */ {                                                                // (22) 0.001953
/*4  */     const MonitorDef *md;                                        // (20) 0.01758
/*6  */     void *ptr;                                                   // (21) 0.01367
/*10 */     for(md = monitor_defs; md->name != NULL; md++) {             // (9) 0.04102
/*12 */         if (compare_cmd(name, md->name)) {                       // (8) 0.04102
/*14 */             if (md->get_value) {                                 // (16) 0.03906
/*16 */                 *pval = md->get_value(md, md->offset);           // (2) 0.06055
/*18 */             } else {                                             // (19) 0.02734
/*20 */                 CPUState *env = mon_get_cpu();                   // (4) 0.05078
/*22 */                 if (!env)                                        // (17) 0.03711
/*24 */                     return -2;                                   // (6) 0.04492
/*26 */                 ptr = (uint8_t *)env + md->offset;               // (3) 0.05664
/*28 */                 switch(md->type) {                               // (7) 0.04297
/*30 */                 case MD_I32:                                     // (10) 0.04102
/*32 */                     *pval = *(int32_t *)ptr;                     // (0) 0.0625
/*34 */                     break;                                       // (11) 0.04102
/*36 */                 case MD_TLONG:                                   // (12) 0.04102
/*38 */                     *pval = *(target_long *)ptr;                 // (1) 0.06055
/*40 */                     break;                                       // (13) 0.04102
/*42 */                 default:                                         // (18) 0.0332
/*44 */                     *pval = 0;                                   // (5) 0.04883
/*46 */                     break;                                       // (14) 0.04102
/*48 */                 }                                                // 0.0
/*50 */             }                                                    // 0.0
/*52 */             return 0;                                            // 0.0
/*54 */         }                                                        // 0.0
/*56 */     }                                                            // 0.0
/*58 */     return -1;                                                   // 0.0
/*60 */ }                                                                // 0.0
