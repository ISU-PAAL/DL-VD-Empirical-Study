// commit message FFmpeg@f7cf12b209 (target=1, prob=0.57392263, correct=True): Set flag after VC-1 VLCs are initialized to avoid race condition
/*0   */ static int vc1_init_common(VC1Context *v)                                                   // (12) 0.03125
/*2   */ {                                                                                           // (19) 0.001953
/*4   */     static int done = 0;                                                                    // (14) 0.01758
/*6   */     int i = 0;                                                                              // (16) 0.01562
/*10  */     v->hrd_rate = v->hrd_buffer = NULL;                                                     // (11) 0.03711
/*14  */     /* VLC tables */                                                                        // (15) 0.01563
/*16  */     if(!done)                                                                               // (17) 0.01562
/*18  */     {                                                                                       // (18) 0.007812
/*20  */         done = 1;                                                                           // (13) 0.02148
/*22  */         init_vlc(&ff_vc1_bfraction_vlc, VC1_BFRACTION_VLC_BITS, 23,                         // (3) 0.07422
/*24  */                  ff_vc1_bfraction_bits, 1, 1,                                               // (7) 0.05859
/*26  */                  ff_vc1_bfraction_codes, 1, 1, INIT_VLC_USE_STATIC);                        // (0) 0.08008
/*28  */         init_vlc(&ff_vc1_norm2_vlc, VC1_NORM2_VLC_BITS, 4,                                  // (4) 0.07422
/*30  */                  ff_vc1_norm2_bits, 1, 1,                                                   // (8) 0.05859
/*32  */                  ff_vc1_norm2_codes, 1, 1, INIT_VLC_USE_STATIC);                            // (1) 0.08008
/*34  */         init_vlc(&ff_vc1_norm6_vlc, VC1_NORM6_VLC_BITS, 64,                                 // (5) 0.07422
/*36  */                  ff_vc1_norm6_bits, 1, 1,                                                   // (9) 0.05859
/*38  */                  ff_vc1_norm6_codes, 2, 2, INIT_VLC_USE_STATIC);                            // (2) 0.08008
/*40  */         init_vlc(&ff_vc1_imode_vlc, VC1_IMODE_VLC_BITS, 7,                                  // (6) 0.07227
/*42  */                  ff_vc1_imode_bits, 1, 1,                                                   // (10) 0.05859
/*44  */                  ff_vc1_imode_codes, 1, 1, INIT_VLC_USE_STATIC);                            // 0.0
/*46  */         for (i=0; i<3; i++)                                                                 // 0.0
/*48  */         {                                                                                   // 0.0
/*50  */             init_vlc(&ff_vc1_ttmb_vlc[i], VC1_TTMB_VLC_BITS, 16,                            // 0.0
/*52  */                      ff_vc1_ttmb_bits[i], 1, 1,                                             // 0.0
/*54  */                      ff_vc1_ttmb_codes[i], 2, 2, INIT_VLC_USE_STATIC);                      // 0.0
/*56  */             init_vlc(&ff_vc1_ttblk_vlc[i], VC1_TTBLK_VLC_BITS, 8,                           // 0.0
/*58  */                      ff_vc1_ttblk_bits[i], 1, 1,                                            // 0.0
/*60  */                      ff_vc1_ttblk_codes[i], 1, 1, INIT_VLC_USE_STATIC);                     // 0.0
/*62  */             init_vlc(&ff_vc1_subblkpat_vlc[i], VC1_SUBBLKPAT_VLC_BITS, 15,                  // 0.0
/*64  */                      ff_vc1_subblkpat_bits[i], 1, 1,                                        // 0.0
/*66  */                      ff_vc1_subblkpat_codes[i], 1, 1, INIT_VLC_USE_STATIC);                 // 0.0
/*68  */         }                                                                                   // 0.0
/*70  */         for(i=0; i<4; i++)                                                                  // 0.0
/*72  */         {                                                                                   // 0.0
/*74  */             init_vlc(&ff_vc1_4mv_block_pattern_vlc[i], VC1_4MV_BLOCK_PATTERN_VLC_BITS, 16,  // 0.0
/*76  */                      ff_vc1_4mv_block_pattern_bits[i], 1, 1,                                // 0.0
/*78  */                      ff_vc1_4mv_block_pattern_codes[i], 1, 1, INIT_VLC_USE_STATIC);         // 0.0
/*80  */             init_vlc(&ff_vc1_cbpcy_p_vlc[i], VC1_CBPCY_P_VLC_BITS, 64,                      // 0.0
/*82  */                      ff_vc1_cbpcy_p_bits[i], 1, 1,                                          // 0.0
/*84  */                      ff_vc1_cbpcy_p_codes[i], 2, 2, INIT_VLC_USE_STATIC);                   // 0.0
/*86  */             init_vlc(&ff_vc1_mv_diff_vlc[i], VC1_MV_DIFF_VLC_BITS, 73,                      // 0.0
/*88  */                      ff_vc1_mv_diff_bits[i], 1, 1,                                          // 0.0
/*90  */                      ff_vc1_mv_diff_codes[i], 2, 2, INIT_VLC_USE_STATIC);                   // 0.0
/*92  */         }                                                                                   // 0.0
/*94  */         for(i=0; i<8; i++)                                                                  // 0.0
/*96  */             init_vlc(&ff_vc1_ac_coeff_table[i], AC_VLC_BITS, vc1_ac_sizes[i],               // 0.0
/*98  */                      &vc1_ac_tables[i][0][1], 8, 4,                                         // 0.0
/*100 */                      &vc1_ac_tables[i][0][0], 8, 4, INIT_VLC_USE_STATIC);                   // 0.0
/*102 */         init_vlc(&ff_msmp4_mb_i_vlc, MB_INTRA_VLC_BITS, 64,                                 // 0.0
/*104 */                  &ff_msmp4_mb_i_table[0][1], 4, 2,                                          // 0.0
/*106 */                  &ff_msmp4_mb_i_table[0][0], 4, 2, INIT_VLC_USE_STATIC);                    // 0.0
/*108 */     }                                                                                       // 0.0
/*112 */     /* Other defaults */                                                                    // 0.0
/*114 */     v->pq = -1;                                                                             // 0.0
/*116 */     v->mvrange = 0; /* 7.1.1.18, p80 */                                                     // 0.0
/*120 */     return 0;                                                                               // 0.0
/*122 */ }                                                                                           // 0.0
