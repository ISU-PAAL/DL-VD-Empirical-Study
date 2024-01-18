// commit message FFmpeg@bf2bc926f0 (target=1, prob=0.4958141, correct=False): - a lot less overflows when decoding frames - no more error with norm6 codes - almost skipped frames (~110 bits) are not overflowed However: - there are very few bits left in those frames, so I wonder if enough MB data is actually left - NORM6/DIFF6 (4/5) bitplanes are a lot more present, which I don't find obvious. patch by anonymous
/*0  */ static int standard_decode_picture_primary_header(VC9Context *v)      // (9) 0.03918
/*2  */ {                                                                     // (30) 0.002062
/*4  */     GetBitContext *gb = &v->s.gb;                                     // (14) 0.03299
/*6  */     int status = 0;                                                   // (18) 0.01649
/*10 */     if (v->finterpflag) v->interpfrm = get_bits(gb, 1);               // (2) 0.05567
/*12 */     skip_bits(gb, 2); //framecnt unused                               // (13) 0.03299
/*14 */     if (v->rangered) v->rangeredfrm = get_bits(gb, 1);                // (3) 0.05155
/*16 */     v->s.pict_type = get_bits(gb, 1);                                 // (10) 0.03918
/*18 */     if (v->s.avctx->max_b_frames)                                     // (11) 0.03711
/*20 */     {                                                                 // (24) 0.008247
/*22 */         if (!v->s.pict_type)                                          // (12) 0.03505
/*24 */         {                                                             // (19) 0.01649
/*26 */             if (get_bits(gb, 1)) v->s.pict_type = I_TYPE;             // (0) 0.06804
/*28 */             else v->s.pict_type = B_TYPE;                             // (4) 0.04948
/*30 */         }                                                             // (20) 0.01649
/*32 */         else v->s.pict_type = P_TYPE;                                 // (8) 0.04124
/*34 */     }                                                                 // (25) 0.008247
/*36 */     else v->s.pict_type++;                                            // (17) 0.02474
/*40 */     switch (v->s.pict_type)                                           // (16) 0.0268
/*42 */     {                                                                 // (26) 0.008247
/*44 */     case I_TYPE: status = decode_i_picture_header(v); break;          // (7) 0.04536
/*46 */     case P_TYPE: status = decode_p_picture_primary_header(v); break;  // (5) 0.04948
/*48 */     case BI_TYPE:                                                     // (21) 0.01649
/*50 */     case B_TYPE: status = decode_b_picture_primary_header(v); break;  // (6) 0.04948
/*52 */     }                                                                 // (27) 0.008247
/*56 */     if (status == FRAME_SKIPED)                                       // (15) 0.02887
/*58 */     {                                                                 // (28) 0.008247
/*60 */       av_log(v->s.avctx, AV_LOG_INFO, "Skipping frame...\n");         // (1) 0.06392
/*62 */       return status;                                                  // (22) 0.01649
/*64 */     }                                                                 // (29) 0.008247
/*66 */     return 0;                                                         // (23) 0.01237
/*68 */ }                                                                     // (31) 0.002062
