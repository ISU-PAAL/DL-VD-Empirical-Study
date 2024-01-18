// commit message FFmpeg@8a57ca5c6a (target=0, prob=0.52873707, correct=False): aasc: fix out of array write
/*0   */ static int aasc_decode_frame(AVCodecContext *avctx,                                                       // (10) 0.03516
/*2   */                               void *data, int *data_size,                                                 // (1) 0.07617
/*4   */                               AVPacket *avpkt)                                                            // (3) 0.07227
/*6   */ {                                                                                                         // (25) 0.001953
/*8   */     const uint8_t *buf = avpkt->data;                                                                     // (11) 0.0332
/*10  */     int buf_size = avpkt->size;                                                                           // (14) 0.02734
/*12  */     AascContext *s = avctx->priv_data;                                                                    // (12) 0.03125
/*14  */     int compr, i, stride;                                                                                 // (18) 0.01953
/*18  */     s->frame.reference = 3;                                                                               // (16) 0.02148
/*20  */     s->frame.buffer_hints = FF_BUFFER_HINTS_VALID | FF_BUFFER_HINTS_PRESERVE | FF_BUFFER_HINTS_REUSABLE;  // (0) 0.09766
/*22  */     if (avctx->reget_buffer(avctx, &s->frame)) {                                                          // (7) 0.04297
/*24  */         av_log(avctx, AV_LOG_ERROR, "reget_buffer() failed\n");                                           // (4) 0.05859
/*26  */         return -1;                                                                                        // (17) 0.02148
/*28  */     }                                                                                                     // (24) 0.007813
/*32  */     compr = AV_RL32(buf);                                                                                 // (15) 0.02344
/*34  */     buf += 4;                                                                                             // (22) 0.01367
/*36  */     buf_size -= 4;                                                                                        // (19) 0.01758
/*38  */     switch (avctx->codec_tag) {                                                                           // (13) 0.02734
/*40  */     case MKTAG('A', 'A', 'S', '4'):                                                                       // (9) 0.03711
/*42  */         bytestream2_init(&s->gb, buf - 4, buf_size + 4);                                                  // (5) 0.05469
/*44  */         ff_msrle_decode(avctx, (AVPicture*)&s->frame, 8, &s->gb);                                         // (2) 0.07227
/*46  */         break;                                                                                            // (20) 0.01758
/*48  */     case MKTAG('A', 'A', 'S', 'C'):                                                                       // (8) 0.03711
/*50  */     switch(compr){                                                                                        // (21) 0.01562
/*52  */     case 0:                                                                                               // (23) 0.01172
/*54  */         stride = (avctx->width * 3 + 3) & ~3;                                                             // (6) 0.04492
/*56  */         for(i = avctx->height - 1; i >= 0; i--){                                                          // 0.0
/*58  */             if(avctx->width*3 > buf_size){                                                                // 0.0
/*60  */                 av_log(avctx, AV_LOG_ERROR, "Next line is beyond buffer bounds\n");                       // 0.0
/*62  */                 break;                                                                                    // 0.0
/*64  */             }                                                                                             // 0.0
/*66  */             memcpy(s->frame.data[0] + i*s->frame.linesize[0], buf, avctx->width*3);                       // 0.0
/*68  */             buf += stride;                                                                                // 0.0
/*70  */             buf_size -= stride;                                                                           // 0.0
/*72  */         }                                                                                                 // 0.0
/*74  */         break;                                                                                            // 0.0
/*76  */     case 1:                                                                                               // 0.0
/*78  */         bytestream2_init(&s->gb, buf, buf_size);                                                          // 0.0
/*80  */         ff_msrle_decode(avctx, (AVPicture*)&s->frame, 8, &s->gb);                                         // 0.0
/*82  */         break;                                                                                            // 0.0
/*84  */     default:                                                                                              // 0.0
/*86  */         av_log(avctx, AV_LOG_ERROR, "Unknown compression type %d\n", compr);                              // 0.0
/*88  */         return -1;                                                                                        // 0.0
/*90  */     }                                                                                                     // 0.0
/*92  */         break;                                                                                            // 0.0
/*94  */     default:                                                                                              // 0.0
/*96  */         av_log(avctx, AV_LOG_ERROR, "Unknown FourCC: %X\n", avctx->codec_tag);                            // 0.0
/*98  */         return -1;                                                                                        // 0.0
/*100 */     }                                                                                                     // 0.0
/*104 */     *data_size = sizeof(AVFrame);                                                                         // 0.0
/*106 */     *(AVFrame*)data = s->frame;                                                                           // 0.0
/*110 */     /* report that the buffer was completely consumed */                                                  // 0.0
/*112 */     return buf_size;                                                                                      // 0.0
/*114 */ }                                                                                                         // 0.0
