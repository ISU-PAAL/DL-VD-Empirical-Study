// commit message FFmpeg@816577716b (target=1, prob=0.44091138, correct=False): avcodec/dvdsubdec: fix accessing dangling pointers
/*0  */ static av_cold int dvdsub_close(AVCodecContext *avctx)  // (0) 0.2405
/*2  */ {                                                       // (5) 0.01266
/*4  */     DVDSubContext *ctx = avctx->priv_data;              // (1) 0.2152
/*6  */     av_freep(&ctx->buf);                                // (2) 0.1519
/*8  */     ctx->buf_size = 0;                                  // (3) 0.1519
/*10 */     return 0;                                           // (4) 0.07595
/*12 */ }                                                       // (6) 0.01266
