// commit message FFmpeg@136ce8baa4 (target=1, prob=0.9575614, correct=True): avcodec/ac3dec_fixed: Fix runtime error: left shift of 419 by 23 places cannot be represented in type 'int'
/*0   */ static void scale_coefs (                                       // (26) 0.01563
/*2   */     int32_t *dst,                                               // (20) 0.02148
/*4   */     const int32_t *src,                                         // (21) 0.02148
/*6   */     int dynrng,                                                 // (25) 0.01563
/*8   */     int len)                                                    // (27) 0.01172
/*10  */ {                                                               // (28) 0.001953
/*12  */     int i, shift, round;                                        // (22) 0.01953
/*14  */     int16_t mul;                                                // (24) 0.01758
/*16  */     int temp, temp1, temp2, temp3, temp4, temp5, temp6, temp7;  // (0) 0.05273
/*20  */     mul = (dynrng & 0x1f) + 0x20;                               // (1) 0.04102
/*22  */     shift = 4 - ((dynrng << 23) >> 28);                         // (11) 0.03516
/*24  */     if (shift > 0 ) {                                           // (23) 0.01953
/*26  */       round = 1 << (shift-1);                                   // (19) 0.02734
/*28  */       for (i=0; i<len; i+=8) {                                  // (10) 0.03906
/*32  */           temp = src[i] * mul;                                  // (12) 0.03516
/*34  */           temp1 = src[i+1] * mul;                               // (2) 0.04102
/*36  */           temp = temp + round;                                  // (18) 0.0293
/*38  */           temp2 = src[i+2] * mul;                               // (3) 0.04102
/*42  */           temp1 = temp1 + round;                                // (14) 0.0332
/*44  */           dst[i] = temp >> shift;                               // (13) 0.03516
/*46  */           temp3 = src[i+3] * mul;                               // (4) 0.04102
/*48  */           temp2 = temp2 + round;                                // (15) 0.0332
/*52  */           dst[i+1] = temp1 >> shift;                            // (5) 0.04102
/*54  */           temp4 = src[i + 4] * mul;                             // (6) 0.04102
/*56  */           temp3 = temp3 + round;                                // (16) 0.0332
/*58  */           dst[i+2] = temp2 >> shift;                            // (7) 0.04102
/*62  */           temp5 = src[i+5] * mul;                               // (8) 0.04102
/*64  */           temp4 = temp4 + round;                                // (17) 0.0332
/*66  */           dst[i+3] = temp3 >> shift;                            // (9) 0.04102
/*68  */           temp6 = src[i+6] * mul;                               // 0.0
/*72  */           dst[i+4] = temp4 >> shift;                            // 0.0
/*74  */           temp5 = temp5 + round;                                // 0.0
/*76  */           temp7 = src[i+7] * mul;                               // 0.0
/*78  */           temp6 = temp6 + round;                                // 0.0
/*82  */           dst[i+5] = temp5 >> shift;                            // 0.0
/*84  */           temp7 = temp7 + round;                                // 0.0
/*86  */           dst[i+6] = temp6 >> shift;                            // 0.0
/*88  */           dst[i+7] = temp7 >> shift;                            // 0.0
/*92  */       }                                                         // 0.0
/*94  */     } else {                                                    // 0.0
/*96  */       shift = -shift;                                           // 0.0
/*98  */       for (i=0; i<len; i+=8) {                                  // 0.0
/*102 */           temp = src[i] * mul;                                  // 0.0
/*104 */           temp1 = src[i+1] * mul;                               // 0.0
/*106 */           temp2 = src[i+2] * mul;                               // 0.0
/*110 */           dst[i] = temp << shift;                               // 0.0
/*112 */           temp3 = src[i+3] * mul;                               // 0.0
/*116 */           dst[i+1] = temp1 << shift;                            // 0.0
/*118 */           temp4 = src[i + 4] * mul;                             // 0.0
/*120 */           dst[i+2] = temp2 << shift;                            // 0.0
/*124 */           temp5 = src[i+5] * mul;                               // 0.0
/*126 */           dst[i+3] = temp3 << shift;                            // 0.0
/*128 */           temp6 = src[i+6] * mul;                               // 0.0
/*132 */           dst[i+4] = temp4 << shift;                            // 0.0
/*134 */           temp7 = src[i+7] * mul;                               // 0.0
/*138 */           dst[i+5] = temp5 << shift;                            // 0.0
/*140 */           dst[i+6] = temp6 << shift;                            // 0.0
/*142 */           dst[i+7] = temp7 << shift;                            // 0.0
/*146 */       }                                                         // 0.0
/*148 */     }                                                           // 0.0
/*150 */ }                                                               // 0.0
