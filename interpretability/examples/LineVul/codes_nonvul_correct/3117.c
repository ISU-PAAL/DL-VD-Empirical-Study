// commit message FFmpeg@9924f1bc34 (target=0, prob=0.36541662, correct=True): avformat/matroskaenc: move some initialization checks to mkv_init
/*0   */ static int mkv_write_header(AVFormatContext *s)                                                                   // (15) 0.0293
/*2   */ {                                                                                                                 // (24) 0.001962
/*4   */     MatroskaMuxContext *mkv = s->priv_data;                                                                       // (8) 0.03711
/*6   */     AVIOContext *pb = s->pb;                                                                                      // (16) 0.02539
/*8   */     ebml_master ebml_header;                                                                                      // (18) 0.02344
/*10  */     AVDictionaryEntry *tag;                                                                                       // (21) 0.01953
/*12  */     int ret, i, version = 2;                                                                                      // (17) 0.02345
/*14  */     int64_t creation_time;                                                                                        // (19) 0.02149
/*18  */     if (!strcmp(s->oformat->name, "webm"))                                                                        // (9) 0.03711
/*20  */         mkv->mode = MODE_WEBM;                                                                                    // (12) 0.03515
/*22  */     else                                                                                                          // (23) 0.007812
/*24  */         mkv->mode = MODE_MATROSKAv2;                                                                              // (5) 0.04297
/*28  */     if (mkv->mode != MODE_WEBM ||                                                                                 // (13) 0.03125
/*30  */         av_dict_get(s->metadata, "stereo_mode", NULL, 0) ||                                                       // (3) 0.05468
/*32  */         av_dict_get(s->metadata, "alpha_mode", NULL, 0))                                                          // (4) 0.05078
/*34  */         version = 4;                                                                                              // (20) 0.02148
/*38  */     if (s->nb_streams > MAX_TRACKS) {                                                                             // (10) 0.03711
/*40  */         av_log(s, AV_LOG_ERROR,                                                                                   // (11) 0.03711
/*42  */                "At most %d streams are supported for muxing in Matroska\n",                                       // (2) 0.06445
/*44  */                MAX_TRACKS);                                                                                       // (7) 0.03906
/*46  */         return AVERROR(EINVAL);                                                                                   // (14) 0.03125
/*48  */     }                                                                                                             // (22) 0.007812
/*52  */     for (i = 0; i < s->nb_streams; i++) {                                                                         // (6) 0.04101
/*54  */         if (s->streams[i]->codecpar->codec_id == AV_CODEC_ID_ATRAC3 ||                                            // (0) 0.07617
/*56  */             s->streams[i]->codecpar->codec_id == AV_CODEC_ID_COOK ||                                              // (1) 0.07617
/*58  */             s->streams[i]->codecpar->codec_id == AV_CODEC_ID_RA_288 ||                                            // 0.0
/*60  */             s->streams[i]->codecpar->codec_id == AV_CODEC_ID_SIPR ||                                              // 0.0
/*62  */             s->streams[i]->codecpar->codec_id == AV_CODEC_ID_RV10 ||                                              // 0.0
/*64  */             s->streams[i]->codecpar->codec_id == AV_CODEC_ID_RV20) {                                              // 0.0
/*66  */             av_log(s, AV_LOG_ERROR,                                                                               // 0.0
/*68  */                    "The Matroska muxer does not yet support muxing %s\n",                                         // 0.0
/*70  */                    avcodec_get_name(s->streams[i]->codecpar->codec_id));                                          // 0.0
/*72  */             return AVERROR_PATCHWELCOME;                                                                          // 0.0
/*74  */         }                                                                                                         // 0.0
/*76  */         if (s->streams[i]->codecpar->codec_id == AV_CODEC_ID_OPUS ||                                              // 0.0
/*78  */             av_dict_get(s->streams[i]->metadata, "stereo_mode", NULL, 0) ||                                       // 0.0
/*80  */             av_dict_get(s->streams[i]->metadata, "alpha_mode", NULL, 0))                                          // 0.0
/*82  */             version = 4;                                                                                          // 0.0
/*84  */     }                                                                                                             // 0.0
/*88  */     mkv->tracks = av_mallocz_array(s->nb_streams, sizeof(*mkv->tracks));                                          // 0.0
/*90  */     if (!mkv->tracks) {                                                                                           // 0.0
/*92  */         ret = AVERROR(ENOMEM);                                                                                    // 0.0
/*94  */         goto fail;                                                                                                // 0.0
/*96  */     }                                                                                                             // 0.0
/*98  */     ebml_header = start_ebml_master(pb, EBML_ID_HEADER, 0);                                                       // 0.0
/*100 */     put_ebml_uint   (pb, EBML_ID_EBMLVERSION        ,           1);                                               // 0.0
/*102 */     put_ebml_uint   (pb, EBML_ID_EBMLREADVERSION    ,           1);                                               // 0.0
/*104 */     put_ebml_uint   (pb, EBML_ID_EBMLMAXIDLENGTH    ,           4);                                               // 0.0
/*106 */     put_ebml_uint   (pb, EBML_ID_EBMLMAXSIZELENGTH  ,           8);                                               // 0.0
/*108 */     put_ebml_string (pb, EBML_ID_DOCTYPE            , s->oformat->name);                                          // 0.0
/*110 */     put_ebml_uint   (pb, EBML_ID_DOCTYPEVERSION     ,     version);                                               // 0.0
/*112 */     put_ebml_uint   (pb, EBML_ID_DOCTYPEREADVERSION ,           2);                                               // 0.0
/*114 */     end_ebml_master(pb, ebml_header);                                                                             // 0.0
/*118 */     mkv->segment = start_ebml_master(pb, MATROSKA_ID_SEGMENT, 0);                                                 // 0.0
/*120 */     mkv->segment_offset = avio_tell(pb);                                                                          // 0.0
/*124 */     // we write 2 seek heads - one at the end of the file to point to each                                        // 0.0
/*126 */     // cluster, and one at the beginning to point to all other level one                                          // 0.0
/*128 */     // elements (including the seek head at the end of the file), which                                           // 0.0
/*130 */     // isn't more than 10 elements if we only write one of each other                                             // 0.0
/*132 */     // currently defined level 1 element                                                                          // 0.0
/*134 */     mkv->main_seekhead    = mkv_start_seekhead(pb, mkv->segment_offset, 10);                                      // 0.0
/*136 */     if (!mkv->main_seekhead) {                                                                                    // 0.0
/*138 */         ret = AVERROR(ENOMEM);                                                                                    // 0.0
/*140 */         goto fail;                                                                                                // 0.0
/*142 */     }                                                                                                             // 0.0
/*146 */     ret = mkv_add_seekhead_entry(mkv->main_seekhead, MATROSKA_ID_INFO, avio_tell(pb));                            // 0.0
/*148 */     if (ret < 0) goto fail;                                                                                       // 0.0
/*152 */     ret = start_ebml_master_crc32(pb, &mkv->info_bc, mkv, &mkv->info, MATROSKA_ID_INFO, 0);                       // 0.0
/*154 */     if (ret < 0)                                                                                                  // 0.0
/*156 */         return ret;                                                                                               // 0.0
/*158 */     pb = mkv->info_bc;                                                                                            // 0.0
/*162 */     put_ebml_uint(pb, MATROSKA_ID_TIMECODESCALE, 1000000);                                                        // 0.0
/*164 */     if ((tag = av_dict_get(s->metadata, "title", NULL, 0)))                                                       // 0.0
/*166 */         put_ebml_string(pb, MATROSKA_ID_TITLE, tag->value);                                                       // 0.0
/*168 */     if (!(s->flags & AVFMT_FLAG_BITEXACT)) {                                                                      // 0.0
/*170 */         put_ebml_string(pb, MATROSKA_ID_MUXINGAPP, LIBAVFORMAT_IDENT);                                            // 0.0
/*172 */         if ((tag = av_dict_get(s->metadata, "encoding_tool", NULL, 0)))                                           // 0.0
/*174 */             put_ebml_string(pb, MATROSKA_ID_WRITINGAPP, tag->value);                                              // 0.0
/*176 */         else                                                                                                      // 0.0
/*178 */             put_ebml_string(pb, MATROSKA_ID_WRITINGAPP, LIBAVFORMAT_IDENT);                                       // 0.0
/*182 */         if (mkv->mode != MODE_WEBM) {                                                                             // 0.0
/*184 */             uint32_t segment_uid[4];                                                                              // 0.0
/*186 */             AVLFG lfg;                                                                                            // 0.0
/*190 */             av_lfg_init(&lfg, av_get_random_seed());                                                              // 0.0
/*194 */             for (i = 0; i < 4; i++)                                                                               // 0.0
/*196 */                 segment_uid[i] = av_lfg_get(&lfg);                                                                // 0.0
/*200 */             put_ebml_binary(pb, MATROSKA_ID_SEGMENTUID, segment_uid, 16);                                         // 0.0
/*202 */         }                                                                                                         // 0.0
/*204 */     } else {                                                                                                      // 0.0
/*206 */         const char *ident = "Lavf";                                                                               // 0.0
/*208 */         put_ebml_string(pb, MATROSKA_ID_MUXINGAPP , ident);                                                       // 0.0
/*210 */         put_ebml_string(pb, MATROSKA_ID_WRITINGAPP, ident);                                                       // 0.0
/*212 */     }                                                                                                             // 0.0
/*216 */     if (ff_parse_creation_time_metadata(s, &creation_time, 0) > 0) {                                              // 0.0
/*218 */         // Adjust time so it's relative to 2001-01-01 and convert to nanoseconds.                                 // 0.0
/*220 */         int64_t date_utc = (creation_time - 978307200000000LL) * 1000;                                            // 0.0
/*222 */         uint8_t date_utc_buf[8];                                                                                  // 0.0
/*224 */         AV_WB64(date_utc_buf, date_utc);                                                                          // 0.0
/*226 */         put_ebml_binary(pb, MATROSKA_ID_DATEUTC, date_utc_buf, 8);                                                // 0.0
/*228 */     }                                                                                                             // 0.0
/*232 */     // reserve space for the duration                                                                             // 0.0
/*234 */     mkv->duration = 0;                                                                                            // 0.0
/*236 */     mkv->duration_offset = avio_tell(pb);                                                                         // 0.0
/*238 */     if (!mkv->is_live) {                                                                                          // 0.0
/*240 */         int64_t metadata_duration = get_metadata_duration(s);                                                     // 0.0
/*244 */         if (s->duration > 0) {                                                                                    // 0.0
/*246 */             int64_t scaledDuration = av_rescale(s->duration, 1000, AV_TIME_BASE);                                 // 0.0
/*248 */             put_ebml_float(pb, MATROSKA_ID_DURATION, scaledDuration);                                             // 0.0
/*250 */             av_log(s, AV_LOG_DEBUG, "Write early duration from recording time = %" PRIu64 "\n", scaledDuration);  // 0.0
/*252 */         } else if (metadata_duration > 0) {                                                                       // 0.0
/*254 */             int64_t scaledDuration = av_rescale(metadata_duration, 1000, AV_TIME_BASE);                           // 0.0
/*256 */             put_ebml_float(pb, MATROSKA_ID_DURATION, scaledDuration);                                             // 0.0
/*258 */             av_log(s, AV_LOG_DEBUG, "Write early duration from metadata = %" PRIu64 "\n", scaledDuration);        // 0.0
/*260 */         } else {                                                                                                  // 0.0
/*262 */             put_ebml_void(pb, 11);              // assumes double-precision float to be written                   // 0.0
/*264 */         }                                                                                                         // 0.0
/*266 */     }                                                                                                             // 0.0
/*268 */     if ((s->pb->seekable & AVIO_SEEKABLE_NORMAL) && !mkv->is_live)                                                // 0.0
/*270 */         end_ebml_master_crc32_preliminary(s->pb, &mkv->info_bc, mkv, mkv->info);                                  // 0.0
/*272 */     else                                                                                                          // 0.0
/*274 */         end_ebml_master_crc32(s->pb, &mkv->info_bc, mkv, mkv->info);                                              // 0.0
/*276 */     pb = s->pb;                                                                                                   // 0.0
/*280 */     // initialize stream_duration fields                                                                          // 0.0
/*282 */     mkv->stream_durations = av_mallocz(s->nb_streams * sizeof(int64_t));                                          // 0.0
/*284 */     mkv->stream_duration_offsets = av_mallocz(s->nb_streams * sizeof(int64_t));                                   // 0.0
/*288 */     ret = mkv_write_tracks(s);                                                                                    // 0.0
/*290 */     if (ret < 0)                                                                                                  // 0.0
/*292 */         goto fail;                                                                                                // 0.0
/*296 */     for (i = 0; i < s->nb_chapters; i++)                                                                          // 0.0
/*298 */         mkv->chapter_id_offset = FFMAX(mkv->chapter_id_offset, 1LL - s->chapters[i]->id);                         // 0.0
/*302 */     ret = mkv_write_chapters(s);                                                                                  // 0.0
/*304 */     if (ret < 0)                                                                                                  // 0.0
/*306 */         goto fail;                                                                                                // 0.0
/*310 */     if (mkv->mode != MODE_WEBM) {                                                                                 // 0.0
/*312 */         ret = mkv_write_attachments(s);                                                                           // 0.0
/*314 */         if (ret < 0)                                                                                              // 0.0
/*316 */             goto fail;                                                                                            // 0.0
/*318 */     }                                                                                                             // 0.0
/*322 */     ret = mkv_write_tags(s);                                                                                      // 0.0
/*324 */     if (ret < 0)                                                                                                  // 0.0
/*326 */         goto fail;                                                                                                // 0.0
/*330 */     if (!(s->pb->seekable & AVIO_SEEKABLE_NORMAL) && !mkv->is_live)                                               // 0.0
/*332 */         mkv_write_seekhead(pb, mkv);                                                                              // 0.0
/*336 */     mkv->cues = mkv_start_cues(mkv->segment_offset);                                                              // 0.0
/*338 */     if (!mkv->cues) {                                                                                             // 0.0
/*340 */         ret = AVERROR(ENOMEM);                                                                                    // 0.0
/*342 */         goto fail;                                                                                                // 0.0
/*344 */     }                                                                                                             // 0.0
/*346 */     if ((pb->seekable & AVIO_SEEKABLE_NORMAL) && mkv->reserve_cues_space) {                                       // 0.0
/*348 */         mkv->cues_pos = avio_tell(pb);                                                                            // 0.0
/*350 */         put_ebml_void(pb, mkv->reserve_cues_space);                                                               // 0.0
/*352 */     }                                                                                                             // 0.0
/*356 */     av_init_packet(&mkv->cur_audio_pkt);                                                                          // 0.0
/*358 */     mkv->cur_audio_pkt.size = 0;                                                                                  // 0.0
/*360 */     mkv->cluster_pos = -1;                                                                                        // 0.0
/*364 */     avio_flush(pb);                                                                                               // 0.0
/*368 */     // start a new cluster every 5 MB or 5 sec, or 32k / 1 sec for streaming or                                   // 0.0
/*370 */     // after 4k and on a keyframe                                                                                 // 0.0
/*372 */     if (pb->seekable & AVIO_SEEKABLE_NORMAL) {                                                                    // 0.0
/*374 */         if (mkv->cluster_time_limit < 0)                                                                          // 0.0
/*376 */             mkv->cluster_time_limit = 5000;                                                                       // 0.0
/*378 */         if (mkv->cluster_size_limit < 0)                                                                          // 0.0
/*380 */             mkv->cluster_size_limit = 5 * 1024 * 1024;                                                            // 0.0
/*382 */     } else {                                                                                                      // 0.0
/*384 */         if (mkv->cluster_time_limit < 0)                                                                          // 0.0
/*386 */             mkv->cluster_time_limit = 1000;                                                                       // 0.0
/*388 */         if (mkv->cluster_size_limit < 0)                                                                          // 0.0
/*390 */             mkv->cluster_size_limit = 32 * 1024;                                                                  // 0.0
/*392 */     }                                                                                                             // 0.0
/*396 */     return 0;                                                                                                     // 0.0
/*398 */ fail:                                                                                                             // 0.0
/*400 */     mkv_free(mkv);                                                                                                // 0.0
/*402 */     return ret;                                                                                                   // 0.0
/*404 */ }                                                                                                                 // 0.0
