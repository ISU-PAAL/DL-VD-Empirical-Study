// commit message FFmpeg@72dbc610be (target=0, prob=0.0035882571, correct=True): avcodec/mips: Improve avc avg mc 02, 12 and 32 msa functions
/*0  */ void ff_avg_h264_qpel16_mc12_msa(uint8_t *dst, const uint8_t *src,       // (3) 0.2
/*2  */                                  ptrdiff_t stride)                       // (2) 0.2171
/*4  */ {                                                                        // (4) 0.005714
/*6  */     avc_luma_midh_qrt_and_aver_dst_16w_msa(src - (2 * stride) - 2,       // (1) 0.2171
/*8  */                                            stride, dst, stride, 16, 0);  // (0) 0.2971
/*10 */ }                                                                        // (5) 0.005714
