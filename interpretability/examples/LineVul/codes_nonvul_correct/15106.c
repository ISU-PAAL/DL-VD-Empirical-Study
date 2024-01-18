// commit message FFmpeg@99e5a9d1ea (target=0, prob=0.05973605, correct=True): Do not redundantly check for both CONFIG_THEORA_DECODER and CONFIG_VP3_DECODER. The Theora decoder depends on the VP3 decoder.
/*0   */ void dsputil_init_arm(DSPContext* c, AVCodecContext *avctx)                                                      // (8) 0.04688
/*2   */ {                                                                                                                // (24) 0.001953
/*4   */     int idct_algo= avctx->idct_algo;                                                                             // (15) 0.03711
/*8   */     ff_put_pixels_clamped = c->put_pixels_clamped;                                                               // (11) 0.04492
/*10  */     ff_add_pixels_clamped = c->add_pixels_clamped;                                                               // (12) 0.04492
/*14  */     if (avctx->lowres == 0) {                                                                                    // (16) 0.02734
/*16  */         if(idct_algo == FF_IDCT_AUTO){                                                                           // (13) 0.04492
/*18  */ #if   HAVE_IPP                                                                                                   // (20) 0.01367
/*20  */             idct_algo = FF_IDCT_IPP;                                                                             // (9) 0.04688
/*22  */ #elif HAVE_NEON                                                                                                  // (21) 0.01367
/*24  */             idct_algo = FF_IDCT_SIMPLENEON;                                                                      // (6) 0.05273
/*26  */ #elif HAVE_ARMV6                                                                                                 // (18) 0.01562
/*28  */             idct_algo = FF_IDCT_SIMPLEARMV6;                                                                     // (4) 0.05469
/*30  */ #elif HAVE_ARMV5TE                                                                                               // (17) 0.01758
/*32  */             idct_algo = FF_IDCT_SIMPLEARMV5TE;                                                                   // (1) 0.05664
/*34  */ #else                                                                                                            // (22) 0.003906
/*36  */             idct_algo = FF_IDCT_ARM;                                                                             // (10) 0.04688
/*38  */ #endif                                                                                                           // (23) 0.003906
/*40  */         }                                                                                                        // (19) 0.01562
/*44  */         if(idct_algo==FF_IDCT_ARM){                                                                              // (14) 0.04297
/*46  */             c->idct_put= j_rev_dct_ARM_put;                                                                      // (2) 0.05664
/*48  */             c->idct_add= j_rev_dct_ARM_add;                                                                      // (3) 0.05664
/*50  */             c->idct    = j_rev_dct_ARM;                                                                          // (5) 0.05469
/*52  */             c->idct_permutation_type= FF_LIBMPEG2_IDCT_PERM;                                                     // (0) 0.06641
/*54  */         } else if (idct_algo==FF_IDCT_SIMPLEARM){                                                                // (7) 0.05078
/*56  */             c->idct_put= simple_idct_ARM_put;                                                                    // 0.0
/*58  */             c->idct_add= simple_idct_ARM_add;                                                                    // 0.0
/*60  */             c->idct    = simple_idct_ARM;                                                                        // 0.0
/*62  */             c->idct_permutation_type= FF_NO_IDCT_PERM;                                                           // 0.0
/*64  */ #if HAVE_ARMV6                                                                                                   // 0.0
/*66  */         } else if (idct_algo==FF_IDCT_SIMPLEARMV6){                                                              // 0.0
/*68  */             c->idct_put= ff_simple_idct_put_armv6;                                                               // 0.0
/*70  */             c->idct_add= ff_simple_idct_add_armv6;                                                               // 0.0
/*72  */             c->idct    = ff_simple_idct_armv6;                                                                   // 0.0
/*74  */             c->idct_permutation_type= FF_LIBMPEG2_IDCT_PERM;                                                     // 0.0
/*76  */ #endif                                                                                                           // 0.0
/*78  */ #if HAVE_ARMV5TE                                                                                                 // 0.0
/*80  */         } else if (idct_algo==FF_IDCT_SIMPLEARMV5TE){                                                            // 0.0
/*82  */             c->idct_put= simple_idct_put_armv5te;                                                                // 0.0
/*84  */             c->idct_add= simple_idct_add_armv5te;                                                                // 0.0
/*86  */             c->idct    = simple_idct_armv5te;                                                                    // 0.0
/*88  */             c->idct_permutation_type = FF_NO_IDCT_PERM;                                                          // 0.0
/*90  */ #endif                                                                                                           // 0.0
/*92  */ #if HAVE_IPP                                                                                                     // 0.0
/*94  */         } else if (idct_algo==FF_IDCT_IPP){                                                                      // 0.0
/*96  */             c->idct_put= simple_idct_ipp_put;                                                                    // 0.0
/*98  */             c->idct_add= simple_idct_ipp_add;                                                                    // 0.0
/*100 */             c->idct    = simple_idct_ipp;                                                                        // 0.0
/*102 */             c->idct_permutation_type= FF_NO_IDCT_PERM;                                                           // 0.0
/*104 */ #endif                                                                                                           // 0.0
/*106 */ #if HAVE_NEON                                                                                                    // 0.0
/*108 */         } else if (idct_algo==FF_IDCT_SIMPLENEON){                                                               // 0.0
/*110 */             c->idct_put= ff_simple_idct_put_neon;                                                                // 0.0
/*112 */             c->idct_add= ff_simple_idct_add_neon;                                                                // 0.0
/*114 */             c->idct    = ff_simple_idct_neon;                                                                    // 0.0
/*116 */             c->idct_permutation_type = FF_PARTTRANS_IDCT_PERM;                                                   // 0.0
/*118 */         } else if ((CONFIG_VP3_DECODER || CONFIG_VP5_DECODER || CONFIG_VP6_DECODER || CONFIG_THEORA_DECODER) &&  // 0.0
/*120 */                    idct_algo==FF_IDCT_VP3){                                                                      // 0.0
/*122 */             c->idct_put= ff_vp3_idct_put_neon;                                                                   // 0.0
/*124 */             c->idct_add= ff_vp3_idct_add_neon;                                                                   // 0.0
/*126 */             c->idct    = ff_vp3_idct_neon;                                                                       // 0.0
/*128 */             c->idct_permutation_type = FF_TRANSPOSE_IDCT_PERM;                                                   // 0.0
/*130 */ #endif                                                                                                           // 0.0
/*132 */         }                                                                                                        // 0.0
/*134 */     }                                                                                                            // 0.0
/*138 */     c->put_pixels_tab[0][0] = put_pixels16_arm;                                                                  // 0.0
/*140 */     c->put_pixels_tab[0][1] = put_pixels16_x2_arm;                                                               // 0.0
/*142 */     c->put_pixels_tab[0][2] = put_pixels16_y2_arm;                                                               // 0.0
/*144 */     c->put_pixels_tab[0][3] = put_pixels16_xy2_arm;                                                              // 0.0
/*146 */     c->put_no_rnd_pixels_tab[0][0] = put_pixels16_arm;                                                           // 0.0
/*148 */     c->put_no_rnd_pixels_tab[0][1] = put_no_rnd_pixels16_x2_arm;                                                 // 0.0
/*150 */     c->put_no_rnd_pixels_tab[0][2] = put_no_rnd_pixels16_y2_arm;                                                 // 0.0
/*152 */     c->put_no_rnd_pixels_tab[0][3] = put_no_rnd_pixels16_xy2_arm;                                                // 0.0
/*154 */     c->put_pixels_tab[1][0] = put_pixels8_arm;                                                                   // 0.0
/*156 */     c->put_pixels_tab[1][1] = put_pixels8_x2_arm;                                                                // 0.0
/*158 */     c->put_pixels_tab[1][2] = put_pixels8_y2_arm;                                                                // 0.0
/*160 */     c->put_pixels_tab[1][3] = put_pixels8_xy2_arm;                                                               // 0.0
/*162 */     c->put_no_rnd_pixels_tab[1][0] = put_pixels8_arm;                                                            // 0.0
/*164 */     c->put_no_rnd_pixels_tab[1][1] = put_no_rnd_pixels8_x2_arm;                                                  // 0.0
/*166 */     c->put_no_rnd_pixels_tab[1][2] = put_no_rnd_pixels8_y2_arm;                                                  // 0.0
/*168 */     c->put_no_rnd_pixels_tab[1][3] = put_no_rnd_pixels8_xy2_arm;                                                 // 0.0
/*172 */ #if HAVE_ARMV5TE                                                                                                 // 0.0
/*174 */     c->prefetch = ff_prefetch_arm;                                                                               // 0.0
/*176 */ #endif                                                                                                           // 0.0
/*180 */ #if HAVE_IWMMXT                                                                                                  // 0.0
/*182 */     dsputil_init_iwmmxt(c, avctx);                                                                               // 0.0
/*184 */ #endif                                                                                                           // 0.0
/*186 */ #if HAVE_ARMVFP                                                                                                  // 0.0
/*188 */     ff_float_init_arm_vfp(c, avctx);                                                                             // 0.0
/*190 */ #endif                                                                                                           // 0.0
/*192 */ #if HAVE_NEON                                                                                                    // 0.0
/*194 */     ff_dsputil_init_neon(c, avctx);                                                                              // 0.0
/*196 */ #endif                                                                                                           // 0.0
/*198 */ }                                                                                                                // 0.0
