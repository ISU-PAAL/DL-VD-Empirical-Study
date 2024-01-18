// commit message FFmpeg@fd92dafaff (target=0, prob=0.6647849, correct=False): bink: Split read_dct_coeffs()
/*0   */ static int binkb_decode_plane(BinkContext *c, AVFrame *frame, BitstreamContext *bc,          // (4) 0.05469
/*2   */                               int plane_idx, int is_key, int is_chroma)                      // (0) 0.08984
/*4   */ {                                                                                            // (23) 0.001953
/*6   */     int blk, ret;                                                                            // (20) 0.01758
/*8   */     int i, j, bx, by;                                                                        // (16) 0.02539
/*10  */     uint8_t *dst, *ref, *ref_start, *ref_end;                                                // (7) 0.04687
/*12  */     int v, col[2];                                                                           // (18) 0.01953
/*14  */     const uint8_t *scan;                                                                     // (17) 0.02148
/*16  */     int xoff, yoff;                                                                          // (19) 0.01953
/*18  */     LOCAL_ALIGNED_16(int16_t, block, [64]);                                                  // (9) 0.04297
/*20  */     LOCAL_ALIGNED_16(int32_t, dctblock, [64]);                                               // (8) 0.04687
/*22  */     int coordmap[64];                                                                        // (21) 0.01758
/*24  */     int ybias = is_key ? -15 : 0;                                                            // (11) 0.0332
/*26  */     int qp;                                                                                  // (22) 0.01367
/*30  */     const int stride = frame->linesize[plane_idx];                                           // (10) 0.0332
/*32  */     int bw = is_chroma ? (c->avctx->width  + 15) >> 4 : (c->avctx->width  + 7) >> 3;         // (1) 0.07812
/*34  */     int bh = is_chroma ? (c->avctx->height + 15) >> 4 : (c->avctx->height + 7) >> 3;         // (3) 0.07422
/*38  */     binkb_init_bundles(c);                                                                   // (15) 0.0293
/*40  */     ref_start = frame->data[plane_idx];                                                      // (13) 0.03125
/*42  */     ref_end   = frame->data[plane_idx] + (bh * frame->linesize[plane_idx] + bw) * 8;         // (2) 0.07617
/*46  */     for (i = 0; i < 64; i++)                                                                 // (14) 0.0293
/*48  */         coordmap[i] = (i & 7) + (i >> 3) * stride;                                           // (6) 0.05273
/*52  */     for (by = 0; by < bh; by++) {                                                            // (12) 0.0332
/*54  */         for (i = 0; i < BINKB_NB_SRC; i++) {                                                 // (5) 0.05273
/*56  */             if ((ret = binkb_read_bundle(c, bc, i)) < 0)                                     // 0.0
/*58  */                 return ret;                                                                  // 0.0
/*60  */         }                                                                                    // 0.0
/*64  */         dst  = frame->data[plane_idx]  + 8*by*stride;                                        // 0.0
/*66  */         for (bx = 0; bx < bw; bx++, dst += 8) {                                              // 0.0
/*68  */             blk = binkb_get_value(c, BINKB_SRC_BLOCK_TYPES);                                 // 0.0
/*70  */             switch (blk) {                                                                   // 0.0
/*72  */             case 0:                                                                          // 0.0
/*74  */                 break;                                                                       // 0.0
/*76  */             case 1:                                                                          // 0.0
/*78  */                 scan = bink_patterns[bitstream_read(bc, 4)];                                 // 0.0
/*80  */                 i = 0;                                                                       // 0.0
/*82  */                 do {                                                                         // 0.0
/*84  */                     int mode = bitstream_read_bit(bc);                                       // 0.0
/*86  */                     int run  = bitstream_read(bc, binkb_runbits[i]) + 1;                     // 0.0
/*90  */                     i += run;                                                                // 0.0
/*92  */                     if (i > 64) {                                                            // 0.0
/*94  */                         av_log(c->avctx, AV_LOG_ERROR, "Run went out of bounds\n");          // 0.0
/*96  */                         return AVERROR_INVALIDDATA;                                          // 0.0
/*98  */                     }                                                                        // 0.0
/*100 */                     if (mode) {                                                              // 0.0
/*102 */                         v = binkb_get_value(c, BINKB_SRC_COLORS);                            // 0.0
/*104 */                         for (j = 0; j < run; j++)                                            // 0.0
/*106 */                             dst[coordmap[*scan++]] = v;                                      // 0.0
/*108 */                     } else {                                                                 // 0.0
/*110 */                         for (j = 0; j < run; j++)                                            // 0.0
/*112 */                             dst[coordmap[*scan++]] = binkb_get_value(c, BINKB_SRC_COLORS);   // 0.0
/*114 */                     }                                                                        // 0.0
/*116 */                 } while (i < 63);                                                            // 0.0
/*118 */                 if (i == 63)                                                                 // 0.0
/*120 */                     dst[coordmap[*scan++]] = binkb_get_value(c, BINKB_SRC_COLORS);           // 0.0
/*122 */                 break;                                                                       // 0.0
/*124 */             case 2:                                                                          // 0.0
/*126 */                 memset(dctblock, 0, sizeof(*dctblock) * 64);                                 // 0.0
/*128 */                 dctblock[0] = binkb_get_value(c, BINKB_SRC_INTRA_DC);                        // 0.0
/*130 */                 qp = binkb_get_value(c, BINKB_SRC_INTRA_Q);                                  // 0.0
/*132 */                 read_dct_coeffs(bc, dctblock, bink_scan, binkb_intra_quant, qp);             // 0.0
/*134 */                 c->binkdsp.idct_put(dst, stride, dctblock);                                  // 0.0
/*136 */                 break;                                                                       // 0.0
/*138 */             case 3:                                                                          // 0.0
/*140 */                 xoff = binkb_get_value(c, BINKB_SRC_X_OFF);                                  // 0.0
/*142 */                 yoff = binkb_get_value(c, BINKB_SRC_Y_OFF) + ybias;                          // 0.0
/*144 */                 ref = dst + xoff + yoff * stride;                                            // 0.0
/*146 */                 if (ref < ref_start || ref + 8*stride > ref_end) {                           // 0.0
/*148 */                     av_log(c->avctx, AV_LOG_WARNING, "Reference block is out of bounds\n");  // 0.0
/*150 */                 } else if (ref + 8*stride < dst || ref >= dst + 8*stride) {                  // 0.0
/*152 */                     c->hdsp.put_pixels_tab[1][0](dst, ref, stride, 8);                       // 0.0
/*154 */                 } else {                                                                     // 0.0
/*156 */                     put_pixels8x8_overlapped(dst, ref, stride);                              // 0.0
/*158 */                 }                                                                            // 0.0
/*160 */                 c->bdsp.clear_block(block);                                                  // 0.0
/*162 */                 v = binkb_get_value(c, BINKB_SRC_INTER_COEFS);                               // 0.0
/*164 */                 read_residue(bc, block, v);                                                  // 0.0
/*166 */                 c->binkdsp.add_pixels8(dst, block, stride);                                  // 0.0
/*168 */                 break;                                                                       // 0.0
/*170 */             case 4:                                                                          // 0.0
/*172 */                 xoff = binkb_get_value(c, BINKB_SRC_X_OFF);                                  // 0.0
/*174 */                 yoff = binkb_get_value(c, BINKB_SRC_Y_OFF) + ybias;                          // 0.0
/*176 */                 ref = dst + xoff + yoff * stride;                                            // 0.0
/*178 */                 if (ref < ref_start || ref + 8 * stride > ref_end) {                         // 0.0
/*180 */                     av_log(c->avctx, AV_LOG_WARNING, "Reference block is out of bounds\n");  // 0.0
/*182 */                 } else if (ref + 8*stride < dst || ref >= dst + 8*stride) {                  // 0.0
/*184 */                     c->hdsp.put_pixels_tab[1][0](dst, ref, stride, 8);                       // 0.0
/*186 */                 } else {                                                                     // 0.0
/*188 */                     put_pixels8x8_overlapped(dst, ref, stride);                              // 0.0
/*190 */                 }                                                                            // 0.0
/*192 */                 memset(dctblock, 0, sizeof(*dctblock) * 64);                                 // 0.0
/*194 */                 dctblock[0] = binkb_get_value(c, BINKB_SRC_INTER_DC);                        // 0.0
/*196 */                 qp = binkb_get_value(c, BINKB_SRC_INTER_Q);                                  // 0.0
/*198 */                 read_dct_coeffs(bc, dctblock, bink_scan, binkb_inter_quant, qp);             // 0.0
/*200 */                 c->binkdsp.idct_add(dst, stride, dctblock);                                  // 0.0
/*202 */                 break;                                                                       // 0.0
/*204 */             case 5:                                                                          // 0.0
/*206 */                 v = binkb_get_value(c, BINKB_SRC_COLORS);                                    // 0.0
/*208 */                 c->bdsp.fill_block_tab[1](dst, v, stride, 8);                                // 0.0
/*210 */                 break;                                                                       // 0.0
/*212 */             case 6:                                                                          // 0.0
/*214 */                 for (i = 0; i < 2; i++)                                                      // 0.0
/*216 */                     col[i] = binkb_get_value(c, BINKB_SRC_COLORS);                           // 0.0
/*218 */                 for (i = 0; i < 8; i++) {                                                    // 0.0
/*220 */                     v = binkb_get_value(c, BINKB_SRC_PATTERN);                               // 0.0
/*222 */                     for (j = 0; j < 8; j++, v >>= 1)                                         // 0.0
/*224 */                         dst[i*stride + j] = col[v & 1];                                      // 0.0
/*226 */                 }                                                                            // 0.0
/*228 */                 break;                                                                       // 0.0
/*230 */             case 7:                                                                          // 0.0
/*232 */                 xoff = binkb_get_value(c, BINKB_SRC_X_OFF);                                  // 0.0
/*234 */                 yoff = binkb_get_value(c, BINKB_SRC_Y_OFF) + ybias;                          // 0.0
/*236 */                 ref = dst + xoff + yoff * stride;                                            // 0.0
/*238 */                 if (ref < ref_start || ref + 8 * stride > ref_end) {                         // 0.0
/*240 */                     av_log(c->avctx, AV_LOG_WARNING, "Reference block is out of bounds\n");  // 0.0
/*242 */                 } else if (ref + 8*stride < dst || ref >= dst + 8*stride) {                  // 0.0
/*244 */                     c->hdsp.put_pixels_tab[1][0](dst, ref, stride, 8);                       // 0.0
/*246 */                 } else {                                                                     // 0.0
/*248 */                     put_pixels8x8_overlapped(dst, ref, stride);                              // 0.0
/*250 */                 }                                                                            // 0.0
/*252 */                 break;                                                                       // 0.0
/*254 */             case 8:                                                                          // 0.0
/*256 */                 for (i = 0; i < 8; i++)                                                      // 0.0
/*258 */                     memcpy(dst + i*stride, c->bundle[BINKB_SRC_COLORS].cur_ptr + i*8, 8);    // 0.0
/*260 */                 c->bundle[BINKB_SRC_COLORS].cur_ptr += 64;                                   // 0.0
/*262 */                 break;                                                                       // 0.0
/*264 */             default:                                                                         // 0.0
/*266 */                 av_log(c->avctx, AV_LOG_ERROR, "Unknown block type %d\n", blk);              // 0.0
/*268 */                 return AVERROR_INVALIDDATA;                                                  // 0.0
/*270 */             }                                                                                // 0.0
/*272 */         }                                                                                    // 0.0
/*274 */     }                                                                                        // 0.0
/*276 */     if (bitstream_tell(bc) & 0x1F) // next plane data starts at 32-bit boundary              // 0.0
/*278 */         bitstream_skip(bc, 32 - (bitstream_tell(bc) & 0x1F));                                // 0.0
/*282 */     return 0;                                                                                // 0.0
/*284 */ }                                                                                            // 0.0
