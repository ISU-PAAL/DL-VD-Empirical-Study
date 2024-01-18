// commit message FFmpeg@6f7f239604 (target=1, prob=0.99919695, correct=True): libnut: check for av_malloc failure.
/*0   */ static int nut_read_header(AVFormatContext * avf, AVFormatParameters * ap) {                                                           // (6) 0.04297
/*2   */     NUTContext * priv = avf->priv_data;                                                                                                // (13) 0.03125
/*4   */     AVIOContext * bc = avf->pb;                                                                                                        // (16) 0.02734
/*6   */     nut_demuxer_opts_tt dopts = {                                                                                                      // (11) 0.0332
/*8   */         .input = {                                                                                                                     // (20) 0.02148
/*10  */             .priv = bc,                                                                                                                // (14) 0.03125
/*12  */             .seek = av_seek,                                                                                                           // (8) 0.03515
/*14  */             .read = av_read,                                                                                                           // (9) 0.03515
/*16  */             .eof = NULL,                                                                                                               // (12) 0.0332
/*18  */             .file_pos = 0,                                                                                                             // (10) 0.03515
/*20  */         },                                                                                                                             // (24) 0.01562
/*22  */         .alloc = { av_malloc, av_realloc, av_free },                                                                                   // (4) 0.04883
/*24  */         .read_index = 1,                                                                                                               // (17) 0.02734
/*26  */         .cache_syncpoints = 1,                                                                                                         // (15) 0.0293
/*28  */     };                                                                                                                                 // (25) 0.007813
/*30  */     nut_context_tt * nut = priv->nut = nut_demuxer_init(&dopts);                                                                       // (2) 0.05273
/*32  */     nut_stream_header_tt * s;                                                                                                          // (18) 0.02539
/*34  */     int ret, i;                                                                                                                        // (23) 0.01563
/*38  */     if ((ret = nut_read_headers(nut, &s, NULL))) {                                                                                     // (7) 0.04102
/*40  */         av_log(avf, AV_LOG_ERROR, " NUT error: %s\n", nut_error(ret));                                                                 // (1) 0.07031
/*43  */         return -1;                                                                                                                     // (19) 0.02148
/*48  */     priv->s = s;                                                                                                                       // (22) 0.01758
/*52  */     for (i = 0; s[i].type != -1 && i < 2; i++) {                                                                                       // (3) 0.04883
/*54  */         AVStream * st = avformat_new_stream(avf, NULL);                                                                                // (5) 0.04687
/*56  */         int j;                                                                                                                         // (21) 0.01953
/*60  */         for (j = 0; j < s[i].fourcc_len && j < 8; j++) st->codec->codec_tag |= s[i].fourcc[j]<<(j*8);                                  // (0) 0.1094
/*64  */         st->codec->has_b_frames = s[i].decode_delay;                                                                                   // 0.0
/*68  */         st->codec->extradata_size = s[i].codec_specific_len;                                                                           // 0.0
/*70  */         if (st->codec->extradata_size) {                                                                                               // 0.0
/*72  */             st->codec->extradata = av_mallocz(st->codec->extradata_size);                                                              // 0.0
/*78  */             memcpy(st->codec->extradata, s[i].codec_specific, st->codec->extradata_size);                                              // 0.0
/*83  */         avpriv_set_pts_info(avf->streams[i], 60, s[i].time_base.num, s[i].time_base.den);                                              // 0.0
/*85  */         st->start_time = 0;                                                                                                            // 0.0
/*87  */         st->duration = s[i].max_pts;                                                                                                   // 0.0
/*91  */         st->codec->codec_id = ff_codec_get_id(nut_tags, st->codec->codec_tag);                                                         // 0.0
/*95  */         switch(s[i].type) {                                                                                                            // 0.0
/*97  */         case NUT_AUDIO_CLASS:                                                                                                          // 0.0
/*99  */             st->codec->codec_type = AVMEDIA_TYPE_AUDIO;                                                                                // 0.0
/*101 */             if (st->codec->codec_id == CODEC_ID_NONE) st->codec->codec_id = ff_codec_get_id(ff_codec_wav_tags, st->codec->codec_tag);  // 0.0
/*105 */             st->codec->channels = s[i].channel_count;                                                                                  // 0.0
/*107 */             st->codec->sample_rate = s[i].samplerate_num / s[i].samplerate_denom;                                                      // 0.0
/*109 */             break;                                                                                                                     // 0.0
/*111 */         case NUT_VIDEO_CLASS:                                                                                                          // 0.0
/*113 */             st->codec->codec_type = AVMEDIA_TYPE_VIDEO;                                                                                // 0.0
/*115 */             if (st->codec->codec_id == CODEC_ID_NONE) st->codec->codec_id = ff_codec_get_id(ff_codec_bmp_tags, st->codec->codec_tag);  // 0.0
/*119 */             st->codec->width = s[i].width;                                                                                             // 0.0
/*121 */             st->codec->height = s[i].height;                                                                                           // 0.0
/*123 */             st->sample_aspect_ratio.num = s[i].sample_width;                                                                           // 0.0
/*125 */             st->sample_aspect_ratio.den = s[i].sample_height;                                                                          // 0.0
/*127 */             break;                                                                                                                     // 0.0
/*130 */         if (st->codec->codec_id == CODEC_ID_NONE) av_log(avf, AV_LOG_ERROR, "Unknown codec?!\n");                                      // 0.0
/*135 */     return 0;                                                                                                                          // 0.0
