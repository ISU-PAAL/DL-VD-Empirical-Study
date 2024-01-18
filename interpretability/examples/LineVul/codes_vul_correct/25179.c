// commit message FFmpeg@5a412a5c3c (target=1, prob=0.762778, correct=True): avcodec/extract_extradata_bsf: Fix leak discovered via fuzzing
/*0   */ static int extract_extradata_h2645(AVBSFContext *ctx, AVPacket *pkt,                   // (7) 0.05078
/*2   */                                    uint8_t **data, int *size)                          // (0) 0.08789
/*4   */ {                                                                                      // (21) 0.001953
/*6   */     static const int extradata_nal_types_hevc[] = {                                    // (10) 0.03711
/*8   */         HEVC_NAL_VPS, HEVC_NAL_SPS, HEVC_NAL_PPS,                                      // (3) 0.06641
/*10  */     };                                                                                 // (20) 0.007812
/*12  */     static const int extradata_nal_types_h264[] = {                                    // (11) 0.03711
/*14  */         H264_NAL_SPS, H264_NAL_PPS,                                                    // (8) 0.04883
/*16  */     };                                                                                 // (19) 0.007812
/*20  */     ExtractExtradataContext *s = ctx->priv_data;                                       // (12) 0.03516
/*24  */     H2645Packet h2645_pkt = { 0 };                                                     // (13) 0.03516
/*26  */     int extradata_size = 0;                                                            // (16) 0.02148
/*28  */     const int *extradata_nal_types;                                                    // (15) 0.0293
/*30  */     int nb_extradata_nal_types;                                                        // (14) 0.03125
/*32  */     int i, has_sps = 0, has_vps = 0, ret = 0;                                          // (9) 0.04688
/*36  */     if (ctx->par_in->codec_id == AV_CODEC_ID_HEVC) {                                   // (6) 0.05469
/*38  */         extradata_nal_types    = extradata_nal_types_hevc;                             // (5) 0.05664
/*40  */         nb_extradata_nal_types = FF_ARRAY_ELEMS(extradata_nal_types_hevc);             // (1) 0.07812
/*42  */     } else {                                                                           // (17) 0.01172
/*44  */         extradata_nal_types    = extradata_nal_types_h264;                             // (4) 0.05664
/*46  */         nb_extradata_nal_types = FF_ARRAY_ELEMS(extradata_nal_types_h264);             // (2) 0.07812
/*48  */     }                                                                                  // (18) 0.007812
/*52  */     ret = ff_h2645_packet_split(&h2645_pkt, pkt->data, pkt->size,                      // 0.0
/*54  */                                 ctx, 0, 0, ctx->par_in->codec_id, 1);                  // 0.0
/*56  */     if (ret < 0)                                                                       // 0.0
/*58  */         return ret;                                                                    // 0.0
/*62  */     for (i = 0; i < h2645_pkt.nb_nals; i++) {                                          // 0.0
/*64  */         H2645NAL *nal = &h2645_pkt.nals[i];                                            // 0.0
/*66  */         if (val_in_array(extradata_nal_types, nb_extradata_nal_types, nal->type)) {    // 0.0
/*68  */             extradata_size += nal->raw_size + 3;                                       // 0.0
/*70  */             if (ctx->par_in->codec_id == AV_CODEC_ID_HEVC) {                           // 0.0
/*72  */                 if (nal->type == HEVC_NAL_SPS) has_sps = 1;                            // 0.0
/*74  */                 if (nal->type == HEVC_NAL_VPS) has_vps = 1;                            // 0.0
/*76  */             } else {                                                                   // 0.0
/*78  */                 if (nal->type == H264_NAL_SPS) has_sps = 1;                            // 0.0
/*80  */             }                                                                          // 0.0
/*82  */         }                                                                              // 0.0
/*84  */     }                                                                                  // 0.0
/*88  */     if (extradata_size &&                                                              // 0.0
/*90  */         ((ctx->par_in->codec_id == AV_CODEC_ID_HEVC && has_sps && has_vps) ||          // 0.0
/*92  */          (ctx->par_in->codec_id == AV_CODEC_ID_H264 && has_sps))) {                    // 0.0
/*94  */         AVBufferRef *filtered_buf;                                                     // 0.0
/*96  */         uint8_t *extradata, *filtered_data;                                            // 0.0
/*100 */         if (s->remove) {                                                               // 0.0
/*102 */             filtered_buf = av_buffer_alloc(pkt->size + AV_INPUT_BUFFER_PADDING_SIZE);  // 0.0
/*104 */             if (!filtered_buf) {                                                       // 0.0
/*106 */                 ret = AVERROR(ENOMEM);                                                 // 0.0
/*108 */                 goto fail;                                                             // 0.0
/*110 */             }                                                                          // 0.0
/*112 */             filtered_data = filtered_buf->data;                                        // 0.0
/*114 */         }                                                                              // 0.0
/*118 */         extradata = av_malloc(extradata_size + AV_INPUT_BUFFER_PADDING_SIZE);          // 0.0
/*120 */         if (!extradata) {                                                              // 0.0
/*122 */             av_buffer_unref(&filtered_buf);                                            // 0.0
/*124 */             ret = AVERROR(ENOMEM);                                                     // 0.0
/*126 */             goto fail;                                                                 // 0.0
/*128 */         }                                                                              // 0.0
/*132 */         *data = extradata;                                                             // 0.0
/*134 */         *size = extradata_size;                                                        // 0.0
/*138 */         for (i = 0; i < h2645_pkt.nb_nals; i++) {                                      // 0.0
/*140 */             H2645NAL *nal = &h2645_pkt.nals[i];                                        // 0.0
/*142 */             if (val_in_array(extradata_nal_types, nb_extradata_nal_types,              // 0.0
/*144 */                              nal->type)) {                                             // 0.0
/*146 */                 AV_WB24(extradata, 1); // startcode                                    // 0.0
/*148 */                 memcpy(extradata + 3, nal->raw_data, nal->raw_size);                   // 0.0
/*150 */                 extradata += 3 + nal->raw_size;                                        // 0.0
/*152 */             } else if (s->remove) {                                                    // 0.0
/*154 */                 AV_WB24(filtered_data, 1); // startcode                                // 0.0
/*156 */                 memcpy(filtered_data + 3, nal->raw_data, nal->raw_size);               // 0.0
/*158 */                 filtered_data += 3 + nal->raw_size;                                    // 0.0
/*160 */             }                                                                          // 0.0
/*162 */         }                                                                              // 0.0
/*166 */         if (s->remove) {                                                               // 0.0
/*168 */             av_buffer_unref(&pkt->buf);                                                // 0.0
/*170 */             pkt->buf  = filtered_buf;                                                  // 0.0
/*172 */             pkt->data = filtered_buf->data;                                            // 0.0
/*174 */             pkt->size = filtered_data - filtered_buf->data;                            // 0.0
/*176 */         }                                                                              // 0.0
/*178 */     }                                                                                  // 0.0
/*182 */ fail:                                                                                  // 0.0
/*184 */     ff_h2645_packet_uninit(&h2645_pkt);                                                // 0.0
/*186 */     return ret;                                                                        // 0.0
/*188 */ }                                                                                      // 0.0
