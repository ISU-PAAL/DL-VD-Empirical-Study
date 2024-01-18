// commit message FFmpeg@be00ec832c (target=0, prob=0.4901489, correct=True): lavc: Deprecate coder_type and its symbols
/*0   */ static int targa_encode_frame(AVCodecContext *avctx, AVPacket *pkt,                      // (6) 0.04883
/*2   */                               const AVFrame *p, int *got_packet)                         // (1) 0.08203
/*4   */ {                                                                                        // (22) 0.001953
/*6   */     int bpp, picsize, datasize = -1, ret;                                                // (12) 0.03516
/*8   */     uint8_t *out;                                                                        // (18) 0.01953
/*12  */     if(avctx->width > 0xffff || avctx->height > 0xffff) {                                // (8) 0.04687
/*14  */         av_log(avctx, AV_LOG_ERROR, "image dimensions too large\n");                     // (4) 0.05469
/*16  */         return AVERROR(EINVAL);                                                          // (13) 0.03125
/*18  */     }                                                                                    // (21) 0.007812
/*20  */     picsize = av_image_get_buffer_size(avctx->pix_fmt,                                   // (7) 0.04883
/*22  */                                        avctx->width, avctx->height, 1);                  // (0) 0.09766
/*24  */     if ((ret = ff_alloc_packet(pkt, picsize + 45)) < 0) {                                // (5) 0.05078
/*26  */         av_log(avctx, AV_LOG_ERROR, "encoded frame too large\n");                        // (3) 0.05664
/*28  */         return ret;                                                                      // (19) 0.01953
/*30  */     }                                                                                    // (20) 0.007813
/*34  */     /* zero out the header and only set applicable fields */                             // (17) 0.02734
/*36  */     memset(pkt->data, 0, 12);                                                            // (15) 0.0293
/*38  */     AV_WL16(pkt->data+12, avctx->width);                                                 // (11) 0.04102
/*40  */     AV_WL16(pkt->data+14, avctx->height);                                                // (10) 0.04102
/*42  */     /* image descriptor byte: origin is always top-left, bits 0-3 specify alpha */       // (9) 0.04297
/*44  */     pkt->data[17] = 0x20 | (avctx->pix_fmt == AV_PIX_FMT_BGRA ? 8 : 0);                  // (2) 0.07812
/*48  */     switch(avctx->pix_fmt) {                                                             // (16) 0.0293
/*50  */     case AV_PIX_FMT_GRAY8:                                                               // (14) 0.03125
/*52  */         pkt->data[2]  = TGA_BW;     /* uncompressed grayscale image */                   // 0.0
/*54  */         pkt->data[16] = 8;          /* bpp */                                            // 0.0
/*56  */         break;                                                                           // 0.0
/*58  */     case AV_PIX_FMT_RGB555LE:                                                            // 0.0
/*60  */         pkt->data[2]  = TGA_RGB;    /* uncompresses true-color image */                  // 0.0
/*62  */         pkt->data[16] = 16;         /* bpp */                                            // 0.0
/*64  */         break;                                                                           // 0.0
/*66  */     case AV_PIX_FMT_BGR24:                                                               // 0.0
/*68  */         pkt->data[2]  = TGA_RGB;    /* uncompressed true-color image */                  // 0.0
/*70  */         pkt->data[16] = 24;         /* bpp */                                            // 0.0
/*72  */         break;                                                                           // 0.0
/*74  */     case AV_PIX_FMT_BGRA:                                                                // 0.0
/*76  */         pkt->data[2]  = TGA_RGB;    /* uncompressed true-color image */                  // 0.0
/*78  */         pkt->data[16] = 32;         /* bpp */                                            // 0.0
/*80  */         break;                                                                           // 0.0
/*82  */     default:                                                                             // 0.0
/*84  */         av_log(avctx, AV_LOG_ERROR, "Pixel format '%s' not supported.\n",                // 0.0
/*86  */                av_get_pix_fmt_name(avctx->pix_fmt));                                     // 0.0
/*88  */         return AVERROR(EINVAL);                                                          // 0.0
/*90  */     }                                                                                    // 0.0
/*92  */     bpp = pkt->data[16] >> 3;                                                            // 0.0
/*96  */     out = pkt->data + 18;  /* skip past the header we just output */                     // 0.0
/*100 */     /* try RLE compression */                                                            // 0.0
/*102 */     if (avctx->coder_type != FF_CODER_TYPE_RAW)                                          // 0.0
/*104 */         datasize = targa_encode_rle(out, picsize, p, bpp, avctx->width, avctx->height);  // 0.0
/*108 */     /* if that worked well, mark the picture as RLE compressed */                        // 0.0
/*110 */     if(datasize >= 0)                                                                    // 0.0
/*112 */         pkt->data[2] |= 8;                                                               // 0.0
/*116 */     /* if RLE didn't make it smaller, go back to no compression */                       // 0.0
/*118 */     else datasize = targa_encode_normal(out, p, bpp, avctx->width, avctx->height);       // 0.0
/*122 */     out += datasize;                                                                     // 0.0
/*126 */     /* The standard recommends including this section, even if we don't use              // 0.0
/*128 */      * any of the features it affords. TODO: take advantage of the pixel                 // 0.0
/*130 */      * aspect ratio and encoder ID fields available? */                                  // 0.0
/*132 */     memcpy(out, "\0\0\0\0\0\0\0\0TRUEVISION-XFILE.", 26);                                // 0.0
/*136 */     pkt->size   = out + 26 - pkt->data;                                                  // 0.0
/*138 */     pkt->flags |= AV_PKT_FLAG_KEY;                                                       // 0.0
/*140 */     *got_packet = 1;                                                                     // 0.0
/*144 */     return 0;                                                                            // 0.0
/*146 */ }                                                                                        // 0.0
