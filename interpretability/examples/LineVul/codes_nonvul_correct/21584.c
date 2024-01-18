// commit message FFmpeg@f3e5a7844b (target=0, prob=0.06667007, correct=True): alac: calculate buffer size outside the loop in allocate_buffers()
/*0  */ static int allocate_buffers(ALACContext *alac)                              // (10) 0.03581
/*2  */ {                                                                           // (17) 0.002558
/*4  */     int ch;                                                                 // (14) 0.01535
/*6  */     for (ch = 0; ch < FFMIN(alac->channels, 2); ch++) {                     // (7) 0.06394
/*8  */         int buf_size = alac->max_samples_per_frame * sizeof(int32_t);       // (6) 0.07928
/*12 */         FF_ALLOC_OR_GOTO(alac->avctx, alac->predict_error_buffer[ch],       // (2) 0.08951
/*14 */                          buf_size, buf_alloc_fail);                         // (3) 0.08696
/*18 */         if (alac->sample_size == 16) {                                      // (8) 0.04859
/*20 */             FF_ALLOC_OR_GOTO(alac->avctx, alac->output_samples_buffer[ch],  // (0) 0.09974
/*22 */                              buf_size, buf_alloc_fail);                     // (1) 0.09719
/*24 */         }                                                                   // (12) 0.02046
/*28 */         FF_ALLOC_OR_GOTO(alac->avctx, alac->extra_bits_buffer[ch],          // (4) 0.08696
/*30 */                          buf_size, buf_alloc_fail);                         // (5) 0.08696
/*32 */     }                                                                       // (16) 0.01023
/*34 */     return 0;                                                               // (15) 0.01535
/*36 */ buf_alloc_fail:                                                             // (13) 0.01535
/*38 */     alac_decode_close(alac->avctx);                                         // (9) 0.04348
/*40 */     return AVERROR(ENOMEM);                                                 // (11) 0.03069
/*42 */ }                                                                           // (18) 0.002558
