// commit message FFmpeg@bf87908cd8 (target=1, prob=0.50906754, correct=True): rmdec: Pass AVIOContext to rm_read_metadata()
/*0   */ static int rm_read_audio_stream_info(AVFormatContext *s, AVIOContext *pb,                               // (5) 0.04687
/*2   */                                      AVStream *st, RMStream *ast, int read_all)                         // (0) 0.09961
/*4   */ {                                                                                                       // (25) 0.001953
/*6   */     char buf[256];                                                                                      // (23) 0.01562
/*8   */     uint32_t version;                                                                                   // (20) 0.01758
/*10  */     int ret;                                                                                            // (24) 0.01172
/*14  */     /* ra type header */                                                                                // (22) 0.01562
/*16  */     version = avio_rb16(pb); /* version */                                                              // (14) 0.03125
/*18  */     if (version == 3) {                                                                                 // (19) 0.01953
/*20  */         unsigned bytes_per_minute;                                                                      // (18) 0.02734
/*22  */         int header_size = avio_rb16(pb);                                                                // (10) 0.03906
/*24  */         int64_t startpos = avio_tell(pb);                                                               // (8) 0.04102
/*26  */         avio_skip(pb, 8);                                                                               // (15) 0.03125
/*28  */         bytes_per_minute = avio_rb16(pb);                                                               // (9) 0.04102
/*30  */         avio_skip(pb, 4);                                                                               // (16) 0.03125
/*32  */         rm_read_metadata(s, 0);                                                                         // (13) 0.0332
/*34  */         if ((startpos + header_size) >= avio_tell(pb) + 2) {                                            // (3) 0.05469
/*36  */             // fourcc (should always be "lpcJ")                                                         // (7) 0.04492
/*38  */             avio_r8(pb);                                                                                // (11) 0.03711
/*40  */             get_str8(pb, buf, sizeof(buf));                                                             // (6) 0.04687
/*42  */         }                                                                                               // (21) 0.01563
/*44  */         // Skip extra header crap (this should never happen)                                            // (12) 0.03516
/*46  */         if ((startpos + header_size) > avio_tell(pb))                                                   // (4) 0.04687
/*48  */             avio_skip(pb, header_size + startpos - avio_tell(pb));                                      // (1) 0.0625
/*50  */         if (bytes_per_minute)                                                                           // (17) 0.0293
/*52  */             st->codec->bit_rate = 8LL * bytes_per_minute / 60;                                          // (2) 0.06055
/*54  */         st->codec->sample_rate = 8000;                                                                  // 0.0
/*56  */         st->codec->channels = 1;                                                                        // 0.0
/*58  */         st->codec->channel_layout = AV_CH_LAYOUT_MONO;                                                  // 0.0
/*60  */         st->codec->codec_type = AVMEDIA_TYPE_AUDIO;                                                     // 0.0
/*62  */         st->codec->codec_id = AV_CODEC_ID_RA_144;                                                       // 0.0
/*64  */         ast->deint_id = DEINT_ID_INT0;                                                                  // 0.0
/*66  */     } else {                                                                                            // 0.0
/*68  */         int flavor, sub_packet_h, coded_framesize, sub_packet_size;                                     // 0.0
/*70  */         int codecdata_length;                                                                           // 0.0
/*72  */         unsigned bytes_per_minute;                                                                      // 0.0
/*74  */         /* old version (4) */                                                                           // 0.0
/*76  */         avio_skip(pb, 2); /* unused */                                                                  // 0.0
/*78  */         avio_rb32(pb); /* .ra4 */                                                                       // 0.0
/*80  */         avio_rb32(pb); /* data size */                                                                  // 0.0
/*82  */         avio_rb16(pb); /* version2 */                                                                   // 0.0
/*84  */         avio_rb32(pb); /* header size */                                                                // 0.0
/*86  */         flavor= avio_rb16(pb); /* add codec info / flavor */                                            // 0.0
/*88  */         ast->coded_framesize = coded_framesize = avio_rb32(pb); /* coded frame size */                  // 0.0
/*90  */         avio_rb32(pb); /* ??? */                                                                        // 0.0
/*92  */         bytes_per_minute = avio_rb32(pb);                                                               // 0.0
/*94  */         if (version == 4) {                                                                             // 0.0
/*96  */             if (bytes_per_minute)                                                                       // 0.0
/*98  */                 st->codec->bit_rate = 8LL * bytes_per_minute / 60;                                      // 0.0
/*100 */         }                                                                                               // 0.0
/*102 */         avio_rb32(pb); /* ??? */                                                                        // 0.0
/*104 */         ast->sub_packet_h = sub_packet_h = avio_rb16(pb); /* 1 */                                       // 0.0
/*106 */         st->codec->block_align= avio_rb16(pb); /* frame size */                                         // 0.0
/*108 */         ast->sub_packet_size = sub_packet_size = avio_rb16(pb); /* sub packet size */                   // 0.0
/*110 */         avio_rb16(pb); /* ??? */                                                                        // 0.0
/*112 */         if (version == 5) {                                                                             // 0.0
/*114 */             avio_rb16(pb); avio_rb16(pb); avio_rb16(pb);                                                // 0.0
/*116 */         }                                                                                               // 0.0
/*118 */         st->codec->sample_rate = avio_rb16(pb);                                                         // 0.0
/*120 */         avio_rb32(pb);                                                                                  // 0.0
/*122 */         st->codec->channels = avio_rb16(pb);                                                            // 0.0
/*124 */         if (version == 5) {                                                                             // 0.0
/*126 */             ast->deint_id = avio_rl32(pb);                                                              // 0.0
/*128 */             avio_read(pb, buf, 4);                                                                      // 0.0
/*130 */             buf[4] = 0;                                                                                 // 0.0
/*132 */         } else {                                                                                        // 0.0
/*134 */             get_str8(pb, buf, sizeof(buf)); /* desc */                                                  // 0.0
/*136 */             ast->deint_id = AV_RL32(buf);                                                               // 0.0
/*138 */             get_str8(pb, buf, sizeof(buf)); /* desc */                                                  // 0.0
/*140 */         }                                                                                               // 0.0
/*142 */         st->codec->codec_type = AVMEDIA_TYPE_AUDIO;                                                     // 0.0
/*144 */         st->codec->codec_tag  = AV_RL32(buf);                                                           // 0.0
/*146 */         st->codec->codec_id   = ff_codec_get_id(ff_rm_codec_tags,                                       // 0.0
/*148 */                                                 st->codec->codec_tag);                                  // 0.0
/*152 */         switch (st->codec->codec_id) {                                                                  // 0.0
/*154 */         case AV_CODEC_ID_AC3:                                                                           // 0.0
/*156 */             st->need_parsing = AVSTREAM_PARSE_FULL;                                                     // 0.0
/*158 */             break;                                                                                      // 0.0
/*160 */         case AV_CODEC_ID_RA_288:                                                                        // 0.0
/*162 */             st->codec->extradata_size= 0;                                                               // 0.0
/*164 */             ast->audio_framesize = st->codec->block_align;                                              // 0.0
/*166 */             st->codec->block_align = coded_framesize;                                                   // 0.0
/*168 */             break;                                                                                      // 0.0
/*170 */         case AV_CODEC_ID_COOK:                                                                          // 0.0
/*172 */             st->need_parsing = AVSTREAM_PARSE_HEADERS;                                                  // 0.0
/*174 */         case AV_CODEC_ID_ATRAC3:                                                                        // 0.0
/*176 */         case AV_CODEC_ID_SIPR:                                                                          // 0.0
/*178 */             if (read_all) {                                                                             // 0.0
/*180 */                 codecdata_length = 0;                                                                   // 0.0
/*182 */             } else {                                                                                    // 0.0
/*184 */                 avio_rb16(pb); avio_r8(pb);                                                             // 0.0
/*186 */                 if (version == 5)                                                                       // 0.0
/*188 */                     avio_r8(pb);                                                                        // 0.0
/*190 */                 codecdata_length = avio_rb32(pb);                                                       // 0.0
/*192 */                 if(codecdata_length + FF_INPUT_BUFFER_PADDING_SIZE <= (unsigned)codecdata_length){      // 0.0
/*194 */                     av_log(s, AV_LOG_ERROR, "codecdata_length too large\n");                            // 0.0
/*196 */                     return -1;                                                                          // 0.0
/*198 */                 }                                                                                       // 0.0
/*200 */             }                                                                                           // 0.0
/*204 */             ast->audio_framesize = st->codec->block_align;                                              // 0.0
/*206 */             if (st->codec->codec_id == AV_CODEC_ID_SIPR) {                                              // 0.0
/*208 */                 if (flavor > 3) {                                                                       // 0.0
/*210 */                     av_log(s, AV_LOG_ERROR, "bad SIPR file flavor %d\n",                                // 0.0
/*212 */                            flavor);                                                                     // 0.0
/*214 */                     return -1;                                                                          // 0.0
/*216 */                 }                                                                                       // 0.0
/*218 */                 st->codec->block_align = ff_sipr_subpk_size[flavor];                                    // 0.0
/*220 */             } else {                                                                                    // 0.0
/*222 */                 if(sub_packet_size <= 0){                                                               // 0.0
/*224 */                     av_log(s, AV_LOG_ERROR, "sub_packet_size is invalid\n");                            // 0.0
/*226 */                     return -1;                                                                          // 0.0
/*228 */                 }                                                                                       // 0.0
/*230 */                 st->codec->block_align = ast->sub_packet_size;                                          // 0.0
/*232 */             }                                                                                           // 0.0
/*234 */             if ((ret = rm_read_extradata(pb, st->codec, codecdata_length)) < 0)                         // 0.0
/*236 */                 return ret;                                                                             // 0.0
/*240 */             break;                                                                                      // 0.0
/*242 */         case AV_CODEC_ID_AAC:                                                                           // 0.0
/*244 */             avio_rb16(pb); avio_r8(pb);                                                                 // 0.0
/*246 */             if (version == 5)                                                                           // 0.0
/*248 */                 avio_r8(pb);                                                                            // 0.0
/*250 */             codecdata_length = avio_rb32(pb);                                                           // 0.0
/*252 */             if(codecdata_length + FF_INPUT_BUFFER_PADDING_SIZE <= (unsigned)codecdata_length){          // 0.0
/*254 */                 av_log(s, AV_LOG_ERROR, "codecdata_length too large\n");                                // 0.0
/*256 */                 return -1;                                                                              // 0.0
/*258 */             }                                                                                           // 0.0
/*260 */             if (codecdata_length >= 1) {                                                                // 0.0
/*262 */                 avio_r8(pb);                                                                            // 0.0
/*264 */                 if ((ret = rm_read_extradata(pb, st->codec, codecdata_length - 1)) < 0)                 // 0.0
/*266 */                     return ret;                                                                         // 0.0
/*268 */             }                                                                                           // 0.0
/*270 */             break;                                                                                      // 0.0
/*272 */         default:                                                                                        // 0.0
/*274 */             av_strlcpy(st->codec->codec_name, buf, sizeof(st->codec->codec_name));                      // 0.0
/*276 */         }                                                                                               // 0.0
/*278 */         if (ast->deint_id == DEINT_ID_INT4 ||                                                           // 0.0
/*280 */             ast->deint_id == DEINT_ID_GENR ||                                                           // 0.0
/*282 */             ast->deint_id == DEINT_ID_SIPR) {                                                           // 0.0
/*284 */             if (st->codec->block_align <= 0 ||                                                          // 0.0
/*286 */                 ast->audio_framesize * sub_packet_h > (unsigned)INT_MAX ||                              // 0.0
/*288 */                 ast->audio_framesize * sub_packet_h < st->codec->block_align)                           // 0.0
/*290 */                 return AVERROR_INVALIDDATA;                                                             // 0.0
/*292 */             if (av_new_packet(&ast->pkt, ast->audio_framesize * sub_packet_h) < 0)                      // 0.0
/*294 */                 return AVERROR(ENOMEM);                                                                 // 0.0
/*296 */         }                                                                                               // 0.0
/*298 */         switch (ast->deint_id) {                                                                        // 0.0
/*300 */         case DEINT_ID_INT4:                                                                             // 0.0
/*302 */             if (ast->coded_framesize > ast->audio_framesize ||                                          // 0.0
/*304 */                 sub_packet_h <= 1 ||                                                                    // 0.0
/*306 */                 ast->coded_framesize * sub_packet_h > (2 + (sub_packet_h & 1)) * ast->audio_framesize)  // 0.0
/*308 */                 return AVERROR_INVALIDDATA;                                                             // 0.0
/*310 */             break;                                                                                      // 0.0
/*312 */         case DEINT_ID_GENR:                                                                             // 0.0
/*314 */             if (ast->sub_packet_size <= 0 ||                                                            // 0.0
/*316 */                 ast->sub_packet_size > ast->audio_framesize)                                            // 0.0
/*318 */                 return AVERROR_INVALIDDATA;                                                             // 0.0
/*320 */             break;                                                                                      // 0.0
/*322 */         case DEINT_ID_SIPR:                                                                             // 0.0
/*324 */         case DEINT_ID_INT0:                                                                             // 0.0
/*326 */         case DEINT_ID_VBRS:                                                                             // 0.0
/*328 */         case DEINT_ID_VBRF:                                                                             // 0.0
/*330 */             break;                                                                                      // 0.0
/*332 */         default:                                                                                        // 0.0
/*334 */             av_log(s, AV_LOG_ERROR, "Unknown interleaver %X\n", ast->deint_id);                         // 0.0
/*336 */             return AVERROR_INVALIDDATA;                                                                 // 0.0
/*338 */         }                                                                                               // 0.0
/*342 */         if (read_all) {                                                                                 // 0.0
/*344 */             avio_r8(pb);                                                                                // 0.0
/*346 */             avio_r8(pb);                                                                                // 0.0
/*348 */             avio_r8(pb);                                                                                // 0.0
/*350 */             rm_read_metadata(s, 0);                                                                     // 0.0
/*352 */         }                                                                                               // 0.0
/*354 */     }                                                                                                   // 0.0
/*356 */     return 0;                                                                                           // 0.0
/*358 */ }                                                                                                       // 0.0
