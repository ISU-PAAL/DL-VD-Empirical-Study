// commit message FFmpeg@d1916d13e2 (target=1, prob=0.6583921, correct=True): dsputil/pngdsp: fix signed/unsigned type in end comparison
/*0  */ static void diff_bytes_c(uint8_t *dst, uint8_t *src1, uint8_t *src2, int w){  // (1) 0.06836
/*2  */     long i;                                                                   // (17) 0.01172
/*4  */ #if !HAVE_FAST_UNALIGNED                                                      // (15) 0.02539
/*6  */     if((long)src2 & (sizeof(long)-1)){                                        // (14) 0.03711
/*8  */         for(i=0; i+7<w; i+=8){                                                // (11) 0.04492
/*10 */             dst[i+0] = src1[i+0]-src2[i+0];                                   // (2) 0.0625
/*12 */             dst[i+1] = src1[i+1]-src2[i+1];                                   // (6) 0.0625
/*14 */             dst[i+2] = src1[i+2]-src2[i+2];                                   // (3) 0.0625
/*16 */             dst[i+3] = src1[i+3]-src2[i+3];                                   // (4) 0.0625
/*18 */             dst[i+4] = src1[i+4]-src2[i+4];                                   // (7) 0.0625
/*20 */             dst[i+5] = src1[i+5]-src2[i+5];                                   // (8) 0.0625
/*22 */             dst[i+6] = src1[i+6]-src2[i+6];                                   // (5) 0.0625
/*24 */             dst[i+7] = src1[i+7]-src2[i+7];                                   // (9) 0.0625
/*26 */         }                                                                     // (16) 0.01563
/*28 */     }else                                                                     // (18) 0.009766
/*30 */ #endif                                                                        // (20) 0.003906
/*32 */     for(i=0; i<=w-sizeof(long); i+=sizeof(long)){                             // (10) 0.05273
/*34 */         long a = *(long*)(src1+i);                                            // (12) 0.03906
/*36 */         long b = *(long*)(src2+i);                                            // (13) 0.03906
/*38 */         *(long*)(dst+i) = ((a|pb_80) - (b&pb_7f)) ^ ((a^b^pb_80)&pb_80);      // (0) 0.0957
/*40 */     }                                                                         // (19) 0.007812
/*42 */     for(; i<w; i++)                                                           // 0.0
/*44 */         dst[i+0] = src1[i+0]-src2[i+0];                                       // 0.0
/*46 */ }                                                                             // 0.0
