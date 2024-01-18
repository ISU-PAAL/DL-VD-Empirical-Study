// commit message FFmpeg@fe6eea99ef (target=1, prob=0.6416258, correct=True): nsvdec: don't ignore the return value of av_get_packet()
/*0   */ static int nsv_read_chunk(AVFormatContext *s, int fill_header)                                                           // (5) 0.04102
/*2   */ {                                                                                                                        // (29) 0.001953
/*4   */     NSVContext *nsv = s->priv_data;                                                                                      // (10) 0.03125
/*6   */     AVIOContext *pb = s->pb;                                                                                             // (15) 0.02539
/*8   */     AVStream *st[2] = {NULL, NULL};                                                                                      // (9) 0.03125
/*10  */     NSVStream *nst;                                                                                                      // (19) 0.01953
/*12  */     AVPacket *pkt;                                                                                                       // (18) 0.01953
/*14  */     int i, err = 0;                                                                                                      // (20) 0.01953
/*16  */     uint8_t auxcount; /* number of aux metadata, also 4 bits of vsize */                                                 // (4) 0.04492
/*18  */     uint32_t vsize;                                                                                                      // (22) 0.01953
/*20  */     uint16_t asize;                                                                                                      // (23) 0.01953
/*22  */     uint16_t auxsize;                                                                                                    // (21) 0.01953
/*26  */     if (nsv->ahead[0].data || nsv->ahead[1].data)                                                                        // (3) 0.04492
/*28  */         return 0; //-1; /* hey! eat what you've in your plate first! */                                                  // (2) 0.05273
/*32  */ null_chunk_retry:                                                                                                        // (28) 0.01563
/*34  */     if (pb->eof_reached)                                                                                                 // (14) 0.02539
/*36  */         return -1;                                                                                                       // (16) 0.02148
/*40  */     for (i = 0; i < NSV_MAX_RESYNC_TRIES && nsv->state < NSV_FOUND_NSVS && !err; i++)                                    // (0) 0.08203
/*42  */         err = nsv_resync(s);                                                                                             // (8) 0.0332
/*44  */     if (err < 0)                                                                                                         // (27) 0.01758
/*46  */         return err;                                                                                                      // (24) 0.01953
/*48  */     if (nsv->state == NSV_FOUND_NSVS)                                                                                    // (7) 0.03711
/*50  */         err = nsv_parse_NSVs_header(s);                                                                                  // (6) 0.04102
/*52  */     if (err < 0)                                                                                                         // (26) 0.01758
/*54  */         return err;                                                                                                      // (25) 0.01953
/*56  */     if (nsv->state != NSV_HAS_READ_NSVS && nsv->state != NSV_FOUND_BEEF)                                                 // (1) 0.07031
/*58  */         return -1;                                                                                                       // (17) 0.02148
/*62  */     auxcount = avio_r8(pb);                                                                                              // (13) 0.02734
/*64  */     vsize = avio_rl16(pb);                                                                                               // (11) 0.02734
/*66  */     asize = avio_rl16(pb);                                                                                               // (12) 0.02734
/*68  */     vsize = (vsize << 4) | (auxcount >> 4);                                                                              // 0.0
/*70  */     auxcount &= 0x0f;                                                                                                    // 0.0
/*72  */     av_log(s, AV_LOG_TRACE, "NSV CHUNK %"PRIu8" aux, %"PRIu32" bytes video, %"PRIu16" bytes audio\n",                    // 0.0
/*74  */            auxcount, vsize, asize);                                                                                      // 0.0
/*76  */     /* skip aux stuff */                                                                                                 // 0.0
/*78  */     for (i = 0; i < auxcount; i++) {                                                                                     // 0.0
/*80  */         uint32_t av_unused auxtag;                                                                                       // 0.0
/*82  */         auxsize = avio_rl16(pb);                                                                                         // 0.0
/*84  */         auxtag = avio_rl32(pb);                                                                                          // 0.0
/*86  */         avio_skip(pb, auxsize);                                                                                          // 0.0
/*88  */         vsize -= auxsize + sizeof(uint16_t) + sizeof(uint32_t); /* that's becoming brain-dead */                         // 0.0
/*90  */     }                                                                                                                    // 0.0
/*94  */     if (pb->eof_reached)                                                                                                 // 0.0
/*96  */         return -1;                                                                                                       // 0.0
/*98  */     if (!vsize && !asize) {                                                                                              // 0.0
/*100 */         nsv->state = NSV_UNSYNC;                                                                                         // 0.0
/*102 */         goto null_chunk_retry;                                                                                           // 0.0
/*104 */     }                                                                                                                    // 0.0
/*108 */     /* map back streams to v,a */                                                                                        // 0.0
/*110 */     if (s->nb_streams > 0)                                                                                               // 0.0
/*112 */         st[s->streams[0]->id] = s->streams[0];                                                                           // 0.0
/*114 */     if (s->nb_streams > 1)                                                                                               // 0.0
/*116 */         st[s->streams[1]->id] = s->streams[1];                                                                           // 0.0
/*120 */     if (vsize && st[NSV_ST_VIDEO]) {                                                                                     // 0.0
/*122 */         nst = st[NSV_ST_VIDEO]->priv_data;                                                                               // 0.0
/*124 */         pkt = &nsv->ahead[NSV_ST_VIDEO];                                                                                 // 0.0
/*126 */         av_get_packet(pb, pkt, vsize);                                                                                   // 0.0
/*128 */         pkt->stream_index = st[NSV_ST_VIDEO]->index;//NSV_ST_VIDEO;                                                      // 0.0
/*130 */         pkt->dts = nst->frame_offset;                                                                                    // 0.0
/*132 */         pkt->flags |= nsv->state == NSV_HAS_READ_NSVS ? AV_PKT_FLAG_KEY : 0; /* keyframe only likely on a sync frame */  // 0.0
/*134 */         for (i = 0; i < FFMIN(8, vsize); i++)                                                                            // 0.0
/*136 */             av_log(s, AV_LOG_TRACE, "NSV video: [%d] = %02"PRIx8"\n",                                                    // 0.0
/*138 */                    i, pkt->data[i]);                                                                                     // 0.0
/*140 */     }                                                                                                                    // 0.0
/*142 */     if(st[NSV_ST_VIDEO])                                                                                                 // 0.0
/*144 */         ((NSVStream*)st[NSV_ST_VIDEO]->priv_data)->frame_offset++;                                                       // 0.0
/*148 */     if (asize && st[NSV_ST_AUDIO]) {                                                                                     // 0.0
/*150 */         nst = st[NSV_ST_AUDIO]->priv_data;                                                                               // 0.0
/*152 */         pkt = &nsv->ahead[NSV_ST_AUDIO];                                                                                 // 0.0
/*154 */         /* read raw audio specific header on the first audio chunk... */                                                 // 0.0
/*156 */         /* on ALL audio chunks ?? seems so! */                                                                           // 0.0
/*158 */         if (asize && st[NSV_ST_AUDIO]->codecpar->codec_tag == MKTAG('P', 'C', 'M', ' ')/* && fill_header*/) {            // 0.0
/*160 */             uint8_t bps;                                                                                                 // 0.0
/*162 */             uint8_t channels;                                                                                            // 0.0
/*164 */             uint16_t samplerate;                                                                                         // 0.0
/*166 */             bps = avio_r8(pb);                                                                                           // 0.0
/*168 */             channels = avio_r8(pb);                                                                                      // 0.0
/*170 */             samplerate = avio_rl16(pb);                                                                                  // 0.0
/*172 */             if (!channels || !samplerate)                                                                                // 0.0
/*174 */                 return AVERROR_INVALIDDATA;                                                                              // 0.0
/*176 */             asize-=4;                                                                                                    // 0.0
/*178 */             av_log(s, AV_LOG_TRACE, "NSV RAWAUDIO: bps %"PRIu8", nchan %"PRIu8", srate %"PRIu16"\n",                     // 0.0
/*180 */                    bps, channels, samplerate);                                                                           // 0.0
/*182 */             if (fill_header) {                                                                                           // 0.0
/*184 */                 st[NSV_ST_AUDIO]->need_parsing = AVSTREAM_PARSE_NONE; /* we know everything */                           // 0.0
/*186 */                 if (bps != 16) {                                                                                         // 0.0
/*188 */                     av_log(s, AV_LOG_TRACE, "NSV AUDIO bit/sample != 16 (%"PRIu8")!!!\n", bps);                          // 0.0
/*190 */                 }                                                                                                        // 0.0
/*192 */                 bps /= channels; // ???                                                                                  // 0.0
/*194 */                 if (bps == 8)                                                                                            // 0.0
/*196 */                     st[NSV_ST_AUDIO]->codecpar->codec_id = AV_CODEC_ID_PCM_U8;                                           // 0.0
/*198 */                 samplerate /= 4;/* UGH ??? XXX */                                                                        // 0.0
/*200 */                 channels = 1;                                                                                            // 0.0
/*202 */                 st[NSV_ST_AUDIO]->codecpar->channels = channels;                                                         // 0.0
/*204 */                 st[NSV_ST_AUDIO]->codecpar->sample_rate = samplerate;                                                    // 0.0
/*206 */                 av_log(s, AV_LOG_TRACE, "NSV RAWAUDIO: bps %"PRIu8", nchan %"PRIu8", srate %"PRIu16"\n",                 // 0.0
/*208 */                        bps, channels, samplerate);                                                                       // 0.0
/*210 */             }                                                                                                            // 0.0
/*212 */         }                                                                                                                // 0.0
/*214 */         av_get_packet(pb, pkt, asize);                                                                                   // 0.0
/*216 */         pkt->stream_index = st[NSV_ST_AUDIO]->index;//NSV_ST_AUDIO;                                                      // 0.0
/*218 */         pkt->flags |= nsv->state == NSV_HAS_READ_NSVS ? AV_PKT_FLAG_KEY : 0; /* keyframe only likely on a sync frame */  // 0.0
/*220 */         if( nsv->state == NSV_HAS_READ_NSVS && st[NSV_ST_VIDEO] ) {                                                      // 0.0
/*222 */             /* on a nsvs frame we have new information on a/v sync */                                                    // 0.0
/*224 */             pkt->dts = (((NSVStream*)st[NSV_ST_VIDEO]->priv_data)->frame_offset-1);                                      // 0.0
/*226 */             pkt->dts *= (int64_t)1000        * nsv->framerate.den;                                                       // 0.0
/*228 */             pkt->dts += (int64_t)nsv->avsync * nsv->framerate.num;                                                       // 0.0
/*230 */             av_log(s, AV_LOG_TRACE, "NSV AUDIO: sync:%"PRId16", dts:%"PRId64,                                            // 0.0
/*232 */                    nsv->avsync, pkt->dts);                                                                               // 0.0
/*234 */         }                                                                                                                // 0.0
/*236 */         nst->frame_offset++;                                                                                             // 0.0
/*238 */     }                                                                                                                    // 0.0
/*242 */     nsv->state = NSV_UNSYNC;                                                                                             // 0.0
/*244 */     return 0;                                                                                                            // 0.0
/*246 */ }                                                                                                                        // 0.0
