// commit message FFmpeg@29d2dc59f9 (target=1, prob=0.7971014, correct=True): fix mem leak patch by Daniel Kristjansson: [danielk cuymedia net] Original thread: [FFmpeg-devel] [PATCH] alloc_picture needs to free buffer when it's not going to use it Date: 07/20/2007 07:27 PM
/*0   */ int alloc_picture(MpegEncContext *s, Picture *pic, int shared){                                                               // (11) 0.03711
/*2   */     const int big_mb_num= s->mb_stride*(s->mb_height+1) + 1; //the +1 is needed so memset(,,stride*height) does not sig11     // (1) 0.09766
/*4   */     const int mb_array_size= s->mb_stride*s->mb_height;                                                                       // (9) 0.04883
/*6   */     const int b8_array_size= s->b8_stride*s->mb_height*2;                                                                     // (7) 0.05469
/*8   */     const int b4_array_size= s->b4_stride*s->mb_height*4;                                                                     // (8) 0.05469
/*10  */     int i;                                                                                                                    // (18) 0.01172
/*14  */     if(shared){                                                                                                               // (17) 0.01367
/*16  */         assert(pic->data[0]);                                                                                                 // (14) 0.0293
/*18  */         assert(pic->type == 0 || pic->type == FF_BUFFER_TYPE_SHARED);                                                         // (5) 0.05859
/*20  */         pic->type= FF_BUFFER_TYPE_SHARED;                                                                                     // (10) 0.04297
/*22  */     }else{                                                                                                                    // (19) 0.01172
/*24  */         int r;                                                                                                                // (15) 0.01953
/*28  */         assert(!pic->data[0]);                                                                                                // (12) 0.03125
/*32  */         r= s->avctx->get_buffer(s->avctx, (AVFrame*)pic);                                                                     // (6) 0.05664
/*36  */         if(r<0 || !pic->age || !pic->type || !pic->data[0]){                                                                  // (4) 0.06055
/*38  */             av_log(s->avctx, AV_LOG_ERROR, "get_buffer() failed (%d %d %d %p)\n", r, pic->age, pic->type, pic->data[0]);      // (0) 0.1152
/*40  */             return -1;                                                                                                        // (13) 0.0293
/*42  */         }                                                                                                                     // (16) 0.01562
/*46  */         if(s->linesize && (s->linesize != pic->linesize[0] || s->uvlinesize != pic->linesize[1])){                            // (2) 0.08398
/*48  */             av_log(s->avctx, AV_LOG_ERROR, "get_buffer() failed (stride changed)\n");                                         // (3) 0.07617
/*50  */             return -1;                                                                                                        // 0.0
/*52  */         }                                                                                                                     // 0.0
/*56  */         if(pic->linesize[1] != pic->linesize[2]){                                                                             // 0.0
/*58  */             av_log(s->avctx, AV_LOG_ERROR, "get_buffer() failed (uv stride mismatch)\n");                                     // 0.0
/*60  */             return -1;                                                                                                        // 0.0
/*62  */         }                                                                                                                     // 0.0
/*66  */         s->linesize  = pic->linesize[0];                                                                                      // 0.0
/*68  */         s->uvlinesize= pic->linesize[1];                                                                                      // 0.0
/*70  */     }                                                                                                                         // 0.0
/*74  */     if(pic->qscale_table==NULL){                                                                                              // 0.0
/*76  */         if (s->encoding) {                                                                                                    // 0.0
/*78  */             CHECKED_ALLOCZ(pic->mb_var   , mb_array_size * sizeof(int16_t))                                                   // 0.0
/*80  */             CHECKED_ALLOCZ(pic->mc_mb_var, mb_array_size * sizeof(int16_t))                                                   // 0.0
/*82  */             CHECKED_ALLOCZ(pic->mb_mean  , mb_array_size * sizeof(int8_t))                                                    // 0.0
/*84  */         }                                                                                                                     // 0.0
/*88  */         CHECKED_ALLOCZ(pic->mbskip_table , mb_array_size * sizeof(uint8_t)+2) //the +2 is for the slice end check             // 0.0
/*90  */         CHECKED_ALLOCZ(pic->qscale_table , mb_array_size * sizeof(uint8_t))                                                   // 0.0
/*92  */         CHECKED_ALLOCZ(pic->mb_type_base , big_mb_num    * sizeof(uint32_t))                                                  // 0.0
/*94  */         pic->mb_type= pic->mb_type_base + s->mb_stride+1;                                                                     // 0.0
/*96  */         if(s->out_format == FMT_H264){                                                                                        // 0.0
/*98  */             for(i=0; i<2; i++){                                                                                               // 0.0
/*100 */                 CHECKED_ALLOCZ(pic->motion_val_base[i], 2 * (b4_array_size+4)  * sizeof(int16_t))                             // 0.0
/*102 */                 pic->motion_val[i]= pic->motion_val_base[i]+4;                                                                // 0.0
/*104 */                 CHECKED_ALLOCZ(pic->ref_index[i], b8_array_size * sizeof(uint8_t))                                            // 0.0
/*106 */             }                                                                                                                 // 0.0
/*108 */             pic->motion_subsample_log2= 2;                                                                                    // 0.0
/*110 */         }else if(s->out_format == FMT_H263 || s->encoding || (s->avctx->debug&FF_DEBUG_MV) || (s->avctx->debug_mv)){          // 0.0
/*112 */             for(i=0; i<2; i++){                                                                                               // 0.0
/*114 */                 CHECKED_ALLOCZ(pic->motion_val_base[i], 2 * (b8_array_size+4) * sizeof(int16_t))                              // 0.0
/*116 */                 pic->motion_val[i]= pic->motion_val_base[i]+4;                                                                // 0.0
/*118 */                 CHECKED_ALLOCZ(pic->ref_index[i], b8_array_size * sizeof(uint8_t))                                            // 0.0
/*120 */             }                                                                                                                 // 0.0
/*122 */             pic->motion_subsample_log2= 3;                                                                                    // 0.0
/*124 */         }                                                                                                                     // 0.0
/*126 */         if(s->avctx->debug&FF_DEBUG_DCT_COEFF) {                                                                              // 0.0
/*128 */             CHECKED_ALLOCZ(pic->dct_coeff, 64 * mb_array_size * sizeof(DCTELEM)*6)                                            // 0.0
/*130 */         }                                                                                                                     // 0.0
/*132 */         pic->qstride= s->mb_stride;                                                                                           // 0.0
/*134 */         CHECKED_ALLOCZ(pic->pan_scan , 1 * sizeof(AVPanScan))                                                                 // 0.0
/*136 */     }                                                                                                                         // 0.0
/*140 */     /* It might be nicer if the application would keep track of these                                                         // 0.0
/*142 */      * but it would require an API change. */                                                                                 // 0.0
/*144 */     memmove(s->prev_pict_types+1, s->prev_pict_types, PREV_PICT_TYPES_BUFFER_SIZE-1);                                         // 0.0
/*146 */     s->prev_pict_types[0]= s->pict_type;                                                                                      // 0.0
/*148 */     if(pic->age < PREV_PICT_TYPES_BUFFER_SIZE && s->prev_pict_types[pic->age] == B_TYPE)                                      // 0.0
/*150 */         pic->age= INT_MAX; // Skipped MBs in B-frames are quite rare in MPEG-1/2 and it is a bit tricky to skip them anyway.  // 0.0
/*154 */     return 0;                                                                                                                 // 0.0
/*156 */ fail: //for the CHECKED_ALLOCZ macro                                                                                          // 0.0
/*158 */     return -1;                                                                                                                // 0.0
/*160 */ }                                                                                                                             // 0.0
