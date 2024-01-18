// commit message FFmpeg@5763f67502 (target=1, prob=0.5550656, correct=True): avformat/mov: Check dimensions before setting aspect
/*0   */ static int mov_read_trak(MOVContext *c, AVIOContext *pb, MOVAtom atom)                           // (5) 0.04883
/*2   */ {                                                                                                // (26) 0.001953
/*4   */     AVStream *st;                                                                                // (22) 0.01562
/*6   */     MOVStreamContext *sc;                                                                        // (21) 0.01758
/*8   */     int ret;                                                                                     // (24) 0.01172
/*12  */     st = avformat_new_stream(c->fc, NULL);                                                       // (10) 0.03516
/*14  */     if (!st) return AVERROR(ENOMEM);                                                             // (13) 0.03125
/*16  */     st->id = c->fc->nb_streams;                                                                  // (12) 0.03125
/*18  */     sc = av_mallocz(sizeof(MOVStreamContext));                                                   // (9) 0.03711
/*20  */     if (!sc) return AVERROR(ENOMEM);                                                             // (14) 0.03125
/*24  */     st->priv_data = sc;                                                                          // (18) 0.02148
/*26  */     st->codec->codec_type = AVMEDIA_TYPE_DATA;                                                   // (8) 0.04102
/*28  */     sc->ffindex = st->index;                                                                     // (17) 0.02344
/*32  */     if ((ret = mov_read_default(c, pb, atom)) < 0)                                               // (7) 0.04492
/*34  */         return ret;                                                                              // (19) 0.01953
/*38  */     /* sanity checks */                                                                          // (23) 0.01367
/*40  */     if (sc->chunk_count && (!sc->stts_count || !sc->stsc_count ||                                // (4) 0.05469
/*42  */                             (!sc->sample_size && !sc->sample_count))) {                          // (0) 0.08203
/*44  */         av_log(c->fc, AV_LOG_ERROR, "stream %d, missing mandatory atoms, broken header\n",       // (2) 0.06836
/*46  */                st->index);                                                                       // (11) 0.03516
/*48  */         return 0;                                                                                // (20) 0.01953
/*50  */     }                                                                                            // (25) 0.007812
/*54  */     fix_timescale(c, sc);                                                                        // (16) 0.02344
/*58  */     avpriv_set_pts_info(st, 64, 1, sc->time_scale);                                              // (6) 0.04883
/*62  */     mov_build_index(c, st);                                                                      // (15) 0.02539
/*66  */     if (sc->dref_id-1 < sc->drefs_count && sc->drefs[sc->dref_id-1].path) {                      // (1) 0.07812
/*68  */         MOVDref *dref = &sc->drefs[sc->dref_id - 1];                                             // (3) 0.05859
/*70  */         if (mov_open_dref(&sc->pb, c->fc->filename, dref, &c->fc->interrupt_callback,            // 0.0
/*72  */             c->use_absolute_path, c->fc) < 0)                                                    // 0.0
/*74  */             av_log(c->fc, AV_LOG_ERROR,                                                          // 0.0
/*76  */                    "stream %d, error opening alias: path='%s', dir='%s', "                       // 0.0
/*78  */                    "filename='%s', volume='%s', nlvl_from=%d, nlvl_to=%d\n",                     // 0.0
/*80  */                    st->index, dref->path, dref->dir, dref->filename,                             // 0.0
/*82  */                    dref->volume, dref->nlvl_from, dref->nlvl_to);                                // 0.0
/*84  */     } else {                                                                                     // 0.0
/*86  */         sc->pb = c->fc->pb;                                                                      // 0.0
/*88  */         sc->pb_is_copied = 1;                                                                    // 0.0
/*90  */     }                                                                                            // 0.0
/*94  */     if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO) {                                           // 0.0
/*96  */         if (!st->sample_aspect_ratio.num &&                                                      // 0.0
/*98  */             (st->codec->width != sc->width || st->codec->height != sc->height)) {                // 0.0
/*100 */             st->sample_aspect_ratio = av_d2q(((double)st->codec->height * sc->width) /           // 0.0
/*102 */                                              ((double)st->codec->width * sc->height), INT_MAX);  // 0.0
/*104 */         }                                                                                        // 0.0
/*108 */ #if FF_API_R_FRAME_RATE                                                                          // 0.0
/*110 */         if (sc->stts_count == 1 || (sc->stts_count == 2 && sc->stts_data[1].count == 1))         // 0.0
/*112 */             av_reduce(&st->r_frame_rate.num, &st->r_frame_rate.den,                              // 0.0
/*114 */                       sc->time_scale, sc->stts_data[0].duration, INT_MAX);                       // 0.0
/*116 */ #endif                                                                                           // 0.0
/*118 */     }                                                                                            // 0.0
/*122 */     // done for ai5q, ai52, ai55, ai1q, ai12 and ai15.                                           // 0.0
/*124 */     if (!st->codec->extradata_size && st->codec->codec_id == AV_CODEC_ID_H264 &&                 // 0.0
/*126 */         TAG_IS_AVCI(st->codec->codec_tag)) {                                                     // 0.0
/*128 */         ret = ff_generate_avci_extradata(st);                                                    // 0.0
/*130 */         if (ret < 0)                                                                             // 0.0
/*132 */             return ret;                                                                          // 0.0
/*134 */     }                                                                                            // 0.0
/*138 */     switch (st->codec->codec_id) {                                                               // 0.0
/*140 */ #if CONFIG_H261_DECODER                                                                          // 0.0
/*142 */     case AV_CODEC_ID_H261:                                                                       // 0.0
/*144 */ #endif                                                                                           // 0.0
/*146 */ #if CONFIG_H263_DECODER                                                                          // 0.0
/*148 */     case AV_CODEC_ID_H263:                                                                       // 0.0
/*150 */ #endif                                                                                           // 0.0
/*152 */ #if CONFIG_MPEG4_DECODER                                                                         // 0.0
/*154 */     case AV_CODEC_ID_MPEG4:                                                                      // 0.0
/*156 */ #endif                                                                                           // 0.0
/*158 */         st->codec->width = 0; /* let decoder init width/height */                                // 0.0
/*160 */         st->codec->height= 0;                                                                    // 0.0
/*162 */         break;                                                                                   // 0.0
/*164 */     }                                                                                            // 0.0
/*168 */     /* Do not need those anymore. */                                                             // 0.0
/*170 */     av_freep(&sc->chunk_offsets);                                                                // 0.0
/*172 */     av_freep(&sc->stsc_data);                                                                    // 0.0
/*174 */     av_freep(&sc->sample_sizes);                                                                 // 0.0
/*176 */     av_freep(&sc->keyframes);                                                                    // 0.0
/*178 */     av_freep(&sc->stts_data);                                                                    // 0.0
/*180 */     av_freep(&sc->stps_data);                                                                    // 0.0
/*182 */     av_freep(&sc->elst_data);                                                                    // 0.0
/*184 */     av_freep(&sc->rap_group);                                                                    // 0.0
/*188 */     return 0;                                                                                    // 0.0
/*190 */ }                                                                                                // 0.0
