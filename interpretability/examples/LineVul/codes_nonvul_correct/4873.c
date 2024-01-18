// commit message FFmpeg@11de006bab (target=0, prob=0.028452605, correct=True): Combine deprecation guards where appropriate
/*0  */ static int v4l2_read_packet(AVFormatContext *s1, AVPacket *pkt)  // (0) 0.08581
/*2  */ {                                                                // (21) 0.0033
/*4  */ #if FF_API_CODED_FRAME                                           // (8) 0.0396
/*6  */ FF_DISABLE_DEPRECATION_WARNINGS                                  // (10) 0.0363
/*8  */     struct video_data *s = s1->priv_data;                        // (4) 0.05611
/*10 */     AVFrame *frame = s1->streams[0]->codec->coded_frame;         // (1) 0.07921
/*12 */ FF_ENABLE_DEPRECATION_WARNINGS                                   // (12) 0.0363
/*14 */ #endif                                                           // (19) 0.006601
/*16 */     int res;                                                     // (16) 0.0198
/*20 */     av_init_packet(pkt);                                         // (7) 0.0429
/*22 */     if ((res = mmap_read_frame(s1, pkt)) < 0) {                  // (2) 0.07921
/*24 */         return res;                                              // (14) 0.033
/*26 */     }                                                            // (18) 0.0132
/*30 */ #if FF_API_CODED_FRAME                                           // (9) 0.0396
/*32 */ FF_DISABLE_DEPRECATION_WARNINGS                                  // (11) 0.0363
/*34 */     if (frame && s->interlaced) {                                // (6) 0.0462
/*36 */         frame->interlaced_frame = 1;                             // (5) 0.05611
/*38 */         frame->top_field_first = s->top_field_first;             // (3) 0.07591
/*40 */     }                                                            // (17) 0.0132
/*42 */ FF_ENABLE_DEPRECATION_WARNINGS                                   // (13) 0.0363
/*44 */ #endif                                                           // (20) 0.006601
/*48 */     return pkt->size;                                            // (15) 0.0297
/*50 */ }                                                                // (22) 0.0033
