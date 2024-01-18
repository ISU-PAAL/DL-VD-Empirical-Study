// commit message FFmpeg@80387f0e25 (target=1, prob=0.4920404, correct=False): mimic: don't use self as reference, and report completion at end of decode().
/*0   */ static int mimic_decode_frame(AVCodecContext *avctx, void *data,                                // (8) 0.04102
/*2   */                               int *data_size, AVPacket *avpkt)                                  // (0) 0.08398
/*4   */ {                                                                                               // (26) 0.001954
/*6   */     const uint8_t *buf = avpkt->data;                                                           // (15) 0.0332
/*8   */     int buf_size = avpkt->size;                                                                 // (17) 0.02734
/*10  */     MimicContext *ctx = avctx->priv_data;                                                       // (16) 0.03125
/*12  */     GetByteContext gb;                                                                          // (23) 0.01758
/*14  */     int is_pframe;                                                                              // (22) 0.01758
/*16  */     int width, height;                                                                          // (24) 0.01562
/*18  */     int quality, num_coeffs;                                                                    // (19) 0.02344
/*20  */     int swap_buf_size = buf_size - MIMIC_HEADER_SIZE;                                           // (2) 0.04492
/*24  */     if (buf_size <= MIMIC_HEADER_SIZE) {                                                        // (12) 0.03711
/*26  */         av_log(avctx, AV_LOG_ERROR, "insufficient data\n");                                     // (1) 0.05273
/*28  */         return -1;                                                                              // (20) 0.02148
/*30  */     }                                                                                           // (25) 0.007812
/*34  */     bytestream2_init(&gb, buf, MIMIC_HEADER_SIZE);                                              // (4) 0.04492
/*36  */     bytestream2_skip(&gb, 2); /* some constant (always 256) */                                  // (7) 0.04297
/*38  */     quality    = bytestream2_get_le16u(&gb);                                                    // (9) 0.04102
/*40  */     width      = bytestream2_get_le16u(&gb);                                                    // (3) 0.04492
/*42  */     height     = bytestream2_get_le16u(&gb);                                                    // (6) 0.04297
/*44  */     bytestream2_skip(&gb, 4); /* some constant */                                               // (14) 0.03516
/*46  */     is_pframe  = bytestream2_get_le32u(&gb);                                                    // (5) 0.04297
/*48  */     num_coeffs = bytestream2_get_byteu(&gb);                                                    // (10) 0.04102
/*50  */     bytestream2_skip(&gb, 3); /* some constant */                                               // (13) 0.03516
/*54  */     if(!ctx->avctx) {                                                                           // (18) 0.02344
/*56  */         int i;                                                                                  // (21) 0.01953
/*60  */         if(!(width == 160 && height == 120) &&                                                  // (11) 0.03906
/*62  */            !(width == 320 && height == 240)) {                                                  // 0.0
/*64  */             av_log(avctx, AV_LOG_ERROR, "invalid width/height!\n");                             // 0.0
/*66  */             return -1;                                                                          // 0.0
/*68  */         }                                                                                       // 0.0
/*72  */         ctx->avctx     = avctx;                                                                 // 0.0
/*74  */         avctx->width   = width;                                                                 // 0.0
/*76  */         avctx->height  = height;                                                                // 0.0
/*78  */         avctx->pix_fmt = PIX_FMT_YUV420P;                                                       // 0.0
/*80  */         for(i = 0; i < 3; i++) {                                                                // 0.0
/*82  */             ctx->num_vblocks[i] = -((-height) >> (3 + !!i));                                    // 0.0
/*84  */             ctx->num_hblocks[i] =     width   >> (3 + !!i) ;                                    // 0.0
/*86  */         }                                                                                       // 0.0
/*88  */     } else if(width != ctx->avctx->width || height != ctx->avctx->height) {                     // 0.0
/*90  */         av_log(avctx, AV_LOG_ERROR, "resolution changing is not supported\n");                  // 0.0
/*92  */         return -1;                                                                              // 0.0
/*94  */     }                                                                                           // 0.0
/*98  */     if(is_pframe && !ctx->buf_ptrs[ctx->prev_index].data[0]) {                                  // 0.0
/*100 */         av_log(avctx, AV_LOG_ERROR, "decoding must start with keyframe\n");                     // 0.0
/*102 */         return -1;                                                                              // 0.0
/*104 */     }                                                                                           // 0.0
/*108 */     ctx->buf_ptrs[ctx->cur_index].reference = 1;                                                // 0.0
/*110 */     ctx->buf_ptrs[ctx->cur_index].pict_type = is_pframe ? AV_PICTURE_TYPE_P:AV_PICTURE_TYPE_I;  // 0.0
/*112 */     if(ff_thread_get_buffer(avctx, &ctx->buf_ptrs[ctx->cur_index])) {                           // 0.0
/*114 */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                                   // 0.0
/*116 */         return -1;                                                                              // 0.0
/*118 */     }                                                                                           // 0.0
/*122 */     ctx->next_prev_index = ctx->cur_index;                                                      // 0.0
/*124 */     ctx->next_cur_index  = (ctx->cur_index - 1) & 15;                                           // 0.0
/*128 */     prepare_avpic(ctx, &ctx->flipped_ptrs[ctx->cur_index],                                      // 0.0
/*130 */                   (AVPicture*) &ctx->buf_ptrs[ctx->cur_index]);                                 // 0.0
/*134 */     ff_thread_finish_setup(avctx);                                                              // 0.0
/*138 */     av_fast_malloc(&ctx->swap_buf, &ctx->swap_buf_size,                                         // 0.0
/*140 */                                  swap_buf_size + FF_INPUT_BUFFER_PADDING_SIZE);                 // 0.0
/*142 */     if(!ctx->swap_buf)                                                                          // 0.0
/*144 */         return AVERROR(ENOMEM);                                                                 // 0.0
/*148 */     ctx->dsp.bswap_buf(ctx->swap_buf,                                                           // 0.0
/*150 */                         (const uint32_t*) (buf + MIMIC_HEADER_SIZE),                            // 0.0
/*152 */                         swap_buf_size>>2);                                                      // 0.0
/*154 */     init_get_bits(&ctx->gb, ctx->swap_buf, swap_buf_size << 3);                                 // 0.0
/*158 */     if(!decode(ctx, quality, num_coeffs, !is_pframe)) {                                         // 0.0
/*160 */         if (avctx->active_thread_type&FF_THREAD_FRAME)                                          // 0.0
/*162 */             ff_thread_report_progress(&ctx->buf_ptrs[ctx->cur_index], INT_MAX, 0);              // 0.0
/*164 */         else {                                                                                  // 0.0
/*166 */             ff_thread_release_buffer(avctx, &ctx->buf_ptrs[ctx->cur_index]);                    // 0.0
/*168 */             return -1;                                                                          // 0.0
/*170 */         }                                                                                       // 0.0
/*172 */     }                                                                                           // 0.0
/*176 */     *(AVFrame*)data = ctx->buf_ptrs[ctx->cur_index];                                            // 0.0
/*178 */     *data_size = sizeof(AVFrame);                                                               // 0.0
/*182 */     ctx->prev_index = ctx->next_prev_index;                                                     // 0.0
/*184 */     ctx->cur_index  = ctx->next_cur_index;                                                      // 0.0
/*188 */     /* Only release frames that aren't used for backreferences anymore */                       // 0.0
/*190 */     if(ctx->buf_ptrs[ctx->cur_index].data[0])                                                   // 0.0
/*192 */         ff_thread_release_buffer(avctx, &ctx->buf_ptrs[ctx->cur_index]);                        // 0.0
/*196 */     return buf_size;                                                                            // 0.0
/*198 */ }                                                                                               // 0.0
