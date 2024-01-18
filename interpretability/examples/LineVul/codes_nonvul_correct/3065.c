// commit message FFmpeg@662234a9a2 (target=0, prob=0.0034169704, correct=True): avcodec/mips: Improve avc put mc 21, 23 and 02 msa functions
/*0 */ void ff_put_h264_qpel8_mc21_msa(uint8_t *dst, const uint8_t *src,                 // (2) 0.2764
/*2 */                                 ptrdiff_t stride)                                 // (1) 0.3008
/*4 */ {                                                                                 // (3) 0.00813
/*6 */     avc_luma_midv_qrt_8w_msa(src - (2 * stride) - 2, stride, dst, stride, 8, 0);  // (0) 0.3333
/*8 */ }                                                                                 // (4) 0.00813
