// commit message FFmpeg@aa6aa2ef09 (target=0, prob=0.80366206, correct=False): avcodec/wmaenc: Check input for finiteness
/*0  */ static void apply_window_and_mdct(AVCodecContext *avctx, const AVFrame *frame)  // (8) 0.05219
/*2  */ {                                                                               // (18) 0.002088
/*4  */     WMACodecContext *s = avctx->priv_data;                                      // (14) 0.03758
/*6  */     float **audio      = (float **) frame->extended_data;                       // (11) 0.04802
/*8  */     int len            = frame->nb_samples;                                     // (9) 0.0501
/*10 */     int window_index   = s->frame_len_bits - s->block_len_bits;                 // (7) 0.05428
/*12 */     FFTContext *mdct   = &s->mdct_ctx[window_index];                            // (10) 0.0501
/*14 */     int ch;                                                                     // (16) 0.01253
/*16 */     const float *win   = s->windows[window_index];                              // (15) 0.03758
/*18 */     int window_len     = 1 << s->block_len_bits;                                // (12) 0.04593
/*20 */     float n            = 2.0 * 32768.0 / window_len;                            // (6) 0.06263
/*24 */     for (ch = 0; ch < avctx->channels; ch++) {                                  // (13) 0.04175
/*26 */         memcpy(s->output, s->frame_out[ch], window_len * sizeof(*s->output));   // (4) 0.06889
/*28 */         s->fdsp->vector_fmul_scalar(s->frame_out[ch], audio[ch], n, len);       // (1) 0.07724
/*30 */         s->fdsp->vector_fmul_reverse(&s->output[window_len], s->frame_out[ch],  // (3) 0.07307
/*32 */                                     win, len);                                  // (0) 0.08142
/*34 */         s->fdsp->vector_fmul(s->frame_out[ch], s->frame_out[ch], win, len);     // (2) 0.07724
/*36 */         mdct->mdct_calc(mdct, s->coefs[ch], s->output);                         // (5) 0.06472
/*38 */     }                                                                           // (17) 0.008351
/*40 */ }                                                                               // (19) 0.002088
