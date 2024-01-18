// commit message FFmpeg@ce551a3925 (target=1, prob=0.9990325, correct=True): avcodec/tiertexseqv: set the fixed dimenasions, do not depend on the demuxer doing so
/*0 */ static av_cold int seqvideo_decode_init(AVCodecContext *avctx)  // (1) 0.1615
/*1 */ {                                                               // (9) 0.007692
/*2 */     SeqVideoContext *seq = avctx->priv_data;                    // (2) 0.1308
/*3 */     seq->avctx = avctx;                                         // (5) 0.08462
/*4 */     avctx->pix_fmt = AV_PIX_FMT_PAL8;                           // (0) 0.1846
/*5 */     seq->frame = av_frame_alloc();                              // (4) 0.1
/*6 */     if (!seq->frame)                                            // (6) 0.06923
/*7 */         return AVERROR(ENOMEM);                                 // (3) 0.1231
/*8 */     return 0;                                                   // (7) 0.04615
/*9 */ }                                                               // (8) 0.007692
