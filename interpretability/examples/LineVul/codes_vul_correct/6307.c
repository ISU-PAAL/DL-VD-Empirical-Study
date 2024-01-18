// commit message FFmpeg@0eec40b713 (target=1, prob=0.5518827, correct=True): avidec: check for valid bit_rate range
/*0  */ static int calculate_bitrate(AVFormatContext *s)                                                   // (16) 0.02539
/*2  */ {                                                                                                  // (26) 0.001953
/*4  */     AVIContext *avi = s->priv_data;                                                                // (13) 0.03125
/*6  */     int i, j;                                                                                      // (24) 0.01562
/*8  */     int64_t lensum = 0;                                                                            // (19) 0.02344
/*10 */     int64_t maxpos = 0;                                                                            // (20) 0.02344
/*14 */     for (i = 0; i<s->nb_streams; i++) {                                                            // (8) 0.04102
/*16 */         int64_t len = 0;                                                                           // (14) 0.0293
/*18 */         AVStream *st = s->streams[i];                                                              // (10) 0.03711
/*22 */         if (!st->nb_index_entries)                                                                 // (12) 0.03516
/*24 */             continue;                                                                              // (17) 0.02539
/*28 */         for (j = 0; j < st->nb_index_entries; j++)                                                 // (4) 0.05078
/*30 */             len += st->index_entries[j].size;                                                      // (6) 0.04688
/*32 */         maxpos = FFMAX(maxpos, st->index_entries[j-1].pos);                                        // (2) 0.05664
/*34 */         lensum += len;                                                                             // (21) 0.02344
/*36 */     }                                                                                              // (25) 0.007812
/*38 */     if (maxpos < avi->io_fsize*9/10) // index does not cover the whole file                        // (3) 0.05469
/*40 */         return 0;                                                                                  // (22) 0.01953
/*42 */     if (lensum*9/10 > maxpos || lensum < maxpos*9/10) // frame sum and filesize mismatch           // (0) 0.06445
/*44 */         return 0;                                                                                  // (23) 0.01953
/*48 */     for (i = 0; i<s->nb_streams; i++) {                                                            // (9) 0.04102
/*50 */         int64_t len = 0;                                                                           // (15) 0.0293
/*52 */         AVStream *st = s->streams[i];                                                              // (11) 0.03711
/*54 */         int64_t duration;                                                                          // (18) 0.02539
/*58 */         for (j = 0; j < st->nb_index_entries; j++)                                                 // (5) 0.05078
/*60 */             len += st->index_entries[j].size;                                                      // (7) 0.04688
/*64 */         if (st->nb_index_entries < 2 || st->codec->bit_rate > 0)                                   // (1) 0.06055
/*66 */             continue;                                                                              // 0.0
/*68 */         duration = st->index_entries[j-1].timestamp - st->index_entries[0].timestamp;              // 0.0
/*70 */         st->codec->bit_rate = av_rescale(8*len, st->time_base.den, duration * st->time_base.num);  // 0.0
/*72 */     }                                                                                              // 0.0
/*74 */     return 1;                                                                                      // 0.0
/*76 */ }                                                                                                  // 0.0
