// commit message FFmpeg@8adff79b6d (target=1, prob=0.4453289, correct=False): avformat/mov: remove redundant assignment
/*0  */ static int mov_seek_fragment(AVFormatContext *s, AVStream *st, int64_t timestamp)  // (6) 0.06835
/*2  */ {                                                                                  // (18) 0.002532
/*4  */     MOVContext *mov = s->priv_data;                                                // (11) 0.03797
/*6  */     int i, j;                                                                      // (14) 0.02025
/*10 */     if (!mov->fragment_index_complete)                                             // (9) 0.04051
/*12 */         return 0;                                                                  // (13) 0.02532
/*16 */     for (i = 0; i < mov->fragment_index_count; i++) {                              // (8) 0.06076
/*18 */         if (mov->fragment_index_data[i]->track_id == st->id) {                     // (1) 0.08101
/*20 */             MOVFragmentIndex *index = index = mov->fragment_index_data[i];         // (2) 0.08101
/*22 */             for (j = index->item_count - 1; j >= 0; j--) {                         // (3) 0.07848
/*24 */                 if (index->items[j].time <= timestamp) {                           // (5) 0.07089
/*26 */                     if (index->items[j].headers_read)                              // (4) 0.07848
/*28 */                         return 0;                                                  // (7) 0.06582
/*32 */                     return mov_switch_root(s, index->items[j].moof_offset);        // (0) 0.09873
/*34 */                 }                                                                  // (10) 0.04051
/*36 */             }                                                                      // (12) 0.03038
/*38 */         }                                                                          // (15) 0.02025
/*40 */     }                                                                              // (17) 0.01013
/*44 */     return 0;                                                                      // (16) 0.01519
/*46 */ }                                                                                  // (19) 0.002532
