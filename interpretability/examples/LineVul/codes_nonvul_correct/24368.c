// commit message FFmpeg@e549933a27 (target=0, prob=0.0060865334, correct=True): avcodec/mips: Improve avc put mc 12, 32 and 22 msa functions
/*0   */ static void avc_luma_mid_8w_msa(const uint8_t *src, int32_t src_stride,     // (6) 0.06445
/*2   */                                 uint8_t *dst, int32_t dst_stride,           // (0) 0.09375
/*4   */                                 int32_t height)                             // (1) 0.07226
/*6   */ {                                                                           // (17) 0.001953
/*8   */     uint32_t loop_cnt;                                                      // (16) 0.02344
/*10  */     v16i8 src0, src1, src2, src3, src4;                                     // (11) 0.04297
/*12  */     v16i8 mask0, mask1, mask2;                                              // (13) 0.03125
/*14  */     v8i16 hz_out0, hz_out1, hz_out2, hz_out3;                               // (7) 0.06055
/*16  */     v8i16 hz_out4, hz_out5, hz_out6, hz_out7, hz_out8;                      // (2) 0.07226
/*18  */     v8i16 dst0, dst1, dst2, dst3;                                           // (12) 0.03711
/*20  */     v16u8 out0, out1;                                                       // (14) 0.02539
/*24  */     LD_SB3(&luma_mask_arr[0], 16, mask0, mask1, mask2);                     // (10) 0.05469
/*28  */     LD_SB5(src, src_stride, src0, src1, src2, src3, src4);                  // (8) 0.05859
/*30  */     XORI_B5_128_SB(src0, src1, src2, src3, src4);                           // (9) 0.05664
/*32  */     src += (5 * src_stride);                                                // (15) 0.02539
/*36  */     hz_out0 = AVC_HORZ_FILTER_SH(src0, src0, mask0, mask1, mask2);          // (3) 0.07031
/*38  */     hz_out1 = AVC_HORZ_FILTER_SH(src1, src1, mask0, mask1, mask2);          // (4) 0.07031
/*40  */     hz_out2 = AVC_HORZ_FILTER_SH(src2, src2, mask0, mask1, mask2);          // (5) 0.07031
/*42  */     hz_out3 = AVC_HORZ_FILTER_SH(src3, src3, mask0, mask1, mask2);          // 0.0
/*44  */     hz_out4 = AVC_HORZ_FILTER_SH(src4, src4, mask0, mask1, mask2);          // 0.0
/*48  */     for (loop_cnt = (height >> 2); loop_cnt--;) {                           // 0.0
/*50  */         LD_SB4(src, src_stride, src0, src1, src2, src3);                    // 0.0
/*52  */         XORI_B4_128_SB(src0, src1, src2, src3);                             // 0.0
/*54  */         src += (4 * src_stride);                                            // 0.0
/*58  */         hz_out5 = AVC_HORZ_FILTER_SH(src0, src0, mask0, mask1, mask2);      // 0.0
/*60  */         hz_out6 = AVC_HORZ_FILTER_SH(src1, src1, mask0, mask1, mask2);      // 0.0
/*62  */         hz_out7 = AVC_HORZ_FILTER_SH(src2, src2, mask0, mask1, mask2);      // 0.0
/*64  */         hz_out8 = AVC_HORZ_FILTER_SH(src3, src3, mask0, mask1, mask2);      // 0.0
/*66  */         dst0 = AVC_CALC_DPADD_H_6PIX_2COEFF_SH(hz_out0, hz_out1, hz_out2,   // 0.0
/*68  */                                                hz_out3, hz_out4, hz_out5);  // 0.0
/*70  */         dst1 = AVC_CALC_DPADD_H_6PIX_2COEFF_SH(hz_out1, hz_out2, hz_out3,   // 0.0
/*72  */                                                hz_out4, hz_out5, hz_out6);  // 0.0
/*74  */         dst2 = AVC_CALC_DPADD_H_6PIX_2COEFF_SH(hz_out2, hz_out3, hz_out4,   // 0.0
/*76  */                                                hz_out5, hz_out6, hz_out7);  // 0.0
/*78  */         dst3 = AVC_CALC_DPADD_H_6PIX_2COEFF_SH(hz_out3, hz_out4, hz_out5,   // 0.0
/*80  */                                                hz_out6, hz_out7, hz_out8);  // 0.0
/*82  */         out0 = PCKEV_XORI128_UB(dst0, dst1);                                // 0.0
/*84  */         out1 = PCKEV_XORI128_UB(dst2, dst3);                                // 0.0
/*86  */         ST8x4_UB(out0, out1, dst, dst_stride);                              // 0.0
/*90  */         dst += (4 * dst_stride);                                            // 0.0
/*92  */         hz_out3 = hz_out7;                                                  // 0.0
/*94  */         hz_out1 = hz_out5;                                                  // 0.0
/*96  */         hz_out5 = hz_out4;                                                  // 0.0
/*98  */         hz_out4 = hz_out8;                                                  // 0.0
/*100 */         hz_out2 = hz_out6;                                                  // 0.0
/*102 */         hz_out0 = hz_out5;                                                  // 0.0
/*104 */     }                                                                       // 0.0
/*106 */ }                                                                           // 0.0
