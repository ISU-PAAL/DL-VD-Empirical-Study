// commit message FFmpeg@042ef4b720 (target=1, prob=0.26080054, correct=False): Precompute a chroma_qp table with index offset for each pps, this saves speed for the upcoming secondqp fix. Patch by Andreas Öman % andreas A olebyn P nu % Original thread: Date: Jun 26, 2007 8:48 PM subject: [FFmpeg-devel] Color corruption and seeking errors with H264 disc sources
/*0   */ static int decode_mb_cavlc(H264Context *h){                                                                                                                    // (14) 0.03136
/*2   */     MpegEncContext * const s = &h->s;                                                                                                                          // (15) 0.03122
/*4   */     const int mb_xy= s->mb_x + s->mb_y*s->mb_stride;                                                                                                           // (6) 0.05659
/*6   */     int partition_count;                                                                                                                                       // (19) 0.01636
/*8   */     unsigned int mb_type, cbp;                                                                                                                                 // (17) 0.02538
/*10  */     int dct8x8_allowed= h->pps.transform_8x8_mode;                                                                                                             // (9) 0.04683
/*14  */     s->dsp.clear_blocks(h->mb); //FIXME avoid if already clear (move after skip handlong?                                                                      // (4) 0.05853
/*18  */     tprintf(s->avctx, "pic:%d mb:%d/%d\n", h->frame_num, s->mb_x, s->mb_y);                                                                                    // (1) 0.08782
/*20  */     cbp = 0; /* avoid warning. FIXME: find a solution without slowing                                                                                          // (10) 0.03903
/*22  */                 down the code */                                                                                                                               // (12) 0.03708
/*24  */     if(h->slice_type != I_TYPE && h->slice_type != SI_TYPE){                                                                                                   // (8) 0.04889
/*26  */         if(s->mb_skip_run==-1)                                                                                                                                 // (11) 0.03901
/*28  */             s->mb_skip_run= get_ue_golomb(&s->gb);                                                                                                             // (3) 0.06049
/*32  */         if (s->mb_skip_run--) {                                                                                                                                // (13) 0.03706
/*34  */             if(FRAME_MBAFF && (s->mb_y&1) == 0){                                                                                                               // (2) 0.06243
/*36  */                 if(s->mb_skip_run==0)                                                                                                                          // (7) 0.05267
/*38  */                     h->mb_mbaff = h->mb_field_decoding_flag = get_bits1(&s->gb);                                                                               // (0) 0.08973
/*40  */                 else                                                                                                                                           // (16) 0.03121
/*42  */                     predict_field_decoding_flag(h);                                                                                                            // (5) 0.05852
/*44  */             }                                                                                                                                                  // (18) 0.02341
/*46  */             decode_mb_skip(h);                                                                                                                                 // 0.0
/*48  */             return 0;                                                                                                                                          // 0.0
/*50  */         }                                                                                                                                                      // 0.0
/*52  */     }                                                                                                                                                          // 0.0
/*54  */     if(FRAME_MBAFF){                                                                                                                                           // 0.0
/*56  */         if( (s->mb_y&1) == 0 )                                                                                                                                 // 0.0
/*58  */             h->mb_mbaff = h->mb_field_decoding_flag = get_bits1(&s->gb);                                                                                       // 0.0
/*60  */     }else                                                                                                                                                      // 0.0
/*62  */         h->mb_field_decoding_flag= (s->picture_structure!=PICT_FRAME);                                                                                         // 0.0
/*66  */     h->prev_mb_skipped= 0;                                                                                                                                     // 0.0
/*70  */     mb_type= get_ue_golomb(&s->gb);                                                                                                                            // 0.0
/*72  */     if(h->slice_type == B_TYPE){                                                                                                                               // 0.0
/*74  */         if(mb_type < 23){                                                                                                                                      // 0.0
/*76  */             partition_count= b_mb_type_info[mb_type].partition_count;                                                                                          // 0.0
/*78  */             mb_type=         b_mb_type_info[mb_type].type;                                                                                                     // 0.0
/*80  */         }else{                                                                                                                                                 // 0.0
/*82  */             mb_type -= 23;                                                                                                                                     // 0.0
/*84  */             goto decode_intra_mb;                                                                                                                              // 0.0
/*86  */         }                                                                                                                                                      // 0.0
/*88  */     }else if(h->slice_type == P_TYPE /*|| h->slice_type == SP_TYPE */){                                                                                        // 0.0
/*90  */         if(mb_type < 5){                                                                                                                                       // 0.0
/*92  */             partition_count= p_mb_type_info[mb_type].partition_count;                                                                                          // 0.0
/*94  */             mb_type=         p_mb_type_info[mb_type].type;                                                                                                     // 0.0
/*96  */         }else{                                                                                                                                                 // 0.0
/*98  */             mb_type -= 5;                                                                                                                                      // 0.0
/*100 */             goto decode_intra_mb;                                                                                                                              // 0.0
/*102 */         }                                                                                                                                                      // 0.0
/*104 */     }else{                                                                                                                                                     // 0.0
/*106 */        assert(h->slice_type == I_TYPE);                                                                                                                        // 0.0
/*108 */ decode_intra_mb:                                                                                                                                               // 0.0
/*110 */         if(mb_type > 25){                                                                                                                                      // 0.0
/*112 */             av_log(h->s.avctx, AV_LOG_ERROR, "mb_type %d in %c slice too large at %d %d\n", mb_type, av_get_pict_type_char(h->slice_type), s->mb_x, s->mb_y);  // 0.0
/*114 */             return -1;                                                                                                                                         // 0.0
/*116 */         }                                                                                                                                                      // 0.0
/*118 */         partition_count=0;                                                                                                                                     // 0.0
/*120 */         cbp= i_mb_type_info[mb_type].cbp;                                                                                                                      // 0.0
/*122 */         h->intra16x16_pred_mode= i_mb_type_info[mb_type].pred_mode;                                                                                            // 0.0
/*124 */         mb_type= i_mb_type_info[mb_type].type;                                                                                                                 // 0.0
/*126 */     }                                                                                                                                                          // 0.0
/*130 */     if(MB_FIELD)                                                                                                                                               // 0.0
/*132 */         mb_type |= MB_TYPE_INTERLACED;                                                                                                                         // 0.0
/*136 */     h->slice_table[ mb_xy ]= h->slice_num;                                                                                                                     // 0.0
/*140 */     if(IS_INTRA_PCM(mb_type)){                                                                                                                                 // 0.0
/*142 */         unsigned int x, y;                                                                                                                                     // 0.0
/*146 */         // We assume these blocks are very rare so we do not optimize it.                                                                                      // 0.0
/*148 */         align_get_bits(&s->gb);                                                                                                                                // 0.0
/*152 */         // The pixels are stored in the same order as levels in h->mb array.                                                                                   // 0.0
/*154 */         for(y=0; y<16; y++){                                                                                                                                   // 0.0
/*156 */             const int index= 4*(y&3) + 32*((y>>2)&1) + 128*(y>>3);                                                                                             // 0.0
/*158 */             for(x=0; x<16; x++){                                                                                                                               // 0.0
/*160 */                 tprintf(s->avctx, "LUMA ICPM LEVEL (%3d)\n", show_bits(&s->gb, 8));                                                                            // 0.0
/*162 */                 h->mb[index + (x&3) + 16*((x>>2)&1) + 64*(x>>3)]= get_bits(&s->gb, 8);                                                                         // 0.0
/*164 */             }                                                                                                                                                  // 0.0
/*166 */         }                                                                                                                                                      // 0.0
/*168 */         for(y=0; y<8; y++){                                                                                                                                    // 0.0
/*170 */             const int index= 256 + 4*(y&3) + 32*(y>>2);                                                                                                        // 0.0
/*172 */             for(x=0; x<8; x++){                                                                                                                                // 0.0
/*174 */                 tprintf(s->avctx, "CHROMA U ICPM LEVEL (%3d)\n", show_bits(&s->gb, 8));                                                                        // 0.0
/*176 */                 h->mb[index + (x&3) + 16*(x>>2)]= get_bits(&s->gb, 8);                                                                                         // 0.0
/*178 */             }                                                                                                                                                  // 0.0
/*180 */         }                                                                                                                                                      // 0.0
/*182 */         for(y=0; y<8; y++){                                                                                                                                    // 0.0
/*184 */             const int index= 256 + 64 + 4*(y&3) + 32*(y>>2);                                                                                                   // 0.0
/*186 */             for(x=0; x<8; x++){                                                                                                                                // 0.0
/*188 */                 tprintf(s->avctx, "CHROMA V ICPM LEVEL (%3d)\n", show_bits(&s->gb, 8));                                                                        // 0.0
/*190 */                 h->mb[index + (x&3) + 16*(x>>2)]= get_bits(&s->gb, 8);                                                                                         // 0.0
/*192 */             }                                                                                                                                                  // 0.0
/*194 */         }                                                                                                                                                      // 0.0
/*198 */         // In deblocking, the quantizer is 0                                                                                                                   // 0.0
/*200 */         s->current_picture.qscale_table[mb_xy]= 0;                                                                                                             // 0.0
/*202 */         h->chroma_qp = get_chroma_qp(h->pps.chroma_qp_index_offset, 0);                                                                                        // 0.0
/*204 */         // All coeffs are present                                                                                                                              // 0.0
/*206 */         memset(h->non_zero_count[mb_xy], 16, 16);                                                                                                              // 0.0
/*210 */         s->current_picture.mb_type[mb_xy]= mb_type;                                                                                                            // 0.0
/*212 */         return 0;                                                                                                                                              // 0.0
/*214 */     }                                                                                                                                                          // 0.0
/*218 */     if(MB_MBAFF){                                                                                                                                              // 0.0
/*220 */         h->ref_count[0] <<= 1;                                                                                                                                 // 0.0
/*222 */         h->ref_count[1] <<= 1;                                                                                                                                 // 0.0
/*224 */     }                                                                                                                                                          // 0.0
/*228 */     fill_caches(h, mb_type, 0);                                                                                                                                // 0.0
/*232 */     //mb_pred                                                                                                                                                  // 0.0
/*234 */     if(IS_INTRA(mb_type)){                                                                                                                                     // 0.0
/*236 */             int pred_mode;                                                                                                                                     // 0.0
/*238 */ //            init_top_left_availability(h);                                                                                                                   // 0.0
/*240 */             if(IS_INTRA4x4(mb_type)){                                                                                                                          // 0.0
/*242 */                 int i;                                                                                                                                         // 0.0
/*244 */                 int di = 1;                                                                                                                                    // 0.0
/*246 */                 if(dct8x8_allowed && get_bits1(&s->gb)){                                                                                                       // 0.0
/*248 */                     mb_type |= MB_TYPE_8x8DCT;                                                                                                                 // 0.0
/*250 */                     di = 4;                                                                                                                                    // 0.0
/*252 */                 }                                                                                                                                              // 0.0
/*256 */ //                fill_intra4x4_pred_table(h);                                                                                                                 // 0.0
/*258 */                 for(i=0; i<16; i+=di){                                                                                                                         // 0.0
/*260 */                     int mode= pred_intra_mode(h, i);                                                                                                           // 0.0
/*264 */                     if(!get_bits1(&s->gb)){                                                                                                                    // 0.0
/*266 */                         const int rem_mode= get_bits(&s->gb, 3);                                                                                               // 0.0
/*268 */                         mode = rem_mode + (rem_mode >= mode);                                                                                                  // 0.0
/*270 */                     }                                                                                                                                          // 0.0
/*274 */                     if(di==4)                                                                                                                                  // 0.0
/*276 */                         fill_rectangle( &h->intra4x4_pred_mode_cache[ scan8[i] ], 2, 2, 8, mode, 1 );                                                          // 0.0
/*278 */                     else                                                                                                                                       // 0.0
/*280 */                         h->intra4x4_pred_mode_cache[ scan8[i] ] = mode;                                                                                        // 0.0
/*282 */                 }                                                                                                                                              // 0.0
/*284 */                 write_back_intra_pred_mode(h);                                                                                                                 // 0.0
/*286 */                 if( check_intra4x4_pred_mode(h) < 0)                                                                                                           // 0.0
/*288 */                     return -1;                                                                                                                                 // 0.0
/*290 */             }else{                                                                                                                                             // 0.0
/*292 */                 h->intra16x16_pred_mode= check_intra_pred_mode(h, h->intra16x16_pred_mode);                                                                    // 0.0
/*294 */                 if(h->intra16x16_pred_mode < 0)                                                                                                                // 0.0
/*296 */                     return -1;                                                                                                                                 // 0.0
/*298 */             }                                                                                                                                                  // 0.0
/*302 */             pred_mode= check_intra_pred_mode(h, get_ue_golomb(&s->gb));                                                                                        // 0.0
/*304 */             if(pred_mode < 0)                                                                                                                                  // 0.0
/*306 */                 return -1;                                                                                                                                     // 0.0
/*308 */             h->chroma_pred_mode= pred_mode;                                                                                                                    // 0.0
/*310 */     }else if(partition_count==4){                                                                                                                              // 0.0
/*312 */         int i, j, sub_partition_count[4], list, ref[2][4];                                                                                                     // 0.0
/*316 */         if(h->slice_type == B_TYPE){                                                                                                                           // 0.0
/*318 */             for(i=0; i<4; i++){                                                                                                                                // 0.0
/*320 */                 h->sub_mb_type[i]= get_ue_golomb(&s->gb);                                                                                                      // 0.0
/*322 */                 if(h->sub_mb_type[i] >=13){                                                                                                                    // 0.0
/*324 */                     av_log(h->s.avctx, AV_LOG_ERROR, "B sub_mb_type %u out of range at %d %d\n", h->sub_mb_type[i], s->mb_x, s->mb_y);                         // 0.0
/*326 */                     return -1;                                                                                                                                 // 0.0
/*328 */                 }                                                                                                                                              // 0.0
/*330 */                 sub_partition_count[i]= b_sub_mb_type_info[ h->sub_mb_type[i] ].partition_count;                                                               // 0.0
/*332 */                 h->sub_mb_type[i]=      b_sub_mb_type_info[ h->sub_mb_type[i] ].type;                                                                          // 0.0
/*334 */             }                                                                                                                                                  // 0.0
/*336 */             if(   IS_DIRECT(h->sub_mb_type[0]) || IS_DIRECT(h->sub_mb_type[1])                                                                                 // 0.0
/*338 */                || IS_DIRECT(h->sub_mb_type[2]) || IS_DIRECT(h->sub_mb_type[3])) {                                                                              // 0.0
/*340 */                 pred_direct_motion(h, &mb_type);                                                                                                               // 0.0
/*342 */                 h->ref_cache[0][scan8[4]] =                                                                                                                    // 0.0
/*344 */                 h->ref_cache[1][scan8[4]] =                                                                                                                    // 0.0
/*346 */                 h->ref_cache[0][scan8[12]] =                                                                                                                   // 0.0
/*348 */                 h->ref_cache[1][scan8[12]] = PART_NOT_AVAILABLE;                                                                                               // 0.0
/*350 */             }                                                                                                                                                  // 0.0
/*352 */         }else{                                                                                                                                                 // 0.0
/*354 */             assert(h->slice_type == P_TYPE || h->slice_type == SP_TYPE); //FIXME SP correct ?                                                                  // 0.0
/*356 */             for(i=0; i<4; i++){                                                                                                                                // 0.0
/*358 */                 h->sub_mb_type[i]= get_ue_golomb(&s->gb);                                                                                                      // 0.0
/*360 */                 if(h->sub_mb_type[i] >=4){                                                                                                                     // 0.0
/*362 */                     av_log(h->s.avctx, AV_LOG_ERROR, "P sub_mb_type %u out of range at %d %d\n", h->sub_mb_type[i], s->mb_x, s->mb_y);                         // 0.0
/*364 */                     return -1;                                                                                                                                 // 0.0
/*366 */                 }                                                                                                                                              // 0.0
/*368 */                 sub_partition_count[i]= p_sub_mb_type_info[ h->sub_mb_type[i] ].partition_count;                                                               // 0.0
/*370 */                 h->sub_mb_type[i]=      p_sub_mb_type_info[ h->sub_mb_type[i] ].type;                                                                          // 0.0
/*372 */             }                                                                                                                                                  // 0.0
/*374 */         }                                                                                                                                                      // 0.0
/*378 */         for(list=0; list<h->list_count; list++){                                                                                                               // 0.0
/*380 */             int ref_count= IS_REF0(mb_type) ? 1 : h->ref_count[list];                                                                                          // 0.0
/*382 */             for(i=0; i<4; i++){                                                                                                                                // 0.0
/*384 */                 if(IS_DIRECT(h->sub_mb_type[i])) continue;                                                                                                     // 0.0
/*386 */                 if(IS_DIR(h->sub_mb_type[i], 0, list)){                                                                                                        // 0.0
/*388 */                     unsigned int tmp = get_te0_golomb(&s->gb, ref_count); //FIXME init to 0 before and skip?                                                   // 0.0
/*390 */                     if(tmp>=ref_count){                                                                                                                        // 0.0
/*392 */                         av_log(h->s.avctx, AV_LOG_ERROR, "ref %u overflow\n", tmp);                                                                            // 0.0
/*394 */                         return -1;                                                                                                                             // 0.0
/*396 */                     }                                                                                                                                          // 0.0
/*398 */                     ref[list][i]= tmp;                                                                                                                         // 0.0
/*400 */                 }else{                                                                                                                                         // 0.0
/*402 */                  //FIXME                                                                                                                                       // 0.0
/*404 */                     ref[list][i] = -1;                                                                                                                         // 0.0
/*406 */                 }                                                                                                                                              // 0.0
/*408 */             }                                                                                                                                                  // 0.0
/*410 */         }                                                                                                                                                      // 0.0
/*414 */         if(dct8x8_allowed)                                                                                                                                     // 0.0
/*416 */             dct8x8_allowed = get_dct8x8_allowed(h);                                                                                                            // 0.0
/*420 */         for(list=0; list<h->list_count; list++){                                                                                                               // 0.0
/*422 */             for(i=0; i<4; i++){                                                                                                                                // 0.0
/*424 */                 if(IS_DIRECT(h->sub_mb_type[i])) {                                                                                                             // 0.0
/*426 */                     h->ref_cache[list][ scan8[4*i] ] = h->ref_cache[list][ scan8[4*i]+1 ];                                                                     // 0.0
/*428 */                     continue;                                                                                                                                  // 0.0
/*430 */                 }                                                                                                                                              // 0.0
/*432 */                 h->ref_cache[list][ scan8[4*i]   ]=h->ref_cache[list][ scan8[4*i]+1 ]=                                                                         // 0.0
/*434 */                 h->ref_cache[list][ scan8[4*i]+8 ]=h->ref_cache[list][ scan8[4*i]+9 ]= ref[list][i];                                                           // 0.0
/*438 */                 if(IS_DIR(h->sub_mb_type[i], 0, list)){                                                                                                        // 0.0
/*440 */                     const int sub_mb_type= h->sub_mb_type[i];                                                                                                  // 0.0
/*442 */                     const int block_width= (sub_mb_type & (MB_TYPE_16x16|MB_TYPE_16x8)) ? 2 : 1;                                                               // 0.0
/*444 */                     for(j=0; j<sub_partition_count[i]; j++){                                                                                                   // 0.0
/*446 */                         int mx, my;                                                                                                                            // 0.0
/*448 */                         const int index= 4*i + block_width*j;                                                                                                  // 0.0
/*450 */                         int16_t (* mv_cache)[2]= &h->mv_cache[list][ scan8[index] ];                                                                           // 0.0
/*452 */                         pred_motion(h, index, block_width, list, h->ref_cache[list][ scan8[index] ], &mx, &my);                                                // 0.0
/*454 */                         mx += get_se_golomb(&s->gb);                                                                                                           // 0.0
/*456 */                         my += get_se_golomb(&s->gb);                                                                                                           // 0.0
/*458 */                         tprintf(s->avctx, "final mv:%d %d\n", mx, my);                                                                                         // 0.0
/*462 */                         if(IS_SUB_8X8(sub_mb_type)){                                                                                                           // 0.0
/*464 */                             mv_cache[ 1 ][0]=                                                                                                                  // 0.0
/*466 */                             mv_cache[ 8 ][0]= mv_cache[ 9 ][0]= mx;                                                                                            // 0.0
/*468 */                             mv_cache[ 1 ][1]=                                                                                                                  // 0.0
/*470 */                             mv_cache[ 8 ][1]= mv_cache[ 9 ][1]= my;                                                                                            // 0.0
/*472 */                         }else if(IS_SUB_8X4(sub_mb_type)){                                                                                                     // 0.0
/*474 */                             mv_cache[ 1 ][0]= mx;                                                                                                              // 0.0
/*476 */                             mv_cache[ 1 ][1]= my;                                                                                                              // 0.0
/*478 */                         }else if(IS_SUB_4X8(sub_mb_type)){                                                                                                     // 0.0
/*480 */                             mv_cache[ 8 ][0]= mx;                                                                                                              // 0.0
/*482 */                             mv_cache[ 8 ][1]= my;                                                                                                              // 0.0
/*484 */                         }                                                                                                                                      // 0.0
/*486 */                         mv_cache[ 0 ][0]= mx;                                                                                                                  // 0.0
/*488 */                         mv_cache[ 0 ][1]= my;                                                                                                                  // 0.0
/*490 */                     }                                                                                                                                          // 0.0
/*492 */                 }else{                                                                                                                                         // 0.0
/*494 */                     uint32_t *p= (uint32_t *)&h->mv_cache[list][ scan8[4*i] ][0];                                                                              // 0.0
/*496 */                     p[0] = p[1]=                                                                                                                               // 0.0
/*498 */                     p[8] = p[9]= 0;                                                                                                                            // 0.0
/*500 */                 }                                                                                                                                              // 0.0
/*502 */             }                                                                                                                                                  // 0.0
/*504 */         }                                                                                                                                                      // 0.0
/*506 */     }else if(IS_DIRECT(mb_type)){                                                                                                                              // 0.0
/*508 */         pred_direct_motion(h, &mb_type);                                                                                                                       // 0.0
/*510 */         dct8x8_allowed &= h->sps.direct_8x8_inference_flag;                                                                                                    // 0.0
/*512 */     }else{                                                                                                                                                     // 0.0
/*514 */         int list, mx, my, i;                                                                                                                                   // 0.0
/*516 */          //FIXME we should set ref_idx_l? to 0 if we use that later ...                                                                                        // 0.0
/*518 */         if(IS_16X16(mb_type)){                                                                                                                                 // 0.0
/*520 */             for(list=0; list<h->list_count; list++){                                                                                                           // 0.0
/*522 */                     unsigned int val;                                                                                                                          // 0.0
/*524 */                     if(IS_DIR(mb_type, 0, list)){                                                                                                              // 0.0
/*526 */                         val= get_te0_golomb(&s->gb, h->ref_count[list]);                                                                                       // 0.0
/*528 */                         if(val >= h->ref_count[list]){                                                                                                         // 0.0
/*530 */                             av_log(h->s.avctx, AV_LOG_ERROR, "ref %u overflow\n", val);                                                                        // 0.0
/*532 */                             return -1;                                                                                                                         // 0.0
/*534 */                         }                                                                                                                                      // 0.0
/*536 */                     }else                                                                                                                                      // 0.0
/*538 */                         val= LIST_NOT_USED&0xFF;                                                                                                               // 0.0
/*540 */                     fill_rectangle(&h->ref_cache[list][ scan8[0] ], 4, 4, 8, val, 1);                                                                          // 0.0
/*542 */             }                                                                                                                                                  // 0.0
/*544 */             for(list=0; list<h->list_count; list++){                                                                                                           // 0.0
/*546 */                 unsigned int val;                                                                                                                              // 0.0
/*548 */                 if(IS_DIR(mb_type, 0, list)){                                                                                                                  // 0.0
/*550 */                     pred_motion(h, 0, 4, list, h->ref_cache[list][ scan8[0] ], &mx, &my);                                                                      // 0.0
/*552 */                     mx += get_se_golomb(&s->gb);                                                                                                               // 0.0
/*554 */                     my += get_se_golomb(&s->gb);                                                                                                               // 0.0
/*556 */                     tprintf(s->avctx, "final mv:%d %d\n", mx, my);                                                                                             // 0.0
/*560 */                     val= pack16to32(mx,my);                                                                                                                    // 0.0
/*562 */                 }else                                                                                                                                          // 0.0
/*564 */                     val=0;                                                                                                                                     // 0.0
/*566 */                 fill_rectangle(h->mv_cache[list][ scan8[0] ], 4, 4, 8, val, 4);                                                                                // 0.0
/*568 */             }                                                                                                                                                  // 0.0
/*570 */         }                                                                                                                                                      // 0.0
/*572 */         else if(IS_16X8(mb_type)){                                                                                                                             // 0.0
/*574 */             for(list=0; list<h->list_count; list++){                                                                                                           // 0.0
/*576 */                     for(i=0; i<2; i++){                                                                                                                        // 0.0
/*578 */                         unsigned int val;                                                                                                                      // 0.0
/*580 */                         if(IS_DIR(mb_type, i, list)){                                                                                                          // 0.0
/*582 */                             val= get_te0_golomb(&s->gb, h->ref_count[list]);                                                                                   // 0.0
/*584 */                             if(val >= h->ref_count[list]){                                                                                                     // 0.0
/*586 */                                 av_log(h->s.avctx, AV_LOG_ERROR, "ref %u overflow\n", val);                                                                    // 0.0
/*588 */                                 return -1;                                                                                                                     // 0.0
/*590 */                             }                                                                                                                                  // 0.0
/*592 */                         }else                                                                                                                                  // 0.0
/*594 */                             val= LIST_NOT_USED&0xFF;                                                                                                           // 0.0
/*596 */                         fill_rectangle(&h->ref_cache[list][ scan8[0] + 16*i ], 4, 2, 8, val, 1);                                                               // 0.0
/*598 */                     }                                                                                                                                          // 0.0
/*600 */             }                                                                                                                                                  // 0.0
/*602 */             for(list=0; list<h->list_count; list++){                                                                                                           // 0.0
/*604 */                 for(i=0; i<2; i++){                                                                                                                            // 0.0
/*606 */                     unsigned int val;                                                                                                                          // 0.0
/*608 */                     if(IS_DIR(mb_type, i, list)){                                                                                                              // 0.0
/*610 */                         pred_16x8_motion(h, 8*i, list, h->ref_cache[list][scan8[0] + 16*i], &mx, &my);                                                         // 0.0
/*612 */                         mx += get_se_golomb(&s->gb);                                                                                                           // 0.0
/*614 */                         my += get_se_golomb(&s->gb);                                                                                                           // 0.0
/*616 */                         tprintf(s->avctx, "final mv:%d %d\n", mx, my);                                                                                         // 0.0
/*620 */                         val= pack16to32(mx,my);                                                                                                                // 0.0
/*622 */                     }else                                                                                                                                      // 0.0
/*624 */                         val=0;                                                                                                                                 // 0.0
/*626 */                     fill_rectangle(h->mv_cache[list][ scan8[0] + 16*i ], 4, 2, 8, val, 4);                                                                     // 0.0
/*628 */                 }                                                                                                                                              // 0.0
/*630 */             }                                                                                                                                                  // 0.0
/*632 */         }else{                                                                                                                                                 // 0.0
/*634 */             assert(IS_8X16(mb_type));                                                                                                                          // 0.0
/*636 */             for(list=0; list<h->list_count; list++){                                                                                                           // 0.0
/*638 */                     for(i=0; i<2; i++){                                                                                                                        // 0.0
/*640 */                         unsigned int val;                                                                                                                      // 0.0
/*642 */                         if(IS_DIR(mb_type, i, list)){ //FIXME optimize                                                                                         // 0.0
/*644 */                             val= get_te0_golomb(&s->gb, h->ref_count[list]);                                                                                   // 0.0
/*646 */                             if(val >= h->ref_count[list]){                                                                                                     // 0.0
/*648 */                                 av_log(h->s.avctx, AV_LOG_ERROR, "ref %u overflow\n", val);                                                                    // 0.0
/*650 */                                 return -1;                                                                                                                     // 0.0
/*652 */                             }                                                                                                                                  // 0.0
/*654 */                         }else                                                                                                                                  // 0.0
/*656 */                             val= LIST_NOT_USED&0xFF;                                                                                                           // 0.0
/*658 */                         fill_rectangle(&h->ref_cache[list][ scan8[0] + 2*i ], 2, 4, 8, val, 1);                                                                // 0.0
/*660 */                     }                                                                                                                                          // 0.0
/*662 */             }                                                                                                                                                  // 0.0
/*664 */             for(list=0; list<h->list_count; list++){                                                                                                           // 0.0
/*666 */                 for(i=0; i<2; i++){                                                                                                                            // 0.0
/*668 */                     unsigned int val;                                                                                                                          // 0.0
/*670 */                     if(IS_DIR(mb_type, i, list)){                                                                                                              // 0.0
/*672 */                         pred_8x16_motion(h, i*4, list, h->ref_cache[list][ scan8[0] + 2*i ], &mx, &my);                                                        // 0.0
/*674 */                         mx += get_se_golomb(&s->gb);                                                                                                           // 0.0
/*676 */                         my += get_se_golomb(&s->gb);                                                                                                           // 0.0
/*678 */                         tprintf(s->avctx, "final mv:%d %d\n", mx, my);                                                                                         // 0.0
/*682 */                         val= pack16to32(mx,my);                                                                                                                // 0.0
/*684 */                     }else                                                                                                                                      // 0.0
/*686 */                         val=0;                                                                                                                                 // 0.0
/*688 */                     fill_rectangle(h->mv_cache[list][ scan8[0] + 2*i ], 2, 4, 8, val, 4);                                                                      // 0.0
/*690 */                 }                                                                                                                                              // 0.0
/*692 */             }                                                                                                                                                  // 0.0
/*694 */         }                                                                                                                                                      // 0.0
/*696 */     }                                                                                                                                                          // 0.0
/*700 */     if(IS_INTER(mb_type))                                                                                                                                      // 0.0
/*702 */         write_back_motion(h, mb_type);                                                                                                                         // 0.0
/*706 */     if(!IS_INTRA16x16(mb_type)){                                                                                                                               // 0.0
/*708 */         cbp= get_ue_golomb(&s->gb);                                                                                                                            // 0.0
/*710 */         if(cbp > 47){                                                                                                                                          // 0.0
/*712 */             av_log(h->s.avctx, AV_LOG_ERROR, "cbp too large (%u) at %d %d\n", cbp, s->mb_x, s->mb_y);                                                          // 0.0
/*714 */             return -1;                                                                                                                                         // 0.0
/*716 */         }                                                                                                                                                      // 0.0
/*720 */         if(IS_INTRA4x4(mb_type))                                                                                                                               // 0.0
/*722 */             cbp= golomb_to_intra4x4_cbp[cbp];                                                                                                                  // 0.0
/*724 */         else                                                                                                                                                   // 0.0
/*726 */             cbp= golomb_to_inter_cbp[cbp];                                                                                                                     // 0.0
/*728 */     }                                                                                                                                                          // 0.0
/*730 */     h->cbp = cbp;                                                                                                                                              // 0.0
/*734 */     if(dct8x8_allowed && (cbp&15) && !IS_INTRA(mb_type)){                                                                                                      // 0.0
/*736 */         if(get_bits1(&s->gb))                                                                                                                                  // 0.0
/*738 */             mb_type |= MB_TYPE_8x8DCT;                                                                                                                         // 0.0
/*740 */     }                                                                                                                                                          // 0.0
/*742 */     s->current_picture.mb_type[mb_xy]= mb_type;                                                                                                                // 0.0
/*746 */     if(cbp || IS_INTRA16x16(mb_type)){                                                                                                                         // 0.0
/*748 */         int i8x8, i4x4, chroma_idx;                                                                                                                            // 0.0
/*750 */         int chroma_qp, dquant;                                                                                                                                 // 0.0
/*752 */         GetBitContext *gb= IS_INTRA(mb_type) ? h->intra_gb_ptr : h->inter_gb_ptr;                                                                              // 0.0
/*754 */         const uint8_t *scan, *scan8x8, *dc_scan;                                                                                                               // 0.0
/*758 */ //        fill_non_zero_count_cache(h);                                                                                                                        // 0.0
/*762 */         if(IS_INTERLACED(mb_type)){                                                                                                                            // 0.0
/*764 */             scan8x8= s->qscale ? h->field_scan8x8_cavlc : h->field_scan8x8_cavlc_q0;                                                                           // 0.0
/*766 */             scan= s->qscale ? h->field_scan : h->field_scan_q0;                                                                                                // 0.0
/*768 */             dc_scan= luma_dc_field_scan;                                                                                                                       // 0.0
/*770 */         }else{                                                                                                                                                 // 0.0
/*772 */             scan8x8= s->qscale ? h->zigzag_scan8x8_cavlc : h->zigzag_scan8x8_cavlc_q0;                                                                         // 0.0
/*774 */             scan= s->qscale ? h->zigzag_scan : h->zigzag_scan_q0;                                                                                              // 0.0
/*776 */             dc_scan= luma_dc_zigzag_scan;                                                                                                                      // 0.0
/*778 */         }                                                                                                                                                      // 0.0
/*782 */         dquant= get_se_golomb(&s->gb);                                                                                                                         // 0.0
/*786 */         if( dquant > 25 || dquant < -26 ){                                                                                                                     // 0.0
/*788 */             av_log(h->s.avctx, AV_LOG_ERROR, "dquant out of range (%d) at %d %d\n", dquant, s->mb_x, s->mb_y);                                                 // 0.0
/*790 */             return -1;                                                                                                                                         // 0.0
/*792 */         }                                                                                                                                                      // 0.0
/*796 */         s->qscale += dquant;                                                                                                                                   // 0.0
/*798 */         if(((unsigned)s->qscale) > 51){                                                                                                                        // 0.0
/*800 */             if(s->qscale<0) s->qscale+= 52;                                                                                                                    // 0.0
/*802 */             else            s->qscale-= 52;                                                                                                                    // 0.0
/*804 */         }                                                                                                                                                      // 0.0
/*808 */         h->chroma_qp= chroma_qp= get_chroma_qp(h->pps.chroma_qp_index_offset, s->qscale);                                                                      // 0.0
/*810 */         if(IS_INTRA16x16(mb_type)){                                                                                                                            // 0.0
/*812 */             if( decode_residual(h, h->intra_gb_ptr, h->mb, LUMA_DC_BLOCK_INDEX, dc_scan, h->dequant4_coeff[0][s->qscale], 16) < 0){                            // 0.0
/*814 */                 return -1; //FIXME continue if partitioned and other return -1 too                                                                             // 0.0
/*816 */             }                                                                                                                                                  // 0.0
/*820 */             assert((cbp&15) == 0 || (cbp&15) == 15);                                                                                                           // 0.0
/*824 */             if(cbp&15){                                                                                                                                        // 0.0
/*826 */                 for(i8x8=0; i8x8<4; i8x8++){                                                                                                                   // 0.0
/*828 */                     for(i4x4=0; i4x4<4; i4x4++){                                                                                                               // 0.0
/*830 */                         const int index= i4x4 + 4*i8x8;                                                                                                        // 0.0
/*832 */                         if( decode_residual(h, h->intra_gb_ptr, h->mb + 16*index, index, scan + 1, h->dequant4_coeff[0][s->qscale], 15) < 0 ){                 // 0.0
/*834 */                             return -1;                                                                                                                         // 0.0
/*836 */                         }                                                                                                                                      // 0.0
/*838 */                     }                                                                                                                                          // 0.0
/*840 */                 }                                                                                                                                              // 0.0
/*842 */             }else{                                                                                                                                             // 0.0
/*844 */                 fill_rectangle(&h->non_zero_count_cache[scan8[0]], 4, 4, 8, 0, 1);                                                                             // 0.0
/*846 */             }                                                                                                                                                  // 0.0
/*848 */         }else{                                                                                                                                                 // 0.0
/*850 */             for(i8x8=0; i8x8<4; i8x8++){                                                                                                                       // 0.0
/*852 */                 if(cbp & (1<<i8x8)){                                                                                                                           // 0.0
/*854 */                     if(IS_8x8DCT(mb_type)){                                                                                                                    // 0.0
/*856 */                         DCTELEM *buf = &h->mb[64*i8x8];                                                                                                        // 0.0
/*858 */                         uint8_t *nnz;                                                                                                                          // 0.0
/*860 */                         for(i4x4=0; i4x4<4; i4x4++){                                                                                                           // 0.0
/*862 */                             if( decode_residual(h, gb, buf, i4x4+4*i8x8, scan8x8+16*i4x4,                                                                      // 0.0
/*864 */                                                 h->dequant8_coeff[IS_INTRA( mb_type ) ? 0:1][s->qscale], 16) <0 )                                              // 0.0
/*866 */                                 return -1;                                                                                                                     // 0.0
/*868 */                         }                                                                                                                                      // 0.0
/*870 */                         nnz= &h->non_zero_count_cache[ scan8[4*i8x8] ];                                                                                        // 0.0
/*872 */                         nnz[0] += nnz[1] + nnz[8] + nnz[9];                                                                                                    // 0.0
/*874 */                     }else{                                                                                                                                     // 0.0
/*876 */                         for(i4x4=0; i4x4<4; i4x4++){                                                                                                           // 0.0
/*878 */                             const int index= i4x4 + 4*i8x8;                                                                                                    // 0.0
/*882 */                             if( decode_residual(h, gb, h->mb + 16*index, index, scan, h->dequant4_coeff[IS_INTRA( mb_type ) ? 0:3][s->qscale], 16) <0 ){       // 0.0
/*884 */                                 return -1;                                                                                                                     // 0.0
/*886 */                             }                                                                                                                                  // 0.0
/*888 */                         }                                                                                                                                      // 0.0
/*890 */                     }                                                                                                                                          // 0.0
/*892 */                 }else{                                                                                                                                         // 0.0
/*894 */                     uint8_t * const nnz= &h->non_zero_count_cache[ scan8[4*i8x8] ];                                                                            // 0.0
/*896 */                     nnz[0] = nnz[1] = nnz[8] = nnz[9] = 0;                                                                                                     // 0.0
/*898 */                 }                                                                                                                                              // 0.0
/*900 */             }                                                                                                                                                  // 0.0
/*902 */         }                                                                                                                                                      // 0.0
/*906 */         if(cbp&0x30){                                                                                                                                          // 0.0
/*908 */             for(chroma_idx=0; chroma_idx<2; chroma_idx++)                                                                                                      // 0.0
/*910 */                 if( decode_residual(h, gb, h->mb + 256 + 16*4*chroma_idx, CHROMA_DC_BLOCK_INDEX, chroma_dc_scan, NULL, 4) < 0){                                // 0.0
/*912 */                     return -1;                                                                                                                                 // 0.0
/*914 */                 }                                                                                                                                              // 0.0
/*916 */         }                                                                                                                                                      // 0.0
/*920 */         if(cbp&0x20){                                                                                                                                          // 0.0
/*922 */             for(chroma_idx=0; chroma_idx<2; chroma_idx++){                                                                                                     // 0.0
/*924 */                 const uint32_t *qmul = h->dequant4_coeff[chroma_idx+1+(IS_INTRA( mb_type ) ? 0:3)][chroma_qp];                                                 // 0.0
/*926 */                 for(i4x4=0; i4x4<4; i4x4++){                                                                                                                   // 0.0
/*928 */                     const int index= 16 + 4*chroma_idx + i4x4;                                                                                                 // 0.0
/*930 */                     if( decode_residual(h, gb, h->mb + 16*index, index, scan + 1, qmul, 15) < 0){                                                              // 0.0
/*932 */                         return -1;                                                                                                                             // 0.0
/*934 */                     }                                                                                                                                          // 0.0
/*936 */                 }                                                                                                                                              // 0.0
/*938 */             }                                                                                                                                                  // 0.0
/*940 */         }else{                                                                                                                                                 // 0.0
/*942 */             uint8_t * const nnz= &h->non_zero_count_cache[0];                                                                                                  // 0.0
/*944 */             nnz[ scan8[16]+0 ] = nnz[ scan8[16]+1 ] =nnz[ scan8[16]+8 ] =nnz[ scan8[16]+9 ] =                                                                  // 0.0
/*946 */             nnz[ scan8[20]+0 ] = nnz[ scan8[20]+1 ] =nnz[ scan8[20]+8 ] =nnz[ scan8[20]+9 ] = 0;                                                               // 0.0
/*948 */         }                                                                                                                                                      // 0.0
/*950 */     }else{                                                                                                                                                     // 0.0
/*952 */         uint8_t * const nnz= &h->non_zero_count_cache[0];                                                                                                      // 0.0
/*954 */         fill_rectangle(&nnz[scan8[0]], 4, 4, 8, 0, 1);                                                                                                         // 0.0
/*956 */         nnz[ scan8[16]+0 ] = nnz[ scan8[16]+1 ] =nnz[ scan8[16]+8 ] =nnz[ scan8[16]+9 ] =                                                                      // 0.0
/*958 */         nnz[ scan8[20]+0 ] = nnz[ scan8[20]+1 ] =nnz[ scan8[20]+8 ] =nnz[ scan8[20]+9 ] = 0;                                                                   // 0.0
/*960 */     }                                                                                                                                                          // 0.0
/*962 */     s->current_picture.qscale_table[mb_xy]= s->qscale;                                                                                                         // 0.0
/*964 */     write_back_non_zero_count(h);                                                                                                                              // 0.0
/*968 */     if(MB_MBAFF){                                                                                                                                              // 0.0
/*970 */         h->ref_count[0] >>= 1;                                                                                                                                 // 0.0
/*972 */         h->ref_count[1] >>= 1;                                                                                                                                 // 0.0
/*974 */     }                                                                                                                                                          // 0.0
/*978 */     return 0;                                                                                                                                                  // 0.0
/*980 */ }                                                                                                                                                              // 0.0
