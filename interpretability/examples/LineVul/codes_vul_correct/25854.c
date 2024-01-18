// commit message FFmpeg@d9fe6b926c (target=1, prob=0.62848175, correct=True): matroskadec: Fix null pointer exception on corrupted input.
/*0   */ static int matroska_read_header(AVFormatContext *s)                                                                  // (11) 0.0372
/*2   */ {                                                                                                                    // (24) 0.00193
/*4   */     MatroskaDemuxContext *matroska = s->priv_data;                                                                   // (9) 0.03953
/*6   */     EbmlList *attachements_list = &matroska->attachments;                                                            // (8) 0.04074
/*8   */     MatroskaAttachement *attachements;                                                                               // (15) 0.02685
/*10  */     EbmlList *chapters_list = &matroska->chapters;                                                                   // (10) 0.03938
/*12  */     MatroskaChapter *chapters;                                                                                       // (19) 0.0222
/*14  */     MatroskaTrack *tracks;                                                                                           // (22) 0.01997
/*16  */     uint64_t max_start = 0;                                                                                          // (14) 0.02877
/*18  */     int64_t pos;                                                                                                     // (16) 0.02349
/*20  */     Ebml ebml = { 0 };                                                                                               // (20) 0.02119
/*22  */     AVStream *st;                                                                                                    // (23) 0.01664
/*24  */     int i, j, k, res;                                                                                                // (18) 0.02281
/*28  */     matroska->ctx = s;                                                                                               // (21) 0.02087
/*32  */     /* First read the EBML header. */                                                                                // (17) 0.02343
/*34  */     if (ebml_parse(matroska, ebml_syntax, &ebml)                                                                     // (4) 0.04553
/*36  */         || ebml.version > EBML_VERSION       || ebml.max_size > sizeof(uint64_t)                                     // (1) 0.07301
/*38  */         || ebml.id_length > sizeof(uint32_t) || ebml.doctype_version > 3) {                                          // (2) 0.0665
/*40  */         av_log(matroska->ctx, AV_LOG_ERROR,                                                                          // (6) 0.04391
/*42  */                "EBML header using unsupported features\n"                                                            // (5) 0.04549
/*44  */                "(EBML version %"PRIu64", doctype %s, doc version %"PRIu64")\n",                                      // (0) 0.07947
/*46  */                ebml.version, ebml.doctype, ebml.doctype_version);                                                    // (3) 0.06612
/*48  */         ebml_free(ebml_syntax, &ebml);                                                                               // (7) 0.04184
/*50  */         return AVERROR_PATCHWELCOME;                                                                                 // (12) 0.03617
/*52  */     } else if (ebml.doctype_version == 3) {                                                                          // (13) 0.03591
/*54  */         av_log(matroska->ctx, AV_LOG_WARNING,                                                                        // 0.0
/*56  */                "EBML header using unsupported features\n"                                                            // 0.0
/*58  */                "(EBML version %"PRIu64", doctype %s, doc version %"PRIu64")\n",                                      // 0.0
/*60  */                ebml.version, ebml.doctype, ebml.doctype_version);                                                    // 0.0
/*62  */     }                                                                                                                // 0.0
/*64  */     for (i = 0; i < FF_ARRAY_ELEMS(matroska_doctypes); i++)                                                          // 0.0
/*66  */         if (!strcmp(ebml.doctype, matroska_doctypes[i]))                                                             // 0.0
/*68  */             break;                                                                                                   // 0.0
/*70  */     if (i >= FF_ARRAY_ELEMS(matroska_doctypes)) {                                                                    // 0.0
/*72  */         av_log(s, AV_LOG_WARNING, "Unknown EBML doctype '%s'\n", ebml.doctype);                                      // 0.0
/*74  */     }                                                                                                                // 0.0
/*76  */     ebml_free(ebml_syntax, &ebml);                                                                                   // 0.0
/*80  */     /* The next thing is a segment. */                                                                               // 0.0
/*82  */     pos = avio_tell(matroska->ctx->pb);                                                                              // 0.0
/*84  */     res = ebml_parse(matroska, matroska_segments, matroska);                                                         // 0.0
/*86  */     // try resyncing until we find a EBML_STOP type element.                                                         // 0.0
/*88  */     while (res != 1) {                                                                                               // 0.0
/*90  */         res = matroska_resync(matroska, pos);                                                                        // 0.0
/*92  */         if (res < 0)                                                                                                 // 0.0
/*94  */             return res;                                                                                              // 0.0
/*96  */         pos = avio_tell(matroska->ctx->pb);                                                                          // 0.0
/*98  */         res = ebml_parse(matroska, matroska_segment, matroska);                                                      // 0.0
/*100 */     }                                                                                                                // 0.0
/*102 */     matroska_execute_seekhead(matroska);                                                                             // 0.0
/*106 */     if (!matroska->time_scale)                                                                                       // 0.0
/*108 */         matroska->time_scale = 1000000;                                                                              // 0.0
/*110 */     if (matroska->duration)                                                                                          // 0.0
/*112 */         matroska->ctx->duration = matroska->duration * matroska->time_scale                                          // 0.0
/*114 */                                   * 1000 / AV_TIME_BASE;                                                             // 0.0
/*116 */     av_dict_set(&s->metadata, "title", matroska->title, 0);                                                          // 0.0
/*120 */     if (matroska->date_utc.size == 8)                                                                                // 0.0
/*122 */         matroska_metadata_creation_time(&s->metadata, AV_RB64(matroska->date_utc.data));                             // 0.0
/*126 */     tracks = matroska->tracks.elem;                                                                                  // 0.0
/*128 */     for (i=0; i < matroska->tracks.nb_elem; i++) {                                                                   // 0.0
/*130 */         MatroskaTrack *track = &tracks[i];                                                                           // 0.0
/*132 */         enum CodecID codec_id = CODEC_ID_NONE;                                                                       // 0.0
/*134 */         EbmlList *encodings_list = &track->encodings;                                                                // 0.0
/*136 */         MatroskaTrackEncoding *encodings = encodings_list->elem;                                                     // 0.0
/*138 */         uint8_t *extradata = NULL;                                                                                   // 0.0
/*140 */         int extradata_size = 0;                                                                                      // 0.0
/*142 */         int extradata_offset = 0;                                                                                    // 0.0
/*144 */         uint32_t fourcc = 0;                                                                                         // 0.0
/*146 */         AVIOContext b;                                                                                               // 0.0
/*150 */         /* Apply some sanity checks. */                                                                              // 0.0
/*152 */         if (track->type != MATROSKA_TRACK_TYPE_VIDEO &&                                                              // 0.0
/*154 */             track->type != MATROSKA_TRACK_TYPE_AUDIO &&                                                              // 0.0
/*156 */             track->type != MATROSKA_TRACK_TYPE_SUBTITLE) {                                                           // 0.0
/*158 */             av_log(matroska->ctx, AV_LOG_INFO,                                                                       // 0.0
/*160 */                    "Unknown or unsupported track type %"PRIu64"\n",                                                  // 0.0
/*162 */                    track->type);                                                                                     // 0.0
/*164 */             continue;                                                                                                // 0.0
/*166 */         }                                                                                                            // 0.0
/*168 */         if (track->codec_id == NULL)                                                                                 // 0.0
/*170 */             continue;                                                                                                // 0.0
/*174 */         if (track->type == MATROSKA_TRACK_TYPE_VIDEO) {                                                              // 0.0
/*176 */             if (!track->default_duration)                                                                            // 0.0
/*178 */                 track->default_duration = 1000000000/track->video.frame_rate;                                        // 0.0
/*180 */             if (!track->video.display_width)                                                                         // 0.0
/*182 */                 track->video.display_width = track->video.pixel_width;                                               // 0.0
/*184 */             if (!track->video.display_height)                                                                        // 0.0
/*186 */                 track->video.display_height = track->video.pixel_height;                                             // 0.0
/*188 */             if (track->video.color_space.size == 4)                                                                  // 0.0
/*190 */                 fourcc = AV_RL32(track->video.color_space.data);                                                     // 0.0
/*192 */         } else if (track->type == MATROSKA_TRACK_TYPE_AUDIO) {                                                       // 0.0
/*194 */             if (!track->audio.out_samplerate)                                                                        // 0.0
/*196 */                 track->audio.out_samplerate = track->audio.samplerate;                                               // 0.0
/*198 */         }                                                                                                            // 0.0
/*200 */         if (encodings_list->nb_elem > 1) {                                                                           // 0.0
/*202 */             av_log(matroska->ctx, AV_LOG_ERROR,                                                                      // 0.0
/*204 */                    "Multiple combined encodings not supported");                                                     // 0.0
/*206 */         } else if (encodings_list->nb_elem == 1) {                                                                   // 0.0
/*208 */             if (encodings[0].type ||                                                                                 // 0.0
/*210 */                 (encodings[0].compression.algo != MATROSKA_TRACK_ENCODING_COMP_HEADERSTRIP &&                        // 0.0
/*212 */ #if CONFIG_ZLIB                                                                                                      // 0.0
/*214 */                  encodings[0].compression.algo != MATROSKA_TRACK_ENCODING_COMP_ZLIB &&                               // 0.0
/*216 */ #endif                                                                                                               // 0.0
/*218 */ #if CONFIG_BZLIB                                                                                                     // 0.0
/*220 */                  encodings[0].compression.algo != MATROSKA_TRACK_ENCODING_COMP_BZLIB &&                              // 0.0
/*222 */ #endif                                                                                                               // 0.0
/*224 */                  encodings[0].compression.algo != MATROSKA_TRACK_ENCODING_COMP_LZO)) {                               // 0.0
/*226 */                 encodings[0].scope = 0;                                                                              // 0.0
/*228 */                 av_log(matroska->ctx, AV_LOG_ERROR,                                                                  // 0.0
/*230 */                        "Unsupported encoding type");                                                                 // 0.0
/*232 */             } else if (track->codec_priv.size && encodings[0].scope&2) {                                             // 0.0
/*234 */                 uint8_t *codec_priv = track->codec_priv.data;                                                        // 0.0
/*236 */                 int offset = matroska_decode_buffer(&track->codec_priv.data,                                         // 0.0
/*238 */                                                     &track->codec_priv.size,                                         // 0.0
/*240 */                                                     track);                                                          // 0.0
/*242 */                 if (offset < 0) {                                                                                    // 0.0
/*244 */                     track->codec_priv.data = NULL;                                                                   // 0.0
/*246 */                     track->codec_priv.size = 0;                                                                      // 0.0
/*248 */                     av_log(matroska->ctx, AV_LOG_ERROR,                                                              // 0.0
/*250 */                            "Failed to decode codec private data\n");                                                 // 0.0
/*252 */                 } else if (offset > 0) {                                                                             // 0.0
/*254 */                     track->codec_priv.data = av_malloc(track->codec_priv.size + offset);                             // 0.0
/*256 */                     memcpy(track->codec_priv.data,                                                                   // 0.0
/*258 */                            encodings[0].compression.settings.data, offset);                                          // 0.0
/*260 */                     memcpy(track->codec_priv.data+offset, codec_priv,                                                // 0.0
/*262 */                            track->codec_priv.size);                                                                  // 0.0
/*264 */                     track->codec_priv.size += offset;                                                                // 0.0
/*266 */                 }                                                                                                    // 0.0
/*268 */                 if (codec_priv != track->codec_priv.data)                                                            // 0.0
/*270 */                     av_free(codec_priv);                                                                             // 0.0
/*272 */             }                                                                                                        // 0.0
/*274 */         }                                                                                                            // 0.0
/*278 */         for(j=0; ff_mkv_codec_tags[j].id != CODEC_ID_NONE; j++){                                                     // 0.0
/*280 */             if(!strncmp(ff_mkv_codec_tags[j].str, track->codec_id,                                                   // 0.0
/*282 */                         strlen(ff_mkv_codec_tags[j].str))){                                                          // 0.0
/*284 */                 codec_id= ff_mkv_codec_tags[j].id;                                                                   // 0.0
/*286 */                 break;                                                                                               // 0.0
/*288 */             }                                                                                                        // 0.0
/*290 */         }                                                                                                            // 0.0
/*294 */         st = track->stream = avformat_new_stream(s, NULL);                                                           // 0.0
/*296 */         if (st == NULL)                                                                                              // 0.0
/*298 */             return AVERROR(ENOMEM);                                                                                  // 0.0
/*302 */         if (!strcmp(track->codec_id, "V_MS/VFW/FOURCC")                                                              // 0.0
/*304 */             && track->codec_priv.size >= 40                                                                          // 0.0
/*306 */             && track->codec_priv.data != NULL) {                                                                     // 0.0
/*308 */             track->ms_compat = 1;                                                                                    // 0.0
/*310 */             fourcc = AV_RL32(track->codec_priv.data + 16);                                                           // 0.0
/*312 */             codec_id = ff_codec_get_id(ff_codec_bmp_tags, fourcc);                                                   // 0.0
/*314 */             extradata_offset = 40;                                                                                   // 0.0
/*316 */         } else if (!strcmp(track->codec_id, "A_MS/ACM")                                                              // 0.0
/*318 */                    && track->codec_priv.size >= 14                                                                   // 0.0
/*320 */                    && track->codec_priv.data != NULL) {                                                              // 0.0
/*322 */             int ret;                                                                                                 // 0.0
/*324 */             ffio_init_context(&b, track->codec_priv.data, track->codec_priv.size,                                    // 0.0
/*326 */                           AVIO_FLAG_READ, NULL, NULL, NULL, NULL);                                                   // 0.0
/*328 */             ret = ff_get_wav_header(&b, st->codec, track->codec_priv.size);                                          // 0.0
/*330 */             if (ret < 0)                                                                                             // 0.0
/*332 */                 return ret;                                                                                          // 0.0
/*334 */             codec_id = st->codec->codec_id;                                                                          // 0.0
/*336 */             extradata_offset = FFMIN(track->codec_priv.size, 18);                                                    // 0.0
/*338 */         } else if (!strcmp(track->codec_id, "V_QUICKTIME")                                                           // 0.0
/*340 */                    && (track->codec_priv.size >= 86)                                                                 // 0.0
/*342 */                    && (track->codec_priv.data != NULL)) {                                                            // 0.0
/*344 */             fourcc = AV_RL32(track->codec_priv.data);                                                                // 0.0
/*346 */             codec_id = ff_codec_get_id(ff_codec_movvideo_tags, fourcc);                                              // 0.0
/*348 */         } else if (codec_id == CODEC_ID_PCM_S16BE) {                                                                 // 0.0
/*350 */             switch (track->audio.bitdepth) {                                                                         // 0.0
/*352 */             case  8:  codec_id = CODEC_ID_PCM_U8;     break;                                                         // 0.0
/*354 */             case 24:  codec_id = CODEC_ID_PCM_S24BE;  break;                                                         // 0.0
/*356 */             case 32:  codec_id = CODEC_ID_PCM_S32BE;  break;                                                         // 0.0
/*358 */             }                                                                                                        // 0.0
/*360 */         } else if (codec_id == CODEC_ID_PCM_S16LE) {                                                                 // 0.0
/*362 */             switch (track->audio.bitdepth) {                                                                         // 0.0
/*364 */             case  8:  codec_id = CODEC_ID_PCM_U8;     break;                                                         // 0.0
/*366 */             case 24:  codec_id = CODEC_ID_PCM_S24LE;  break;                                                         // 0.0
/*368 */             case 32:  codec_id = CODEC_ID_PCM_S32LE;  break;                                                         // 0.0
/*370 */             }                                                                                                        // 0.0
/*372 */         } else if (codec_id==CODEC_ID_PCM_F32LE && track->audio.bitdepth==64) {                                      // 0.0
/*374 */             codec_id = CODEC_ID_PCM_F64LE;                                                                           // 0.0
/*376 */         } else if (codec_id == CODEC_ID_AAC && !track->codec_priv.size) {                                            // 0.0
/*378 */             int profile = matroska_aac_profile(track->codec_id);                                                     // 0.0
/*380 */             int sri = matroska_aac_sri(track->audio.samplerate);                                                     // 0.0
/*382 */             extradata = av_mallocz(5 + FF_INPUT_BUFFER_PADDING_SIZE);                                                // 0.0
/*384 */             if (extradata == NULL)                                                                                   // 0.0
/*386 */                 return AVERROR(ENOMEM);                                                                              // 0.0
/*388 */             extradata[0] = (profile << 3) | ((sri&0x0E) >> 1);                                                       // 0.0
/*390 */             extradata[1] = ((sri&0x01) << 7) | (track->audio.channels<<3);                                           // 0.0
/*392 */             if (strstr(track->codec_id, "SBR")) {                                                                    // 0.0
/*394 */                 sri = matroska_aac_sri(track->audio.out_samplerate);                                                 // 0.0
/*396 */                 extradata[2] = 0x56;                                                                                 // 0.0
/*398 */                 extradata[3] = 0xE5;                                                                                 // 0.0
/*400 */                 extradata[4] = 0x80 | (sri<<3);                                                                      // 0.0
/*402 */                 extradata_size = 5;                                                                                  // 0.0
/*404 */             } else                                                                                                   // 0.0
/*406 */                 extradata_size = 2;                                                                                  // 0.0
/*408 */         } else if (codec_id == CODEC_ID_TTA) {                                                                       // 0.0
/*410 */             extradata_size = 30;                                                                                     // 0.0
/*412 */             extradata = av_mallocz(extradata_size + FF_INPUT_BUFFER_PADDING_SIZE);                                   // 0.0
/*414 */             if (extradata == NULL)                                                                                   // 0.0
/*416 */                 return AVERROR(ENOMEM);                                                                              // 0.0
/*418 */             ffio_init_context(&b, extradata, extradata_size, 1,                                                      // 0.0
/*420 */                           NULL, NULL, NULL, NULL);                                                                   // 0.0
/*422 */             avio_write(&b, "TTA1", 4);                                                                               // 0.0
/*424 */             avio_wl16(&b, 1);                                                                                        // 0.0
/*426 */             avio_wl16(&b, track->audio.channels);                                                                    // 0.0
/*428 */             avio_wl16(&b, track->audio.bitdepth);                                                                    // 0.0
/*430 */             avio_wl32(&b, track->audio.out_samplerate);                                                              // 0.0
/*432 */             avio_wl32(&b, matroska->ctx->duration * track->audio.out_samplerate);                                    // 0.0
/*434 */         } else if (codec_id == CODEC_ID_RV10 || codec_id == CODEC_ID_RV20 ||                                         // 0.0
/*436 */                    codec_id == CODEC_ID_RV30 || codec_id == CODEC_ID_RV40) {                                         // 0.0
/*438 */             extradata_offset = 26;                                                                                   // 0.0
/*440 */         } else if (codec_id == CODEC_ID_RA_144) {                                                                    // 0.0
/*442 */             track->audio.out_samplerate = 8000;                                                                      // 0.0
/*444 */             track->audio.channels = 1;                                                                               // 0.0
/*446 */         } else if (codec_id == CODEC_ID_RA_288 || codec_id == CODEC_ID_COOK ||                                       // 0.0
/*448 */                    codec_id == CODEC_ID_ATRAC3 || codec_id == CODEC_ID_SIPR) {                                       // 0.0
/*450 */             int flavor;                                                                                              // 0.0
/*452 */             ffio_init_context(&b, track->codec_priv.data,track->codec_priv.size,                                     // 0.0
/*454 */                           0, NULL, NULL, NULL, NULL);                                                                // 0.0
/*456 */             avio_skip(&b, 22);                                                                                       // 0.0
/*458 */             flavor                       = avio_rb16(&b);                                                            // 0.0
/*460 */             track->audio.coded_framesize = avio_rb32(&b);                                                            // 0.0
/*462 */             avio_skip(&b, 12);                                                                                       // 0.0
/*464 */             track->audio.sub_packet_h    = avio_rb16(&b);                                                            // 0.0
/*466 */             track->audio.frame_size      = avio_rb16(&b);                                                            // 0.0
/*468 */             track->audio.sub_packet_size = avio_rb16(&b);                                                            // 0.0
/*470 */             track->audio.buf = av_malloc(track->audio.frame_size * track->audio.sub_packet_h);                       // 0.0
/*472 */             if (codec_id == CODEC_ID_RA_288) {                                                                       // 0.0
/*474 */                 st->codec->block_align = track->audio.coded_framesize;                                               // 0.0
/*476 */                 track->codec_priv.size = 0;                                                                          // 0.0
/*478 */             } else {                                                                                                 // 0.0
/*480 */                 if (codec_id == CODEC_ID_SIPR && flavor < 4) {                                                       // 0.0
/*482 */                     const int sipr_bit_rate[4] = { 6504, 8496, 5000, 16000 };                                        // 0.0
/*484 */                     track->audio.sub_packet_size = ff_sipr_subpk_size[flavor];                                       // 0.0
/*486 */                     st->codec->bit_rate = sipr_bit_rate[flavor];                                                     // 0.0
/*488 */                 }                                                                                                    // 0.0
/*490 */                 st->codec->block_align = track->audio.sub_packet_size;                                               // 0.0
/*492 */                 extradata_offset = 78;                                                                               // 0.0
/*494 */             }                                                                                                        // 0.0
/*496 */         }                                                                                                            // 0.0
/*498 */         track->codec_priv.size -= extradata_offset;                                                                  // 0.0
/*502 */         if (codec_id == CODEC_ID_NONE)                                                                               // 0.0
/*504 */             av_log(matroska->ctx, AV_LOG_INFO,                                                                       // 0.0
/*506 */                    "Unknown/unsupported CodecID %s.\n", track->codec_id);                                            // 0.0
/*510 */         if (track->time_scale < 0.01)                                                                                // 0.0
/*512 */             track->time_scale = 1.0;                                                                                 // 0.0
/*514 */         avpriv_set_pts_info(st, 64, matroska->time_scale*track->time_scale, 1000*1000*1000); /* 64 bit pts in ns */  // 0.0
/*518 */         st->codec->codec_id = codec_id;                                                                              // 0.0
/*520 */         st->start_time = 0;                                                                                          // 0.0
/*522 */         if (strcmp(track->language, "und"))                                                                          // 0.0
/*524 */             av_dict_set(&st->metadata, "language", track->language, 0);                                              // 0.0
/*526 */         av_dict_set(&st->metadata, "title", track->name, 0);                                                         // 0.0
/*530 */         if (track->flag_default)                                                                                     // 0.0
/*532 */             st->disposition |= AV_DISPOSITION_DEFAULT;                                                               // 0.0
/*534 */         if (track->flag_forced)                                                                                      // 0.0
/*536 */             st->disposition |= AV_DISPOSITION_FORCED;                                                                // 0.0
/*540 */         if (!st->codec->extradata) {                                                                                 // 0.0
/*542 */             if(extradata){                                                                                           // 0.0
/*544 */                 st->codec->extradata = extradata;                                                                    // 0.0
/*546 */                 st->codec->extradata_size = extradata_size;                                                          // 0.0
/*548 */             } else if(track->codec_priv.data && track->codec_priv.size > 0){                                         // 0.0
/*550 */                 st->codec->extradata = av_mallocz(track->codec_priv.size +                                           // 0.0
/*552 */                                                   FF_INPUT_BUFFER_PADDING_SIZE);                                     // 0.0
/*554 */                 if(st->codec->extradata == NULL)                                                                     // 0.0
/*556 */                     return AVERROR(ENOMEM);                                                                          // 0.0
/*558 */                 st->codec->extradata_size = track->codec_priv.size;                                                  // 0.0
/*560 */                 memcpy(st->codec->extradata,                                                                         // 0.0
/*562 */                        track->codec_priv.data + extradata_offset,                                                    // 0.0
/*564 */                        track->codec_priv.size);                                                                      // 0.0
/*566 */             }                                                                                                        // 0.0
/*568 */         }                                                                                                            // 0.0
/*572 */         if (track->type == MATROSKA_TRACK_TYPE_VIDEO) {                                                              // 0.0
/*574 */             MatroskaTrackPlane *planes = track->operation.combine_planes.elem;                                       // 0.0
/*578 */             st->codec->codec_type = AVMEDIA_TYPE_VIDEO;                                                              // 0.0
/*580 */             st->codec->codec_tag  = fourcc;                                                                          // 0.0
/*582 */             st->codec->width  = track->video.pixel_width;                                                            // 0.0
/*584 */             st->codec->height = track->video.pixel_height;                                                           // 0.0
/*586 */             av_reduce(&st->sample_aspect_ratio.num,                                                                  // 0.0
/*588 */                       &st->sample_aspect_ratio.den,                                                                  // 0.0
/*590 */                       st->codec->height * track->video.display_width,                                                // 0.0
/*592 */                       st->codec-> width * track->video.display_height,                                               // 0.0
/*594 */                       255);                                                                                          // 0.0
/*596 */             st->need_parsing = AVSTREAM_PARSE_HEADERS;                                                               // 0.0
/*598 */             if (track->default_duration)                                                                             // 0.0
/*600 */                 st->avg_frame_rate = av_d2q(1000000000.0/track->default_duration, INT_MAX);                          // 0.0
/*604 */             /* export stereo mode flag as metadata tag */                                                            // 0.0
/*606 */             if (track->video.stereo_mode && track->video.stereo_mode < MATROSKA_VIDEO_STEREO_MODE_COUNT)             // 0.0
/*608 */                 av_dict_set(&st->metadata, "stereo_mode", matroska_video_stereo_mode[track->video.stereo_mode], 0);  // 0.0
/*612 */             /* if we have virtual track, mark the real tracks */                                                     // 0.0
/*614 */             for (j=0; j < track->operation.combine_planes.nb_elem; j++) {                                            // 0.0
/*616 */                 char buf[32];                                                                                        // 0.0
/*618 */                 if (planes[j].type >= MATROSKA_VIDEO_STEREO_PLANE_COUNT)                                             // 0.0
/*620 */                     continue;                                                                                        // 0.0
/*622 */                 snprintf(buf, sizeof(buf), "%s_%d",                                                                  // 0.0
/*624 */                          matroska_video_stereo_plane[planes[j].type], i);                                            // 0.0
/*626 */                 for (k=0; k < matroska->tracks.nb_elem; k++)                                                         // 0.0
/*628 */                     if (planes[j].uid == tracks[k].uid) {                                                            // 0.0
/*630 */                         av_dict_set(&s->streams[k]->metadata,                                                        // 0.0
/*632 */                                     "stereo_mode", buf, 0);                                                          // 0.0
/*634 */                         break;                                                                                       // 0.0
/*636 */                     }                                                                                                // 0.0
/*638 */             }                                                                                                        // 0.0
/*640 */         } else if (track->type == MATROSKA_TRACK_TYPE_AUDIO) {                                                       // 0.0
/*642 */             st->codec->codec_type = AVMEDIA_TYPE_AUDIO;                                                              // 0.0
/*644 */             st->codec->sample_rate = track->audio.out_samplerate;                                                    // 0.0
/*646 */             st->codec->channels = track->audio.channels;                                                             // 0.0
/*648 */             if (st->codec->codec_id != CODEC_ID_AAC)                                                                 // 0.0
/*650 */             st->need_parsing = AVSTREAM_PARSE_HEADERS;                                                               // 0.0
/*652 */         } else if (track->type == MATROSKA_TRACK_TYPE_SUBTITLE) {                                                    // 0.0
/*654 */             st->codec->codec_type = AVMEDIA_TYPE_SUBTITLE;                                                           // 0.0
/*656 */         }                                                                                                            // 0.0
/*658 */     }                                                                                                                // 0.0
/*662 */     attachements = attachements_list->elem;                                                                          // 0.0
/*664 */     for (j=0; j<attachements_list->nb_elem; j++) {                                                                   // 0.0
/*666 */         if (!(attachements[j].filename && attachements[j].mime &&                                                    // 0.0
/*668 */               attachements[j].bin.data && attachements[j].bin.size > 0)) {                                           // 0.0
/*670 */             av_log(matroska->ctx, AV_LOG_ERROR, "incomplete attachment\n");                                          // 0.0
/*672 */         } else {                                                                                                     // 0.0
/*674 */             AVStream *st = avformat_new_stream(s, NULL);                                                             // 0.0
/*676 */             if (st == NULL)                                                                                          // 0.0
/*678 */                 break;                                                                                               // 0.0
/*680 */             av_dict_set(&st->metadata, "filename",attachements[j].filename, 0);                                      // 0.0
/*682 */             av_dict_set(&st->metadata, "mimetype", attachements[j].mime, 0);                                         // 0.0
/*684 */             st->codec->codec_id = CODEC_ID_NONE;                                                                     // 0.0
/*686 */             st->codec->codec_type = AVMEDIA_TYPE_ATTACHMENT;                                                         // 0.0
/*688 */             st->codec->extradata  = av_malloc(attachements[j].bin.size + FF_INPUT_BUFFER_PADDING_SIZE);              // 0.0
/*690 */             if(st->codec->extradata == NULL)                                                                         // 0.0
/*692 */                 break;                                                                                               // 0.0
/*694 */             st->codec->extradata_size = attachements[j].bin.size;                                                    // 0.0
/*696 */             memcpy(st->codec->extradata, attachements[j].bin.data, attachements[j].bin.size);                        // 0.0
/*700 */             for (i=0; ff_mkv_mime_tags[i].id != CODEC_ID_NONE; i++) {                                                // 0.0
/*702 */                 if (!strncmp(ff_mkv_mime_tags[i].str, attachements[j].mime,                                          // 0.0
/*704 */                              strlen(ff_mkv_mime_tags[i].str))) {                                                     // 0.0
/*706 */                     st->codec->codec_id = ff_mkv_mime_tags[i].id;                                                    // 0.0
/*708 */                     break;                                                                                           // 0.0
/*710 */                 }                                                                                                    // 0.0
/*712 */             }                                                                                                        // 0.0
/*714 */             attachements[j].stream = st;                                                                             // 0.0
/*716 */         }                                                                                                            // 0.0
/*718 */     }                                                                                                                // 0.0
/*722 */     chapters = chapters_list->elem;                                                                                  // 0.0
/*724 */     for (i=0; i<chapters_list->nb_elem; i++)                                                                         // 0.0
/*726 */         if (chapters[i].start != AV_NOPTS_VALUE && chapters[i].uid                                                   // 0.0
/*728 */             && (max_start==0 || chapters[i].start > max_start)) {                                                    // 0.0
/*730 */             chapters[i].chapter =                                                                                    // 0.0
/*732 */             avpriv_new_chapter(s, chapters[i].uid, (AVRational){1, 1000000000},                                      // 0.0
/*734 */                            chapters[i].start, chapters[i].end,                                                       // 0.0
/*736 */                            chapters[i].title);                                                                       // 0.0
/*738 */             av_dict_set(&chapters[i].chapter->metadata,                                                              // 0.0
/*740 */                              "title", chapters[i].title, 0);                                                         // 0.0
/*742 */             max_start = chapters[i].start;                                                                           // 0.0
/*744 */         }                                                                                                            // 0.0
/*748 */     matroska_add_index_entries(matroska);                                                                            // 0.0
/*752 */     matroska_convert_tags(s);                                                                                        // 0.0
/*756 */     return 0;                                                                                                        // 0.0
/*758 */ }                                                                                                                    // 0.0
