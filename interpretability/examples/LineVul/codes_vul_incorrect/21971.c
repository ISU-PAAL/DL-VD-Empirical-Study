// commit message FFmpeg@7441d1ec33 (target=1, prob=0.432548, correct=False): avformat/aviobuf: fix null dereference in avio_close_dyn_buf()
/*0  */ int avio_close_dyn_buf(AVIOContext *s, uint8_t **pbuffer)          // (1) 0.08897
/*2  */ {                                                                  // (20) 0.003559
/*4  */     DynBuffer *d = s->opaque;                                      // (6) 0.04626
/*6  */     int size;                                                      // (17) 0.02135
/*8  */     static const char padbuf[FF_INPUT_BUFFER_PADDING_SIZE] = {0};  // (0) 0.09609
/*10 */     int padding = 0;                                               // (15) 0.02847
/*14 */     if (!s) {                                                      // (14) 0.02847
/*16 */         *pbuffer = NULL;                                           // (7) 0.04626
/*18 */         return 0;                                                  // (10) 0.03559
/*20 */     }                                                              // (19) 0.01423
/*24 */     /* don't attempt to pad fixed-size packet buffers */           // (5) 0.05338
/*26 */     if (!s->max_packet_size) {                                     // (4) 0.05338
/*28 */         avio_write(s, padbuf, sizeof(padbuf));                     // (3) 0.07829
/*30 */         padding = FF_INPUT_BUFFER_PADDING_SIZE;                    // (2) 0.08185
/*32 */     }                                                              // (18) 0.01423
/*36 */     avio_flush(s);                                                 // (9) 0.03559
/*40 */     *pbuffer = d->buffer;                                          // (8) 0.03915
/*42 */     size = d->size;                                                // (13) 0.03203
/*44 */     av_free(d);                                                    // (12) 0.03203
/*46 */     av_free(s);                                                    // (11) 0.03203
/*48 */     return size - padding;                                         // (16) 0.02847
/*50 */ }                                                                  // (21) 0.003559
