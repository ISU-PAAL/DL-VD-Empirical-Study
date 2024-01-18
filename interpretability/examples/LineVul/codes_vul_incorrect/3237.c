// commit message qemu@068abdc8a5 (target=1, prob=0.4045536, correct=False): Fix inconsistent end conditions in ppc_find_xxx functions.   (crash reported by Andreas Farber when using default CPU).
/*0  */ int ppc_find_by_pvr (uint32_t pvr, ppc_def_t **def)      // (1) 0.1174
/*2  */ {                                                        // (13) 0.004348
/*4  */     int i, ret;                                          // (7) 0.03478
/*8  */     ret = -1;                                            // (8) 0.03478
/*10 */     *def = NULL;                                         // (9) 0.03478
/*12 */     for (i = 0; ppc_defs[i].name != NULL; i++) {         // (3) 0.1043
/*14 */         if ((pvr & ppc_defs[i].pvr_mask) ==              // (2) 0.113
/*16 */             (ppc_defs[i].pvr & ppc_defs[i].pvr_mask)) {  // (0) 0.1609
/*18 */             *def = &ppc_defs[i];                         // (4) 0.1
/*20 */             ret = 0;                                     // (5) 0.06522
/*22 */             break;                                       // (6) 0.05652
/*24 */         }                                                // (10) 0.03478
/*26 */     }                                                    // (12) 0.01739
/*30 */     return ret;                                          // (11) 0.02609
/*32 */ }                                                        // (14) 0.004348
