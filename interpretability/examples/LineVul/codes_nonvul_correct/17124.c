// commit message FFmpeg@28f9ab7029 (target=0, prob=0.0743611, correct=True): vp3: move idct and loop filter pointers to new vp3dsp context
/*0   */ static void dsputil_init_mmx2(DSPContext *c, AVCodecContext *avctx,           // (11) 0.05273
/*2   */                               int mm_flags)                                   // (4) 0.06641
/*4   */ {                                                                             // (17) 0.001953
/*6   */     const int bit_depth      = avctx->bits_per_raw_sample;                    // (12) 0.04883
/*8   */     const int high_bit_depth = bit_depth > 8;                                 // (13) 0.0332
/*12  */     c->prefetch = prefetch_mmx2;                                              // (14) 0.03125
/*16  */     if (!high_bit_depth) {                                                    // (15) 0.02344
/*18  */         c->put_pixels_tab[0][1] = put_pixels16_x2_mmx2;                       // (5) 0.06641
/*20  */         c->put_pixels_tab[0][2] = put_pixels16_y2_mmx2;                       // (6) 0.06641
/*24  */         c->avg_pixels_tab[0][0] = avg_pixels16_mmx2;                          // (9) 0.0625
/*26  */         c->avg_pixels_tab[0][1] = avg_pixels16_x2_mmx2;                       // (0) 0.06836
/*28  */         c->avg_pixels_tab[0][2] = avg_pixels16_y2_mmx2;                       // (1) 0.06836
/*32  */         c->put_pixels_tab[1][1] = put_pixels8_x2_mmx2;                        // (7) 0.06641
/*34  */         c->put_pixels_tab[1][2] = put_pixels8_y2_mmx2;                        // (8) 0.06641
/*38  */         c->avg_pixels_tab[1][0] = avg_pixels8_mmx2;                           // (10) 0.0625
/*40  */         c->avg_pixels_tab[1][1] = avg_pixels8_x2_mmx2;                        // (2) 0.06836
/*42  */         c->avg_pixels_tab[1][2] = avg_pixels8_y2_mmx2;                        // (3) 0.06836
/*44  */     }                                                                         // (16) 0.007813
/*48  */     if (!(avctx->flags & CODEC_FLAG_BITEXACT)) {                              // 0.0
/*50  */         if (!high_bit_depth) {                                                // 0.0
/*52  */             c->put_no_rnd_pixels_tab[0][1] = put_no_rnd_pixels16_x2_mmx2;     // 0.0
/*54  */             c->put_no_rnd_pixels_tab[0][2] = put_no_rnd_pixels16_y2_mmx2;     // 0.0
/*56  */             c->put_no_rnd_pixels_tab[1][1] = put_no_rnd_pixels8_x2_mmx2;      // 0.0
/*58  */             c->put_no_rnd_pixels_tab[1][2] = put_no_rnd_pixels8_y2_mmx2;      // 0.0
/*62  */             c->avg_pixels_tab[0][3] = avg_pixels16_xy2_mmx2;                  // 0.0
/*64  */             c->avg_pixels_tab[1][3] = avg_pixels8_xy2_mmx2;                   // 0.0
/*66  */         }                                                                     // 0.0
/*70  */         if (CONFIG_VP3_DECODER && HAVE_YASM) {                                // 0.0
/*72  */             c->vp3_v_loop_filter = ff_vp3_v_loop_filter_mmx2;                 // 0.0
/*74  */             c->vp3_h_loop_filter = ff_vp3_h_loop_filter_mmx2;                 // 0.0
/*76  */         }                                                                     // 0.0
/*78  */     }                                                                         // 0.0
/*80  */     if (CONFIG_VP3_DECODER && HAVE_YASM)                                      // 0.0
/*82  */         c->vp3_idct_dc_add = ff_vp3_idct_dc_add_mmx2;                         // 0.0
/*86  */     if (CONFIG_VP3_DECODER && (avctx->codec_id == CODEC_ID_VP3 ||             // 0.0
/*88  */                                avctx->codec_id == CODEC_ID_THEORA)) {         // 0.0
/*90  */         c->put_no_rnd_pixels_tab[1][1] = put_no_rnd_pixels8_x2_exact_mmx2;    // 0.0
/*92  */         c->put_no_rnd_pixels_tab[1][2] = put_no_rnd_pixels8_y2_exact_mmx2;    // 0.0
/*94  */     }                                                                         // 0.0
/*98  */     if (CONFIG_H264QPEL) {                                                    // 0.0
/*100 */         SET_QPEL_FUNCS(put_qpel,        0, 16, mmx2, );                       // 0.0
/*102 */         SET_QPEL_FUNCS(put_qpel,        1,  8, mmx2, );                       // 0.0
/*104 */         SET_QPEL_FUNCS(put_no_rnd_qpel, 0, 16, mmx2, );                       // 0.0
/*106 */         SET_QPEL_FUNCS(put_no_rnd_qpel, 1,  8, mmx2, );                       // 0.0
/*108 */         SET_QPEL_FUNCS(avg_qpel,        0, 16, mmx2, );                       // 0.0
/*110 */         SET_QPEL_FUNCS(avg_qpel,        1,  8, mmx2, );                       // 0.0
/*114 */         if (!high_bit_depth) {                                                // 0.0
/*116 */             SET_QPEL_FUNCS(put_h264_qpel, 0, 16, mmx2, );                     // 0.0
/*118 */             SET_QPEL_FUNCS(put_h264_qpel, 1,  8, mmx2, );                     // 0.0
/*120 */             SET_QPEL_FUNCS(put_h264_qpel, 2,  4, mmx2, );                     // 0.0
/*122 */             SET_QPEL_FUNCS(avg_h264_qpel, 0, 16, mmx2, );                     // 0.0
/*124 */             SET_QPEL_FUNCS(avg_h264_qpel, 1,  8, mmx2, );                     // 0.0
/*126 */             SET_QPEL_FUNCS(avg_h264_qpel, 2,  4, mmx2, );                     // 0.0
/*128 */         } else if (bit_depth == 10) {                                         // 0.0
/*130 */ #if HAVE_YASM                                                                 // 0.0
/*132 */ #if !ARCH_X86_64                                                              // 0.0
/*134 */             SET_QPEL_FUNCS(avg_h264_qpel, 0, 16, 10_mmxext, ff_);             // 0.0
/*136 */             SET_QPEL_FUNCS(put_h264_qpel, 0, 16, 10_mmxext, ff_);             // 0.0
/*138 */             SET_QPEL_FUNCS(put_h264_qpel, 1,  8, 10_mmxext, ff_);             // 0.0
/*140 */             SET_QPEL_FUNCS(avg_h264_qpel, 1,  8, 10_mmxext, ff_);             // 0.0
/*142 */ #endif                                                                        // 0.0
/*144 */             SET_QPEL_FUNCS(put_h264_qpel, 2, 4,  10_mmxext, ff_);             // 0.0
/*146 */             SET_QPEL_FUNCS(avg_h264_qpel, 2, 4,  10_mmxext, ff_);             // 0.0
/*148 */ #endif                                                                        // 0.0
/*150 */         }                                                                     // 0.0
/*154 */         SET_QPEL_FUNCS(put_2tap_qpel, 0, 16, mmx2, );                         // 0.0
/*156 */         SET_QPEL_FUNCS(put_2tap_qpel, 1,  8, mmx2, );                         // 0.0
/*158 */         SET_QPEL_FUNCS(avg_2tap_qpel, 0, 16, mmx2, );                         // 0.0
/*160 */         SET_QPEL_FUNCS(avg_2tap_qpel, 1,  8, mmx2, );                         // 0.0
/*162 */     }                                                                         // 0.0
/*166 */ #if HAVE_YASM                                                                 // 0.0
/*168 */     if (!high_bit_depth && CONFIG_H264CHROMA) {                               // 0.0
/*170 */         c->avg_h264_chroma_pixels_tab[0] = ff_avg_h264_chroma_mc8_mmx2_rnd;   // 0.0
/*172 */         c->avg_h264_chroma_pixels_tab[1] = ff_avg_h264_chroma_mc4_mmx2;       // 0.0
/*174 */         c->avg_h264_chroma_pixels_tab[2] = ff_avg_h264_chroma_mc2_mmx2;       // 0.0
/*176 */         c->put_h264_chroma_pixels_tab[2] = ff_put_h264_chroma_mc2_mmx2;       // 0.0
/*178 */     }                                                                         // 0.0
/*180 */     if (bit_depth == 10 && CONFIG_H264CHROMA) {                               // 0.0
/*182 */         c->put_h264_chroma_pixels_tab[2] = ff_put_h264_chroma_mc2_10_mmxext;  // 0.0
/*184 */         c->avg_h264_chroma_pixels_tab[2] = ff_avg_h264_chroma_mc2_10_mmxext;  // 0.0
/*186 */         c->put_h264_chroma_pixels_tab[1] = ff_put_h264_chroma_mc4_10_mmxext;  // 0.0
/*188 */         c->avg_h264_chroma_pixels_tab[1] = ff_avg_h264_chroma_mc4_10_mmxext;  // 0.0
/*190 */     }                                                                         // 0.0
/*194 */     c->add_hfyu_median_prediction   = ff_add_hfyu_median_prediction_mmx2;     // 0.0
/*198 */     c->scalarproduct_int16          = ff_scalarproduct_int16_mmx2;            // 0.0
/*200 */     c->scalarproduct_and_madd_int16 = ff_scalarproduct_and_madd_int16_mmx2;   // 0.0
/*204 */     if (avctx->flags & CODEC_FLAG_BITEXACT) {                                 // 0.0
/*206 */         c->apply_window_int16 = ff_apply_window_int16_mmxext_ba;              // 0.0
/*208 */     } else {                                                                  // 0.0
/*210 */         c->apply_window_int16 = ff_apply_window_int16_mmxext;                 // 0.0
/*212 */     }                                                                         // 0.0
/*214 */ #endif                                                                        // 0.0
/*216 */ }                                                                             // 0.0
