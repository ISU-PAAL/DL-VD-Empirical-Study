// commit message FFmpeg@83548fe894 (target=0, prob=0.43094784, correct=True): lavf: fix usage of AVIOContext.seekable
/*0   */ static int gxf_write_header(AVFormatContext *s)                                                            // (12) 0.0293
/*2   */ {                                                                                                          // (23) 0.001955
/*4   */     AVIOContext *pb = s->pb;                                                                               // (16) 0.02539
/*6   */     GXFContext *gxf = s->priv_data;                                                                        // (11) 0.0332
/*8   */     GXFStreamContext *vsc = NULL;                                                                          // (15) 0.02734
/*10  */     uint8_t tracks[255] = {0};                                                                             // (13) 0.0293
/*12  */     int i, media_info = 0;                                                                                 // (17) 0.02344
/*16  */     if (!pb->seekable) {                                                                                   // (19) 0.02149
/*18  */         av_log(s, AV_LOG_ERROR, "gxf muxer does not support streamed output, patch welcome");              // (3) 0.06641
/*20  */         return -1;                                                                                         // (21) 0.02148
/*22  */     }                                                                                                      // (22) 0.007812
/*26  */     gxf->flags |= 0x00080000; /* material is simple clip */                                                // (7) 0.04102
/*28  */     for (i = 0; i < s->nb_streams; ++i) {                                                                  // (6) 0.04297
/*30  */         AVStream *st = s->streams[i];                                                                      // (9) 0.03711
/*32  */         GXFStreamContext *sc = av_mallocz(sizeof(*sc));                                                    // (5) 0.05078
/*34  */         if (!sc)                                                                                           // (20) 0.02148
/*36  */             return AVERROR(ENOMEM);                                                                        // (8) 0.03906
/*38  */         st->priv_data = sc;                                                                                // (14) 0.0293
/*42  */         sc->media_type = ff_codec_get_tag(gxf_media_types, st->codecpar->codec_id);                        // (0) 0.07812
/*44  */         if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {                                              // (4) 0.05859
/*46  */             if (st->codecpar->codec_id != AV_CODEC_ID_PCM_S16LE) {                                         // (2) 0.07812
/*48  */                 av_log(s, AV_LOG_ERROR, "only 16 BIT PCM LE allowed for now\n");                           // (1) 0.07812
/*50  */                 return -1;                                                                                 // (10) 0.03711
/*52  */             }                                                                                              // (18) 0.02344
/*54  */             if (st->codecpar->sample_rate != 48000) {                                                      // 0.0
/*56  */                 av_log(s, AV_LOG_ERROR, "only 48000hz sampling rate is allowed\n");                        // 0.0
/*58  */                 return -1;                                                                                 // 0.0
/*60  */             }                                                                                              // 0.0
/*62  */             if (st->codecpar->channels != 1) {                                                             // 0.0
/*64  */                 av_log(s, AV_LOG_ERROR, "only mono tracks are allowed\n");                                 // 0.0
/*66  */                 return -1;                                                                                 // 0.0
/*68  */             }                                                                                              // 0.0
/*70  */             sc->track_type = 2;                                                                            // 0.0
/*72  */             sc->sample_rate = st->codecpar->sample_rate;                                                   // 0.0
/*74  */             avpriv_set_pts_info(st, 64, 1, sc->sample_rate);                                               // 0.0
/*76  */             sc->sample_size = 16;                                                                          // 0.0
/*78  */             sc->frame_rate_index = -2;                                                                     // 0.0
/*80  */             sc->lines_index = -2;                                                                          // 0.0
/*82  */             sc->fields = -2;                                                                               // 0.0
/*84  */             gxf->audio_tracks++;                                                                           // 0.0
/*86  */             gxf->flags |= 0x04000000; /* audio is 16 bit pcm */                                            // 0.0
/*88  */             media_info = 'A';                                                                              // 0.0
/*90  */         } else if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {                                       // 0.0
/*92  */             if (i != 0) {                                                                                  // 0.0
/*94  */                 av_log(s, AV_LOG_ERROR, "video stream must be the first track\n");                         // 0.0
/*96  */                 return -1;                                                                                 // 0.0
/*98  */             }                                                                                              // 0.0
/*100 */             /* FIXME check from time_base ? */                                                             // 0.0
/*102 */             if (st->codecpar->height == 480 || st->codecpar->height == 512) { /* NTSC or NTSC+VBI */       // 0.0
/*104 */                 sc->frame_rate_index = 5;                                                                  // 0.0
/*106 */                 sc->sample_rate = 60;                                                                      // 0.0
/*108 */                 gxf->flags |= 0x00000080;                                                                  // 0.0
/*110 */                 gxf->time_base = (AVRational){ 1001, 60000 };                                              // 0.0
/*112 */             } else if (st->codecpar->height == 576 || st->codecpar->height == 608) { /* PAL or PAL+VBI */  // 0.0
/*114 */                 sc->frame_rate_index = 6;                                                                  // 0.0
/*116 */                 sc->media_type++;                                                                          // 0.0
/*118 */                 sc->sample_rate = 50;                                                                      // 0.0
/*120 */                 gxf->flags |= 0x00000040;                                                                  // 0.0
/*122 */                 gxf->time_base = (AVRational){ 1, 50 };                                                    // 0.0
/*124 */             } else {                                                                                       // 0.0
/*126 */                 av_log(s, AV_LOG_ERROR, "unsupported video resolution, "                                   // 0.0
/*128 */                        "gxf muxer only accepts PAL or NTSC resolutions currently\n");                      // 0.0
/*130 */                 return -1;                                                                                 // 0.0
/*132 */             }                                                                                              // 0.0
/*134 */             avpriv_set_pts_info(st, 64, gxf->time_base.num, gxf->time_base.den);                           // 0.0
/*136 */             if (gxf_find_lines_index(st) < 0)                                                              // 0.0
/*138 */                 sc->lines_index = -1;                                                                      // 0.0
/*140 */             sc->sample_size = st->codecpar->bit_rate;                                                      // 0.0
/*142 */             sc->fields = 2; /* interlaced */                                                               // 0.0
/*146 */             vsc = sc;                                                                                      // 0.0
/*150 */             switch (st->codecpar->codec_id) {                                                              // 0.0
/*152 */             case AV_CODEC_ID_MJPEG:                                                                        // 0.0
/*154 */                 sc->track_type = 1;                                                                        // 0.0
/*156 */                 gxf->flags |= 0x00004000;                                                                  // 0.0
/*158 */                 media_info = 'J';                                                                          // 0.0
/*160 */                 break;                                                                                     // 0.0
/*162 */             case AV_CODEC_ID_MPEG1VIDEO:                                                                   // 0.0
/*164 */                 sc->track_type = 9;                                                                        // 0.0
/*166 */                 gxf->mpeg_tracks++;                                                                        // 0.0
/*168 */                 media_info = 'L';                                                                          // 0.0
/*170 */                 break;                                                                                     // 0.0
/*172 */             case AV_CODEC_ID_MPEG2VIDEO:                                                                   // 0.0
/*174 */                 sc->first_gop_closed = -1;                                                                 // 0.0
/*176 */                 sc->track_type = 4;                                                                        // 0.0
/*178 */                 gxf->mpeg_tracks++;                                                                        // 0.0
/*180 */                 gxf->flags |= 0x00008000;                                                                  // 0.0
/*182 */                 media_info = 'M';                                                                          // 0.0
/*184 */                 break;                                                                                     // 0.0
/*186 */             case AV_CODEC_ID_DVVIDEO:                                                                      // 0.0
/*188 */                 if (st->codecpar->format == AV_PIX_FMT_YUV422P) {                                          // 0.0
/*190 */                     sc->media_type += 2;                                                                   // 0.0
/*192 */                     sc->track_type = 6;                                                                    // 0.0
/*194 */                     gxf->flags |= 0x00002000;                                                              // 0.0
/*196 */                     media_info = 'E';                                                                      // 0.0
/*198 */                 } else {                                                                                   // 0.0
/*200 */                     sc->track_type = 5;                                                                    // 0.0
/*202 */                     gxf->flags |= 0x00001000;                                                              // 0.0
/*204 */                     media_info = 'D';                                                                      // 0.0
/*206 */                 }                                                                                          // 0.0
/*208 */                 break;                                                                                     // 0.0
/*210 */             default:                                                                                       // 0.0
/*212 */                 av_log(s, AV_LOG_ERROR, "video codec not supported\n");                                    // 0.0
/*214 */                 return -1;                                                                                 // 0.0
/*216 */             }                                                                                              // 0.0
/*218 */         }                                                                                                  // 0.0
/*220 */         /* FIXME first 10 audio tracks are 0 to 9 next 22 are A to V */                                    // 0.0
/*222 */         sc->media_info = media_info<<8 | ('0'+tracks[media_info]++);                                       // 0.0
/*224 */         sc->order = s->nb_streams - st->index;                                                             // 0.0
/*226 */     }                                                                                                      // 0.0
/*230 */     if (ff_audio_interleave_init(s, GXF_samples_per_frame, (AVRational){ 1, 48000 }) < 0)                  // 0.0
/*232 */         return -1;                                                                                         // 0.0
/*236 */     gxf_init_timecode_track(&gxf->timecode_track, vsc);                                                    // 0.0
/*238 */     gxf->flags |= 0x200000; // time code track is non-drop frame                                           // 0.0
/*242 */     gxf_write_map_packet(s, 0);                                                                            // 0.0
/*244 */     gxf_write_flt_packet(s);                                                                               // 0.0
/*246 */     gxf_write_umf_packet(s);                                                                               // 0.0
/*250 */     gxf->packet_count = 3;                                                                                 // 0.0
/*254 */     avio_flush(pb);                                                                                        // 0.0
/*256 */     return 0;                                                                                              // 0.0
/*258 */ }                                                                                                          // 0.0
