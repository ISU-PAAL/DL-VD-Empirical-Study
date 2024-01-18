// commit message qemu@5a1972c847 (target=1, prob=0.5594795, correct=True): ppc405_uc: Fix buffer overflow
/*0  */ static uint32_t dcr_read_pob (void *opaque, int dcrn)  // (1) 0.09664
/*2  */ {                                                      // (18) 0.004202
/*4  */     ppc4xx_pob_t *pob;                                 // (2) 0.06723
/*6  */     uint32_t ret;                                      // (10) 0.03782
/*10 */     pob = opaque;                                      // (14) 0.03361
/*12 */     switch (dcrn) {                                    // (9) 0.04202
/*14 */     case POB0_BEAR:                                    // (7) 0.04622
/*16 */         ret = pob->bear;                               // (3) 0.05882
/*18 */         break;                                         // (11) 0.03782
/*20 */     case POB0_BESR0:                                   // (4) 0.05462
/*22 */     case POB0_BESR1:                                   // (5) 0.05462
/*24 */         ret = pob->besr[dcrn - POB0_BESR0];            // (0) 0.1176
/*26 */         break;                                         // (12) 0.03782
/*28 */     default:                                           // (16) 0.02101
/*30 */         /* Avoid gcc warning */                        // (6) 0.05042
/*32 */         ret = 0;                                       // (8) 0.04622
/*34 */         break;                                         // (13) 0.03782
/*36 */     }                                                  // (17) 0.01681
/*40 */     return ret;                                        // (15) 0.02521
/*42 */ }                                                      // (19) 0.004202
