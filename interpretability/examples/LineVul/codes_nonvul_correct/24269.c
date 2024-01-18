// commit message FFmpeg@9745f19ffc (target=0, prob=0.19030872, correct=True): assdec: check the right variable
/*0  */ static av_cold int ass_decode_init(AVCodecContext *avctx)                     // (3) 0.1361
/*2  */ {                                                                             // (7) 0.006803
/*4  */     avctx->subtitle_header = av_malloc(avctx->extradata_size);                // (1) 0.1701
/*6  */     if (!avctx->extradata)                                                    // (5) 0.08163
/*8  */         return AVERROR(ENOMEM);                                               // (4) 0.1088
/*10 */     memcpy(avctx->subtitle_header, avctx->extradata, avctx->extradata_size);  // (0) 0.2109
/*12 */     avctx->subtitle_header_size = avctx->extradata_size;                      // (2) 0.1497
/*14 */     return 0;                                                                 // (6) 0.04082
/*16 */ }                                                                             // (8) 0.006803
