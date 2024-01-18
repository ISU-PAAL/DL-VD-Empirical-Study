// commit message FFmpeg@22fa38f0c8 (target=0, prob=0.085454, correct=True): part 2/2 of fixing Altivec-accelerated H264 luma inloop filter
/*0  */ static inline void h264_deblock_q1(register vector unsigned char p0,                     // (8) 0.03711
/*2  */                                                    register vector unsigned char p1,     // (1) 0.1113
/*4  */                                                    register vector unsigned char p2,     // (2) 0.1113
/*6  */                                                    register vector unsigned char q0,     // (3) 0.1113
/*8  */                                                    register vector unsigned char tc0) {  // (0) 0.1133
/*12 */     register vector unsigned char average = vec_avg(p0, q0);                             // (7) 0.03906
/*14 */     register vector unsigned char temp;                                                  // (15) 0.01758
/*16 */     register vector unsigned char uncliped;                                              // (13) 0.02148
/*18 */     register vector unsigned char ones;                                                  // (17) 0.01758
/*20 */     register vector unsigned char max;                                                   // (16) 0.01758
/*22 */     register vector unsigned char min;                                                   // (14) 0.01758
/*26 */     temp = vec_xor(average, p2);                                                         // (11) 0.0293
/*28 */     average = vec_avg(average, p2);     /*avg(p2, avg(p0, q0)) */                        // (6) 0.06836
/*30 */     ones = vec_splat_u8(1);                                                              // (12) 0.0293
/*32 */     temp = vec_and(temp, ones);         /*(p2^avg(p0, q0)) & 1 */                        // (4) 0.07422
/*34 */     uncliped = vec_subs(average, temp); /*(p2+((p0+q0+1)>>1))>>1 */                      // (5) 0.07031
/*36 */     max = vec_adds(p1, tc0);                                                             // (9) 0.03125
/*38 */     min = vec_subs(p1, tc0);                                                             // (10) 0.03125
/*40 */     p1 = vec_max(min, uncliped);                                                         // 0.0
/*42 */     p1 = vec_min(max, p1);                                                               // 0.0
/*44 */ }                                                                                        // 0.0
