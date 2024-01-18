// commit message FFmpeg@5afe1d2791 (target=1, prob=0.1339961, correct=False): avio: Add const qualifiers to ffio_read_indirect
/*0  */ static int read_packet(AVFormatContext *s, uint8_t *buf, int raw_packet_size, uint8_t **data)  // (0) 0.09511
/*2  */ {                                                                                              // (20) 0.002717
/*4  */     AVIOContext *pb = s->pb;                                                                   // (10) 0.03533
/*6  */     int len;                                                                                   // (17) 0.0163
/*10 */     for(;;) {                                                                                  // (15) 0.02174
/*12 */         len = ffio_read_indirect(pb, buf, TS_PACKET_SIZE, data);                               // (2) 0.08424
/*14 */         if (len != TS_PACKET_SIZE)                                                             // (7) 0.05163
/*16 */             return len < 0 ? len : AVERROR_EOF;                                                // (3) 0.06793
/*18 */         /* check packet sync byte */                                                           // (11) 0.03533
/*20 */         if ((*data)[0] != 0x47) {                                                              // (6) 0.05435
/*22 */             /* find a new packet start */                                                      // (8) 0.04891
/*24 */             avio_seek(pb, -TS_PACKET_SIZE, SEEK_CUR);                                          // (1) 0.08967
/*26 */             if (mpegts_resync(s) < 0)                                                          // (4) 0.06522
/*28 */                 return AVERROR(EAGAIN);                                                        // (5) 0.06522
/*30 */             else                                                                               // (13) 0.03261
/*32 */                 continue;                                                                      // (9) 0.0462
/*34 */         } else {                                                                               // (14) 0.02717
/*36 */             break;                                                                             // (12) 0.03533
/*38 */         }                                                                                      // (16) 0.02174
/*40 */     }                                                                                          // (19) 0.01087
/*42 */     return 0;                                                                                  // (18) 0.0163
/*44 */ }                                                                                              // (21) 0.002717
