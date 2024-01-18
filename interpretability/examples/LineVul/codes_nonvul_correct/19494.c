// commit message FFmpeg@3594554a06 (target=0, prob=0.14264111, correct=True): sparc: dsputil: Simplify high_bit_depth checks
/*0   */ av_cold void ff_dsputil_init_vis(DSPContext *c, AVCodecContext *avctx)  // (8) 0.05469
/*2   */ {                                                                       // (20) 0.001953
/*4   */   /* VIS-specific optimizations */                                      // (18) 0.01367
/*6   */   int accel = vis_level ();                                             // (17) 0.01758
/*8   */   const int high_bit_depth = avctx->bits_per_raw_sample > 8;            // (13) 0.04297
/*12  */   if (accel & ACCEL_SPARC_VIS) {                                        // (15) 0.0293
/*14  */       if (avctx->bits_per_raw_sample <= 8 &&                            // (14) 0.03906
/*16  */           avctx->idct_algo == FF_IDCT_SIMPLEVIS) {                      // (9) 0.05469
/*18  */           c->idct_put = ff_simple_idct_put_vis;                         // (10) 0.05273
/*20  */           c->idct_add = ff_simple_idct_add_vis;                         // (11) 0.05273
/*22  */           c->idct     = ff_simple_idct_vis;                             // (12) 0.05273
/*24  */           c->idct_permutation_type = FF_TRANSPOSE_IDCT_PERM;            // (0) 0.0625
/*26  */       }                                                                 // (19) 0.01172
/*30  */       if (!high_bit_depth) {                                            // (16) 0.02734
/*32  */       c->put_pixels_tab[0][0] = MC_put_o_16_vis;                        // (1) 0.05664
/*34  */       c->put_pixels_tab[0][1] = MC_put_x_16_vis;                        // (2) 0.05664
/*36  */       c->put_pixels_tab[0][2] = MC_put_y_16_vis;                        // (3) 0.05664
/*38  */       c->put_pixels_tab[0][3] = MC_put_xy_16_vis;                       // (4) 0.05664
/*42  */       c->put_pixels_tab[1][0] = MC_put_o_8_vis;                         // (5) 0.05664
/*44  */       c->put_pixels_tab[1][1] = MC_put_x_8_vis;                         // (6) 0.05664
/*46  */       c->put_pixels_tab[1][2] = MC_put_y_8_vis;                         // (7) 0.05664
/*48  */       c->put_pixels_tab[1][3] = MC_put_xy_8_vis;                        // 0.0
/*52  */       c->avg_pixels_tab[0][0] = MC_avg_o_16_vis;                        // 0.0
/*54  */       c->avg_pixels_tab[0][1] = MC_avg_x_16_vis;                        // 0.0
/*56  */       c->avg_pixels_tab[0][2] = MC_avg_y_16_vis;                        // 0.0
/*58  */       c->avg_pixels_tab[0][3] = MC_avg_xy_16_vis;                       // 0.0
/*62  */       c->avg_pixels_tab[1][0] = MC_avg_o_8_vis;                         // 0.0
/*64  */       c->avg_pixels_tab[1][1] = MC_avg_x_8_vis;                         // 0.0
/*66  */       c->avg_pixels_tab[1][2] = MC_avg_y_8_vis;                         // 0.0
/*68  */       c->avg_pixels_tab[1][3] = MC_avg_xy_8_vis;                        // 0.0
/*72  */       c->put_no_rnd_pixels_tab[0][0] = MC_put_no_round_o_16_vis;        // 0.0
/*74  */       c->put_no_rnd_pixels_tab[0][1] = MC_put_no_round_x_16_vis;        // 0.0
/*76  */       c->put_no_rnd_pixels_tab[0][2] = MC_put_no_round_y_16_vis;        // 0.0
/*78  */       c->put_no_rnd_pixels_tab[0][3] = MC_put_no_round_xy_16_vis;       // 0.0
/*82  */       c->put_no_rnd_pixels_tab[1][0] = MC_put_no_round_o_8_vis;         // 0.0
/*84  */       c->put_no_rnd_pixels_tab[1][1] = MC_put_no_round_x_8_vis;         // 0.0
/*86  */       c->put_no_rnd_pixels_tab[1][2] = MC_put_no_round_y_8_vis;         // 0.0
/*88  */       c->put_no_rnd_pixels_tab[1][3] = MC_put_no_round_xy_8_vis;        // 0.0
/*92  */       c->avg_no_rnd_pixels_tab[0] = MC_avg_no_round_o_16_vis;           // 0.0
/*94  */       c->avg_no_rnd_pixels_tab[1] = MC_avg_no_round_x_16_vis;           // 0.0
/*96  */       c->avg_no_rnd_pixels_tab[2] = MC_avg_no_round_y_16_vis;           // 0.0
/*98  */       c->avg_no_rnd_pixels_tab[3] = MC_avg_no_round_xy_16_vis;          // 0.0
/*100 */       }                                                                 // 0.0
/*102 */   }                                                                     // 0.0
/*104 */ }                                                                       // 0.0
