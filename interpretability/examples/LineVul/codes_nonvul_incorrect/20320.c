// commit message FFmpeg@3583eb9341 (target=0, prob=0.5128969, correct=False): CrystalHD: Remove redundant interlaced check.
/*0   */ static inline CopyRet copy_frame(AVCodecContext *avctx,                          // (9) 0.03125
/*2   */                                  BC_DTS_PROC_OUT *output,                        // (0) 0.08594
/*4   */                                  void *data, int *data_size,                     // (1) 0.08203
/*6   */                                  uint8_t second_field)                           // (2) 0.07812
/*8   */ {                                                                                // (23) 0.001954
/*10  */     BC_STATUS ret;                                                               // (19) 0.01758
/*12  */     BC_DTS_STATUS decoder_status;                                                // (12) 0.0293
/*14  */     uint8_t is_paff;                                                             // (16) 0.02344
/*16  */     uint8_t next_frame_same;                                                     // (15) 0.02539
/*18  */     uint8_t interlaced;                                                          // (17) 0.02148
/*22  */     CHDContext *priv = avctx->priv_data;                                         // (10) 0.03125
/*26  */     uint8_t bottom_field = (output->PicInfo.flags & VDEC_FLAG_BOTTOMFIELD) ==    // (5) 0.05859
/*28  */                            VDEC_FLAG_BOTTOMFIELD;                                // (3) 0.07031
/*30  */     uint8_t bottom_first = !!(output->PicInfo.flags & VDEC_FLAG_BOTTOM_FIRST);   // (4) 0.0625
/*34  */     int width    = output->PicInfo.width;                                        // (11) 0.03125
/*36  */     int height   = output->PicInfo.height;                                       // (14) 0.0293
/*38  */     int bwidth;                                                                  // (22) 0.01367
/*40  */     uint8_t *src = output->Ybuff;                                                // (13) 0.0293
/*42  */     int sStride;                                                                 // (21) 0.01562
/*44  */     uint8_t *dst;                                                                // (18) 0.02148
/*46  */     int dStride;                                                                 // (20) 0.01562
/*50  */     ret = DtsGetDriverStatus(priv->dev, &decoder_status);                        // (6) 0.04102
/*52  */     if (ret != BC_STS_SUCCESS) {                                                 // (8) 0.0332
/*54  */         av_log(avctx, AV_LOG_ERROR,                                              // (7) 0.03906
/*56  */                "CrystalHD: GetDriverStatus failed: %u\n", ret);                  // 0.0
/*58  */        return RET_ERROR;                                                         // 0.0
/*60  */     }                                                                            // 0.0
/*64  */     is_paff           = ASSUME_PAFF_OVER_MBAFF ||                                // 0.0
/*66  */                         !(output->PicInfo.flags & VDEC_FLAG_UNKNOWN_SRC);        // 0.0
/*68  */     next_frame_same   = output->PicInfo.picture_number ==                        // 0.0
/*70  */                         (decoder_status.picNumFlags & ~0x40000000);              // 0.0
/*72  */     interlaced        = ((output->PicInfo.flags &                                // 0.0
/*74  */                           VDEC_FLAG_INTERLACED_SRC) && is_paff) ||               // 0.0
/*76  */                          next_frame_same || bottom_field || second_field;        // 0.0
/*80  */     av_log(avctx, AV_LOG_VERBOSE, "CrystalHD: next_frame_same: %u | %u | %u\n",  // 0.0
/*82  */            next_frame_same, output->PicInfo.picture_number,                      // 0.0
/*84  */            decoder_status.picNumFlags & ~0x40000000);                            // 0.0
/*88  */     if (priv->pic.data[0] && !priv->need_second_field)                           // 0.0
/*90  */         avctx->release_buffer(avctx, &priv->pic);                                // 0.0
/*94  */     priv->need_second_field = interlaced && !priv->need_second_field;            // 0.0
/*98  */     priv->pic.buffer_hints = FF_BUFFER_HINTS_VALID | FF_BUFFER_HINTS_PRESERVE |  // 0.0
/*100 */                              FF_BUFFER_HINTS_REUSABLE;                           // 0.0
/*102 */     if (!priv->pic.data[0]) {                                                    // 0.0
/*104 */         if (avctx->get_buffer(avctx, &priv->pic) < 0) {                          // 0.0
/*106 */             av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                // 0.0
/*108 */             return RET_ERROR;                                                    // 0.0
/*110 */         }                                                                        // 0.0
/*112 */     }                                                                            // 0.0
/*116 */     bwidth = av_image_get_linesize(avctx->pix_fmt, width, 0);                    // 0.0
/*118 */     if (priv->is_70012) {                                                        // 0.0
/*120 */         int pStride;                                                             // 0.0
/*124 */         if (width <= 720)                                                        // 0.0
/*126 */             pStride = 720;                                                       // 0.0
/*128 */         else if (width <= 1280)                                                  // 0.0
/*130 */             pStride = 1280;                                                      // 0.0
/*132 */         else if (width <= 1080)                                                  // 0.0
/*134 */             pStride = 1080;                                                      // 0.0
/*136 */         sStride = av_image_get_linesize(avctx->pix_fmt, pStride, 0);             // 0.0
/*138 */     } else {                                                                     // 0.0
/*140 */         sStride = bwidth;                                                        // 0.0
/*142 */     }                                                                            // 0.0
/*146 */     dStride = priv->pic.linesize[0];                                             // 0.0
/*148 */     dst     = priv->pic.data[0];                                                 // 0.0
/*152 */     av_log(priv->avctx, AV_LOG_VERBOSE, "CrystalHD: Copying out frame\n");       // 0.0
/*156 */     if (interlaced) {                                                            // 0.0
/*158 */         int dY = 0;                                                              // 0.0
/*160 */         int sY = 0;                                                              // 0.0
/*164 */         height /= 2;                                                             // 0.0
/*166 */         if (bottom_field) {                                                      // 0.0
/*168 */             av_log(priv->avctx, AV_LOG_VERBOSE, "Interlaced: bottom field\n");   // 0.0
/*170 */             dY = 1;                                                              // 0.0
/*172 */         } else {                                                                 // 0.0
/*174 */             av_log(priv->avctx, AV_LOG_VERBOSE, "Interlaced: top field\n");      // 0.0
/*176 */             dY = 0;                                                              // 0.0
/*178 */         }                                                                        // 0.0
/*182 */         for (sY = 0; sY < height; dY++, sY++) {                                  // 0.0
/*184 */             memcpy(&(dst[dY * dStride]), &(src[sY * sStride]), bwidth);          // 0.0
/*186 */             if (interlaced)                                                      // 0.0
/*188 */                 dY++;                                                            // 0.0
/*190 */         }                                                                        // 0.0
/*192 */     } else {                                                                     // 0.0
/*194 */         av_image_copy_plane(dst, dStride, src, sStride, bwidth, height);         // 0.0
/*196 */     }                                                                            // 0.0
/*200 */     priv->pic.interlaced_frame = interlaced;                                     // 0.0
/*202 */     if (interlaced)                                                              // 0.0
/*204 */         priv->pic.top_field_first = !bottom_first;                               // 0.0
/*208 */     if (output->PicInfo.timeStamp != 0) {                                        // 0.0
/*210 */         priv->pic.pkt_pts = opaque_list_pop(priv, output->PicInfo.timeStamp);    // 0.0
/*212 */         av_log(avctx, AV_LOG_VERBOSE, "output \"pts\": %"PRIu64"\n",             // 0.0
/*214 */                priv->pic.pkt_pts);                                               // 0.0
/*216 */     }                                                                            // 0.0
/*220 */     if (!priv->need_second_field) {                                              // 0.0
/*222 */         *data_size       = sizeof(AVFrame);                                      // 0.0
/*224 */         *(AVFrame *)data = priv->pic;                                            // 0.0
/*226 */     }                                                                            // 0.0
/*230 */     if (ASSUME_TWO_INPUTS_ONE_OUTPUT &&                                          // 0.0
/*232 */         output->PicInfo.flags & VDEC_FLAG_UNKNOWN_SRC) {                         // 0.0
/*234 */         av_log(priv->avctx, AV_LOG_VERBOSE, "Fieldpair from two packets.\n");    // 0.0
/*236 */         return RET_SKIP_NEXT_COPY;                                               // 0.0
/*238 */     }                                                                            // 0.0
/*242 */     return RET_OK;                                                               // 0.0
/*244 */ }                                                                                // 0.0
