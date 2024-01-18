// commit message FFmpeg@e8c4df40e3 (target=1, prob=0.3074574, correct=False): check for malloc failure
/*0   */ static int mov_write_packet(AVFormatContext *s, AVPacket *pkt)                                                    // (6) 0.04297
/*2   */ {                                                                                                                 // (25) 0.001954
/*4   */     MOVContext *mov = s->priv_data;                                                                               // (15) 0.0293
/*6   */     ByteIOContext *pb = s->pb;                                                                                    // (17) 0.02539
/*8   */     MOVTrack *trk = &mov->tracks[pkt->stream_index];                                                              // (7) 0.04297
/*10  */     AVCodecContext *enc = trk->enc;                                                                               // (14) 0.0293
/*12  */     unsigned int samplesInChunk = 0;                                                                              // (19) 0.02344
/*14  */     int size= pkt->size;                                                                                          // (21) 0.02148
/*18  */     if (url_is_streamed(s->pb)) return 0; /* Can't handle that */                                                 // (3) 0.04883
/*20  */     if (!size) return 0; /* Discard 0 sized packets */                                                            // (11) 0.0332
/*24  */     if (enc->codec_id == CODEC_ID_AMR_NB) {                                                                       // (4) 0.04687
/*26  */         /* We must find out how many AMR blocks there are in one packet */                                        // (5) 0.04492
/*28  */         static uint16_t packed_size[16] =                                                                         // (10) 0.03711
/*30  */             {13, 14, 16, 18, 20, 21, 27, 32, 6, 0, 0, 0, 0, 0, 0, 0};                                             // (1) 0.08594
/*32  */         int len = 0;                                                                                              // (20) 0.02344
/*36  */         while (len < size && samplesInChunk < 100) {                                                              // (8) 0.04102
/*38  */             len += packed_size[(pkt->data[len] >> 3) & 0x0F];                                                     // (2) 0.06641
/*40  */             samplesInChunk++;                                                                                     // (13) 0.03125
/*42  */         }                                                                                                         // (23) 0.01562
/*44  */         if(samplesInChunk > 1){                                                                                   // (12) 0.0332
/*46  */             av_log(s, AV_LOG_ERROR, "fatal error, input is not a single packet, implement a AVParser for it\n");  // (0) 0.08789
/*48  */             return -1;                                                                                            // (16) 0.0293
/*50  */         }                                                                                                         // (22) 0.01562
/*52  */     } else if (trk->sampleSize)                                                                                   // (18) 0.02539
/*54  */         samplesInChunk = size/trk->sampleSize;                                                                    // (9) 0.03906
/*56  */     else                                                                                                          // (24) 0.007812
/*58  */         samplesInChunk = 1;                                                                                       // 0.0
/*62  */     /* copy extradata if it exists */                                                                             // 0.0
/*64  */     if (trk->vosLen == 0 && enc->extradata_size > 0) {                                                            // 0.0
/*66  */         trk->vosLen = enc->extradata_size;                                                                        // 0.0
/*68  */         trk->vosData = av_malloc(trk->vosLen);                                                                    // 0.0
/*70  */         memcpy(trk->vosData, enc->extradata, trk->vosLen);                                                        // 0.0
/*72  */     }                                                                                                             // 0.0
/*76  */     if (enc->codec_id == CODEC_ID_H264 && trk->vosLen > 0 && *(uint8_t *)trk->vosData != 1) {                     // 0.0
/*78  */         /* from x264 or from bytestream h264 */                                                                   // 0.0
/*80  */         /* nal reformating needed */                                                                              // 0.0
/*82  */         int ret = ff_avc_parse_nal_units(pkt->data, &pkt->data, &pkt->size);                                      // 0.0
/*84  */         if (ret < 0)                                                                                              // 0.0
/*86  */             return ret;                                                                                           // 0.0
/*88  */         assert(pkt->size);                                                                                        // 0.0
/*90  */         size = pkt->size;                                                                                         // 0.0
/*92  */     } else if (enc->codec_id == CODEC_ID_DNXHD && !trk->vosLen) {                                                 // 0.0
/*94  */         /* copy frame to create needed atoms */                                                                   // 0.0
/*96  */         trk->vosLen = size;                                                                                       // 0.0
/*98  */         trk->vosData = av_malloc(size);                                                                           // 0.0
/*102 */         memcpy(trk->vosData, pkt->data, size);                                                                    // 0.0
/*104 */     }                                                                                                             // 0.0
/*108 */     if (!(trk->entry % MOV_INDEX_CLUSTER_SIZE)) {                                                                 // 0.0
/*110 */         trk->cluster = av_realloc(trk->cluster, (trk->entry + MOV_INDEX_CLUSTER_SIZE) * sizeof(*trk->cluster));   // 0.0
/*112 */         if (!trk->cluster)                                                                                        // 0.0
/*114 */             return -1;                                                                                            // 0.0
/*116 */     }                                                                                                             // 0.0
/*120 */     trk->cluster[trk->entry].pos = url_ftell(pb);                                                                 // 0.0
/*122 */     trk->cluster[trk->entry].samplesInChunk = samplesInChunk;                                                     // 0.0
/*124 */     trk->cluster[trk->entry].size = size;                                                                         // 0.0
/*126 */     trk->cluster[trk->entry].entries = samplesInChunk;                                                            // 0.0
/*128 */     trk->cluster[trk->entry].dts = pkt->dts;                                                                      // 0.0
/*130 */     trk->trackDuration = pkt->dts - trk->cluster[0].dts + pkt->duration;                                          // 0.0
/*134 */     if (pkt->pts == AV_NOPTS_VALUE) {                                                                             // 0.0
/*136 */         av_log(s, AV_LOG_WARNING, "pts has no value\n");                                                          // 0.0
/*138 */         pkt->pts = pkt->dts;                                                                                      // 0.0
/*140 */     }                                                                                                             // 0.0
/*142 */     if (pkt->dts != pkt->pts)                                                                                     // 0.0
/*144 */         trk->hasBframes = 1;                                                                                      // 0.0
/*146 */     trk->cluster[trk->entry].cts = pkt->pts - pkt->dts;                                                           // 0.0
/*148 */     trk->cluster[trk->entry].key_frame = !!(pkt->flags & PKT_FLAG_KEY);                                           // 0.0
/*150 */     if(trk->cluster[trk->entry].key_frame)                                                                        // 0.0
/*152 */         trk->hasKeyframes++;                                                                                      // 0.0
/*154 */     trk->entry++;                                                                                                 // 0.0
/*156 */     trk->sampleCount += samplesInChunk;                                                                           // 0.0
/*158 */     mov->mdat_size += size;                                                                                       // 0.0
/*162 */     put_buffer(pb, pkt->data, size);                                                                              // 0.0
/*166 */     put_flush_packet(pb);                                                                                         // 0.0
/*168 */     return 0;                                                                                                     // 0.0
/*170 */ }                                                                                                                 // 0.0
