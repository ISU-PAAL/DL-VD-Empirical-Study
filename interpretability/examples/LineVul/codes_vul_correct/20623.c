// commit message FFmpeg@220b24c7c9 (target=1, prob=0.9788674, correct=True): lavc: remove libschroedinger encoding and decoding wrappers
/*0  */ static int set_chroma_format(AVCodecContext *avctx)                      // (9) 0.0462
/*2  */ {                                                                        // (16) 0.002717
/*4  */     int num_formats = sizeof(schro_pixel_format_map) /                   // (8) 0.05707
/*6  */                       sizeof(schro_pixel_format_map[0]);                 // (2) 0.09239
/*8  */     int idx;                                                             // (13) 0.01902
/*12 */     SchroEncoderParams *p_schro_params = avctx->priv_data;               // (5) 0.0625
/*16 */     for (idx = 0; idx < num_formats; ++idx) {                            // (6) 0.0625
/*18 */         if (schro_pixel_format_map[idx].ff_pix_fmt == avctx->pix_fmt) {  // (1) 0.106
/*20 */             p_schro_params->format->chroma_format =                      // (4) 0.06793
/*22 */                             schro_pixel_format_map[idx].schro_pix_fmt;   // (0) 0.1304
/*24 */             return 0;                                                    // (11) 0.03804
/*26 */         }                                                                // (12) 0.02174
/*28 */     }                                                                    // (15) 0.01087
/*32 */     av_log(avctx, AV_LOG_ERROR,                                          // (10) 0.04348
/*34 */            "This codec currently only supports planar YUV 4:2:0, 4:2:2"  // (3) 0.08696
/*36 */            " and 4:4:4 formats.\n");                                     // (7) 0.05978
/*40 */     return -1;                                                           // (14) 0.01902
/*42 */ }                                                                        // (17) 0.002717
