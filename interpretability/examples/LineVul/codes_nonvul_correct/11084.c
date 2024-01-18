// commit message FFmpeg@3c895fc098 (target=0, prob=0.47862008, correct=True): correctly interleave packets during encoding dts/pts fixed for streamcopy dont use coded_frame->key_frame hack in muxers, use AVPacket.flags instead
/*0  */ static void compute_frame_duration(int *pnum, int *pden,                     // (7) 0.03939
/*2  */                                    AVFormatContext *s, AVStream *st,         // (1) 0.1007
/*4  */                                    AVCodecParserContext *pc, AVPacket *pkt)  // (0) 0.1072
/*6  */ {                                                                            // (25) 0.002188
/*8  */     int frame_size;                                                          // (21) 0.01751
/*12 */     *pnum = 0;                                                               // (16) 0.01969
/*14 */     *pden = 0;                                                               // (17) 0.01969
/*16 */     switch(st->codec.codec_type) {                                           // (10) 0.03501
/*18 */     case CODEC_TYPE_VIDEO:                                                   // (15) 0.02626
/*20 */         *pnum = st->codec.frame_rate_base;                                   // (4) 0.04814
/*22 */         *pden = st->codec.frame_rate;                                        // (5) 0.04376
/*24 */         if (pc && pc->repeat_pict) {                                         // (8) 0.03939
/*26 */             *pden *= 2;                                                      // (9) 0.03939
/*28 */             *pnum = (*pnum) * (2 + pc->repeat_pict);                         // (2) 0.06346
/*30 */         }                                                                    // (22) 0.01751
/*32 */         break;                                                               // (18) 0.01969
/*34 */     case CODEC_TYPE_AUDIO:                                                   // (13) 0.02845
/*36 */         frame_size = get_audio_frame_size(&st->codec, pkt->size);            // (3) 0.06346
/*38 */         if (frame_size < 0)                                                  // (11) 0.03282
/*40 */             break;                                                           // (14) 0.02845
/*42 */         *pnum = frame_size;                                                  // (12) 0.03282
/*44 */         *pden = st->codec.sample_rate;                                       // (6) 0.04376
/*46 */         break;                                                               // (19) 0.01969
/*48 */     default:                                                                 // (23) 0.01094
/*50 */         break;                                                               // (20) 0.01969
/*52 */     }                                                                        // (24) 0.008753
/*54 */ }                                                                            // (26) 0.002188
