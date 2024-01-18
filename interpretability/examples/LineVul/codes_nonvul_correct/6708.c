// commit message FFmpeg@7b94df232a (target=0, prob=0.45306703, correct=True): avcodec/srtdec: Check ff_htmlmarkup_to_ass() return code
/*0  */ static int srt_decode_frame(AVCodecContext *avctx,                                            // (12) 0.03614
/*2  */                             void *data, int *got_sub_ptr, AVPacket *avpkt)                    // (0) 0.09438
/*4  */ {                                                                                             // (24) 0.002008
/*6  */     AVSubtitle *sub = data;                                                                   // (17) 0.02209
/*8  */     AVBPrint buffer;                                                                          // (21) 0.01606
/*10 */     int x1 = -1, y1 = -1, x2 = -1, y2 = -1;                                                   // (4) 0.05622
/*12 */     int size, ret;                                                                            // (22) 0.01606
/*14 */     const uint8_t *p = av_packet_get_side_data(avpkt, AV_PKT_DATA_SUBTITLE_POSITION, &size);  // (1) 0.08835
/*16 */     FFASSDecoderContext *s = avctx->priv_data;                                                // (9) 0.03815
/*20 */     if (p && size == 16) {                                                                    // (16) 0.0241
/*22 */         x1 = AV_RL32(p     );                                                                 // (6) 0.04217
/*24 */         y1 = AV_RL32(p +  4);                                                                 // (7) 0.04016
/*26 */         x2 = AV_RL32(p +  8);                                                                 // (8) 0.04016
/*28 */         y2 = AV_RL32(p + 12);                                                                 // (10) 0.03815
/*30 */     }                                                                                         // (23) 0.008032
/*34 */     if (avpkt->size <= 0)                                                                     // (15) 0.0261
/*36 */         return avpkt->size;                                                                   // (14) 0.02811
/*40 */     av_bprint_init(&buffer, 0, AV_BPRINT_SIZE_UNLIMITED);                                     // (5) 0.05422
/*44 */     srt_to_ass(avctx, &buffer, avpkt->data, x1, y1, x2, y2);                                  // (2) 0.06827
/*46 */     ret = ff_ass_add_rect(sub, buffer.str, s->readorder++, 0, NULL, NULL);                    // (3) 0.06225
/*48 */     av_bprint_finalize(&buffer, NULL);                                                        // (13) 0.03012
/*50 */     if (ret < 0)                                                                              // (20) 0.01807
/*52 */         return ret;                                                                           // (18) 0.02008
/*56 */     *got_sub_ptr = sub->num_rects > 0;                                                        // (11) 0.03815
/*58 */     return avpkt->size;                                                                       // (19) 0.02008
/*60 */ }                                                                                             // (25) 0.002008
