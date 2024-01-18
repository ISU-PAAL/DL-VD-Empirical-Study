// commit message FFmpeg@7cc84d241b (target=1, prob=0.28927904, correct=False): - samples from mplayer ftp in the "adv" profile seem to have profile=2, which isn't the advanced one; and indeed, using adv. profile parser fails. Using normal parser works, and that's what is done - attempt at taking care of stride for NORM2 bitplane decoding - duplication of much code from msmpeg4.c; this code isn't yet used, but goes down as far as the block layer (mainly Transform Type stuff, the remains are wild editing without checking). Unusable yet, and lacks the AC decoding (but a step further in bitstream parsing) patch by anonymous
/*0  */ static int standard_decode_picture_secondary_header(VC9Context *v)      // (7) 0.05234
/*2  */ {                                                                       // (23) 0.002755
/*4  */     GetBitContext *gb = &v->s.gb;                                       // (9) 0.04408
/*6  */     int status = 0, index;                                              // (12) 0.02755
/*10 */     switch (v->s.pict_type)                                             // (11) 0.03581
/*12 */     {                                                                   // (18) 0.01102
/*14 */     case P_TYPE: status = decode_p_picture_secondary_header(v); break;  // (3) 0.06612
/*16 */     case B_TYPE: status = decode_b_picture_secondary_header(v); break;  // (4) 0.06612
/*18 */     case BI_TYPE:                                                       // (14) 0.02204
/*20 */     case I_TYPE: break; //Nothing needed as it's done in the epilog     // (5) 0.06061
/*22 */     }                                                                   // (19) 0.01102
/*24 */     if (status < 0) return FRAME_SKIPED;                                // (8) 0.04683
/*28 */     /* AC Syntax */                                                     // (15) 0.02204
/*30 */     v->ac_table_level = decode012(gb);                                  // (10) 0.04408
/*32 */     if (v->s.pict_type == I_TYPE || v->s.pict_type == BI_TYPE)          // (2) 0.07989
/*34 */     {                                                                   // (20) 0.01102
/*36 */         v->ac2_table_level = decode012(gb);                             // (6) 0.05785
/*38 */     }                                                                   // (21) 0.01102
/*40 */     /* DC Syntax */                                                     // (16) 0.02204
/*42 */     index = decode012(gb);                                              // (13) 0.02755
/*44 */     v->luma_dc_vlc = &ff_msmp4_dc_luma_vlc[index];                      // (0) 0.08264
/*46 */     v->chroma_dc_vlc = &ff_msmp4_dc_chroma_vlc[index];                  // (1) 0.08264
/*48 */                                                                         // (22) 0.008264
/*50 */     return 0;                                                           // (17) 0.01653
/*52 */ }                                                                       // (24) 0.002755
