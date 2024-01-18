// commit message FFmpeg@073c2593c9 (target=1, prob=0.29647008, correct=False): Memory leak fix patch by (Burkhard Plaum <plaum >at< ipf.uni-stuttgart )dot( de>)
/*0  */ void h263_decode_init_vlc(MpegEncContext *s)                      // (13) 0.03711
/*2  */ {                                                                 // (20) 0.001953
/*4  */     static int done = 0;                                          // (18) 0.01758
/*8  */     if (!done) {                                                  // (19) 0.01562
/*10 */         done = 1;                                                 // (17) 0.02148
/*14 */         init_vlc(&intra_MCBPC_vlc, INTRA_MCBPC_VLC_BITS, 9,       // (0) 0.07422
/*16 */                  intra_MCBPC_bits, 1, 1,                          // (7) 0.05469
/*18 */                  intra_MCBPC_code, 1, 1);                         // (8) 0.05469
/*20 */         init_vlc(&inter_MCBPC_vlc, INTER_MCBPC_VLC_BITS, 28,      // (1) 0.07031
/*22 */                  inter_MCBPC_bits, 1, 1,                          // (9) 0.05469
/*24 */                  inter_MCBPC_code, 1, 1);                         // (10) 0.05469
/*26 */         init_vlc(&cbpy_vlc, CBPY_VLC_BITS, 16,                    // (2) 0.05859
/*28 */                  &cbpy_tab[0][1], 2, 1,                           // (3) 0.05859
/*30 */                  &cbpy_tab[0][0], 2, 1);                          // (4) 0.05859
/*32 */         init_vlc(&mv_vlc, MV_VLC_BITS, 33,                        // (11) 0.05469
/*34 */                  &mvtab[0][1], 2, 1,                              // (5) 0.05664
/*36 */                  &mvtab[0][0], 2, 1);                             // (6) 0.05664
/*38 */         init_rl(&rl_inter);                                       // (16) 0.0293
/*40 */         init_rl(&rl_intra);                                       // (15) 0.03125
/*42 */         init_rl(&rvlc_rl_inter);                                  // (14) 0.03711
/*44 */         init_rl(&rvlc_rl_intra);                                  // (12) 0.03906
/*46 */         init_rl(&rl_intra_aic);                                   // 0.0
/*48 */         init_vlc_rl(&rl_inter);                                   // 0.0
/*50 */         init_vlc_rl(&rl_intra);                                   // 0.0
/*52 */         init_vlc_rl(&rvlc_rl_inter);                              // 0.0
/*54 */         init_vlc_rl(&rvlc_rl_intra);                              // 0.0
/*56 */         init_vlc_rl(&rl_intra_aic);                               // 0.0
/*58 */         init_vlc(&dc_lum, DC_VLC_BITS, 10 /* 13 */,               // 0.0
/*60 */                  &DCtab_lum[0][1], 2, 1,                          // 0.0
/*62 */                  &DCtab_lum[0][0], 2, 1);                         // 0.0
/*64 */         init_vlc(&dc_chrom, DC_VLC_BITS, 10 /* 13 */,             // 0.0
/*66 */                  &DCtab_chrom[0][1], 2, 1,                        // 0.0
/*68 */                  &DCtab_chrom[0][0], 2, 1);                       // 0.0
/*70 */         init_vlc(&sprite_trajectory, SPRITE_TRAJ_VLC_BITS, 15,    // 0.0
/*72 */                  &sprite_trajectory_tab[0][1], 4, 2,              // 0.0
/*74 */                  &sprite_trajectory_tab[0][0], 4, 2);             // 0.0
/*76 */         init_vlc(&mb_type_b_vlc, MB_TYPE_B_VLC_BITS, 4,           // 0.0
/*78 */                  &mb_type_b_tab[0][1], 2, 1,                      // 0.0
/*80 */                  &mb_type_b_tab[0][0], 2, 1);                     // 0.0
/*82 */         init_vlc(&h263_mbtype_b_vlc, H263_MBTYPE_B_VLC_BITS, 15,  // 0.0
/*84 */                  &h263_mbtype_b_tab[0][1], 2, 1,                  // 0.0
/*86 */                  &h263_mbtype_b_tab[0][0], 2, 1);                 // 0.0
/*88 */         init_vlc(&cbpc_b_vlc, CBPC_B_VLC_BITS, 4,                 // 0.0
/*90 */                  &cbpc_b_tab[0][1], 2, 1,                         // 0.0
/*92 */                  &cbpc_b_tab[0][0], 2, 1);                        // 0.0
/*94 */     }                                                             // 0.0
/*96 */ }                                                                 // 0.0
