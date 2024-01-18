// commit message FFmpeg@f98c9fb27d (target=0, prob=0.6412466, correct=False): mpeg1video: don't abort if thread_count is too high.
/*0   */ av_cold int MPV_common_init(MpegEncContext *s)                                                                                         // (12) 0.03517
/*2   */ {                                                                                                                                      // (21) 0.001953
/*4   */     int y_size, c_size, yc_size, i, mb_array_size, mv_table_size, x, y, threads;                                                       // (2) 0.07618
/*8   */     if(s->codec_id == CODEC_ID_MPEG2VIDEO && !s->progressive_sequence)                                                                 // (4) 0.06055
/*10  */         s->mb_height = (s->height + 31) / 32 * 2;                                                                                      // (7) 0.04883
/*12  */     else if (s->codec_id != CODEC_ID_H264)                                                                                             // (10) 0.04297
/*14  */         s->mb_height = (s->height + 15) / 16;                                                                                          // (9) 0.04492
/*18  */     if(s->avctx->pix_fmt == PIX_FMT_NONE){                                                                                             // (8) 0.04883
/*20  */         av_log(s->avctx, AV_LOG_ERROR, "decoding to PIX_FMT_NONE is not supported.\n");                                                // (1) 0.08008
/*22  */         return -1;                                                                                                                     // (17) 0.02148
/*24  */     }                                                                                                                                  // (20) 0.007812
/*28  */     if((s->encoding || (s->avctx->active_thread_type & FF_THREAD_SLICE)) &&                                                            // (5) 0.06055
/*30  */        (s->avctx->thread_count > MAX_THREADS || (s->avctx->thread_count > s->mb_height && s->mb_height))){                             // (0) 0.08789
/*32  */         av_log(s->avctx, AV_LOG_ERROR, "too many threads\n");                                                                          // (6) 0.05664
/*34  */         return -1;                                                                                                                     // (18) 0.02148
/*36  */     }                                                                                                                                  // (19) 0.007812
/*40  */     if((s->width || s->height) && av_image_check_size(s->width, s->height, 0, s->avctx))                                               // (3) 0.07226
/*42  */         return -1;                                                                                                                     // (16) 0.02148
/*46  */     dsputil_init(&s->dsp, s->avctx);                                                                                                   // (11) 0.03906
/*48  */     ff_dct_common_init(s);                                                                                                             // (14) 0.02734
/*52  */     s->flags= s->avctx->flags;                                                                                                         // (15) 0.02734
/*54  */     s->flags2= s->avctx->flags2;                                                                                                       // (13) 0.03125
/*58  */     if (s->width && s->height) {                                                                                                       // 0.0
/*60  */         s->mb_width  = (s->width  + 15) / 16;                                                                                          // 0.0
/*62  */         s->mb_stride = s->mb_width + 1;                                                                                                // 0.0
/*64  */         s->b8_stride = s->mb_width*2 + 1;                                                                                              // 0.0
/*66  */         s->b4_stride = s->mb_width*4 + 1;                                                                                              // 0.0
/*68  */         mb_array_size= s->mb_height * s->mb_stride;                                                                                    // 0.0
/*70  */         mv_table_size= (s->mb_height+2) * s->mb_stride + 1;                                                                            // 0.0
/*74  */         /* set chroma shifts */                                                                                                        // 0.0
/*76  */         avcodec_get_chroma_sub_sample(s->avctx->pix_fmt,&(s->chroma_x_shift),                                                          // 0.0
/*78  */                                       &(s->chroma_y_shift) );                                                                          // 0.0
/*82  */         /* set default edge pos, will be overriden in decode_header if needed */                                                       // 0.0
/*84  */         s->h_edge_pos= s->mb_width*16;                                                                                                 // 0.0
/*86  */         s->v_edge_pos= s->mb_height*16;                                                                                                // 0.0
/*90  */         s->mb_num = s->mb_width * s->mb_height;                                                                                        // 0.0
/*94  */         s->block_wrap[0]=                                                                                                              // 0.0
/*96  */         s->block_wrap[1]=                                                                                                              // 0.0
/*98  */         s->block_wrap[2]=                                                                                                              // 0.0
/*100 */         s->block_wrap[3]= s->b8_stride;                                                                                                // 0.0
/*102 */         s->block_wrap[4]=                                                                                                              // 0.0
/*104 */         s->block_wrap[5]= s->mb_stride;                                                                                                // 0.0
/*108 */         y_size = s->b8_stride * (2 * s->mb_height + 1);                                                                                // 0.0
/*110 */         c_size = s->mb_stride * (s->mb_height + 1);                                                                                    // 0.0
/*112 */         yc_size = y_size + 2 * c_size;                                                                                                 // 0.0
/*116 */         /* convert fourcc to upper case */                                                                                             // 0.0
/*118 */         s->codec_tag = ff_toupper4(s->avctx->codec_tag);                                                                               // 0.0
/*122 */         s->stream_codec_tag = ff_toupper4(s->avctx->stream_codec_tag);                                                                 // 0.0
/*126 */         s->avctx->coded_frame= (AVFrame*)&s->current_picture;                                                                          // 0.0
/*130 */         FF_ALLOCZ_OR_GOTO(s->avctx, s->mb_index2xy, (s->mb_num+1)*sizeof(int), fail) //error ressilience code looks cleaner with this  // 0.0
/*132 */         for(y=0; y<s->mb_height; y++){                                                                                                 // 0.0
/*134 */             for(x=0; x<s->mb_width; x++){                                                                                              // 0.0
/*136 */                 s->mb_index2xy[ x + y*s->mb_width ] = x + y*s->mb_stride;                                                              // 0.0
/*138 */             }                                                                                                                          // 0.0
/*140 */         }                                                                                                                              // 0.0
/*142 */         s->mb_index2xy[ s->mb_height*s->mb_width ] = (s->mb_height-1)*s->mb_stride + s->mb_width; //FIXME really needed?               // 0.0
/*146 */         if (s->encoding) {                                                                                                             // 0.0
/*148 */             /* Allocate MV tables */                                                                                                   // 0.0
/*150 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->p_mv_table_base            , mv_table_size * 2 * sizeof(int16_t), fail)                     // 0.0
/*152 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->b_forw_mv_table_base       , mv_table_size * 2 * sizeof(int16_t), fail)                     // 0.0
/*154 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->b_back_mv_table_base       , mv_table_size * 2 * sizeof(int16_t), fail)                     // 0.0
/*156 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->b_bidir_forw_mv_table_base , mv_table_size * 2 * sizeof(int16_t), fail)                     // 0.0
/*158 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->b_bidir_back_mv_table_base , mv_table_size * 2 * sizeof(int16_t), fail)                     // 0.0
/*160 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->b_direct_mv_table_base     , mv_table_size * 2 * sizeof(int16_t), fail)                     // 0.0
/*162 */             s->p_mv_table           = s->p_mv_table_base            + s->mb_stride + 1;                                                // 0.0
/*164 */             s->b_forw_mv_table      = s->b_forw_mv_table_base       + s->mb_stride + 1;                                                // 0.0
/*166 */             s->b_back_mv_table      = s->b_back_mv_table_base       + s->mb_stride + 1;                                                // 0.0
/*168 */             s->b_bidir_forw_mv_table= s->b_bidir_forw_mv_table_base + s->mb_stride + 1;                                                // 0.0
/*170 */             s->b_bidir_back_mv_table= s->b_bidir_back_mv_table_base + s->mb_stride + 1;                                                // 0.0
/*172 */             s->b_direct_mv_table    = s->b_direct_mv_table_base     + s->mb_stride + 1;                                                // 0.0
/*176 */             if(s->msmpeg4_version){                                                                                                    // 0.0
/*178 */                 FF_ALLOCZ_OR_GOTO(s->avctx, s->ac_stats, 2*2*(MAX_LEVEL+1)*(MAX_RUN+1)*2*sizeof(int), fail);                           // 0.0
/*180 */             }                                                                                                                          // 0.0
/*182 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->avctx->stats_out, 256, fail);                                                               // 0.0
/*186 */             /* Allocate MB type table */                                                                                               // 0.0
/*188 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->mb_type  , mb_array_size * sizeof(uint16_t), fail) //needed for encoding                    // 0.0
/*192 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->lambda_table, mb_array_size * sizeof(int), fail)                                            // 0.0
/*196 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->q_intra_matrix  , 64*32   * sizeof(int), fail)                                              // 0.0
/*198 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->q_inter_matrix  , 64*32   * sizeof(int), fail)                                              // 0.0
/*200 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->q_intra_matrix16, 64*32*2 * sizeof(uint16_t), fail)                                         // 0.0
/*202 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->q_inter_matrix16, 64*32*2 * sizeof(uint16_t), fail)                                         // 0.0
/*204 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->input_picture, MAX_PICTURE_COUNT * sizeof(Picture*), fail)                                  // 0.0
/*206 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->reordered_input_picture, MAX_PICTURE_COUNT * sizeof(Picture*), fail)                        // 0.0
/*210 */             if(s->avctx->noise_reduction){                                                                                             // 0.0
/*212 */                 FF_ALLOCZ_OR_GOTO(s->avctx, s->dct_offset, 2 * 64 * sizeof(uint16_t), fail)                                            // 0.0
/*214 */             }                                                                                                                          // 0.0
/*216 */         }                                                                                                                              // 0.0
/*218 */     }                                                                                                                                  // 0.0
/*222 */     s->picture_count = MAX_PICTURE_COUNT * FFMAX(1, s->avctx->thread_count);                                                           // 0.0
/*224 */     FF_ALLOCZ_OR_GOTO(s->avctx, s->picture, s->picture_count * sizeof(Picture), fail)                                                  // 0.0
/*226 */     for(i = 0; i < s->picture_count; i++) {                                                                                            // 0.0
/*228 */         avcodec_get_frame_defaults((AVFrame *)&s->picture[i]);                                                                         // 0.0
/*230 */     }                                                                                                                                  // 0.0
/*234 */     if (s->width && s->height) {                                                                                                       // 0.0
/*236 */         FF_ALLOCZ_OR_GOTO(s->avctx, s->error_status_table, mb_array_size*sizeof(uint8_t), fail)                                        // 0.0
/*240 */         if(s->codec_id==CODEC_ID_MPEG4 || (s->flags & CODEC_FLAG_INTERLACED_ME)){                                                      // 0.0
/*242 */             /* interlaced direct mode decoding tables */                                                                               // 0.0
/*244 */             for(i=0; i<2; i++){                                                                                                        // 0.0
/*246 */                 int j, k;                                                                                                              // 0.0
/*248 */                 for(j=0; j<2; j++){                                                                                                    // 0.0
/*250 */                     for(k=0; k<2; k++){                                                                                                // 0.0
/*252 */                         FF_ALLOCZ_OR_GOTO(s->avctx,    s->b_field_mv_table_base[i][j][k], mv_table_size * 2 * sizeof(int16_t), fail)   // 0.0
/*254 */                         s->b_field_mv_table[i][j][k] = s->b_field_mv_table_base[i][j][k] + s->mb_stride + 1;                           // 0.0
/*256 */                     }                                                                                                                  // 0.0
/*258 */                     FF_ALLOCZ_OR_GOTO(s->avctx, s->b_field_select_table [i][j], mb_array_size * 2 * sizeof(uint8_t), fail)             // 0.0
/*260 */                     FF_ALLOCZ_OR_GOTO(s->avctx, s->p_field_mv_table_base[i][j], mv_table_size * 2 * sizeof(int16_t), fail)             // 0.0
/*262 */                     s->p_field_mv_table[i][j] = s->p_field_mv_table_base[i][j]+ s->mb_stride + 1;                                      // 0.0
/*264 */                 }                                                                                                                      // 0.0
/*266 */                 FF_ALLOCZ_OR_GOTO(s->avctx, s->p_field_select_table[i], mb_array_size * 2 * sizeof(uint8_t), fail)                     // 0.0
/*268 */             }                                                                                                                          // 0.0
/*270 */         }                                                                                                                              // 0.0
/*272 */         if (s->out_format == FMT_H263) {                                                                                               // 0.0
/*274 */             /* cbp values */                                                                                                           // 0.0
/*276 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->coded_block_base, y_size, fail);                                                            // 0.0
/*278 */             s->coded_block= s->coded_block_base + s->b8_stride + 1;                                                                    // 0.0
/*282 */             /* cbp, ac_pred, pred_dir */                                                                                               // 0.0
/*284 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->cbp_table     , mb_array_size * sizeof(uint8_t), fail)                                      // 0.0
/*286 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->pred_dir_table, mb_array_size * sizeof(uint8_t), fail)                                      // 0.0
/*288 */         }                                                                                                                              // 0.0
/*292 */         if (s->h263_pred || s->h263_plus || !s->encoding) {                                                                            // 0.0
/*294 */             /* dc values */                                                                                                            // 0.0
/*296 */             //MN: we need these for error resilience of intra-frames                                                                   // 0.0
/*298 */             FF_ALLOCZ_OR_GOTO(s->avctx, s->dc_val_base, yc_size * sizeof(int16_t), fail);                                              // 0.0
/*300 */             s->dc_val[0] = s->dc_val_base + s->b8_stride + 1;                                                                          // 0.0
/*302 */             s->dc_val[1] = s->dc_val_base + y_size + s->mb_stride + 1;                                                                 // 0.0
/*304 */             s->dc_val[2] = s->dc_val[1] + c_size;                                                                                      // 0.0
/*306 */             for(i=0;i<yc_size;i++)                                                                                                     // 0.0
/*308 */                 s->dc_val_base[i] = 1024;                                                                                              // 0.0
/*310 */         }                                                                                                                              // 0.0
/*314 */         /* which mb is a intra block */                                                                                                // 0.0
/*316 */         FF_ALLOCZ_OR_GOTO(s->avctx, s->mbintra_table, mb_array_size, fail);                                                            // 0.0
/*318 */         memset(s->mbintra_table, 1, mb_array_size);                                                                                    // 0.0
/*322 */         /* init macroblock skip table */                                                                                               // 0.0
/*324 */         FF_ALLOCZ_OR_GOTO(s->avctx, s->mbskip_table, mb_array_size+2, fail);                                                           // 0.0
/*326 */         //Note the +1 is for a quicker mpeg4 slice_end detection                                                                       // 0.0
/*328 */         FF_ALLOCZ_OR_GOTO(s->avctx, s->prev_pict_types, PREV_PICT_TYPES_BUFFER_SIZE, fail);                                            // 0.0
/*332 */         s->parse_context.state= -1;                                                                                                    // 0.0
/*334 */         if((s->avctx->debug&(FF_DEBUG_VIS_QP|FF_DEBUG_VIS_MB_TYPE)) || (s->avctx->debug_mv)){                                          // 0.0
/*336 */             s->visualization_buffer[0] = av_malloc((s->mb_width*16 + 2*EDGE_WIDTH) * s->mb_height*16 + 2*EDGE_WIDTH);                  // 0.0
/*338 */             s->visualization_buffer[1] = av_malloc((s->mb_width*16 + 2*EDGE_WIDTH) * s->mb_height*16 + 2*EDGE_WIDTH);                  // 0.0
/*340 */             s->visualization_buffer[2] = av_malloc((s->mb_width*16 + 2*EDGE_WIDTH) * s->mb_height*16 + 2*EDGE_WIDTH);                  // 0.0
/*342 */         }                                                                                                                              // 0.0
/*344 */     }                                                                                                                                  // 0.0
/*348 */     s->context_initialized = 1;                                                                                                        // 0.0
/*350 */     s->thread_context[0]= s;                                                                                                           // 0.0
/*354 */     if (s->width && s->height) {                                                                                                       // 0.0
/*356 */     if (s->encoding || (HAVE_THREADS && s->avctx->active_thread_type&FF_THREAD_SLICE)) {                                               // 0.0
/*358 */         threads = s->avctx->thread_count;                                                                                              // 0.0
/*362 */         for(i=1; i<threads; i++){                                                                                                      // 0.0
/*364 */             s->thread_context[i]= av_malloc(sizeof(MpegEncContext));                                                                   // 0.0
/*366 */             memcpy(s->thread_context[i], s, sizeof(MpegEncContext));                                                                   // 0.0
/*368 */         }                                                                                                                              // 0.0
/*372 */         for(i=0; i<threads; i++){                                                                                                      // 0.0
/*374 */             if(init_duplicate_context(s->thread_context[i], s) < 0)                                                                    // 0.0
/*376 */                 goto fail;                                                                                                             // 0.0
/*378 */             s->thread_context[i]->start_mb_y= (s->mb_height*(i  ) + s->avctx->thread_count/2) / s->avctx->thread_count;                // 0.0
/*380 */             s->thread_context[i]->end_mb_y  = (s->mb_height*(i+1) + s->avctx->thread_count/2) / s->avctx->thread_count;                // 0.0
/*382 */         }                                                                                                                              // 0.0
/*384 */     } else {                                                                                                                           // 0.0
/*386 */         if(init_duplicate_context(s, s) < 0) goto fail;                                                                                // 0.0
/*388 */         s->start_mb_y = 0;                                                                                                             // 0.0
/*390 */         s->end_mb_y   = s->mb_height;                                                                                                  // 0.0
/*392 */     }                                                                                                                                  // 0.0
/*394 */     }                                                                                                                                  // 0.0
/*398 */     return 0;                                                                                                                          // 0.0
/*400 */  fail:                                                                                                                                 // 0.0
/*402 */     MPV_common_end(s);                                                                                                                 // 0.0
/*404 */     return -1;                                                                                                                         // 0.0
/*406 */ }                                                                                                                                      // 0.0
