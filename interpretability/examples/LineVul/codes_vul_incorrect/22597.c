// commit message FFmpeg@b791a0831b (target=1, prob=0.050255537, correct=False): avcodec/x86/dsputil_init: only use xvid idct for lowres=0
/*0  */ static av_cold void dsputil_init_sse2(DSPContext *c, AVCodecContext *avctx,  // (8) 0.05859
/*2  */                                       int mm_flags)                          // (0) 0.08203
/*4  */ {                                                                            // (19) 0.001953
/*6  */ #if HAVE_SSE2_INLINE                                                         // (15) 0.01953
/*8  */     const int high_bit_depth = avctx->bits_per_raw_sample > 8;               // (11) 0.04688
/*12 */     if (!high_bit_depth && avctx->idct_algo == FF_IDCT_XVIDMMX) {            // (6) 0.06055
/*14 */         c->idct_put              = ff_idct_xvid_sse2_put;                    // (1) 0.08008
/*16 */         c->idct_add              = ff_idct_xvid_sse2_add;                    // (2) 0.08008
/*18 */         c->idct                  = ff_idct_xvid_sse2;                        // (3) 0.08008
/*20 */         c->idct_permutation_type = FF_SSE2_IDCT_PERM;                        // (9) 0.05664
/*22 */     }                                                                        // (17) 0.007812
/*24 */ #endif /* HAVE_SSE2_INLINE */                                                // (13) 0.02344
/*28 */ #if HAVE_SSE2_EXTERNAL                                                       // (14) 0.02148
/*30 */     c->scalarproduct_int16          = ff_scalarproduct_int16_sse2;           // (5) 0.07031
/*32 */     c->scalarproduct_and_madd_int16 = ff_scalarproduct_and_madd_int16_sse2;  // (4) 0.07227
/*34 */     if (mm_flags & AV_CPU_FLAG_ATOM) {                                       // (12) 0.03711
/*36 */         c->vector_clip_int32 = ff_vector_clip_int32_int_sse2;                // (7) 0.06055
/*38 */     } else {                                                                 // (16) 0.01172
/*40 */         c->vector_clip_int32 = ff_vector_clip_int32_sse2;                    // (10) 0.05664
/*42 */     }                                                                        // (18) 0.007812
/*44 */     if (avctx->flags & CODEC_FLAG_BITEXACT) {                                // 0.0
/*46 */         c->apply_window_int16 = ff_apply_window_int16_sse2;                  // 0.0
/*48 */     } else if (!(mm_flags & AV_CPU_FLAG_SSE2SLOW)) {                         // 0.0
/*50 */         c->apply_window_int16 = ff_apply_window_int16_round_sse2;            // 0.0
/*52 */     }                                                                        // 0.0
/*54 */     c->bswap_buf = ff_bswap32_buf_sse2;                                      // 0.0
/*56 */ #endif /* HAVE_SSE2_EXTERNAL */                                              // 0.0
/*58 */ }                                                                            // 0.0
