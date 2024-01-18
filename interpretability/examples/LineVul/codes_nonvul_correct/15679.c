// commit message FFmpeg@17dc7c7a60 (target=0, prob=0.014278297, correct=True): Fix h264/vp8 intra pred on Athlon XP Whose idea was it to have a CPU that didn't SIGILL on an invalid instruction?
/*0   */ void ff_h264_pred_init_x86(H264PredContext *h, int codec_id)               // (9) 0.04883
/*2   */ {                                                                          // (17) 0.001953
/*4   */     mm_flags = mm_support();                                               // (13) 0.02148
/*8   */ #if HAVE_YASM                                                              // (15) 0.01367
/*10  */     if (mm_flags & FF_MM_MMX) {                                            // (12) 0.0332
/*12  */         h->pred16x16[VERT_PRED8x8] = ff_pred16x16_vertical_mmx;            // (8) 0.07031
/*14  */         h->pred16x16[HOR_PRED8x8 ] = ff_pred16x16_horizontal_mmx;          // (6) 0.07227
/*16  */         h->pred8x8  [VERT_PRED8x8] = ff_pred8x8_vertical_mmx;              // (7) 0.07227
/*18  */         h->pred8x8  [HOR_PRED8x8 ] = ff_pred8x8_horizontal_mmx;            // (4) 0.07422
/*20  */         if (codec_id == CODEC_ID_VP8) {                                    // (10) 0.04688
/*22  */             h->pred16x16[PLANE_PRED8x8] = ff_pred16x16_tm_vp8_mmx;         // (2) 0.08398
/*24  */             h->pred8x8  [PLANE_PRED8x8] = ff_pred8x8_tm_vp8_mmx;           // (0) 0.08594
/*26  */             h->pred4x4  [TM_VP8_PRED  ] = ff_pred4x4_tm_vp8_mmx;           // (1) 0.08594
/*28  */         }                                                                  // (14) 0.01562
/*30  */     }                                                                      // (16) 0.007812
/*34  */     if (mm_flags & FF_MM_MMX2) {                                           // (11) 0.03516
/*36  */         h->pred16x16[HOR_PRED8x8 ] = ff_pred16x16_horizontal_mmxext;       // (3) 0.07422
/*38  */         h->pred16x16[DC_PRED8x8  ] = ff_pred16x16_dc_mmxext;               // (5) 0.07227
/*40  */         h->pred8x8  [HOR_PRED8x8 ] = ff_pred8x8_horizontal_mmxext;         // 0.0
/*42  */         h->pred4x4  [DC_PRED     ] = ff_pred4x4_dc_mmxext;                 // 0.0
/*44  */         if (codec_id == CODEC_ID_VP8) {                                    // 0.0
/*46  */             h->pred16x16[PLANE_PRED8x8] = ff_pred16x16_tm_vp8_mmxext;      // 0.0
/*48  */             h->pred8x8  [DC_PRED8x8   ] = ff_pred8x8_dc_rv40_mmxext;       // 0.0
/*50  */             h->pred8x8  [PLANE_PRED8x8] = ff_pred8x8_tm_vp8_mmxext;        // 0.0
/*52  */             h->pred4x4  [TM_VP8_PRED  ] = ff_pred4x4_tm_vp8_mmxext;        // 0.0
/*54  */             h->pred4x4  [VERT_PRED    ] = ff_pred4x4_vertical_vp8_mmxext;  // 0.0
/*56  */         }                                                                  // 0.0
/*58  */     }                                                                      // 0.0
/*62  */     if (mm_flags & FF_MM_SSE) {                                            // 0.0
/*64  */         h->pred16x16[VERT_PRED8x8] = ff_pred16x16_vertical_sse;            // 0.0
/*66  */         h->pred16x16[DC_PRED8x8  ] = ff_pred16x16_dc_sse;                  // 0.0
/*68  */     }                                                                      // 0.0
/*72  */     if (mm_flags & FF_MM_SSE2) {                                           // 0.0
/*74  */         h->pred16x16[DC_PRED8x8  ] = ff_pred16x16_dc_sse2;                 // 0.0
/*76  */         if (codec_id == CODEC_ID_VP8) {                                    // 0.0
/*78  */             h->pred16x16[PLANE_PRED8x8] = ff_pred16x16_tm_vp8_sse2;        // 0.0
/*80  */             h->pred8x8  [PLANE_PRED8x8] = ff_pred8x8_tm_vp8_sse2;          // 0.0
/*82  */         }                                                                  // 0.0
/*84  */     }                                                                      // 0.0
/*88  */     if (mm_flags & FF_MM_SSSE3) {                                          // 0.0
/*90  */         h->pred16x16[HOR_PRED8x8 ] = ff_pred16x16_horizontal_ssse3;        // 0.0
/*92  */         h->pred16x16[DC_PRED8x8  ] = ff_pred16x16_dc_ssse3;                // 0.0
/*94  */         h->pred8x8  [HOR_PRED8x8 ] = ff_pred8x8_horizontal_ssse3;          // 0.0
/*96  */         if (codec_id == CODEC_ID_VP8) {                                    // 0.0
/*98  */             h->pred8x8  [PLANE_PRED8x8] = ff_pred8x8_tm_vp8_ssse3;         // 0.0
/*100 */             h->pred4x4  [TM_VP8_PRED  ] = ff_pred4x4_tm_vp8_ssse3;         // 0.0
/*102 */         }                                                                  // 0.0
/*104 */     }                                                                      // 0.0
/*106 */ #endif                                                                     // 0.0
/*108 */ }                                                                          // 0.0
