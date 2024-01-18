// commit message FFmpeg@71a1f76d3c (target=0, prob=0.45646542, correct=True): swr: update double precision checks for our resampler
/*0   */ int swr_init(struct SwrContext *s){                                                                                                                                            // (3) 0.02739
/*2   */     s->in_buffer_index= 0;                                                                                                                                                     // (19) 0.002745
/*4   */     s->in_buffer_count= 0;                                                                                                                                                     // (21) 0.002577
/*6   */     s->resample_in_constraint= 0;                                                                                                                                              // (17) 0.002983
/*8   */     free_temp(&s->postin);                                                                                                                                                     // (20) 0.002624
/*10  */     free_temp(&s->midbuf);                                                                                                                                                     // (13) 0.003896
/*12  */     free_temp(&s->preout);                                                                                                                                                     // (23) 0.002051
/*14  */     free_temp(&s->in_buffer);                                                                                                                                                  // (22) 0.002254
/*16  */     free_temp(&s->dither);                                                                                                                                                     // (7) 0.009476
/*18  */     swri_audio_convert_free(&s-> in_convert);                                                                                                                                  // (16) 0.003012
/*20  */     swri_audio_convert_free(&s->out_convert);                                                                                                                                  // (11) 0.004403
/*22  */     swri_audio_convert_free(&s->full_convert);                                                                                                                                 // (14) 0.003441
/*24  */     swri_rematrix_free(s);                                                                                                                                                     // (18) 0.002806
/*28  */     s->flushed = 0;                                                                                                                                                            // (15) 0.003355
/*32  */     if(s-> in_sample_fmt >= AV_SAMPLE_FMT_NB){                                                                                                                                 // (10) 0.006179
/*34  */         av_log(s, AV_LOG_ERROR, "Requested input sample format %d is invalid\n", s->in_sample_fmt);                                                                            // (6) 0.01098
/*36  */         return AVERROR(EINVAL);                                                                                                                                                // (12) 0.004245
/*38  */     }                                                                                                                                                                          // (24) 0.001673
/*40  */     if(s->out_sample_fmt >= AV_SAMPLE_FMT_NB){                                                                                                                                 // (8) 0.009012
/*42  */         av_log(s, AV_LOG_ERROR, "Requested output sample format %d is invalid\n", s->out_sample_fmt);                                                                          // (5) 0.01292
/*44  */         return AVERROR(EINVAL);                                                                                                                                                // (4) 0.01521
/*46  */     }                                                                                                                                                                          // (1) 0.04718
/*50  */     //FIXME should we allow/support using FLT on material that doesnt need it ?                                                                                                // (0) 0.71
/*52  */     if(av_get_planar_sample_fmt(s->in_sample_fmt) <= AV_SAMPLE_FMT_S16P || s->int_sample_fmt==AV_SAMPLE_FMT_S16P){                                                             // (2) 0.03718
/*54  */         s->int_sample_fmt= AV_SAMPLE_FMT_S16P;                                                                                                                                 // (9) 0.008288
/*56  */     }else                                                                                                                                                                      // 0.0
/*58  */         s->int_sample_fmt= AV_SAMPLE_FMT_FLTP;                                                                                                                                 // 0.0
/*62  */     if(   s->int_sample_fmt != AV_SAMPLE_FMT_S16P                                                                                                                              // 0.0
/*64  */         &&s->int_sample_fmt != AV_SAMPLE_FMT_S32P                                                                                                                              // 0.0
/*66  */         &&s->int_sample_fmt != AV_SAMPLE_FMT_FLTP){                                                                                                                            // 0.0
/*68  */         av_log(s, AV_LOG_ERROR, "Requested sample format %s is not supported internally, S16/S32/FLT is supported\n", av_get_sample_fmt_name(s->int_sample_fmt));              // 0.0
/*70  */         return AVERROR(EINVAL);                                                                                                                                                // 0.0
/*72  */     }                                                                                                                                                                          // 0.0
/*76  */     set_audiodata_fmt(&s-> in, s-> in_sample_fmt);                                                                                                                             // 0.0
/*78  */     set_audiodata_fmt(&s->out, s->out_sample_fmt);                                                                                                                             // 0.0
/*82  */     if (s->out_sample_rate!=s->in_sample_rate || (s->flags & SWR_FLAG_RESAMPLE)){                                                                                              // 0.0
/*84  */         s->resample = swri_resample_init(s->resample, s->out_sample_rate, s->in_sample_rate, s->filter_size, s->phase_shift, s->linear_interp, s->cutoff, s->int_sample_fmt);  // 0.0
/*86  */     }else                                                                                                                                                                      // 0.0
/*88  */         swri_resample_free(&s->resample);                                                                                                                                      // 0.0
/*90  */     if(    s->int_sample_fmt != AV_SAMPLE_FMT_S16P                                                                                                                             // 0.0
/*92  */         && s->int_sample_fmt != AV_SAMPLE_FMT_S32P                                                                                                                             // 0.0
/*94  */         && s->int_sample_fmt != AV_SAMPLE_FMT_FLTP                                                                                                                             // 0.0
/*96  */         && s->resample){                                                                                                                                                       // 0.0
/*98  */         av_log(s, AV_LOG_ERROR, "Resampling only supported with internal s16/s32/flt\n");                                                                                      // 0.0
/*100 */         return -1;                                                                                                                                                             // 0.0
/*102 */     }                                                                                                                                                                          // 0.0
/*106 */     if(!s->used_ch_count)                                                                                                                                                      // 0.0
/*108 */         s->used_ch_count= s->in.ch_count;                                                                                                                                      // 0.0
/*112 */     if(s->used_ch_count && s-> in_ch_layout && s->used_ch_count != av_get_channel_layout_nb_channels(s-> in_ch_layout)){                                                       // 0.0
/*114 */         av_log(s, AV_LOG_WARNING, "Input channel layout has a different number of channels than the number of used channels, ignoring layout\n");                              // 0.0
/*116 */         s-> in_ch_layout= 0;                                                                                                                                                   // 0.0
/*118 */     }                                                                                                                                                                          // 0.0
/*122 */     if(!s-> in_ch_layout)                                                                                                                                                      // 0.0
/*124 */         s-> in_ch_layout= av_get_default_channel_layout(s->used_ch_count);                                                                                                     // 0.0
/*126 */     if(!s->out_ch_layout)                                                                                                                                                      // 0.0
/*128 */         s->out_ch_layout= av_get_default_channel_layout(s->out.ch_count);                                                                                                      // 0.0
/*132 */     s->rematrix= s->out_ch_layout  !=s->in_ch_layout || s->rematrix_volume!=1.0 ||                                                                                             // 0.0
/*134 */                  s->rematrix_custom;                                                                                                                                           // 0.0
/*138 */ #define RSC 1 //FIXME finetune                                                                                                                                                 // 0.0
/*140 */     if(!s-> in.ch_count)                                                                                                                                                       // 0.0
/*142 */         s-> in.ch_count= av_get_channel_layout_nb_channels(s-> in_ch_layout);                                                                                                  // 0.0
/*144 */     if(!s->used_ch_count)                                                                                                                                                      // 0.0
/*146 */         s->used_ch_count= s->in.ch_count;                                                                                                                                      // 0.0
/*148 */     if(!s->out.ch_count)                                                                                                                                                       // 0.0
/*150 */         s->out.ch_count= av_get_channel_layout_nb_channels(s->out_ch_layout);                                                                                                  // 0.0
/*154 */     if(!s-> in.ch_count){                                                                                                                                                      // 0.0
/*156 */         av_assert0(!s->in_ch_layout);                                                                                                                                          // 0.0
/*158 */         av_log(s, AV_LOG_ERROR, "Input channel count and layout are unset\n");                                                                                                 // 0.0
/*160 */         return -1;                                                                                                                                                             // 0.0
/*162 */     }                                                                                                                                                                          // 0.0
/*166 */     if ((!s->out_ch_layout || !s->in_ch_layout) && s->used_ch_count != s->out.ch_count && !s->rematrix_custom) {                                                               // 0.0
/*168 */         av_log(s, AV_LOG_ERROR, "Rematrix is needed but there is not enough information to do it\n");                                                                          // 0.0
/*170 */         return -1;                                                                                                                                                             // 0.0
/*172 */     }                                                                                                                                                                          // 0.0
/*176 */ av_assert0(s->used_ch_count);                                                                                                                                                  // 0.0
/*178 */ av_assert0(s->out.ch_count);                                                                                                                                                   // 0.0
/*180 */     s->resample_first= RSC*s->out.ch_count/s->in.ch_count - RSC < s->out_sample_rate/(float)s-> in_sample_rate - 1.0;                                                          // 0.0
/*184 */     s->in_buffer= s->in;                                                                                                                                                       // 0.0
/*188 */     if(!s->resample && !s->rematrix && !s->channel_map && !s->dither_method){                                                                                                  // 0.0
/*190 */         s->full_convert = swri_audio_convert_alloc(s->out_sample_fmt,                                                                                                          // 0.0
/*192 */                                                    s-> in_sample_fmt, s-> in.ch_count, NULL, 0);                                                                               // 0.0
/*194 */         return 0;                                                                                                                                                              // 0.0
/*196 */     }                                                                                                                                                                          // 0.0
/*200 */     s->in_convert = swri_audio_convert_alloc(s->int_sample_fmt,                                                                                                                // 0.0
/*202 */                                              s-> in_sample_fmt, s->used_ch_count, s->channel_map, 0);                                                                          // 0.0
/*204 */     s->out_convert= swri_audio_convert_alloc(s->out_sample_fmt,                                                                                                                // 0.0
/*206 */                                              s->int_sample_fmt, s->out.ch_count, NULL, 0);                                                                                     // 0.0
/*212 */     s->postin= s->in;                                                                                                                                                          // 0.0
/*214 */     s->preout= s->out;                                                                                                                                                         // 0.0
/*216 */     s->midbuf= s->in;                                                                                                                                                          // 0.0
/*220 */     if(s->channel_map){                                                                                                                                                        // 0.0
/*222 */         s->postin.ch_count=                                                                                                                                                    // 0.0
/*224 */         s->midbuf.ch_count= s->used_ch_count;                                                                                                                                  // 0.0
/*226 */         if(s->resample)                                                                                                                                                        // 0.0
/*228 */             s->in_buffer.ch_count= s->used_ch_count;                                                                                                                           // 0.0
/*230 */     }                                                                                                                                                                          // 0.0
/*232 */     if(!s->resample_first){                                                                                                                                                    // 0.0
/*234 */         s->midbuf.ch_count= s->out.ch_count;                                                                                                                                   // 0.0
/*236 */         if(s->resample)                                                                                                                                                        // 0.0
/*238 */             s->in_buffer.ch_count = s->out.ch_count;                                                                                                                           // 0.0
/*240 */     }                                                                                                                                                                          // 0.0
/*244 */     set_audiodata_fmt(&s->postin, s->int_sample_fmt);                                                                                                                          // 0.0
/*246 */     set_audiodata_fmt(&s->midbuf, s->int_sample_fmt);                                                                                                                          // 0.0
/*248 */     set_audiodata_fmt(&s->preout, s->int_sample_fmt);                                                                                                                          // 0.0
/*252 */     if(s->resample){                                                                                                                                                           // 0.0
/*254 */         set_audiodata_fmt(&s->in_buffer, s->int_sample_fmt);                                                                                                                   // 0.0
/*256 */     }                                                                                                                                                                          // 0.0
/*260 */     s->dither = s->preout;                                                                                                                                                     // 0.0
/*264 */     if(s->rematrix || s->dither_method)                                                                                                                                        // 0.0
/*266 */         return swri_rematrix_init(s);                                                                                                                                          // 0.0
/*270 */     return 0;                                                                                                                                                                  // 0.0
/*272 */ }                                                                                                                                                                              // 0.0
