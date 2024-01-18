// commit message FFmpeg@607ad990d3 (target=0, prob=0.65262663, correct=False): dvbsubdec: check memory allocations and propagate errors
/*0   */ static int dvbsub_decode(AVCodecContext *avctx,                                          // (8) 0.0352
/*2   */                          void *data, int *data_size,                                     // (0) 0.06638
/*4   */                          AVPacket *avpkt)                                                // (1) 0.06249
/*6   */ {                                                                                        // (31) 0.001957
/*8   */     const uint8_t *buf = avpkt->data;                                                    // (13) 0.0332
/*10  */     int buf_size = avpkt->size;                                                          // (17) 0.02734
/*12  */     DVBSubContext *ctx = avctx->priv_data;                                               // (12) 0.03321
/*14  */     AVSubtitle *sub = data;                                                              // (19) 0.0215
/*16  */     const uint8_t *p, *p_end;                                                            // (14) 0.03124
/*18  */     int segment_type;                                                                    // (24) 0.01565
/*20  */     int page_id;                                                                         // (25) 0.01564
/*22  */     int segment_length;                                                                  // (26) 0.01563
/*24  */     int i;                                                                               // (28) 0.01172
/*28  */     av_dlog(avctx, "DVB sub packet:\n");                                                 // (7) 0.0371
/*32  */     for (i=0; i < buf_size; i++) {                                                       // (10) 0.03515
/*34  */         av_dlog(avctx, "%02x ", buf[i]);                                                 // (2) 0.04491
/*36  */         if (i % 16 == 15)                                                                // (15) 0.02929
/*38  */             av_dlog(avctx, "\n");                                                        // (5) 0.04295
/*40  */     }                                                                                    // (29) 0.00781
/*44  */     if (i % 16)                                                                          // (23) 0.01757
/*46  */         av_dlog(avctx, "\n");                                                            // (11) 0.03514
/*50  */     if (buf_size <= 6 || *buf != 0x0f) {                                                 // (6) 0.03905
/*52  */         av_dlog(avctx, "incomplete or broken packet");                                   // (4) 0.04296
/*54  */         return -1;                                                                       // (22) 0.02148
/*56  */     }                                                                                    // (30) 0.00781
/*60  */     p = buf;                                                                             // (27) 0.01367
/*62  */     p_end = buf + buf_size;                                                              // (18) 0.02539
/*66  */     while (p_end - p >= 6 && *p == 0x0f) {                                               // (3) 0.04297
/*68  */         p += 1;                                                                          // (20) 0.02148
/*70  */         segment_type = *p++;                                                             // (16) 0.02738
/*72  */         page_id = AV_RB16(p);                                                            // (9) 0.03517
/*74  */         p += 2;                                                                          // (21) 0.02148
/*76  */         segment_length = AV_RB16(p);                                                     // 0.0
/*78  */         p += 2;                                                                          // 0.0
/*82  */         if (p_end - p < segment_length) {                                                // 0.0
/*84  */             av_dlog(avctx, "incomplete or broken packet");                               // 0.0
/*86  */             return -1;                                                                   // 0.0
/*88  */         }                                                                                // 0.0
/*92  */         if (page_id == ctx->composition_id || page_id == ctx->ancillary_id ||            // 0.0
/*94  */             ctx->composition_id == -1 || ctx->ancillary_id == -1) {                      // 0.0
/*96  */             switch (segment_type) {                                                      // 0.0
/*98  */             case DVBSUB_PAGE_SEGMENT:                                                    // 0.0
/*100 */                 dvbsub_parse_page_segment(avctx, p, segment_length);                     // 0.0
/*102 */                 break;                                                                   // 0.0
/*104 */             case DVBSUB_REGION_SEGMENT:                                                  // 0.0
/*106 */                 dvbsub_parse_region_segment(avctx, p, segment_length);                   // 0.0
/*108 */                 break;                                                                   // 0.0
/*110 */             case DVBSUB_CLUT_SEGMENT:                                                    // 0.0
/*112 */                 dvbsub_parse_clut_segment(avctx, p, segment_length);                     // 0.0
/*114 */                 break;                                                                   // 0.0
/*116 */             case DVBSUB_OBJECT_SEGMENT:                                                  // 0.0
/*118 */                 dvbsub_parse_object_segment(avctx, p, segment_length);                   // 0.0
/*120 */                 break;                                                                   // 0.0
/*122 */             case DVBSUB_DISPLAYDEFINITION_SEGMENT:                                       // 0.0
/*124 */                 dvbsub_parse_display_definition_segment(avctx, p, segment_length);       // 0.0
/*126 */                 break;                                                                   // 0.0
/*128 */             case DVBSUB_DISPLAY_SEGMENT:                                                 // 0.0
/*130 */                 *data_size = dvbsub_display_end_segment(avctx, p, segment_length, sub);  // 0.0
/*132 */                 break;                                                                   // 0.0
/*134 */             default:                                                                     // 0.0
/*136 */                 av_dlog(avctx, "Subtitling segment type 0x%x, page id %d, length %d\n",  // 0.0
/*138 */                         segment_type, page_id, segment_length);                          // 0.0
/*140 */                 break;                                                                   // 0.0
/*142 */             }                                                                            // 0.0
/*144 */         }                                                                                // 0.0
/*148 */         p += segment_length;                                                             // 0.0
/*150 */     }                                                                                    // 0.0
/*154 */     return p - buf;                                                                      // 0.0
/*156 */ }                                                                                        // 0.0
