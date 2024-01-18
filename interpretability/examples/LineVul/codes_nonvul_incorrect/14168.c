// commit message FFmpeg@70d54392f5 (target=0, prob=0.6291776, correct=False): lowres2 support.
/*0   */ av_cold int ff_dvvideo_init(AVCodecContext *avctx)                             // (12) 0.03906
/*2   */ {                                                                              // (20) 0.001953
/*4   */     DVVideoContext *s = avctx->priv_data;                                      // (13) 0.03125
/*6   */     DSPContext dsp;                                                            // (16) 0.01758
/*8   */     static int done = 0;                                                       // (17) 0.01758
/*10  */     int i, j;                                                                  // (18) 0.01562
/*14  */     if (!done) {                                                               // (19) 0.01562
/*16  */         VLC dv_vlc;                                                            // (14) 0.0293
/*18  */         uint16_t new_dv_vlc_bits[NB_DV_VLC*2];                                 // (8) 0.06055
/*20  */         uint8_t  new_dv_vlc_len[NB_DV_VLC*2];                                  // (5) 0.0625
/*22  */         uint8_t  new_dv_vlc_run[NB_DV_VLC*2];                                  // (6) 0.0625
/*24  */         int16_t  new_dv_vlc_level[NB_DV_VLC*2];                                // (7) 0.0625
/*28  */         done = 1;                                                              // (15) 0.02148
/*32  */         /* it's faster to include sign bit in a generic VLC parsing scheme */  // (11) 0.04492
/*34  */         for (i = 0, j = 0; i < NB_DV_VLC; i++, j++) {                          // (4) 0.06445
/*36  */             new_dv_vlc_bits[j]  = dv_vlc_bits[i];                              // (2) 0.06836
/*38  */             new_dv_vlc_len[j]   = dv_vlc_len[i];                               // (0) 0.07031
/*40  */             new_dv_vlc_run[j]   = dv_vlc_run[i];                               // (1) 0.07031
/*42  */             new_dv_vlc_level[j] = dv_vlc_level[i];                             // (3) 0.06641
/*46  */             if (dv_vlc_level[i]) {                                             // (10) 0.04688
/*48  */                 new_dv_vlc_bits[j] <<= 1;                                      // (9) 0.06055
/*50  */                 new_dv_vlc_len[j]++;                                           // 0.0
/*54  */                 j++;                                                           // 0.0
/*56  */                 new_dv_vlc_bits[j]  = (dv_vlc_bits[i] << 1) | 1;               // 0.0
/*58  */                 new_dv_vlc_len[j]   =  dv_vlc_len[i] + 1;                      // 0.0
/*60  */                 new_dv_vlc_run[j]   =  dv_vlc_run[i];                          // 0.0
/*62  */                 new_dv_vlc_level[j] = -dv_vlc_level[i];                        // 0.0
/*64  */             }                                                                  // 0.0
/*66  */         }                                                                      // 0.0
/*70  */         /* NOTE: as a trick, we use the fact the no codes are unused           // 0.0
/*72  */            to accelerate the parsing of partial codes */                       // 0.0
/*74  */         init_vlc(&dv_vlc, TEX_VLC_BITS, j,                                     // 0.0
/*76  */                  new_dv_vlc_len, 1, 1, new_dv_vlc_bits, 2, 2, 0);              // 0.0
/*78  */         assert(dv_vlc.table_size == 1184);                                     // 0.0
/*82  */         for (i = 0; i < dv_vlc.table_size; i++){                               // 0.0
/*84  */             int code = dv_vlc.table[i][0];                                     // 0.0
/*86  */             int len  = dv_vlc.table[i][1];                                     // 0.0
/*88  */             int level, run;                                                    // 0.0
/*92  */             if (len < 0){ //more bits needed                                   // 0.0
/*94  */                 run   = 0;                                                     // 0.0
/*96  */                 level = code;                                                  // 0.0
/*98  */             } else {                                                           // 0.0
/*100 */                 run   = new_dv_vlc_run  [code] + 1;                            // 0.0
/*102 */                 level = new_dv_vlc_level[code];                                // 0.0
/*104 */             }                                                                  // 0.0
/*106 */             ff_dv_rl_vlc[i].len   = len;                                       // 0.0
/*108 */             ff_dv_rl_vlc[i].level = level;                                     // 0.0
/*110 */             ff_dv_rl_vlc[i].run   = run;                                       // 0.0
/*112 */         }                                                                      // 0.0
/*114 */         ff_free_vlc(&dv_vlc);                                                  // 0.0
/*116 */     }                                                                          // 0.0
/*120 */     /* Generic DSP setup */                                                    // 0.0
/*122 */     ff_dsputil_init(&dsp, avctx);                                              // 0.0
/*124 */     ff_set_cmp(&dsp, dsp.ildct_cmp, avctx->ildct_cmp);                         // 0.0
/*126 */     s->get_pixels = dsp.get_pixels;                                            // 0.0
/*128 */     s->ildct_cmp = dsp.ildct_cmp[5];                                           // 0.0
/*132 */     /* 88DCT setup */                                                          // 0.0
/*134 */     s->fdct[0]     = dsp.fdct;                                                 // 0.0
/*136 */     s->idct_put[0] = dsp.idct_put;                                             // 0.0
/*138 */     for (i = 0; i < 64; i++)                                                   // 0.0
/*140 */        s->dv_zigzag[0][i] = dsp.idct_permutation[ff_zigzag_direct[i]];         // 0.0
/*144 */     /* 248DCT setup */                                                         // 0.0
/*146 */     s->fdct[1]     = dsp.fdct248;                                              // 0.0
/*148 */     s->idct_put[1] = ff_simple_idct248_put;  // FIXME: need to add it to DSP   // 0.0
/*150 */     memcpy(s->dv_zigzag[1], ff_zigzag248_direct, 64);                          // 0.0
/*154 */     avctx->coded_frame = &s->picture;                                          // 0.0
/*156 */     s->avctx = avctx;                                                          // 0.0
/*158 */     avctx->chroma_sample_location = AVCHROMA_LOC_TOPLEFT;                      // 0.0
/*162 */     return 0;                                                                  // 0.0
/*164 */ }                                                                              // 0.0
