// commit message FFmpeg@ddef3d902f (target=1, prob=0.43806782, correct=False): avformat, ffmpeg: deprecate old rotation API
/*0   */ static int mov_write_tkhd_tag(AVIOContext *pb, MOVMuxContext *mov,                                 // (6) 0.05078
/*2   */                               MOVTrack *track, AVStream *st)                                       // (3) 0.07617
/*4   */ {                                                                                                  // (20) 0.001953
/*6   */     int64_t duration = av_rescale_rnd(track->track_duration, MOV_TIMESCALE,                        // (4) 0.06055
/*8   */                                       track->timescale, AV_ROUND_UP);                              // (1) 0.0957
/*10  */     int version = duration < INT32_MAX ? 0 : 1;                                                    // (12) 0.0332
/*12  */     int flags   = MOV_TKHD_FLAG_IN_MOVIE;                                                          // (8) 0.04297
/*14  */     int rotation = 0;                                                                              // (17) 0.01563
/*16  */     int group   = 0;                                                                               // (15) 0.01953
/*20  */     uint32_t *display_matrix = NULL;                                                               // (14) 0.0293
/*22  */     int      display_matrix_size, i;                                                               // (10) 0.03516
/*26  */     if (st) {                                                                                      // (16) 0.01563
/*28  */         if (mov->per_stream_grouping)                                                              // (9) 0.03711
/*30  */             group = st->index;                                                                     // (13) 0.0332
/*32  */         else                                                                                       // (18) 0.01562
/*34  */             group = st->codecpar->codec_type;                                                      // (7) 0.04687
/*38  */         display_matrix = (uint32_t*)av_stream_get_side_data(st, AV_PKT_DATA_DISPLAYMATRIX,         // (2) 0.08398
/*40  */                                                             &display_matrix_size);                 // (0) 0.1309
/*42  */         if (display_matrix && display_matrix_size < 9 * sizeof(*display_matrix))                   // (5) 0.05859
/*44  */             display_matrix = NULL;                                                                 // (11) 0.03516
/*46  */     }                                                                                              // (19) 0.007812
/*50  */     if (track->flags & MOV_TRACK_ENABLED)                                                          // 0.0
/*52  */         flags |= MOV_TKHD_FLAG_ENABLED;                                                            // 0.0
/*56  */     if (track->mode == MODE_ISM)                                                                   // 0.0
/*58  */         version = 1;                                                                               // 0.0
/*62  */     (version == 1) ? avio_wb32(pb, 104) : avio_wb32(pb, 92); /* size */                            // 0.0
/*64  */     ffio_wfourcc(pb, "tkhd");                                                                      // 0.0
/*66  */     avio_w8(pb, version);                                                                          // 0.0
/*68  */     avio_wb24(pb, flags);                                                                          // 0.0
/*70  */     if (version == 1) {                                                                            // 0.0
/*72  */         avio_wb64(pb, track->time);                                                                // 0.0
/*74  */         avio_wb64(pb, track->time);                                                                // 0.0
/*76  */     } else {                                                                                       // 0.0
/*78  */         avio_wb32(pb, track->time); /* creation time */                                            // 0.0
/*80  */         avio_wb32(pb, track->time); /* modification time */                                        // 0.0
/*82  */     }                                                                                              // 0.0
/*84  */     avio_wb32(pb, track->track_id); /* track-id */                                                 // 0.0
/*86  */     avio_wb32(pb, 0); /* reserved */                                                               // 0.0
/*88  */     if (!track->entry && mov->mode == MODE_ISM)                                                    // 0.0
/*90  */         (version == 1) ? avio_wb64(pb, UINT64_C(0xffffffffffffffff)) : avio_wb32(pb, 0xffffffff);  // 0.0
/*92  */     else if (!track->entry)                                                                        // 0.0
/*94  */         (version == 1) ? avio_wb64(pb, 0) : avio_wb32(pb, 0);                                      // 0.0
/*96  */     else                                                                                           // 0.0
/*98  */         (version == 1) ? avio_wb64(pb, duration) : avio_wb32(pb, duration);                        // 0.0
/*102 */     avio_wb32(pb, 0); /* reserved */                                                               // 0.0
/*104 */     avio_wb32(pb, 0); /* reserved */                                                               // 0.0
/*106 */     avio_wb16(pb, 0); /* layer */                                                                  // 0.0
/*108 */     avio_wb16(pb, group); /* alternate group) */                                                   // 0.0
/*110 */     /* Volume, only for audio */                                                                   // 0.0
/*112 */     if (track->par->codec_type == AVMEDIA_TYPE_AUDIO)                                              // 0.0
/*114 */         avio_wb16(pb, 0x0100);                                                                     // 0.0
/*116 */     else                                                                                           // 0.0
/*118 */         avio_wb16(pb, 0);                                                                          // 0.0
/*120 */     avio_wb16(pb, 0); /* reserved */                                                               // 0.0
/*124 */     /* Matrix structure */                                                                         // 0.0
/*127 */     if (st && st->metadata) {                                                                      // 0.0
/*129 */         AVDictionaryEntry *rot = av_dict_get(st->metadata, "rotate", NULL, 0);                     // 0.0
/*131 */         rotation = (rot && rot->value) ? atoi(rot->value) : 0;                                     // 0.0
/*133 */     }                                                                                              // 0.0
/*136 */     if (display_matrix) {                                                                          // 0.0
/*138 */         for (i = 0; i < 9; i++)                                                                    // 0.0
/*140 */             avio_wb32(pb, display_matrix[i]);                                                      // 0.0
/*143 */     } else if (rotation == 90) {                                                                   // 0.0
/*145 */         write_matrix(pb,  0,  1, -1,  0, track->par->height, 0);                                   // 0.0
/*147 */     } else if (rotation == 180) {                                                                  // 0.0
/*149 */         write_matrix(pb, -1,  0,  0, -1, track->par->width, track->par->height);                   // 0.0
/*151 */     } else if (rotation == 270) {                                                                  // 0.0
/*153 */         write_matrix(pb,  0, -1,  1,  0, 0, track->par->width);                                    // 0.0
/*156 */     } else {                                                                                       // 0.0
/*158 */         write_matrix(pb,  1,  0,  0,  1, 0, 0);                                                    // 0.0
/*160 */     }                                                                                              // 0.0
/*162 */     /* Track width and height, for visual only */                                                  // 0.0
/*164 */     if (st && (track->par->codec_type == AVMEDIA_TYPE_VIDEO ||                                     // 0.0
/*166 */                track->par->codec_type == AVMEDIA_TYPE_SUBTITLE)) {                                 // 0.0
/*168 */         int64_t track_width_1616;                                                                  // 0.0
/*170 */         if (track->mode == MODE_MOV) {                                                             // 0.0
/*172 */             track_width_1616 = track->par->width * 0x10000ULL;                                     // 0.0
/*174 */         } else {                                                                                   // 0.0
/*176 */             track_width_1616 = av_rescale(st->sample_aspect_ratio.num,                             // 0.0
/*178 */                                                   track->par->width * 0x10000LL,                   // 0.0
/*180 */                                                   st->sample_aspect_ratio.den);                    // 0.0
/*182 */             if (!track_width_1616 ||                                                               // 0.0
/*184 */                 track->height != track->par->height ||                                             // 0.0
/*186 */                 track_width_1616 > UINT32_MAX)                                                     // 0.0
/*188 */                 track_width_1616 = track->par->width * 0x10000ULL;                                 // 0.0
/*190 */         }                                                                                          // 0.0
/*192 */         if (track_width_1616 > UINT32_MAX) {                                                       // 0.0
/*194 */             av_log(mov->fc, AV_LOG_WARNING, "track width is too large\n");                         // 0.0
/*196 */             track_width_1616 = 0;                                                                  // 0.0
/*198 */         }                                                                                          // 0.0
/*200 */         avio_wb32(pb, track_width_1616);                                                           // 0.0
/*202 */         if (track->height > 0xFFFF) {                                                              // 0.0
/*204 */             av_log(mov->fc, AV_LOG_WARNING, "track height is too large\n");                        // 0.0
/*206 */             avio_wb32(pb, 0);                                                                      // 0.0
/*208 */         } else                                                                                     // 0.0
/*210 */             avio_wb32(pb, track->height * 0x10000U);                                               // 0.0
/*212 */     } else {                                                                                       // 0.0
/*214 */         avio_wb32(pb, 0);                                                                          // 0.0
/*216 */         avio_wb32(pb, 0);                                                                          // 0.0
/*218 */     }                                                                                              // 0.0
/*220 */     return 0x5c;                                                                                   // 0.0
/*222 */ }                                                                                                  // 0.0
