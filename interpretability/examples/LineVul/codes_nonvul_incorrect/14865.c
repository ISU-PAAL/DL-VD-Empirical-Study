// commit message FFmpeg@81a8701eb5 (target=0, prob=0.85112447, correct=False): avformat/oggenc: Check segments_count for headers too
/*0   */ static int ogg_buffer_data(AVFormatContext *s, AVStream *st,                       // (9) 0.03905
/*2   */                            uint8_t *data, unsigned size, int64_t granule,          // (0) 0.08395
/*4   */                            int header)                                             // (3) 0.05662
/*6   */ {                                                                                  // (24) 0.001956
/*8   */     OGGStreamContext *oggstream = st->priv_data;                                   // (15) 0.03319
/*10  */     OGGContext *ogg = s->priv_data;                                                // (17) 0.02928
/*12  */     int total_segments = size / 255 + 1;                                           // (16) 0.02929
/*14  */     uint8_t *p = data;                                                             // (19) 0.02343
/*16  */     int i, segments, len, flush = 0;                                               // (18) 0.02734
/*20  */     // Handles VFR by flushing page because this frame needs to have a timestamp   // (8) 0.03909
/*22  */     // For theora, keyframes also need to have a timestamp to correctly mark       // (12) 0.03717
/*24  */     // them as such, otherwise seeking will not work correctly at the very         // (13) 0.03324
/*26  */     // least with old libogg versions.                                             // (20) 0.0215
/*28  */     // Do not try to flush header packets though, that will create broken files.   // (11) 0.03718
/*30  */     if (st->codec->codec_id == AV_CODEC_ID_THEORA && !header &&                    // (2) 0.05857
/*32  */         (ogg_granule_to_timestamp(oggstream, granule) >                            // (4) 0.04881
/*34  */          ogg_granule_to_timestamp(oggstream, oggstream->last_granule) + 1 ||       // (1) 0.06638
/*36  */          ogg_key_granule(oggstream, granule))) {                                   // (7) 0.04495
/*38  */         if (oggstream->page.granule != -1)                                         // (10) 0.03905
/*40  */             ogg_buffer_page(s, oggstream);                                         // (6) 0.04685
/*42  */         flush = 1;                                                                 // (21) 0.02148
/*44  */     }                                                                              // (23) 0.007814
/*48  */     // avoid a continued page                                                      // (22) 0.01563
/*50  */     if (!header && oggstream->page.size > 0 &&                                     // (14) 0.03319
/*52  */         MAX_PAGE_SIZE - oggstream->page.size < size) {                             // (5) 0.04881
/*54  */         ogg_buffer_page(s, oggstream);                                             // 0.0
/*56  */     }                                                                              // 0.0
/*60  */     for (i = 0; i < total_segments; ) {                                            // 0.0
/*62  */         OGGPage *page = &oggstream->page;                                          // 0.0
/*66  */         segments = FFMIN(total_segments - i, 255 - page->segments_count);          // 0.0
/*70  */         if (i && !page->segments_count)                                            // 0.0
/*72  */             page->flags |= 1; // continued packet                                  // 0.0
/*76  */         memset(page->segments+page->segments_count, 255, segments - 1);            // 0.0
/*78  */         page->segments_count += segments - 1;                                      // 0.0
/*82  */         len = FFMIN(size, segments*255);                                           // 0.0
/*84  */         page->segments[page->segments_count++] = len - (segments-1)*255;           // 0.0
/*86  */         memcpy(page->data+page->size, p, len);                                     // 0.0
/*88  */         p += len;                                                                  // 0.0
/*90  */         size -= len;                                                               // 0.0
/*92  */         i += segments;                                                             // 0.0
/*94  */         page->size += len;                                                         // 0.0
/*98  */         if (i == total_segments)                                                   // 0.0
/*100 */             page->granule = granule;                                               // 0.0
/*104 */         if (!header) {                                                             // 0.0
/*106 */             AVStream *st = s->streams[page->stream_index];                         // 0.0
/*110 */             int64_t start = av_rescale_q(page->start_granule, st->time_base,       // 0.0
/*112 */                                          AV_TIME_BASE_Q);                          // 0.0
/*114 */             int64_t next  = av_rescale_q(page->granule, st->time_base,             // 0.0
/*116 */                                          AV_TIME_BASE_Q);                          // 0.0
/*120 */             if (page->segments_count == 255 ||                                     // 0.0
/*122 */                 (ogg->pref_size     > 0 && page->size   >= ogg->pref_size) ||      // 0.0
/*124 */                 (ogg->pref_duration > 0 && next - start >= ogg->pref_duration)) {  // 0.0
/*126 */                 ogg_buffer_page(s, oggstream);                                     // 0.0
/*128 */             }                                                                      // 0.0
/*130 */         }                                                                          // 0.0
/*132 */     }                                                                              // 0.0
/*136 */     if (flush && oggstream->page.granule != -1)                                    // 0.0
/*138 */         ogg_buffer_page(s, oggstream);                                             // 0.0
/*142 */     return 0;                                                                      // 0.0
/*144 */ }                                                                                  // 0.0
