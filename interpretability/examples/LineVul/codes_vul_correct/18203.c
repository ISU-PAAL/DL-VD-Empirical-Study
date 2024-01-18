// commit message FFmpeg@aba232cfa9 (target=1, prob=0.64765173, correct=True): lavf: deprecate r_frame_rate.
/*0   */ ff_rm_read_mdpr_codecdata (AVFormatContext *s, AVIOContext *pb,                                           // (8) 0.04883
/*2   */                            AVStream *st, RMStream *rst, int codec_data_size)                              // (1) 0.08594
/*4   */ {                                                                                                         // (22) 0.001953
/*6   */     unsigned int v;                                                                                       // (18) 0.01367
/*8   */     int size;                                                                                             // (19) 0.01172
/*10  */     int64_t codec_pos;                                                                                    // (17) 0.02148
/*12  */     int ret;                                                                                              // (20) 0.01172
/*16  */     avpriv_set_pts_info(st, 64, 1, 1000);                                                                 // (11) 0.04102
/*18  */     codec_pos = avio_tell(pb);                                                                            // (13) 0.02734
/*20  */     v = avio_rb32(pb);                                                                                    // (15) 0.02539
/*22  */     if (v == MKTAG(0xfd, 'a', 'r', '.')) {                                                                // (9) 0.04688
/*24  */         /* ra type header */                                                                              // (16) 0.02344
/*26  */         if (rm_read_audio_stream_info(s, pb, st, rst, 0))                                                 // (5) 0.06055
/*28  */             return -1;                                                                                    // (12) 0.0293
/*30  */     } else if (v == MKBETAG('L', 'S', 'D', ':')) {                                                        // (6) 0.05078
/*32  */         avio_seek(pb, -4, SEEK_CUR);                                                                      // (10) 0.04492
/*34  */         if ((ret = rm_read_extradata(pb, st->codec, codec_data_size)) < 0)                                // (3) 0.06836
/*36  */             return ret;                                                                                   // (14) 0.02734
/*40  */         st->codec->codec_type = AVMEDIA_TYPE_AUDIO;                                                       // (7) 0.05078
/*42  */         st->codec->codec_tag  = AV_RL32(st->codec->extradata);                                            // (4) 0.0625
/*44  */         st->codec->codec_id   = ff_codec_get_id(ff_rm_codec_tags,                                         // (2) 0.07227
/*46  */                                                 st->codec->codec_tag);                                    // (0) 0.1113
/*48  */     } else {                                                                                              // 0.0
/*50  */         int fps;                                                                                          // 0.0
/*52  */         if (avio_rl32(pb) != MKTAG('V', 'I', 'D', 'O')) {                                                 // 0.0
/*54  */         fail1:                                                                                            // 0.0
/*56  */             av_log(st->codec, AV_LOG_ERROR, "Unsupported video codec\n");                                 // 0.0
/*58  */             goto skip;                                                                                    // 0.0
/*60  */         }                                                                                                 // 0.0
/*62  */         st->codec->codec_tag = avio_rl32(pb);                                                             // 0.0
/*64  */         st->codec->codec_id  = ff_codec_get_id(ff_rm_codec_tags,                                          // 0.0
/*66  */                                                st->codec->codec_tag);                                     // 0.0
/*68  */ //        av_log(s, AV_LOG_DEBUG, "%X %X\n", st->codec->codec_tag, MKTAG('R', 'V', '2', '0'));            // 0.0
/*70  */         if (st->codec->codec_id == CODEC_ID_NONE)                                                         // 0.0
/*72  */             goto fail1;                                                                                   // 0.0
/*74  */         st->codec->width  = avio_rb16(pb);                                                                // 0.0
/*76  */         st->codec->height = avio_rb16(pb);                                                                // 0.0
/*78  */         avio_skip(pb, 2); // looks like bits per sample                                                   // 0.0
/*80  */         avio_skip(pb, 4); // always zero?                                                                 // 0.0
/*82  */         st->codec->codec_type = AVMEDIA_TYPE_VIDEO;                                                       // 0.0
/*84  */         st->need_parsing = AVSTREAM_PARSE_TIMESTAMPS;                                                     // 0.0
/*86  */         fps = avio_rb32(pb);                                                                              // 0.0
/*90  */         if ((ret = rm_read_extradata(pb, st->codec, codec_data_size - (avio_tell(pb) - codec_pos))) < 0)  // 0.0
/*92  */             return ret;                                                                                   // 0.0
/*96  */         av_reduce(&st->r_frame_rate.den, &st->r_frame_rate.num,                                           // 0.0
/*98  */                   0x10000, fps, (1 << 30) - 1);                                                           // 0.0
/*100 */         st->avg_frame_rate = st->r_frame_rate;                                                            // 0.0
/*102 */     }                                                                                                     // (21) 0.007812
/*106 */ skip:                                                                                                     // 0.0
/*108 */     /* skip codec info */                                                                                 // 0.0
/*110 */     size = avio_tell(pb) - codec_pos;                                                                     // 0.0
/*112 */     avio_skip(pb, codec_data_size - size);                                                                // 0.0
/*116 */     return 0;                                                                                             // 0.0
/*118 */ }                                                                                                         // 0.0
