// commit message FFmpeg@099d6813c2 (target=1, prob=0.0663246, correct=False): svq3: Fix memory corruption introduced by automatic thread_count.
/*0  */ int ff_h264_alloc_tables(H264Context *h){                                                                                 // (10) 0.03321
/*2  */     MpegEncContext * const s = &h->s;                                                                                     // (11) 0.03125
/*4  */     const int big_mb_num= s->mb_stride * (s->mb_height+1);                                                                // (9) 0.05274
/*6  */     const int row_mb_num= 2*s->mb_stride*s->avctx->thread_count;                                                          // (8) 0.05664
/*8  */     int x,y;                                                                                                              // (12) 0.01563
/*12 */     FF_ALLOCZ_OR_GOTO(h->s.avctx, h->intra4x4_pred_mode, row_mb_num * 8  * sizeof(uint8_t), fail)                         // (1) 0.09961
/*16 */     FF_ALLOCZ_OR_GOTO(h->s.avctx, h->non_zero_count    , big_mb_num * 48 * sizeof(uint8_t), fail)                         // (2) 0.0957
/*18 */     FF_ALLOCZ_OR_GOTO(h->s.avctx, h->slice_table_base  , (big_mb_num+s->mb_stride) * sizeof(*h->slice_table_base), fail)  // (0) 0.1113
/*20 */     FF_ALLOCZ_OR_GOTO(h->s.avctx, h->cbp_table, big_mb_num * sizeof(uint16_t), fail)                                      // (7) 0.08398
/*24 */     FF_ALLOCZ_OR_GOTO(h->s.avctx, h->chroma_pred_mode_table, big_mb_num * sizeof(uint8_t), fail)                          // (5) 0.09179
/*26 */     FF_ALLOCZ_OR_GOTO(h->s.avctx, h->mvd_table[0], 16*row_mb_num * sizeof(uint8_t), fail);                                // (4) 0.09179
/*28 */     FF_ALLOCZ_OR_GOTO(h->s.avctx, h->mvd_table[1], 16*row_mb_num * sizeof(uint8_t), fail);                                // (3) 0.09179
/*30 */     FF_ALLOCZ_OR_GOTO(h->s.avctx, h->direct_table, 4*big_mb_num * sizeof(uint8_t) , fail);                                // (6) 0.08789
/*32 */     FF_ALLOCZ_OR_GOTO(h->s.avctx, h->list_counts, big_mb_num * sizeof(uint8_t), fail)                                     // 0.0
/*36 */     memset(h->slice_table_base, -1, (big_mb_num+s->mb_stride)  * sizeof(*h->slice_table_base));                           // 0.0
/*38 */     h->slice_table= h->slice_table_base + s->mb_stride*2 + 1;                                                             // 0.0
/*42 */     FF_ALLOCZ_OR_GOTO(h->s.avctx, h->mb2b_xy  , big_mb_num * sizeof(uint32_t), fail);                                     // 0.0
/*44 */     FF_ALLOCZ_OR_GOTO(h->s.avctx, h->mb2br_xy , big_mb_num * sizeof(uint32_t), fail);                                     // 0.0
/*46 */     for(y=0; y<s->mb_height; y++){                                                                                        // 0.0
/*48 */         for(x=0; x<s->mb_width; x++){                                                                                     // 0.0
/*50 */             const int mb_xy= x + y*s->mb_stride;                                                                          // 0.0
/*52 */             const int b_xy = 4*x + 4*y*h->b_stride;                                                                       // 0.0
/*56 */             h->mb2b_xy [mb_xy]= b_xy;                                                                                     // 0.0
/*58 */             h->mb2br_xy[mb_xy]= 8*(FMO ? mb_xy : (mb_xy % (2*s->mb_stride)));                                             // 0.0
/*60 */         }                                                                                                                 // 0.0
/*62 */     }                                                                                                                     // 0.0
/*66 */     s->obmc_scratchpad = NULL;                                                                                            // 0.0
/*70 */     if(!h->dequant4_coeff[0])                                                                                             // 0.0
/*72 */         init_dequant_tables(h);                                                                                           // 0.0
/*76 */     return 0;                                                                                                             // 0.0
/*78 */ fail:                                                                                                                     // 0.0
/*80 */     free_tables(h, 1);                                                                                                    // 0.0
/*82 */     return -1;                                                                                                            // 0.0
/*84 */ }                                                                                                                         // 0.0
