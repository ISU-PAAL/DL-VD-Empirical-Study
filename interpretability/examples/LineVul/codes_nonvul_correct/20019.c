// commit message FFmpeg@3e1507a954 (target=0, prob=0.2160069, correct=True): avcodec/mjpegenc: Bypass the 2 pass encoding when optimal tables are not requested
/*0  */ static void encode_block(MpegEncContext *s, int16_t *block, int n)  // (4) 0.04492
/*2  */ {                                                                   // (29) 0.001953
/*4  */     int i, j, table_id;                                             // (20) 0.02344
/*6  */     int component, dc, last_index, val, run;                        // (11) 0.03125
/*8  */     MJpegContext *m = s->mjpeg_ctx;                                 // (9) 0.0332
/*12 */     /* DC coef */                                                   // (25) 0.01563
/*14 */     component = (n <= 3 ? 0 : (n&1) + 1);                           // (5) 0.03906
/*16 */     table_id = (n <= 3 ? 0 : 1);                                    // (12) 0.03125
/*18 */     dc = block[0]; /* overflow is impossible */                     // (15) 0.02734
/*20 */     val = dc - s->last_dc[component];                               // (13) 0.0293
/*24 */     ff_mjpeg_encode_coef(m, table_id, val, 0);                      // (2) 0.04883
/*28 */     s->last_dc[component] = dc;                                     // (17) 0.02734
/*32 */     /* AC coefs */                                                  // (24) 0.01758
/*36 */     run = 0;                                                        // (27) 0.01367
/*38 */     last_index = s->block_last_index[n];                            // (10) 0.0332
/*40 */     table_id |= 2;                                                  // (22) 0.01953
/*44 */     for(i=1;i<=last_index;i++) {                                    // (6) 0.03711
/*46 */         j = s->intra_scantable.permutated[i];                       // (3) 0.04688
/*48 */         val = block[j];                                             // (18) 0.02539
/*52 */         if (val == 0) {                                             // (16) 0.02734
/*54 */             run++;                                                  // (19) 0.02539
/*56 */         } else {                                                    // (23) 0.01953
/*58 */             while (run >= 16) {                                     // (8) 0.03516
/*60 */                 ff_mjpeg_encode_code(m, table_id, 0xf0);            // (0) 0.07031
/*62 */                 run -= 16;                                          // (7) 0.03711
/*64 */             }                                                       // (21) 0.02344
/*66 */             ff_mjpeg_encode_coef(m, table_id, val, run);            // (1) 0.06445
/*68 */             run = 0;                                                // (14) 0.0293
/*70 */         }                                                           // (26) 0.01563
/*72 */     }                                                               // (28) 0.007813
/*76 */     /* output EOB only if not already 64 values */                  // 0.0
/*78 */     if (last_index < 63 || run != 0)                                // 0.0
/*80 */         ff_mjpeg_encode_code(m, table_id, 0);                       // 0.0
/*82 */ }                                                                   // 0.0
