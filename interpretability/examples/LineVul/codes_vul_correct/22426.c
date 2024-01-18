// commit message FFmpeg@c0175fa92b (target=1, prob=0.5289117, correct=True): idroqdec: fix leaking pkt on failure
/*0   */ static int roq_read_packet(AVFormatContext *s,                                                             // (14) 0.03125
/*2   */                            AVPacket *pkt)                                                                  // (1) 0.06445
/*4   */ {                                                                                                          // (26) 0.001954
/*6   */     RoqDemuxContext *roq = s->priv_data;                                                                   // (12) 0.03516
/*8   */     AVIOContext *pb = s->pb;                                                                               // (17) 0.02539
/*10  */     int ret = 0;                                                                                           // (25) 0.01562
/*12  */     unsigned int chunk_size;                                                                               // (23) 0.01758
/*14  */     unsigned int chunk_type;                                                                               // (24) 0.01758
/*16  */     unsigned int codebook_size;                                                                            // (22) 0.01953
/*18  */     unsigned char preamble[RoQ_CHUNK_PREAMBLE_SIZE];                                                       // (4) 0.04297
/*20  */     int packet_read = 0;                                                                                   // (21) 0.01953
/*22  */     int64_t codebook_offset;                                                                               // (19) 0.02344
/*26  */     while (!packet_read) {                                                                                 // (20) 0.02148
/*30  */         if (avio_feof(s->pb))                                                                              // (9) 0.03711
/*32  */             return AVERROR(EIO);                                                                           // (11) 0.03711
/*36  */         /* get the next chunk preamble */                                                                  // (15) 0.03125
/*38  */         if ((ret = avio_read(pb, preamble, RoQ_CHUNK_PREAMBLE_SIZE)) !=                                    // (0) 0.07031
/*40  */             RoQ_CHUNK_PREAMBLE_SIZE)                                                                       // (3) 0.04687
/*42  */             return AVERROR(EIO);                                                                           // (10) 0.03711
/*46  */         chunk_type = AV_RL16(&preamble[0]);                                                                // (6) 0.04297
/*48  */         chunk_size = AV_RL32(&preamble[2]);                                                                // (7) 0.04297
/*50  */         if(chunk_size > INT_MAX)                                                                           // (13) 0.03516
/*52  */             return AVERROR_INVALIDDATA;                                                                    // (8) 0.04102
/*56  */         chunk_size = ffio_limit(pb, chunk_size);                                                           // (5) 0.04297
/*60  */         switch (chunk_type) {                                                                              // (16) 0.0293
/*64  */         case RoQ_INFO:                                                                                     // (18) 0.02539
/*66  */             if (roq->video_stream_index == -1) {                                                           // (2) 0.05078
/*68  */                 AVStream *st = avformat_new_stream(s, NULL);                                               // 0.0
/*70  */                 if (!st)                                                                                   // 0.0
/*72  */                     return AVERROR(ENOMEM);                                                                // 0.0
/*74  */                 avpriv_set_pts_info(st, 63, 1, roq->frame_rate);                                           // 0.0
/*76  */                 roq->video_stream_index = st->index;                                                       // 0.0
/*78  */                 st->codecpar->codec_type   = AVMEDIA_TYPE_VIDEO;                                           // 0.0
/*80  */                 st->codecpar->codec_id     = AV_CODEC_ID_ROQ;                                              // 0.0
/*82  */                 st->codecpar->codec_tag    = 0;  /* no fourcc */                                           // 0.0
/*86  */                 if (avio_read(pb, preamble, RoQ_CHUNK_PREAMBLE_SIZE) != RoQ_CHUNK_PREAMBLE_SIZE)           // 0.0
/*88  */                     return AVERROR(EIO);                                                                   // 0.0
/*90  */                 st->codecpar->width  = roq->width  = AV_RL16(preamble);                                    // 0.0
/*92  */                 st->codecpar->height = roq->height = AV_RL16(preamble + 2);                                // 0.0
/*94  */                 break;                                                                                     // 0.0
/*96  */             }                                                                                              // 0.0
/*98  */             /* don't care about this chunk anymore */                                                      // 0.0
/*100 */             avio_skip(pb, RoQ_CHUNK_PREAMBLE_SIZE);                                                        // 0.0
/*102 */             break;                                                                                         // 0.0
/*106 */         case RoQ_QUAD_CODEBOOK:                                                                            // 0.0
/*108 */             if (roq->video_stream_index < 0)                                                               // 0.0
/*110 */                 return AVERROR_INVALIDDATA;                                                                // 0.0
/*112 */             /* packet needs to contain both this codebook and next VQ chunk */                             // 0.0
/*114 */             codebook_offset = avio_tell(pb) - RoQ_CHUNK_PREAMBLE_SIZE;                                     // 0.0
/*116 */             codebook_size = chunk_size;                                                                    // 0.0
/*118 */             avio_skip(pb, codebook_size);                                                                  // 0.0
/*120 */             if (avio_read(pb, preamble, RoQ_CHUNK_PREAMBLE_SIZE) !=                                        // 0.0
/*122 */                 RoQ_CHUNK_PREAMBLE_SIZE)                                                                   // 0.0
/*124 */                 return AVERROR(EIO);                                                                       // 0.0
/*126 */             chunk_size = AV_RL32(&preamble[2]) + RoQ_CHUNK_PREAMBLE_SIZE * 2 +                             // 0.0
/*128 */                 codebook_size;                                                                             // 0.0
/*132 */             if (chunk_size > INT_MAX)                                                                      // 0.0
/*134 */                 return AVERROR_INVALIDDATA;                                                                // 0.0
/*138 */             /* rewind */                                                                                   // 0.0
/*140 */             avio_seek(pb, codebook_offset, SEEK_SET);                                                      // 0.0
/*144 */             /* load up the packet */                                                                       // 0.0
/*146 */             ret= av_get_packet(pb, pkt, chunk_size);                                                       // 0.0
/*148 */             if (ret != chunk_size)                                                                         // 0.0
/*150 */                 return AVERROR(EIO);                                                                       // 0.0
/*152 */             pkt->stream_index = roq->video_stream_index;                                                   // 0.0
/*154 */             pkt->pts = roq->video_pts++;                                                                   // 0.0
/*158 */             packet_read = 1;                                                                               // 0.0
/*160 */             break;                                                                                         // 0.0
/*164 */         case RoQ_SOUND_MONO:                                                                               // 0.0
/*166 */         case RoQ_SOUND_STEREO:                                                                             // 0.0
/*168 */             if (roq->audio_stream_index == -1) {                                                           // 0.0
/*170 */                 AVStream *st = avformat_new_stream(s, NULL);                                               // 0.0
/*172 */                 if (!st)                                                                                   // 0.0
/*174 */                     return AVERROR(ENOMEM);                                                                // 0.0
/*176 */                 avpriv_set_pts_info(st, 32, 1, RoQ_AUDIO_SAMPLE_RATE);                                     // 0.0
/*178 */                 roq->audio_stream_index = st->index;                                                       // 0.0
/*180 */                 st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;                                             // 0.0
/*182 */                 st->codecpar->codec_id = AV_CODEC_ID_ROQ_DPCM;                                             // 0.0
/*184 */                 st->codecpar->codec_tag = 0;  /* no tag */                                                 // 0.0
/*186 */                 if (chunk_type == RoQ_SOUND_STEREO) {                                                      // 0.0
/*188 */                     st->codecpar->channels       = 2;                                                      // 0.0
/*190 */                     st->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;                                    // 0.0
/*192 */                 } else {                                                                                   // 0.0
/*194 */                     st->codecpar->channels       = 1;                                                      // 0.0
/*196 */                     st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;                                      // 0.0
/*198 */                 }                                                                                          // 0.0
/*200 */                 roq->audio_channels    = st->codecpar->channels;                                           // 0.0
/*202 */                 st->codecpar->sample_rate = RoQ_AUDIO_SAMPLE_RATE;                                         // 0.0
/*204 */                 st->codecpar->bits_per_coded_sample = 16;                                                  // 0.0
/*206 */                 st->codecpar->bit_rate = st->codecpar->channels * st->codecpar->sample_rate *              // 0.0
/*208 */                     st->codecpar->bits_per_coded_sample;                                                   // 0.0
/*210 */                 st->codecpar->block_align = st->codecpar->channels * st->codecpar->bits_per_coded_sample;  // 0.0
/*212 */             }                                                                                              // 0.0
/*214 */         case RoQ_QUAD_VQ:                                                                                  // 0.0
/*216 */             if (chunk_type == RoQ_QUAD_VQ) {                                                               // 0.0
/*218 */                 if (roq->video_stream_index < 0)                                                           // 0.0
/*220 */                     return AVERROR_INVALIDDATA;                                                            // 0.0
/*222 */             }                                                                                              // 0.0
/*226 */             /* load up the packet */                                                                       // 0.0
/*228 */             if (av_new_packet(pkt, chunk_size + RoQ_CHUNK_PREAMBLE_SIZE))                                  // 0.0
/*230 */                 return AVERROR(EIO);                                                                       // 0.0
/*232 */             /* copy over preamble */                                                                       // 0.0
/*234 */             memcpy(pkt->data, preamble, RoQ_CHUNK_PREAMBLE_SIZE);                                          // 0.0
/*238 */             if (chunk_type == RoQ_QUAD_VQ) {                                                               // 0.0
/*240 */                 pkt->stream_index = roq->video_stream_index;                                               // 0.0
/*242 */                 pkt->pts = roq->video_pts++;                                                               // 0.0
/*244 */             } else {                                                                                       // 0.0
/*246 */                 pkt->stream_index = roq->audio_stream_index;                                               // 0.0
/*248 */                 pkt->pts = roq->audio_frame_count;                                                         // 0.0
/*250 */                 roq->audio_frame_count += (chunk_size / roq->audio_channels);                              // 0.0
/*252 */             }                                                                                              // 0.0
/*256 */             pkt->pos= avio_tell(pb);                                                                       // 0.0
/*258 */             ret = avio_read(pb, pkt->data + RoQ_CHUNK_PREAMBLE_SIZE,                                       // 0.0
/*260 */                 chunk_size);                                                                               // 0.0
/*262 */             if (ret != chunk_size)                                                                         // 0.0
/*264 */                 ret = AVERROR(EIO);                                                                        // 0.0
/*268 */             packet_read = 1;                                                                               // 0.0
/*270 */             break;                                                                                         // 0.0
/*274 */         default:                                                                                           // 0.0
/*276 */             av_log(s, AV_LOG_ERROR, "  unknown RoQ chunk (%04X)\n", chunk_type);                           // 0.0
/*278 */             return AVERROR_INVALIDDATA;                                                                    // 0.0
/*280 */         }                                                                                                  // 0.0
/*282 */     }                                                                                                      // 0.0
/*286 */     return ret;                                                                                            // 0.0
/*288 */ }                                                                                                          // 0.0
