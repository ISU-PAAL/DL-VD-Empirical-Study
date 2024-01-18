// commit message FFmpeg@8b2fce0d3f (target=1, prob=0.97337127, correct=True): Turn ancient V offset numerical constants into named ones. Add a check that checks that the width is within the choosen constant. This might have been exploitable.
/*0  */ static inline void yuv2nv12XinC(int16_t *lumFilter, int16_t **lumSrc, int lumFilterSize,              // (1) 0.07108
/*2  */                                 int16_t *chrFilter, int16_t **chrSrc, int chrFilterSize,              // (13) 0.001925
/*4  */                                 uint8_t *dest, uint8_t *uDest, int dstW, int chrDstW, int dstFormat)  // (4) 0.01318
/*6  */ {                                                                                                     // (2) 0.04816
/*8  */     //FIXME Optimize (just quickly writen not opti..)                                                 // (0) 0.678
/*10 */     int i;                                                                                            // (5) 0.0126
/*12 */     for (i=0; i<dstW; i++)                                                                            // (6) 0.008816
/*14 */     {                                                                                                 // (9) 0.003252
/*16 */         int val=1<<18;                                                                                // (12) 0.002237
/*18 */         int j;                                                                                        // (20) 0.0005664
/*20 */         for (j=0; j<lumFilterSize; j++)                                                               // (14) 0.001767
/*22 */             val += lumSrc[j][i] * lumFilter[j];                                                       // (10) 0.002873
/*26 */         dest[i]= av_clip_uint8(val>>19);                                                              // (7) 0.008309
/*28 */     }                                                                                                 // (11) 0.002255
/*32 */     if (!uDest)                                                                                       // (8) 0.005854
/*34 */         return;                                                                                       // (16) 0.001542
/*38 */     if (dstFormat == PIX_FMT_NV12)                                                                    // (3) 0.01554
/*40 */         for (i=0; i<chrDstW; i++)                                                                     // (18) 0.001375
/*42 */         {                                                                                             // (23) 0.0001139
/*44 */             int u=1<<18;                                                                              // (17) 0.001449
/*46 */             int v=1<<18;                                                                              // (15) 0.001573
/*48 */             int j;                                                                                    // (21) 0.0002554
/*50 */             for (j=0; j<chrFilterSize; j++)                                                           // (19) 0.001087
/*52 */             {                                                                                         // (22) 0.0001917
/*54 */                 u += chrSrc[j][i] * chrFilter[j];                                                     // 0.0
/*56 */                 v += chrSrc[j][i + 2048] * chrFilter[j];                                              // 0.0
/*58 */             }                                                                                         // 0.0
/*62 */             uDest[2*i]= av_clip_uint8(u>>19);                                                         // 0.0
/*64 */             uDest[2*i+1]= av_clip_uint8(v>>19);                                                       // 0.0
/*66 */         }                                                                                             // 0.0
/*68 */     else                                                                                              // 0.0
/*70 */         for (i=0; i<chrDstW; i++)                                                                     // 0.0
/*72 */         {                                                                                             // 0.0
/*74 */             int u=1<<18;                                                                              // 0.0
/*76 */             int v=1<<18;                                                                              // 0.0
/*78 */             int j;                                                                                    // 0.0
/*80 */             for (j=0; j<chrFilterSize; j++)                                                           // 0.0
/*82 */             {                                                                                         // 0.0
/*84 */                 u += chrSrc[j][i] * chrFilter[j];                                                     // 0.0
/*86 */                 v += chrSrc[j][i + 2048] * chrFilter[j];                                              // 0.0
/*88 */             }                                                                                         // 0.0
/*92 */             uDest[2*i]= av_clip_uint8(v>>19);                                                         // 0.0
/*94 */             uDest[2*i+1]= av_clip_uint8(u>>19);                                                       // 0.0
/*96 */         }                                                                                             // 0.0
/*98 */ }                                                                                                     // 0.0
