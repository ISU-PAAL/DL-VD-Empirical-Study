// commit message FFmpeg@273e6af47b (target=0, prob=0.4994598, correct=True): ea: check chunk_size for validity.
/*0   */ static int ea_read_packet(AVFormatContext *s,                                   // (11) 0.03129
/*2   */                           AVPacket *pkt)                                        // (2) 0.06226
/*4   */ {                                                                               // (26) 0.002553
/*6   */     EaDemuxContext *ea = s->priv_data;                                          // (8) 0.03341
/*8   */     AVIOContext *pb = s->pb;                                                    // (19) 0.02529
/*10  */     int ret = 0;                                                                // (25) 0.01558
/*12  */     int packet_read = 0;                                                        // (23) 0.01949
/*14  */     unsigned int chunk_type, chunk_size;                                        // (18) 0.0253
/*16  */     int key = 0;                                                                // (24) 0.01561
/*18  */     int av_uninit(num_samples);                                                 // (13) 0.02757
/*22  */     while (!packet_read) {                                                      // (21) 0.02182
/*24  */         chunk_type = avio_rl32(pb);                                             // (7) 0.0371
/*26  */         chunk_size = (ea->big_endian ? avio_rb32(pb) : avio_rl32(pb)) - 8;      // (0) 0.07583
/*30  */         switch (chunk_type) {                                                   // (12) 0.02917
/*32  */         /* audio data */                                                        // (22) 0.02139
/*34  */         case ISNh_TAG:                                                          // (14) 0.02721
/*36  */             /* header chunk also contains data; skip over the header portion*/  // (4) 0.04668
/*38  */             avio_skip(pb, 32);                                                  // (6) 0.03888
/*40  */             chunk_size -= 32;                                                   // (9) 0.03305
/*42  */         case ISNd_TAG:                                                          // (15) 0.02721
/*44  */         case SCDl_TAG:                                                          // (16) 0.02721
/*46  */         case SNDC_TAG:                                                          // (17) 0.02721
/*48  */         case SDEN_TAG:                                                          // (20) 0.02527
/*50  */             if (!ea->audio_codec) {                                             // (5) 0.04083
/*52  */                 avio_skip(pb, chunk_size);                                      // (3) 0.05054
/*54  */                 break;                                                          // (10) 0.03304
/*56  */             } else if (ea->audio_codec == CODEC_ID_PCM_S16LE_PLANAR ||          // (1) 0.07583
/*58  */                        ea->audio_codec == CODEC_ID_MP3) {                       // 0.0
/*60  */                 num_samples = avio_rl32(pb);                                    // 0.0
/*62  */                 avio_skip(pb, 8);                                               // 0.0
/*64  */                 chunk_size -= 12;                                               // 0.0
/*66  */             }                                                                   // 0.0
/*68  */             ret = av_get_packet(pb, pkt, chunk_size);                           // 0.0
/*70  */             if (ret < 0)                                                        // 0.0
/*72  */                 return ret;                                                     // 0.0
/*74  */             pkt->stream_index = ea->audio_stream_index;                         // 0.0
/*78  */             switch (ea->audio_codec) {                                          // 0.0
/*80  */             case CODEC_ID_ADPCM_EA:                                             // 0.0
/*82  */             case CODEC_ID_ADPCM_EA_R1:                                          // 0.0
/*84  */             case CODEC_ID_ADPCM_EA_R2:                                          // 0.0
/*86  */             case CODEC_ID_ADPCM_IMA_EA_EACS:                                    // 0.0
/*88  */                 pkt->duration = AV_RL32(pkt->data);                             // 0.0
/*90  */                 break;                                                          // 0.0
/*92  */             case CODEC_ID_ADPCM_EA_R3:                                          // 0.0
/*94  */                 pkt->duration = AV_RB32(pkt->data);                             // 0.0
/*96  */                 break;                                                          // 0.0
/*98  */             case CODEC_ID_ADPCM_IMA_EA_SEAD:                                    // 0.0
/*100 */                 pkt->duration = ret * 2 / ea->num_channels;                     // 0.0
/*102 */                 break;                                                          // 0.0
/*104 */             case CODEC_ID_PCM_S16LE_PLANAR:                                     // 0.0
/*106 */             case CODEC_ID_MP3:                                                  // 0.0
/*108 */                 pkt->duration = num_samples;                                    // 0.0
/*110 */                 break;                                                          // 0.0
/*112 */             default:                                                            // 0.0
/*114 */                 pkt->duration = chunk_size / (ea->bytes * ea->num_channels);    // 0.0
/*116 */             }                                                                   // 0.0
/*120 */             packet_read = 1;                                                    // 0.0
/*122 */             break;                                                              // 0.0
/*126 */         /* ending tag */                                                        // 0.0
/*128 */         case 0:                                                                 // 0.0
/*130 */         case ISNe_TAG:                                                          // 0.0
/*132 */         case SCEl_TAG:                                                          // 0.0
/*134 */         case SEND_TAG:                                                          // 0.0
/*136 */         case SEEN_TAG:                                                          // 0.0
/*138 */             ret = AVERROR(EIO);                                                 // 0.0
/*140 */             packet_read = 1;                                                    // 0.0
/*142 */             break;                                                              // 0.0
/*146 */         case MVIh_TAG:                                                          // 0.0
/*148 */         case kVGT_TAG:                                                          // 0.0
/*150 */         case pQGT_TAG:                                                          // 0.0
/*152 */         case TGQs_TAG:                                                          // 0.0
/*154 */         case MADk_TAG:                                                          // 0.0
/*156 */             key = AV_PKT_FLAG_KEY;                                              // 0.0
/*158 */         case MVIf_TAG:                                                          // 0.0
/*160 */         case fVGT_TAG:                                                          // 0.0
/*162 */         case MADm_TAG:                                                          // 0.0
/*164 */         case MADe_TAG:                                                          // 0.0
/*166 */             avio_seek(pb, -8, SEEK_CUR);     // include chunk preamble          // 0.0
/*168 */             chunk_size += 8;                                                    // 0.0
/*170 */             goto get_video_packet;                                              // 0.0
/*174 */         case mTCD_TAG:                                                          // 0.0
/*176 */             avio_skip(pb, 8);  // skip ea dct header                            // 0.0
/*178 */             chunk_size -= 8;                                                    // 0.0
/*180 */             goto get_video_packet;                                              // 0.0
/*184 */         case MV0K_TAG:                                                          // 0.0
/*186 */         case MPCh_TAG:                                                          // 0.0
/*188 */         case pIQT_TAG:                                                          // 0.0
/*190 */             key = AV_PKT_FLAG_KEY;                                              // 0.0
/*192 */         case MV0F_TAG:                                                          // 0.0
/*194 */ get_video_packet:                                                               // 0.0
/*196 */             ret = av_get_packet(pb, pkt, chunk_size);                           // 0.0
/*198 */             if (ret < 0)                                                        // 0.0
/*200 */                 return ret;                                                     // 0.0
/*202 */             pkt->stream_index = ea->video_stream_index;                         // 0.0
/*204 */             pkt->flags |= key;                                                  // 0.0
/*206 */             packet_read = 1;                                                    // 0.0
/*208 */             break;                                                              // 0.0
/*212 */         default:                                                                // 0.0
/*214 */             avio_skip(pb, chunk_size);                                          // 0.0
/*216 */             break;                                                              // 0.0
/*218 */         }                                                                       // 0.0
/*220 */     }                                                                           // 0.0
/*224 */     return ret;                                                                 // 0.0
/*226 */ }                                                                               // 0.0
