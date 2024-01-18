// commit message FFmpeg@3a25c707fa (target=0, prob=0.3778515, correct=True): remove vorbis dec hack, decoding will be done anyway to get frame size
/*0   */ static int mov_read_trak(MOVContext *c, ByteIOContext *pb, MOV_atom_t atom)                         // (4) 0.05273
/*2   */ {                                                                                                   // (26) 0.001953
/*4   */     AVStream *st;                                                                                   // (22) 0.01562
/*6   */     MOVStreamContext *sc;                                                                           // (21) 0.01758
/*8   */     int ret;                                                                                        // (24) 0.01172
/*12  */     st = av_new_stream(c->fc, c->fc->nb_streams);                                                   // (5) 0.04687
/*14  */     if (!st) return AVERROR(ENOMEM);                                                                // (13) 0.03125
/*16  */     sc = av_mallocz(sizeof(MOVStreamContext));                                                      // (9) 0.03711
/*18  */     if (!sc) return AVERROR(ENOMEM);                                                                // (14) 0.03125
/*22  */     st->priv_data = sc;                                                                             // (18) 0.02148
/*24  */     st->codec->codec_type = CODEC_TYPE_DATA;                                                        // (7) 0.04102
/*26  */     st->start_time = 0; /* XXX: check */                                                            // (12) 0.03125
/*30  */     if ((ret = mov_read_default(c, pb, atom)) < 0)                                                  // (6) 0.04492
/*32  */         return ret;                                                                                 // (19) 0.01953
/*36  */     /* sanity checks */                                                                             // (23) 0.01367
/*38  */     if(sc->chunk_count && (!sc->stts_count || !sc->sample_to_chunk_sz ||                            // (2) 0.06445
/*40  */                            (!sc->sample_size && !sc->sample_count))){                               // (0) 0.08008
/*42  */         av_log(c->fc, AV_LOG_ERROR, "stream %d, missing mandatory atoms, broken header\n",          // (1) 0.06836
/*44  */                st->index);                                                                          // (11) 0.03516
/*46  */         sc->sample_count = 0; //ignore track                                                        // (10) 0.03516
/*48  */         return 0;                                                                                   // (20) 0.01953
/*50  */     }                                                                                               // (25) 0.007812
/*52  */     if(!sc->time_rate)                                                                              // (16) 0.02344
/*54  */         sc->time_rate=1;                                                                            // (15) 0.0293
/*56  */     if(!sc->time_scale)                                                                             // (17) 0.02344
/*58  */         sc->time_scale= c->time_scale;                                                              // (8) 0.03711
/*60  */     av_set_pts_info(st, 64, sc->time_rate, sc->time_scale);                                         // (3) 0.05469
/*64  */     if (st->codec->codec_type == CODEC_TYPE_AUDIO &&                                                // 0.0
/*66  */         !st->codec->frame_size && sc->stts_count == 1)                                              // 0.0
/*68  */         st->codec->frame_size = av_rescale(sc->time_rate, st->codec->sample_rate, sc->time_scale);  // 0.0
/*72  */     if(st->duration != AV_NOPTS_VALUE){                                                             // 0.0
/*74  */         assert(st->duration % sc->time_rate == 0);                                                  // 0.0
/*76  */         st->duration /= sc->time_rate;                                                              // 0.0
/*78  */     }                                                                                               // 0.0
/*80  */     sc->ffindex = st->index;                                                                        // 0.0
/*82  */     mov_build_index(c, st);                                                                         // 0.0
/*86  */     if (sc->dref_id-1 < sc->drefs_count && sc->drefs[sc->dref_id-1].path) {                         // 0.0
/*88  */         if (url_fopen(&sc->pb, sc->drefs[sc->dref_id-1].path, URL_RDONLY) < 0)                      // 0.0
/*90  */             av_log(c->fc, AV_LOG_ERROR, "stream %d, error opening file %s: %s\n",                   // 0.0
/*92  */                    st->index, sc->drefs[sc->dref_id-1].path, strerror(errno));                      // 0.0
/*94  */     } else                                                                                          // 0.0
/*96  */         sc->pb = c->fc->pb;                                                                         // 0.0
/*100 */     switch (st->codec->codec_id) {                                                                  // 0.0
/*102 */ #ifdef CONFIG_H261_DECODER                                                                          // 0.0
/*104 */     case CODEC_ID_H261:                                                                             // 0.0
/*106 */ #endif                                                                                              // 0.0
/*108 */ #ifdef CONFIG_H263_DECODER                                                                          // 0.0
/*110 */     case CODEC_ID_H263:                                                                             // 0.0
/*112 */ #endif                                                                                              // 0.0
/*114 */ #ifdef CONFIG_MPEG4_DECODER                                                                         // 0.0
/*116 */     case CODEC_ID_MPEG4:                                                                            // 0.0
/*118 */ #endif                                                                                              // 0.0
/*120 */         st->codec->width= 0; /* let decoder init width/height */                                    // 0.0
/*122 */         st->codec->height= 0;                                                                       // 0.0
/*124 */         break;                                                                                      // 0.0
/*126 */ #ifdef CONFIG_VORBIS_DECODER                                                                        // 0.0
/*128 */     case CODEC_ID_VORBIS:                                                                           // 0.0
/*130 */ #endif                                                                                              // 0.0
/*132 */         st->codec->sample_rate= 0; /* let decoder init parameters properly */                       // 0.0
/*134 */         break;                                                                                      // 0.0
/*136 */     }                                                                                               // 0.0
/*140 */     /* Do not need those anymore. */                                                                // 0.0
/*142 */     av_freep(&sc->chunk_offsets);                                                                   // 0.0
/*144 */     av_freep(&sc->sample_to_chunk);                                                                 // 0.0
/*146 */     av_freep(&sc->sample_sizes);                                                                    // 0.0
/*148 */     av_freep(&sc->keyframes);                                                                       // 0.0
/*150 */     av_freep(&sc->stts_data);                                                                       // 0.0
/*154 */     return 0;                                                                                       // 0.0
/*156 */ }                                                                                                   // 0.0
