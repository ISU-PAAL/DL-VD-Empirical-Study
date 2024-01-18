// commit message FFmpeg@253d0be6a1 (target=0, prob=0.28897047, correct=True): pgssubdec: handle more complex PGS scenarios
/*0   */ static int parse_presentation_segment(AVCodecContext *avctx,                                                                 // (7) 0.03516
/*2   */                                       const uint8_t *buf, int buf_size,                                                      // (0) 0.09766
/*4   */                                       int64_t pts)                                                                           // (1) 0.08398
/*6   */ {                                                                                                                            // (29) 0.001953
/*8   */     PGSSubContext *ctx = avctx->priv_data;                                                                                   // (8) 0.0332
/*12  */     int x, y, ret;                                                                                                           // (19) 0.01953
/*16  */     int w = bytestream_get_be16(&buf);                                                                                       // (10) 0.0332
/*18  */     int h = bytestream_get_be16(&buf);                                                                                       // (11) 0.0332
/*22  */     ctx->presentation.pts = pts;                                                                                             // (16) 0.02734
/*26  */     av_dlog(avctx, "Video Dimensions %dx%d\n",                                                                               // (4) 0.04102
/*28  */             w, h);                                                                                                           // (13) 0.0293
/*30  */     ret = ff_set_dimensions(avctx, w, h);                                                                                    // (5) 0.03711
/*32  */     if (ret < 0)                                                                                                             // (23) 0.01758
/*34  */         return ret;                                                                                                          // (20) 0.01953
/*38  */     /* Skip 1 bytes of unknown, frame rate? */                                                                               // (14) 0.02734
/*40  */     buf++;                                                                                                                   // (25) 0.009766
/*44  */     ctx->presentation.id_number = bytestream_get_be16(&buf);                                                                 // (2) 0.04687
/*48  */     /*                                                                                                                       // (27) 0.007812
/*50  */      * Skip 3 bytes of unknown:                                                                                              // (17) 0.02148
/*52  */      *     state                                                                                                             // (21) 0.01953
/*54  */      *     palette_update_flag (0x80),                                                                                       // (6) 0.03711
/*56  */      *     palette_id_to_use,                                                                                                // (9) 0.0332
/*58  */      */                                                                                                                      // (26) 0.009766
/*60  */     buf += 3;                                                                                                                // (24) 0.01367
/*64  */     ctx->presentation.object_number = bytestream_get_byte(&buf);                                                             // (3) 0.04492
/*66  */     ctx->presentation.composition_flag = 0;                                                                                  // (12) 0.03125
/*68  */     if (!ctx->presentation.object_number)                                                                                    // (15) 0.02734
/*70  */         return 0;                                                                                                            // (22) 0.01953
/*74  */     /*                                                                                                                       // (28) 0.007812
/*76  */      * Skip 3 bytes of unknown:                                                                                              // (18) 0.02148
/*78  */      *     object_id_ref (2 bytes),                                                                                          // 0.0
/*80  */      *     window_id_ref,                                                                                                    // 0.0
/*82  */      */                                                                                                                      // 0.0
/*84  */     buf += 3;                                                                                                                // 0.0
/*86  */     ctx->presentation.composition_flag = bytestream_get_byte(&buf);                                                          // 0.0
/*90  */     x = bytestream_get_be16(&buf);                                                                                           // 0.0
/*92  */     y = bytestream_get_be16(&buf);                                                                                           // 0.0
/*96  */     /* TODO If cropping, cropping_x, cropping_y, cropping_width, cropping_height (all 2 bytes).*/                            // 0.0
/*100 */     av_dlog(avctx, "Subtitle Placement x=%d, y=%d\n", x, y);                                                                 // 0.0
/*104 */     if (x > avctx->width || y > avctx->height) {                                                                             // 0.0
/*106 */         av_log(avctx, AV_LOG_ERROR, "Subtitle out of video bounds. x = %d, y = %d, video width = %d, video height = %d.\n",  // 0.0
/*108 */                x, y, avctx->width, avctx->height);                                                                           // 0.0
/*110 */         x = 0; y = 0;                                                                                                        // 0.0
/*112 */     }                                                                                                                        // 0.0
/*116 */     /* Fill in dimensions */                                                                                                 // 0.0
/*118 */     ctx->presentation.x = x;                                                                                                 // 0.0
/*120 */     ctx->presentation.y = y;                                                                                                 // 0.0
/*124 */     return 0;                                                                                                                // 0.0
/*126 */ }                                                                                                                            // 0.0
