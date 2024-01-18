// commit message FFmpeg@29b0d94b43 (target=1, prob=0.60932964, correct=True): dfa: convert to bytestream2 API
/*0  */ static int decode_copy(uint8_t *frame, int width, int height,       // (1) 0.1429
/*2  */                        const uint8_t *src, const uint8_t *src_end)  // (0) 0.3008
/*4  */ {                                                                   // (7) 0.007519
/*6  */     const int size = width * height;                                // (4) 0.08271
/*10 */     if (src_end - src < size)                                       // (3) 0.09774
/*12 */         return -1;                                                  // (5) 0.08271
/*14 */     bytestream_get_buffer(&src, frame, size);                       // (2) 0.1278
/*16 */     return 0;                                                       // (6) 0.04511
/*18 */ }                                                                   // (8) 0.007519
