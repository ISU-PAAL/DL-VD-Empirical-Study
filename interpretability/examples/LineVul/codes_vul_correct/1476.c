// commit message FFmpeg@eb465b8c56 (target=1, prob=0.7031957, correct=True): avfilter/vf_uspp: clear AVPacket to not leave uninitialized memory
/*0   */ static void filter(USPPContext *p, uint8_t *dst[3], uint8_t *src[3],                                                         // (4) 0.05664
/*2   */                    int dst_stride[3], int src_stride[3], int width,                                                          // (3) 0.07227
/*4   */                    int height, uint8_t *qp_store, int qp_stride)                                                             // (2) 0.07422
/*6   */ {                                                                                                                            // (18) 0.001953
/*8   */     int x, y, i, j;                                                                                                          // (17) 0.02344
/*10  */     const int count = 1<<p->log2_count;                                                                                      // (13) 0.03125
/*14  */     for (i = 0; i < 3; i++) {                                                                                                // (14) 0.03125
/*16  */         int is_chroma = !!i;                                                                                                 // (15) 0.03125
/*18  */         int w = width  >> (is_chroma ? p->hsub : 0);                                                                         // (6) 0.05078
/*20  */         int h = height >> (is_chroma ? p->vsub : 0);                                                                         // (7) 0.04883
/*22  */         int stride = p->temp_stride[i];                                                                                      // (12) 0.03711
/*24  */         int block = BLOCK >> (is_chroma ? p->hsub : 0);                                                                      // (5) 0.05078
/*28  */         if (!src[i] || !dst[i])                                                                                              // (10) 0.03906
/*30  */             continue;                                                                                                        // (16) 0.02539
/*32  */         for (y = 0; y < h; y++) {                                                                                            // (11) 0.03906
/*34  */             int index = block + block * stride + y * stride;                                                                 // (8) 0.04687
/*38  */             memcpy(p->src[i] + index, src[i] + y * src_stride[i], w );                                                       // (1) 0.07812
/*40  */             for (x = 0; x < block; x++) {                                                                                    // (9) 0.04687
/*42  */                 p->src[i][index     - x - 1] = p->src[i][index +     x    ];                                                 // (0) 0.0957
/*44  */                 p->src[i][index + w + x    ] = p->src[i][index + w - x - 1];                                                 // 0.0
/*46  */             }                                                                                                                // 0.0
/*48  */         }                                                                                                                    // 0.0
/*50  */         for (y = 0; y < block; y++) {                                                                                        // 0.0
/*52  */             memcpy(p->src[i] + (  block-1-y) * stride, p->src[i] + (  y+block  ) * stride, stride);                          // 0.0
/*54  */             memcpy(p->src[i] + (h+block  +y) * stride, p->src[i] + (h-y+block-1) * stride, stride);                          // 0.0
/*56  */         }                                                                                                                    // 0.0
/*60  */         p->frame->linesize[i] = stride;                                                                                      // 0.0
/*62  */         memset(p->temp[i], 0, (h + 2 * block) * stride * sizeof(int16_t));                                                   // 0.0
/*64  */     }                                                                                                                        // 0.0
/*68  */     if (p->qp)                                                                                                               // 0.0
/*70  */         p->frame->quality = p->qp * FF_QP2LAMBDA;                                                                            // 0.0
/*72  */     else {                                                                                                                   // 0.0
/*74  */         int qpsum=0;                                                                                                         // 0.0
/*76  */         int qpcount = (height>>4) * (height>>4);                                                                             // 0.0
/*80  */         for (y = 0; y < (height>>4); y++) {                                                                                  // 0.0
/*82  */             for (x = 0; x < (width>>4); x++)                                                                                 // 0.0
/*84  */                 qpsum += qp_store[x + y * qp_stride];                                                                        // 0.0
/*86  */         }                                                                                                                    // 0.0
/*88  */         p->frame->quality = norm_qscale((qpsum + qpcount/2) / qpcount, p->qscale_type) * FF_QP2LAMBDA;                       // 0.0
/*90  */     }                                                                                                                        // 0.0
/*92  */ //    init per MB qscale stuff FIXME                                                                                         // 0.0
/*94  */     p->frame->height = height;                                                                                               // 0.0
/*96  */     p->frame->width  = width;                                                                                                // 0.0
/*100 */     for (i = 0; i < count; i++) {                                                                                            // 0.0
/*102 */         const int x1 = offset[i+count-1][0];                                                                                 // 0.0
/*104 */         const int y1 = offset[i+count-1][1];                                                                                 // 0.0
/*106 */         const int x1c = x1 >> p->hsub;                                                                                       // 0.0
/*108 */         const int y1c = y1 >> p->vsub;                                                                                       // 0.0
/*110 */         const int BLOCKc = BLOCK >> p->hsub;                                                                                 // 0.0
/*112 */         int offset;                                                                                                          // 0.0
/*114 */         AVPacket pkt;                                                                                                        // 0.0
/*116 */         int got_pkt_ptr;                                                                                                     // 0.0
/*120 */         av_init_packet(&pkt);                                                                                                // 0.0
/*122 */         pkt.data = p->outbuf;                                                                                                // 0.0
/*124 */         pkt.size = p->outbuf_size;                                                                                           // 0.0
/*128 */         p->frame->data[0] = p->src[0] + x1   + y1   * p->frame->linesize[0];                                                 // 0.0
/*130 */         p->frame->data[1] = p->src[1] + x1c  + y1c  * p->frame->linesize[1];                                                 // 0.0
/*132 */         p->frame->data[2] = p->src[2] + x1c  + y1c  * p->frame->linesize[2];                                                 // 0.0
/*134 */         p->frame->format  = p->avctx_enc[i]->pix_fmt;                                                                        // 0.0
/*138 */         avcodec_encode_video2(p->avctx_enc[i], &pkt, p->frame, &got_pkt_ptr);                                                // 0.0
/*140 */         p->frame_dec = p->avctx_enc[i]->coded_frame;                                                                         // 0.0
/*144 */         offset = (BLOCK-x1) + (BLOCK-y1) * p->frame_dec->linesize[0];                                                        // 0.0
/*148 */         for (y = 0; y < height; y++)                                                                                         // 0.0
/*150 */             for (x = 0; x < width; x++)                                                                                      // 0.0
/*152 */                 p->temp[0][x + y * p->temp_stride[0]] += p->frame_dec->data[0][x + y * p->frame_dec->linesize[0] + offset];  // 0.0
/*156 */         if (!src[2] || !dst[2])                                                                                              // 0.0
/*158 */             continue;                                                                                                        // 0.0
/*162 */         offset = (BLOCKc-x1c) + (BLOCKc-y1c) * p->frame_dec->linesize[1];                                                    // 0.0
/*166 */         for (y = 0; y < height>>p->vsub; y++) {                                                                              // 0.0
/*168 */             for (x = 0; x < width>>p->hsub; x++) {                                                                           // 0.0
/*170 */                 p->temp[1][x + y * p->temp_stride[1]] += p->frame_dec->data[1][x + y * p->frame_dec->linesize[1] + offset];  // 0.0
/*172 */                 p->temp[2][x + y * p->temp_stride[2]] += p->frame_dec->data[2][x + y * p->frame_dec->linesize[2] + offset];  // 0.0
/*174 */             }                                                                                                                // 0.0
/*176 */         }                                                                                                                    // 0.0
/*178 */     }                                                                                                                        // 0.0
/*182 */     for (j = 0; j < 3; j++) {                                                                                                // 0.0
/*184 */         int is_chroma = !!j;                                                                                                 // 0.0
/*186 */         if (!dst[j])                                                                                                         // 0.0
/*188 */             continue;                                                                                                        // 0.0
/*190 */         store_slice_c(dst[j], p->temp[j], dst_stride[j], p->temp_stride[j],                                                  // 0.0
/*192 */                       width  >> (is_chroma ? p->hsub : 0),                                                                   // 0.0
/*194 */                       height >> (is_chroma ? p->vsub : 0),                                                                   // 0.0
/*196 */                       8-p->log2_count);                                                                                      // 0.0
/*198 */     }                                                                                                                        // 0.0
/*200 */ }                                                                                                                            // 0.0
