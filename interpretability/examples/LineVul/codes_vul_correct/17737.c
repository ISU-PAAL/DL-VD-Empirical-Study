// commit message FFmpeg@0232f788b6 (target=1, prob=0.52848077, correct=True): swr: fix invalid sample format message.
/*0   */ int swr_init(struct SwrContext *s){                                                                                                                                     // (14) 0.026
/*2   */     s->in_buffer_index= 0;                                                                                                                                              // (15) 0.02533
/*4   */     s->in_buffer_count= 0;                                                                                                                                              // (16) 0.02532
/*6   */     s->resample_in_constraint= 0;                                                                                                                                       // (13) 0.03117
/*8   */     free_temp(&s->postin);                                                                                                                                              // (19) 0.02338
/*10  */     free_temp(&s->midbuf);                                                                                                                                              // (18) 0.02339
/*12  */     free_temp(&s->preout);                                                                                                                                              // (20) 0.02337
/*14  */     free_temp(&s->in_buffer);                                                                                                                                           // (17) 0.02532
/*16  */     swri_audio_convert_free(&s-> in_convert);                                                                                                                           // (10) 0.03895
/*18  */     swri_audio_convert_free(&s->out_convert);                                                                                                                           // (9) 0.03896
/*20  */     swri_audio_convert_free(&s->full_convert);                                                                                                                          // (8) 0.03899
/*24  */     s-> in.planar= av_sample_fmt_is_planar(s-> in_sample_fmt);                                                                                                          // (4) 0.06087
/*26  */     s->out.planar= av_sample_fmt_is_planar(s->out_sample_fmt);                                                                                                          // (5) 0.06037
/*28  */     s-> in_sample_fmt= av_get_alt_sample_fmt(s-> in_sample_fmt, 0);                                                                                                     // (3) 0.06621
/*30  */     s->out_sample_fmt= av_get_alt_sample_fmt(s->out_sample_fmt, 0);                                                                                                     // (2) 0.06623
/*34  */     if(s-> in_sample_fmt >= AV_SAMPLE_FMT_NB){                                                                                                                          // (7) 0.0468
/*36  */         av_log(s, AV_LOG_ERROR, "Requested sample format %s is invalid\n", av_get_sample_fmt_name(s->in_sample_fmt));                                                   // (1) 0.09932
/*38  */         return AVERROR(EINVAL);                                                                                                                                         // (12) 0.03117
/*40  */     }                                                                                                                                                                   // (22) 0.007804
/*42  */     if(s->out_sample_fmt >= AV_SAMPLE_FMT_NB){                                                                                                                          // (6) 0.04681
/*44  */         av_log(s, AV_LOG_ERROR, "Requested sample format %s is invalid\n", av_get_sample_fmt_name(s->out_sample_fmt));                                                  // (0) 0.09935
/*46  */         return AVERROR(EINVAL);                                                                                                                                         // (11) 0.03135
/*48  */     }                                                                                                                                                                   // (21) 0.008084
/*52  */     if(   s->int_sample_fmt != AV_SAMPLE_FMT_S16                                                                                                                        // 0.0
/*54  */         &&s->int_sample_fmt != AV_SAMPLE_FMT_FLT){                                                                                                                      // 0.0
/*56  */         av_log(s, AV_LOG_ERROR, "Requested sample format %s is not supported internally, only float & S16 is supported\n", av_get_sample_fmt_name(s->int_sample_fmt));  // 0.0
/*58  */         return AVERROR(EINVAL);                                                                                                                                         // 0.0
/*60  */     }                                                                                                                                                                   // 0.0
/*64  */     //FIXME should we allow/support using FLT on material that doesnt need it ?                                                                                         // 0.0
/*66  */     if(s->in_sample_fmt <= AV_SAMPLE_FMT_S16 || s->int_sample_fmt==AV_SAMPLE_FMT_S16){                                                                                  // 0.0
/*68  */         s->int_sample_fmt= AV_SAMPLE_FMT_S16;                                                                                                                           // 0.0
/*70  */     }else                                                                                                                                                               // 0.0
/*72  */         s->int_sample_fmt= AV_SAMPLE_FMT_FLT;                                                                                                                           // 0.0
/*78  */     if (s->out_sample_rate!=s->in_sample_rate || (s->flags & SWR_FLAG_RESAMPLE)){                                                                                       // 0.0
/*80  */         s->resample = swri_resample_init(s->resample, s->out_sample_rate, s->in_sample_rate, 16, 10, 0, 0.8);                                                           // 0.0
/*82  */     }else                                                                                                                                                               // 0.0
/*84  */         swri_resample_free(&s->resample);                                                                                                                               // 0.0
/*86  */     if(s->int_sample_fmt != AV_SAMPLE_FMT_S16 && s->resample){                                                                                                          // 0.0
/*88  */         av_log(s, AV_LOG_ERROR, "Resampling only supported with internal s16 currently\n"); //FIXME                                                                     // 0.0
/*90  */         return -1;                                                                                                                                                      // 0.0
/*92  */     }                                                                                                                                                                   // 0.0
/*96  */     if(!s->used_ch_count)                                                                                                                                               // 0.0
/*98  */         s->used_ch_count= s->in.ch_count;                                                                                                                               // 0.0
/*102 */     if(s->used_ch_count && s-> in_ch_layout && s->used_ch_count != av_get_channel_layout_nb_channels(s-> in_ch_layout)){                                                // 0.0
/*104 */         av_log(s, AV_LOG_WARNING, "Input channel layout has a different number of channels than the number of used channels, ignoring layout\n");                       // 0.0
/*106 */         s-> in_ch_layout= 0;                                                                                                                                            // 0.0
/*108 */     }                                                                                                                                                                   // 0.0
/*112 */     if(!s-> in_ch_layout)                                                                                                                                               // 0.0
/*114 */         s-> in_ch_layout= av_get_default_channel_layout(s->used_ch_count);                                                                                              // 0.0
/*116 */     if(!s->out_ch_layout)                                                                                                                                               // 0.0
/*118 */         s->out_ch_layout= av_get_default_channel_layout(s->out.ch_count);                                                                                               // 0.0
/*122 */     s->rematrix= s->out_ch_layout  !=s->in_ch_layout || s->rematrix_volume!=1.0;                                                                                        // 0.0
/*126 */ #define RSC 1 //FIXME finetune                                                                                                                                          // 0.0
/*128 */     if(!s-> in.ch_count)                                                                                                                                                // 0.0
/*130 */         s-> in.ch_count= av_get_channel_layout_nb_channels(s-> in_ch_layout);                                                                                           // 0.0
/*132 */     if(!s->used_ch_count)                                                                                                                                               // 0.0
/*134 */         s->used_ch_count= s->in.ch_count;                                                                                                                               // 0.0
/*136 */     if(!s->out.ch_count)                                                                                                                                                // 0.0
/*138 */         s->out.ch_count= av_get_channel_layout_nb_channels(s->out_ch_layout);                                                                                           // 0.0
/*142 */ av_assert0(s-> in.ch_count);                                                                                                                                            // 0.0
/*144 */ av_assert0(s->used_ch_count);                                                                                                                                           // 0.0
/*146 */ av_assert0(s->out.ch_count);                                                                                                                                            // 0.0
/*148 */     s->resample_first= RSC*s->out.ch_count/s->in.ch_count - RSC < s->out_sample_rate/(float)s-> in_sample_rate - 1.0;                                                   // 0.0
/*152 */     s-> in.bps= av_get_bytes_per_sample(s-> in_sample_fmt);                                                                                                             // 0.0
/*154 */     s->int_bps= av_get_bytes_per_sample(s->int_sample_fmt);                                                                                                             // 0.0
/*156 */     s->out.bps= av_get_bytes_per_sample(s->out_sample_fmt);                                                                                                             // 0.0
/*160 */     if(!s->resample && !s->rematrix && !s->channel_map){                                                                                                                // 0.0
/*162 */         s->full_convert = swri_audio_convert_alloc(s->out_sample_fmt,                                                                                                   // 0.0
/*164 */                                                    s-> in_sample_fmt, s-> in.ch_count, NULL, 0);                                                                        // 0.0
/*166 */         return 0;                                                                                                                                                       // 0.0
/*168 */     }                                                                                                                                                                   // 0.0
/*172 */     s->in_convert = swri_audio_convert_alloc(s->int_sample_fmt,                                                                                                         // 0.0
/*174 */                                              s-> in_sample_fmt, s->used_ch_count, s->channel_map, 0);                                                                   // 0.0
/*176 */     s->out_convert= swri_audio_convert_alloc(s->out_sample_fmt,                                                                                                         // 0.0
/*178 */                                              s->int_sample_fmt, s->out.ch_count, NULL, 0);                                                                              // 0.0
/*184 */     s->postin= s->in;                                                                                                                                                   // 0.0
/*186 */     s->preout= s->out;                                                                                                                                                  // 0.0
/*188 */     s->midbuf= s->in;                                                                                                                                                   // 0.0
/*190 */     s->in_buffer= s->in;                                                                                                                                                // 0.0
/*192 */     if(s->channel_map){                                                                                                                                                 // 0.0
/*194 */         s->postin.ch_count=                                                                                                                                             // 0.0
/*196 */         s->midbuf.ch_count=                                                                                                                                             // 0.0
/*198 */         s->in_buffer.ch_count= s->used_ch_count;                                                                                                                        // 0.0
/*200 */     }                                                                                                                                                                   // 0.0
/*202 */     if(!s->resample_first){                                                                                                                                             // 0.0
/*204 */         s->midbuf.ch_count= s->out.ch_count;                                                                                                                            // 0.0
/*206 */         s->in_buffer.ch_count = s->out.ch_count;                                                                                                                        // 0.0
/*208 */     }                                                                                                                                                                   // 0.0
/*212 */     s->in_buffer.bps = s->postin.bps = s->midbuf.bps = s->preout.bps =  s->int_bps;                                                                                     // 0.0
/*214 */     s->in_buffer.planar = s->postin.planar = s->midbuf.planar = s->preout.planar =  1;                                                                                  // 0.0
/*220 */     if(s->rematrix)                                                                                                                                                     // 0.0
/*222 */         return swri_rematrix_init(s);                                                                                                                                   // 0.0
/*226 */     return 0;                                                                                                                                                           // 0.0
/*228 */ }                                                                                                                                                                       // 0.0
