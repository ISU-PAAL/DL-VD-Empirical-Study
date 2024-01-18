// commit message FFmpeg@44ac13eed4 (target=1, prob=0.95337486, correct=True): dca: fix misaligned access in avpriv_dca_convert_bitstream
/*0  */ int avpriv_dca_convert_bitstream(const uint8_t *src, int src_size, uint8_t *dst,               // (1) 0.06641
/*2  */                              int max_size)                                                     // (2) 0.06445
/*4  */ {                                                                                              // (23) 0.001953
/*6  */     uint32_t mrk;                                                                              // (19) 0.02148
/*8  */     int i, tmp;                                                                                // (22) 0.01562
/*10 */     const uint16_t *ssrc = (const uint16_t *) src;                                             // (7) 0.04102
/*12 */     uint16_t *sdst = (uint16_t *) dst;                                                         // (11) 0.03711
/*14 */     PutBitContext pb;                                                                          // (20) 0.01758
/*18 */     if ((unsigned) src_size > (unsigned) max_size)                                             // (12) 0.03516
/*20 */         src_size = max_size;                                                                   // (15) 0.0293
/*24 */     mrk = AV_RB32(src);                                                                        // (16) 0.02734
/*26 */     switch (mrk) {                                                                             // (21) 0.01758
/*28 */     case DCA_SYNCWORD_CORE_BE:                                                                 // (13) 0.0332
/*30 */         memcpy(dst, src, src_size);                                                            // (8) 0.03906
/*32 */         return src_size;                                                                       // (17) 0.02344
/*34 */     case DCA_SYNCWORD_CORE_LE:                                                                 // (14) 0.0332
/*36 */         for (i = 0; i < (src_size + 1) >> 1; i++)                                              // (4) 0.05273
/*38 */             *sdst++ = av_bswap16(*ssrc++);                                                     // (5) 0.05273
/*40 */         return src_size;                                                                       // (18) 0.02344
/*42 */     case DCA_SYNCWORD_CORE_14B_BE:                                                             // (9) 0.03906
/*44 */     case DCA_SYNCWORD_CORE_14B_LE:                                                             // (10) 0.03906
/*46 */         init_put_bits(&pb, dst, max_size);                                                     // (6) 0.04102
/*48 */         for (i = 0; i < (src_size + 1) >> 1; i++, src += 2) {                                  // (3) 0.06445
/*50 */             tmp = ((mrk == DCA_SYNCWORD_CORE_14B_BE) ? AV_RB16(src) : AV_RL16(src)) & 0x3FFF;  // (0) 0.1094
/*52 */             put_bits(&pb, 14, tmp);                                                            // 0.0
/*54 */         }                                                                                      // 0.0
/*56 */         flush_put_bits(&pb);                                                                   // 0.0
/*58 */         return (put_bits_count(&pb) + 7) >> 3;                                                 // 0.0
/*60 */     default:                                                                                   // 0.0
/*62 */         return AVERROR_INVALIDDATA;                                                            // 0.0
/*64 */     }                                                                                          // 0.0
/*66 */ }                                                                                              // 0.0
