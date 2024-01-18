// commit message FFmpeg@57cd2f7777 (target=0, prob=0.59109277, correct=False): lavf/mpegenc: provide better feedback in case of invalid media type
/*0   */ static av_cold int mpeg_mux_init(AVFormatContext *ctx)                                                // (8) 0.03711
/*2   */ {                                                                                                     // (16) 0.001953
/*4   */     MpegMuxContext *s = ctx->priv_data;                                                               // (9) 0.03516
/*6   */     int bitrate, i, mpa_id, mpv_id, h264_id, mps_id, ac3_id, dts_id, lpcm_id, j;                      // (2) 0.0918
/*8   */     AVStream *st;                                                                                     // (15) 0.01563
/*10  */     StreamInfo *stream;                                                                               // (14) 0.01563
/*12  */     int audio_bitrate;                                                                                // (12) 0.01758
/*14  */     int video_bitrate;                                                                                // (13) 0.01758
/*18  */     s->packet_number = 0;                                                                             // (11) 0.02344
/*20  */     s->is_vcd   =  (CONFIG_MPEG1VCD_MUXER  && ctx->oformat == &ff_mpeg1vcd_muxer);                    // (3) 0.08984
/*22  */     s->is_svcd  =  (CONFIG_MPEG2SVCD_MUXER && ctx->oformat == &ff_mpeg2svcd_muxer);                   // (5) 0.08789
/*24  */     s->is_mpeg2 = ((CONFIG_MPEG2VOB_MUXER  && ctx->oformat == &ff_mpeg2vob_muxer) ||                  // (6) 0.08594
/*26  */                    (CONFIG_MPEG2DVD_MUXER  && ctx->oformat == &ff_mpeg2dvd_muxer) ||                  // (0) 0.09961
/*28  */                    (CONFIG_MPEG2SVCD_MUXER && ctx->oformat == &ff_mpeg2svcd_muxer));                  // (1) 0.09961
/*30  */     s->is_dvd   =  (CONFIG_MPEG2DVD_MUXER  && ctx->oformat == &ff_mpeg2dvd_muxer);                    // (4) 0.08789
/*34  */     if (ctx->packet_size) {                                                                           // (10) 0.02539
/*36  */         if (ctx->packet_size < 20 || ctx->packet_size > (1 << 23) + 10) {                             // (7) 0.06836
/*38  */             av_log(ctx, AV_LOG_ERROR, "Invalid packet size %d\n",                                     // 0.0
/*40  */                    ctx->packet_size);                                                                 // 0.0
/*42  */             goto fail;                                                                                // 0.0
/*44  */         }                                                                                             // 0.0
/*46  */         s->packet_size = ctx->packet_size;                                                            // 0.0
/*48  */     } else                                                                                            // 0.0
/*50  */         s->packet_size = 2048;                                                                        // 0.0
/*52  */     if (ctx->max_delay < 0)     /* Not set by the caller */                                           // 0.0
/*54  */         ctx->max_delay = AV_TIME_BASE*7/10;                                                           // 0.0
/*58  */     s->vcd_padding_bytes_written = 0;                                                                 // 0.0
/*60  */     s->vcd_padding_bitrate_num   = 0;                                                                 // 0.0
/*64  */     s->audio_bound = 0;                                                                               // 0.0
/*66  */     s->video_bound = 0;                                                                               // 0.0
/*70  */     mpa_id  = AUDIO_ID;                                                                               // 0.0
/*72  */     ac3_id  = AC3_ID;                                                                                 // 0.0
/*74  */     dts_id  = DTS_ID;                                                                                 // 0.0
/*76  */     mpv_id  = VIDEO_ID;                                                                               // 0.0
/*78  */     h264_id = H264_ID;                                                                                // 0.0
/*80  */     mps_id  = SUB_ID;                                                                                 // 0.0
/*82  */     lpcm_id = LPCM_ID;                                                                                // 0.0
/*86  */     for (i = 0; i < ctx->nb_streams; i++) {                                                           // 0.0
/*88  */         st     = ctx->streams[i];                                                                     // 0.0
/*90  */         stream = av_mallocz(sizeof(StreamInfo));                                                      // 0.0
/*92  */         if (!stream)                                                                                  // 0.0
/*94  */             goto fail;                                                                                // 0.0
/*96  */         st->priv_data = stream;                                                                       // 0.0
/*100 */         avpriv_set_pts_info(st, 64, 1, 90000);                                                        // 0.0
/*104 */         switch (st->codec->codec_type) {                                                              // 0.0
/*106 */         case AVMEDIA_TYPE_AUDIO:                                                                      // 0.0
/*108 */             if (!s->is_mpeg2 &&                                                                       // 0.0
/*110 */                 (st->codec->codec_id == AV_CODEC_ID_AC3 ||                                            // 0.0
/*112 */                  st->codec->codec_id == AV_CODEC_ID_DTS ||                                            // 0.0
/*114 */                  st->codec->codec_id == AV_CODEC_ID_PCM_S16BE))                                       // 0.0
/*116 */                  av_log(ctx, AV_LOG_WARNING,                                                          // 0.0
/*118 */                         "%s in MPEG-1 system streams is not widely supported, "                       // 0.0
/*120 */                         "consider using the vob or the dvd muxer "                                    // 0.0
/*122 */                         "to force a MPEG-2 program stream.\n",                                        // 0.0
/*124 */                         avcodec_get_name(st->codec->codec_id));                                       // 0.0
/*126 */             if (st->codec->codec_id == AV_CODEC_ID_AC3) {                                             // 0.0
/*128 */                 stream->id = ac3_id++;                                                                // 0.0
/*130 */             } else if (st->codec->codec_id == AV_CODEC_ID_DTS) {                                      // 0.0
/*132 */                 stream->id = dts_id++;                                                                // 0.0
/*134 */             } else if (st->codec->codec_id == AV_CODEC_ID_PCM_S16BE) {                                // 0.0
/*136 */                 stream->id = lpcm_id++;                                                               // 0.0
/*138 */                 for (j = 0; j < 4; j++) {                                                             // 0.0
/*140 */                     if (lpcm_freq_tab[j] == st->codec->sample_rate)                                   // 0.0
/*142 */                         break;                                                                        // 0.0
/*144 */                 }                                                                                     // 0.0
/*146 */                 if (j == 4)                                                                           // 0.0
/*148 */                     goto fail;                                                                        // 0.0
/*150 */                 if (st->codec->channels > 8)                                                          // 0.0
/*152 */                     return -1;                                                                        // 0.0
/*154 */                 stream->lpcm_header[0] = 0x0c;                                                        // 0.0
/*156 */                 stream->lpcm_header[1] = (st->codec->channels - 1) | (j << 4);                        // 0.0
/*158 */                 stream->lpcm_header[2] = 0x80;                                                        // 0.0
/*160 */                 stream->lpcm_align     = st->codec->channels * 2;                                     // 0.0
/*162 */             } else {                                                                                  // 0.0
/*164 */                 stream->id = mpa_id++;                                                                // 0.0
/*166 */             }                                                                                         // 0.0
/*170 */             /* This value HAS to be used for VCD (see VCD standard, p. IV-7).                         // 0.0
/*172 */              * Right now it is also used for everything else. */                                      // 0.0
/*174 */             stream->max_buffer_size = 4 * 1024;                                                       // 0.0
/*176 */             s->audio_bound++;                                                                         // 0.0
/*178 */             break;                                                                                    // 0.0
/*180 */         case AVMEDIA_TYPE_VIDEO:                                                                      // 0.0
/*182 */             if (st->codec->codec_id == AV_CODEC_ID_H264)                                              // 0.0
/*184 */                 stream->id = h264_id++;                                                               // 0.0
/*186 */             else                                                                                      // 0.0
/*188 */                 stream->id = mpv_id++;                                                                // 0.0
/*190 */             if (st->codec->rc_buffer_size)                                                            // 0.0
/*192 */                 stream->max_buffer_size = 6 * 1024 + st->codec->rc_buffer_size / 8;                   // 0.0
/*194 */             else {                                                                                    // 0.0
/*196 */                 av_log(ctx, AV_LOG_WARNING,                                                           // 0.0
/*198 */                        "VBV buffer size not set, using default size of 130KB\n"                       // 0.0
/*200 */                        "If you want the mpeg file to be compliant to some specification\n"            // 0.0
/*202 */                        "Like DVD, VCD or others, make sure you set the correct buffer size\n");       // 0.0
/*204 */                 // FIXME: this is probably too small as default                                       // 0.0
/*206 */                 stream->max_buffer_size = 230 * 1024;                                                 // 0.0
/*208 */             }                                                                                         // 0.0
/*210 */             if (stream->max_buffer_size > 1024 * 8191) {                                              // 0.0
/*212 */                 av_log(ctx, AV_LOG_WARNING, "buffer size %d, too large\n", stream->max_buffer_size);  // 0.0
/*214 */                 stream->max_buffer_size = 1024 * 8191;                                                // 0.0
/*216 */             }                                                                                         // 0.0
/*218 */             s->video_bound++;                                                                         // 0.0
/*220 */             break;                                                                                    // 0.0
/*222 */         case AVMEDIA_TYPE_SUBTITLE:                                                                   // 0.0
/*224 */             stream->id              = mps_id++;                                                       // 0.0
/*226 */             stream->max_buffer_size = 16 * 1024;                                                      // 0.0
/*228 */             break;                                                                                    // 0.0
/*230 */         default:                                                                                      // 0.0
/*232 */             return -1;                                                                                // 0.0
/*234 */         }                                                                                             // 0.0
/*236 */         stream->fifo = av_fifo_alloc(16);                                                             // 0.0
/*238 */         if (!stream->fifo)                                                                            // 0.0
/*240 */             goto fail;                                                                                // 0.0
/*242 */     }                                                                                                 // 0.0
/*244 */     bitrate       = 0;                                                                                // 0.0
/*246 */     audio_bitrate = 0;                                                                                // 0.0
/*248 */     video_bitrate = 0;                                                                                // 0.0
/*250 */     for (i = 0; i < ctx->nb_streams; i++) {                                                           // 0.0
/*252 */         int codec_rate;                                                                               // 0.0
/*254 */         st     = ctx->streams[i];                                                                     // 0.0
/*256 */         stream = (StreamInfo *)st->priv_data;                                                         // 0.0
/*260 */         if (st->codec->rc_max_rate ||                                                                 // 0.0
/*262 */             st->codec->codec_type == AVMEDIA_TYPE_VIDEO)                                              // 0.0
/*264 */             codec_rate = st->codec->rc_max_rate;                                                      // 0.0
/*266 */         else                                                                                          // 0.0
/*268 */             codec_rate = st->codec->bit_rate;                                                         // 0.0
/*272 */         if (!codec_rate)                                                                              // 0.0
/*274 */             codec_rate = (1 << 21) * 8 * 50 / ctx->nb_streams;                                        // 0.0
/*278 */         bitrate += codec_rate;                                                                        // 0.0
/*282 */         if ((stream->id & 0xe0) == AUDIO_ID)                                                          // 0.0
/*284 */             audio_bitrate += codec_rate;                                                              // 0.0
/*286 */         else if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO)                                         // 0.0
/*288 */             video_bitrate += codec_rate;                                                              // 0.0
/*290 */     }                                                                                                 // 0.0
/*294 */     if (s->user_mux_rate) {                                                                           // 0.0
/*296 */         s->mux_rate = (s->user_mux_rate + (8 * 50) - 1) / (8 * 50);                                   // 0.0
/*298 */     } else {                                                                                          // 0.0
/*300 */         /* we increase slightly the bitrate to take into account the                                  // 0.0
/*302 */          * headers. XXX: compute it exactly */                                                        // 0.0
/*304 */         bitrate    += bitrate / 20;                                                                   // 0.0
/*306 */         bitrate    += 10000;                                                                          // 0.0
/*308 */         s->mux_rate = (bitrate + (8 * 50) - 1) / (8 * 50);                                            // 0.0
/*310 */         if (s->mux_rate >= (1<<22)) {                                                                 // 0.0
/*312 */             av_log(ctx, AV_LOG_WARNING, "mux rate %d is too large\n", s->mux_rate);                   // 0.0
/*314 */             s->mux_rate = (1<<22) - 1;                                                                // 0.0
/*316 */         }                                                                                             // 0.0
/*318 */     }                                                                                                 // 0.0
/*322 */     if (s->is_vcd) {                                                                                  // 0.0
/*324 */         int64_t overhead_rate;                                                                        // 0.0
/*328 */         /* The VCD standard mandates that the mux_rate field is 3528                                  // 0.0
/*330 */          * (see standard p. IV-6).                                                                    // 0.0
/*332 */          * The value is actually "wrong", i.e. if you calculate                                       // 0.0
/*334 */          * it using the normal formula and the 75 sectors per second transfer                         // 0.0
/*336 */          * rate you get a different value because the real pack size is 2324,                         // 0.0
/*338 */          * not 2352. But the standard explicitly specifies that the mux_rate                          // 0.0
/*340 */          * field in the header must have this value. */                                               // 0.0
/*342 */         // s->mux_rate = 2352 * 75 / 50;    /* = 3528 */                                              // 0.0
/*346 */         /* The VCD standard states that the muxed stream must be                                      // 0.0
/*348 */          * exactly 75 packs / second (the data rate of a single speed cdrom).                         // 0.0
/*350 */          * Since the video bitrate (probably 1150000 bits/sec) will be below                          // 0.0
/*352 */          * the theoretical maximum we have to add some padding packets                                // 0.0
/*354 */          * to make up for the lower data rate.                                                        // 0.0
/*356 */          * (cf. VCD standard p. IV-6 ) */                                                             // 0.0
/*360 */         /* Add the header overhead to the data rate.                                                  // 0.0
/*362 */          * 2279 data bytes per audio pack, 2294 data bytes per video pack */                          // 0.0
/*364 */         overhead_rate  = audio_bitrate * 2294LL * (2324 - 2279);                                      // 0.0
/*366 */         overhead_rate += video_bitrate * 2279LL * (2324 - 2294);                                      // 0.0
/*370 */         /* Add padding so that the full bitrate is 2324*75 bytes/sec */                               // 0.0
/*372 */         s->vcd_padding_bitrate_num = (2324LL * 75 * 8 - bitrate) * 2279 * 2294 - overhead_rate;       // 0.0
/*374 */ #define VCD_PADDING_BITRATE_DEN (2279 * 2294)                                                         // 0.0
/*376 */     }                                                                                                 // 0.0
/*380 */     if (s->is_vcd || s->is_mpeg2)                                                                     // 0.0
/*382 */         /* every packet */                                                                            // 0.0
/*384 */         s->pack_header_freq = 1;                                                                      // 0.0
/*386 */     else                                                                                              // 0.0
/*388 */         /* every 2 seconds */                                                                         // 0.0
/*390 */         s->pack_header_freq = 2 * bitrate / s->packet_size / 8;                                       // 0.0
/*394 */     /* the above seems to make pack_header_freq zero sometimes */                                     // 0.0
/*396 */     if (s->pack_header_freq == 0)                                                                     // 0.0
/*398 */         s->pack_header_freq = 1;                                                                      // 0.0
/*402 */     if (s->is_mpeg2)                                                                                  // 0.0
/*404 */         /* every 200 packets. Need to look at the spec.  */                                           // 0.0
/*406 */         s->system_header_freq = s->pack_header_freq * 40;                                             // 0.0
/*408 */     else if (s->is_vcd)                                                                               // 0.0
/*410 */         /* the standard mandates that there are only two system headers                               // 0.0
/*412 */          * in the whole file: one in the first packet of each stream.                                 // 0.0
/*414 */          * (see standard p. IV-7 and IV-8) */                                                         // 0.0
/*416 */         s->system_header_freq = 0x7fffffff;                                                           // 0.0
/*418 */     else                                                                                              // 0.0
/*420 */         s->system_header_freq = s->pack_header_freq * 5;                                              // 0.0
/*424 */     for (i = 0; i < ctx->nb_streams; i++) {                                                           // 0.0
/*426 */         stream                = ctx->streams[i]->priv_data;                                           // 0.0
/*428 */         stream->packet_number = 0;                                                                    // 0.0
/*430 */     }                                                                                                 // 0.0
/*432 */     s->system_header_size = get_system_header_size(ctx);                                              // 0.0
/*434 */     s->last_scr           = AV_NOPTS_VALUE;                                                           // 0.0
/*436 */     return 0;                                                                                         // 0.0
/*440 */ fail:                                                                                                 // 0.0
/*442 */     for (i = 0; i < ctx->nb_streams; i++)                                                             // 0.0
/*444 */         av_freep(&ctx->streams[i]->priv_data);                                                        // 0.0
/*446 */     return AVERROR(ENOMEM);                                                                           // 0.0
/*448 */ }                                                                                                     // 0.0
