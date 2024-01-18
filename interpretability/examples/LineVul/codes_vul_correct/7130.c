// commit message FFmpeg@bf2bc926f0 (target=1, prob=0.5428004, correct=True): - a lot less overflows when decoding frames - no more error with norm6 codes - almost skipped frames (~110 bits) are not overflowed However: - there are very few bits left in those frames, so I wonder if enough MB data is actually left - NORM6/DIFF6 (4/5) bitplanes are a lot more present, which I don't find obvious. patch by anonymous
/*0   */ static int decode_b_picture_secondary_header(VC9Context *v)             // (11) 0.03516
/*2   */ {                                                                       // (28) 0.001953
/*4   */     GetBitContext *gb = &v->s.gb;                                       // (13) 0.03125
/*6   */     int status;                                                         // (19) 0.01172
/*10  */     bitplane_decoding(&v->skip_mb_plane, v);                            // (10) 0.03711
/*12  */     if (status < 0) return -1;                                          // (15) 0.02539
/*14  */ #if TRACE                                                               // (21) 0.007813
/*16  */     if (v->mv_mode == MV_PMODE_MIXED_MV)                                // (8) 0.04688
/*18  */     {                                                                   // (24) 0.007812
/*20  */         status = bitplane_decoding(&v->mv_type_mb_plane, v);            // (5) 0.05469
/*22  */         if (status < 0)                                                 // (17) 0.02539
/*24  */             return -1;                                                  // (14) 0.0293
/*26  */ #if TRACE                                                               // (22) 0.007813
/*28  */         av_log(v->s.avctx, AV_LOG_DEBUG, "MB MV Type plane encoding: "  // (3) 0.0625
/*30  */                "Imode: %i, Invert: %i\n", status>>1, status&1);         // (0) 0.07227
/*32  */ #endif                                                                  // (25) 0.003906
/*34  */     }                                                                   // (20) 0.007813
/*38  */     //bitplane                                                          // (18) 0.01172
/*40  */     status = bitplane_decoding(&v->direct_mb_plane, v);                 // (9) 0.04102
/*42  */     if (status < 0) return -1;                                          // (16) 0.02539
/*44  */ #if TRACE                                                               // (23) 0.007813
/*46  */     av_log(v->s.avctx, AV_LOG_DEBUG, "MB Direct plane encoding: "       // (7) 0.05273
/*48  */            "Imode: %i, Invert: %i\n", status>>1, status&1);             // (1) 0.06445
/*50  */ #endif                                                                  // (27) 0.003906
/*54  */     av_log(v->s.avctx, AV_LOG_DEBUG, "Skip MB plane encoding: "         // (6) 0.05273
/*56  */            "Imode: %i, Invert: %i\n", status>>1, status&1);             // (2) 0.06445
/*58  */ #endif                                                                  // (26) 0.003906
/*62  */     /* FIXME: what is actually chosen for B frames ? */                 // (12) 0.03125
/*64  */     v->s.mv_table_index = get_bits(gb, 2); //but using vc9_ tables      // (4) 0.05859
/*66  */     v->cbpcy_vlc = &vc9_cbpcy_p_vlc[get_bits(gb, 2)];                   // 0.0
/*70  */     if (v->dquant)                                                      // 0.0
/*72  */     {                                                                   // 0.0
/*74  */         vop_dquant_decoding(v);                                         // 0.0
/*76  */     }                                                                   // 0.0
/*80  */     if (v->vstransform)                                                 // 0.0
/*82  */     {                                                                   // 0.0
/*84  */         v->ttmbf = get_bits(gb, 1);                                     // 0.0
/*86  */         if (v->ttmbf)                                                   // 0.0
/*88  */         {                                                               // 0.0
/*90  */             v->ttfrm = get_bits(gb, 2);                                 // 0.0
/*92  */             av_log(v->s.avctx, AV_LOG_INFO, "Transform used: %ix%i\n",  // 0.0
/*94  */                    (v->ttfrm & 2) ? 4 : 8, (v->ttfrm & 1) ? 4 : 8);     // 0.0
/*96  */         }                                                               // 0.0
/*98  */     }                                                                   // 0.0
/*100 */     /* Epilog (AC/DC syntax) should be done in caller */                // 0.0
/*102 */     return 0;                                                           // 0.0
/*104 */ }                                                                       // 0.0
