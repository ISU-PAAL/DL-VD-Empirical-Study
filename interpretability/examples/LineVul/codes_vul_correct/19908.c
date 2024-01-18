// commit message FFmpeg@984add64a4 (target=1, prob=0.99921584, correct=True): wma: check byte_offset_bits
/*0   */ int ff_wma_init(AVCodecContext *avctx, int flags2)                                          // (1) 0.07109
/*2   */ {                                                                                           // (22) 0.01201
/*4   */     WMACodecContext *s = avctx->priv_data;                                                  // (6) 0.04836
/*6   */     int i;                                                                                  // (23) 0.009612
/*8   */     float bps1, high_freq;                                                                  // (10) 0.03837
/*10  */     volatile float bps;                                                                     // (17) 0.02016
/*12  */     int sample_rate1;                                                                       // (21) 0.01384
/*14  */     int coef_vlc_table;                                                                     // (11) 0.03415
/*18  */     if (   avctx->sample_rate <= 0 || avctx->sample_rate > 50000                            // (7) 0.04753
/*20  */         || avctx->channels    <= 0 || avctx->channels    > 2                                // (2) 0.05606
/*22  */         || avctx->bit_rate    <= 0)                                                         // (15) 0.02807
/*24  */         return -1;                                                                          // (20) 0.0155
/*28  */     ff_fmt_convert_init(&s->fmt_conv, avctx);                                               // (8) 0.04259
/*30  */     avpriv_float_dsp_init(&s->fdsp, avctx->flags & CODEC_FLAG_BITEXACT);                    // (4) 0.05293
/*34  */     if (avctx->codec->id == AV_CODEC_ID_WMAV1) {                                            // (3) 0.05413
/*36  */         s->version = 1;                                                                     // (18) 0.01828
/*38  */     } else {                                                                                // (24) 0.008757
/*40  */         s->version = 2;                                                                     // (16) 0.02345
/*45  */     /* compute MDCT block size */                                                           // (19) 0.01659
/*47  */     s->frame_len_bits = ff_wma_get_frame_len_bits(avctx->sample_rate,                       // (5) 0.0484
/*49  */                                                   s->version, 0);                           // (0) 0.07466
/*51  */     s->next_block_len_bits = s->frame_len_bits;                                             // (13) 0.03157
/*53  */     s->prev_block_len_bits = s->frame_len_bits;                                             // (14) 0.02884
/*55  */     s->block_len_bits      = s->frame_len_bits;                                             // (12) 0.03289
/*59  */     s->frame_len = 1 << s->frame_len_bits;                                                  // (9) 0.0423
/*61  */     if (s->use_variable_block_len) {                                                        // 0.0
/*63  */         int nb_max, nb;                                                                     // 0.0
/*65  */         nb = ((flags2 >> 3) & 3) + 1;                                                       // 0.0
/*67  */         if ((avctx->bit_rate / avctx->channels) >= 32000)                                   // 0.0
/*69  */             nb += 2;                                                                        // 0.0
/*71  */         nb_max = s->frame_len_bits - BLOCK_MIN_BITS;                                        // 0.0
/*73  */         if (nb > nb_max)                                                                    // 0.0
/*75  */             nb = nb_max;                                                                    // 0.0
/*77  */         s->nb_block_sizes = nb + 1;                                                         // 0.0
/*79  */     } else {                                                                                // 0.0
/*81  */         s->nb_block_sizes = 1;                                                              // 0.0
/*86  */     /* init rate dependent parameters */                                                    // 0.0
/*88  */     s->use_noise_coding = 1;                                                                // 0.0
/*90  */     high_freq = avctx->sample_rate * 0.5;                                                   // 0.0
/*94  */     /* if version 2, then the rates are normalized */                                       // 0.0
/*96  */     sample_rate1 = avctx->sample_rate;                                                      // 0.0
/*98  */     if (s->version == 2) {                                                                  // 0.0
/*100 */         if (sample_rate1 >= 44100) {                                                        // 0.0
/*102 */             sample_rate1 = 44100;                                                           // 0.0
/*104 */         } else if (sample_rate1 >= 22050) {                                                 // 0.0
/*106 */             sample_rate1 = 22050;                                                           // 0.0
/*108 */         } else if (sample_rate1 >= 16000) {                                                 // 0.0
/*110 */             sample_rate1 = 16000;                                                           // 0.0
/*112 */         } else if (sample_rate1 >= 11025) {                                                 // 0.0
/*114 */             sample_rate1 = 11025;                                                           // 0.0
/*116 */         } else if (sample_rate1 >= 8000) {                                                  // 0.0
/*118 */             sample_rate1 = 8000;                                                            // 0.0
/*124 */     bps = (float)avctx->bit_rate / (float)(avctx->channels * avctx->sample_rate);           // 0.0
/*126 */     s->byte_offset_bits = av_log2((int)(bps * s->frame_len / 8.0 + 0.5)) + 2;               // 0.0
/*134 */     /* compute high frequency value and choose if noise coding should                       // 0.0
/*136 */        be activated */                                                                      // 0.0
/*138 */     bps1 = bps;                                                                             // 0.0
/*140 */     if (avctx->channels == 2)                                                               // 0.0
/*142 */         bps1 = bps * 1.6;                                                                   // 0.0
/*144 */     if (sample_rate1 == 44100) {                                                            // 0.0
/*146 */         if (bps1 >= 0.61) {                                                                 // 0.0
/*148 */             s->use_noise_coding = 0;                                                        // 0.0
/*150 */         } else {                                                                            // 0.0
/*152 */             high_freq = high_freq * 0.4;                                                    // 0.0
/*155 */     } else if (sample_rate1 == 22050) {                                                     // 0.0
/*157 */         if (bps1 >= 1.16) {                                                                 // 0.0
/*159 */             s->use_noise_coding = 0;                                                        // 0.0
/*161 */         } else if (bps1 >= 0.72) {                                                          // 0.0
/*163 */             high_freq = high_freq * 0.7;                                                    // 0.0
/*165 */         } else {                                                                            // 0.0
/*167 */             high_freq = high_freq * 0.6;                                                    // 0.0
/*170 */     } else if (sample_rate1 == 16000) {                                                     // 0.0
/*172 */         if (bps > 0.5) {                                                                    // 0.0
/*174 */             high_freq = high_freq * 0.5;                                                    // 0.0
/*176 */         } else {                                                                            // 0.0
/*178 */             high_freq = high_freq * 0.3;                                                    // 0.0
/*181 */     } else if (sample_rate1 == 11025) {                                                     // 0.0
/*183 */         high_freq = high_freq * 0.7;                                                        // 0.0
/*185 */     } else if (sample_rate1 == 8000) {                                                      // 0.0
/*187 */         if (bps <= 0.625) {                                                                 // 0.0
/*189 */             high_freq = high_freq * 0.5;                                                    // 0.0
/*191 */         } else if (bps > 0.75) {                                                            // 0.0
/*193 */             s->use_noise_coding = 0;                                                        // 0.0
/*195 */         } else {                                                                            // 0.0
/*197 */             high_freq = high_freq * 0.65;                                                   // 0.0
/*200 */     } else {                                                                                // 0.0
/*202 */         if (bps >= 0.8) {                                                                   // 0.0
/*204 */             high_freq = high_freq * 0.75;                                                   // 0.0
/*206 */         } else if (bps >= 0.6) {                                                            // 0.0
/*208 */             high_freq = high_freq * 0.6;                                                    // 0.0
/*210 */         } else {                                                                            // 0.0
/*212 */             high_freq = high_freq * 0.5;                                                    // 0.0
/*216 */     av_dlog(s->avctx, "flags2=0x%x\n", flags2);                                             // 0.0
/*218 */     av_dlog(s->avctx, "version=%d channels=%d sample_rate=%d bitrate=%d block_align=%d\n",  // 0.0
/*220 */             s->version, avctx->channels, avctx->sample_rate, avctx->bit_rate,               // 0.0
/*222 */             avctx->block_align);                                                            // 0.0
/*224 */     av_dlog(s->avctx, "bps=%f bps1=%f high_freq=%f bitoffset=%d\n",                         // 0.0
/*226 */             bps, bps1, high_freq, s->byte_offset_bits);                                     // 0.0
/*228 */     av_dlog(s->avctx, "use_noise_coding=%d use_exp_vlc=%d nb_block_sizes=%d\n",             // 0.0
/*230 */             s->use_noise_coding, s->use_exp_vlc, s->nb_block_sizes);                        // 0.0
/*234 */     /* compute the scale factor band sizes for each MDCT block size */                      // 0.0
/*236 */     {                                                                                       // 0.0
/*238 */         int a, b, pos, lpos, k, block_len, i, j, n;                                         // 0.0
/*240 */         const uint8_t *table;                                                               // 0.0
/*244 */         if (s->version == 1) {                                                              // 0.0
/*246 */             s->coefs_start = 3;                                                             // 0.0
/*248 */         } else {                                                                            // 0.0
/*250 */             s->coefs_start = 0;                                                             // 0.0
/*253 */         for (k = 0; k < s->nb_block_sizes; k++) {                                           // 0.0
/*255 */             block_len = s->frame_len >> k;                                                  // 0.0
/*259 */             if (s->version == 1) {                                                          // 0.0
/*261 */                 lpos = 0;                                                                   // 0.0
/*263 */                 for (i = 0; i < 25; i++) {                                                  // 0.0
/*265 */                     a = ff_wma_critical_freqs[i];                                           // 0.0
/*267 */                     b = avctx->sample_rate;                                                 // 0.0
/*269 */                     pos = ((block_len * 2 * a) + (b >> 1)) / b;                             // 0.0
/*271 */                     if (pos > block_len)                                                    // 0.0
/*273 */                         pos = block_len;                                                    // 0.0
/*275 */                     s->exponent_bands[0][i] = pos - lpos;                                   // 0.0
/*277 */                     if (pos >= block_len) {                                                 // 0.0
/*279 */                         i++;                                                                // 0.0
/*281 */                         break;                                                              // 0.0
/*284 */                     lpos = pos;                                                             // 0.0
/*287 */                 s->exponent_sizes[0] = i;                                                   // 0.0
/*289 */             } else {                                                                        // 0.0
/*291 */                 /* hardcoded tables */                                                      // 0.0
/*293 */                 table = NULL;                                                               // 0.0
/*295 */                 a = s->frame_len_bits - BLOCK_MIN_BITS - k;                                 // 0.0
/*297 */                 if (a < 3) {                                                                // 0.0
/*299 */                     if (avctx->sample_rate >= 44100) {                                      // 0.0
/*301 */                         table = exponent_band_44100[a];                                     // 0.0
/*303 */                     } else if (avctx->sample_rate >= 32000) {                               // 0.0
/*305 */                         table = exponent_band_32000[a];                                     // 0.0
/*307 */                     } else if (avctx->sample_rate >= 22050) {                               // 0.0
/*309 */                         table = exponent_band_22050[a];                                     // 0.0
/*313 */                 if (table) {                                                                // 0.0
/*315 */                     n = *table++;                                                           // 0.0
/*317 */                     for (i = 0; i < n; i++)                                                 // 0.0
/*319 */                         s->exponent_bands[k][i] = table[i];                                 // 0.0
/*321 */                     s->exponent_sizes[k] = n;                                               // 0.0
/*323 */                 } else {                                                                    // 0.0
/*325 */                     j = 0;                                                                  // 0.0
/*327 */                     lpos = 0;                                                               // 0.0
/*329 */                     for (i = 0; i < 25; i++) {                                              // 0.0
/*331 */                         a = ff_wma_critical_freqs[i];                                       // 0.0
/*333 */                         b = avctx->sample_rate;                                             // 0.0
/*335 */                         pos = ((block_len * 2 * a) + (b << 1)) / (4 * b);                   // 0.0
/*337 */                         pos <<= 2;                                                          // 0.0
/*339 */                         if (pos > block_len)                                                // 0.0
/*341 */                             pos = block_len;                                                // 0.0
/*343 */                         if (pos > lpos)                                                     // 0.0
/*345 */                             s->exponent_bands[k][j++] = pos - lpos;                         // 0.0
/*347 */                         if (pos >= block_len)                                               // 0.0
/*349 */                             break;                                                          // 0.0
/*351 */                         lpos = pos;                                                         // 0.0
/*354 */                     s->exponent_sizes[k] = j;                                               // 0.0
/*360 */             /* max number of coefs */                                                       // 0.0
/*362 */             s->coefs_end[k] = (s->frame_len - ((s->frame_len * 9) / 100)) >> k;             // 0.0
/*364 */             /* high freq computation */                                                     // 0.0
/*366 */             s->high_band_start[k] = (int)((block_len * 2 * high_freq) /                     // 0.0
/*368 */                                           avctx->sample_rate + 0.5);                        // 0.0
/*370 */             n = s->exponent_sizes[k];                                                       // 0.0
/*372 */             j = 0;                                                                          // 0.0
/*374 */             pos = 0;                                                                        // 0.0
/*376 */             for (i = 0; i < n; i++) {                                                       // 0.0
/*378 */                 int start, end;                                                             // 0.0
/*380 */                 start = pos;                                                                // 0.0
/*382 */                 pos += s->exponent_bands[k][i];                                             // 0.0
/*384 */                 end = pos;                                                                  // 0.0
/*386 */                 if (start < s->high_band_start[k])                                          // 0.0
/*388 */                     start = s->high_band_start[k];                                          // 0.0
/*390 */                 if (end > s->coefs_end[k])                                                  // 0.0
/*392 */                     end = s->coefs_end[k];                                                  // 0.0
/*394 */                 if (end > start)                                                            // 0.0
/*396 */                     s->exponent_high_bands[k][j++] = end - start;                           // 0.0
/*399 */             s->exponent_high_sizes[k] = j;                                                  // 0.0
/*401 */ #if 0                                                                                       // 0.0
/*403 */             tprintf(s->avctx, "%5d: coefs_end=%d high_band_start=%d nb_high_bands=%d: ",    // 0.0
/*405 */                     s->frame_len >> k,                                                      // 0.0
/*407 */                     s->coefs_end[k],                                                        // 0.0
/*409 */                     s->high_band_start[k],                                                  // 0.0
/*411 */                     s->exponent_high_sizes[k]);                                             // 0.0
/*413 */             for (j = 0; j < s->exponent_high_sizes[k]; j++)                                 // 0.0
/*415 */                 tprintf(s->avctx, " %d", s->exponent_high_bands[k][j]);                     // 0.0
/*417 */             tprintf(s->avctx, "\n");                                                        // 0.0
/*419 */ #endif                                                                                      // 0.0
/*425 */ #ifdef TRACE                                                                                // 0.0
/*427 */     {                                                                                       // 0.0
/*429 */         int i, j;                                                                           // 0.0
/*431 */         for (i = 0; i < s->nb_block_sizes; i++) {                                           // 0.0
/*433 */             tprintf(s->avctx, "%5d: n=%2d:",                                                // 0.0
/*435 */                     s->frame_len >> i,                                                      // 0.0
/*437 */                     s->exponent_sizes[i]);                                                  // 0.0
/*439 */             for (j = 0; j < s->exponent_sizes[i]; j++)                                      // 0.0
/*441 */                 tprintf(s->avctx, " %d", s->exponent_bands[i][j]);                          // 0.0
/*443 */             tprintf(s->avctx, "\n");                                                        // 0.0
/*447 */ #endif                                                                                      // 0.0
/*451 */     /* init MDCT windows : simple sinus window */                                           // 0.0
/*453 */     for (i = 0; i < s->nb_block_sizes; i++) {                                               // 0.0
/*455 */         ff_init_ff_sine_windows(s->frame_len_bits - i);                                     // 0.0
/*457 */         s->windows[i] = ff_sine_windows[s->frame_len_bits - i];                             // 0.0
/*462 */     s->reset_block_lengths = 1;                                                             // 0.0
/*466 */     if (s->use_noise_coding) {                                                              // 0.0
/*470 */         /* init the noise generator */                                                      // 0.0
/*472 */         if (s->use_exp_vlc) {                                                               // 0.0
/*474 */             s->noise_mult = 0.02;                                                           // 0.0
/*476 */         } else {                                                                            // 0.0
/*478 */             s->noise_mult = 0.04;                                                           // 0.0
/*483 */ #ifdef TRACE                                                                                // 0.0
/*485 */         for (i = 0; i < NOISE_TAB_SIZE; i++)                                                // 0.0
/*487 */             s->noise_table[i] = 1.0 * s->noise_mult;                                        // 0.0
/*489 */ #else                                                                                       // 0.0
/*491 */         {                                                                                   // 0.0
/*493 */             unsigned int seed;                                                              // 0.0
/*495 */             float norm;                                                                     // 0.0
/*497 */             seed = 1;                                                                       // 0.0
/*499 */             norm = (1.0 / (float)(1LL << 31)) * sqrt(3) * s->noise_mult;                    // 0.0
/*501 */             for (i = 0; i < NOISE_TAB_SIZE; i++) {                                          // 0.0
/*503 */                 seed = seed * 314159 + 1;                                                   // 0.0
/*505 */                 s->noise_table[i] = (float)((int)seed) * norm;                              // 0.0
/*509 */ #endif                                                                                      // 0.0
/*514 */     /* choose the VLC tables for the coefficients */                                        // 0.0
/*516 */     coef_vlc_table = 2;                                                                     // 0.0
/*518 */     if (avctx->sample_rate >= 32000) {                                                      // 0.0
/*520 */         if (bps1 < 0.72) {                                                                  // 0.0
/*522 */             coef_vlc_table = 0;                                                             // 0.0
/*524 */         } else if (bps1 < 1.16) {                                                           // 0.0
/*526 */             coef_vlc_table = 1;                                                             // 0.0
/*530 */     s->coef_vlcs[0]= &coef_vlcs[coef_vlc_table * 2    ];                                    // 0.0
/*532 */     s->coef_vlcs[1]= &coef_vlcs[coef_vlc_table * 2 + 1];                                    // 0.0
/*534 */     init_coef_vlc(&s->coef_vlc[0], &s->run_table[0], &s->level_table[0], &s->int_table[0],  // 0.0
/*536 */                   s->coef_vlcs[0]);                                                         // 0.0
/*538 */     init_coef_vlc(&s->coef_vlc[1], &s->run_table[1], &s->level_table[1], &s->int_table[1],  // 0.0
/*540 */                   s->coef_vlcs[1]);                                                         // 0.0
/*544 */     return 0;                                                                               // 0.0
