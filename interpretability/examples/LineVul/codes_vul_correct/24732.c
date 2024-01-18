// commit message FFmpeg@93c39db5f1 (target=1, prob=0.9990375, correct=True): aiff: check block_align in aiff_read_packet
/*0  */ static int aiff_read_packet(AVFormatContext *s,                                                                            // (11) 0.03125
/*1  */                             AVPacket *pkt)                                                                                 // (1) 0.06641
/*2  */ {                                                                                                                          // (28) 0.001953
/*3  */     AVStream *st = s->streams[0];                                                                                          // (13) 0.0293
/*4  */     AIFFInputContext *aiff = s->priv_data;                                                                                 // (7) 0.0332
/*5  */     int64_t max_size;                                                                                                      // (19) 0.02148
/*6  */     int res, size;                                                                                                         // (26) 0.01562
/*7  */     /* calculate size of remaining data */                                                                                 // (21) 0.01953
/*8  */     max_size = aiff->data_end - avio_tell(s->pb);                                                                          // (3) 0.04492
/*9  */     if (max_size <= 0)                                                                                                     // (20) 0.02148
/*10 */         return AVERROR_EOF;                                                                                                // (15) 0.0293
/*11 */     /* Now for that packet */                                                                                              // (23) 0.01758
/*12 */     switch (st->codecpar->codec_id) {                                                                                      // (9) 0.0332
/*13 */     case AV_CODEC_ID_ADPCM_IMA_QT:                                                                                         // (4) 0.04297
/*14 */     case AV_CODEC_ID_GSM:                                                                                                  // (14) 0.0293
/*15 */     case AV_CODEC_ID_QDM2:                                                                                                 // (12) 0.03125
/*16 */     case AV_CODEC_ID_QCELP:                                                                                                // (10) 0.0332
/*17 */         size = st->codecpar->block_align;                                                                                  // (6) 0.03711
/*18 */         break;                                                                                                             // (25) 0.01758
/*19 */     default:                                                                                                               // (27) 0.009766
/*20 */         size = st->codecpar->block_align ? (MAX_SIZE / st->codecpar->block_align) * st->codecpar->block_align : MAX_SIZE;  // (0) 0.0957
/*21 */     size = FFMIN(max_size, size);                                                                                          // (16) 0.02734
/*22 */     res = av_get_packet(s->pb, pkt, size);                                                                                 // (5) 0.04102
/*23 */     if (res < 0)                                                                                                           // (24) 0.01758
/*24 */         return res;                                                                                                        // (22) 0.01953
/*25 */     if (size >= st->codecpar->block_align)                                                                                 // (8) 0.0332
/*26 */         pkt->flags &= ~AV_PKT_FLAG_CORRUPT;                                                                                // (2) 0.05078
/*27 */     /* Only one stream in an AIFF file */                                                                                  // (17) 0.02539
/*28 */     pkt->stream_index = 0;                                                                                                 // (18) 0.02344
/*29 */     pkt->duration     = (res / st->codecpar->block_align) * aiff->block_duration;                                          // 0.0
/*30 */     return 0;                                                                                                              // 0.0
