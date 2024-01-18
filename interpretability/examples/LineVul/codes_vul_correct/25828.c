// commit message FFmpeg@77d9889821 (target=1, prob=0.999099, correct=True): avcodec/pixlet: Fix runtime error: signed integer overflow: 2147483647 + 32 cannot be represented in type 'int'
/*0  */ static int pixlet_decode_frame(AVCodecContext *avctx, void *data,                 // (4) 0.04749
/*1  */                                int *got_frame, AVPacket *avpkt)                   // (0) 0.0856
/*2  */ {                                                                                 // (23) 0.00194
/*3  */     PixletContext *ctx = avctx->priv_data;                                        // (15) 0.03126
/*4  */     int i, w, h, width, height, ret, version;                                     // (7) 0.04379
/*5  */     AVFrame *p = data;                                                            // (20) 0.01943
/*6  */     ThreadFrame frame = { .f = data };                                            // (18) 0.02536
/*7  */     uint32_t pktsize;                                                             // (19) 0.02307
/*8  */     bytestream2_init(&ctx->gb, avpkt->data, avpkt->size);                         // (3) 0.05006
/*9  */     pktsize = bytestream2_get_be32(&ctx->gb);                                     // (9) 0.04228
/*10 */     if (pktsize <= 44 || pktsize - 4 > bytestream2_get_bytes_left(&ctx->gb)) {    // (2) 0.06726
/*11 */         av_log(avctx, AV_LOG_ERROR, "Invalid packet size %"PRIu32"\n", pktsize);  // (1) 0.07496
/*12 */     }                                                                             // (22) 0.00769
/*13 */     version = bytestream2_get_le32(&ctx->gb);                                     // (13) 0.03654
/*14 */     if (version != 1)                                                             // (21) 0.01733
/*15 */         avpriv_request_sample(avctx, "Version %d", version);                      // (5) 0.04625
/*16 */     bytestream2_skip(&ctx->gb, 4);                                                // (16) 0.03074
/*17 */     if (bytestream2_get_be32(&ctx->gb) != 1)                                      // (11) 0.04226
/*18 */     bytestream2_skip(&ctx->gb, 4);                                                // (17) 0.03074
/*19 */     width  = bytestream2_get_be32(&ctx->gb);                                      // (12) 0.03843
/*20 */     height = bytestream2_get_be32(&ctx->gb);                                      // (14) 0.03653
/*21 */     w = FFALIGN(width,  1 << (NB_LEVELS + 1));                                    // (6) 0.0444
/*22 */     h = FFALIGN(height, 1 << (NB_LEVELS + 1));                                    // (8) 0.04247
/*23 */     ctx->levels = bytestream2_get_be32(&ctx->gb);                                 // (10) 0.04227
/*24 */     if (ctx->levels != NB_LEVELS)                                                 // 0.0
/*25 */     ctx->depth = bytestream2_get_be32(&ctx->gb);                                  // 0.0
/*26 */     if (ctx->depth < 8 || ctx->depth > 15) {                                      // 0.0
/*27 */         avpriv_request_sample(avctx, "Depth %d", ctx->depth);                     // 0.0
/*28 */     }                                                                             // 0.0
/*29 */     ret = ff_set_dimensions(avctx, w, h);                                         // 0.0
/*30 */     if (ret < 0)                                                                  // 0.0
/*31 */         return ret;                                                               // 0.0
/*32 */     avctx->width  = width;                                                        // 0.0
/*33 */     avctx->height = height;                                                       // 0.0
/*34 */     if (ctx->w != w || ctx->h != h) {                                             // 0.0
/*35 */         free_buffers(avctx);                                                      // 0.0
/*36 */         ctx->w = w;                                                               // 0.0
/*37 */         ctx->h = h;                                                               // 0.0
/*38 */         ret = init_decoder(avctx);                                                // 0.0
/*39 */         if (ret < 0) {                                                            // 0.0
/*40 */             free_buffers(avctx);                                                  // 0.0
/*41 */             ctx->w = 0;                                                           // 0.0
/*42 */             ctx->h = 0;                                                           // 0.0
/*43 */             return ret;                                                           // 0.0
/*44 */         }                                                                         // 0.0
/*45 */     }                                                                             // 0.0
/*46 */     bytestream2_skip(&ctx->gb, 8);                                                // 0.0
/*47 */     p->pict_type = AV_PICTURE_TYPE_I;                                             // 0.0
/*48 */     p->key_frame = 1;                                                             // 0.0
/*49 */     p->color_range = AVCOL_RANGE_JPEG;                                            // 0.0
/*50 */     ret = ff_thread_get_buffer(avctx, &frame, 0);                                 // 0.0
/*51 */     if (ret < 0)                                                                  // 0.0
/*52 */         return ret;                                                               // 0.0
/*53 */     for (i = 0; i < 3; i++) {                                                     // 0.0
/*54 */         ret = decode_plane(avctx, i, avpkt, frame.f);                             // 0.0
/*55 */         if (ret < 0)                                                              // 0.0
/*56 */             return ret;                                                           // 0.0
/*57 */         if (avctx->flags & AV_CODEC_FLAG_GRAY)                                    // 0.0
/*58 */             break;                                                                // 0.0
/*59 */     }                                                                             // 0.0
/*60 */     postprocess_luma(frame.f, ctx->w, ctx->h, ctx->depth);                        // 0.0
/*61 */     postprocess_chroma(frame.f, ctx->w >> 1, ctx->h >> 1, ctx->depth);            // 0.0
/*62 */     *got_frame = 1;                                                               // 0.0
/*63 */     return pktsize;                                                               // 0.0
/*64 */ }                                                                                 // 0.0
