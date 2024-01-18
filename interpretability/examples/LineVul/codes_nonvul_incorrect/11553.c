// commit message FFmpeg@6722e564a8 (target=0, prob=0.5353933, correct=False): avformat/hdsenc: fix off by 1 error in array size check
/*0  */ static int parse_header(OutputStream *os, const uint8_t *buf, int buf_size)  // (6) 0.04688
/*2  */ {                                                                            // (22) 0.001953
/*4  */     if (buf_size < 13)                                                       // (20) 0.02148
/*6  */         return AVERROR_INVALIDDATA;                                          // (13) 0.0332
/*8  */     if (memcmp(buf, "FLV", 3))                                               // (15) 0.03125
/*10 */         return AVERROR_INVALIDDATA;                                          // (14) 0.0332
/*12 */     buf      += 13;                                                          // (19) 0.02344
/*14 */     buf_size -= 13;                                                          // (21) 0.01758
/*16 */     while (buf_size >= 11 + 4) {                                             // (17) 0.02734
/*18 */         int type = buf[0];                                                   // (18) 0.02734
/*20 */         int size = AV_RB24(&buf[1]) + 11 + 4;                                // (7) 0.04687
/*22 */         if (size > buf_size)                                                 // (16) 0.0293
/*24 */             return AVERROR_INVALIDDATA;                                      // (9) 0.04102
/*26 */         if (type == 8 || type == 9) {                                        // (12) 0.03516
/*28 */             if (os->nb_extra_packets > FF_ARRAY_ELEMS(os->extra_packets))    // (0) 0.07422
/*30 */                 return AVERROR_INVALIDDATA;                                  // (5) 0.04883
/*32 */             os->extra_packet_sizes[os->nb_extra_packets] = size;             // (3) 0.06445
/*34 */             os->extra_packets[os->nb_extra_packets] = av_malloc(size);       // (2) 0.06836
/*36 */             if (!os->extra_packets[os->nb_extra_packets])                    // (4) 0.05664
/*38 */                 return AVERROR(ENOMEM);                                      // (8) 0.04687
/*40 */             memcpy(os->extra_packets[os->nb_extra_packets], buf, size);      // (1) 0.06836
/*42 */             os->nb_extra_packets++;                                          // (10) 0.03906
/*44 */         } else if (type == 0x12) {                                           // (11) 0.03516
/*46 */             if (os->metadata)                                                // 0.0
/*48 */                 return AVERROR_INVALIDDATA;                                  // 0.0
/*50 */             os->metadata_size = size - 11 - 4;                               // 0.0
/*52 */             os->metadata      = av_malloc(os->metadata_size);                // 0.0
/*54 */             if (!os->metadata)                                               // 0.0
/*56 */                 return AVERROR(ENOMEM);                                      // 0.0
/*58 */             memcpy(os->metadata, buf + 11, os->metadata_size);               // 0.0
/*60 */         }                                                                    // 0.0
/*62 */         buf      += size;                                                    // 0.0
/*64 */         buf_size -= size;                                                    // 0.0
/*66 */     }                                                                        // 0.0
/*68 */     if (!os->metadata)                                                       // 0.0
/*70 */         return AVERROR_INVALIDDATA;                                          // 0.0
/*72 */     return 0;                                                                // 0.0
/*74 */ }                                                                            // 0.0
