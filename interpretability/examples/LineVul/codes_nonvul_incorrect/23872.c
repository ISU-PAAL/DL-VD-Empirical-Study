// commit message FFmpeg@0780ad9c68 (target=0, prob=0.57166845, correct=False): avcodec/rdft: remove sintable
/*0  */ static void rdft_calc_c(RDFTContext *s, FFTSample *data)                     // (6) 0.04688
/*2  */ {                                                                            // (25) 0.001953
/*4  */     int i, i1, i2;                                                           // (19) 0.02344
/*6  */     FFTComplex ev, od;                                                       // (22) 0.02148
/*8  */     const int n = 1 << s->nbits;                                             // (17) 0.02734
/*10 */     const float k1 = 0.5;                                                    // (20) 0.02344
/*12 */     const float k2 = 0.5 - s->inverse;                                       // (11) 0.0332
/*14 */     const FFTSample *tcos = s->tcos;                                         // (12) 0.03125
/*16 */     const FFTSample *tsin = s->tsin;                                         // (13) 0.03125
/*20 */     if (!s->inverse) {                                                       // (21) 0.02148
/*22 */         s->fft.fft_permute(&s->fft, (FFTComplex*)data);                      // (1) 0.06055
/*24 */         s->fft.fft_calc(&s->fft, (FFTComplex*)data);                         // (0) 0.06055
/*26 */     }                                                                        // (24) 0.007812
/*28 */     /* i=0 is a special case because of packing, the DC term is real, so we  // (8) 0.04492
/*30 */        are going to throw the N/2 term (also real) in with it. */            // (7) 0.04688
/*32 */     ev.re = data[0];                                                         // (23) 0.02148
/*34 */     data[0] = ev.re+data[1];                                                 // (14) 0.03125
/*36 */     data[1] = ev.re-data[1];                                                 // (15) 0.03125
/*38 */     for (i = 1; i < (n>>2); i++) {                                           // (9) 0.03711
/*40 */         i1 = 2*i;                                                            // (18) 0.02734
/*42 */         i2 = n-i1;                                                           // (16) 0.0293
/*44 */         /* Separate even and odd FFTs */                                     // (10) 0.0332
/*46 */         ev.re =  k1*(data[i1  ]+data[i2  ]);                                 // (2) 0.05859
/*48 */         od.im = -k2*(data[i1  ]-data[i2  ]);                                 // (3) 0.05859
/*50 */         ev.im =  k1*(data[i1+1]-data[i2+1]);                                 // (4) 0.05859
/*52 */         od.re =  k2*(data[i1+1]+data[i2+1]);                                 // (5) 0.05859
/*54 */         /* Apply twiddle factors to the odd FFT and add to the even FFT */   // 0.0
/*56 */         data[i1  ] =  ev.re + od.re*tcos[i] - od.im*tsin[i];                 // 0.0
/*58 */         data[i1+1] =  ev.im + od.im*tcos[i] + od.re*tsin[i];                 // 0.0
/*60 */         data[i2  ] =  ev.re - od.re*tcos[i] + od.im*tsin[i];                 // 0.0
/*62 */         data[i2+1] = -ev.im + od.im*tcos[i] + od.re*tsin[i];                 // 0.0
/*64 */     }                                                                        // 0.0
/*66 */     data[2*i+1]=s->sign_convention*data[2*i+1];                              // 0.0
/*68 */     if (s->inverse) {                                                        // 0.0
/*70 */         data[0] *= k1;                                                       // 0.0
/*72 */         data[1] *= k1;                                                       // 0.0
/*74 */         s->fft.fft_permute(&s->fft, (FFTComplex*)data);                      // 0.0
/*76 */         s->fft.fft_calc(&s->fft, (FFTComplex*)data);                         // 0.0
/*78 */     }                                                                        // 0.0
/*80 */ }                                                                            // 0.0
