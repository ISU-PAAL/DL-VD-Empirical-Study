// commit message FFmpeg@a91d82b5cc (target=1, prob=0.74220455, correct=True): Move the SBR patch count check to prevent overwrites.
/*0  */ static int sbr_hf_calc_npatches(AACContext *ac, SpectralBandReplication *sbr)                                      // (5) 0.05859
/*2  */ {                                                                                                                  // (22) 0.001953
/*4  */     int i, k, sb = 0;                                                                                              // (16) 0.02539
/*6  */     int msb = sbr->k[0];                                                                                           // (14) 0.02734
/*8  */     int usb = sbr->kx[1];                                                                                          // (15) 0.02734
/*10 */     int goal_sb = ((1000 << 11) + (sbr->sample_rate >> 1)) / sbr->sample_rate;                                     // (3) 0.0625
/*14 */     sbr->num_patches = 0;                                                                                          // (17) 0.02539
/*18 */     if (goal_sb < sbr->kx[1] + sbr->m[1]) {                                                                        // (7) 0.05078
/*20 */         for (k = 0; sbr->f_master[k] < goal_sb; k++) ;                                                             // (6) 0.05859
/*22 */     } else                                                                                                         // (20) 0.009766
/*24 */         k = sbr->n_master;                                                                                         // (12) 0.03125
/*28 */     do {                                                                                                           // (21) 0.009766
/*30 */         int odd = 0;                                                                                               // (18) 0.02344
/*32 */         for (i = k; i == k || sb > (sbr->k[0] - 1 + msb - odd); i--) {                                             // (1) 0.07812
/*34 */             sb = sbr->f_master[i];                                                                                 // (9) 0.04492
/*36 */             odd = (sb + sbr->k[0]) & 1;                                                                            // (8) 0.05078
/*38 */         }                                                                                                          // (19) 0.01562
/*42 */         sbr->patch_num_subbands[sbr->num_patches]  = FFMAX(sb - usb, 0);                                           // (2) 0.07031
/*44 */         sbr->patch_start_subband[sbr->num_patches] = sbr->k[0] - odd - sbr->patch_num_subbands[sbr->num_patches];  // (0) 0.1055
/*48 */         if (sbr->patch_num_subbands[sbr->num_patches] > 0) {                                                       // (4) 0.06055
/*50 */             usb = sb;                                                                                              // (13) 0.03125
/*52 */             msb = sb;                                                                                              // (11) 0.0332
/*54 */             sbr->num_patches++;                                                                                    // (10) 0.03711
/*56 */         } else                                                                                                     // 0.0
/*58 */             msb = sbr->kx[1];                                                                                      // 0.0
/*62 */         if (sbr->f_master[k] - sb < 3)                                                                             // 0.0
/*64 */             k = sbr->n_master;                                                                                     // 0.0
/*66 */     } while (sb != sbr->kx[1] + sbr->m[1]);                                                                        // 0.0
/*70 */     if (sbr->patch_num_subbands[sbr->num_patches-1] < 3 && sbr->num_patches > 1)                                   // 0.0
/*72 */         sbr->num_patches--;                                                                                        // 0.0
/*76 */     // Requirements (14496-3 sp04 p205) sets the maximum number of patches to 5                                    // 0.0
/*78 */     // However the Coding Technologies decoder check uses 6 patches                                                // 0.0
/*80 */     if (sbr->num_patches > 6) {                                                                                    // 0.0
/*82 */         av_log(ac->avccontext, AV_LOG_ERROR, "Too many patches: %d\n", sbr->num_patches);                          // 0.0
/*84 */         return -1;                                                                                                 // 0.0
/*86 */     }                                                                                                              // 0.0
/*90 */     return 0;                                                                                                      // 0.0
/*92 */ }                                                                                                                  // 0.0
