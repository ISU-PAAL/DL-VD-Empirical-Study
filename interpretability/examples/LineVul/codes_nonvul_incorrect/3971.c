// commit message FFmpeg@5a2ad7ede3 (target=0, prob=0.7139461, correct=False): vorbisenc: Separate copying audio samples from windowing
/*0   */ static int apply_window_and_mdct(vorbis_enc_context *venc,                                  // (12) 0.04102
/*2   */                                  float *audio, int samples)                                 // (0) 0.07617
/*4   */ {                                                                                           // (22) 0.001953
/*6   */     int channel;                                                                            // (19) 0.01172
/*8   */     const float * win = venc->win[0];                                                       // (15) 0.0293
/*10  */     int window_len = 1 << (venc->log2_blocksize[0] - 1);                                    // (8) 0.04883
/*12  */     float n = (float)(1 << venc->log2_blocksize[0]) / 4.0;                                  // (6) 0.05273
/*14  */     AVFloatDSPContext *fdsp = venc->fdsp;                                                   // (13) 0.03516
/*18  */     if (!venc->have_saved && !samples)                                                      // (14) 0.0332
/*20  */         return 0;                                                                           // (17) 0.01953
/*24  */     if (venc->have_saved) {                                                                 // (16) 0.02734
/*26  */         for (channel = 0; channel < venc->channels; channel++)                              // (10) 0.04492
/*28  */             memcpy(venc->samples + channel * window_len * 2,                                // (5) 0.05664
/*30  */                    venc->saved + channel * window_len, sizeof(float) * window_len);         // (1) 0.07617
/*32  */     } else {                                                                                // (20) 0.01172
/*34  */         for (channel = 0; channel < venc->channels; channel++)                              // (11) 0.04492
/*36  */             memset(venc->samples + channel * window_len * 2, 0,                             // (4) 0.05859
/*38  */                    sizeof(float) * window_len);                                             // (7) 0.05273
/*40  */     }                                                                                       // (21) 0.007812
/*44  */     if (samples) {                                                                          // (18) 0.01758
/*46  */         for (channel = 0; channel < venc->channels; channel++) {                            // (9) 0.04688
/*48  */             float *offset = venc->samples + channel * window_len * 2 + window_len;          // (3) 0.06445
/*52  */             fdsp->vector_fmul_reverse(offset, audio + channel * window_len, win, samples);  // (2) 0.07031
/*54  */             fdsp->vector_fmul_scalar(offset, offset, 1/n, samples);                         // 0.0
/*56  */         }                                                                                   // 0.0
/*58  */     } else {                                                                                // 0.0
/*60  */         for (channel = 0; channel < venc->channels; channel++)                              // 0.0
/*62  */             memset(venc->samples + channel * window_len * 2 + window_len,                   // 0.0
/*64  */                    0, sizeof(float) * window_len);                                          // 0.0
/*66  */     }                                                                                       // 0.0
/*70  */     for (channel = 0; channel < venc->channels; channel++)                                  // 0.0
/*72  */         venc->mdct[0].mdct_calc(&venc->mdct[0], venc->coeffs + channel * window_len,        // 0.0
/*74  */                      venc->samples + channel * window_len * 2);                             // 0.0
/*78  */     if (samples) {                                                                          // 0.0
/*80  */         for (channel = 0; channel < venc->channels; channel++) {                            // 0.0
/*82  */             float *offset = venc->saved + channel * window_len;                             // 0.0
/*86  */             fdsp->vector_fmul(offset, audio + channel * window_len, win, samples);          // 0.0
/*88  */             fdsp->vector_fmul_scalar(offset, offset, 1/n, samples);                         // 0.0
/*90  */         }                                                                                   // 0.0
/*92  */         venc->have_saved = 1;                                                               // 0.0
/*94  */     } else {                                                                                // 0.0
/*96  */         venc->have_saved = 0;                                                               // 0.0
/*98  */     }                                                                                       // 0.0
/*100 */     return 1;                                                                               // 0.0
/*102 */ }                                                                                           // 0.0
