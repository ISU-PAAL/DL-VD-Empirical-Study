// commit message FFmpeg@6f1ec38ce2 (target=0, prob=0.5879867, correct=False): mpegaudio: clean up compute_antialias() definition
/*0   */ static av_cold int decode_init(AVCodecContext * avctx)                                   // (9) 0.03396
/*2   */ {                                                                                        // (24) 0.002014
/*4   */     MPADecodeContext *s = avctx->priv_data;                                              // (6) 0.03519
/*6   */     static int init=0;                                                                   // (22) 0.01756
/*8   */     int i, j, k;                                                                         // (20) 0.01955
/*12  */     s->avctx = avctx;                                                                    // (19) 0.02145
/*16  */     ff_mpadsp_init(&s->mpadsp);                                                          // (10) 0.03324
/*20  */     avctx->sample_fmt= OUT_FMT;                                                          // (15) 0.03123
/*22  */     s->error_recognition= avctx->error_recognition;                                      // (7) 0.03511
/*26  */     if (!init && !avctx->parse_only) {                                                   // (14) 0.03124
/*28  */         int offset;                                                                      // (21) 0.01954
/*32  */         /* scale factors table for layer 1/2 */                                          // (11) 0.0332
/*34  */         for(i=0;i<64;i++) {                                                              // (4) 0.03898
/*36  */             int shift, mod;                                                              // (16) 0.03119
/*38  */             /* 1.0 (i = 3) is normalized to 2 ^ FRAC_BITS */                             // (2) 0.06042
/*40  */             shift = (i / 3);                                                             // (8) 0.03508
/*42  */             mod = i % 3;                                                                 // (12) 0.03313
/*44  */             scale_factor_modshift[i] = mod | (shift << 2);                               // (3) 0.05458
/*46  */         }                                                                                // (23) 0.01559
/*50  */         /* scale factor multiply for layer 1 */                                          // (18) 0.0293
/*52  */         for(i=0;i<15;i++) {                                                              // (5) 0.03898
/*54  */             int n, norm;                                                                 // (17) 0.03118
/*56  */             n = i + 2;                                                                   // (13) 0.03313
/*58  */             norm = ((INT64_C(1) << n) * FRAC_ONE) / ((1 << n) - 1);                      // (1) 0.07602
/*60  */             scale_factor_mult[i][0] = MULLx(norm, FIXR(1.0          * 2.0), FRAC_BITS);  // (0) 0.1053
/*62  */             scale_factor_mult[i][1] = MULLx(norm, FIXR(0.7937005259 * 2.0), FRAC_BITS);  // 0.0
/*64  */             scale_factor_mult[i][2] = MULLx(norm, FIXR(0.6299605249 * 2.0), FRAC_BITS);  // 0.0
/*66  */             av_dlog(avctx, "%d: norm=%x s=%x %x %x\n",                                   // 0.0
/*68  */                     i, norm,                                                             // 0.0
/*70  */                     scale_factor_mult[i][0],                                             // 0.0
/*72  */                     scale_factor_mult[i][1],                                             // 0.0
/*74  */                     scale_factor_mult[i][2]);                                            // 0.0
/*76  */         }                                                                                // 0.0
/*80  */         RENAME(ff_mpa_synth_init)(RENAME(ff_mpa_synth_window));                          // 0.0
/*84  */         /* huffman decode tables */                                                      // 0.0
/*86  */         offset = 0;                                                                      // 0.0
/*88  */         for(i=1;i<16;i++) {                                                              // 0.0
/*90  */             const HuffTable *h = &mpa_huff_tables[i];                                    // 0.0
/*92  */             int xsize, x, y;                                                             // 0.0
/*94  */             uint8_t  tmp_bits [512];                                                     // 0.0
/*96  */             uint16_t tmp_codes[512];                                                     // 0.0
/*100 */             memset(tmp_bits , 0, sizeof(tmp_bits ));                                     // 0.0
/*102 */             memset(tmp_codes, 0, sizeof(tmp_codes));                                     // 0.0
/*106 */             xsize = h->xsize;                                                            // 0.0
/*110 */             j = 0;                                                                       // 0.0
/*112 */             for(x=0;x<xsize;x++) {                                                       // 0.0
/*114 */                 for(y=0;y<xsize;y++){                                                    // 0.0
/*116 */                     tmp_bits [(x << 5) | y | ((x&&y)<<4)]= h->bits [j  ];                // 0.0
/*118 */                     tmp_codes[(x << 5) | y | ((x&&y)<<4)]= h->codes[j++];                // 0.0
/*120 */                 }                                                                        // 0.0
/*122 */             }                                                                            // 0.0
/*126 */             /* XXX: fail test */                                                         // 0.0
/*128 */             huff_vlc[i].table = huff_vlc_tables+offset;                                  // 0.0
/*130 */             huff_vlc[i].table_allocated = huff_vlc_tables_sizes[i];                      // 0.0
/*132 */             init_vlc(&huff_vlc[i], 7, 512,                                               // 0.0
/*134 */                      tmp_bits, 1, 1, tmp_codes, 2, 2,                                    // 0.0
/*136 */                      INIT_VLC_USE_NEW_STATIC);                                           // 0.0
/*138 */             offset += huff_vlc_tables_sizes[i];                                          // 0.0
/*140 */         }                                                                                // 0.0
/*142 */         assert(offset == FF_ARRAY_ELEMS(huff_vlc_tables));                               // 0.0
/*146 */         offset = 0;                                                                      // 0.0
/*148 */         for(i=0;i<2;i++) {                                                               // 0.0
/*150 */             huff_quad_vlc[i].table = huff_quad_vlc_tables+offset;                        // 0.0
/*152 */             huff_quad_vlc[i].table_allocated = huff_quad_vlc_tables_sizes[i];            // 0.0
/*154 */             init_vlc(&huff_quad_vlc[i], i == 0 ? 7 : 4, 16,                              // 0.0
/*156 */                      mpa_quad_bits[i], 1, 1, mpa_quad_codes[i], 1, 1,                    // 0.0
/*158 */                      INIT_VLC_USE_NEW_STATIC);                                           // 0.0
/*160 */             offset += huff_quad_vlc_tables_sizes[i];                                     // 0.0
/*162 */         }                                                                                // 0.0
/*164 */         assert(offset == FF_ARRAY_ELEMS(huff_quad_vlc_tables));                          // 0.0
/*168 */         for(i=0;i<9;i++) {                                                               // 0.0
/*170 */             k = 0;                                                                       // 0.0
/*172 */             for(j=0;j<22;j++) {                                                          // 0.0
/*174 */                 band_index_long[i][j] = k;                                               // 0.0
/*176 */                 k += band_size_long[i][j];                                               // 0.0
/*178 */             }                                                                            // 0.0
/*180 */             band_index_long[i][22] = k;                                                  // 0.0
/*182 */         }                                                                                // 0.0
/*186 */         /* compute n ^ (4/3) and store it in mantissa/exp format */                      // 0.0
/*190 */         int_pow_init();                                                                  // 0.0
/*192 */         mpegaudio_tableinit();                                                           // 0.0
/*196 */         for (i = 0; i < 4; i++)                                                          // 0.0
/*198 */             if (ff_mpa_quant_bits[i] < 0)                                                // 0.0
/*200 */                 for (j = 0; j < (1<<(-ff_mpa_quant_bits[i]+1)); j++) {                   // 0.0
/*202 */                     int val1, val2, val3, steps;                                         // 0.0
/*204 */                     int val = j;                                                         // 0.0
/*206 */                     steps  = ff_mpa_quant_steps[i];                                      // 0.0
/*208 */                     val1 = val % steps;                                                  // 0.0
/*210 */                     val /= steps;                                                        // 0.0
/*212 */                     val2 = val % steps;                                                  // 0.0
/*214 */                     val3 = val / steps;                                                  // 0.0
/*216 */                     division_tabs[i][j] = val1 + (val2 << 4) + (val3 << 8);              // 0.0
/*218 */                 }                                                                        // 0.0
/*224 */         for(i=0;i<7;i++) {                                                               // 0.0
/*226 */             float f;                                                                     // 0.0
/*228 */             INTFLOAT v;                                                                  // 0.0
/*230 */             if (i != 6) {                                                                // 0.0
/*232 */                 f = tan((double)i * M_PI / 12.0);                                        // 0.0
/*234 */                 v = FIXR(f / (1.0 + f));                                                 // 0.0
/*236 */             } else {                                                                     // 0.0
/*238 */                 v = FIXR(1.0);                                                           // 0.0
/*240 */             }                                                                            // 0.0
/*242 */             is_table[0][i] = v;                                                          // 0.0
/*244 */             is_table[1][6 - i] = v;                                                      // 0.0
/*246 */         }                                                                                // 0.0
/*248 */         /* invalid values */                                                             // 0.0
/*250 */         for(i=7;i<16;i++)                                                                // 0.0
/*252 */             is_table[0][i] = is_table[1][i] = 0.0;                                       // 0.0
/*256 */         for(i=0;i<16;i++) {                                                              // 0.0
/*258 */             double f;                                                                    // 0.0
/*260 */             int e, k;                                                                    // 0.0
/*264 */             for(j=0;j<2;j++) {                                                           // 0.0
/*266 */                 e = -(j + 1) * ((i + 1) >> 1);                                           // 0.0
/*268 */                 f = pow(2.0, e / 4.0);                                                   // 0.0
/*270 */                 k = i & 1;                                                               // 0.0
/*272 */                 is_table_lsf[j][k ^ 1][i] = FIXR(f);                                     // 0.0
/*274 */                 is_table_lsf[j][k][i] = FIXR(1.0);                                       // 0.0
/*276 */                 av_dlog(avctx, "is_table_lsf %d %d: %x %x\n",                            // 0.0
/*278 */                         i, j, is_table_lsf[j][0][i], is_table_lsf[j][1][i]);             // 0.0
/*280 */             }                                                                            // 0.0
/*282 */         }                                                                                // 0.0
/*286 */         for(i=0;i<8;i++) {                                                               // 0.0
/*288 */             float ci, cs, ca;                                                            // 0.0
/*290 */             ci = ci_table[i];                                                            // 0.0
/*292 */             cs = 1.0 / sqrt(1.0 + ci * ci);                                              // 0.0
/*294 */             ca = cs * ci;                                                                // 0.0
/*296 */             csa_table[i][0] = FIXHR(cs/4);                                               // 0.0
/*298 */             csa_table[i][1] = FIXHR(ca/4);                                               // 0.0
/*300 */             csa_table[i][2] = FIXHR(ca/4) + FIXHR(cs/4);                                 // 0.0
/*302 */             csa_table[i][3] = FIXHR(ca/4) - FIXHR(cs/4);                                 // 0.0
/*304 */             csa_table_float[i][0] = cs;                                                  // 0.0
/*306 */             csa_table_float[i][1] = ca;                                                  // 0.0
/*308 */             csa_table_float[i][2] = ca + cs;                                             // 0.0
/*310 */             csa_table_float[i][3] = ca - cs;                                             // 0.0
/*312 */         }                                                                                // 0.0
/*316 */         /* compute mdct windows */                                                       // 0.0
/*318 */         for(i=0;i<36;i++) {                                                              // 0.0
/*320 */             for(j=0; j<4; j++){                                                          // 0.0
/*322 */                 double d;                                                                // 0.0
/*326 */                 if(j==2 && i%3 != 1)                                                     // 0.0
/*328 */                     continue;                                                            // 0.0
/*332 */                 d= sin(M_PI * (i + 0.5) / 36.0);                                         // 0.0
/*334 */                 if(j==1){                                                                // 0.0
/*336 */                     if     (i>=30) d= 0;                                                 // 0.0
/*338 */                     else if(i>=24) d= sin(M_PI * (i - 18 + 0.5) / 12.0);                 // 0.0
/*340 */                     else if(i>=18) d= 1;                                                 // 0.0
/*342 */                 }else if(j==3){                                                          // 0.0
/*344 */                     if     (i<  6) d= 0;                                                 // 0.0
/*346 */                     else if(i< 12) d= sin(M_PI * (i -  6 + 0.5) / 12.0);                 // 0.0
/*348 */                     else if(i< 18) d= 1;                                                 // 0.0
/*350 */                 }                                                                        // 0.0
/*352 */                 //merge last stage of imdct into the window coefficients                 // 0.0
/*354 */                 d*= 0.5 / cos(M_PI*(2*i + 19)/72);                                       // 0.0
/*358 */                 if(j==2)                                                                 // 0.0
/*360 */                     mdct_win[j][i/3] = FIXHR((d / (1<<5)));                              // 0.0
/*362 */                 else                                                                     // 0.0
/*364 */                     mdct_win[j][i  ] = FIXHR((d / (1<<5)));                              // 0.0
/*366 */             }                                                                            // 0.0
/*368 */         }                                                                                // 0.0
/*372 */         /* NOTE: we do frequency inversion adter the MDCT by changing                    // 0.0
/*374 */            the sign of the right window coefs */                                         // 0.0
/*376 */         for(j=0;j<4;j++) {                                                               // 0.0
/*378 */             for(i=0;i<36;i+=2) {                                                         // 0.0
/*380 */                 mdct_win[j + 4][i] = mdct_win[j][i];                                     // 0.0
/*382 */                 mdct_win[j + 4][i + 1] = -mdct_win[j][i + 1];                            // 0.0
/*384 */             }                                                                            // 0.0
/*386 */         }                                                                                // 0.0
/*390 */         init = 1;                                                                        // 0.0
/*392 */     }                                                                                    // 0.0
/*396 */     if (avctx->codec_id == CODEC_ID_MP3ADU)                                              // 0.0
/*398 */         s->adu_mode = 1;                                                                 // 0.0
/*400 */     return 0;                                                                            // 0.0
/*402 */ }                                                                                        // 0.0
