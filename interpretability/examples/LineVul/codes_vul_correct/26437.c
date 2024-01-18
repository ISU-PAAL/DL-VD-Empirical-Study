// commit message FFmpeg@7cc84d241b (target=1, prob=0.5446096, correct=True): - samples from mplayer ftp in the "adv" profile seem to have profile=2, which isn't the advanced one; and indeed, using adv. profile parser fails. Using normal parser works, and that's what is done - attempt at taking care of stride for NORM2 bitplane decoding - duplication of much code from msmpeg4.c; this code isn't yet used, but goes down as far as the block layer (mainly Transform Type stuff, the remains are wild editing without checking). Unusable yet, and lacks the AC decoding (but a step further in bitstream parsing) patch by anonymous
/*0  */ static int standard_decode_i_mbs(VC9Context *v)                                                     // (11) 0.03516
/*2  */ {                                                                                                   // (21) 0.001953
/*4  */     GetBitContext *gb = &v->s.gb;                                                                   // (14) 0.03125
/*6  */     MpegEncContext *s = &v->s;                                                                      // (15) 0.0293
/*8  */     int current_mb = 0; /* MB/Block Position info */                                                // (12) 0.0332
/*10 */     uint8_t cbpcy[4], previous_cbpcy[4], predicted_cbpcy,                                           // (6) 0.05273
/*12 */         *p_cbpcy /* Pointer to skip some math */;                                                   // (10) 0.04297
/*16 */     /* Reset CBPCY predictors */                                                                    // (18) 0.02148
/*18 */     memset(v->previous_line_cbpcy, 0, s->mb_stride<<2);                                             // (5) 0.05469
/*22 */     /* Select ttmb table depending on pq */                                                         // (17) 0.02734
/*24 */     if (v->pq < 5) v->ttmb_vlc = &vc9_ttmb_vlc[0];                                                  // (3) 0.0625
/*26 */     else if (v->pq < 13) v->ttmb_vlc = &vc9_ttmb_vlc[1];                                            // (2) 0.06445
/*28 */     else v->ttmb_vlc = &vc9_ttmb_vlc[2];                                                            // (9) 0.04687
/*32 */     for (s->mb_y=0; s->mb_y<s->mb_height; s->mb_y++)                                                // (4) 0.06055
/*34 */     {                                                                                               // (20) 0.007812
/*36 */         /* Init CBPCY for line */                                                                   // (16) 0.0293
/*38 */         *((uint32_t*)previous_cbpcy) = 0x00000000;                                                  // (7) 0.05078
/*40 */         p_cbpcy = v->previous_line_cbpcy+4;                                                         // (8) 0.05078
/*44 */         for (s->mb_x=0; s->mb_x<s->mb_width; s->mb_x++, p_cbpcy += 4)                               // (0) 0.08594
/*46 */         {                                                                                           // (19) 0.01562
/*48 */             /* Get CBPCY */                                                                         // (13) 0.0332
/*50 */             GET_CBPCY(ff_msmp4_mb_i_vlc.table, MB_INTRA_VLC_BITS);                                  // (1) 0.08398
/*54 */             s->ac_pred = get_bits(gb, 1);                                                           // 0.0
/*58 */             /* TODO: Decode blocks from that mb wrt cbpcy */                                        // 0.0
/*62 */             /* Update for next block */                                                             // 0.0
/*64 */ #if TRACE > 2                                                                                       // 0.0
/*66 */             av_log(s->avctx, AV_LOG_DEBUG, "Block %4i: p_cbpcy=%i%i%i%i, previous_cbpcy=%i%i%i%i,"  // 0.0
/*68 */                    " cbpcy=%i%i%i%i\n", current_mb,                                                 // 0.0
/*70 */                    p_cbpcy[0], p_cbpcy[1], p_cbpcy[2], p_cbpcy[3],                                  // 0.0
/*72 */                    previous_cbpcy[0], previous_cbpcy[1], previous_cbpcy[2], previous_cbpcy[3],      // 0.0
/*74 */                    cbpcy[0], cbpcy[1], cbpcy[2], cbpcy[3]);                                         // 0.0
/*76 */ #endif                                                                                              // 0.0
/*78 */             *((uint32_t*)p_cbpcy) = *((uint32_t*)previous_cbpcy);                                   // 0.0
/*80 */             *((uint32_t*)previous_cbpcy) = *((uint32_t*)cbpcy);                                     // 0.0
/*82 */             current_mb++;                                                                           // 0.0
/*84 */         }                                                                                           // 0.0
/*86 */     }                                                                                               // 0.0
/*88 */     return 0;                                                                                       // 0.0
/*90 */ }                                                                                                   // 0.0
