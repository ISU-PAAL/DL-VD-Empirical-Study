// commit message FFmpeg@03abf55f25 (target=1, prob=0.7599739, correct=True): avformat/rmdec: Check for overflow in ff_rm_read_mdpr_codecdata()
/*0   */ int ff_rm_read_mdpr_codecdata(AVFormatContext *s, AVIOContext *pb,                                        // (3) 0.05078
/*2   */                               AVStream *st, RMStream *rst,                                                // (1) 0.07813
/*4   */                               unsigned int codec_data_size, const uint8_t *mime)                          // (0) 0.08984
/*6   */ {                                                                                                         // (26) 0.001953
/*8   */     unsigned int v;                                                                                       // (22) 0.01367
/*10  */     int size;                                                                                             // (24) 0.01172
/*12  */     int64_t codec_pos;                                                                                    // (19) 0.02148
/*14  */     int ret;                                                                                              // (23) 0.01172
/*18  */     if (codec_data_size > INT_MAX)                                                                        // (14) 0.03125
/*20  */         return AVERROR_INVALIDDATA;                                                                       // (12) 0.0332
/*24  */     avpriv_set_pts_info(st, 64, 1, 1000);                                                                 // (9) 0.04102
/*26  */     codec_pos = avio_tell(pb);                                                                            // (17) 0.02734
/*28  */     v = avio_rb32(pb);                                                                                    // (18) 0.02539
/*32  */     if (v == MKBETAG('M', 'L', 'T', 'I')) {                                                               // (4) 0.04883
/*34  */         int number_of_streams = avio_rb16(pb);                                                            // (7) 0.04492
/*36  */         int number_of_mdpr;                                                                               // (15) 0.0293
/*38  */         int i;                                                                                            // (20) 0.01953
/*40  */         for (i = 0; i<number_of_streams; i++)                                                             // (6) 0.04687
/*42  */             avio_rb16(pb);                                                                                // (10) 0.03711
/*44  */         number_of_mdpr = avio_rb16(pb);                                                                   // (8) 0.04297
/*46  */         if (number_of_mdpr != 1) {                                                                        // (11) 0.03711
/*48  */             avpriv_request_sample(s, "MLTI with multiple MDPR");                                          // (2) 0.05469
/*50  */         }                                                                                                 // (21) 0.01562
/*52  */         avio_rb32(pb);                                                                                    // (16) 0.0293
/*54  */         v = avio_rb32(pb);                                                                                // (13) 0.0332
/*56  */     }                                                                                                     // (25) 0.007812
/*60  */     if (v == MKTAG(0xfd, 'a', 'r', '.')) {                                                                // (5) 0.04687
/*62  */         /* ra type header */                                                                              // 0.0
/*64  */         if (rm_read_audio_stream_info(s, pb, st, rst, 0))                                                 // 0.0
/*66  */             return -1;                                                                                    // 0.0
/*68  */     } else if (v == MKBETAG('L', 'S', 'D', ':')) {                                                        // 0.0
/*70  */         avio_seek(pb, -4, SEEK_CUR);                                                                      // 0.0
/*72  */         if ((ret = rm_read_extradata(pb, st->codec, codec_data_size)) < 0)                                // 0.0
/*74  */             return ret;                                                                                   // 0.0
/*78  */         st->codec->codec_type = AVMEDIA_TYPE_AUDIO;                                                       // 0.0
/*80  */         st->codec->codec_tag  = AV_RL32(st->codec->extradata);                                            // 0.0
/*82  */         st->codec->codec_id   = ff_codec_get_id(ff_rm_codec_tags,                                         // 0.0
/*84  */                                                 st->codec->codec_tag);                                    // 0.0
/*86  */     } else if(mime && !strcmp(mime, "logical-fileinfo")){                                                 // 0.0
/*88  */         int stream_count, rule_count, property_count, i;                                                  // 0.0
/*90  */         ff_free_stream(s, st);                                                                            // 0.0
/*92  */         if (avio_rb16(pb) != 0) {                                                                         // 0.0
/*94  */             av_log(s, AV_LOG_WARNING, "Unsupported version\n");                                           // 0.0
/*96  */             goto skip;                                                                                    // 0.0
/*98  */         }                                                                                                 // 0.0
/*100 */         stream_count = avio_rb16(pb);                                                                     // 0.0
/*102 */         avio_skip(pb, 6*stream_count);                                                                    // 0.0
/*104 */         rule_count = avio_rb16(pb);                                                                       // 0.0
/*106 */         avio_skip(pb, 2*rule_count);                                                                      // 0.0
/*108 */         property_count = avio_rb16(pb);                                                                   // 0.0
/*110 */         for(i=0; i<property_count; i++){                                                                  // 0.0
/*112 */             uint8_t name[128], val[128];                                                                  // 0.0
/*114 */             avio_rb32(pb);                                                                                // 0.0
/*116 */             if (avio_rb16(pb) != 0) {                                                                     // 0.0
/*118 */                 av_log(s, AV_LOG_WARNING, "Unsupported Name value property version\n");                   // 0.0
/*120 */                 goto skip; //FIXME skip just this one                                                     // 0.0
/*122 */             }                                                                                             // 0.0
/*124 */             get_str8(pb, name, sizeof(name));                                                             // 0.0
/*126 */             switch(avio_rb32(pb)) {                                                                       // 0.0
/*128 */             case 2: get_strl(pb, val, sizeof(val), avio_rb16(pb));                                        // 0.0
/*130 */                 av_dict_set(&s->metadata, name, val, 0);                                                  // 0.0
/*132 */                 break;                                                                                    // 0.0
/*134 */             default: avio_skip(pb, avio_rb16(pb));                                                        // 0.0
/*136 */             }                                                                                             // 0.0
/*138 */         }                                                                                                 // 0.0
/*140 */     } else {                                                                                              // 0.0
/*142 */         int fps;                                                                                          // 0.0
/*144 */         if (avio_rl32(pb) != MKTAG('V', 'I', 'D', 'O')) {                                                 // 0.0
/*146 */         fail1:                                                                                            // 0.0
/*148 */             av_log(s, AV_LOG_WARNING, "Unsupported stream type %08x\n", v);                               // 0.0
/*150 */             goto skip;                                                                                    // 0.0
/*152 */         }                                                                                                 // 0.0
/*154 */         st->codec->codec_tag = avio_rl32(pb);                                                             // 0.0
/*156 */         st->codec->codec_id  = ff_codec_get_id(ff_rm_codec_tags,                                          // 0.0
/*158 */                                                st->codec->codec_tag);                                     // 0.0
/*160 */         av_dlog(s, "%X %X\n", st->codec->codec_tag, MKTAG('R', 'V', '2', '0'));                           // 0.0
/*162 */         if (st->codec->codec_id == AV_CODEC_ID_NONE)                                                      // 0.0
/*164 */             goto fail1;                                                                                   // 0.0
/*166 */         st->codec->width  = avio_rb16(pb);                                                                // 0.0
/*168 */         st->codec->height = avio_rb16(pb);                                                                // 0.0
/*170 */         avio_skip(pb, 2); // looks like bits per sample                                                   // 0.0
/*172 */         avio_skip(pb, 4); // always zero?                                                                 // 0.0
/*174 */         st->codec->codec_type = AVMEDIA_TYPE_VIDEO;                                                       // 0.0
/*176 */         st->need_parsing = AVSTREAM_PARSE_TIMESTAMPS;                                                     // 0.0
/*178 */         fps = avio_rb32(pb);                                                                              // 0.0
/*182 */         if ((ret = rm_read_extradata(pb, st->codec, codec_data_size - (avio_tell(pb) - codec_pos))) < 0)  // 0.0
/*184 */             return ret;                                                                                   // 0.0
/*188 */         if (fps > 0) {                                                                                    // 0.0
/*190 */             av_reduce(&st->avg_frame_rate.den, &st->avg_frame_rate.num,                                   // 0.0
/*192 */                       0x10000, fps, (1 << 30) - 1);                                                       // 0.0
/*194 */ #if FF_API_R_FRAME_RATE                                                                                   // 0.0
/*196 */             st->r_frame_rate = st->avg_frame_rate;                                                        // 0.0
/*198 */ #endif                                                                                                    // 0.0
/*200 */         } else if (s->error_recognition & AV_EF_EXPLODE) {                                                // 0.0
/*202 */             av_log(s, AV_LOG_ERROR, "Invalid framerate\n");                                               // 0.0
/*204 */             return AVERROR_INVALIDDATA;                                                                   // 0.0
/*206 */         }                                                                                                 // 0.0
/*208 */     }                                                                                                     // 0.0
/*212 */ skip:                                                                                                     // 0.0
/*214 */     /* skip codec info */                                                                                 // 0.0
/*216 */     size = avio_tell(pb) - codec_pos;                                                                     // 0.0
/*218 */     avio_skip(pb, codec_data_size - size);                                                                // 0.0
/*222 */     return 0;                                                                                             // 0.0
/*224 */ }                                                                                                         // 0.0
