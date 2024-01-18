// commit message FFmpeg@dc2e4c2e53 (target=0, prob=0.7029737, correct=False): lavf/wavdec: Fix seeking in files with unaligned offsets
/*0  */ static int64_t find_tag(AVIOContext *pb, uint32_t tag1)  // (1) 0.1215
/*2  */ {                                                        // (12) 0.005525
/*4  */     unsigned int tag;                                    // (9) 0.03867
/*6  */     int64_t size;                                        // (7) 0.04972
/*10 */     for (;;) {                                           // (8) 0.0442
/*12 */         if (url_feof(pb))                                // (4) 0.0884
/*14 */             return AVERROR_EOF;                          // (2) 0.105
/*16 */         size = next_tag(pb, &tag);                       // (3) 0.09945
/*18 */         if (tag == tag1)                                 // (5) 0.07735
/*20 */             break;                                       // (6) 0.07182
/*22 */         wav_seek_tag(pb, size, SEEK_CUR);                // (0) 0.1326
/*24 */     }                                                    // (11) 0.0221
/*26 */     return size;                                         // (10) 0.03315
/*28 */ }                                                        // (13) 0.005525
