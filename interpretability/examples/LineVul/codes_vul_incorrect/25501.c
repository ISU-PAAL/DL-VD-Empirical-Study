// commit message FFmpeg@2d40a09b6e (target=1, prob=0.12801826, correct=False): avformat: Remove support for libquvi
/*0 */ static int libquvi_read_packet(AVFormatContext *s, AVPacket *pkt)  // (0) 0.3333
/*2 */ {                                                                  // (3) 0.01389
/*4 */     LibQuviContext *qc = s->priv_data;                             // (2) 0.2361
/*6 */     return av_read_frame(qc->fmtctx, pkt);                         // (1) 0.2778
/*8 */ }                                                                  // (4) 0.01389
