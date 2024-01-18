// commit message FFmpeg@f2e9a0ecbe (target=1, prob=0.9991048, correct=True): qsv/vp8dec: fixes memory leak issue
/*0 */ static av_cold int qsv_decode_close(AVCodecContext *avctx)  // (0) 0.2
/*1 */ {                                                           // (7) 0.009524
/*2 */     QSVOtherContext *s = avctx->priv_data;                  // (1) 0.1714
/*3 */     ff_qsv_decode_close(&s->qsv);                           // (2) 0.1714
/*4 */     qsv_clear_buffers(s);                                   // (4) 0.1238
/*5 */     av_fifo_free(s->packet_fifo);                           // (3) 0.1714
/*6 */     return 0;                                               // (5) 0.05714
/*7 */ }                                                           // (6) 0.009524
