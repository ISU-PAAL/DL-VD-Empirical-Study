// commit message FFmpeg@51e1cc16d3 (target=1, prob=0.99908674, correct=True): matroskadec: fix a memory leak
/*0   */ matroska_parse_block(MatroskaDemuxContext *matroska, uint8_t *data, int size,                           // (0) 0.103
/*1   */                      int64_t pos, uint64_t cluster_time, uint64_t duration,                             // (1) 0.07233
/*2   */                      int is_keyframe, int is_bframe)                                                    // (3) 0.05686
/*3   */ {                                                                                                       // (30) 0.001714
/*4   */     int res = 0;                                                                                        // (23) 0.01437
/*5   */     int track;                                                                                          // (27) 0.009951
/*6   */     AVStream *st;                                                                                       // (21) 0.01564
/*7   */     AVPacket *pkt;                                                                                      // (12) 0.02416
/*8   */     uint8_t *origdata = data;                                                                           // (15) 0.02211
/*9   */     int16_t block_time;                                                                                 // (17) 0.01888
/*10  */     uint32_t *lace_size = NULL;                                                                         // (7) 0.04106
/*11  */     int n, flags, laces = 0;                                                                            // (2) 0.06062
/*12  */     uint64_t num;                                                                                       // (20) 0.01607
/*13  */     int stream_index;                                                                                   // (24) 0.01327
/*14  */     /* first byte(s): tracknum */                                                                       // (16) 0.02007
/*15  */     if ((n = matroska_ebmlnum_uint(data, size, &num)) < 0) {                                            // (6) 0.04729
/*16  */         av_log(matroska->ctx, AV_LOG_ERROR, "EBML block data error\n");                                 // (4) 0.0542
/*17  */         av_free(origdata);                                                                              // (14) 0.02324
/*18  */         return res;                                                                                     // (18) 0.0175
/*19  */     }                                                                                                   // (29) 0.006662
/*20  */     data += n;                                                                                          // (25) 0.01185
/*21  */     size -= n;                                                                                          // (26) 0.0117
/*22  */     /* fetch track from num */                                                                          // (22) 0.01517
/*23  */     track = matroska_find_track_by_num(matroska, num);                                                  // (10) 0.03808
/*24  */     if (size <= 3 || track < 0 || track >= matroska->num_tracks) {                                      // (8) 0.03964
/*25  */         av_log(matroska->ctx, AV_LOG_INFO,                                                              // (9) 0.0383
/*26  */                "Invalid stream %d or size %u\n", track, size);                                          // (5) 0.04942
/*27  */         av_free(origdata);                                                                              // (13) 0.0235
/*28  */         return res;                                                                                     // (19) 0.01742
/*29  */     }                                                                                                   // (28) 0.008104
/*30  */     stream_index = matroska->tracks[track]->stream_index;                                               // (11) 0.03592
/*31  */     if (stream_index < 0 || stream_index >= matroska->ctx->nb_streams) {                                // 0.0
/*32  */         av_free(origdata);                                                                              // 0.0
/*33  */         return res;                                                                                     // 0.0
/*34  */     }                                                                                                   // 0.0
/*35  */     st = matroska->ctx->streams[stream_index];                                                          // 0.0
/*36  */     if (st->discard >= AVDISCARD_ALL) {                                                                 // 0.0
/*37  */         av_free(origdata);                                                                              // 0.0
/*38  */         return res;                                                                                     // 0.0
/*39  */     }                                                                                                   // 0.0
/*40  */     if (duration == AV_NOPTS_VALUE)                                                                     // 0.0
/*41  */         duration = matroska->tracks[track]->default_duration / matroska->time_scale;                    // 0.0
/*42  */     /* block_time (relative to cluster time) */                                                         // 0.0
/*43  */     block_time = AV_RB16(data);                                                                         // 0.0
/*44  */     data += 2;                                                                                          // 0.0
/*45  */     flags = *data++;                                                                                    // 0.0
/*46  */     size -= 3;                                                                                          // 0.0
/*47  */     if (is_keyframe == -1)                                                                              // 0.0
/*48  */         is_keyframe = flags & 0x80 ? PKT_FLAG_KEY : 0;                                                  // 0.0
/*49  */     if (matroska->skip_to_keyframe) {                                                                   // 0.0
/*50  */         if (!is_keyframe || st != matroska->skip_to_stream) {                                           // 0.0
/*51  */             av_free(origdata);                                                                          // 0.0
/*52  */             return res;                                                                                 // 0.0
/*53  */         }                                                                                               // 0.0
/*54  */         matroska->skip_to_keyframe = 0;                                                                 // 0.0
/*55  */     }                                                                                                   // 0.0
/*56  */     switch ((flags & 0x06) >> 1) {                                                                      // 0.0
/*57  */         case 0x0: /* no lacing */                                                                       // 0.0
/*58  */             laces = 1;                                                                                  // 0.0
/*59  */             lace_size = av_mallocz(sizeof(int));                                                        // 0.0
/*60  */             lace_size[0] = size;                                                                        // 0.0
/*61  */             break;                                                                                      // 0.0
/*62  */         case 0x1: /* xiph lacing */                                                                     // 0.0
/*63  */         case 0x2: /* fixed-size lacing */                                                               // 0.0
/*64  */         case 0x3: /* EBML lacing */                                                                     // 0.0
/*65  */             assert(size>0); // size <=3 is checked before size-=3 above                                 // 0.0
/*66  */             laces = (*data) + 1;                                                                        // 0.0
/*67  */             data += 1;                                                                                  // 0.0
/*68  */             size -= 1;                                                                                  // 0.0
/*69  */             lace_size = av_mallocz(laces * sizeof(int));                                                // 0.0
/*70  */             switch ((flags & 0x06) >> 1) {                                                              // 0.0
/*71  */                 case 0x1: /* xiph lacing */ {                                                           // 0.0
/*72  */                     uint8_t temp;                                                                       // 0.0
/*73  */                     uint32_t total = 0;                                                                 // 0.0
/*74  */                     for (n = 0; res == 0 && n < laces - 1; n++) {                                       // 0.0
/*75  */                         while (1) {                                                                     // 0.0
/*76  */                             if (size == 0) {                                                            // 0.0
/*77  */                                 res = -1;                                                               // 0.0
/*78  */                                 break;                                                                  // 0.0
/*79  */                             }                                                                           // 0.0
/*80  */                             temp = *data;                                                               // 0.0
/*81  */                             lace_size[n] += temp;                                                       // 0.0
/*82  */                             data += 1;                                                                  // 0.0
/*83  */                             size -= 1;                                                                  // 0.0
/*84  */                             if (temp != 0xff)                                                           // 0.0
/*85  */                                 break;                                                                  // 0.0
/*86  */                         }                                                                               // 0.0
/*87  */                         total += lace_size[n];                                                          // 0.0
/*88  */                     }                                                                                   // 0.0
/*89  */                     lace_size[n] = size - total;                                                        // 0.0
/*90  */                     break;                                                                              // 0.0
/*91  */                 }                                                                                       // 0.0
/*92  */                 case 0x2: /* fixed-size lacing */                                                       // 0.0
/*93  */                     for (n = 0; n < laces; n++)                                                         // 0.0
/*94  */                         lace_size[n] = size / laces;                                                    // 0.0
/*95  */                     break;                                                                              // 0.0
/*96  */                 case 0x3: /* EBML lacing */ {                                                           // 0.0
/*97  */                     uint32_t total;                                                                     // 0.0
/*98  */                     n = matroska_ebmlnum_uint(data, size, &num);                                        // 0.0
/*99  */                     if (n < 0) {                                                                        // 0.0
/*100 */                         av_log(matroska->ctx, AV_LOG_INFO,                                              // 0.0
/*101 */                                "EBML block data error\n");                                              // 0.0
/*102 */                         break;                                                                          // 0.0
/*103 */                     }                                                                                   // 0.0
/*104 */                     data += n;                                                                          // 0.0
/*105 */                     size -= n;                                                                          // 0.0
/*106 */                     total = lace_size[0] = num;                                                         // 0.0
/*107 */                     for (n = 1; res == 0 && n < laces - 1; n++) {                                       // 0.0
/*108 */                         int64_t snum;                                                                   // 0.0
/*109 */                         int r;                                                                          // 0.0
/*110 */                         r = matroska_ebmlnum_sint (data, size, &snum);                                  // 0.0
/*111 */                         if (r < 0) {                                                                    // 0.0
/*112 */                             av_log(matroska->ctx, AV_LOG_INFO,                                          // 0.0
/*113 */                                    "EBML block data error\n");                                          // 0.0
/*114 */                             break;                                                                      // 0.0
/*115 */                         }                                                                               // 0.0
/*116 */                         data += r;                                                                      // 0.0
/*117 */                         size -= r;                                                                      // 0.0
/*118 */                         lace_size[n] = lace_size[n - 1] + snum;                                         // 0.0
/*119 */                         total += lace_size[n];                                                          // 0.0
/*120 */                     }                                                                                   // 0.0
/*121 */                     lace_size[n] = size - total;                                                        // 0.0
/*122 */                     break;                                                                              // 0.0
/*123 */                 }                                                                                       // 0.0
/*124 */             }                                                                                           // 0.0
/*125 */             break;                                                                                      // 0.0
/*126 */     }                                                                                                   // 0.0
/*127 */     if (res == 0) {                                                                                     // 0.0
/*128 */         uint64_t timecode = AV_NOPTS_VALUE;                                                             // 0.0
/*129 */         if (cluster_time != (uint64_t)-1                                                                // 0.0
/*130 */             && (block_time >= 0 || cluster_time >= -block_time))                                        // 0.0
/*131 */             timecode = cluster_time + block_time;                                                       // 0.0
/*132 */         for (n = 0; n < laces; n++) {                                                                   // 0.0
/*133 */             if (st->codec->codec_id == CODEC_ID_RA_288 ||                                               // 0.0
/*134 */                 st->codec->codec_id == CODEC_ID_COOK ||                                                 // 0.0
/*135 */                 st->codec->codec_id == CODEC_ID_ATRAC3) {                                               // 0.0
/*136 */                 MatroskaAudioTrack *audiotrack = (MatroskaAudioTrack *)matroska->tracks[track];         // 0.0
/*137 */                 int a = st->codec->block_align;                                                         // 0.0
/*138 */                 int sps = audiotrack->sub_packet_size;                                                  // 0.0
/*139 */                 int cfs = audiotrack->coded_framesize;                                                  // 0.0
/*140 */                 int h = audiotrack->sub_packet_h;                                                       // 0.0
/*141 */                 int y = audiotrack->sub_packet_cnt;                                                     // 0.0
/*142 */                 int w = audiotrack->frame_size;                                                         // 0.0
/*143 */                 int x;                                                                                  // 0.0
/*144 */                 if (!audiotrack->pkt_cnt) {                                                             // 0.0
/*145 */                     if (st->codec->codec_id == CODEC_ID_RA_288)                                         // 0.0
/*146 */                         for (x=0; x<h/2; x++)                                                           // 0.0
/*147 */                             memcpy(audiotrack->buf+x*2*w+y*cfs,                                         // 0.0
/*148 */                                    data+x*cfs, cfs);                                                    // 0.0
/*149 */                     else                                                                                // 0.0
/*150 */                         for (x=0; x<w/sps; x++)                                                         // 0.0
/*151 */                             memcpy(audiotrack->buf+sps*(h*x+((h+1)/2)*(y&1)+(y>>1)), data+x*sps, sps);  // 0.0
/*152 */                     if (++audiotrack->sub_packet_cnt >= h) {                                            // 0.0
/*153 */                         audiotrack->sub_packet_cnt = 0;                                                 // 0.0
/*154 */                         audiotrack->pkt_cnt = h*w / a;                                                  // 0.0
/*155 */                     }                                                                                   // 0.0
/*156 */                 }                                                                                       // 0.0
/*157 */                 while (audiotrack->pkt_cnt) {                                                           // 0.0
/*158 */                     pkt = av_mallocz(sizeof(AVPacket));                                                 // 0.0
/*159 */                     av_new_packet(pkt, a);                                                              // 0.0
/*160 */                     memcpy(pkt->data, audiotrack->buf                                                   // 0.0
/*161 */                            + a * (h*w / a - audiotrack->pkt_cnt--), a);                                 // 0.0
/*162 */                     pkt->pos = pos;                                                                     // 0.0
/*163 */                     pkt->stream_index = stream_index;                                                   // 0.0
/*164 */                     matroska_queue_packet(matroska, pkt);                                               // 0.0
/*165 */                 }                                                                                       // 0.0
/*166 */             } else {                                                                                    // 0.0
/*167 */                 int result, offset = 0, ilen, olen, pkt_size = lace_size[n];                            // 0.0
/*168 */                 uint8_t *pkt_data = data;                                                               // 0.0
/*169 */                 if (matroska->tracks[track]->encoding_scope & 1) {                                      // 0.0
/*170 */                     switch (matroska->tracks[track]->encoding_algo) {                                   // 0.0
/*171 */                     case MATROSKA_TRACK_ENCODING_COMP_HEADERSTRIP:                                      // 0.0
/*172 */                         offset = matroska->tracks[track]->encoding_settings_len;                        // 0.0
/*173 */                         break;                                                                          // 0.0
/*174 */                     case MATROSKA_TRACK_ENCODING_COMP_LZO:                                              // 0.0
/*175 */                         pkt_data = NULL;                                                                // 0.0
/*176 */                         do {                                                                            // 0.0
/*177 */                             ilen = lace_size[n];                                                        // 0.0
/*178 */                             olen = pkt_size *= 3;                                                       // 0.0
/*179 */                             pkt_data = av_realloc(pkt_data,                                             // 0.0
/*180 */                                                   pkt_size+LZO_OUTPUT_PADDING);                         // 0.0
/*181 */                             result = lzo1x_decode(pkt_data, &olen, data, &ilen);                        // 0.0
/*182 */                         } while (result==LZO_OUTPUT_FULL && pkt_size<10000000);                         // 0.0
/*183 */                         if (result) {                                                                   // 0.0
/*184 */                             continue;                                                                   // 0.0
/*185 */                         }                                                                               // 0.0
/*186 */                         pkt_size -= olen;                                                               // 0.0
/*187 */                         break;                                                                          // 0.0
/*188 */ #ifdef CONFIG_ZLIB                                                                                      // 0.0
/*189 */                     case MATROSKA_TRACK_ENCODING_COMP_ZLIB: {                                           // 0.0
/*190 */                         z_stream zstream = {0};                                                         // 0.0
/*191 */                         pkt_data = NULL;                                                                // 0.0
/*192 */                         if (inflateInit(&zstream) != Z_OK)                                              // 0.0
/*193 */                             continue;                                                                   // 0.0
/*194 */                         zstream.next_in = data;                                                         // 0.0
/*195 */                         zstream.avail_in = lace_size[n];                                                // 0.0
/*196 */                         do {                                                                            // 0.0
/*197 */                             pkt_size *= 3;                                                              // 0.0
/*198 */                             pkt_data = av_realloc(pkt_data, pkt_size);                                  // 0.0
/*199 */                             zstream.avail_out = pkt_size - zstream.total_out;                           // 0.0
/*200 */                             zstream.next_out = pkt_data + zstream.total_out;                            // 0.0
/*201 */                             result = inflate(&zstream, Z_NO_FLUSH);                                     // 0.0
/*202 */                         } while (result==Z_OK && pkt_size<10000000);                                    // 0.0
/*203 */                         pkt_size = zstream.total_out;                                                   // 0.0
/*204 */                         inflateEnd(&zstream);                                                           // 0.0
/*205 */                         if (result != Z_STREAM_END) {                                                   // 0.0
/*206 */                             continue;                                                                   // 0.0
/*207 */                         }                                                                               // 0.0
/*208 */                         break;                                                                          // 0.0
/*209 */                     }                                                                                   // 0.0
/*210 */ #endif                                                                                                  // 0.0
/*211 */ #ifdef CONFIG_BZLIB                                                                                     // 0.0
/*212 */                     case MATROSKA_TRACK_ENCODING_COMP_BZLIB: {                                          // 0.0
/*213 */                         bz_stream bzstream = {0};                                                       // 0.0
/*214 */                         pkt_data = NULL;                                                                // 0.0
/*215 */                         if (BZ2_bzDecompressInit(&bzstream, 0, 0) != BZ_OK)                             // 0.0
/*216 */                             continue;                                                                   // 0.0
/*217 */                         bzstream.next_in = data;                                                        // 0.0
/*218 */                         bzstream.avail_in = lace_size[n];                                               // 0.0
/*219 */                         do {                                                                            // 0.0
/*220 */                             pkt_size *= 3;                                                              // 0.0
/*221 */                             pkt_data = av_realloc(pkt_data, pkt_size);                                  // 0.0
/*222 */                             bzstream.avail_out = pkt_size - bzstream.total_out_lo32;                    // 0.0
/*223 */                             bzstream.next_out = pkt_data + bzstream.total_out_lo32;                     // 0.0
/*224 */                             result = BZ2_bzDecompress(&bzstream);                                       // 0.0
/*225 */                         } while (result==BZ_OK && pkt_size<10000000);                                   // 0.0
/*226 */                         pkt_size = bzstream.total_out_lo32;                                             // 0.0
/*227 */                         BZ2_bzDecompressEnd(&bzstream);                                                 // 0.0
/*228 */                         if (result != BZ_STREAM_END) {                                                  // 0.0
/*229 */                             continue;                                                                   // 0.0
/*230 */                         }                                                                               // 0.0
/*231 */                         break;                                                                          // 0.0
/*232 */                     }                                                                                   // 0.0
/*233 */ #endif                                                                                                  // 0.0
/*234 */                     }                                                                                   // 0.0
/*235 */                 }                                                                                       // 0.0
/*236 */                 pkt = av_mallocz(sizeof(AVPacket));                                                     // 0.0
/*237 */                 /* XXX: prevent data copy... */                                                         // 0.0
/*238 */                 if (av_new_packet(pkt, pkt_size+offset) < 0) {                                          // 0.0
/*239 */                     av_free(pkt);                                                                       // 0.0
/*240 */                     res = AVERROR(ENOMEM);                                                              // 0.0
/*241 */                     n = laces-1;                                                                        // 0.0
/*242 */                     break;                                                                              // 0.0
/*243 */                 }                                                                                       // 0.0
/*244 */                 if (offset)                                                                             // 0.0
/*245 */                     memcpy (pkt->data, matroska->tracks[track]->encoding_settings, offset);             // 0.0
/*246 */                 memcpy (pkt->data+offset, pkt_data, pkt_size);                                          // 0.0
/*247 */                 if (n == 0)                                                                             // 0.0
/*248 */                     pkt->flags = is_keyframe;                                                           // 0.0
/*249 */                 pkt->stream_index = stream_index;                                                       // 0.0
/*250 */                 pkt->pts = timecode;                                                                    // 0.0
/*251 */                 pkt->pos = pos;                                                                         // 0.0
/*252 */                 pkt->duration = duration;                                                               // 0.0
/*253 */                 matroska_queue_packet(matroska, pkt);                                                   // 0.0
/*254 */             }                                                                                           // 0.0
/*255 */             if (timecode != AV_NOPTS_VALUE)                                                             // 0.0
/*256 */                 timecode = duration ? timecode + duration : AV_NOPTS_VALUE;                             // 0.0
/*257 */             data += lace_size[n];                                                                       // 0.0
/*258 */         }                                                                                               // 0.0
/*259 */     }                                                                                                   // 0.0
/*260 */     av_free(lace_size);                                                                                 // 0.0
/*261 */     av_free(origdata);                                                                                  // 0.0
/*262 */     return res;                                                                                         // 0.0
/*263 */ }                                                                                                       // 0.0
