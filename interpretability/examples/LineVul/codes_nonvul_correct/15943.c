// commit message qemu@b2c98d9d39 (target=0, prob=0.02364254, correct=True): tcg/s390: Expose host facilities to tcg-target.h
/*0  */ static int tcg_match_ori(TCGType type, tcg_target_long val)              // (2) 0.07029
/*2  */ {                                                                        // (19) 0.003195
/*4  */     if (facilities & FACILITY_EXT_IMM) {                                 // (7) 0.05751
/*6  */         if (type == TCG_TYPE_I32) {                                      // (5) 0.0639
/*8  */             /* All 32-bit ORs can be performed with 1 48-bit insn.  */   // (0) 0.09904
/*10 */             return 1;                                                    // (9) 0.04473
/*12 */         }                                                                // (13) 0.02556
/*14 */     }                                                                    // (17) 0.01278
/*18 */     /* Look for negative values.  These are best to load with LGHI.  */  // (4) 0.06709
/*20 */     if (val < 0) {                                                       // (12) 0.03195
/*22 */         if (val == (int16_t)val) {                                       // (6) 0.0639
/*24 */             return 0;                                                    // (10) 0.04473
/*26 */         }                                                                // (14) 0.02556
/*28 */         if (facilities & FACILITY_EXT_IMM) {                             // (3) 0.07029
/*30 */             if (val == (int32_t)val) {                                   // (1) 0.07668
/*32 */                 return 0;                                                // (8) 0.05751
/*34 */             }                                                            // (11) 0.03834
/*36 */         }                                                                // (15) 0.02556
/*38 */     }                                                                    // (18) 0.01278
/*42 */     return 1;                                                            // (16) 0.01917
/*44 */ }                                                                        // (20) 0.003195
