// commit message FFmpeg@2005fddcbb (target=0, prob=0.27831754, correct=True): h264/ff_h264_check_intra_pred_mode: fix input value check
/*0  */ int ff_h264_check_intra_pred_mode(H264Context *h, int mode, int is_chroma)        // (4) 0.05859
/*2  */ {                                                                                 // (22) 0.001953
/*4  */     static const int8_t top[7]  = { LEFT_DC_PRED8x8, 1, -1, -1 };                 // (1) 0.06836
/*6  */     static const int8_t left[7] = { TOP_DC_PRED8x8, -1, 2, -1, DC_128_PRED8x8 };  // (0) 0.08398
/*10 */     if (mode > 6U) {                                                              // (17) 0.02148
/*12 */         av_log(h->avctx, AV_LOG_ERROR,                                            // (11) 0.04297
/*14 */                "out of range intra chroma pred mode at %d %d\n",                  // (3) 0.06055
/*16 */                h->mb_x, h->mb_y);                                                 // (8) 0.05078
/*18 */         return -1;                                                                // (18) 0.02148
/*20 */     }                                                                             // (20) 0.007812
/*24 */     if (!(h->top_samples_available & 0x8000)) {                                   // (12) 0.03906
/*26 */         mode = top[mode];                                                         // (15) 0.02539
/*28 */         if (mode < 0) {                                                           // (14) 0.02734
/*30 */             av_log(h->avctx, AV_LOG_ERROR,                                        // (9) 0.05078
/*32 */                    "top block unavailable for requested intra mode at %d %d\n",   // (2) 0.06641
/*34 */                    h->mb_x, h->mb_y);                                             // (6) 0.05859
/*36 */             return -1;                                                            // (13) 0.0293
/*38 */         }                                                                         // (19) 0.01562
/*40 */     }                                                                             // (21) 0.007812
/*44 */     if ((h->left_samples_available & 0x8080) != 0x8080) {                         // (10) 0.05078
/*46 */         mode = left[mode];                                                        // (16) 0.02539
/*48 */         if (is_chroma && (h->left_samples_available & 0x8080)) {                  // (5) 0.05859
/*50 */             // mad cow disease mode, aka MBAFF + constrained_intra_pred           // (7) 0.05273
/*52 */             mode = ALZHEIMER_DC_L0T_PRED8x8 +                                     // 0.0
/*54 */                    (!(h->left_samples_available & 0x8000)) +                      // 0.0
/*56 */                    2 * (mode == DC_128_PRED8x8);                                  // 0.0
/*58 */         }                                                                         // 0.0
/*60 */         if (mode < 0) {                                                           // 0.0
/*62 */             av_log(h->avctx, AV_LOG_ERROR,                                        // 0.0
/*64 */                    "left block unavailable for requested intra mode at %d %d\n",  // 0.0
/*66 */                    h->mb_x, h->mb_y);                                             // 0.0
/*68 */             return -1;                                                            // 0.0
/*70 */         }                                                                         // 0.0
/*72 */     }                                                                             // 0.0
/*76 */     return mode;                                                                  // 0.0
/*78 */ }                                                                                 // 0.0
