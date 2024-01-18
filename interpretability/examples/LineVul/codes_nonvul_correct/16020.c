// commit message FFmpeg@332f9ac4e3 (target=0, prob=0.32716754, correct=True): h263 loop filter fixed h263 modified quantization CODEC_FLAG_OBMC
/*0   */ int intel_h263_decode_picture_header(MpegEncContext *s)                              // (9) 0.03906
/*2   */ {                                                                                    // (29) 0.001953
/*4   */     int format;                                                                      // (23) 0.01172
/*8   */     /* picture header */                                                             // (22) 0.01367
/*10  */     if (get_bits_long(&s->gb, 22) != 0x20) {                                         // (5) 0.04492
/*12  */         av_log(s->avctx, AV_LOG_ERROR, "Bad picture start code\n");                  // (1) 0.05859
/*14  */         return -1;                                                                   // (19) 0.02148
/*16  */     }                                                                                // (25) 0.007812
/*18  */     s->picture_number = get_bits(&s->gb, 8); /* picture timestamp */                 // (4) 0.04492
/*22  */     if (get_bits1(&s->gb) != 1) {                                                    // (12) 0.03516
/*24  */         av_log(s->avctx, AV_LOG_ERROR, "Bad marker\n");                              // (3) 0.05469
/*26  */         return -1;	/* marker */                                                      // (17) 0.0293
/*28  */     }                                                                                // (26) 0.007812
/*30  */     if (get_bits1(&s->gb) != 0) {                                                    // (13) 0.03516
/*32  */         av_log(s->avctx, AV_LOG_ERROR, "Bad H263 id\n");                             // (2) 0.05859
/*34  */         return -1;	/* h263 id */                                                     // (15) 0.0332
/*36  */     }                                                                                // (27) 0.007812
/*38  */     skip_bits1(&s->gb);	/* split screen off */                                       // (14) 0.03516
/*40  */     skip_bits1(&s->gb);	/* camera  off */                                            // (11) 0.03516
/*42  */     skip_bits1(&s->gb);	/* freeze picture release off */                             // (10) 0.03711
/*46  */     format = get_bits(&s->gb, 3);                                                    // (16) 0.0293
/*48  */     if (format != 7) {                                                               // (21) 0.01953
/*50  */         av_log(s->avctx, AV_LOG_ERROR, "Intel H263 free format not supported\n");    // (0) 0.06445
/*52  */         return -1;                                                                   // (20) 0.02148
/*54  */     }                                                                                // (28) 0.007812
/*56  */     s->h263_plus = 0;                                                                // (18) 0.02344
/*60  */     s->pict_type = I_TYPE + get_bits1(&s->gb);                                       // (6) 0.04297
/*62  */                                                                                      // (24) 0.007813
/*64  */     s->unrestricted_mv = get_bits1(&s->gb);                                          // (8) 0.04102
/*66  */     s->h263_long_vectors = s->unrestricted_mv;                                       // (7) 0.04102
/*70  */     if (get_bits1(&s->gb) != 0) {                                                    // 0.0
/*72  */         av_log(s->avctx, AV_LOG_ERROR, "SAC not supported\n");                       // 0.0
/*74  */         return -1;	/* SAC: off */                                                    // 0.0
/*76  */     }                                                                                // 0.0
/*78  */     if (get_bits1(&s->gb) != 0) {                                                    // 0.0
/*80  */         s->obmc= 1;                                                                  // 0.0
/*82  */         av_log(s->avctx, AV_LOG_ERROR, "Advanced Prediction Mode not supported\n");  // 0.0
/*84  */ //        return -1;	/* advanced prediction mode: off */                             // 0.0
/*86  */     }                                                                                // 0.0
/*88  */     if (get_bits1(&s->gb) != 0) {                                                    // 0.0
/*90  */         av_log(s->avctx, AV_LOG_ERROR, "PB frame mode no supported\n");              // 0.0
/*92  */         return -1;	/* PB frame mode */                                               // 0.0
/*94  */     }                                                                                // 0.0
/*98  */     /* skip unknown header garbage */                                                // 0.0
/*100 */     skip_bits(&s->gb, 41);                                                           // 0.0
/*104 */     s->qscale = get_bits(&s->gb, 5);                                                 // 0.0
/*106 */     skip_bits1(&s->gb);	/* Continuous Presence Multipoint mode: off */               // 0.0
/*110 */     /* PEI */                                                                        // 0.0
/*112 */     while (get_bits1(&s->gb) != 0) {                                                 // 0.0
/*114 */         skip_bits(&s->gb, 8);                                                        // 0.0
/*116 */     }                                                                                // 0.0
/*118 */     s->f_code = 1;                                                                   // 0.0
/*122 */     s->y_dc_scale_table=                                                             // 0.0
/*124 */     s->c_dc_scale_table= ff_mpeg1_dc_scale_table;                                    // 0.0
/*128 */     return 0;                                                                        // 0.0
/*130 */ }                                                                                    // 0.0
