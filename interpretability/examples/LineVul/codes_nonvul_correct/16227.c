// commit message FFmpeg@3e1507a954 (target=0, prob=0.120084845, correct=True): avcodec/mjpegenc: Bypass the 2 pass encoding when optimal tables are not requested
/*0  */ void ff_mjpeg_encode_mb(MpegEncContext *s, int16_t block[12][64])  // (0) 0.05664
/*2  */ {                                                                  // (25) 0.001953
/*4  */     int i;                                                         // (23) 0.01172
/*6  */     if (s->chroma_format == CHROMA_444) {                          // (13) 0.03711
/*8  */         encode_block(s, block[0], 0);                              // (15) 0.03711
/*10 */         encode_block(s, block[2], 2);                              // (16) 0.03711
/*12 */         encode_block(s, block[4], 4);                              // (14) 0.03711
/*14 */         encode_block(s, block[8], 8);                              // (17) 0.03711
/*16 */         encode_block(s, block[5], 5);                              // (18) 0.03711
/*18 */         encode_block(s, block[9], 9);                              // (19) 0.03711
/*22 */         if (16*s->mb_x+8 < s->width) {                             // (1) 0.04687
/*24 */             encode_block(s, block[1], 1);                          // (2) 0.04492
/*26 */             encode_block(s, block[3], 3);                          // (3) 0.04492
/*28 */             encode_block(s, block[6], 6);                          // (4) 0.04492
/*30 */             encode_block(s, block[10], 10);                        // (5) 0.04492
/*32 */             encode_block(s, block[7], 7);                          // (6) 0.04492
/*34 */             encode_block(s, block[11], 11);                        // (7) 0.04492
/*36 */         }                                                          // (21) 0.01562
/*38 */     } else {                                                       // (24) 0.01172
/*40 */         for(i=0;i<5;i++) {                                         // (12) 0.03906
/*42 */             encode_block(s, block[i], i);                          // (8) 0.04492
/*44 */         }                                                          // (22) 0.01562
/*46 */         if (s->chroma_format == CHROMA_420) {                      // (9) 0.04492
/*48 */             encode_block(s, block[5], 5);                          // (10) 0.04492
/*50 */         } else {                                                   // (20) 0.01953
/*52 */             encode_block(s, block[6], 6);                          // (11) 0.04492
/*54 */             encode_block(s, block[5], 5);                          // 0.0
/*56 */             encode_block(s, block[7], 7);                          // 0.0
/*58 */         }                                                          // 0.0
/*60 */     }                                                              // 0.0
/*62 */ }                                                                  // 0.0
