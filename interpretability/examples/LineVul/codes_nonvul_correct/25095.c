// commit message FFmpeg@2c9be3882a (target=0, prob=0.32503158, correct=True): mjpegenc_common: check for codec ID before using avctx->priv_data
/*0   */ static void jpeg_table_header(AVCodecContext *avctx, PutBitContext *p,         // (8) 0.04492
/*2   */                               ScanTable *intra_scantable,                      // (4) 0.07617
/*4   */                               uint16_t luma_intra_matrix[64],                  // (3) 0.08594
/*6   */                               uint16_t chroma_intra_matrix[64],                // (2) 0.08594
/*8   */                               int hsample[3])                                  // (5) 0.06836
/*10  */ {                                                                              // (19) 0.001953
/*12  */     int i, j, size;                                                            // (16) 0.01953
/*14  */     uint8_t *ptr;                                                              // (17) 0.01953
/*16  */     MpegEncContext *s = avctx->priv_data;                                      // (11) 0.0332
/*20  */     if (avctx->codec_id != AV_CODEC_ID_LJPEG) {                                // (7) 0.05078
/*22  */         int matrix_count = 1 + !!memcmp(luma_intra_matrix,                     // (6) 0.05273
/*24  */                                         chroma_intra_matrix,                   // (1) 0.09375
/*26  */                                         sizeof(luma_intra_matrix[0]) * 64);    // (0) 0.1074
/*28  */     if (s->force_duplicated_matrix)                                            // (13) 0.03125
/*30  */         matrix_count = 2;                                                      // (15) 0.02539
/*32  */     /* quant matrixes */                                                       // (18) 0.01562
/*34  */     put_marker(p, DQT);                                                        // (14) 0.02734
/*36  */     put_bits(p, 16, 2 + matrix_count * (1 + 64));                              // (9) 0.04297
/*38  */     put_bits(p, 4, 0); /* 8 bit precision */                                   // (10) 0.03516
/*40  */     put_bits(p, 4, 0); /* table 0 */                                           // (12) 0.0332
/*42  */     for(i=0;i<64;i++) {                                                        // 0.0
/*44  */         j = intra_scantable->permutated[i];                                    // 0.0
/*46  */         put_bits(p, 8, luma_intra_matrix[j]);                                  // 0.0
/*48  */     }                                                                          // 0.0
/*52  */         if (matrix_count > 1) {                                                // 0.0
/*54  */             put_bits(p, 4, 0); /* 8 bit precision */                           // 0.0
/*56  */             put_bits(p, 4, 1); /* table 1 */                                   // 0.0
/*58  */             for(i=0;i<64;i++) {                                                // 0.0
/*60  */                 j = intra_scantable->permutated[i];                            // 0.0
/*62  */                 put_bits(p, 8, chroma_intra_matrix[j]);                        // 0.0
/*64  */             }                                                                  // 0.0
/*66  */         }                                                                      // 0.0
/*68  */     }                                                                          // 0.0
/*72  */     if(avctx->active_thread_type & FF_THREAD_SLICE){                           // 0.0
/*74  */         put_marker(p, DRI);                                                    // 0.0
/*76  */         put_bits(p, 16, 4);                                                    // 0.0
/*78  */         put_bits(p, 16, (avctx->width-1)/(8*hsample[0]) + 1);                  // 0.0
/*80  */     }                                                                          // 0.0
/*84  */     /* huffman table */                                                        // 0.0
/*86  */     put_marker(p, DHT);                                                        // 0.0
/*88  */     flush_put_bits(p);                                                         // 0.0
/*90  */     ptr = put_bits_ptr(p);                                                     // 0.0
/*92  */     put_bits(p, 16, 0); /* patched later */                                    // 0.0
/*94  */     size = 2;                                                                  // 0.0
/*98  */     // Only MJPEG can have a variable Huffman variable. All other              // 0.0
/*100 */     // formats use the default Huffman table.                                  // 0.0
/*102 */     if (s->out_format == FMT_MJPEG && s->huffman == HUFFMAN_TABLE_OPTIMAL) {   // 0.0
/*104 */         size += put_huffman_table(p, 0, 0, s->mjpeg_ctx->bits_dc_luminance,    // 0.0
/*106 */                                   s->mjpeg_ctx->val_dc_luminance);             // 0.0
/*108 */         size += put_huffman_table(p, 0, 1, s->mjpeg_ctx->bits_dc_chrominance,  // 0.0
/*110 */                                   s->mjpeg_ctx->val_dc_chrominance);           // 0.0
/*114 */         size += put_huffman_table(p, 1, 0, s->mjpeg_ctx->bits_ac_luminance,    // 0.0
/*116 */                                   s->mjpeg_ctx->val_ac_luminance);             // 0.0
/*118 */         size += put_huffman_table(p, 1, 1, s->mjpeg_ctx->bits_ac_chrominance,  // 0.0
/*120 */                                   s->mjpeg_ctx->val_ac_chrominance);           // 0.0
/*122 */     } else {                                                                   // 0.0
/*124 */         size += put_huffman_table(p, 0, 0, avpriv_mjpeg_bits_dc_luminance,     // 0.0
/*126 */                                   avpriv_mjpeg_val_dc);                        // 0.0
/*128 */         size += put_huffman_table(p, 0, 1, avpriv_mjpeg_bits_dc_chrominance,   // 0.0
/*130 */                                   avpriv_mjpeg_val_dc);                        // 0.0
/*134 */         size += put_huffman_table(p, 1, 0, avpriv_mjpeg_bits_ac_luminance,     // 0.0
/*136 */                                   avpriv_mjpeg_val_ac_luminance);              // 0.0
/*138 */         size += put_huffman_table(p, 1, 1, avpriv_mjpeg_bits_ac_chrominance,   // 0.0
/*140 */                                   avpriv_mjpeg_val_ac_chrominance);            // 0.0
/*142 */     }                                                                          // 0.0
/*144 */     AV_WB16(ptr, size);                                                        // 0.0
/*146 */ }                                                                              // 0.0
