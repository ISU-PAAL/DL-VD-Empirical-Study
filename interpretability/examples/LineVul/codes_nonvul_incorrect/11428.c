// commit message FFmpeg@577393321c (target=0, prob=0.7508008, correct=False): intrax8: Carry over the loopfilter value in ff_intrax8_decode_picture
/*0  */ void ff_vc1_decode_blocks(VC1Context *v)                                                 // (15) 0.0332
/*2  */ {                                                                                        // (21) 0.001953
/*6  */     v->s.esc3_level_length = 0;                                                          // (16) 0.03125
/*8  */     if (v->x8_type) {                                                                    // (17) 0.02539
/*10 */         ff_intrax8_decode_picture(&v->x8, 2*v->pq + v->halfpq, v->pq * !v->pquantizer);  // (1) 0.09375
/*14 */         ff_er_add_slice(&v->s.er, 0, 0,                                                  // (5) 0.04883
/*16 */                         (v->s.mb_x >> 1) - 1, (v->s.mb_y >> 1) - 1,                      // (0) 0.09961
/*18 */                         ER_MB_END);                                                      // (3) 0.05664
/*20 */     } else {                                                                             // (20) 0.01172
/*22 */         v->cur_blk_idx     =  0;                                                         // (7) 0.04687
/*24 */         v->left_blk_idx    = -1;                                                         // (9) 0.04492
/*26 */         v->topleft_blk_idx =  1;                                                         // (11) 0.04297
/*28 */         v->top_blk_idx     =  2;                                                         // (8) 0.04687
/*30 */         switch (v->s.pict_type) {                                                        // (12) 0.03516
/*32 */         case AV_PICTURE_TYPE_I:                                                          // (14) 0.03516
/*34 */             if (v->profile == PROFILE_ADVANCED)                                          // (6) 0.04883
/*36 */                 vc1_decode_i_blocks_adv(v);                                              // (2) 0.05859
/*38 */             else                                                                         // (19) 0.02344
/*40 */                 vc1_decode_i_blocks(v);                                                  // (4) 0.05469
/*42 */             break;                                                                       // (18) 0.02539
/*44 */         case AV_PICTURE_TYPE_P:                                                          // (13) 0.03516
/*46 */             if (v->p_frame_skipped)                                                      // (10) 0.04297
/*48 */                 vc1_decode_skip_blocks(v);                                               // 0.0
/*50 */             else                                                                         // 0.0
/*52 */                 vc1_decode_p_blocks(v);                                                  // 0.0
/*54 */             break;                                                                       // 0.0
/*56 */         case AV_PICTURE_TYPE_B:                                                          // 0.0
/*58 */             if (v->bi_type) {                                                            // 0.0
/*60 */                 if (v->profile == PROFILE_ADVANCED)                                      // 0.0
/*62 */                     vc1_decode_i_blocks_adv(v);                                          // 0.0
/*64 */                 else                                                                     // 0.0
/*66 */                     vc1_decode_i_blocks(v);                                              // 0.0
/*68 */             } else                                                                       // 0.0
/*70 */                 vc1_decode_b_blocks(v);                                                  // 0.0
/*72 */             break;                                                                       // 0.0
/*74 */         }                                                                                // 0.0
/*76 */     }                                                                                    // 0.0
/*78 */ }                                                                                        // 0.0
