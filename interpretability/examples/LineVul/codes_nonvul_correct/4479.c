// commit message FFmpeg@36583d23bd (target=0, prob=0.21082103, correct=True): audio_frame_que: simplify
/*0  */ void ff_af_queue_init(AVCodecContext *avctx, AudioFrameQueue *afq)  // (1) 0.1678
/*2  */ {                                                                   // (6) 0.006993
/*4  */     afq->avctx             = avctx;                                 // (2) 0.1678
/*6  */     afq->next_pts          = AV_NOPTS_VALUE;                        // (0) 0.1958
/*8  */     afq->remaining_delay   = avctx->delay;                          // (3) 0.1259
/*10 */     afq->remaining_samples = avctx->delay;                          // (5) 0.1189
/*12 */     afq->frame_queue       = NULL;                                  // (4) 0.1259
/*14 */ }                                                                   // (7) 0.006993
