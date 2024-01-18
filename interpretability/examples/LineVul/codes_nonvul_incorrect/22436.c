// commit message FFmpeg@d3b4b74c32 (target=0, prob=0.65753704, correct=False): Fix lossless jpeg encoder to comply to spec and store full redundant residuals, Note this does not change RGB32 as we need to check this against some decoder that supports it.
/*0   */ static int encode_picture_lossless(AVCodecContext *avctx, unsigned char *buf, int buf_size, void *data){                                              // (0) 0.06055
/*2   */     MpegEncContext * const s = avctx->priv_data;                                                                                                      // (13) 0.03515
/*4   */     MJpegContext * const m = s->mjpeg_ctx;                                                                                                            // (15) 0.03514
/*6   */     AVFrame *pict = data;                                                                                                                             // (22) 0.01953
/*8   */     const int width= s->width;                                                                                                                        // (20) 0.02148
/*10  */     const int height= s->height;                                                                                                                      // (19) 0.02148
/*12  */     AVFrame * const p= (AVFrame*)&s->current_picture;                                                                                                 // (8) 0.03907
/*14  */     const int predictor= avctx->prediction_method+1;                                                                                                  // (16) 0.03319
/*18  */     init_put_bits(&s->pb, buf, buf_size);                                                                                                             // (11) 0.0371
/*22  */     *p = *pict;                                                                                                                                       // (23) 0.01757
/*24  */     p->pict_type= FF_I_TYPE;                                                                                                                          // (17) 0.02929
/*26  */     p->key_frame= 1;                                                                                                                                  // (21) 0.02147
/*30  */     ff_mjpeg_encode_picture_header(s);                                                                                                                // (14) 0.03515
/*34  */     s->header_bits= put_bits_count(&s->pb);                                                                                                           // (10) 0.03716
/*38  */     if(avctx->pix_fmt == PIX_FMT_RGB32){                                                                                                              // (5) 0.04505
/*40  */         int x, y, i;                                                                                                                                  // (18) 0.02733
/*42  */         const int linesize= p->linesize[0];                                                                                                           // (12) 0.03709
/*44  */         uint16_t (*buffer)[4]= (void *) s->rd_scratchpad;                                                                                             // (2) 0.05271
/*46  */         int left[3], top[3], topleft[3];                                                                                                              // (6) 0.04296
/*50  */         for(i=0; i<3; i++){                                                                                                                           // (7) 0.03908
/*52  */             buffer[0][i]= 1 << (9 - 1);                                                                                                               // (4) 0.04685
/*54  */         }                                                                                                                                             // (24) 0.01562
/*58  */         for(y = 0; y < height; y++) {                                                                                                                 // (9) 0.03905
/*60  */             const int modified_predictor= y ? predictor : 1;                                                                                          // (3) 0.04881
/*62  */             uint8_t *ptr = p->data[0] + (linesize * y);                                                                                               // (1) 0.06052
/*66  */             if(s->pb.buf_end - s->pb.buf - (put_bits_count(&s->pb)>>3) < width*3*4){                                                                  // 0.0
/*68  */                 av_log(s->avctx, AV_LOG_ERROR, "encoded frame too large\n");                                                                          // 0.0
/*70  */                 return -1;                                                                                                                            // 0.0
/*72  */             }                                                                                                                                         // 0.0
/*76  */             for(i=0; i<3; i++){                                                                                                                       // 0.0
/*78  */                 top[i]= left[i]= topleft[i]= buffer[0][i];                                                                                            // 0.0
/*80  */             }                                                                                                                                         // 0.0
/*82  */             for(x = 0; x < width; x++) {                                                                                                              // 0.0
/*84  */                 buffer[x][1] = ptr[4*x+0] - ptr[4*x+1] + 0x100;                                                                                       // 0.0
/*86  */                 buffer[x][2] = ptr[4*x+2] - ptr[4*x+1] + 0x100;                                                                                       // 0.0
/*88  */                 buffer[x][0] = (ptr[4*x+0] + 2*ptr[4*x+1] + ptr[4*x+2])>>2;                                                                           // 0.0
/*92  */                 for(i=0;i<3;i++) {                                                                                                                    // 0.0
/*94  */                     int pred, diff;                                                                                                                   // 0.0
/*98  */                     PREDICT(pred, topleft[i], top[i], left[i], modified_predictor);                                                                   // 0.0
/*102 */                     topleft[i]= top[i];                                                                                                               // 0.0
/*104 */                     top[i]= buffer[x+1][i];                                                                                                           // 0.0
/*108 */                     left[i]= buffer[x][i];                                                                                                            // 0.0
/*112 */                     diff= ((left[i] - pred + 0x100)&0x1FF) - 0x100;                                                                                   // 0.0
/*116 */                     if(i==0)                                                                                                                          // 0.0
/*118 */                         ff_mjpeg_encode_dc(s, diff, m->huff_size_dc_luminance, m->huff_code_dc_luminance); //FIXME ugly                               // 0.0
/*120 */                     else                                                                                                                              // 0.0
/*122 */                         ff_mjpeg_encode_dc(s, diff, m->huff_size_dc_chrominance, m->huff_code_dc_chrominance);                                        // 0.0
/*124 */                 }                                                                                                                                     // 0.0
/*126 */             }                                                                                                                                         // 0.0
/*128 */         }                                                                                                                                             // 0.0
/*130 */     }else{                                                                                                                                            // 0.0
/*132 */         int mb_x, mb_y, i;                                                                                                                            // 0.0
/*134 */         const int mb_width  = (width  + s->mjpeg_hsample[0] - 1) / s->mjpeg_hsample[0];                                                               // 0.0
/*136 */         const int mb_height = (height + s->mjpeg_vsample[0] - 1) / s->mjpeg_vsample[0];                                                               // 0.0
/*140 */         for(mb_y = 0; mb_y < mb_height; mb_y++) {                                                                                                     // 0.0
/*142 */             if(s->pb.buf_end - s->pb.buf - (put_bits_count(&s->pb)>>3) < mb_width * 4 * 3 * s->mjpeg_hsample[0] * s->mjpeg_vsample[0]){               // 0.0
/*144 */                 av_log(s->avctx, AV_LOG_ERROR, "encoded frame too large\n");                                                                          // 0.0
/*146 */                 return -1;                                                                                                                            // 0.0
/*148 */             }                                                                                                                                         // 0.0
/*150 */             for(mb_x = 0; mb_x < mb_width; mb_x++) {                                                                                                  // 0.0
/*152 */                 if(mb_x==0 || mb_y==0){                                                                                                               // 0.0
/*154 */                     for(i=0;i<3;i++) {                                                                                                                // 0.0
/*156 */                         uint8_t *ptr;                                                                                                                 // 0.0
/*158 */                         int x, y, h, v, linesize;                                                                                                     // 0.0
/*160 */                         h = s->mjpeg_hsample[i];                                                                                                      // 0.0
/*162 */                         v = s->mjpeg_vsample[i];                                                                                                      // 0.0
/*164 */                         linesize= p->linesize[i];                                                                                                     // 0.0
/*168 */                         for(y=0; y<v; y++){                                                                                                           // 0.0
/*170 */                             for(x=0; x<h; x++){                                                                                                       // 0.0
/*172 */                                 int pred;                                                                                                             // 0.0
/*176 */                                 ptr = p->data[i] + (linesize * (v * mb_y + y)) + (h * mb_x + x); //FIXME optimize this crap                           // 0.0
/*178 */                                 if(y==0 && mb_y==0){                                                                                                  // 0.0
/*180 */                                     if(x==0 && mb_x==0){                                                                                              // 0.0
/*182 */                                         pred= 128;                                                                                                    // 0.0
/*184 */                                     }else{                                                                                                            // 0.0
/*186 */                                         pred= ptr[-1];                                                                                                // 0.0
/*188 */                                     }                                                                                                                 // 0.0
/*190 */                                 }else{                                                                                                                // 0.0
/*192 */                                     if(x==0 && mb_x==0){                                                                                              // 0.0
/*194 */                                         pred= ptr[-linesize];                                                                                         // 0.0
/*196 */                                     }else{                                                                                                            // 0.0
/*198 */                                         PREDICT(pred, ptr[-linesize-1], ptr[-linesize], ptr[-1], predictor);                                          // 0.0
/*200 */                                     }                                                                                                                 // 0.0
/*202 */                                 }                                                                                                                     // 0.0
/*206 */                                 if(i==0)                                                                                                              // 0.0
/*208 */                                     ff_mjpeg_encode_dc(s, (int8_t)(*ptr - pred), m->huff_size_dc_luminance, m->huff_code_dc_luminance); //FIXME ugly  // 0.0
/*210 */                                 else                                                                                                                  // 0.0
/*212 */                                     ff_mjpeg_encode_dc(s, (int8_t)(*ptr - pred), m->huff_size_dc_chrominance, m->huff_code_dc_chrominance);           // 0.0
/*214 */                             }                                                                                                                         // 0.0
/*216 */                         }                                                                                                                             // 0.0
/*218 */                     }                                                                                                                                 // 0.0
/*220 */                 }else{                                                                                                                                // 0.0
/*222 */                     for(i=0;i<3;i++) {                                                                                                                // 0.0
/*224 */                         uint8_t *ptr;                                                                                                                 // 0.0
/*226 */                         int x, y, h, v, linesize;                                                                                                     // 0.0
/*228 */                         h = s->mjpeg_hsample[i];                                                                                                      // 0.0
/*230 */                         v = s->mjpeg_vsample[i];                                                                                                      // 0.0
/*232 */                         linesize= p->linesize[i];                                                                                                     // 0.0
/*236 */                         for(y=0; y<v; y++){                                                                                                           // 0.0
/*238 */                             for(x=0; x<h; x++){                                                                                                       // 0.0
/*240 */                                 int pred;                                                                                                             // 0.0
/*244 */                                 ptr = p->data[i] + (linesize * (v * mb_y + y)) + (h * mb_x + x); //FIXME optimize this crap                           // 0.0
/*246 */ //printf("%d %d %d %d %8X\n", mb_x, mb_y, x, y, ptr);                                                                                                 // 0.0
/*248 */                                 PREDICT(pred, ptr[-linesize-1], ptr[-linesize], ptr[-1], predictor);                                                  // 0.0
/*252 */                                 if(i==0)                                                                                                              // 0.0
/*254 */                                     ff_mjpeg_encode_dc(s, (int8_t)(*ptr - pred), m->huff_size_dc_luminance, m->huff_code_dc_luminance); //FIXME ugly  // 0.0
/*256 */                                 else                                                                                                                  // 0.0
/*258 */                                     ff_mjpeg_encode_dc(s, (int8_t)(*ptr - pred), m->huff_size_dc_chrominance, m->huff_code_dc_chrominance);           // 0.0
/*260 */                             }                                                                                                                         // 0.0
/*262 */                         }                                                                                                                             // 0.0
/*264 */                     }                                                                                                                                 // 0.0
/*266 */                 }                                                                                                                                     // 0.0
/*268 */             }                                                                                                                                         // 0.0
/*270 */         }                                                                                                                                             // 0.0
/*272 */     }                                                                                                                                                 // 0.0
/*276 */     emms_c();                                                                                                                                         // 0.0
/*280 */     ff_mjpeg_encode_picture_trailer(s);                                                                                                               // 0.0
/*282 */     s->picture_number++;                                                                                                                              // 0.0
/*286 */     flush_put_bits(&s->pb);                                                                                                                           // 0.0
/*288 */     return pbBufPtr(&s->pb) - s->pb.buf;                                                                                                              // 0.0
/*290 */ //    return (put_bits_count(&f->pb)+7)/8;                                                                                                            // 0.0
/*292 */ }                                                                                                                                                     // 0.0
