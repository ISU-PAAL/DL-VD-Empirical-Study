// commit message FFmpeg@7167bc94cb (target=1, prob=0.61791867, correct=True): aacdec: Remove the warning about non-meaningful window transitions.
/*0   */ static void imdct_and_windowing(AACContext *ac, SingleChannelElement *sce, float bias)                              // (6) 0.05273
/*2   */ {                                                                                                                   // (18) 0.001953
/*4   */     IndividualChannelStream *ics = &sce->ics;                                                                       // (11) 0.0293
/*6   */     float *in    = sce->coeffs;                                                                                     // (10) 0.0332
/*8   */     float *out   = sce->ret;                                                                                        // (13) 0.02734
/*10  */     float *saved = sce->saved;                                                                                      // (14) 0.02734
/*12  */     const float *swindow      = ics->use_kb_window[0] ? ff_aac_kbd_short_128 : ff_sine_128;                         // (0) 0.08984
/*14  */     const float *lwindow_prev = ics->use_kb_window[1] ? ff_aac_kbd_long_1024 : ff_sine_1024;                        // (4) 0.08203
/*16  */     const float *swindow_prev = ics->use_kb_window[1] ? ff_aac_kbd_short_128 : ff_sine_128;                         // (3) 0.08398
/*18  */     float *buf  = ac->buf_mdct;                                                                                     // (12) 0.0293
/*20  */     float *temp = ac->temp;                                                                                         // (15) 0.02148
/*22  */     int i;                                                                                                          // (17) 0.01172
/*26  */     // imdct                                                                                                        // (16) 0.01367
/*28  */     if (ics->window_sequence[0] == EIGHT_SHORT_SEQUENCE) {                                                          // (8) 0.04883
/*30  */         if (ics->window_sequence[1] == ONLY_LONG_SEQUENCE || ics->window_sequence[1] == LONG_STOP_SEQUENCE)         // (1) 0.08984
/*32  */             av_log(ac->avctx, AV_LOG_WARNING,                                                                       // (7) 0.05078
/*34  */                    "Transition from an ONLY_LONG or LONG_STOP to an EIGHT_SHORT sequence detected. "                // (2) 0.08398
/*36  */                    "If you heard an audible artifact, please submit the sample to the FFmpeg developers.\n");       // (5) 0.07617
/*38  */         for (i = 0; i < 1024; i += 128)                                                                             // (9) 0.04102
/*40  */             ff_imdct_half(&ac->mdct_small, buf + i, in + i);                                                        // 0.0
/*42  */     } else                                                                                                          // 0.0
/*44  */         ff_imdct_half(&ac->mdct, buf, in);                                                                          // 0.0
/*48  */     /* window overlapping                                                                                           // 0.0
/*50  */      * NOTE: To simplify the overlapping code, all 'meaningless' short to long                                      // 0.0
/*52  */      * and long to short transitions are considered to be short to short                                            // 0.0
/*54  */      * transitions. This leaves just two cases (long to long and short to short)                                    // 0.0
/*56  */      * with a little special sauce for EIGHT_SHORT_SEQUENCE.                                                        // 0.0
/*58  */      */                                                                                                             // 0.0
/*60  */     if ((ics->window_sequence[1] == ONLY_LONG_SEQUENCE || ics->window_sequence[1] == LONG_STOP_SEQUENCE) &&         // 0.0
/*62  */             (ics->window_sequence[0] == ONLY_LONG_SEQUENCE || ics->window_sequence[0] == LONG_START_SEQUENCE)) {    // 0.0
/*64  */         ac->dsp.vector_fmul_window(    out,               saved,            buf,         lwindow_prev, bias, 512);  // 0.0
/*66  */     } else {                                                                                                        // 0.0
/*68  */         for (i = 0; i < 448; i++)                                                                                   // 0.0
/*70  */             out[i] = saved[i] + bias;                                                                               // 0.0
/*74  */         if (ics->window_sequence[0] == EIGHT_SHORT_SEQUENCE) {                                                      // 0.0
/*76  */             ac->dsp.vector_fmul_window(out + 448 + 0*128, saved + 448,      buf + 0*128, swindow_prev, bias, 64);   // 0.0
/*78  */             ac->dsp.vector_fmul_window(out + 448 + 1*128, buf + 0*128 + 64, buf + 1*128, swindow,      bias, 64);   // 0.0
/*80  */             ac->dsp.vector_fmul_window(out + 448 + 2*128, buf + 1*128 + 64, buf + 2*128, swindow,      bias, 64);   // 0.0
/*82  */             ac->dsp.vector_fmul_window(out + 448 + 3*128, buf + 2*128 + 64, buf + 3*128, swindow,      bias, 64);   // 0.0
/*84  */             ac->dsp.vector_fmul_window(temp,              buf + 3*128 + 64, buf + 4*128, swindow,      bias, 64);   // 0.0
/*86  */             memcpy(                    out + 448 + 4*128, temp, 64 * sizeof(float));                                // 0.0
/*88  */         } else {                                                                                                    // 0.0
/*90  */             ac->dsp.vector_fmul_window(out + 448,         saved + 448,      buf,         swindow_prev, bias, 64);   // 0.0
/*92  */             for (i = 576; i < 1024; i++)                                                                            // 0.0
/*94  */                 out[i] = buf[i-512] + bias;                                                                         // 0.0
/*96  */         }                                                                                                           // 0.0
/*98  */     }                                                                                                               // 0.0
/*102 */     // buffer update                                                                                                // 0.0
/*104 */     if (ics->window_sequence[0] == EIGHT_SHORT_SEQUENCE) {                                                          // 0.0
/*106 */         for (i = 0; i < 64; i++)                                                                                    // 0.0
/*108 */             saved[i] = temp[64 + i] - bias;                                                                         // 0.0
/*110 */         ac->dsp.vector_fmul_window(saved + 64,  buf + 4*128 + 64, buf + 5*128, swindow, 0, 64);                     // 0.0
/*112 */         ac->dsp.vector_fmul_window(saved + 192, buf + 5*128 + 64, buf + 6*128, swindow, 0, 64);                     // 0.0
/*114 */         ac->dsp.vector_fmul_window(saved + 320, buf + 6*128 + 64, buf + 7*128, swindow, 0, 64);                     // 0.0
/*116 */         memcpy(                    saved + 448, buf + 7*128 + 64,  64 * sizeof(float));                             // 0.0
/*118 */     } else if (ics->window_sequence[0] == LONG_START_SEQUENCE) {                                                    // 0.0
/*120 */         memcpy(                    saved,       buf + 512,        448 * sizeof(float));                             // 0.0
/*122 */         memcpy(                    saved + 448, buf + 7*128 + 64,  64 * sizeof(float));                             // 0.0
/*124 */     } else { // LONG_STOP or ONLY_LONG                                                                              // 0.0
/*126 */         memcpy(                    saved,       buf + 512,        512 * sizeof(float));                             // 0.0
/*128 */     }                                                                                                               // 0.0
/*130 */ }                                                                                                                   // 0.0
