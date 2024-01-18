// commit message FFmpeg@480324e7ca (target=0, prob=0.55117923, correct=False): libgsm: simplify decoding by using a loop
/*0  */ static int libgsm_decode_frame(AVCodecContext *avctx,                                       // (8) 0.03755
/*2  */                                void *data, int *data_size,                                  // (1) 0.07905
/*4  */                                AVPacket *avpkt) {                                           // (2) 0.07708
/*6  */     uint8_t *buf = avpkt->data;                                                             // (11) 0.03162
/*8  */     int buf_size = avpkt->size;                                                             // (16) 0.02767
/*10 */     int out_size = avctx->frame_size * av_get_bytes_per_sample(avctx->sample_fmt);          // (3) 0.06522
/*14 */     if (*data_size < out_size) {                                                            // (14) 0.02767
/*16 */         av_log(avctx, AV_LOG_ERROR, "Output buffer is too small\n");                        // (5) 0.05731
/*18 */         return AVERROR(EINVAL);                                                             // (12) 0.03162
/*20 */     }                                                                                       // (23) 0.007905
/*24 */     if (buf_size < avctx->block_align) {                                                    // (9) 0.0336
/*26 */         av_log(avctx, AV_LOG_ERROR, "Packet is too small\n");                               // (6) 0.05731
/*28 */         return AVERROR_INVALIDDATA;                                                         // (10) 0.0336
/*30 */     }                                                                                       // (21) 0.007905
/*34 */     switch(avctx->codec_id) {                                                               // (15) 0.02767
/*36 */     case CODEC_ID_GSM:                                                                      // (17) 0.02569
/*38 */         if(gsm_decode(avctx->priv_data,buf,data)) return -1;                                // (4) 0.05929
/*40 */         break;                                                                              // (20) 0.01779
/*42 */     case CODEC_ID_GSM_MS:                                                                   // (13) 0.02964
/*44 */         if(gsm_decode(avctx->priv_data,buf,data) ||                                         // (7) 0.05336
/*46 */            gsm_decode(avctx->priv_data,buf+33,((int16_t*)data)+GSM_FRAME_SIZE)) return -1;  // (0) 0.09289
/*48 */     }                                                                                       // (22) 0.007905
/*52 */     *data_size = out_size;                                                                  // (18) 0.02372
/*54 */     return avctx->block_align;                                                              // (19) 0.02174
/*56 */ }                                                                                           // (24) 0.001976
