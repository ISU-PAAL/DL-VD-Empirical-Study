// commit message FFmpeg@37013fd018 (target=0, prob=0.6787428, correct=False): swresample/swresample-test: Add () to protect uint_rand() argument
/*0   */ static void audiogen(void *data, enum AVSampleFormat sample_fmt,            // (9) 0.03516
/*2   */                      int channels, int sample_rate, int nb_samples)         // (0) 0.06836
/*4   */ {                                                                           // (26) 0.001953
/*6   */     int i, ch, k;                                                           // (20) 0.01953
/*8   */     double v, f, a, ampa;                                                   // (19) 0.02539
/*10  */     double tabf1[SWR_CH_MAX];                                               // (16) 0.0293
/*12  */     double tabf2[SWR_CH_MAX];                                               // (15) 0.0293
/*14  */     double taba[SWR_CH_MAX];                                                // (18) 0.02734
/*16  */     unsigned static rnd;                                                    // (21) 0.01563
/*20  */ #define PUT_SAMPLE set(data, ch, k, channels, sample_fmt, v);               // (5) 0.04687
/*22  */ #define uint_rand(x) (x = x * 1664525 + 1013904223)                         // (6) 0.04297
/*24  */ #define dbl_rand(x) (uint_rand(x)*2.0 / (double)UINT_MAX - 1)               // (3) 0.05859
/*26  */     k = 0;                                                                  // (22) 0.01367
/*30  */     /* 1 second of single freq sinus at 1000 Hz */                          // (12) 0.03125
/*32  */     a = 0;                                                                  // (23) 0.01367
/*34  */     for (i = 0; i < 1 * sample_rate && k < nb_samples; i++, k++) {          // (1) 0.06055
/*36  */         v = sin(a) * 0.30;                                                  // (10) 0.03516
/*38  */         for (ch = 0; ch < channels; ch++)                                   // (7) 0.03711
/*40  */             PUT_SAMPLE                                                      // (14) 0.03125
/*42  */         a += M_PI * 1000.0 * 2.0 / sample_rate;                             // (4) 0.04883
/*44  */     }                                                                       // (25) 0.007812
/*48  */     /* 1 second of varying frequency between 100 and 10000 Hz */            // (17) 0.0293
/*50  */     a = 0;                                                                  // (24) 0.01367
/*52  */     for (i = 0; i < 1 * sample_rate && k < nb_samples; i++, k++) {          // (2) 0.06055
/*54  */         v = sin(a) * 0.30;                                                  // (11) 0.03516
/*56  */         for (ch = 0; ch < channels; ch++)                                   // (8) 0.03711
/*58  */             PUT_SAMPLE                                                      // (13) 0.03125
/*60  */         f  = 100.0 + (((10000.0 - 100.0) * i) / sample_rate);               // 0.0
/*62  */         a += M_PI * f * 2.0 / sample_rate;                                  // 0.0
/*64  */     }                                                                       // 0.0
/*68  */     /* 0.5 second of low amplitude white noise */                           // 0.0
/*70  */     for (i = 0; i < sample_rate / 2 && k < nb_samples; i++, k++) {          // 0.0
/*72  */         v = dbl_rand(rnd) * 0.30;                                           // 0.0
/*74  */         for (ch = 0; ch < channels; ch++)                                   // 0.0
/*76  */             PUT_SAMPLE                                                      // 0.0
/*78  */     }                                                                       // 0.0
/*82  */     /* 0.5 second of high amplitude white noise */                          // 0.0
/*84  */     for (i = 0; i < sample_rate / 2 && k < nb_samples; i++, k++) {          // 0.0
/*86  */         v = dbl_rand(rnd);                                                  // 0.0
/*88  */         for (ch = 0; ch < channels; ch++)                                   // 0.0
/*90  */             PUT_SAMPLE                                                      // 0.0
/*92  */     }                                                                       // 0.0
/*96  */     /* 1 second of unrelated ramps for each channel */                      // 0.0
/*98  */     for (ch = 0; ch < channels; ch++) {                                     // 0.0
/*100 */         taba[ch]  = 0;                                                      // 0.0
/*102 */         tabf1[ch] = 100 + uint_rand(rnd) % 5000;                            // 0.0
/*104 */         tabf2[ch] = 100 + uint_rand(rnd) % 5000;                            // 0.0
/*106 */     }                                                                       // 0.0
/*108 */     for (i = 0; i < 1 * sample_rate && k < nb_samples; i++, k++) {          // 0.0
/*110 */         for (ch = 0; ch < channels; ch++) {                                 // 0.0
/*112 */             v = sin(taba[ch]) * 0.30;                                       // 0.0
/*114 */             PUT_SAMPLE                                                      // 0.0
/*116 */             f = tabf1[ch] + (((tabf2[ch] - tabf1[ch]) * i) / sample_rate);  // 0.0
/*118 */             taba[ch] += M_PI * f * 2.0 / sample_rate;                       // 0.0
/*120 */         }                                                                   // 0.0
/*122 */     }                                                                       // 0.0
/*126 */     /* 2 seconds of 500 Hz with varying volume */                           // 0.0
/*128 */     a    = 0;                                                               // 0.0
/*130 */     ampa = 0;                                                               // 0.0
/*132 */     for (i = 0; i < 2 * sample_rate && k < nb_samples; i++, k++) {          // 0.0
/*134 */         for (ch = 0; ch < channels; ch++) {                                 // 0.0
/*136 */             double amp = (1.0 + sin(ampa)) * 0.15;                          // 0.0
/*138 */             if (ch & 1)                                                     // 0.0
/*140 */                 amp = 0.30 - amp;                                           // 0.0
/*142 */             v = sin(a) * amp;                                               // 0.0
/*144 */             PUT_SAMPLE                                                      // 0.0
/*146 */             a    += M_PI * 500.0 * 2.0 / sample_rate;                       // 0.0
/*148 */             ampa += M_PI *  2.0 / sample_rate;                              // 0.0
/*150 */         }                                                                   // 0.0
/*152 */     }                                                                       // 0.0
/*154 */ }                                                                           // 0.0
