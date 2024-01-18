// commit message FFmpeg@2aab7c2dfa (target=0, prob=0.003620827, correct=True): avcodec/mips: Improve avc put mc 11, 31, 13 and 33 msa functions
/*0  */ void ff_put_h264_qpel8_mc31_msa(uint8_t *dst, const uint8_t *src,     // (3) 0.1838
/*2  */                                 ptrdiff_t stride)                     // (1) 0.2
/*4  */ {                                                                     // (5) 0.005405
/*6  */     avc_luma_hv_qrt_8w_msa(src - 2,                                   // (4) 0.1351
/*8  */                            src - (stride * 2) +                       // (2) 0.1892
/*10 */                            sizeof(uint8_t), stride, dst, stride, 8);  // (0) 0.2216
/*12 */ }                                                                     // (6) 0.005405
