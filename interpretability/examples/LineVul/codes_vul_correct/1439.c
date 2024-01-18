// commit message FFmpeg@16c429166d (target=1, prob=0.5931199, correct=True): Revert "apngdec: use side data to pass extradata to the decoder"
/*0  */ static av_cold int png_dec_end(AVCodecContext *avctx)       // (2) 0.07018
/*2  */ {                                                           // (17) 0.003509
/*4  */     PNGDecContext *s = avctx->priv_data;                    // (6) 0.05614
/*8  */     ff_thread_release_buffer(avctx, &s->previous_picture);  // (0) 0.07719
/*10 */     av_frame_free(&s->previous_picture.f);                  // (4) 0.06316
/*12 */     ff_thread_release_buffer(avctx, &s->last_picture);      // (1) 0.07368
/*14 */     av_frame_free(&s->last_picture.f);                      // (5) 0.05965
/*16 */     ff_thread_release_buffer(avctx, &s->picture);           // (3) 0.06667
/*18 */     av_frame_free(&s->picture.f);                           // (7) 0.05263
/*20 */     av_freep(&s->buffer);                                   // (14) 0.04211
/*22 */     s->buffer_size = 0;                                     // (15) 0.0386
/*24 */     av_freep(&s->last_row);                                 // (8) 0.04912
/*26 */     s->last_row_size = 0;                                   // (11) 0.04561
/*28 */     av_freep(&s->tmp_row);                                  // (9) 0.04912
/*30 */     s->tmp_row_size = 0;                                    // (12) 0.04561
/*32 */     av_freep(&s->extra_data);                               // (10) 0.04912
/*34 */     s->extra_data_size = 0;                                 // (13) 0.04561
/*38 */     return 0;                                               // (16) 0.02105
/*40 */ }                                                           // (18) 0.003509
