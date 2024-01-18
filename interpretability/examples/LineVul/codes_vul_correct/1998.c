// commit message FFmpeg@2f76157eb0 (target=1, prob=0.5231111, correct=True): swresample/rematrix: Use clipping s16 rematrixing if overflows are possible
/*0   */ av_cold int swri_rematrix_init(SwrContext *s){                                    // (12) 0.03711
/*2   */     int i, j;                                                                     // (20) 0.01563
/*4   */     int nb_in  = av_get_channel_layout_nb_channels(s->in_ch_layout);              // (4) 0.06055
/*6   */     int nb_out = av_get_channel_layout_nb_channels(s->out_ch_layout);             // (5) 0.05859
/*10  */     s->mix_any_f = NULL;                                                          // (17) 0.02539
/*14  */     if (!s->rematrix_custom) {                                                    // (15) 0.02734
/*16  */         int r = auto_matrix(s);                                                   // (13) 0.0332
/*18  */         if (r)                                                                    // (19) 0.02148
/*20  */             return r;                                                             // (16) 0.02734
/*22  */     }                                                                             // (21) 0.007812
/*24  */     if (s->midbuf.fmt == AV_SAMPLE_FMT_S16P){                                     // (8) 0.04883
/*26  */         s->native_matrix = av_calloc(nb_in * nb_out, sizeof(int));                // (3) 0.0625
/*28  */         s->native_one    = av_mallocz(sizeof(int));                               // (7) 0.05273
/*30  */         if (!s->native_matrix || !s->native_one)                                  // (9) 0.04492
/*32  */             return AVERROR(ENOMEM);                                               // (11) 0.03906
/*34  */         for (i = 0; i < nb_out; i++) {                                            // (10) 0.04492
/*36  */             double rem = 0;                                                       // (14) 0.03125
/*40  */             for (j = 0; j < nb_in; j++) {                                         // (6) 0.05273
/*42  */                 double target = s->matrix[i][j] * 32768 + rem;                    // (2) 0.06445
/*44  */                 ((int*)s->native_matrix)[i * nb_in + j] = lrintf(target);         // (0) 0.08008
/*46  */                 rem += target - ((int*)s->native_matrix)[i * nb_in + j];          // (1) 0.07422
/*48  */             }                                                                     // (18) 0.02344
/*50  */         }                                                                         // 0.0
/*52  */         *((int*)s->native_one) = 32768;                                           // 0.0
/*54  */         s->mix_1_1_f = (mix_1_1_func_type*)copy_s16;                              // 0.0
/*56  */         s->mix_2_1_f = (mix_2_1_func_type*)sum2_s16;                              // 0.0
/*58  */         s->mix_any_f = (mix_any_func_type*)get_mix_any_func_s16(s);               // 0.0
/*60  */     }else if(s->midbuf.fmt == AV_SAMPLE_FMT_FLTP){                                // 0.0
/*62  */         s->native_matrix = av_calloc(nb_in * nb_out, sizeof(float));              // 0.0
/*64  */         s->native_one    = av_mallocz(sizeof(float));                             // 0.0
/*66  */         if (!s->native_matrix || !s->native_one)                                  // 0.0
/*68  */             return AVERROR(ENOMEM);                                               // 0.0
/*70  */         for (i = 0; i < nb_out; i++)                                              // 0.0
/*72  */             for (j = 0; j < nb_in; j++)                                           // 0.0
/*74  */                 ((float*)s->native_matrix)[i * nb_in + j] = s->matrix[i][j];      // 0.0
/*76  */         *((float*)s->native_one) = 1.0;                                           // 0.0
/*78  */         s->mix_1_1_f = (mix_1_1_func_type*)copy_float;                            // 0.0
/*80  */         s->mix_2_1_f = (mix_2_1_func_type*)sum2_float;                            // 0.0
/*82  */         s->mix_any_f = (mix_any_func_type*)get_mix_any_func_float(s);             // 0.0
/*84  */     }else if(s->midbuf.fmt == AV_SAMPLE_FMT_DBLP){                                // 0.0
/*86  */         s->native_matrix = av_calloc(nb_in * nb_out, sizeof(double));             // 0.0
/*88  */         s->native_one    = av_mallocz(sizeof(double));                            // 0.0
/*90  */         if (!s->native_matrix || !s->native_one)                                  // 0.0
/*92  */             return AVERROR(ENOMEM);                                               // 0.0
/*94  */         for (i = 0; i < nb_out; i++)                                              // 0.0
/*96  */             for (j = 0; j < nb_in; j++)                                           // 0.0
/*98  */                 ((double*)s->native_matrix)[i * nb_in + j] = s->matrix[i][j];     // 0.0
/*100 */         *((double*)s->native_one) = 1.0;                                          // 0.0
/*102 */         s->mix_1_1_f = (mix_1_1_func_type*)copy_double;                           // 0.0
/*104 */         s->mix_2_1_f = (mix_2_1_func_type*)sum2_double;                           // 0.0
/*106 */         s->mix_any_f = (mix_any_func_type*)get_mix_any_func_double(s);            // 0.0
/*108 */     }else if(s->midbuf.fmt == AV_SAMPLE_FMT_S32P){                                // 0.0
/*110 */         // Only for dithering currently                                           // 0.0
/*112 */ //         s->native_matrix = av_calloc(nb_in * nb_out, sizeof(double));          // 0.0
/*114 */         s->native_one    = av_mallocz(sizeof(int));                               // 0.0
/*116 */         if (!s->native_one)                                                       // 0.0
/*118 */             return AVERROR(ENOMEM);                                               // 0.0
/*120 */ //         for (i = 0; i < nb_out; i++)                                           // 0.0
/*122 */ //             for (j = 0; j < nb_in; j++)                                        // 0.0
/*124 */ //                 ((double*)s->native_matrix)[i * nb_in + j] = s->matrix[i][j];  // 0.0
/*126 */         *((int*)s->native_one) = 32768;                                           // 0.0
/*128 */         s->mix_1_1_f = (mix_1_1_func_type*)copy_s32;                              // 0.0
/*130 */         s->mix_2_1_f = (mix_2_1_func_type*)sum2_s32;                              // 0.0
/*132 */         s->mix_any_f = (mix_any_func_type*)get_mix_any_func_s32(s);               // 0.0
/*134 */     }else                                                                         // 0.0
/*136 */         av_assert0(0);                                                            // 0.0
/*138 */     //FIXME quantize for integeres                                                // 0.0
/*140 */     for (i = 0; i < SWR_CH_MAX; i++) {                                            // 0.0
/*142 */         int ch_in=0;                                                              // 0.0
/*144 */         for (j = 0; j < SWR_CH_MAX; j++) {                                        // 0.0
/*146 */             s->matrix32[i][j]= lrintf(s->matrix[i][j] * 32768);                   // 0.0
/*148 */             if(s->matrix[i][j])                                                   // 0.0
/*150 */                 s->matrix_ch[i][++ch_in]= j;                                      // 0.0
/*152 */         }                                                                         // 0.0
/*154 */         s->matrix_ch[i][0]= ch_in;                                                // 0.0
/*156 */     }                                                                             // 0.0
/*160 */     if(HAVE_YASM && HAVE_MMX)                                                     // 0.0
/*162 */         return swri_rematrix_init_x86(s);                                         // 0.0
/*166 */     return 0;                                                                     // 0.0
/*168 */ }                                                                                 // 0.0
