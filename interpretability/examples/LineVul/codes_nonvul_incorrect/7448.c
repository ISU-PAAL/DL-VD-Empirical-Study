// commit message FFmpeg@7ec9c5ce8a (target=0, prob=0.5576096, correct=False): avcodec/pngenc: Replace memcpy by av_image_copy()
/*0   */ static int encode_apng(AVCodecContext *avctx, AVPacket *pkt,                                                               // (7) 0.04297
/*2   */                        const AVFrame *pict, int *got_packet)                                                               // (4) 0.06836
/*4   */ {                                                                                                                          // (22) 0.001954
/*6   */     PNGEncContext *s = avctx->priv_data;                                                                                   // (13) 0.03125
/*8   */     int ret;                                                                                                               // (20) 0.01172
/*10  */     int enc_row_size;                                                                                                      // (17) 0.01953
/*12  */     size_t max_packet_size;                                                                                                // (15) 0.02539
/*14  */     APNGFctlChunk fctl_chunk = {0};                                                                                        // (11) 0.03516
/*18  */     if (pict && avctx->codec_id == AV_CODEC_ID_APNG && s->color_type == PNG_COLOR_TYPE_PALETTE) {                          // (1) 0.08594
/*20  */         uint32_t checksum = ~av_crc(av_crc_get_table(AV_CRC_32_IEEE_LE), ~0U, pict->data[1], 256 * sizeof(uint32_t));      // (0) 0.1172
/*24  */         if (avctx->frame_number == 0) {                                                                                    // (10) 0.03711
/*26  */             s->palette_checksum = checksum;                                                                                // (8) 0.04297
/*28  */         } else if (checksum != s->palette_checksum) {                                                                      // (6) 0.04492
/*30  */             av_log(avctx, AV_LOG_ERROR,                                                                                    // (5) 0.04687
/*32  */                    "Input contains more than one unique palette. APNG does not support multiple palettes.\n");             // (3) 0.07617
/*34  */             return -1;                                                                                                     // (14) 0.0293
/*36  */         }                                                                                                                  // (19) 0.01562
/*38  */     }                                                                                                                      // (21) 0.007812
/*42  */     enc_row_size    = deflateBound(&s->zstream, (avctx->width * s->bits_per_pixel + 7) >> 3);                              // (2) 0.07812
/*44  */     max_packet_size =                                                                                                      // (18) 0.01953
/*46  */         AV_INPUT_BUFFER_MIN_SIZE + // headers                                                                              // (9) 0.04102
/*48  */         avctx->height * (                                                                                                  // (16) 0.02539
/*50  */             enc_row_size +                                                                                                 // (12) 0.0332
/*52  */             (4 + 12) * (((int64_t)enc_row_size + IOBUF_SIZE - 1) / IOBUF_SIZE) // fdAT * ceil(enc_row_size / IOBUF_SIZE)   // 0.0
/*54  */         );                                                                                                                 // 0.0
/*56  */     if (max_packet_size > INT_MAX)                                                                                         // 0.0
/*58  */         return AVERROR(ENOMEM);                                                                                            // 0.0
/*62  */     if (avctx->frame_number == 0) {                                                                                        // 0.0
/*64  */         if (!pict)                                                                                                         // 0.0
/*66  */             return AVERROR(EINVAL);                                                                                        // 0.0
/*70  */         s->bytestream = avctx->extradata = av_malloc(FF_MIN_BUFFER_SIZE);                                                  // 0.0
/*72  */         if (!avctx->extradata)                                                                                             // 0.0
/*74  */             return AVERROR(ENOMEM);                                                                                        // 0.0
/*78  */         ret = encode_headers(avctx, pict);                                                                                 // 0.0
/*80  */         if (ret < 0)                                                                                                       // 0.0
/*82  */             return ret;                                                                                                    // 0.0
/*86  */         avctx->extradata_size = s->bytestream - avctx->extradata;                                                          // 0.0
/*90  */         s->last_frame_packet = av_malloc(max_packet_size);                                                                 // 0.0
/*92  */         if (!s->last_frame_packet)                                                                                         // 0.0
/*94  */             return AVERROR(ENOMEM);                                                                                        // 0.0
/*96  */     } else if (s->last_frame) {                                                                                            // 0.0
/*98  */         ret = ff_alloc_packet2(avctx, pkt, max_packet_size, 0);                                                            // 0.0
/*100 */         if (ret < 0)                                                                                                       // 0.0
/*102 */             return ret;                                                                                                    // 0.0
/*106 */         memcpy(pkt->data, s->last_frame_packet, s->last_frame_packet_size);                                                // 0.0
/*108 */         pkt->size = s->last_frame_packet_size;                                                                             // 0.0
/*110 */         pkt->pts = pkt->dts = s->last_frame->pts;                                                                          // 0.0
/*112 */     }                                                                                                                      // 0.0
/*116 */     if (pict) {                                                                                                            // 0.0
/*118 */         s->bytestream_start =                                                                                              // 0.0
/*120 */         s->bytestream       = s->last_frame_packet;                                                                        // 0.0
/*122 */         s->bytestream_end   = s->bytestream + max_packet_size;                                                             // 0.0
/*126 */         // We're encoding the frame first, so we have to do a bit of shuffling around                                      // 0.0
/*128 */         // to have the image data write to the correct place in the buffer                                                 // 0.0
/*130 */         fctl_chunk.sequence_number = s->sequence_number;                                                                   // 0.0
/*132 */         ++s->sequence_number;                                                                                              // 0.0
/*134 */         s->bytestream += 26 + 12;                                                                                          // 0.0
/*138 */         ret = apng_encode_frame(avctx, pict, &fctl_chunk, &s->last_frame_fctl);                                            // 0.0
/*140 */         if (ret < 0)                                                                                                       // 0.0
/*142 */             return ret;                                                                                                    // 0.0
/*146 */         fctl_chunk.delay_num = 0; // delay filled in during muxing                                                         // 0.0
/*148 */         fctl_chunk.delay_den = 0;                                                                                          // 0.0
/*150 */     } else {                                                                                                               // 0.0
/*152 */         s->last_frame_fctl.dispose_op = APNG_DISPOSE_OP_NONE;                                                              // 0.0
/*154 */     }                                                                                                                      // 0.0
/*158 */     if (s->last_frame) {                                                                                                   // 0.0
/*160 */         uint8_t* last_fctl_chunk_start = pkt->data;                                                                        // 0.0
/*162 */         uint8_t buf[26];                                                                                                   // 0.0
/*166 */         AV_WB32(buf + 0, s->last_frame_fctl.sequence_number);                                                              // 0.0
/*168 */         AV_WB32(buf + 4, s->last_frame_fctl.width);                                                                        // 0.0
/*170 */         AV_WB32(buf + 8, s->last_frame_fctl.height);                                                                       // 0.0
/*172 */         AV_WB32(buf + 12, s->last_frame_fctl.x_offset);                                                                    // 0.0
/*174 */         AV_WB32(buf + 16, s->last_frame_fctl.y_offset);                                                                    // 0.0
/*176 */         AV_WB16(buf + 20, s->last_frame_fctl.delay_num);                                                                   // 0.0
/*178 */         AV_WB16(buf + 22, s->last_frame_fctl.delay_den);                                                                   // 0.0
/*180 */         buf[24] = s->last_frame_fctl.dispose_op;                                                                           // 0.0
/*182 */         buf[25] = s->last_frame_fctl.blend_op;                                                                             // 0.0
/*184 */         png_write_chunk(&last_fctl_chunk_start, MKTAG('f', 'c', 'T', 'L'), buf, 26);                                       // 0.0
/*188 */         *got_packet = 1;                                                                                                   // 0.0
/*190 */     }                                                                                                                      // 0.0
/*194 */     if (pict) {                                                                                                            // 0.0
/*196 */         if (!s->last_frame) {                                                                                              // 0.0
/*198 */             s->last_frame = av_frame_alloc();                                                                              // 0.0
/*200 */             if (!s->last_frame)                                                                                            // 0.0
/*202 */                 return AVERROR(ENOMEM);                                                                                    // 0.0
/*204 */         } else if (s->last_frame_fctl.dispose_op != APNG_DISPOSE_OP_PREVIOUS) {                                            // 0.0
/*206 */             if (!s->prev_frame) {                                                                                          // 0.0
/*208 */                 s->prev_frame = av_frame_alloc();                                                                          // 0.0
/*210 */                 if (!s->prev_frame)                                                                                        // 0.0
/*212 */                     return AVERROR(ENOMEM);                                                                                // 0.0
/*216 */                 s->prev_frame->format = pict->format;                                                                      // 0.0
/*218 */                 s->prev_frame->width = pict->width;                                                                        // 0.0
/*220 */                 s->prev_frame->height = pict->height;                                                                      // 0.0
/*222 */                 if ((ret = av_frame_get_buffer(s->prev_frame, 32)) < 0)                                                    // 0.0
/*224 */                     return ret;                                                                                            // 0.0
/*226 */             }                                                                                                              // 0.0
/*230 */             // Do disposal, but not blending                                                                               // 0.0
/*232 */             memcpy(s->prev_frame->data[0], s->last_frame->data[0],                                                         // 0.0
/*234 */                    s->last_frame->linesize[0] * s->last_frame->height);                                                    // 0.0
/*236 */             if (s->last_frame_fctl.dispose_op == APNG_DISPOSE_OP_BACKGROUND) {                                             // 0.0
/*238 */                 uint32_t y;                                                                                                // 0.0
/*240 */                 uint8_t bpp = (s->bits_per_pixel + 7) >> 3;                                                                // 0.0
/*242 */                 for (y = s->last_frame_fctl.y_offset; y < s->last_frame_fctl.y_offset + s->last_frame_fctl.height; ++y) {  // 0.0
/*244 */                     size_t row_start = s->last_frame->linesize[0] * y + bpp * s->last_frame_fctl.x_offset;                 // 0.0
/*246 */                     memset(s->prev_frame->data[0] + row_start, 0, bpp * s->last_frame_fctl.width);                         // 0.0
/*248 */                 }                                                                                                          // 0.0
/*250 */             }                                                                                                              // 0.0
/*252 */         }                                                                                                                  // 0.0
/*256 */         av_frame_unref(s->last_frame);                                                                                     // 0.0
/*258 */         ret = av_frame_ref(s->last_frame, (AVFrame*)pict);                                                                 // 0.0
/*260 */         if (ret < 0)                                                                                                       // 0.0
/*262 */             return ret;                                                                                                    // 0.0
/*266 */         s->last_frame_fctl = fctl_chunk;                                                                                   // 0.0
/*268 */         s->last_frame_packet_size = s->bytestream - s->bytestream_start;                                                   // 0.0
/*270 */     } else {                                                                                                               // 0.0
/*272 */         av_frame_free(&s->last_frame);                                                                                     // 0.0
/*274 */     }                                                                                                                      // 0.0
/*278 */     return 0;                                                                                                              // 0.0
/*280 */ }                                                                                                                          // 0.0
