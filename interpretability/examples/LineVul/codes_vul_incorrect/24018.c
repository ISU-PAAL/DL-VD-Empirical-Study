// commit message FFmpeg@cd19c677cb (target=1, prob=0.3654216, correct=False): fix a crash on dropped frames
/*0   */ static int decode_frame(AVCodecContext *avctx,                                                 // (13) 0.02572
/*2   */                              void *data, int *data_size,                                       // (2) 0.05651
/*4   */                              uint8_t *buf, int buf_size)                                       // (1) 0.06014
/*6   */ {                                                                                              // (27) 0.004895
/*8   */     H264Context *h = avctx->priv_data;                                                         // (11) 0.02841
/*10  */     MpegEncContext *s = &h->s;                                                                 // (14) 0.02277
/*12  */     AVFrame *pict = data;                                                                      // (16) 0.01992
/*14  */     int buf_index;                                                                             // (21) 0.01196
/*16  */                                                                                                // (26) 0.005922
/*18  */     s->flags= avctx->flags;                                                                    // (17) 0.01795
/*20  */     s->flags2= avctx->flags2;                                                                  // (15) 0.021
/*24  */    /* no supplementary picture */                                                              // (19) 0.01703
/*26  */     if (buf_size == 0) {                                                                       // (18) 0.01794
/*28  */         return 0;                                                                              // (20) 0.01497
/*30  */     }                                                                                          // (24) 0.006132
/*32  */                                                                                                // (25) 0.00605
/*34  */     if(s->flags&CODEC_FLAG_TRUNCATED){                                                         // (8) 0.02985
/*36  */         int next= find_frame_end(h, buf, buf_size);                                            // (5) 0.03634
/*38  */                                                                                                // (22) 0.01184
/*40  */         if( ff_combine_frame(&s->parse_context, next, &buf, &buf_size) < 0 )                   // (3) 0.05485
/*42  */             return buf_size;                                                                   // (9) 0.02967
/*44  */ //printf("next:%d buf_size:%d last_index:%d\n", next, buf_size, s->parse_context.last_index);  // (0) 0.1908
/*46  */     }                                                                                          // (23) 0.007277
/*50  */     if(h->is_avc && !h->got_avcC) {                                                            // (6) 0.03324
/*52  */         int i, cnt, nalsize;                                                                   // (12) 0.02576
/*54  */         unsigned char *p = avctx->extradata;                                                   // (10) 0.02922
/*56  */         if(avctx->extradata_size < 7) {                                                        // (7) 0.03156
/*58  */             av_log(avctx, AV_LOG_ERROR, "avcC too short\n");                                   // (4) 0.05021
/*60  */             return -1;                                                                         // 0.0
/*62  */         }                                                                                      // 0.0
/*64  */         if(*p != 1) {                                                                          // 0.0
/*66  */             av_log(avctx, AV_LOG_ERROR, "Unknown avcC version %d\n", *p);                      // 0.0
/*68  */             return -1;                                                                         // 0.0
/*70  */         }                                                                                      // 0.0
/*72  */         /* sps and pps in the avcC always have length coded with 2 bytes,                      // 0.0
/*74  */            so put a fake nal_length_size = 2 while parsing them */                             // 0.0
/*76  */         h->nal_length_size = 2;                                                                // 0.0
/*78  */         // Decode sps from avcC                                                                // 0.0
/*80  */         cnt = *(p+5) & 0x1f; // Number of sps                                                  // 0.0
/*82  */         p += 6;                                                                                // 0.0
/*84  */         for (i = 0; i < cnt; i++) {                                                            // 0.0
/*86  */             nalsize = BE_16(p) + 2;                                                            // 0.0
/*88  */             if(decode_nal_units(h, p, nalsize) < 0) {                                          // 0.0
/*90  */                 av_log(avctx, AV_LOG_ERROR, "Decoding sps %d from avcC failed\n", i);          // 0.0
/*92  */                 return -1;                                                                     // 0.0
/*94  */             }                                                                                  // 0.0
/*96  */             p += nalsize;                                                                      // 0.0
/*98  */         }                                                                                      // 0.0
/*100 */         // Decode pps from avcC                                                                // 0.0
/*102 */         cnt = *(p++); // Number of pps                                                         // 0.0
/*104 */         for (i = 0; i < cnt; i++) {                                                            // 0.0
/*106 */             nalsize = BE_16(p) + 2;                                                            // 0.0
/*108 */             if(decode_nal_units(h, p, nalsize)  != nalsize) {                                  // 0.0
/*110 */                 av_log(avctx, AV_LOG_ERROR, "Decoding pps %d from avcC failed\n", i);          // 0.0
/*112 */                 return -1;                                                                     // 0.0
/*114 */             }                                                                                  // 0.0
/*116 */             p += nalsize;                                                                      // 0.0
/*118 */         }                                                                                      // 0.0
/*120 */         // Now store right nal length size, that will be use to parse all other nals           // 0.0
/*122 */         h->nal_length_size = ((*(((char*)(avctx->extradata))+4))&0x03)+1;                      // 0.0
/*124 */         // Do not reparse avcC                                                                 // 0.0
/*126 */         h->got_avcC = 1;                                                                       // 0.0
/*128 */     }                                                                                          // 0.0
/*132 */     if(!h->is_avc && s->avctx->extradata_size && s->picture_number==0){                        // 0.0
/*134 */         if(decode_nal_units(h, s->avctx->extradata, s->avctx->extradata_size) < 0)             // 0.0
/*136 */             return -1;                                                                         // 0.0
/*138 */     }                                                                                          // 0.0
/*142 */     buf_index=decode_nal_units(h, buf, buf_size);                                              // 0.0
/*144 */     if(buf_index < 0)                                                                          // 0.0
/*146 */         return -1;                                                                             // 0.0
/*150 */     //FIXME do something with unavailable reference frames                                     // 0.0
/*152 */                                                                                                // (28) 0.001485
/*154 */ //    if(ret==FRAME_SKIPPED) return get_consumed_bytes(s, buf_index, buf_size);                // 0.0
/*156 */     if(!s->current_picture_ptr){                                                               // 0.0
/*158 */         av_log(h->s.avctx, AV_LOG_DEBUG, "error, NO frame\n");                                 // 0.0
/*160 */         return -1;                                                                             // 0.0
/*162 */     }                                                                                          // 0.0
/*166 */     {                                                                                          // 0.0
/*168 */         Picture *out = s->current_picture_ptr;                                                 // 0.0
/*170 */ #if 0 //decode order                                                                           // 0.0
/*172 */         *data_size = sizeof(AVFrame);                                                          // 0.0
/*174 */ #else                                                                                          // 0.0
/*176 */         /* Sort B-frames into display order */                                                 // 0.0
/*178 */         Picture *cur = s->current_picture_ptr;                                                 // 0.0
/*180 */         Picture *prev = h->delayed_output_pic;                                                 // 0.0
/*182 */         int out_idx = 0;                                                                       // 0.0
/*184 */         int pics = 0;                                                                          // 0.0
/*186 */         int out_of_order;                                                                      // 0.0
/*188 */         int cross_idr = 0;                                                                     // 0.0
/*190 */         int dropped_frame = 0;                                                                 // 0.0
/*192 */         int i;                                                                                 // 0.0
/*196 */         if(h->sps.bitstream_restriction_flag                                                   // 0.0
/*198 */            && s->avctx->has_b_frames < h->sps.num_reorder_frames){                             // 0.0
/*200 */             s->avctx->has_b_frames = h->sps.num_reorder_frames;                                // 0.0
/*202 */             s->low_delay = 0;                                                                  // 0.0
/*204 */         }                                                                                      // 0.0
/*208 */         while(h->delayed_pic[pics]) pics++;                                                    // 0.0
/*210 */         h->delayed_pic[pics++] = cur;                                                          // 0.0
/*212 */         if(cur->reference == 0)                                                                // 0.0
/*214 */             cur->reference = 1;                                                                // 0.0
/*218 */         for(i=0; h->delayed_pic[i]; i++)                                                       // 0.0
/*220 */             if(h->delayed_pic[i]->key_frame || h->delayed_pic[i]->poc==0)                      // 0.0
/*222 */                 cross_idr = 1;                                                                 // 0.0
/*226 */         out = h->delayed_pic[0];                                                               // 0.0
/*228 */         for(i=1; h->delayed_pic[i] && !h->delayed_pic[i]->key_frame; i++)                      // 0.0
/*230 */             if(h->delayed_pic[i]->poc < out->poc){                                             // 0.0
/*232 */                 out = h->delayed_pic[i];                                                       // 0.0
/*234 */                 out_idx = i;                                                                   // 0.0
/*236 */             }                                                                                  // 0.0
/*240 */         out_of_order = !cross_idr && prev && out->poc < prev->poc;                             // 0.0
/*242 */         if(prev && pics <= s->avctx->has_b_frames)                                             // 0.0
/*244 */             out = prev;                                                                        // 0.0
/*246 */         else if((out_of_order && pics-1 == s->avctx->has_b_frames)                             // 0.0
/*248 */            || (s->low_delay &&                                                                 // 0.0
/*250 */             ((!cross_idr && prev && out->poc > prev->poc + 2)                                  // 0.0
/*252 */              || cur->pict_type == B_TYPE)))                                                    // 0.0
/*254 */         {                                                                                      // 0.0
/*256 */             s->low_delay = 0;                                                                  // 0.0
/*258 */             s->avctx->has_b_frames++;                                                          // 0.0
/*260 */             out = prev;                                                                        // 0.0
/*262 */         }                                                                                      // 0.0
/*264 */         else if(out_of_order)                                                                  // 0.0
/*266 */             out = prev;                                                                        // 0.0
/*270 */         if(out_of_order || pics > s->avctx->has_b_frames){                                     // 0.0
/*272 */             dropped_frame = (out != h->delayed_pic[out_idx]);                                  // 0.0
/*274 */             for(i=out_idx; h->delayed_pic[i]; i++)                                             // 0.0
/*276 */                 h->delayed_pic[i] = h->delayed_pic[i+1];                                       // 0.0
/*278 */         }                                                                                      // 0.0
/*282 */         if(prev == out && !dropped_frame)                                                      // 0.0
/*284 */             *data_size = 0;                                                                    // 0.0
/*286 */         else                                                                                   // 0.0
/*288 */             *data_size = sizeof(AVFrame);                                                      // 0.0
/*290 */         if(prev && prev != out && prev->reference == 1)                                        // 0.0
/*292 */             prev->reference = 0;                                                               // 0.0
/*294 */         h->delayed_output_pic = out;                                                           // 0.0
/*296 */ #endif                                                                                         // 0.0
/*300 */         *pict= *(AVFrame*)out;                                                                 // 0.0
/*302 */     }                                                                                          // 0.0
/*306 */     assert(pict->data[0]);                                                                     // 0.0
/*308 */     ff_print_debug_info(s, pict);                                                              // 0.0
/*310 */ //printf("out %d\n", (int)pict->data[0]);                                                      // 0.0
/*312 */ #if 0 //?                                                                                      // 0.0
/*316 */     /* Return the Picture timestamp as the frame number */                                     // 0.0
/*318 */     /* we substract 1 because it is added on utils.c    */                                     // 0.0
/*320 */     avctx->frame_number = s->picture_number - 1;                                               // 0.0
/*322 */ #endif                                                                                         // 0.0
/*324 */     return get_consumed_bytes(s, buf_index, buf_size);                                         // 0.0
/*326 */ }                                                                                              // 0.0
