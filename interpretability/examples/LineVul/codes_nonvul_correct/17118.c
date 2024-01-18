// commit message FFmpeg@2aab7c2dfa (target=0, prob=0.003696739, correct=True): avcodec/mips: Improve avc put mc 11, 31, 13 and 33 msa functions
/*0  */ void ff_put_h264_qpel4_mc33_msa(uint8_t *dst, const uint8_t *src,     // (3) 0.1818
/*2  */                                 ptrdiff_t stride)                     // (1) 0.1979
/*4  */ {                                                                     // (5) 0.005348
/*6  */     avc_luma_hv_qrt_4w_msa(src + stride - 2,                          // (4) 0.1444
/*8  */                            src - (stride * 2) +                       // (2) 0.1872
/*10 */                            sizeof(uint8_t), stride, dst, stride, 4);  // (0) 0.2193
/*12 */ }                                                                     // (6) 0.005348
