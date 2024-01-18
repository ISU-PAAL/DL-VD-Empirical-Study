// commit message FFmpeg@9f61abc811 (target=0, prob=0.5317762, correct=False): lavf: allow custom IO for all files
/*0  */ static int segment_hls_window(AVFormatContext *s, int last)              // (12) 0.03516
/*2  */ {                                                                        // (20) 0.001953
/*4  */     SegmentContext *seg = s->priv_data;                                  // (15) 0.03125
/*6  */     int i, ret = 0;                                                      // (16) 0.01953
/*8  */     char buf[1024];                                                      // (18) 0.01563
/*12 */     if ((ret = avio_open2(&seg->pb, seg->list, AVIO_FLAG_WRITE,          // (4) 0.06055
/*14 */                               &s->interrupt_callback, NULL)) < 0)        // (0) 0.08203
/*16 */         goto fail;                                                       // (17) 0.01953
/*20 */     avio_printf(seg->pb, "#EXTM3U\n");                                   // (11) 0.04102
/*22 */     avio_printf(seg->pb, "#EXT-X-VERSION:3\n");                          // (9) 0.04687
/*24 */     avio_printf(seg->pb, "#EXT-X-TARGETDURATION:%d\n", (int)seg->time);  // (1) 0.07227
/*26 */     avio_printf(seg->pb, "#EXT-X-MEDIA-SEQUENCE:%d\n",                   // (7) 0.05859
/*28 */                 FFMAX(0, seg->number - seg->size));                      // (6) 0.05859
/*32 */     av_log(s, AV_LOG_VERBOSE, "EXT-X-MEDIA-SEQUENCE:%d\n",               // (3) 0.06641
/*34 */            FFMAX(0, seg->number - seg->size));                           // (8) 0.04883
/*38 */     for (i = FFMAX(0, seg->number - seg->size);                          // (10) 0.04297
/*40 */          i < seg->number; i++) {                                         // (13) 0.03516
/*42 */         avio_printf(seg->pb, "#EXTINF:%d,\n", (int)seg->time);           // (2) 0.07031
/*44 */         if (seg->entry_prefix) {                                         // (14) 0.0332
/*46 */             avio_printf(seg->pb, "%s", seg->entry_prefix);               // (5) 0.06055
/*48 */         }                                                                // (19) 0.01562
/*50 */         ret = av_get_frame_filename(buf, sizeof(buf), s->filename, i);   // 0.0
/*52 */         if (ret < 0) {                                                   // 0.0
/*54 */             ret = AVERROR(EINVAL);                                       // 0.0
/*56 */             goto fail;                                                   // 0.0
/*58 */         }                                                                // 0.0
/*60 */         avio_printf(seg->pb, "%s\n", buf);                               // 0.0
/*62 */     }                                                                    // 0.0
/*66 */     if (last)                                                            // 0.0
/*68 */         avio_printf(seg->pb, "#EXT-X-ENDLIST\n");                        // 0.0
/*70 */ fail:                                                                    // 0.0
/*72 */     avio_closep(&seg->pb);                                               // 0.0
/*74 */     return ret;                                                          // 0.0
/*76 */ }                                                                        // 0.0
