// commit message FFmpeg@7effbee66c (target=1, prob=0.99909747, correct=True): Mark truncated packets as corrupt in av_get_packet.
/*0  */ static int sox_read_packet(AVFormatContext *s,             // (3) 0.07656
/*2  */                            AVPacket *pkt)                  // (0) 0.1579
/*4  */ {                                                          // (13) 0.004785
/*6  */     int ret, size;                                         // (10) 0.03828
/*10 */     if (url_feof(s->pb))                                   // (6) 0.06699
/*12 */         return AVERROR_EOF;                                // (4) 0.07177
/*16 */     size = SOX_SAMPLES*s->streams[0]->codec->block_align;  // (1) 0.1292
/*18 */     ret = av_get_packet(s->pb, pkt, size);                 // (2) 0.1005
/*20 */     if (ret < 0)                                           // (9) 0.04306
/*22 */         return AVERROR(EIO);                               // (5) 0.07177
/*25 */     pkt->stream_index = 0;                                 // (7) 0.05742
/*27 */     pkt->size = ret;                                       // (8) 0.04785
/*31 */     return 0;                                              // (11) 0.02871
/*33 */ }                                                          // (12) 0.004785
