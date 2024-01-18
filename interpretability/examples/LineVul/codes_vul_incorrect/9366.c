// commit message FFmpeg@ec79b1fc88 (target=1, prob=0.4651427, correct=False): wtvdec: fix null pointer dereference
/*0   */ static int parse_chunks(AVFormatContext *s, int mode, int64_t seekts, int *len_ptr)                                                                                                    // (0) 0.06396
/*2   */ {                                                                                                                                                                                      // (22) 0.002681
/*4   */     WtvContext *wtv = s->priv_data;                                                                                                                                                    // (13) 0.03129
/*6   */     AVIOContext *pb = wtv->pb;                                                                                                                                                         // (16) 0.0272
/*8   */     while (!url_feof(pb)) {                                                                                                                                                            // (18) 0.02513
/*10  */         ff_asf_guid g;                                                                                                                                                                 // (14) 0.03082
/*12  */         int len, sid, consumed;                                                                                                                                                        // (17) 0.02699
/*16  */         ff_get_guid(pb, &g);                                                                                                                                                           // (10) 0.0366
/*18  */         len = avio_rl32(pb);                                                                                                                                                           // (12) 0.03274
/*20  */         if (len < 32)                                                                                                                                                                  // (19) 0.02504
/*22  */             break;                                                                                                                                                                     // (20) 0.02503
/*24  */         sid = avio_rl32(pb) & 0x7FFF;                                                                                                                                                  // (7) 0.04621
/*26  */         avio_skip(pb, 8);                                                                                                                                                              // (15) 0.03081
/*28  */         consumed = 32;                                                                                                                                                                 // (21) 0.02119
/*32  */         if (!ff_guidcmp(g, ff_SBE2_STREAM_DESC_EVENT)) {                                                                                                                               // (1) 0.06363
/*34  */             if (ff_find_stream_index(s, sid) < 0) {                                                                                                                                    // (3) 0.05585
/*36  */                 ff_asf_guid mediatype, subtype, formattype;                                                                                                                            // (2) 0.06161
/*38  */                 int size;                                                                                                                                                              // (11) 0.03465
/*40  */                 avio_skip(pb, 28);                                                                                                                                                     // (8) 0.0462
/*42  */                 ff_get_guid(pb, &mediatype);                                                                                                                                           // (4) 0.05584
/*44  */                 ff_get_guid(pb, &subtype);                                                                                                                                             // (6) 0.05391
/*46  */                 avio_skip(pb, 12);                                                                                                                                                     // (9) 0.0462
/*48  */                 ff_get_guid(pb, &formattype);                                                                                                                                          // (5) 0.05391
/*50  */                 size = avio_rl32(pb);                                                                                                                                                  // 0.0
/*52  */                 parse_media_type(s, 0, sid, mediatype, subtype, formattype, size);                                                                                                     // 0.0
/*54  */                 consumed += 92 + size;                                                                                                                                                 // 0.0
/*56  */             }                                                                                                                                                                          // 0.0
/*58  */         } else if (!ff_guidcmp(g, ff_stream2_guid)) {                                                                                                                                  // 0.0
/*60  */             int stream_index = ff_find_stream_index(s, sid);                                                                                                                           // 0.0
/*62  */             if (stream_index >= 0 && !((WtvStream*)s->streams[stream_index]->priv_data)->seen_data) {                                                                                  // 0.0
/*64  */                 ff_asf_guid mediatype, subtype, formattype;                                                                                                                            // 0.0
/*66  */                 int size;                                                                                                                                                              // 0.0
/*68  */                 avio_skip(pb, 12);                                                                                                                                                     // 0.0
/*70  */                 ff_get_guid(pb, &mediatype);                                                                                                                                           // 0.0
/*72  */                 ff_get_guid(pb, &subtype);                                                                                                                                             // 0.0
/*74  */                 avio_skip(pb, 12);                                                                                                                                                     // 0.0
/*76  */                 ff_get_guid(pb, &formattype);                                                                                                                                          // 0.0
/*78  */                 size = avio_rl32(pb);                                                                                                                                                  // 0.0
/*80  */                 parse_media_type(s, s->streams[stream_index], sid, mediatype, subtype, formattype, size);                                                                              // 0.0
/*82  */                 consumed += 76 + size;                                                                                                                                                 // 0.0
/*84  */             }                                                                                                                                                                          // 0.0
/*86  */         } else if (!ff_guidcmp(g, EVENTID_AudioDescriptorSpanningEvent) ||                                                                                                             // 0.0
/*88  */                    !ff_guidcmp(g, EVENTID_CtxADescriptorSpanningEvent) ||                                                                                                              // 0.0
/*90  */                    !ff_guidcmp(g, EVENTID_CSDescriptorSpanningEvent) ||                                                                                                                // 0.0
/*92  */                    !ff_guidcmp(g, EVENTID_StreamIDSpanningEvent) ||                                                                                                                    // 0.0
/*94  */                    !ff_guidcmp(g, EVENTID_SubtitleSpanningEvent) ||                                                                                                                    // 0.0
/*96  */                    !ff_guidcmp(g, EVENTID_TeletextSpanningEvent)) {                                                                                                                    // 0.0
/*98  */             int stream_index = ff_find_stream_index(s, sid);                                                                                                                           // 0.0
/*100 */             if (stream_index >= 0) {                                                                                                                                                   // 0.0
/*102 */                 AVStream *st = s->streams[stream_index];                                                                                                                               // 0.0
/*104 */                 uint8_t buf[258];                                                                                                                                                      // 0.0
/*106 */                 const uint8_t *pbuf = buf;                                                                                                                                             // 0.0
/*108 */                 int buf_size;                                                                                                                                                          // 0.0
/*112 */                 avio_skip(pb, 8);                                                                                                                                                      // 0.0
/*114 */                 consumed += 8;                                                                                                                                                         // 0.0
/*116 */                 if (!ff_guidcmp(g, EVENTID_CtxADescriptorSpanningEvent) ||                                                                                                             // 0.0
/*118 */                     !ff_guidcmp(g, EVENTID_CSDescriptorSpanningEvent)) {                                                                                                               // 0.0
/*120 */                     avio_skip(pb, 6);                                                                                                                                                  // 0.0
/*122 */                     consumed += 6;                                                                                                                                                     // 0.0
/*124 */                 }                                                                                                                                                                      // 0.0
/*128 */                 buf_size = FFMIN(len - consumed, sizeof(buf));                                                                                                                         // 0.0
/*130 */                 avio_read(pb, buf, buf_size);                                                                                                                                          // 0.0
/*132 */                 consumed += buf_size;                                                                                                                                                  // 0.0
/*134 */                 ff_parse_mpeg2_descriptor(s, st, 0, &pbuf, buf + buf_size, NULL, 0, 0, NULL);                                                                                          // 0.0
/*136 */             }                                                                                                                                                                          // 0.0
/*138 */         } else if (!ff_guidcmp(g, EVENTID_AudioTypeSpanningEvent)) {                                                                                                                   // 0.0
/*140 */             int stream_index = ff_find_stream_index(s, sid);                                                                                                                           // 0.0
/*142 */             if (stream_index >= 0) {                                                                                                                                                   // 0.0
/*144 */                 AVStream *st = s->streams[stream_index];                                                                                                                               // 0.0
/*146 */                 int audio_type;                                                                                                                                                        // 0.0
/*148 */                 avio_skip(pb, 8);                                                                                                                                                      // 0.0
/*150 */                 audio_type = avio_r8(pb);                                                                                                                                              // 0.0
/*152 */                 if (audio_type == 2)                                                                                                                                                   // 0.0
/*154 */                     st->disposition |= AV_DISPOSITION_HEARING_IMPAIRED;                                                                                                                // 0.0
/*156 */                 else if (audio_type == 3)                                                                                                                                              // 0.0
/*158 */                     st->disposition |= AV_DISPOSITION_VISUAL_IMPAIRED;                                                                                                                 // 0.0
/*160 */                 consumed += 9;                                                                                                                                                         // 0.0
/*162 */             }                                                                                                                                                                          // 0.0
/*164 */         } else if (!ff_guidcmp(g, EVENTID_DVBScramblingControlSpanningEvent)) {                                                                                                        // 0.0
/*166 */             int stream_index = ff_find_stream_index(s, sid);                                                                                                                           // 0.0
/*168 */             if (stream_index >= 0) {                                                                                                                                                   // 0.0
/*170 */                 avio_skip(pb, 12);                                                                                                                                                     // 0.0
/*172 */                 if (avio_rl32(pb))                                                                                                                                                     // 0.0
/*174 */                     av_log(s, AV_LOG_WARNING, "DVB scrambled stream detected (st:%d), decoding will likely fail\n", stream_index);                                                     // 0.0
/*176 */                 consumed += 16;                                                                                                                                                        // 0.0
/*178 */             }                                                                                                                                                                          // 0.0
/*180 */         } else if (!ff_guidcmp(g, EVENTID_LanguageSpanningEvent)) {                                                                                                                    // 0.0
/*182 */             int stream_index = ff_find_stream_index(s, sid);                                                                                                                           // 0.0
/*184 */             if (stream_index >= 0) {                                                                                                                                                   // 0.0
/*186 */                 AVStream *st = s->streams[stream_index];                                                                                                                               // 0.0
/*188 */                 uint8_t language[4];                                                                                                                                                   // 0.0
/*190 */                 avio_skip(pb, 12);                                                                                                                                                     // 0.0
/*192 */                 avio_read(pb, language, 3);                                                                                                                                            // 0.0
/*194 */                 if (language[0]) {                                                                                                                                                     // 0.0
/*196 */                     language[3] = 0;                                                                                                                                                   // 0.0
/*198 */                     av_dict_set(&st->metadata, "language", language, 0);                                                                                                               // 0.0
/*200 */                     if (!strcmp(language, "nar") || !strcmp(language, "NAR"))                                                                                                          // 0.0
/*202 */                         st->disposition |= AV_DISPOSITION_VISUAL_IMPAIRED;                                                                                                             // 0.0
/*204 */                 }                                                                                                                                                                      // 0.0
/*206 */                 consumed += 15;                                                                                                                                                        // 0.0
/*208 */             }                                                                                                                                                                          // 0.0
/*210 */         } else if (!ff_guidcmp(g, ff_timestamp_guid)) {                                                                                                                                // 0.0
/*212 */             int stream_index = ff_find_stream_index(s, sid);                                                                                                                           // 0.0
/*214 */             if (stream_index >= 0) {                                                                                                                                                   // 0.0
/*216 */                 avio_skip(pb, 8);                                                                                                                                                      // 0.0
/*218 */                 wtv->pts = avio_rl64(pb);                                                                                                                                              // 0.0
/*220 */                 consumed += 16;                                                                                                                                                        // 0.0
/*222 */                 if (wtv->pts == -1)                                                                                                                                                    // 0.0
/*224 */                     wtv->pts = AV_NOPTS_VALUE;                                                                                                                                         // 0.0
/*226 */                 else {                                                                                                                                                                 // 0.0
/*228 */                     wtv->last_valid_pts = wtv->pts;                                                                                                                                    // 0.0
/*230 */                     if (wtv->epoch == AV_NOPTS_VALUE || wtv->pts < wtv->epoch)                                                                                                         // 0.0
/*232 */                         wtv->epoch = wtv->pts;                                                                                                                                         // 0.0
/*234 */                 if (mode == SEEK_TO_PTS && wtv->pts >= seekts) {                                                                                                                       // 0.0
/*236 */                     avio_skip(pb, WTV_PAD8(len) - consumed);                                                                                                                           // 0.0
/*238 */                     return 0;                                                                                                                                                          // 0.0
/*240 */                 }                                                                                                                                                                      // 0.0
/*242 */                 }                                                                                                                                                                      // 0.0
/*244 */             }                                                                                                                                                                          // 0.0
/*246 */         } else if (!ff_guidcmp(g, ff_data_guid)) {                                                                                                                                     // 0.0
/*248 */             int stream_index = ff_find_stream_index(s, sid);                                                                                                                           // 0.0
/*250 */             if (mode == SEEK_TO_DATA && stream_index >= 0 && len > 32 && s->streams[stream_index]->priv_data) {                                                                        // 0.0
/*252 */                 WtvStream *wst = s->streams[stream_index]->priv_data;                                                                                                                  // 0.0
/*254 */                 wst->seen_data = 1;                                                                                                                                                    // 0.0
/*256 */                 if (len_ptr) {                                                                                                                                                         // 0.0
/*258 */                     *len_ptr = len;                                                                                                                                                    // 0.0
/*260 */                 }                                                                                                                                                                      // 0.0
/*262 */                 return stream_index;                                                                                                                                                   // 0.0
/*264 */             }                                                                                                                                                                          // 0.0
/*266 */         } else if (!ff_guidcmp(g, /* DSATTRIB_WMDRMProtectionInfo */ (const ff_asf_guid){0x83,0x95,0x74,0x40,0x9D,0x6B,0xEC,0x4E,0xB4,0x3C,0x67,0xA1,0x80,0x1E,0x1A,0x9B})) {          // 0.0
/*268 */             int stream_index = ff_find_stream_index(s, sid);                                                                                                                           // 0.0
/*270 */             if (stream_index >= 0)                                                                                                                                                     // 0.0
/*272 */                 av_log(s, AV_LOG_WARNING, "encrypted stream detected (st:%d), decoding will likely fail\n", stream_index);                                                             // 0.0
/*274 */         } else if (                                                                                                                                                                    // 0.0
/*276 */             !ff_guidcmp(g, /* DSATTRIB_CAPTURE_STREAMTIME */ (const ff_asf_guid){0x14,0x56,0x1A,0x0C,0xCD,0x30,0x40,0x4F,0xBC,0xBF,0xD0,0x3E,0x52,0x30,0x62,0x07}) ||                  // 0.0
/*278 */             !ff_guidcmp(g, /* DSATTRIB_PBDATAG_ATTRIBUTE */ (const ff_asf_guid){0x79,0x66,0xB5,0xE0,0xB9,0x12,0xCC,0x43,0xB7,0xDF,0x57,0x8C,0xAA,0x5A,0x7B,0x63}) ||                   // 0.0
/*280 */             !ff_guidcmp(g, /* DSATTRIB_PicSampleSeq */ (const ff_asf_guid){0x02,0xAE,0x5B,0x2F,0x8F,0x7B,0x60,0x4F,0x82,0xD6,0xE4,0xEA,0x2F,0x1F,0x4C,0x99}) ||                        // 0.0
/*282 */             !ff_guidcmp(g, /* DSATTRIB_TRANSPORT_PROPERTIES */ ff_DSATTRIB_TRANSPORT_PROPERTIES) ||                                                                                    // 0.0
/*284 */             !ff_guidcmp(g, /* dvr_ms_vid_frame_rep_data */ (const ff_asf_guid){0xCC,0x32,0x64,0xDD,0x29,0xE2,0xDB,0x40,0x80,0xF6,0xD2,0x63,0x28,0xD2,0x76,0x1F}) ||                    // 0.0
/*286 */             !ff_guidcmp(g, /* EVENTID_ChannelChangeSpanningEvent */ (const ff_asf_guid){0xE5,0xC5,0x67,0x90,0x5C,0x4C,0x05,0x42,0x86,0xC8,0x7A,0xFE,0x20,0xFE,0x1E,0xFA}) ||           // 0.0
/*288 */             !ff_guidcmp(g, /* EVENTID_ChannelInfoSpanningEvent */ (const ff_asf_guid){0x80,0x6D,0xF3,0x41,0x32,0x41,0xC2,0x4C,0xB1,0x21,0x01,0xA4,0x32,0x19,0xD8,0x1B}) ||             // 0.0
/*290 */             !ff_guidcmp(g, /* EVENTID_ChannelTypeSpanningEvent */ (const ff_asf_guid){0x51,0x1D,0xAB,0x72,0xD2,0x87,0x9B,0x48,0xBA,0x11,0x0E,0x08,0xDC,0x21,0x02,0x43}) ||             // 0.0
/*292 */             !ff_guidcmp(g, /* EVENTID_PIDListSpanningEvent */ (const ff_asf_guid){0x65,0x8F,0xFC,0x47,0xBB,0xE2,0x34,0x46,0x9C,0xEF,0xFD,0xBF,0xE6,0x26,0x1D,0x5C}) ||                 // 0.0
/*294 */             !ff_guidcmp(g, /* EVENTID_SignalAndServiceStatusSpanningEvent */ (const ff_asf_guid){0xCB,0xC5,0x68,0x80,0x04,0x3C,0x2B,0x49,0xB4,0x7D,0x03,0x08,0x82,0x0D,0xCE,0x51}) ||  // 0.0
/*296 */             !ff_guidcmp(g, /* EVENTID_StreamTypeSpanningEvent */ (const ff_asf_guid){0xBC,0x2E,0xAF,0x82,0xA6,0x30,0x64,0x42,0xA8,0x0B,0xAD,0x2E,0x13,0x72,0xAC,0x60}) ||              // 0.0
/*298 */             !ff_guidcmp(g, (const ff_asf_guid){0x1E,0xBE,0xC3,0xC5,0x43,0x92,0xDC,0x11,0x85,0xE5,0x00,0x12,0x3F,0x6F,0x73,0xB9}) ||                                                    // 0.0
/*300 */             !ff_guidcmp(g, (const ff_asf_guid){0x3B,0x86,0xA2,0xB1,0xEB,0x1E,0xC3,0x44,0x8C,0x88,0x1C,0xA3,0xFF,0xE3,0xE7,0x6A}) ||                                                    // 0.0
/*302 */             !ff_guidcmp(g, (const ff_asf_guid){0x4E,0x7F,0x4C,0x5B,0xC4,0xD0,0x38,0x4B,0xA8,0x3E,0x21,0x7F,0x7B,0xBF,0x52,0xE7}) ||                                                    // 0.0
/*304 */             !ff_guidcmp(g, (const ff_asf_guid){0x63,0x36,0xEB,0xFE,0xA1,0x7E,0xD9,0x11,0x83,0x08,0x00,0x07,0xE9,0x5E,0xAD,0x8D}) ||                                                    // 0.0
/*306 */             !ff_guidcmp(g, (const ff_asf_guid){0x70,0xE9,0xF1,0xF8,0x89,0xA4,0x4C,0x4D,0x83,0x73,0xB8,0x12,0xE0,0xD5,0xF8,0x1E}) ||                                                    // 0.0
/*308 */             !ff_guidcmp(g, ff_index_guid) ||                                                                                                                                           // 0.0
/*310 */             !ff_guidcmp(g, ff_sync_guid) ||                                                                                                                                            // 0.0
/*312 */             !ff_guidcmp(g, ff_stream1_guid) ||                                                                                                                                         // 0.0
/*314 */             !ff_guidcmp(g, (const ff_asf_guid){0xF7,0x10,0x02,0xB9,0xEE,0x7C,0xED,0x4E,0xBD,0x7F,0x05,0x40,0x35,0x86,0x18,0xA1})) {                                                    // 0.0
/*316 */             //ignore known guids                                                                                                                                                       // 0.0
/*318 */         } else                                                                                                                                                                         // 0.0
/*320 */             av_log(s, AV_LOG_WARNING, "unsupported chunk:"FF_PRI_GUID"\n", FF_ARG_GUID(g));                                                                                            // 0.0
/*324 */         avio_skip(pb, WTV_PAD8(len) - consumed);                                                                                                                                       // 0.0
/*326 */     }                                                                                                                                                                                  // 0.0
/*328 */     return AVERROR_EOF;                                                                                                                                                                // 0.0
/*330 */ }                                                                                                                                                                                      // 0.0
