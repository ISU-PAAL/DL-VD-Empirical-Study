// commit message FFmpeg@70d54392f5 (target=0, prob=0.18500696, correct=True): lowres2 support.
/*0   */ void ff_dsputil_init_alpha(DSPContext* c, AVCodecContext *avctx)       // (13) 0.04883
/*2   */ {                                                                      // (16) 0.001953
/*4   */     const int high_bit_depth = avctx->bits_per_raw_sample > 8;         // (14) 0.04688
/*8   */     if (!high_bit_depth) {                                             // (15) 0.02344
/*10  */     c->put_pixels_tab[0][0] = put_pixels16_axp_asm;                    // (11) 0.05469
/*12  */     c->put_pixels_tab[0][1] = put_pixels16_x2_axp;                     // (8) 0.05664
/*14  */     c->put_pixels_tab[0][2] = put_pixels16_y2_axp;                     // (9) 0.05664
/*16  */     c->put_pixels_tab[0][3] = put_pixels16_xy2_axp;                    // (10) 0.05664
/*20  */     c->put_no_rnd_pixels_tab[0][0] = put_pixels16_axp_asm;             // (4) 0.06445
/*22  */     c->put_no_rnd_pixels_tab[0][1] = put_no_rnd_pixels16_x2_axp;       // (1) 0.07617
/*24  */     c->put_no_rnd_pixels_tab[0][2] = put_no_rnd_pixels16_y2_axp;       // (0) 0.07617
/*26  */     c->put_no_rnd_pixels_tab[0][3] = put_no_rnd_pixels16_xy2_axp;      // (2) 0.07617
/*30  */     c->avg_pixels_tab[0][0] = avg_pixels16_axp;                        // (12) 0.05273
/*32  */     c->avg_pixels_tab[0][1] = avg_pixels16_x2_axp;                     // (5) 0.05859
/*34  */     c->avg_pixels_tab[0][2] = avg_pixels16_y2_axp;                     // (6) 0.05859
/*36  */     c->avg_pixels_tab[0][3] = avg_pixels16_xy2_axp;                    // (7) 0.05859
/*40  */     c->avg_no_rnd_pixels_tab[0][0] = avg_no_rnd_pixels16_axp;          // (3) 0.07227
/*42  */     c->avg_no_rnd_pixels_tab[0][1] = avg_no_rnd_pixels16_x2_axp;       // 0.0
/*44  */     c->avg_no_rnd_pixels_tab[0][2] = avg_no_rnd_pixels16_y2_axp;       // 0.0
/*46  */     c->avg_no_rnd_pixels_tab[0][3] = avg_no_rnd_pixels16_xy2_axp;      // 0.0
/*50  */     c->put_pixels_tab[1][0] = put_pixels_axp_asm;                      // 0.0
/*52  */     c->put_pixels_tab[1][1] = put_pixels_x2_axp;                       // 0.0
/*54  */     c->put_pixels_tab[1][2] = put_pixels_y2_axp;                       // 0.0
/*56  */     c->put_pixels_tab[1][3] = put_pixels_xy2_axp;                      // 0.0
/*60  */     c->put_no_rnd_pixels_tab[1][0] = put_pixels_axp_asm;               // 0.0
/*62  */     c->put_no_rnd_pixels_tab[1][1] = put_no_rnd_pixels_x2_axp;         // 0.0
/*64  */     c->put_no_rnd_pixels_tab[1][2] = put_no_rnd_pixels_y2_axp;         // 0.0
/*66  */     c->put_no_rnd_pixels_tab[1][3] = put_no_rnd_pixels_xy2_axp;        // 0.0
/*70  */     c->avg_pixels_tab[1][0] = avg_pixels_axp;                          // 0.0
/*72  */     c->avg_pixels_tab[1][1] = avg_pixels_x2_axp;                       // 0.0
/*74  */     c->avg_pixels_tab[1][2] = avg_pixels_y2_axp;                       // 0.0
/*76  */     c->avg_pixels_tab[1][3] = avg_pixels_xy2_axp;                      // 0.0
/*80  */     c->avg_no_rnd_pixels_tab[1][0] = avg_no_rnd_pixels_axp;            // 0.0
/*82  */     c->avg_no_rnd_pixels_tab[1][1] = avg_no_rnd_pixels_x2_axp;         // 0.0
/*84  */     c->avg_no_rnd_pixels_tab[1][2] = avg_no_rnd_pixels_y2_axp;         // 0.0
/*86  */     c->avg_no_rnd_pixels_tab[1][3] = avg_no_rnd_pixels_xy2_axp;        // 0.0
/*90  */     c->clear_blocks = clear_blocks_axp;                                // 0.0
/*92  */     }                                                                  // 0.0
/*96  */     /* amask clears all bits that correspond to present features.  */  // 0.0
/*98  */     if (amask(AMASK_MVI) == 0) {                                       // 0.0
/*100 */         c->put_pixels_clamped = put_pixels_clamped_mvi_asm;            // 0.0
/*102 */         c->add_pixels_clamped = add_pixels_clamped_mvi_asm;            // 0.0
/*106 */         if (!high_bit_depth)                                           // 0.0
/*108 */             c->get_pixels   = get_pixels_mvi;                          // 0.0
/*110 */         c->diff_pixels      = diff_pixels_mvi;                         // 0.0
/*112 */         c->sad[0]           = pix_abs16x16_mvi_asm;                    // 0.0
/*114 */         c->sad[1]           = pix_abs8x8_mvi;                          // 0.0
/*116 */         c->pix_abs[0][0]    = pix_abs16x16_mvi_asm;                    // 0.0
/*118 */         c->pix_abs[1][0]    = pix_abs8x8_mvi;                          // 0.0
/*120 */         c->pix_abs[0][1]    = pix_abs16x16_x2_mvi;                     // 0.0
/*122 */         c->pix_abs[0][2]    = pix_abs16x16_y2_mvi;                     // 0.0
/*124 */         c->pix_abs[0][3]    = pix_abs16x16_xy2_mvi;                    // 0.0
/*126 */     }                                                                  // 0.0
/*130 */     put_pixels_clamped_axp_p = c->put_pixels_clamped;                  // 0.0
/*132 */     add_pixels_clamped_axp_p = c->add_pixels_clamped;                  // 0.0
/*136 */     if (avctx->bits_per_raw_sample <= 8 &&                             // 0.0
/*138 */         (avctx->idct_algo == FF_IDCT_AUTO ||                           // 0.0
/*140 */          avctx->idct_algo == FF_IDCT_SIMPLEALPHA)) {                   // 0.0
/*142 */         c->idct_put = ff_simple_idct_put_axp;                          // 0.0
/*144 */         c->idct_add = ff_simple_idct_add_axp;                          // 0.0
/*146 */         c->idct =     ff_simple_idct_axp;                              // 0.0
/*148 */     }                                                                  // 0.0
/*150 */ }                                                                      // 0.0
