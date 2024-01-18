// commit message FFmpeg@842b6c14bc (target=0, prob=0.67595035, correct=False): avformat/mpegtsenc: Check data array size in mpegts_write_pmt()
/*0   */ static void mpegts_write_pmt(AVFormatContext *s, MpegTSService *service)                                                                    // (4) 0.04688
/*2   */ {                                                                                                                                           // (25) 0.001953
/*4   */     MpegTSWrite *ts = s->priv_data;                                                                                                         // (16) 0.03125
/*6   */     uint8_t data[1012], *q, *desc_length_ptr, *program_info_length_ptr;                                                                     // (0) 0.06055
/*8   */     int val, stream_type, i;                                                                                                                // (21) 0.02344
/*12  */     q = data;                                                                                                                               // (24) 0.01367
/*14  */     put16(&q, 0xe000 | service->pcr_pid);                                                                                                   // (13) 0.03711
/*18  */     program_info_length_ptr = q;                                                                                                            // (18) 0.02539
/*20  */     q += 2; /* patched after */                                                                                                             // (22) 0.02148
/*24  */     /* put program info here */                                                                                                             // (23) 0.01758
/*28  */     val = 0xf000 | (q - program_info_length_ptr - 2);                                                                                       // (6) 0.04297
/*30  */     program_info_length_ptr[0] = val >> 8;                                                                                                  // (15) 0.03516
/*32  */     program_info_length_ptr[1] = val;                                                                                                       // (17) 0.03125
/*36  */     for(i = 0; i < s->nb_streams; i++) {                                                                                                    // (7) 0.04102
/*38  */         AVStream *st = s->streams[i];                                                                                                       // (12) 0.03711
/*40  */         MpegTSWriteStream *ts_st = st->priv_data;                                                                                           // (5) 0.04492
/*42  */         AVDictionaryEntry *lang = av_dict_get(st->metadata, "language", NULL,0);                                                            // (1) 0.06055
/*44  */         switch(st->codec->codec_id) {                                                                                                       // (10) 0.03906
/*46  */         case AV_CODEC_ID_MPEG1VIDEO:                                                                                                        // (8) 0.04102
/*48  */         case AV_CODEC_ID_MPEG2VIDEO:                                                                                                        // (9) 0.04102
/*50  */             stream_type = STREAM_TYPE_VIDEO_MPEG2;                                                                                          // (2) 0.05078
/*52  */             break;                                                                                                                          // (19) 0.02539
/*54  */         case AV_CODEC_ID_MPEG4:                                                                                                             // (11) 0.03906
/*56  */             stream_type = STREAM_TYPE_VIDEO_MPEG4;                                                                                          // (3) 0.05078
/*58  */             break;                                                                                                                          // (20) 0.02539
/*60  */         case AV_CODEC_ID_H264:                                                                                                              // (14) 0.03711
/*62  */             stream_type = STREAM_TYPE_VIDEO_H264;                                                                                           // 0.0
/*64  */             break;                                                                                                                          // 0.0
/*66  */         case AV_CODEC_ID_CAVS:                                                                                                              // 0.0
/*68  */             stream_type = STREAM_TYPE_VIDEO_CAVS;                                                                                           // 0.0
/*70  */             break;                                                                                                                          // 0.0
/*72  */         case AV_CODEC_ID_DIRAC:                                                                                                             // 0.0
/*74  */             stream_type = STREAM_TYPE_VIDEO_DIRAC;                                                                                          // 0.0
/*76  */             break;                                                                                                                          // 0.0
/*78  */         case AV_CODEC_ID_MP2:                                                                                                               // 0.0
/*80  */         case AV_CODEC_ID_MP3:                                                                                                               // 0.0
/*82  */             stream_type = STREAM_TYPE_AUDIO_MPEG1;                                                                                          // 0.0
/*84  */             break;                                                                                                                          // 0.0
/*86  */         case AV_CODEC_ID_AAC:                                                                                                               // 0.0
/*88  */             stream_type = (ts->flags & MPEGTS_FLAG_AAC_LATM) ? STREAM_TYPE_AUDIO_AAC_LATM : STREAM_TYPE_AUDIO_AAC;                          // 0.0
/*90  */             break;                                                                                                                          // 0.0
/*92  */         case AV_CODEC_ID_AAC_LATM:                                                                                                          // 0.0
/*94  */             stream_type = STREAM_TYPE_AUDIO_AAC_LATM;                                                                                       // 0.0
/*96  */             break;                                                                                                                          // 0.0
/*98  */         case AV_CODEC_ID_AC3:                                                                                                               // 0.0
/*100 */             stream_type = STREAM_TYPE_AUDIO_AC3;                                                                                            // 0.0
/*102 */             break;                                                                                                                          // 0.0
/*104 */         default:                                                                                                                            // 0.0
/*106 */             stream_type = STREAM_TYPE_PRIVATE_DATA;                                                                                         // 0.0
/*108 */             break;                                                                                                                          // 0.0
/*110 */         }                                                                                                                                   // 0.0
/*112 */         *q++ = stream_type;                                                                                                                 // 0.0
/*114 */         put16(&q, 0xe000 | ts_st->pid);                                                                                                     // 0.0
/*116 */         desc_length_ptr = q;                                                                                                                // 0.0
/*118 */         q += 2; /* patched after */                                                                                                         // 0.0
/*122 */         /* write optional descriptors here */                                                                                               // 0.0
/*124 */         switch(st->codec->codec_type) {                                                                                                     // 0.0
/*126 */         case AVMEDIA_TYPE_AUDIO:                                                                                                            // 0.0
/*128 */             if(st->codec->codec_id==AV_CODEC_ID_EAC3){                                                                                      // 0.0
/*130 */                 *q++=0x7a; // EAC3 descriptor see A038 DVB SI                                                                               // 0.0
/*132 */                 *q++=1; // 1 byte, all flags sets to 0                                                                                      // 0.0
/*134 */                 *q++=0; // omit all fields...                                                                                               // 0.0
/*136 */             }                                                                                                                               // 0.0
/*138 */             if(st->codec->codec_id==AV_CODEC_ID_S302M){                                                                                     // 0.0
/*140 */                 *q++ = 0x05; /* MPEG-2 registration descriptor*/                                                                            // 0.0
/*142 */                 *q++ = 4;                                                                                                                   // 0.0
/*144 */                 *q++ = 'B';                                                                                                                 // 0.0
/*146 */                 *q++ = 'S';                                                                                                                 // 0.0
/*148 */                 *q++ = 'S';                                                                                                                 // 0.0
/*150 */                 *q++ = 'D';                                                                                                                 // 0.0
/*152 */             }                                                                                                                               // 0.0
/*156 */             if (lang) {                                                                                                                     // 0.0
/*158 */                 char *p;                                                                                                                    // 0.0
/*160 */                 char *next = lang->value;                                                                                                   // 0.0
/*162 */                 uint8_t *len_ptr;                                                                                                           // 0.0
/*166 */                 *q++ = 0x0a; /* ISO 639 language descriptor */                                                                              // 0.0
/*168 */                 len_ptr = q++;                                                                                                              // 0.0
/*170 */                 *len_ptr = 0;                                                                                                               // 0.0
/*174 */                 for (p = lang->value; next && *len_ptr < 255 / 4 * 4; p = next + 1) {                                                       // 0.0
/*176 */                     next = strchr(p, ',');                                                                                                  // 0.0
/*178 */                     if (strlen(p) != 3 && (!next || next != p + 3))                                                                         // 0.0
/*180 */                         continue; /* not a 3-letter code */                                                                                 // 0.0
/*184 */                     *q++ = *p++;                                                                                                            // 0.0
/*186 */                     *q++ = *p++;                                                                                                            // 0.0
/*188 */                     *q++ = *p++;                                                                                                            // 0.0
/*192 */                 if (st->disposition & AV_DISPOSITION_CLEAN_EFFECTS)                                                                         // 0.0
/*194 */                     *q++ = 0x01;                                                                                                            // 0.0
/*196 */                 else if (st->disposition & AV_DISPOSITION_HEARING_IMPAIRED)                                                                 // 0.0
/*198 */                     *q++ = 0x02;                                                                                                            // 0.0
/*200 */                 else if (st->disposition & AV_DISPOSITION_VISUAL_IMPAIRED)                                                                  // 0.0
/*202 */                     *q++ = 0x03;                                                                                                            // 0.0
/*204 */                 else                                                                                                                        // 0.0
/*206 */                     *q++ = 0; /* undefined type */                                                                                          // 0.0
/*210 */                     *len_ptr += 4;                                                                                                          // 0.0
/*212 */                 }                                                                                                                           // 0.0
/*216 */                 if (*len_ptr == 0)                                                                                                          // 0.0
/*218 */                     q -= 2; /* no language codes were written */                                                                            // 0.0
/*220 */             }                                                                                                                               // 0.0
/*222 */             break;                                                                                                                          // 0.0
/*224 */         case AVMEDIA_TYPE_SUBTITLE:                                                                                                         // 0.0
/*226 */             {                                                                                                                               // 0.0
/*228 */                 const char default_language[] = "und";                                                                                      // 0.0
/*230 */                 const char *language = lang && strlen(lang->value) >= 3 ? lang->value : default_language;                                   // 0.0
/*234 */                 if (st->codec->codec_id == AV_CODEC_ID_DVB_SUBTITLE) {                                                                      // 0.0
/*236 */                     uint8_t *len_ptr;                                                                                                       // 0.0
/*238 */                     int extradata_copied = 0;                                                                                               // 0.0
/*242 */                     *q++ = 0x59; /* subtitling_descriptor */                                                                                // 0.0
/*244 */                     len_ptr = q++;                                                                                                          // 0.0
/*248 */                     while (strlen(language) >= 3 && (sizeof(data) - (q - data)) >= 8) { /* 8 bytes per DVB subtitle substream data */       // 0.0
/*250 */                         *q++ = *language++;                                                                                                 // 0.0
/*252 */                         *q++ = *language++;                                                                                                 // 0.0
/*254 */                         *q++ = *language++;                                                                                                 // 0.0
/*256 */                         /* Skip comma */                                                                                                    // 0.0
/*258 */                         if (*language != '\0')                                                                                              // 0.0
/*260 */                             language++;                                                                                                     // 0.0
/*264 */                         if (st->codec->extradata_size - extradata_copied >= 5) {                                                            // 0.0
/*266 */                             *q++ = st->codec->extradata[extradata_copied + 4]; /* subtitling_type */                                        // 0.0
/*268 */                             memcpy(q, st->codec->extradata + extradata_copied, 4); /* composition_page_id and ancillary_page_id */          // 0.0
/*270 */                             extradata_copied += 5;                                                                                          // 0.0
/*272 */                             q += 4;                                                                                                         // 0.0
/*274 */                         } else {                                                                                                            // 0.0
/*276 */                             /* subtitling_type:                                                                                             // 0.0
/*278 */                              * 0x10 - normal with no monitor aspect ratio criticality                                                       // 0.0
/*280 */                              * 0x20 - for the hard of hearing with no monitor aspect ratio criticality */                                   // 0.0
/*282 */                             *q++ = (st->disposition & AV_DISPOSITION_HEARING_IMPAIRED) ? 0x20 : 0x10;                                       // 0.0
/*284 */                             if ((st->codec->extradata_size == 4) && (extradata_copied == 0)) {                                              // 0.0
/*286 */                                 /* support of old 4-byte extradata format */                                                                // 0.0
/*288 */                                 memcpy(q, st->codec->extradata, 4); /* composition_page_id and ancillary_page_id */                         // 0.0
/*290 */                                 extradata_copied += 4;                                                                                      // 0.0
/*292 */                                 q += 4;                                                                                                     // 0.0
/*294 */                             } else {                                                                                                        // 0.0
/*296 */                                 put16(&q, 1); /* composition_page_id */                                                                     // 0.0
/*298 */                                 put16(&q, 1); /* ancillary_page_id */                                                                       // 0.0
/*300 */                             }                                                                                                               // 0.0
/*302 */                         }                                                                                                                   // 0.0
/*304 */                     }                                                                                                                       // 0.0
/*308 */                     *len_ptr = q - len_ptr - 1;                                                                                             // 0.0
/*310 */                 } else if (st->codec->codec_id == AV_CODEC_ID_DVB_TELETEXT) {                                                               // 0.0
/*312 */                     uint8_t *len_ptr = NULL;                                                                                                // 0.0
/*314 */                     int extradata_copied = 0;                                                                                               // 0.0
/*318 */                     /* The descriptor tag. teletext_descriptor */                                                                           // 0.0
/*320 */                     *q++ = 0x56;                                                                                                            // 0.0
/*322 */                     len_ptr = q++;                                                                                                          // 0.0
/*326 */                     while (strlen(language) >= 3) {                                                                                         // 0.0
/*328 */                         *q++ = *language++;                                                                                                 // 0.0
/*330 */                         *q++ = *language++;                                                                                                 // 0.0
/*332 */                         *q++ = *language++;                                                                                                 // 0.0
/*334 */                         /* Skip comma */                                                                                                    // 0.0
/*336 */                         if (*language != '\0')                                                                                              // 0.0
/*338 */                             language++;                                                                                                     // 0.0
/*342 */                         if (st->codec->extradata_size - 1 > extradata_copied) {                                                             // 0.0
/*344 */                             memcpy(q, st->codec->extradata + extradata_copied, 2);                                                          // 0.0
/*346 */                             extradata_copied += 2;                                                                                          // 0.0
/*348 */                             q += 2;                                                                                                         // 0.0
/*350 */                         } else {                                                                                                            // 0.0
/*352 */                             /* The Teletext descriptor:                                                                                     // 0.0
/*354 */                              * teletext_type: This 5-bit field indicates the type of Teletext page indicated. (0x01 Initial Teletext page)  // 0.0
/*356 */                              * teletext_magazine_number: This is a 3-bit field which identifies the magazine number.                        // 0.0
/*358 */                              * teletext_page_number: This is an 8-bit field giving two 4-bit hex digits identifying the page number. */     // 0.0
/*360 */                             *q++ = 0x08;                                                                                                    // 0.0
/*362 */                             *q++ = 0x00;                                                                                                    // 0.0
/*364 */                         }                                                                                                                   // 0.0
/*366 */                     }                                                                                                                       // 0.0
/*370 */                     *len_ptr = q - len_ptr - 1;                                                                                             // 0.0
/*372 */                  }                                                                                                                          // 0.0
/*374 */             }                                                                                                                               // 0.0
/*376 */             break;                                                                                                                          // 0.0
/*378 */         case AVMEDIA_TYPE_VIDEO:                                                                                                            // 0.0
/*380 */             if (stream_type == STREAM_TYPE_VIDEO_DIRAC) {                                                                                   // 0.0
/*382 */                 *q++ = 0x05; /*MPEG-2 registration descriptor*/                                                                             // 0.0
/*384 */                 *q++ = 4;                                                                                                                   // 0.0
/*386 */                 *q++ = 'd';                                                                                                                 // 0.0
/*388 */                 *q++ = 'r';                                                                                                                 // 0.0
/*390 */                 *q++ = 'a';                                                                                                                 // 0.0
/*392 */                 *q++ = 'c';                                                                                                                 // 0.0
/*394 */             }                                                                                                                               // 0.0
/*396 */             break;                                                                                                                          // 0.0
/*398 */         case AVMEDIA_TYPE_DATA:                                                                                                             // 0.0
/*400 */             if (st->codec->codec_id == AV_CODEC_ID_SMPTE_KLV) {                                                                             // 0.0
/*402 */                 *q++ = 0x05; /* MPEG-2 registration descriptor */                                                                           // 0.0
/*404 */                 *q++ = 4;                                                                                                                   // 0.0
/*406 */                 *q++ = 'K';                                                                                                                 // 0.0
/*408 */                 *q++ = 'L';                                                                                                                 // 0.0
/*410 */                 *q++ = 'V';                                                                                                                 // 0.0
/*412 */                 *q++ = 'A';                                                                                                                 // 0.0
/*414 */             }                                                                                                                               // 0.0
/*416 */             break;                                                                                                                          // 0.0
/*418 */         }                                                                                                                                   // 0.0
/*422 */         val = 0xf000 | (q - desc_length_ptr - 2);                                                                                           // 0.0
/*424 */         desc_length_ptr[0] = val >> 8;                                                                                                      // 0.0
/*426 */         desc_length_ptr[1] = val;                                                                                                           // 0.0
/*428 */     }                                                                                                                                       // 0.0
/*430 */     mpegts_write_section1(&service->pmt, PMT_TID, service->sid, ts->tables_version, 0, 0,                                                   // 0.0
/*432 */                           data, q - data);                                                                                                  // 0.0
/*434 */ }                                                                                                                                           // 0.0
