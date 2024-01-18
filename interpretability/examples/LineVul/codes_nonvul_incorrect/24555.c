// commit message FFmpeg@f3c0e0bf6f (target=0, prob=0.66804224, correct=False): avcodec/dnxhddec: treat pix_fmt like width/height
/*0   */ static int dnxhd_decode_header(DNXHDContext *ctx, AVFrame *frame,                 // (8) 0.04688
/*2   */                                const uint8_t *buf, int buf_size,                  // (0) 0.08398
/*4   */                                int first_field)                                   // (4) 0.06836
/*6   */ {                                                                                 // (20) 0.001953
/*8   */     static const uint8_t header_prefix[]    = { 0x00, 0x00, 0x02, 0x80, 0x01 };   // (2) 0.07422
/*10  */     static const uint8_t header_prefix444[] = { 0x00, 0x00, 0x02, 0x80, 0x02 };   // (3) 0.07031
/*12  */     int i, cid, ret;                                                              // (17) 0.02148
/*16  */     if (buf_size < 0x280)                                                         // (16) 0.02539
/*18  */         return AVERROR_INVALIDDATA;                                               // (14) 0.0332
/*22  */     if (memcmp(buf, header_prefix, 5) && memcmp(buf, header_prefix444, 5)) {      // (5) 0.05859
/*24  */         av_log(ctx->avctx, AV_LOG_ERROR, "error in header\n");                    // (6) 0.05664
/*26  */         return AVERROR_INVALIDDATA;                                               // (15) 0.0332
/*28  */     }                                                                             // (19) 0.007812
/*30  */     if (buf[5] & 2) { /* interlaced */                                            // (12) 0.03516
/*32  */         ctx->cur_field = buf[5] & 1;                                              // (10) 0.04102
/*34  */         frame->interlaced_frame = 1;                                              // (13) 0.0332
/*36  */         frame->top_field_first  = first_field ^ ctx->cur_field;                   // (7) 0.05273
/*38  */         av_log(ctx->avctx, AV_LOG_DEBUG,                                          // (9) 0.04297
/*40  */                "interlaced %d, cur field %d\n", buf[5] & 3, ctx->cur_field);      // (1) 0.08203
/*42  */     }                                                                             // (18) 0.007812
/*46  */     ctx->height = AV_RB16(buf + 0x18);                                            // (11) 0.03711
/*48  */     ctx->width  = AV_RB16(buf + 0x1a);                                            // 0.0
/*52  */     av_dlog(ctx->avctx, "width %d, height %d\n", ctx->width, ctx->height);        // 0.0
/*56  */     ctx->is_444 = 0;                                                              // 0.0
/*58  */     if (buf[0x4] == 0x2) {                                                        // 0.0
/*60  */         ctx->avctx->pix_fmt = AV_PIX_FMT_YUV444P10;                               // 0.0
/*62  */         ctx->avctx->bits_per_raw_sample = 10;                                     // 0.0
/*64  */         if (ctx->bit_depth != 10) {                                               // 0.0
/*66  */             ff_blockdsp_init(&ctx->bdsp, ctx->avctx);                             // 0.0
/*68  */             ff_idctdsp_init(&ctx->idsp, ctx->avctx);                              // 0.0
/*70  */             ctx->bit_depth = 10;                                                  // 0.0
/*72  */             ctx->decode_dct_block = dnxhd_decode_dct_block_10_444;                // 0.0
/*74  */         }                                                                         // 0.0
/*76  */         ctx->is_444 = 1;                                                          // 0.0
/*78  */     } else if (buf[0x21] & 0x40) {                                                // 0.0
/*80  */         ctx->avctx->pix_fmt = AV_PIX_FMT_YUV422P10;                               // 0.0
/*82  */         ctx->avctx->bits_per_raw_sample = 10;                                     // 0.0
/*84  */         if (ctx->bit_depth != 10) {                                               // 0.0
/*86  */             ff_blockdsp_init(&ctx->bdsp, ctx->avctx);                             // 0.0
/*88  */             ff_idctdsp_init(&ctx->idsp, ctx->avctx);                              // 0.0
/*90  */             ctx->bit_depth = 10;                                                  // 0.0
/*92  */             ctx->decode_dct_block = dnxhd_decode_dct_block_10;                    // 0.0
/*94  */         }                                                                         // 0.0
/*96  */     } else {                                                                      // 0.0
/*98  */         ctx->avctx->pix_fmt = AV_PIX_FMT_YUV422P;                                 // 0.0
/*100 */         ctx->avctx->bits_per_raw_sample = 8;                                      // 0.0
/*102 */         if (ctx->bit_depth != 8) {                                                // 0.0
/*104 */             ff_blockdsp_init(&ctx->bdsp, ctx->avctx);                             // 0.0
/*106 */             ff_idctdsp_init(&ctx->idsp, ctx->avctx);                              // 0.0
/*108 */             ctx->bit_depth = 8;                                                   // 0.0
/*110 */             ctx->decode_dct_block = dnxhd_decode_dct_block_8;                     // 0.0
/*112 */         }                                                                         // 0.0
/*114 */     }                                                                             // 0.0
/*118 */     cid = AV_RB32(buf + 0x28);                                                    // 0.0
/*120 */     av_dlog(ctx->avctx, "compression id %d\n", cid);                              // 0.0
/*124 */     if ((ret = dnxhd_init_vlc(ctx, cid)) < 0)                                     // 0.0
/*126 */         return ret;                                                               // 0.0
/*130 */     if (buf_size < ctx->cid_table->coding_unit_size) {                            // 0.0
/*132 */         av_log(ctx->avctx, AV_LOG_ERROR, "incorrect frame size\n");               // 0.0
/*134 */         return AVERROR_INVALIDDATA;                                               // 0.0
/*136 */     }                                                                             // 0.0
/*140 */     ctx->mb_width  = ctx->width >> 4;                                             // 0.0
/*142 */     ctx->mb_height = buf[0x16d];                                                  // 0.0
/*146 */     av_dlog(ctx->avctx,                                                           // 0.0
/*148 */             "mb width %d, mb height %d\n", ctx->mb_width, ctx->mb_height);        // 0.0
/*152 */     if ((ctx->height + 15) >> 4 == ctx->mb_height && frame->interlaced_frame)     // 0.0
/*154 */         ctx->height <<= 1;                                                        // 0.0
/*158 */     if (ctx->mb_height > 68 ||                                                    // 0.0
/*160 */         (ctx->mb_height << frame->interlaced_frame) > (ctx->height + 15) >> 4) {  // 0.0
/*162 */         av_log(ctx->avctx, AV_LOG_ERROR,                                          // 0.0
/*164 */                "mb height too big: %d\n", ctx->mb_height);                        // 0.0
/*166 */         return AVERROR_INVALIDDATA;                                               // 0.0
/*168 */     }                                                                             // 0.0
/*172 */     for (i = 0; i < ctx->mb_height; i++) {                                        // 0.0
/*174 */         ctx->mb_scan_index[i] = AV_RB32(buf + 0x170 + (i << 2));                  // 0.0
/*176 */         av_dlog(ctx->avctx, "mb scan index %d\n", ctx->mb_scan_index[i]);         // 0.0
/*178 */         if (buf_size < ctx->mb_scan_index[i] + 0x280LL) {                         // 0.0
/*180 */             av_log(ctx->avctx, AV_LOG_ERROR, "invalid mb scan index\n");          // 0.0
/*182 */             return AVERROR_INVALIDDATA;                                           // 0.0
/*184 */         }                                                                         // 0.0
/*186 */     }                                                                             // 0.0
/*190 */     return 0;                                                                     // 0.0
/*192 */ }                                                                                 // 0.0
