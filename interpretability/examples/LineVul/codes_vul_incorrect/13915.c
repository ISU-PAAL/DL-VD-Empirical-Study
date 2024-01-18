// commit message FFmpeg@220b24c7c9 (target=1, prob=0.44242153, correct=False): lavc: remove libschroedinger encoding and decoding wrappers
/*0  */ static int libschroedinger_encode_close(AVCodecContext *avctx)  // (4) 0.08108
/*2  */ {                                                               // (13) 0.003861
/*4  */     SchroEncoderParams *p_schro_params = avctx->priv_data;      // (2) 0.0888
/*8  */     /* Close the encoder. */                                    // (11) 0.03861
/*10 */     schro_encoder_free(p_schro_params->encoder);                // (5) 0.08108
/*14 */     /* Free data in the output frame queue. */                  // (8) 0.05019
/*16 */     ff_schro_queue_free(&p_schro_params->enc_frame_queue,       // (1) 0.09653
/*18 */                         libschroedinger_free_frame);            // (0) 0.1274
/*24 */     /* Free the encoder buffer. */                              // (10) 0.04247
/*26 */     if (p_schro_params->enc_buf_size)                           // (6) 0.0695
/*28 */         av_freep(&p_schro_params->enc_buf);                     // (3) 0.0888
/*32 */     /* Free the video format structure. */                      // (9) 0.04247
/*34 */     av_freep(&p_schro_params->format);                          // (7) 0.06564
/*38 */     return 0;                                                   // (12) 0.02317
/*40 */ }                                                               // (14) 0.003861
