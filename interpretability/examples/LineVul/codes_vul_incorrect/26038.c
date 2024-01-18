// commit message FFmpeg@2453f40602 (target=1, prob=0.40875068, correct=False): Prevent scalefactors from overflowing. fixes issue351
/*0   */ static void compute_scale_factors(unsigned char scale_code[SBLIMIT],        // (11) 0.03906
/*2   */                                   unsigned char scale_factors[SBLIMIT][3],  // (1) 0.0918
/*4   */                                   int sb_samples[3][12][SBLIMIT],           // (0) 0.09571
/*6   */                                   int sblimit)                              // (2) 0.07617
/*8   */ {                                                                           // (20) 0.001954
/*10  */     int *p, vmax, v, n, i, j, k, code;                                      // (7) 0.04297
/*12  */     int index, d1, d2;                                                      // (18) 0.02344
/*14  */     unsigned char *sf = &scale_factors[0][0];                               // (15) 0.03516
/*18  */     for(j=0;j<sblimit;j++) {                                                // (13) 0.03711
/*20  */         for(i=0;i<3;i++) {                                                  // (12) 0.03906
/*22  */             /* find the max absolute value */                               // (16) 0.03516
/*24  */             p = &sb_samples[i][0][j];                                       // (3) 0.04883
/*26  */             vmax = abs(*p);                                                 // (17) 0.03516
/*28  */             for(k=1;k<12;k++) {                                             // (4) 0.04687
/*30  */                 p += SBLIMIT;                                               // (8) 0.04297
/*32  */                 v = abs(*p);                                                // (10) 0.04101
/*34  */                 if (v > vmax)                                               // (9) 0.04297
/*36  */                     vmax = v;                                               // (5) 0.04687
/*38  */             }                                                               // (19) 0.02344
/*40  */             /* compute the scale factor index using log 2 computations */   // (6) 0.04493
/*42  */             if (vmax > 0) {                                                 // (14) 0.03711
/*44  */                 n = av_log2(vmax);                                          // 0.0
/*46  */                 /* n is the position of the MSB of vmax. now                // 0.0
/*48  */                    use at most 2 compares to find the index */              // 0.0
/*50  */                 index = (21 - n) * 3 - 3;                                   // 0.0
/*52  */                 if (index >= 0) {                                           // 0.0
/*54  */                     while (vmax <= scale_factor_table[index+1])             // 0.0
/*56  */                         index++;                                            // 0.0
/*58  */                 } else {                                                    // 0.0
/*60  */                     index = 0; /* very unlikely case of overflow */         // 0.0
/*62  */                 }                                                           // 0.0
/*64  */             } else {                                                        // 0.0
/*66  */                 index = 62; /* value 63 is not allowed */                   // 0.0
/*68  */             }                                                               // 0.0
/*72  */ #if 0                                                                       // 0.0
/*74  */             printf("%2d:%d in=%x %x %d\n",                                  // 0.0
/*76  */                    j, i, vmax, scale_factor_table[index], index);           // 0.0
/*78  */ #endif                                                                      // 0.0
/*80  */             /* store the scale factor */                                    // 0.0
/*82  */             assert(index >=0 && index <= 63);                               // 0.0
/*84  */             sf[i] = index;                                                  // 0.0
/*86  */         }                                                                   // 0.0
/*90  */         /* compute the transmission factor : look if the scale factors      // 0.0
/*92  */            are close enough to each other */                                // 0.0
/*94  */         d1 = scale_diff_table[sf[0] - sf[1] + 64];                          // 0.0
/*96  */         d2 = scale_diff_table[sf[1] - sf[2] + 64];                          // 0.0
/*100 */         /* handle the 25 cases */                                           // 0.0
/*102 */         switch(d1 * 5 + d2) {                                               // 0.0
/*104 */         case 0*5+0:                                                         // 0.0
/*106 */         case 0*5+4:                                                         // 0.0
/*108 */         case 3*5+4:                                                         // 0.0
/*110 */         case 4*5+0:                                                         // 0.0
/*112 */         case 4*5+4:                                                         // 0.0
/*114 */             code = 0;                                                       // 0.0
/*116 */             break;                                                          // 0.0
/*118 */         case 0*5+1:                                                         // 0.0
/*120 */         case 0*5+2:                                                         // 0.0
/*122 */         case 4*5+1:                                                         // 0.0
/*124 */         case 4*5+2:                                                         // 0.0
/*126 */             code = 3;                                                       // 0.0
/*128 */             sf[2] = sf[1];                                                  // 0.0
/*130 */             break;                                                          // 0.0
/*132 */         case 0*5+3:                                                         // 0.0
/*134 */         case 4*5+3:                                                         // 0.0
/*136 */             code = 3;                                                       // 0.0
/*138 */             sf[1] = sf[2];                                                  // 0.0
/*140 */             break;                                                          // 0.0
/*142 */         case 1*5+0:                                                         // 0.0
/*144 */         case 1*5+4:                                                         // 0.0
/*146 */         case 2*5+4:                                                         // 0.0
/*148 */             code = 1;                                                       // 0.0
/*150 */             sf[1] = sf[0];                                                  // 0.0
/*152 */             break;                                                          // 0.0
/*154 */         case 1*5+1:                                                         // 0.0
/*156 */         case 1*5+2:                                                         // 0.0
/*158 */         case 2*5+0:                                                         // 0.0
/*160 */         case 2*5+1:                                                         // 0.0
/*162 */         case 2*5+2:                                                         // 0.0
/*164 */             code = 2;                                                       // 0.0
/*166 */             sf[1] = sf[2] = sf[0];                                          // 0.0
/*168 */             break;                                                          // 0.0
/*170 */         case 2*5+3:                                                         // 0.0
/*172 */         case 3*5+3:                                                         // 0.0
/*174 */             code = 2;                                                       // 0.0
/*176 */             sf[0] = sf[1] = sf[2];                                          // 0.0
/*178 */             break;                                                          // 0.0
/*180 */         case 3*5+0:                                                         // 0.0
/*182 */         case 3*5+1:                                                         // 0.0
/*184 */         case 3*5+2:                                                         // 0.0
/*186 */             code = 2;                                                       // 0.0
/*188 */             sf[0] = sf[2] = sf[1];                                          // 0.0
/*190 */             break;                                                          // 0.0
/*192 */         case 1*5+3:                                                         // 0.0
/*194 */             code = 2;                                                       // 0.0
/*196 */             if (sf[0] > sf[2])                                              // 0.0
/*198 */               sf[0] = sf[2];                                                // 0.0
/*200 */             sf[1] = sf[2] = sf[0];                                          // 0.0
/*202 */             break;                                                          // 0.0
/*204 */         default:                                                            // 0.0
/*206 */             assert(0); //cannot happen                                      // 0.0
/*208 */             code = 0;           /* kill warning */                          // 0.0
/*210 */         }                                                                   // 0.0
/*214 */ #if 0                                                                       // 0.0
/*216 */         printf("%d: %2d %2d %2d %d %d -> %d\n", j,                          // 0.0
/*218 */                sf[0], sf[1], sf[2], d1, d2, code);                          // 0.0
/*220 */ #endif                                                                      // 0.0
/*222 */         scale_code[j] = code;                                               // 0.0
/*224 */         sf += 3;                                                            // 0.0
/*226 */     }                                                                       // 0.0
/*228 */ }                                                                           // 0.0
