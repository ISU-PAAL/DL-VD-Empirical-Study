// commit message FFmpeg@f61d44b74a (target=0, prob=0.53337675, correct=False): opus_silk: fix typo causing overflow in silk_stabilize_lsf
/*0   */ static inline void silk_stabilize_lsf(int16_t nlsf[16], int order, const uint16_t min_delta[17])  // (0) 0.07227
/*2   */ {                                                                                                 // (23) 0.001953
/*4   */     int pass, i;                                                                                  // (21) 0.01562
/*6   */     for (pass = 0; pass < 20; pass++) {                                                           // (15) 0.03125
/*8   */         int k, min_diff = 0;                                                                      // (17) 0.03125
/*10  */         for (i = 0; i < order+1; i++) {                                                           // (5) 0.04297
/*12  */             int low  = i != 0     ? nlsf[i-1] : 0;                                                // (1) 0.06641
/*14  */             int high = i != order ? nlsf[i]   : 32768;                                            // (2) 0.05859
/*16  */             int diff = (high - low) - (min_delta[i]);                                             // (3) 0.05469
/*20  */             if (diff < min_diff) {                                                                // (10) 0.03906
/*22  */                 min_diff = diff;                                                                  // (8) 0.04102
/*24  */                 k = i;                                                                            // (13) 0.03711
/*28  */                 if (pass == 20)                                                                   // (7) 0.04102
/*30  */                     break;                                                                        // (9) 0.04102
/*32  */             }                                                                                     // (20) 0.02344
/*34  */         }                                                                                         // (22) 0.01562
/*36  */         if (min_diff == 0) /* no issues; stabilized */                                            // (6) 0.04102
/*38  */             return;                                                                               // (19) 0.02539
/*42  */         /* wiggle one or two LSFs */                                                              // (14) 0.0332
/*44  */         if (k == 0) {                                                                             // (18) 0.02734
/*46  */             /* repel away from lower bound */                                                     // (11) 0.03711
/*48  */             nlsf[0] = min_delta[0];                                                               // (4) 0.04883
/*50  */         } else if (k == order) {                                                                  // (16) 0.03125
/*52  */             /* repel away from higher bound */                                                    // (12) 0.03711
/*54  */             nlsf[order-1] = 32768 - min_delta[order];                                             // 0.0
/*56  */         } else {                                                                                  // 0.0
/*58  */             /* repel away from current position */                                                // 0.0
/*60  */             int min_center = 0, max_center = 32768, center_val;                                   // 0.0
/*64  */             /* lower extent */                                                                    // 0.0
/*66  */             for (i = 0; i < k; i++)                                                               // 0.0
/*68  */                 min_center += min_delta[i];                                                       // 0.0
/*70  */             min_center += min_delta[k] >> 1;                                                      // 0.0
/*74  */             /* upper extent */                                                                    // 0.0
/*76  */             for (i = order; i > k; i--)                                                           // 0.0
/*78  */                 max_center -= min_delta[k];                                                       // 0.0
/*80  */             max_center -= min_delta[k] >> 1;                                                      // 0.0
/*84  */             /* move apart */                                                                      // 0.0
/*86  */             center_val = nlsf[k - 1] + nlsf[k];                                                   // 0.0
/*88  */             center_val = (center_val >> 1) + (center_val & 1); // rounded divide by 2             // 0.0
/*90  */             center_val = FFMIN(max_center, FFMAX(min_center, center_val));                        // 0.0
/*94  */             nlsf[k - 1] = center_val - (min_delta[k] >> 1);                                       // 0.0
/*96  */             nlsf[k]     = nlsf[k - 1] + min_delta[k];                                             // 0.0
/*98  */         }                                                                                         // 0.0
/*100 */     }                                                                                             // 0.0
/*104 */     /* resort to the fall-back method, the standard method for LSF stabilization */               // 0.0
/*108 */     /* sort; as the LSFs should be nearly sorted, use insertion sort */                           // 0.0
/*110 */     for (i = 1; i < order; i++) {                                                                 // 0.0
/*112 */         int j, value = nlsf[i];                                                                   // 0.0
/*114 */         for (j = i - 1; j >= 0 && nlsf[j] > value; j--)                                           // 0.0
/*116 */             nlsf[j + 1] = nlsf[j];                                                                // 0.0
/*118 */         nlsf[j + 1] = value;                                                                      // 0.0
/*120 */     }                                                                                             // 0.0
/*124 */     /* push forwards to increase distance */                                                      // 0.0
/*126 */     if (nlsf[0] < min_delta[0])                                                                   // 0.0
/*128 */         nlsf[0] = min_delta[0];                                                                   // 0.0
/*130 */     for (i = 1; i < order; i++)                                                                   // 0.0
/*132 */         if (nlsf[i] < nlsf[i - 1] + min_delta[i])                                                 // 0.0
/*134 */             nlsf[i] = nlsf[i - 1] + min_delta[i];                                                 // 0.0
/*138 */     /* push backwards to increase distance */                                                     // 0.0
/*140 */     if (nlsf[order-1] > 32768 - min_delta[order])                                                 // 0.0
/*142 */         nlsf[order-1] = 32768 - min_delta[order];                                                 // 0.0
/*144 */     for (i = order-2; i >= 0; i--)                                                                // 0.0
/*146 */         if (nlsf[i] > nlsf[i + 1] - min_delta[i+1])                                               // 0.0
/*148 */             nlsf[i] = nlsf[i + 1] - min_delta[i+1];                                               // 0.0
/*152 */     return;                                                                                       // 0.0
/*154 */ }                                                                                                 // 0.0
