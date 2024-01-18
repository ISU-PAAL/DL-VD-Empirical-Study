// commit message FFmpeg@bf2bc926f0 (target=1, prob=0.44679534, correct=False): - a lot less overflows when decoding frames - no more error with norm6 codes - almost skipped frames (~110 bits) are not overflowed However: - there are very few bits left in those frames, so I wonder if enough MB data is actually left - NORM6/DIFF6 (4/5) bitplanes are a lot more present, which I don't find obvious. patch by anonymous
/*0   */ static int decode_i_picture_header(VC9Context *v)                                  // (13) 0.03125
/*2   */ {                                                                                  // (29) 0.001953
/*4   */     GetBitContext *gb = &v->s.gb;                                                  // (14) 0.03125
/*6   */     int pqindex, status = 0;                                                       // (17) 0.02344
/*10  */     /* Prolog common to all frametypes should be done in caller */                 // (12) 0.03516
/*12  */     //BF = Buffer Fullness                                                         // (19) 0.01758
/*14  */     if (v->profile <= PROFILE_MAIN && get_bits(gb, 7))                             // (6) 0.04492
/*16  */     {                                                                              // (23) 0.007812
/*18  */         av_log(v->s.avctx, AV_LOG_DEBUG, "I BufferFullness not 0\n");              // (1) 0.06641
/*20  */     }                                                                              // (21) 0.007812
/*24  */     /* Quantizer stuff */                                                          // (20) 0.01563
/*26  */     pqindex = get_bits(gb, 5);                                                     // (16) 0.0293
/*28  */     if (v->quantizer_mode == QUANT_FRAME_IMPLICIT)                                 // (8) 0.04297
/*30  */         v->pq = pquant_table[0][pqindex];                                          // (7) 0.04492
/*32  */     else                                                                           // (24) 0.007812
/*34  */     {                                                                              // (27) 0.007812
/*36  */         v->pq = pquant_table[v->quantizer_mode-1][pqindex];                        // (3) 0.05859
/*38  */     }                                                                              // (25) 0.007812
/*40  */     if (pqindex < 9) v->halfpq = get_bits(gb, 1);                                  // (5) 0.04883
/*42  */     if (v->quantizer_mode == QUANT_FRAME_EXPLICIT)                                 // (9) 0.04297
/*44  */         v->pquantizer = get_bits(gb, 1);                                           // (10) 0.04102
/*46  */     av_log(v->s.avctx, AV_LOG_DEBUG, "I frame: QP=%i (+%i/2)\n",                   // (0) 0.07227
/*48  */            v->pq, v->halfpq);                                                      // (11) 0.04102
/*50  */ #if HAS_ADVANCED_PROFILE                                                           // (18) 0.02148
/*52  */     if (v->profile <= PROFILE_MAIN)                                                // (15) 0.0293
/*54  */ #endif                                                                             // (28) 0.003906
/*56  */     {                                                                              // (26) 0.007812
/*58  */         if (v->extended_mv) v->mvrange = get_prefix(gb, 0, 3);                     // (2) 0.06445
/*60  */         if (v->multires) v->respic = get_bits(gb, 2);                              // (4) 0.05273
/*62  */     }                                                                              // (22) 0.007812
/*64  */ #if HAS_ADVANCED_PROFILE                                                           // 0.0
/*66  */     else                                                                           // 0.0
/*68  */     {                                                                              // 0.0
/*70  */         v->s.ac_pred = get_bits(gb, 1);                                            // 0.0
/*72  */         if (v->postprocflag) v->postproc = get_bits(gb, 1);                        // 0.0
/*74  */         /* 7.1.1.34 + 8.5.2 */                                                     // 0.0
/*76  */         if (v->overlap && v->pq<9)                                                 // 0.0
/*78  */         {                                                                          // 0.0
/*80  */             v->condover = get_bits(gb, 1);                                         // 0.0
/*82  */             if (v->condover)                                                       // 0.0
/*84  */             {                                                                      // 0.0
/*86  */                 v->condover = 2+get_bits(gb, 1);                                   // 0.0
/*88  */                 if (v->condover == 3)                                              // 0.0
/*90  */                 {                                                                  // 0.0
/*92  */                     status = bitplane_decoding(&v->over_flags_plane, v);           // 0.0
/*94  */                     if (status < 0) return -1;                                     // 0.0
/*96  */ #if TRACE                                                                          // 0.0
/*98  */                     av_log(v->s.avctx, AV_LOG_DEBUG, "Overflags plane encoding: "  // 0.0
/*100 */                            "Imode: %i, Invert: %i\n", status>>1, status&1);        // 0.0
/*102 */ #endif                                                                             // 0.0
/*104 */                 }                                                                  // 0.0
/*106 */             }                                                                      // 0.0
/*108 */         }                                                                          // 0.0
/*110 */     }                                                                              // 0.0
/*112 */ #endif                                                                             // 0.0
/*116 */     /* Epilog (AC/DC syntax) should be done in caller */                           // 0.0
/*118 */     return status;                                                                 // 0.0
/*120 */ }                                                                                  // 0.0
