// commit message FFmpeg@3dbc0ff9c3 (target=1, prob=0.60883933, correct=True): iff: fix integer overflow
/*0   */ static int iff_read_header(AVFormatContext *s)                                                                                     // (12) 0.02931
/*2   */ {                                                                                                                                  // (32) 0.001974
/*4   */     IffDemuxContext *iff = s->priv_data;                                                                                           // (6) 0.0332
/*6   */     AVIOContext *pb = s->pb;                                                                                                       // (22) 0.02539
/*8   */     AVStream *st;                                                                                                                  // (28) 0.01562
/*10  */     uint8_t *buf;                                                                                                                  // (26) 0.01953
/*12  */     uint32_t chunk_id, data_size;                                                                                                  // (14) 0.02929
/*14  */     uint32_t screenmode = 0, num, den;                                                                                             // (7) 0.03126
/*16  */     unsigned transparency = 0;                                                                                                     // (29) 0.01562
/*18  */     unsigned masking = 0; // no mask                                                                                               // (23) 0.02343
/*20  */     uint8_t fmt[16];                                                                                                               // (25) 0.02148
/*22  */     int fmt_size;                                                                                                                  // (30) 0.01562
/*26  */     st = avformat_new_stream(s, NULL);                                                                                             // (8) 0.03125
/*28  */     if (!st)                                                                                                                       // (31) 0.01367
/*30  */         return AVERROR(ENOMEM);                                                                                                    // (10) 0.03125
/*34  */     st->codec->channels = 1;                                                                                                       // (21) 0.02539
/*36  */     st->codec->channel_layout = AV_CH_LAYOUT_MONO;                                                                                 // (1) 0.04492
/*38  */     avio_skip(pb, 8);                                                                                                              // (24) 0.02343
/*40  */     // codec_tag used by ByteRun1 decoder to distinguish progressive (PBM) and interlaced (ILBM) content                           // (0) 0.05859
/*42  */     st->codec->codec_tag = avio_rl32(pb);                                                                                          // (2) 0.04101
/*44  */     iff->bitmap_compression = -1;                                                                                                  // (16) 0.02929
/*46  */     iff->svx8_compression = -1;                                                                                                    // (11) 0.03125
/*48  */     iff->maud_bits = -1;                                                                                                           // (20) 0.02734
/*50  */     iff->maud_compression = -1;                                                                                                    // (15) 0.02929
/*54  */     while(!url_feof(pb)) {                                                                                                         // (18) 0.02734
/*56  */         uint64_t orig_pos;                                                                                                         // (17) 0.02929
/*58  */         int res;                                                                                                                   // (27) 0.01953
/*60  */         const char *metadata_tag = NULL;                                                                                           // (9) 0.03125
/*62  */         chunk_id = avio_rl32(pb);                                                                                                  // (3) 0.0371
/*64  */         data_size = avio_rb32(pb);                                                                                                 // (4) 0.0371
/*66  */         orig_pos = avio_tell(pb);                                                                                                  // (5) 0.03515
/*70  */         switch(chunk_id) {                                                                                                         // (13) 0.0293
/*72  */         case ID_VHDR:                                                                                                              // (19) 0.02734
/*74  */             st->codec->codec_type = AVMEDIA_TYPE_AUDIO;                                                                            // 0.0
/*78  */             if (data_size < 14)                                                                                                    // 0.0
/*80  */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*82  */             avio_skip(pb, 12);                                                                                                     // 0.0
/*84  */             st->codec->sample_rate = avio_rb16(pb);                                                                                // 0.0
/*86  */             if (data_size >= 16) {                                                                                                 // 0.0
/*88  */                 avio_skip(pb, 1);                                                                                                  // 0.0
/*90  */                 iff->svx8_compression = avio_r8(pb);                                                                               // 0.0
/*92  */             }                                                                                                                      // 0.0
/*94  */             break;                                                                                                                 // 0.0
/*98  */         case ID_MHDR:                                                                                                              // 0.0
/*100 */             st->codec->codec_type = AVMEDIA_TYPE_AUDIO;                                                                            // 0.0
/*104 */             if (data_size < 32)                                                                                                    // 0.0
/*106 */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*108 */             avio_skip(pb, 4);                                                                                                      // 0.0
/*110 */             iff->maud_bits = avio_rb16(pb);                                                                                        // 0.0
/*112 */             avio_skip(pb, 2);                                                                                                      // 0.0
/*114 */             num = avio_rb32(pb);                                                                                                   // 0.0
/*116 */             den = avio_rb16(pb);                                                                                                   // 0.0
/*118 */             if (!den)                                                                                                              // 0.0
/*120 */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*122 */             avio_skip(pb, 2);                                                                                                      // 0.0
/*124 */             st->codec->sample_rate = num / den;                                                                                    // 0.0
/*126 */             st->codec->channels = avio_rb16(pb);                                                                                   // 0.0
/*128 */             iff->maud_compression = avio_rb16(pb);                                                                                 // 0.0
/*130 */             if (st->codec->channels == 1)                                                                                          // 0.0
/*132 */                 st->codec->channel_layout = AV_CH_LAYOUT_MONO;                                                                     // 0.0
/*134 */             else if (st->codec->channels == 2)                                                                                     // 0.0
/*136 */                 st->codec->channel_layout = AV_CH_LAYOUT_STEREO;                                                                   // 0.0
/*138 */             break;                                                                                                                 // 0.0
/*142 */         case ID_ABIT:                                                                                                              // 0.0
/*144 */         case ID_BODY:                                                                                                              // 0.0
/*146 */         case ID_DBOD:                                                                                                              // 0.0
/*148 */         case ID_MDAT:                                                                                                              // 0.0
/*150 */             iff->body_pos = avio_tell(pb);                                                                                         // 0.0
/*152 */             iff->body_end = iff->body_pos + data_size;                                                                             // 0.0
/*154 */             iff->body_size = data_size;                                                                                            // 0.0
/*156 */             break;                                                                                                                 // 0.0
/*160 */         case ID_CHAN:                                                                                                              // 0.0
/*162 */             if (data_size < 4)                                                                                                     // 0.0
/*164 */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*166 */             if (avio_rb32(pb) < 6) {                                                                                               // 0.0
/*168 */                 st->codec->channels       = 1;                                                                                     // 0.0
/*170 */                 st->codec->channel_layout = AV_CH_LAYOUT_MONO;                                                                     // 0.0
/*172 */             } else {                                                                                                               // 0.0
/*174 */                 st->codec->channels       = 2;                                                                                     // 0.0
/*176 */                 st->codec->channel_layout = AV_CH_LAYOUT_STEREO;                                                                   // 0.0
/*178 */             }                                                                                                                      // 0.0
/*180 */             break;                                                                                                                 // 0.0
/*184 */         case ID_CAMG:                                                                                                              // 0.0
/*186 */             if (data_size < 4)                                                                                                     // 0.0
/*188 */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*190 */             screenmode                = avio_rb32(pb);                                                                             // 0.0
/*192 */             break;                                                                                                                 // 0.0
/*196 */         case ID_CMAP:                                                                                                              // 0.0
/*198 */             if (data_size > INT_MAX - IFF_EXTRA_VIDEO_SIZE - FF_INPUT_BUFFER_PADDING_SIZE)                                         // 0.0
/*200 */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*202 */             st->codec->extradata_size = data_size + IFF_EXTRA_VIDEO_SIZE;                                                          // 0.0
/*204 */             st->codec->extradata      = av_malloc(data_size + IFF_EXTRA_VIDEO_SIZE + FF_INPUT_BUFFER_PADDING_SIZE);                // 0.0
/*206 */             if (!st->codec->extradata)                                                                                             // 0.0
/*208 */                 return AVERROR(ENOMEM);                                                                                            // 0.0
/*210 */             if (avio_read(pb, st->codec->extradata + IFF_EXTRA_VIDEO_SIZE, data_size) < 0)                                         // 0.0
/*212 */                 return AVERROR(EIO);                                                                                               // 0.0
/*214 */             break;                                                                                                                 // 0.0
/*218 */         case ID_BMHD:                                                                                                              // 0.0
/*220 */             st->codec->codec_type            = AVMEDIA_TYPE_VIDEO;                                                                 // 0.0
/*222 */             if (data_size <= 8)                                                                                                    // 0.0
/*224 */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*226 */             st->codec->width                 = avio_rb16(pb);                                                                      // 0.0
/*228 */             st->codec->height                = avio_rb16(pb);                                                                      // 0.0
/*230 */             avio_skip(pb, 4); // x, y offset                                                                                       // 0.0
/*232 */             st->codec->bits_per_coded_sample = avio_r8(pb);                                                                        // 0.0
/*234 */             if (data_size >= 10)                                                                                                   // 0.0
/*236 */                 masking                      = avio_r8(pb);                                                                        // 0.0
/*238 */             if (data_size >= 11)                                                                                                   // 0.0
/*240 */                 iff->bitmap_compression      = avio_r8(pb);                                                                        // 0.0
/*242 */             if (data_size >= 14) {                                                                                                 // 0.0
/*244 */                 avio_skip(pb, 1); // padding                                                                                       // 0.0
/*246 */                 transparency                 = avio_rb16(pb);                                                                      // 0.0
/*248 */             }                                                                                                                      // 0.0
/*250 */             if (data_size >= 16) {                                                                                                 // 0.0
/*252 */                 st->sample_aspect_ratio.num  = avio_r8(pb);                                                                        // 0.0
/*254 */                 st->sample_aspect_ratio.den  = avio_r8(pb);                                                                        // 0.0
/*256 */             }                                                                                                                      // 0.0
/*258 */             break;                                                                                                                 // 0.0
/*262 */         case ID_DPEL:                                                                                                              // 0.0
/*264 */             if (data_size < 4 || (data_size & 3))                                                                                  // 0.0
/*266 */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*268 */             if ((fmt_size = avio_read(pb, fmt, sizeof(fmt))) < 0)                                                                  // 0.0
/*270 */                 return fmt_size;                                                                                                   // 0.0
/*272 */             if (fmt_size == sizeof(deep_rgb24) && !memcmp(fmt, deep_rgb24, sizeof(deep_rgb24)))                                    // 0.0
/*274 */                 st->codec->pix_fmt = AV_PIX_FMT_RGB24;                                                                             // 0.0
/*276 */             else if (fmt_size == sizeof(deep_rgba) && !memcmp(fmt, deep_rgba, sizeof(deep_rgba)))                                  // 0.0
/*278 */                 st->codec->pix_fmt = AV_PIX_FMT_RGBA;                                                                              // 0.0
/*280 */             else if (fmt_size == sizeof(deep_bgra) && !memcmp(fmt, deep_bgra, sizeof(deep_bgra)))                                  // 0.0
/*282 */                 st->codec->pix_fmt = AV_PIX_FMT_BGRA;                                                                              // 0.0
/*284 */             else if (fmt_size == sizeof(deep_argb) && !memcmp(fmt, deep_argb, sizeof(deep_argb)))                                  // 0.0
/*286 */                 st->codec->pix_fmt = AV_PIX_FMT_ARGB;                                                                              // 0.0
/*288 */             else if (fmt_size == sizeof(deep_abgr) && !memcmp(fmt, deep_abgr, sizeof(deep_abgr)))                                  // 0.0
/*290 */                 st->codec->pix_fmt = AV_PIX_FMT_ABGR;                                                                              // 0.0
/*292 */             else {                                                                                                                 // 0.0
/*294 */                 av_log_ask_for_sample(s, "unsupported color format\n");                                                            // 0.0
/*296 */                 return AVERROR_PATCHWELCOME;                                                                                       // 0.0
/*298 */             }                                                                                                                      // 0.0
/*300 */             break;                                                                                                                 // 0.0
/*304 */         case ID_DGBL:                                                                                                              // 0.0
/*306 */             st->codec->codec_type            = AVMEDIA_TYPE_VIDEO;                                                                 // 0.0
/*308 */             if (data_size < 8)                                                                                                     // 0.0
/*310 */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*312 */             st->codec->width                 = avio_rb16(pb);                                                                      // 0.0
/*314 */             st->codec->height                = avio_rb16(pb);                                                                      // 0.0
/*316 */             iff->bitmap_compression          = avio_rb16(pb);                                                                      // 0.0
/*318 */             st->sample_aspect_ratio.num      = avio_r8(pb);                                                                        // 0.0
/*320 */             st->sample_aspect_ratio.den      = avio_r8(pb);                                                                        // 0.0
/*322 */             st->codec->bits_per_coded_sample = 24;                                                                                 // 0.0
/*324 */             break;                                                                                                                 // 0.0
/*328 */         case ID_DLOC:                                                                                                              // 0.0
/*330 */             if (data_size < 4)                                                                                                     // 0.0
/*332 */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*334 */             st->codec->width  = avio_rb16(pb);                                                                                     // 0.0
/*336 */             st->codec->height = avio_rb16(pb);                                                                                     // 0.0
/*338 */             break;                                                                                                                 // 0.0
/*342 */         case ID_TVDC:                                                                                                              // 0.0
/*344 */             if (data_size < sizeof(iff->tvdc))                                                                                     // 0.0
/*346 */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*348 */             res = avio_read(pb, iff->tvdc, sizeof(iff->tvdc));                                                                     // 0.0
/*350 */             if (res < 0)                                                                                                           // 0.0
/*352 */                 return res;                                                                                                        // 0.0
/*354 */             break;                                                                                                                 // 0.0
/*358 */         case ID_ANNO:                                                                                                              // 0.0
/*360 */         case ID_TEXT:      metadata_tag = "comment";   break;                                                                      // 0.0
/*362 */         case ID_AUTH:      metadata_tag = "artist";    break;                                                                      // 0.0
/*364 */         case ID_COPYRIGHT: metadata_tag = "copyright"; break;                                                                      // 0.0
/*366 */         case ID_NAME:      metadata_tag = "title";     break;                                                                      // 0.0
/*368 */         }                                                                                                                          // 0.0
/*372 */         if (metadata_tag) {                                                                                                        // 0.0
/*374 */             if ((res = get_metadata(s, metadata_tag, data_size)) < 0) {                                                            // 0.0
/*376 */                 av_log(s, AV_LOG_ERROR, "cannot allocate metadata tag %s!\n", metadata_tag);                                       // 0.0
/*378 */                 return res;                                                                                                        // 0.0
/*380 */             }                                                                                                                      // 0.0
/*382 */         }                                                                                                                          // 0.0
/*384 */         avio_skip(pb, data_size - (avio_tell(pb) - orig_pos) + (data_size & 1));                                                   // 0.0
/*386 */     }                                                                                                                              // 0.0
/*390 */     avio_seek(pb, iff->body_pos, SEEK_SET);                                                                                        // 0.0
/*394 */     switch(st->codec->codec_type) {                                                                                                // 0.0
/*396 */     case AVMEDIA_TYPE_AUDIO:                                                                                                       // 0.0
/*398 */         avpriv_set_pts_info(st, 32, 1, st->codec->sample_rate);                                                                    // 0.0
/*402 */         if (st->codec->codec_tag == ID_16SV)                                                                                       // 0.0
/*404 */             st->codec->codec_id = AV_CODEC_ID_PCM_S16BE_PLANAR;                                                                    // 0.0
/*406 */         else if (st->codec->codec_tag == ID_MAUD) {                                                                                // 0.0
/*408 */             if (iff->maud_bits == 8 && !iff->maud_compression) {                                                                   // 0.0
/*410 */                 st->codec->codec_id = AV_CODEC_ID_PCM_U8;                                                                          // 0.0
/*412 */             } else if (iff->maud_bits == 16 && !iff->maud_compression) {                                                           // 0.0
/*414 */                 st->codec->codec_id = AV_CODEC_ID_PCM_S16BE;                                                                       // 0.0
/*416 */             } else if (iff->maud_bits ==  8 && iff->maud_compression == 2) {                                                       // 0.0
/*418 */                 st->codec->codec_id = AV_CODEC_ID_PCM_ALAW;                                                                        // 0.0
/*420 */             } else if (iff->maud_bits ==  8 && iff->maud_compression == 3) {                                                       // 0.0
/*422 */                 st->codec->codec_id = AV_CODEC_ID_PCM_MULAW;                                                                       // 0.0
/*424 */             } else {                                                                                                               // 0.0
/*426 */                 av_log_ask_for_sample(s, "unsupported compression %d and bit depth %d\n", iff->maud_compression, iff->maud_bits);  // 0.0
/*428 */                 return AVERROR_PATCHWELCOME;                                                                                       // 0.0
/*430 */             }                                                                                                                      // 0.0
/*434 */             st->codec->bits_per_coded_sample =                                                                                     // 0.0
/*436 */                 av_get_bits_per_sample(st->codec->codec_id);                                                                       // 0.0
/*440 */             st->codec->block_align =                                                                                               // 0.0
/*442 */                 st->codec->bits_per_coded_sample * st->codec->channels / 8;                                                        // 0.0
/*444 */         } else {                                                                                                                   // 0.0
/*446 */         switch (iff->svx8_compression) {                                                                                           // 0.0
/*448 */         case COMP_NONE:                                                                                                            // 0.0
/*450 */             st->codec->codec_id = AV_CODEC_ID_PCM_S8_PLANAR;                                                                       // 0.0
/*452 */             break;                                                                                                                 // 0.0
/*454 */         case COMP_FIB:                                                                                                             // 0.0
/*456 */             st->codec->codec_id = AV_CODEC_ID_8SVX_FIB;                                                                            // 0.0
/*458 */             break;                                                                                                                 // 0.0
/*460 */         case COMP_EXP:                                                                                                             // 0.0
/*462 */             st->codec->codec_id = AV_CODEC_ID_8SVX_EXP;                                                                            // 0.0
/*464 */             break;                                                                                                                 // 0.0
/*466 */         default:                                                                                                                   // 0.0
/*468 */             av_log(s, AV_LOG_ERROR,                                                                                                // 0.0
/*470 */                    "Unknown SVX8 compression method '%d'\n", iff->svx8_compression);                                               // 0.0
/*472 */             return -1;                                                                                                             // 0.0
/*474 */         }                                                                                                                          // 0.0
/*476 */         }                                                                                                                          // 0.0
/*480 */         st->codec->bits_per_coded_sample = av_get_bits_per_sample(st->codec->codec_id);                                            // 0.0
/*482 */         st->codec->bit_rate = st->codec->channels * st->codec->sample_rate * st->codec->bits_per_coded_sample;                     // 0.0
/*484 */         st->codec->block_align = st->codec->channels * st->codec->bits_per_coded_sample;                                           // 0.0
/*486 */         break;                                                                                                                     // 0.0
/*490 */     case AVMEDIA_TYPE_VIDEO:                                                                                                       // 0.0
/*492 */         iff->bpp          = st->codec->bits_per_coded_sample;                                                                      // 0.0
/*494 */         if ((screenmode & 0x800 /* Hold And Modify */) && iff->bpp <= 8) {                                                         // 0.0
/*496 */             iff->ham      = iff->bpp > 6 ? 6 : 4;                                                                                  // 0.0
/*498 */             st->codec->bits_per_coded_sample = 24;                                                                                 // 0.0
/*500 */         }                                                                                                                          // 0.0
/*502 */         iff->flags        = (screenmode & 0x80 /* Extra HalfBrite */) && iff->bpp <= 8;                                            // 0.0
/*504 */         iff->masking      = masking;                                                                                               // 0.0
/*506 */         iff->transparency = transparency;                                                                                          // 0.0
/*510 */         if (!st->codec->extradata) {                                                                                               // 0.0
/*512 */             st->codec->extradata_size = IFF_EXTRA_VIDEO_SIZE;                                                                      // 0.0
/*514 */             st->codec->extradata      = av_malloc(IFF_EXTRA_VIDEO_SIZE + FF_INPUT_BUFFER_PADDING_SIZE);                            // 0.0
/*516 */             if (!st->codec->extradata)                                                                                             // 0.0
/*518 */                 return AVERROR(ENOMEM);                                                                                            // 0.0
/*520 */         }                                                                                                                          // 0.0
/*523 */         buf = st->codec->extradata;                                                                                                // 0.0
/*525 */         bytestream_put_be16(&buf, IFF_EXTRA_VIDEO_SIZE);                                                                           // 0.0
/*527 */         bytestream_put_byte(&buf, iff->bitmap_compression);                                                                        // 0.0
/*529 */         bytestream_put_byte(&buf, iff->bpp);                                                                                       // 0.0
/*531 */         bytestream_put_byte(&buf, iff->ham);                                                                                       // 0.0
/*533 */         bytestream_put_byte(&buf, iff->flags);                                                                                     // 0.0
/*535 */         bytestream_put_be16(&buf, iff->transparency);                                                                              // 0.0
/*537 */         bytestream_put_byte(&buf, iff->masking);                                                                                   // 0.0
/*539 */         bytestream_put_buffer(&buf, iff->tvdc, sizeof(iff->tvdc));                                                                 // 0.0
/*541 */         st->codec->codec_id = AV_CODEC_ID_IFF_ILBM;                                                                                // 0.0
/*543 */         break;                                                                                                                     // 0.0
/*545 */     default:                                                                                                                       // 0.0
/*547 */         return -1;                                                                                                                 // 0.0
/*549 */     }                                                                                                                              // 0.0
/*553 */     return 0;                                                                                                                      // 0.0
/*555 */ }                                                                                                                                  // 0.0
