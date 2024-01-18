// commit message FFmpeg@fa5dacce14 (target=1, prob=0.9990895, correct=True): indeo5: check against scaleable frames in non scaleable streams.
/*0  */ static int decode_pic_hdr(IVI5DecContext *ctx, AVCodecContext *avctx)                                   // (4) 0.04883
/*1  */ {                                                                                                       // (21) 0.001953
/*2  */     if (get_bits(&ctx->gb, 5) != 0x1F) {                                                                // (8) 0.04297
/*3  */         av_log(avctx, AV_LOG_ERROR, "Invalid picture start code!\n");                                   // (3) 0.05664
/*4  */         return -1;                                                                                      // (19) 0.02148
/*5  */     ctx->prev_frame_type = ctx->frame_type;                                                             // (13) 0.03711
/*6  */     ctx->frame_type      = get_bits(&ctx->gb, 3);                                                       // (5) 0.04883
/*7  */     if (ctx->frame_type >= 5) {                                                                         // (18) 0.02734
/*8  */         av_log(avctx, AV_LOG_ERROR, "Invalid frame type: %d \n", ctx->frame_type);                      // (2) 0.07226
/*9  */         return -1;                                                                                      // (20) 0.02148
/*10 */     ctx->frame_num = get_bits(&ctx->gb, 8);                                                             // (11) 0.03906
/*11 */     if (ctx->frame_type == FRAMETYPE_INTRA) {                                                           // (9) 0.04101
/*12 */         ctx->gop_invalid = 1;                                                                           // (14) 0.03516
/*13 */         if (decode_gop_header(ctx, avctx))                                                              // (7) 0.04297
/*14 */             return -1;                                                                                  // (16) 0.0293
/*15 */         ctx->gop_invalid = 0;                                                                           // (15) 0.03516
/*16 */     if (ctx->frame_type != FRAMETYPE_NULL) {                                                            // (10) 0.03906
/*17 */         ctx->frame_flags = get_bits(&ctx->gb, 8);                                                       // (6) 0.04687
/*18 */         ctx->pic_hdr_size = (ctx->frame_flags & 1) ? get_bits_long(&ctx->gb, 24) : 0;                   // (0) 0.08203
/*19 */         ctx->checksum = (ctx->frame_flags & 0x10) ? get_bits(&ctx->gb, 16) : 0;                         // (1) 0.07422
/*20 */         /* skip unknown extension if any */                                                             // (17) 0.02735
/*21 */         if (ctx->frame_flags & 0x20)                                                                    // (12) 0.03711
/*22 */             skip_hdr_extension(&ctx->gb); /* XXX: untested */                                           // 0.0
/*23 */         /* decode macroblock huffman codebook */                                                        // 0.0
/*24 */         if (ff_ivi_dec_huff_desc(&ctx->gb, ctx->frame_flags & 0x40, IVI_MB_HUFF, &ctx->mb_vlc, avctx))  // 0.0
/*25 */             return -1;                                                                                  // 0.0
/*26 */         skip_bits(&ctx->gb, 3); /* FIXME: unknown meaning! */                                           // 0.0
/*27 */     align_get_bits(&ctx->gb);                                                                           // 0.0
/*28 */     return 0;                                                                                           // 0.0
