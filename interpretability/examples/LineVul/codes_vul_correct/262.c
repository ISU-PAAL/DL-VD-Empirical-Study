// commit message FFmpeg@964f07f68e (target=1, prob=0.9990613, correct=True): hevc: Fix memory leak related to a53_caption data
/*0  */ static av_cold int hevc_init_context(AVCodecContext *avctx)  // (6) 0.04073
/*1  */ {                                                            // (32) 0.002037
/*2  */     HEVCContext *s = avctx->priv_data;                       // (10) 0.03259
/*3  */     int i;                                                   // (28) 0.01222
/*4  */     s->avctx = avctx;                                        // (20) 0.0224
/*5  */     s->HEVClc = av_mallocz(sizeof(HEVCLocalContext));        // (2) 0.05092
/*6  */     if (!s->HEVClc)                                          // (18) 0.02444
/*7  */         goto fail;                                           // (23) 0.02037
/*8  */     s->HEVClcList[0] = s->HEVClc;                            // (5) 0.04277
/*9  */     s->sList[0] = s;                                         // (14) 0.02648
/*10 */     s->cabac_state = av_malloc(HEVC_CONTEXTS);               // (3) 0.04684
/*11 */     if (!s->cabac_state)                                     // (15) 0.02648
/*12 */         goto fail;                                           // (24) 0.02037
/*13 */     s->output_frame = av_frame_alloc();                      // (11) 0.03055
/*14 */     if (!s->output_frame)                                    // (21) 0.0224
/*15 */         goto fail;                                           // (25) 0.02037
/*16 */     for (i = 0; i < FF_ARRAY_ELEMS(s->DPB); i++) {           // (0) 0.05703
/*17 */         s->DPB[i].frame = av_frame_alloc();                  // (4) 0.04481
/*18 */         if (!s->DPB[i].frame)                                // (8) 0.03666
/*19 */             goto fail;                                       // (13) 0.02851
/*20 */         s->DPB[i].tf.f = s->DPB[i].frame;                    // (1) 0.05499
/*21 */     }                                                        // (30) 0.008147
/*22 */     s->max_ra = INT_MAX;                                     // (16) 0.02648
/*23 */     s->md5_ctx = av_md5_alloc();                             // (9) 0.03462
/*24 */     if (!s->md5_ctx)                                         // (19) 0.02444
/*25 */         goto fail;                                           // (26) 0.02037
/*26 */     ff_bswapdsp_init(&s->bdsp);                              // (7) 0.03666
/*27 */     s->context_initialized = 1;                              // (22) 0.0224
/*28 */     s->eos = 0;                                              // (27) 0.02037
/*29 */     return 0;                                                // (29) 0.01222
/*30 */ fail:                                                        // (31) 0.004073
/*31 */     hevc_decode_free(avctx);                                 // (12) 0.02851
/*32 */     return AVERROR(ENOMEM);                                  // (17) 0.02444
/*33 */ }                                                            // (33) 0.002037
