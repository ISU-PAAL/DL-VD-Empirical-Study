// commit message FFmpeg@77d2a1ca59 (target=1, prob=0.35369, correct=False): avformat/rmdec: when reading audio blocks, dont leave holes when reading fails
/*0   */ ff_rm_parse_packet (AVFormatContext *s, AVIOContext *pb,                                         // (13) 0.04102
/*2   */                     AVStream *st, RMStream *ast, int len, AVPacket *pkt,                         // (0) 0.07617
/*4   */                     int *seq, int flags, int64_t timestamp)                                      // (2) 0.0625
/*6   */ {                                                                                                // (21) 0.001953
/*8   */     RMDemuxContext *rm = s->priv_data;                                                           // (17) 0.03125
/*10  */     int ret;                                                                                     // (20) 0.01172
/*14  */     if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO) {                                           // (8) 0.04687
/*16  */         rm->current_stream= st->id;                                                              // (15) 0.0332
/*18  */         ret = rm_assemble_video_frame(s, pb, rm, ast, pkt, len, seq, &timestamp);                // (1) 0.07422
/*20  */         if(ret)                                                                                  // (19) 0.02148
/*22  */             return ret < 0 ? ret : -1; //got partial frame or error                              // (5) 0.05273
/*24  */     } else if (st->codec->codec_type == AVMEDIA_TYPE_AUDIO) {                                    // (6) 0.05273
/*26  */         if ((ast->deint_id == DEINT_ID_GENR) ||                                                  // (7) 0.04883
/*28  */             (ast->deint_id == DEINT_ID_INT4) ||                                                  // (4) 0.05469
/*30  */             (ast->deint_id == DEINT_ID_SIPR)) {                                                  // (3) 0.05664
/*32  */             int x;                                                                               // (18) 0.02734
/*34  */             int sps = ast->sub_packet_size;                                                      // (9) 0.04687
/*36  */             int cfs = ast->coded_framesize;                                                      // (12) 0.04297
/*38  */             int h = ast->sub_packet_h;                                                           // (11) 0.04492
/*40  */             int y = ast->sub_packet_cnt;                                                         // (10) 0.04687
/*42  */             int w = ast->audio_framesize;                                                        // (14) 0.04102
/*46  */             if (flags & 2)                                                                       // (16) 0.0332
/*48  */                 y = ast->sub_packet_cnt = 0;                                                     // 0.0
/*50  */             if (!y)                                                                              // 0.0
/*52  */                 ast->audiotimestamp = timestamp;                                                 // 0.0
/*56  */             switch (ast->deint_id) {                                                             // 0.0
/*58  */                 case DEINT_ID_INT4:                                                              // 0.0
/*60  */                     for (x = 0; x < h/2; x++)                                                    // 0.0
/*62  */                         avio_read(pb, ast->pkt.data+x*2*w+y*cfs, cfs);                           // 0.0
/*64  */                     break;                                                                       // 0.0
/*66  */                 case DEINT_ID_GENR:                                                              // 0.0
/*68  */                     for (x = 0; x < w/sps; x++)                                                  // 0.0
/*70  */                         avio_read(pb, ast->pkt.data+sps*(h*x+((h+1)/2)*(y&1)+(y>>1)), sps);      // 0.0
/*72  */                     break;                                                                       // 0.0
/*74  */                 case DEINT_ID_SIPR:                                                              // 0.0
/*76  */                     avio_read(pb, ast->pkt.data + y * w, w);                                     // 0.0
/*78  */                     break;                                                                       // 0.0
/*80  */             }                                                                                    // 0.0
/*84  */             if (++(ast->sub_packet_cnt) < h)                                                     // 0.0
/*86  */                 return -1;                                                                       // 0.0
/*88  */             if (ast->deint_id == DEINT_ID_SIPR)                                                  // 0.0
/*90  */                 ff_rm_reorder_sipr_data(ast->pkt.data, h, w);                                    // 0.0
/*94  */              ast->sub_packet_cnt = 0;                                                            // 0.0
/*96  */              rm->audio_stream_num = st->index;                                                   // 0.0
/*98  */              rm->audio_pkt_cnt = h * w / st->codec->block_align;                                 // 0.0
/*100 */         } else if ((ast->deint_id == DEINT_ID_VBRF) ||                                           // 0.0
/*102 */                    (ast->deint_id == DEINT_ID_VBRS)) {                                           // 0.0
/*104 */             int x;                                                                               // 0.0
/*106 */             rm->audio_stream_num = st->index;                                                    // 0.0
/*108 */             ast->sub_packet_cnt = (avio_rb16(pb) & 0xf0) >> 4;                                   // 0.0
/*110 */             if (ast->sub_packet_cnt) {                                                           // 0.0
/*112 */                 for (x = 0; x < ast->sub_packet_cnt; x++)                                        // 0.0
/*114 */                     ast->sub_packet_lengths[x] = avio_rb16(pb);                                  // 0.0
/*116 */                 rm->audio_pkt_cnt = ast->sub_packet_cnt;                                         // 0.0
/*118 */                 ast->audiotimestamp = timestamp;                                                 // 0.0
/*120 */             } else                                                                               // 0.0
/*122 */                 return -1;                                                                       // 0.0
/*124 */         } else {                                                                                 // 0.0
/*126 */             av_get_packet(pb, pkt, len);                                                         // 0.0
/*128 */             rm_ac3_swap_bytes(st, pkt);                                                          // 0.0
/*130 */         }                                                                                        // 0.0
/*132 */     } else                                                                                       // 0.0
/*134 */         av_get_packet(pb, pkt, len);                                                             // 0.0
/*138 */     pkt->stream_index = st->index;                                                               // 0.0
/*142 */ #if 0                                                                                            // 0.0
/*144 */     if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO) {                                           // 0.0
/*146 */         if(st->codec->codec_id == AV_CODEC_ID_RV20){                                             // 0.0
/*148 */             int seq= 128*(pkt->data[2]&0x7F) + (pkt->data[3]>>1);                                // 0.0
/*150 */             av_log(s, AV_LOG_DEBUG, "%d %"PRId64" %d\n", *timestamp, *timestamp*512LL/25, seq);  // 0.0
/*154 */             seq |= (timestamp&~0x3FFF);                                                          // 0.0
/*156 */             if(seq - timestamp >  0x2000) seq -= 0x4000;                                         // 0.0
/*158 */             if(seq - timestamp < -0x2000) seq += 0x4000;                                         // 0.0
/*160 */         }                                                                                        // 0.0
/*162 */     }                                                                                            // 0.0
/*164 */ #endif                                                                                           // 0.0
/*168 */     pkt->pts = timestamp;                                                                        // 0.0
/*170 */     if (flags & 2)                                                                               // 0.0
/*172 */         pkt->flags |= AV_PKT_FLAG_KEY;                                                           // 0.0
/*176 */     return st->codec->codec_type == AVMEDIA_TYPE_AUDIO ? rm->audio_pkt_cnt : 0;                  // 0.0
/*178 */ }                                                                                                // 0.0
