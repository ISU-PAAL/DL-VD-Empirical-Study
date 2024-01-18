// commit message FFmpeg@eb9fb508b0 (target=1, prob=0.71197444, correct=True): matroskadec: use uint64_t instead of int for index_scale
/*0  */ static void matroska_add_index_entries(MatroskaDemuxContext *matroska)            // (7) 0.04688
/*2  */ {                                                                                 // (22) 0.001953
/*4  */     EbmlList *index_list;                                                         // (16) 0.02148
/*6  */     MatroskaIndex *index;                                                         // (17) 0.01953
/*8  */     int index_scale = 1;                                                          // (18) 0.01953
/*10 */     int i, j;                                                                     // (20) 0.01562
/*14 */     if (matroska->ctx->flags & AVFMT_FLAG_IGNIDX)                                 // (8) 0.04492
/*16 */         return;                                                                   // (19) 0.01758
/*20 */     index_list = &matroska->index;                                                // (15) 0.02734
/*22 */     index      = index_list->elem;                                                // (13) 0.0332
/*24 */     if (index_list->nb_elem &&                                                    // (14) 0.02734
/*26 */         index[0].time > 1E14 / matroska->time_scale) {                            // (5) 0.05078
/*28 */         av_log(matroska->ctx, AV_LOG_WARNING, "Working around broken index.\n");  // (2) 0.0625
/*30 */         index_scale = matroska->time_scale;                                       // (11) 0.03711
/*32 */     }                                                                             // (21) 0.007812
/*34 */     for (i = 0; i < index_list->nb_elem; i++) {                                   // (9) 0.04492
/*36 */         EbmlList *pos_list    = &index[i].pos;                                    // (6) 0.04883
/*38 */         MatroskaIndexPos *pos = pos_list->elem;                                   // (10) 0.04297
/*40 */         for (j = 0; j < pos_list->nb_elem; j++) {                                 // (3) 0.05273
/*42 */             MatroskaTrack *track = matroska_find_track_by_num(matroska,           // (1) 0.06641
/*44 */                                                               pos[j].track);      // (0) 0.1309
/*46 */             if (track && track->stream)                                           // (12) 0.03711
/*48 */                 av_add_index_entry(track->stream,                                 // (4) 0.05273
/*50 */                                    pos[j].pos + matroska->segment_start,          // 0.0
/*52 */                                    index[i].time / index_scale, 0, 0,             // 0.0
/*54 */                                    AVINDEX_KEYFRAME);                             // 0.0
/*56 */         }                                                                         // 0.0
/*58 */     }                                                                             // 0.0
/*60 */ }                                                                                 // 0.0
