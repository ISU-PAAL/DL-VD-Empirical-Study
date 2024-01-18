// commit message FFmpeg@238ddd6482 (target=1, prob=0.24924098, correct=False): avformat/dump: Fix context/level for payload dump
/*0  */ static void pkt_dump_internal(void *avcl, FILE *f, int level, const AVPacket *pkt,  // (5) 0.05823
/*2  */                               int dump_payload, AVRational time_base)               // (0) 0.08434
/*4  */ {                                                                                   // (21) 0.002008
/*6  */     HEXDUMP_PRINT("stream #%d:\n", pkt->stream_index);                              // (6) 0.0502
/*8  */     HEXDUMP_PRINT("  keyframe=%d\n", (pkt->flags & AV_PKT_FLAG_KEY) != 0);          // (1) 0.07631
/*10 */     HEXDUMP_PRINT("  duration=%0.3f\n", pkt->duration * av_q2d(time_base));         // (2) 0.0743
/*12 */     /* DTS is _always_ valid after av_read_frame() */                               // (9) 0.03815
/*14 */     HEXDUMP_PRINT("  dts=");                                                        // (15) 0.03213
/*16 */     if (pkt->dts == AV_NOPTS_VALUE)                                                 // (10) 0.03815
/*18 */         HEXDUMP_PRINT("N/A");                                                       // (11) 0.03815
/*20 */     else                                                                            // (19) 0.008032
/*22 */         HEXDUMP_PRINT("%0.3f", pkt->dts * av_q2d(time_base));                       // (3) 0.0743
/*24 */     /* PTS may not be known if B-frames are present. */                             // (14) 0.03414
/*26 */     HEXDUMP_PRINT("  pts=");                                                        // (16) 0.03012
/*28 */     if (pkt->pts == AV_NOPTS_VALUE)                                                 // (12) 0.03815
/*30 */         HEXDUMP_PRINT("N/A");                                                       // (13) 0.03815
/*32 */     else                                                                            // (20) 0.008032
/*34 */         HEXDUMP_PRINT("%0.3f", pkt->pts * av_q2d(time_base));                       // (4) 0.0743
/*36 */     HEXDUMP_PRINT("\n");                                                            // (17) 0.02811
/*38 */     HEXDUMP_PRINT("  size=%d\n", pkt->size);                                        // (8) 0.04819
/*40 */     if (dump_payload)                                                               // (18) 0.02008
/*42 */         av_hex_dump(f, pkt->data, pkt->size);                                       // (7) 0.0502
/*44 */ }                                                                                   // (22) 0.002008
