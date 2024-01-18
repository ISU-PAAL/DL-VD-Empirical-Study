// commit message FFmpeg@56706ac0d5 (target=1, prob=0.8256506, correct=True): libopenjpegenc: fix out-of-bounds reads when filling the edges
/*0  */ static int libopenjpeg_copy_packed12(AVCodecContext *avctx, const AVFrame *frame, opj_image_t *image)  // (2) 0.06836
/*2  */ {                                                                                                      // (22) 0.001953
/*4  */     int compno;                                                                                        // (20) 0.01367
/*6  */     int x, y;                                                                                          // (18) 0.01562
/*8  */     int *image_line;                                                                                   // (16) 0.01758
/*10 */     int frame_index;                                                                                   // (17) 0.01562
/*12 */     const int numcomps  = image->numcomps;                                                             // (13) 0.03125
/*14 */     uint16_t *frame_ptr = (uint16_t *)frame->data[0];                                                  // (8) 0.04688
/*18 */     for (compno = 0; compno < numcomps; ++compno) {                                                    // (11) 0.04297
/*20 */         if (image->comps[compno].w > frame->linesize[0] / numcomps) {                                  // (4) 0.0625
/*22 */             av_log(avctx, AV_LOG_ERROR, "Error: frame's linesize is too small for the image\n");       // (0) 0.07812
/*24 */             return 0;                                                                                  // (14) 0.02734
/*26 */         }                                                                                              // (19) 0.01562
/*28 */     }                                                                                                  // (21) 0.007812
/*32 */     for (compno = 0; compno < numcomps; ++compno) {                                                    // (12) 0.04297
/*34 */         for (y = 0; y < avctx->height; ++y) {                                                          // (9) 0.04687
/*36 */             image_line = image->comps[compno].data + y * image->comps[compno].w;                       // (1) 0.07227
/*38 */             frame_index = y * (frame->linesize[0] / 2) + compno;                                       // (5) 0.0625
/*40 */             for (x = 0; x < avctx->width; ++x) {                                                       // (7) 0.05469
/*42 */                 image_line[x] = frame_ptr[frame_index] >> 4;                                           // (3) 0.06445
/*44 */                 frame_index += numcomps;                                                               // (10) 0.04492
/*46 */             }                                                                                          // (15) 0.02344
/*48 */             for (; x < image->comps[compno].w; ++x) {                                                  // (6) 0.05859
/*50 */                 image_line[x] = image_line[x - 1];                                                     // 0.0
/*52 */             }                                                                                          // 0.0
/*54 */         }                                                                                              // 0.0
/*56 */         for (; y < image->comps[compno].h; ++y) {                                                      // 0.0
/*58 */             image_line = image->comps[compno].data + y * image->comps[compno].w;                       // 0.0
/*60 */             for (x = 0; x < image->comps[compno].w; ++x) {                                             // 0.0
/*62 */                 image_line[x] = image_line[x - image->comps[compno].w];                                // 0.0
/*64 */             }                                                                                          // 0.0
/*66 */         }                                                                                              // 0.0
/*68 */     }                                                                                                  // 0.0
/*72 */     return 1;                                                                                          // 0.0
/*74 */ }                                                                                                      // 0.0
