// commit message FFmpeg@e13f860ac8 (target=0, prob=0.36657563, correct=True): oops
/*0   */ static int decode_vol_header(MpegEncContext *s, GetBitContext *gb){                                             // (8) 0.04102
/*2   */     int width, height, vo_ver_id;                                                                               // (19) 0.02734
/*6   */     /* vol header */                                                                                            // (21) 0.01367
/*8   */     skip_bits(gb, 1); /* random access */                                                                       // (18) 0.0293
/*10  */     s->vo_type= get_bits(gb, 8);                                                                                // (15) 0.0332
/*12  */     if (get_bits1(gb) != 0) { /* is_ol_id */                                                                    // (7) 0.04492
/*14  */         vo_ver_id = get_bits(gb, 4); /* vo_ver_id */                                                            // (3) 0.05469
/*16  */         skip_bits(gb, 3); /* vo_priority */                                                                     // (12) 0.03906
/*18  */     } else {                                                                                                    // (23) 0.01172
/*20  */         vo_ver_id = 1;                                                                                          // (17) 0.0293
/*22  */     }                                                                                                           // (24) 0.007813
/*24  */ //printf("vo type:%d\n",s->vo_type);                                                                            // (14) 0.03321
/*26  */     s->aspect_ratio_info= get_bits(gb, 4);                                                                      // (9) 0.04102
/*28  */     if(s->aspect_ratio_info == FF_ASPECT_EXTENDED){	                                                            // (2) 0.05664
/*30  */         s->aspected_width = get_bits(gb, 8); // par_width                                                       // (5) 0.05078
/*32  */         s->aspected_height = get_bits(gb, 8); // par_height                                                     // (6) 0.05078
/*34  */     }else{                                                                                                      // (22) 0.01172
/*36  */         s->aspected_width = pixel_aspect[s->aspect_ratio_info][0];                                              // (0) 0.06055
/*38  */         s->aspected_height= pixel_aspect[s->aspect_ratio_info][1];                                              // (1) 0.06055
/*40  */     }                                                                                                           // (25) 0.007812
/*44  */     if ((s->vol_control_parameters=get_bits1(gb))) { /* vol control parameter */                                // (4) 0.05273
/*46  */         int chroma_format= get_bits(gb, 2);                                                                     // (10) 0.04102
/*48  */         if(chroma_format!=1){                                                                                   // (16) 0.0332
/*50  */             printf("illegal chroma format\n");                                                                  // (11) 0.03906
/*52  */         }                                                                                                       // (20) 0.01562
/*54  */         s->low_delay= get_bits1(gb);                                                                            // (13) 0.03906
/*56  */         if(get_bits1(gb)){ /* vbv parameters */                                                                 // 0.0
/*58  */             get_bits(gb, 15);	/* first_half_bitrate */                                                          // 0.0
/*60  */             skip_bits1(gb);	/* marker */                                                                        // 0.0
/*62  */             get_bits(gb, 15);	/* latter_half_bitrate */                                                         // 0.0
/*64  */             skip_bits1(gb);	/* marker */                                                                        // 0.0
/*66  */             get_bits(gb, 15);	/* first_half_vbv_buffer_size */                                                  // 0.0
/*68  */             skip_bits1(gb);	/* marker */                                                                        // 0.0
/*70  */             get_bits(gb, 3);	/* latter_half_vbv_buffer_size */                                                  // 0.0
/*72  */             get_bits(gb, 11);	/* first_half_vbv_occupancy */                                                    // 0.0
/*74  */             skip_bits1(gb);	/* marker */                                                                        // 0.0
/*76  */             get_bits(gb, 15);	/* latter_half_vbv_occupancy */                                                   // 0.0
/*78  */             skip_bits1(gb);	/* marker */                                                                        // 0.0
/*80  */         }                                                                                                       // 0.0
/*82  */     }else{                                                                                                      // 0.0
/*84  */         // set low delay flag only once so the smart? low delay detection wont be overriden                     // 0.0
/*86  */         if(s->picture_number==0)                                                                                // 0.0
/*88  */             s->low_delay=0;                                                                                     // 0.0
/*90  */     }                                                                                                           // 0.0
/*94  */     s->shape = get_bits(gb, 2); /* vol shape */                                                                 // 0.0
/*96  */     if(s->shape != RECT_SHAPE) printf("only rectangular vol supported\n");                                      // 0.0
/*98  */     if(s->shape == GRAY_SHAPE && vo_ver_id != 1){                                                               // 0.0
/*100 */         printf("Gray shape not supported\n");                                                                   // 0.0
/*102 */         skip_bits(gb, 4);  //video_object_layer_shape_extension                                                 // 0.0
/*104 */     }                                                                                                           // 0.0
/*108 */     skip_bits1(gb);   /* marker */                                                                              // 0.0
/*110 */                                                                                                                 // (26) 0.007812
/*112 */     s->time_increment_resolution = get_bits(gb, 16);                                                            // 0.0
/*114 */                                                                                                                 // 0.0
/*116 */     s->time_increment_bits = av_log2(s->time_increment_resolution - 1) + 1;                                     // 0.0
/*118 */     if (s->time_increment_bits < 1)                                                                             // 0.0
/*120 */         s->time_increment_bits = 1;                                                                             // 0.0
/*122 */     skip_bits1(gb);   /* marker */                                                                              // 0.0
/*126 */     if (get_bits1(gb) != 0) {   /* fixed_vop_rate  */                                                           // 0.0
/*128 */         skip_bits(gb, s->time_increment_bits);                                                                  // 0.0
/*130 */     }                                                                                                           // 0.0
/*134 */     if (s->shape != BIN_ONLY_SHAPE) {                                                                           // 0.0
/*136 */         if (s->shape == RECT_SHAPE) {                                                                           // 0.0
/*138 */             skip_bits1(gb);   /* marker */                                                                      // 0.0
/*140 */             width = get_bits(gb, 13);                                                                           // 0.0
/*142 */             skip_bits1(gb);   /* marker */                                                                      // 0.0
/*144 */             height = get_bits(gb, 13);                                                                          // 0.0
/*146 */             skip_bits1(gb);   /* marker */                                                                      // 0.0
/*148 */             if(width && height){ /* they should be non zero but who knows ... */                                // 0.0
/*150 */                 s->width = width;                                                                               // 0.0
/*152 */                 s->height = height;                                                                             // 0.0
/*154 */ //                printf("width/height: %d %d\n", width, height);                                               // 0.0
/*156 */             }                                                                                                   // 0.0
/*158 */         }                                                                                                       // 0.0
/*160 */                                                                                                                 // 0.0
/*162 */         s->progressive_sequence= get_bits1(gb)^1;                                                               // 0.0
/*164 */         if(!get_bits1(gb)) printf("OBMC not supported (very likely buggy encoder)\n");   /* OBMC Disable */     // 0.0
/*166 */         if (vo_ver_id == 1) {                                                                                   // 0.0
/*168 */             s->vol_sprite_usage = get_bits1(gb); /* vol_sprite_usage */                                         // 0.0
/*170 */         } else {                                                                                                // 0.0
/*172 */             s->vol_sprite_usage = get_bits(gb, 2); /* vol_sprite_usage */                                       // 0.0
/*174 */         }                                                                                                       // 0.0
/*176 */         if(s->vol_sprite_usage==STATIC_SPRITE) printf("Static Sprites not supported\n");                        // 0.0
/*178 */         if(s->vol_sprite_usage==STATIC_SPRITE || s->vol_sprite_usage==GMC_SPRITE){                              // 0.0
/*180 */             if(s->vol_sprite_usage==STATIC_SPRITE){                                                             // 0.0
/*182 */                 s->sprite_width = get_bits(gb, 13);                                                             // 0.0
/*184 */                 skip_bits1(gb); /* marker */                                                                    // 0.0
/*186 */                 s->sprite_height= get_bits(gb, 13);                                                             // 0.0
/*188 */                 skip_bits1(gb); /* marker */                                                                    // 0.0
/*190 */                 s->sprite_left  = get_bits(gb, 13);                                                             // 0.0
/*192 */                 skip_bits1(gb); /* marker */                                                                    // 0.0
/*194 */                 s->sprite_top   = get_bits(gb, 13);                                                             // 0.0
/*196 */                 skip_bits1(gb); /* marker */                                                                    // 0.0
/*198 */             }                                                                                                   // 0.0
/*200 */             s->num_sprite_warping_points= get_bits(gb, 6);                                                      // 0.0
/*202 */             s->sprite_warping_accuracy = get_bits(gb, 2);                                                       // 0.0
/*204 */             s->sprite_brightness_change= get_bits1(gb);                                                         // 0.0
/*206 */             if(s->vol_sprite_usage==STATIC_SPRITE)                                                              // 0.0
/*208 */                 s->low_latency_sprite= get_bits1(gb);                                                           // 0.0
/*210 */         }                                                                                                       // 0.0
/*212 */         // FIXME sadct disable bit if verid!=1 && shape not rect                                                // 0.0
/*214 */                                                                                                                 // 0.0
/*216 */         if (get_bits1(gb) == 1) {   /* not_8_bit */                                                             // 0.0
/*218 */             s->quant_precision = get_bits(gb, 4); /* quant_precision */                                         // 0.0
/*220 */             if(get_bits(gb, 4)!=8) printf("N-bit not supported\n"); /* bits_per_pixel */                        // 0.0
/*222 */             if(s->quant_precision!=5) printf("quant precission %d\n", s->quant_precision);                      // 0.0
/*224 */         } else {                                                                                                // 0.0
/*226 */             s->quant_precision = 5;                                                                             // 0.0
/*228 */         }                                                                                                       // 0.0
/*230 */                                                                                                                 // 0.0
/*232 */         // FIXME a bunch of grayscale shape things                                                              // 0.0
/*236 */         if((s->mpeg_quant=get_bits1(gb))){ /* vol_quant_type */                                                 // 0.0
/*238 */             int i, v;                                                                                           // 0.0
/*240 */                                                                                                                 // 0.0
/*242 */             /* load default matrixes */                                                                         // 0.0
/*244 */             for(i=0; i<64; i++){                                                                                // 0.0
/*246 */                 int j= s->dsp.idct_permutation[i];                                                              // 0.0
/*248 */                 v= ff_mpeg4_default_intra_matrix[i];                                                            // 0.0
/*250 */                 s->intra_matrix[j]= v;                                                                          // 0.0
/*252 */                 s->chroma_intra_matrix[j]= v;                                                                   // 0.0
/*254 */                                                                                                                 // 0.0
/*256 */                 v= ff_mpeg4_default_non_intra_matrix[i];                                                        // 0.0
/*258 */                 s->inter_matrix[j]= v;                                                                          // 0.0
/*260 */                 s->chroma_inter_matrix[j]= v;                                                                   // 0.0
/*262 */             }                                                                                                   // 0.0
/*266 */             /* load custom intra matrix */                                                                      // 0.0
/*268 */             if(get_bits1(gb)){                                                                                  // 0.0
/*270 */                 int last=0;                                                                                     // 0.0
/*272 */ 		for(i=0; i<64; i++){                                                                                          // 0.0
/*274 */                     int j;                                                                                      // 0.0
/*276 */                     v= get_bits(gb, 8);                                                                         // 0.0
/*278 */                     if(v==0) break;                                                                             // 0.0
/*280 */                                                                                                                 // 0.0
/*282 */                     last= v;                                                                                    // 0.0
/*284 */                     j= s->dsp.idct_permutation[ ff_zigzag_direct[i] ];                                          // 0.0
/*286 */                     s->intra_matrix[j]= v;                                                                      // 0.0
/*288 */                     s->chroma_intra_matrix[j]= v;                                                               // 0.0
/*290 */                 }                                                                                               // 0.0
/*294 */                 /* replicate last value */                                                                      // 0.0
/*296 */                 for(; i<64; i++){                                                                               // 0.0
/*298 */ 		    int j= s->dsp.idct_permutation[ ff_zigzag_direct[i] ];                                                    // 0.0
/*300 */                     s->intra_matrix[j]= v;                                                                      // 0.0
/*302 */                     s->chroma_intra_matrix[j]= v;                                                               // 0.0
/*304 */                 }                                                                                               // 0.0
/*306 */             }                                                                                                   // 0.0
/*310 */             /* load custom non intra matrix */                                                                  // 0.0
/*312 */             if(get_bits1(gb)){                                                                                  // 0.0
/*314 */                 int last=0;                                                                                     // 0.0
/*316 */ 		for(i=0; i<64; i++){                                                                                          // 0.0
/*318 */                     int j;                                                                                      // 0.0
/*320 */                     v= get_bits(gb, 8);                                                                         // 0.0
/*322 */                     if(v==0) break;                                                                             // 0.0
/*326 */                     last= v;                                                                                    // 0.0
/*328 */                     j= s->dsp.idct_permutation[ ff_zigzag_direct[i] ];                                          // 0.0
/*330 */                     s->inter_matrix[j]= v;                                                                      // 0.0
/*332 */                     s->chroma_inter_matrix[j]= v;                                                               // 0.0
/*334 */                 }                                                                                               // 0.0
/*338 */                 /* replicate last value */                                                                      // 0.0
/*340 */                 for(; i<64; i++){                                                                               // 0.0
/*342 */ 		    int j= s->dsp.idct_permutation[ ff_zigzag_direct[i] ];                                                    // 0.0
/*344 */                     s->inter_matrix[j]= last;                                                                   // 0.0
/*346 */                     s->chroma_inter_matrix[j]= last;                                                            // 0.0
/*348 */                 }                                                                                               // 0.0
/*350 */             }                                                                                                   // 0.0
/*354 */             // FIXME a bunch of grayscale shape things                                                          // 0.0
/*356 */         }                                                                                                       // 0.0
/*360 */         if(vo_ver_id != 1)                                                                                      // 0.0
/*362 */              s->quarter_sample= get_bits1(gb);                                                                  // 0.0
/*364 */         else s->quarter_sample=0;                                                                               // 0.0
/*368 */         if(!get_bits1(gb)) printf("Complexity estimation not supported\n");                                     // 0.0
/*372 */         s->resync_marker= !get_bits1(gb); /* resync_marker_disabled */                                          // 0.0
/*376 */         s->data_partitioning= get_bits1(gb);                                                                    // 0.0
/*378 */         if(s->data_partitioning){                                                                               // 0.0
/*380 */             s->rvlc= get_bits1(gb);                                                                             // 0.0
/*382 */             if(s->rvlc){                                                                                        // 0.0
/*384 */                 printf("reversible vlc not supported\n");                                                       // 0.0
/*386 */             }                                                                                                   // 0.0
/*388 */         }                                                                                                       // 0.0
/*390 */                                                                                                                 // 0.0
/*392 */         if(vo_ver_id != 1) {                                                                                    // 0.0
/*394 */             s->new_pred= get_bits1(gb);                                                                         // 0.0
/*396 */             if(s->new_pred){                                                                                    // 0.0
/*398 */                 printf("new pred not supported\n");                                                             // 0.0
/*400 */                 skip_bits(gb, 2); /* requested upstream message type */                                         // 0.0
/*402 */                 skip_bits1(gb); /* newpred segment type */                                                      // 0.0
/*404 */             }                                                                                                   // 0.0
/*406 */             s->reduced_res_vop= get_bits1(gb);                                                                  // 0.0
/*408 */             if(s->reduced_res_vop) printf("reduced resolution VOP not supported\n");                            // 0.0
/*410 */         }                                                                                                       // 0.0
/*412 */         else{                                                                                                   // 0.0
/*414 */             s->new_pred=0;                                                                                      // 0.0
/*416 */             s->reduced_res_vop= 0;                                                                              // 0.0
/*418 */         }                                                                                                       // 0.0
/*422 */         s->scalability= get_bits1(gb);                                                                          // 0.0
/*426 */         if (s->scalability) {                                                                                   // 0.0
/*428 */             GetBitContext bak= *gb;                                                                             // 0.0
/*430 */             int ref_layer_id;                                                                                   // 0.0
/*432 */             int ref_layer_sampling_dir;                                                                         // 0.0
/*434 */             int h_sampling_factor_n;                                                                            // 0.0
/*436 */             int h_sampling_factor_m;                                                                            // 0.0
/*438 */             int v_sampling_factor_n;                                                                            // 0.0
/*440 */             int v_sampling_factor_m;                                                                            // 0.0
/*442 */                                                                                                                 // 0.0
/*444 */             s->hierachy_type= get_bits1(gb);                                                                    // 0.0
/*446 */             ref_layer_id= get_bits(gb, 4);                                                                      // 0.0
/*448 */             ref_layer_sampling_dir= get_bits1(gb);                                                              // 0.0
/*450 */             h_sampling_factor_n= get_bits(gb, 5);                                                               // 0.0
/*452 */             h_sampling_factor_m= get_bits(gb, 5);                                                               // 0.0
/*454 */             v_sampling_factor_n= get_bits(gb, 5);                                                               // 0.0
/*456 */             v_sampling_factor_m= get_bits(gb, 5);                                                               // 0.0
/*458 */             s->enhancement_type= get_bits1(gb);                                                                 // 0.0
/*460 */                                                                                                                 // 0.0
/*462 */             if(   h_sampling_factor_n==0 || h_sampling_factor_m==0                                              // 0.0
/*464 */                || v_sampling_factor_n==0 || v_sampling_factor_m==0){                                            // 0.0
/*466 */                                                                                                                 // 0.0
/*468 */ //                fprintf(stderr, "illegal scalability header (VERY broken encoder), trying to workaround\n");  // 0.0
/*470 */                 s->scalability=0;                                                                               // 0.0
/*472 */                                                                                                                 // 0.0
/*474 */                 *gb= bak;                                                                                       // 0.0
/*476 */             }else                                                                                               // 0.0
/*478 */                 printf("scalability not supported\n");                                                          // 0.0
/*480 */                                                                                                                 // 0.0
/*482 */             // bin shape stuff FIXME                                                                            // 0.0
/*484 */         }                                                                                                       // 0.0
/*486 */     }                                                                                                           // 0.0
/*488 */     return 0;                                                                                                   // 0.0
/*490 */ }                                                                                                               // 0.0
