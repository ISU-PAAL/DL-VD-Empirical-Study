// commit message FFmpeg@1197c04896 (target=1, prob=0.43122238, correct=False): avcodec/fft_template: Fix multiple runtime error: signed integer overflow: -1943918714 - 1935113003 cannot be represented in type 'int'
/*0   */ static void fft_calc_c(FFTContext *s, FFTComplex *z) {                             // (3) 0.04698
/*4   */     int nbits, i, n, num_transforms, offset, step;                                 // (12) 0.04141
/*6   */     int n4, n2, n34;                                                               // (20) 0.02543
/*8   */     FFTSample tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8;                      // (0) 0.05836
/*10  */     FFTComplex *tmpz;                                                              // (21) 0.02145
/*12  */     const int fft_size = (1 << s->nbits);                                          // (18) 0.03512
/*14  */     int64_t accu;                                                                  // (22) 0.01953
/*18  */     num_transforms = (0x2aab >> (16 - s->nbits)) | 1;                              // (1) 0.05073
/*22  */     for (n=0; n<num_transforms; n++){                                              // (17) 0.0372
/*24  */         offset = ff_fft_offsets_lut[n] << 2;                                       // (2) 0.04918
/*26  */         tmpz = z + offset;                                                         // (19) 0.02743
/*30  */         tmp1 = tmpz[0].re + tmpz[1].re;                                            // (4) 0.04663
/*32  */         tmp5 = tmpz[2].re + tmpz[3].re;                                            // (7) 0.04663
/*34  */         tmp2 = tmpz[0].im + tmpz[1].im;                                            // (9) 0.04663
/*36  */         tmp6 = tmpz[2].im + tmpz[3].im;                                            // (5) 0.04663
/*38  */         tmp3 = tmpz[0].re - tmpz[1].re;                                            // (10) 0.04663
/*40  */         tmp8 = tmpz[2].im - tmpz[3].im;                                            // (6) 0.04663
/*42  */         tmp4 = tmpz[0].im - tmpz[1].im;                                            // (11) 0.04662
/*44  */         tmp7 = tmpz[2].re - tmpz[3].re;                                            // (8) 0.04663
/*48  */         tmpz[0].re = tmp1 + tmp5;                                                  // (14) 0.03886
/*50  */         tmpz[2].re = tmp1 - tmp5;                                                  // (15) 0.03885
/*52  */         tmpz[0].im = tmp2 + tmp6;                                                  // (16) 0.03885
/*54  */         tmpz[2].im = tmp2 - tmp6;                                                  // (13) 0.03886
/*56  */         tmpz[1].re = tmp3 + tmp8;                                                  // 0.0
/*58  */         tmpz[3].re = tmp3 - tmp8;                                                  // 0.0
/*60  */         tmpz[1].im = tmp4 - tmp7;                                                  // 0.0
/*62  */         tmpz[3].im = tmp4 + tmp7;                                                  // 0.0
/*64  */     }                                                                              // 0.0
/*68  */     if (fft_size < 8)                                                              // 0.0
/*70  */         return;                                                                    // 0.0
/*74  */     num_transforms = (num_transforms >> 1) | 1;                                    // 0.0
/*78  */     for (n=0; n<num_transforms; n++){                                              // 0.0
/*80  */         offset = ff_fft_offsets_lut[n] << 3;                                       // 0.0
/*82  */         tmpz = z + offset;                                                         // 0.0
/*86  */         tmp1 = tmpz[4].re + tmpz[5].re;                                            // 0.0
/*88  */         tmp3 = tmpz[6].re + tmpz[7].re;                                            // 0.0
/*90  */         tmp2 = tmpz[4].im + tmpz[5].im;                                            // 0.0
/*92  */         tmp4 = tmpz[6].im + tmpz[7].im;                                            // 0.0
/*94  */         tmp5 = tmp1 + tmp3;                                                        // 0.0
/*96  */         tmp7 = tmp1 - tmp3;                                                        // 0.0
/*98  */         tmp6 = tmp2 + tmp4;                                                        // 0.0
/*100 */         tmp8 = tmp2 - tmp4;                                                        // 0.0
/*104 */         tmp1 = tmpz[4].re - tmpz[5].re;                                            // 0.0
/*106 */         tmp2 = tmpz[4].im - tmpz[5].im;                                            // 0.0
/*108 */         tmp3 = tmpz[6].re - tmpz[7].re;                                            // 0.0
/*110 */         tmp4 = tmpz[6].im - tmpz[7].im;                                            // 0.0
/*114 */         tmpz[4].re = tmpz[0].re - tmp5;                                            // 0.0
/*116 */         tmpz[0].re = tmpz[0].re + tmp5;                                            // 0.0
/*118 */         tmpz[4].im = tmpz[0].im - tmp6;                                            // 0.0
/*120 */         tmpz[0].im = tmpz[0].im + tmp6;                                            // 0.0
/*122 */         tmpz[6].re = tmpz[2].re - tmp8;                                            // 0.0
/*124 */         tmpz[2].re = tmpz[2].re + tmp8;                                            // 0.0
/*126 */         tmpz[6].im = tmpz[2].im + tmp7;                                            // 0.0
/*128 */         tmpz[2].im = tmpz[2].im - tmp7;                                            // 0.0
/*132 */         accu = (int64_t)Q31(M_SQRT1_2)*(tmp1 + tmp2);                              // 0.0
/*134 */         tmp5 = (int32_t)((accu + 0x40000000) >> 31);                               // 0.0
/*136 */         accu = (int64_t)Q31(M_SQRT1_2)*(tmp3 - tmp4);                              // 0.0
/*138 */         tmp7 = (int32_t)((accu + 0x40000000) >> 31);                               // 0.0
/*140 */         accu = (int64_t)Q31(M_SQRT1_2)*(tmp2 - tmp1);                              // 0.0
/*142 */         tmp6 = (int32_t)((accu + 0x40000000) >> 31);                               // 0.0
/*144 */         accu = (int64_t)Q31(M_SQRT1_2)*(tmp3 + tmp4);                              // 0.0
/*146 */         tmp8 = (int32_t)((accu + 0x40000000) >> 31);                               // 0.0
/*148 */         tmp1 = tmp5 + tmp7;                                                        // 0.0
/*150 */         tmp3 = tmp5 - tmp7;                                                        // 0.0
/*152 */         tmp2 = tmp6 + tmp8;                                                        // 0.0
/*154 */         tmp4 = tmp6 - tmp8;                                                        // 0.0
/*158 */         tmpz[5].re = tmpz[1].re - tmp1;                                            // 0.0
/*160 */         tmpz[1].re = tmpz[1].re + tmp1;                                            // 0.0
/*162 */         tmpz[5].im = tmpz[1].im - tmp2;                                            // 0.0
/*164 */         tmpz[1].im = tmpz[1].im + tmp2;                                            // 0.0
/*166 */         tmpz[7].re = tmpz[3].re - tmp4;                                            // 0.0
/*168 */         tmpz[3].re = tmpz[3].re + tmp4;                                            // 0.0
/*170 */         tmpz[7].im = tmpz[3].im + tmp3;                                            // 0.0
/*172 */         tmpz[3].im = tmpz[3].im - tmp3;                                            // 0.0
/*174 */     }                                                                              // 0.0
/*178 */     step = 1 << ((MAX_LOG2_NFFT-4) - 4);                                           // 0.0
/*180 */     n4 = 4;                                                                        // 0.0
/*184 */     for (nbits=4; nbits<=s->nbits; nbits++){                                       // 0.0
/*186 */         n2  = 2*n4;                                                                // 0.0
/*188 */         n34 = 3*n4;                                                                // 0.0
/*190 */         num_transforms = (num_transforms >> 1) | 1;                                // 0.0
/*194 */         for (n=0; n<num_transforms; n++){                                          // 0.0
/*196 */             const FFTSample *w_re_ptr = ff_w_tab_sr + step;                        // 0.0
/*198 */             const FFTSample *w_im_ptr = ff_w_tab_sr + MAX_FFT_SIZE/(4*16) - step;  // 0.0
/*200 */             offset = ff_fft_offsets_lut[n] << nbits;                               // 0.0
/*202 */             tmpz = z + offset;                                                     // 0.0
/*206 */             tmp5 = tmpz[ n2].re + tmpz[n34].re;                                    // 0.0
/*208 */             tmp1 = tmpz[ n2].re - tmpz[n34].re;                                    // 0.0
/*210 */             tmp6 = tmpz[ n2].im + tmpz[n34].im;                                    // 0.0
/*212 */             tmp2 = tmpz[ n2].im - tmpz[n34].im;                                    // 0.0
/*216 */             tmpz[ n2].re = tmpz[ 0].re - tmp5;                                     // 0.0
/*218 */             tmpz[  0].re = tmpz[ 0].re + tmp5;                                     // 0.0
/*220 */             tmpz[ n2].im = tmpz[ 0].im - tmp6;                                     // 0.0
/*222 */             tmpz[  0].im = tmpz[ 0].im + tmp6;                                     // 0.0
/*224 */             tmpz[n34].re = tmpz[n4].re - tmp2;                                     // 0.0
/*226 */             tmpz[ n4].re = tmpz[n4].re + tmp2;                                     // 0.0
/*228 */             tmpz[n34].im = tmpz[n4].im + tmp1;                                     // 0.0
/*230 */             tmpz[ n4].im = tmpz[n4].im - tmp1;                                     // 0.0
/*234 */             for (i=1; i<n4; i++){                                                  // 0.0
/*236 */                 FFTSample w_re = w_re_ptr[0];                                      // 0.0
/*238 */                 FFTSample w_im = w_im_ptr[0];                                      // 0.0
/*240 */                 accu  = (int64_t)w_re*tmpz[ n2+i].re;                              // 0.0
/*242 */                 accu += (int64_t)w_im*tmpz[ n2+i].im;                              // 0.0
/*244 */                 tmp1 = (int32_t)((accu + 0x40000000) >> 31);                       // 0.0
/*246 */                 accu  = (int64_t)w_re*tmpz[ n2+i].im;                              // 0.0
/*248 */                 accu -= (int64_t)w_im*tmpz[ n2+i].re;                              // 0.0
/*250 */                 tmp2 = (int32_t)((accu + 0x40000000) >> 31);                       // 0.0
/*252 */                 accu  = (int64_t)w_re*tmpz[n34+i].re;                              // 0.0
/*254 */                 accu -= (int64_t)w_im*tmpz[n34+i].im;                              // 0.0
/*256 */                 tmp3 = (int32_t)((accu + 0x40000000) >> 31);                       // 0.0
/*258 */                 accu  = (int64_t)w_re*tmpz[n34+i].im;                              // 0.0
/*260 */                 accu += (int64_t)w_im*tmpz[n34+i].re;                              // 0.0
/*262 */                 tmp4 = (int32_t)((accu + 0x40000000) >> 31);                       // 0.0
/*266 */                 tmp5 = tmp1 + tmp3;                                                // 0.0
/*268 */                 tmp1 = tmp1 - tmp3;                                                // 0.0
/*270 */                 tmp6 = tmp2 + tmp4;                                                // 0.0
/*272 */                 tmp2 = tmp2 - tmp4;                                                // 0.0
/*276 */                 tmpz[ n2+i].re = tmpz[   i].re - tmp5;                             // 0.0
/*278 */                 tmpz[    i].re = tmpz[   i].re + tmp5;                             // 0.0
/*280 */                 tmpz[ n2+i].im = tmpz[   i].im - tmp6;                             // 0.0
/*282 */                 tmpz[    i].im = tmpz[   i].im + tmp6;                             // 0.0
/*284 */                 tmpz[n34+i].re = tmpz[n4+i].re - tmp2;                             // 0.0
/*286 */                 tmpz[ n4+i].re = tmpz[n4+i].re + tmp2;                             // 0.0
/*288 */                 tmpz[n34+i].im = tmpz[n4+i].im + tmp1;                             // 0.0
/*290 */                 tmpz[ n4+i].im = tmpz[n4+i].im - tmp1;                             // 0.0
/*294 */                 w_re_ptr += step;                                                  // 0.0
/*296 */                 w_im_ptr -= step;                                                  // 0.0
/*298 */             }                                                                      // 0.0
/*300 */         }                                                                          // 0.0
/*302 */         step >>= 1;                                                                // 0.0
/*304 */         n4   <<= 1;                                                                // 0.0
/*306 */     }                                                                              // 0.0
/*308 */ }                                                                                  // 0.0
