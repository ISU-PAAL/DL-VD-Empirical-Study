// commit message FFmpeg@204cb29b3c (target=1, prob=0.56838477, correct=True): shorten: Use separate pointers for the allocated memory for decoded samples.
/*0  */ static av_cold int shorten_decode_close(AVCodecContext *avctx)  // (0) 0.1136
/*2  */ {                                                               // (11) 0.005682
/*4  */     ShortenContext *s = avctx->priv_data;                       // (5) 0.09091
/*6  */     int i;                                                      // (8) 0.03409
/*10 */     for (i = 0; i < s->channels; i++) {                         // (2) 0.108
/*12 */         s->decoded[i] -= s->nwrap;                              // (1) 0.1136
/*14 */         av_freep(&s->decoded[i]);                               // (3) 0.108
/*16 */         av_freep(&s->offset[i]);                                // (4) 0.1023
/*18 */     }                                                           // (10) 0.02273
/*20 */     av_freep(&s->bitstream);                                    // (7) 0.07386
/*22 */     av_freep(&s->coeffs);                                       // (6) 0.07955
/*26 */     return 0;                                                   // (9) 0.03409
/*28 */ }                                                               // (12) 0.005682
