// commit message FFmpeg@435535e411 (target=1, prob=0.53603333, correct=True): jv demuxer: prevent video packet size overflow
/*0   */ static int read_header(AVFormatContext *s,                                                // (1) 0.061
/*2   */                        AVFormatParameters *ap)                                            // (4) 0.0294
/*4   */ {                                                                                         // (26) 0.004378
/*6   */     JVDemuxContext *jv = s->priv_data;                                                    // (14) 0.02138
/*8   */     AVIOContext *pb = s->pb;                                                              // (22) 0.01374
/*10  */     AVStream *vst, *ast;                                                                  // (19) 0.01606
/*12  */     int64_t audio_pts = 0;                                                                // (2) 0.03989
/*14  */     int64_t offset;                                                                       // (0) 0.3578
/*16  */     int i;                                                                                // (25) 0.01098
/*20  */     avio_skip(pb, 80);                                                                    // (21) 0.01415
/*24  */     ast = av_new_stream(s, 0);                                                            // (18) 0.01614
/*26  */     vst = av_new_stream(s, 1);                                                            // (17) 0.01655
/*28  */     if (!ast || !vst)                                                                     // (24) 0.01211
/*30  */         return AVERROR(ENOMEM);                                                           // (20) 0.01576
/*34  */     vst->codec->codec_type  = CODEC_TYPE_VIDEO;                                           // (5) 0.02715
/*36  */     vst->codec->codec_id    = CODEC_ID_JV;                                                // (8) 0.02409
/*38  */     vst->codec->codec_tag   = 0; /* no fourcc */                                          // (11) 0.02295
/*40  */     vst->codec->width       = avio_rl16(pb);                                              // (7) 0.02474
/*42  */     vst->codec->height      = avio_rl16(pb);                                              // (10) 0.02304
/*44  */     vst->nb_frames          =                                                             // (15) 0.02086
/*46  */     ast->nb_index_entries   = avio_rl16(pb);                                              // (12) 0.02283
/*48  */     av_set_pts_info(vst, 64, avio_rl16(pb), 1000);                                        // (3) 0.03185
/*52  */     avio_skip(pb, 4);                                                                     // (23) 0.01282
/*56  */     ast->codec->codec_type  = CODEC_TYPE_AUDIO;                                           // (9) 0.02304
/*58  */     ast->codec->codec_id    = CODEC_ID_PCM_U8;                                            // (6) 0.02648
/*60  */     ast->codec->codec_tag   = 0; /* no fourcc */                                          // (13) 0.02263
/*62  */     ast->codec->sample_rate = avio_rl16(pb);                                              // (16) 0.02002
/*64  */     ast->codec->channels    = 1;                                                          // 0.0
/*66  */     av_set_pts_info(ast, 64, 1, ast->codec->sample_rate);                                 // 0.0
/*70  */     avio_skip(pb, 10);                                                                    // 0.0
/*74  */     ast->index_entries = av_malloc(ast->nb_index_entries * sizeof(*ast->index_entries));  // 0.0
/*76  */     if (!ast->index_entries)                                                              // 0.0
/*78  */         return AVERROR(ENOMEM);                                                           // 0.0
/*82  */     jv->frames = av_malloc(ast->nb_index_entries * sizeof(JVFrame));                      // 0.0
/*84  */     if (!jv->frames)                                                                      // 0.0
/*86  */         return AVERROR(ENOMEM);                                                           // 0.0
/*90  */     offset = 0x68 + ast->nb_index_entries * 16;                                           // 0.0
/*92  */     for(i = 0; i < ast->nb_index_entries; i++) {                                          // 0.0
/*94  */         AVIndexEntry *e   = ast->index_entries + i;                                       // 0.0
/*96  */         JVFrame      *jvf = jv->frames + i;                                               // 0.0
/*100 */         /* total frame size including audio, video, palette data and padding */           // 0.0
/*102 */         e->size         = avio_rl32(pb);                                                  // 0.0
/*104 */         e->timestamp    = i;                                                              // 0.0
/*106 */         e->pos          = offset;                                                         // 0.0
/*108 */         offset         += e->size;                                                        // 0.0
/*112 */         jvf->audio_size = avio_rl32(pb);                                                  // 0.0
/*114 */         jvf->video_size = avio_rl32(pb);                                                  // 0.0
/*116 */         jvf->palette_size = avio_r8(pb) ? 768 : 0;                                        // 0.0
/*120 */         if (avio_r8(pb))                                                                  // 0.0
/*122 */              av_log(s, AV_LOG_WARNING, "unsupported audio codec\n");                      // 0.0
/*124 */         jvf->video_type = avio_r8(pb);                                                    // 0.0
/*126 */         avio_skip(pb, 1);                                                                 // 0.0
/*130 */         e->timestamp = jvf->audio_size ? audio_pts : AV_NOPTS_VALUE;                      // 0.0
/*132 */         audio_pts += jvf->audio_size;                                                     // 0.0
/*136 */         e->flags = jvf->video_type != 1 ? AVINDEX_KEYFRAME : 0;                           // 0.0
/*138 */     }                                                                                     // 0.0
/*142 */     jv->state = JV_AUDIO;                                                                 // 0.0
/*144 */     return 0;                                                                             // 0.0
/*146 */ }                                                                                         // 0.0
