// commit message FFmpeg@1181d93231 (target=0, prob=0.003648985, correct=True): avcodec/mips: Improve avc avg mc 22, 11, 31, 13 and 33 msa functions
/*0  */ void ff_avg_h264_qpel16_mc33_msa(uint8_t *dst, const uint8_t *src,   // (4) 0.1296
/*2  */                                  ptrdiff_t stride)                   // (3) 0.1407
/*4  */ {                                                                    // (6) 0.003704
/*6  */     avc_luma_hv_qrt_and_aver_dst_16x16_msa(src + stride - 2,         // (5) 0.1296
/*8  */                                            src - (stride * 2) +      // (0) 0.1889
/*10 */                                            sizeof(uint8_t), stride,  // (1) 0.1889
/*12 */                                            dst, stride);             // (2) 0.1704
/*14 */ }                                                                    // (7) 0.003704
