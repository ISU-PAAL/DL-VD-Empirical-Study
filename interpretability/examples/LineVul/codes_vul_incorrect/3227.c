// commit message FFmpeg@f0adb99d06 (target=1, prob=0.420712, correct=False): avcodec/qsvdec: Fix null dereferences in the qsv decoder
/*0  */ void ff_qsv_decode_reset(AVCodecContext *avctx, QSVContext *q)                    // (2) 0.05078
/*2  */ {                                                                                 // (29) 0.001953
/*4  */     QSVFrame *cur;                                                                // (21) 0.01953
/*6  */     AVPacket pkt;                                                                 // (22) 0.01758
/*8  */     int ret = 0;                                                                  // (25) 0.01562
/*10 */     mfxVideoParam param = { { 0 } };                                              // (13) 0.02734
/*14 */     if (q->reinit_pending) {                                                      // (15) 0.02734
/*16 */         close_decoder(q);                                                         // (12) 0.02734
/*18 */     } else if (q->engine_ready) {                                                 // (14) 0.02734
/*20 */         ret = MFXVideoDECODE_GetVideoParam(q->session, &param);                   // (3) 0.05078
/*22 */         if (ret < 0) {                                                            // (16) 0.02734
/*24 */             av_log(avctx, AV_LOG_ERROR, "MFX decode get param error %d\n", ret);  // (0) 0.07422
/*26 */         }                                                                         // (26) 0.01562
/*30 */         ret = MFXVideoDECODE_Reset(q->session, &param);                           // (4) 0.04883
/*32 */         if (ret < 0) {                                                            // (17) 0.02734
/*34 */             av_log(avctx, AV_LOG_ERROR, "MFX decode reset error %d\n", ret);      // (1) 0.07227
/*36 */         }                                                                         // (27) 0.01562
/*40 */         /* Free all frames*/                                                      // (18) 0.02344
/*42 */         cur = q->work_frames;                                                     // (11) 0.0293
/*44 */         while (cur) {                                                             // (19) 0.02344
/*46 */             q->work_frames = cur->next;                                           // (7) 0.04102
/*48 */             av_frame_free(&cur->frame);                                           // (6) 0.04102
/*50 */             av_freep(&cur);                                                       // (10) 0.03516
/*52 */             cur = q->work_frames;                                                 // (8) 0.03711
/*54 */         }                                                                         // (24) 0.01563
/*56 */     }                                                                             // (28) 0.007813
/*60 */     /* Reset output surfaces */                                                   // (23) 0.01563
/*62 */     av_fifo_reset(q->async_fifo);                                                 // (9) 0.03516
/*66 */     /* Reset input packets fifo */                                                // (20) 0.01953
/*68 */     while (av_fifo_size(q->pkt_fifo)) {                                           // (5) 0.04102
/*70 */         av_fifo_generic_read(q->pkt_fifo, &pkt, sizeof(pkt), NULL);               // 0.0
/*72 */         av_packet_unref(&pkt);                                                    // 0.0
/*74 */     }                                                                             // 0.0
/*78 */     /* Reset input bitstream fifo */                                              // 0.0
/*80 */     av_fifo_reset(q->input_fifo);                                                 // 0.0
/*82 */ }                                                                                 // 0.0
