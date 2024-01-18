// commit message FFmpeg@ebbcdc9ac0 (target=0, prob=0.023091055, correct=True): user specified motion estimation range limit h263 me range fixed (was smaller then needed)
/*0  */ static inline void get_limits(MpegEncContext *s, int *range, int *xmin, int *ymin, int *xmax, int *ymax, int f_code)  // (0) 0.09977
/*2  */ {                                                                                                                     // (23) 0.00232
/*4  */     *range = 8 * (1 << (f_code - 1));                                                                                 // (10) 0.04176
/*6  */     /* XXX: temporary kludge to avoid overflow for msmpeg4 */                                                         // (7) 0.04408
/*8  */     if (s->out_format == FMT_H263 && !s->h263_msmpeg4)                                                                // (2) 0.06265
/*10 */ 	*range *= 2;                                                                                                         // (20) 0.01624
/*14 */     if (s->unrestricted_mv) {                                                                                         // (13) 0.03248
/*16 */         *xmin = -16;                                                                                                  // (14) 0.03248
/*18 */         *ymin = -16;                                                                                                  // (15) 0.03248
/*20 */         if (s->h263_plus)                                                                                             // (12) 0.03712
/*22 */             *range *= 2;                                                                                              // (11) 0.03944
/*24 */         if(s->avctx->codec->id!=CODEC_ID_MPEG4){                                                                      // (1) 0.06961
/*26 */             *xmax = s->mb_width*16;                                                                                   // (3) 0.05336
/*28 */             *ymax = s->mb_height*16;                                                                                  // (4) 0.05336
/*30 */         }else {                                                                                                       // (18) 0.0232
/*32 */             *xmax = s->width;                                                                                         // (8) 0.04408
/*34 */             *ymax = s->height;                                                                                        // (9) 0.04408
/*36 */         }                                                                                                             // (19) 0.01856
/*38 */     } else {                                                                                                          // (21) 0.01392
/*40 */         *xmin = 0;                                                                                                    // (16) 0.03016
/*42 */         *ymin = 0;                                                                                                    // (17) 0.03016
/*44 */         *xmax = s->mb_width*16 - 16;                                                                                  // (5) 0.04872
/*46 */         *ymax = s->mb_height*16 - 16;                                                                                 // (6) 0.04872
/*48 */     }                                                                                                                 // (22) 0.009281
/*50 */ }                                                                                                                     // (24) 0.00232
