// commit message FFmpeg@c9f6eab184 (target=1, prob=0.30453998, correct=False): Detect byte-swapped AC-3 (aka DNET) and support decoding it directly.
/*0  */ static av_cold int ac3_decode_init(AVCodecContext *avctx)                                    // (9) 0.04102
/*2  */ {                                                                                            // (26) 0.001955
/*4  */     AC3DecodeContext *s = avctx->priv_data;                                                  // (13) 0.03516
/*6  */     s->avctx = avctx;                                                                        // (22) 0.02148
/*10 */     ff_ac3_common_init();                                                                    // (19) 0.02344
/*12 */     ac3_tables_init();                                                                       // (21) 0.02148
/*14 */     ff_mdct_init(&s->imdct_256, 8, 1, 1.0);                                                  // (1) 0.05078
/*16 */     ff_mdct_init(&s->imdct_512, 9, 1, 1.0);                                                  // (2) 0.05078
/*18 */     ff_kbd_window_init(s->window, 5.0, 256);                                                 // (7) 0.04297
/*20 */     dsputil_init(&s->dsp, avctx);                                                            // (14) 0.03516
/*22 */     ff_fmt_convert_init(&s->fmt_conv, avctx);                                                // (4) 0.04492
/*24 */     av_lfg_init(&s->dith_state, 0);                                                          // (12) 0.03711
/*28 */     /* set scale value for float to int16 conversion */                                      // (17) 0.02734
/*30 */     s->mul_bias = 32767.0f;                                                                  // (15) 0.0332
/*34 */     /* allow downmixing to stereo or mono */                                                 // (18) 0.02539
/*36 */     if (avctx->channels > 0 && avctx->request_channels > 0 &&                                // (5) 0.04492
/*38 */             avctx->request_channels < avctx->channels &&                                     // (3) 0.04883
/*40 */             avctx->request_channels <= 2) {                                                  // (8) 0.04297
/*42 */         avctx->channels = avctx->request_channels;                                           // (10) 0.04101
/*44 */     }                                                                                        // (25) 0.007812
/*46 */     s->downmixed = 1;                                                                        // (20) 0.02148
/*50 */     /* allocate context input buffer */                                                      // (23) 0.01758
/*52 */     if (avctx->error_recognition >= FF_ER_CAREFUL) {                                         // (6) 0.04297
/*54 */         s->input_buffer = av_mallocz(AC3_FRAME_BUFFER_SIZE + FF_INPUT_BUFFER_PADDING_SIZE);  // (0) 0.08594
/*56 */         if (!s->input_buffer)                                                                // (16) 0.0293
/*58 */             return AVERROR(ENOMEM);                                                          // (11) 0.03906
/*60 */     }                                                                                        // (24) 0.007812
/*64 */     avctx->sample_fmt = AV_SAMPLE_FMT_S16;                                                   // 0.0
/*66 */     return 0;                                                                                // 0.0
/*68 */ }                                                                                            // 0.0
