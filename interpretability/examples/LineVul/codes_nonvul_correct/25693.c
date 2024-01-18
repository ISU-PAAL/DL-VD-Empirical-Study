// commit message FFmpeg@1181d93231 (target=0, prob=0.0038757224, correct=True): avcodec/mips: Improve avc avg mc 22, 11, 31, 13 and 33 msa functions
/*0  */ void ff_avg_h264_qpel4_mc13_msa(uint8_t *dst, const uint8_t *src,  // (3) 0.1636
/*2  */                                 ptrdiff_t stride)                  // (2) 0.1729
/*4  */ {                                                                  // (5) 0.004673
/*6  */     avc_luma_hv_qrt_and_aver_dst_4x4_msa(src + stride - 2,         // (4) 0.1636
/*8  */                                          src - (stride * 2),       // (0) 0.2243
/*10 */                                          stride, dst, stride);     // (1) 0.215
/*12 */ }                                                                  // (6) 0.004673
