// commit message FFmpeg@1181d93231 (target=0, prob=0.003645848, correct=True): avcodec/mips: Improve avc avg mc 22, 11, 31, 13 and 33 msa functions
/*0  */ void ff_avg_h264_qpel4_mc31_msa(uint8_t *dst, const uint8_t *src,                // (3) 0.1591
/*2  */                                 ptrdiff_t stride)                                // (2) 0.1682
/*4  */ {                                                                                // (5) 0.004545
/*6  */     avc_luma_hv_qrt_and_aver_dst_4x4_msa(src - 2,                                // (4) 0.15
/*8  */                                          src - (stride * 2) +                    // (1) 0.2227
/*10 */                                          sizeof(uint8_t), stride, dst, stride);  // (0) 0.2409
/*12 */ }                                                                                // (6) 0.004545
