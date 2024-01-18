// commit message FFmpeg@01a33b835f (target=1, prob=0.96088946, correct=True): avcodec/pictordec: Fix runtime error: left shift of 64 by 25 places cannot be represented in type 'int'
/*0  */ static void picmemset(PicContext *s, AVFrame *frame, int value, int run,  // (10) 0.04297
/*2  */                       int *x, int *y, int *plane, int bits_per_plane)     // (0) 0.07812
/*4  */ {                                                                         // (22) 0.001953
/*6  */     uint8_t *d;                                                           // (20) 0.01953
/*8  */     int shift = *plane * bits_per_plane;                                  // (17) 0.0293
/*10 */     int mask  = ((1 << bits_per_plane) - 1) << shift;                     // (11) 0.04297
/*12 */     value   <<= shift;                                                    // (19) 0.01953
/*16 */     while (run > 0) {                                                     // (18) 0.01953
/*18 */         int j;                                                            // (21) 0.01953
/*20 */         for (j = 8-bits_per_plane; j >= 0; j -= bits_per_plane) {         // (1) 0.0625
/*22 */             d = frame->data[0] + *y * frame->linesize[0];                 // (2) 0.05859
/*24 */             d[*x] |= (value >> j) & mask;                                 // (7) 0.05078
/*26 */             *x += 1;                                                      // (16) 0.03125
/*28 */             if (*x == s->width) {                                         // (13) 0.03906
/*30 */                 *y -= 1;                                                  // (14) 0.03906
/*32 */                 *x = 0;                                                   // (15) 0.03906
/*34 */                 if (*y < 0) {                                             // (12) 0.04297
/*36 */                    *y = s->height - 1;                                    // (6) 0.05273
/*38 */                    *plane += 1;                                           // (9) 0.04492
/*40 */                    if (*plane >= s->nb_planes)                            // (4) 0.05469
/*42 */                        return;                                            // (8) 0.04687
/*44 */                    value <<= bits_per_plane;                              // (5) 0.05273
/*46 */                    mask  <<= bits_per_plane;                              // (3) 0.05469
/*48 */                 }                                                         // 0.0
/*50 */             }                                                             // 0.0
/*52 */         }                                                                 // 0.0
/*54 */         run--;                                                            // 0.0
/*56 */     }                                                                     // 0.0
/*58 */ }                                                                         // 0.0
