// commit message FFmpeg@ac66834c75 (target=0, prob=0.19866425, correct=True): avcodec_decode_audio2() difference to avcodec_decode_audio() is that the user can pass the allocated size of the output buffer to the decoder and the decoder can check if theres enough space
/*0  */ int avcodec_decode_audio(AVCodecContext *avctx, int16_t *samples,    // (5) 0.09848
/*2  */                          int *frame_size_ptr,                        // (2) 0.1212
/*4  */                          uint8_t *buf, int buf_size)                 // (1) 0.1364
/*6  */ {                                                                    // (13) 0.003788
/*8  */     int ret;                                                         // (10) 0.02273
/*12 */     *frame_size_ptr= 0;                                              // (7) 0.04545
/*14 */     if((avctx->codec->capabilities & CODEC_CAP_DELAY) || buf_size){  // (4) 0.1098
/*16 */         ret = avctx->codec->decode(avctx, samples, frame_size_ptr,   // (3) 0.1098
/*18 */                                 buf, buf_size);                      // (0) 0.1402
/*20 */         avctx->frame_number++;                                       // (6) 0.05303
/*22 */     }else                                                            // (11) 0.01894
/*24 */         ret= 0;                                                      // (8) 0.04167
/*26 */     return ret;                                                      // (9) 0.02273
/*28 */ }                                                                    // (12) 0.003788
