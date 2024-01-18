// commit message FFmpeg@7cc84d241b (target=1, prob=0.45081076, correct=False): - samples from mplayer ftp in the "adv" profile seem to have profile=2, which isn't the advanced one; and indeed, using adv. profile parser fails. Using normal parser works, and that's what is done - attempt at taking care of stride for NORM2 bitplane decoding - duplication of much code from msmpeg4.c; this code isn't yet used, but goes down as far as the block layer (mainly Transform Type stuff, the remains are wild editing without checking). Unusable yet, and lacks the AC decoding (but a step further in bitstream parsing) patch by anonymous
/*0  */ static int decode_i_picture_primary_header(VC9Context *v)              // (11) 0.04401
/*2  */ {                                                                      // (24) 0.002445
/*4  */     GetBitContext *gb = &v->s.gb;                                      // (12) 0.03912
/*6  */     int pqindex;                                                       // (16) 0.01956
/*10 */     /* Prolog common to all frametypes should be done in caller */     // (10) 0.04401
/*12 */     //BF = Buffer Fullness                                             // (14) 0.02201
/*14 */     if (v->profile <= PROFILE_MAIN && get_bits(gb, 7))                 // (4) 0.05623
/*16 */     {                                                                  // (18) 0.00978
/*18 */         av_log(v->s.avctx, AV_LOG_DEBUG, "I BufferFullness not 0\n");  // (1) 0.08313
/*20 */     }                                                                  // (20) 0.00978
/*24 */     /* Quantizer stuff */                                              // (15) 0.01956
/*26 */     pqindex = get_bits(gb, 5);                                         // (13) 0.03667
/*28 */     if (v->quantizer_mode == QUANT_FRAME_IMPLICIT)                     // (6) 0.05379
/*30 */         v->pq = pquant_table[0][pqindex];                              // (5) 0.05623
/*32 */     else                                                               // (21) 0.00978
/*34 */     {                                                                  // (19) 0.00978
/*36 */         v->pq = pquant_table[v->quantizer_mode-1][pqindex];            // (2) 0.07335
/*38 */     }                                                                  // (22) 0.00978
/*40 */     if (pqindex < 9) v->halfpq = get_bits(gb, 1);                      // (3) 0.06112
/*42 */     if (v->quantizer_mode == QUANT_FRAME_EXPLICIT)                     // (7) 0.05379
/*44 */         v->pquantizer = get_bits(gb, 1);                               // (9) 0.05134
/*46 */     av_log(v->s.avctx, AV_LOG_DEBUG, "I frame: QP=%i (+%i/2)\n",       // (0) 0.09046
/*48 */            v->pq, v->halfpq);                                          // (8) 0.05134
/*50 */     return 0;                                                          // (17) 0.01467
/*52 */ }                                                                      // (23) 0.002445
