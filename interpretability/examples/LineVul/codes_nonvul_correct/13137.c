// commit message FFmpeg@662234a9a2 (target=0, prob=0.0060965507, correct=True): avcodec/mips: Improve avc put mc 21, 23 and 02 msa functions
/*0   */ static void avc_luma_midv_qrt_4w_msa(const uint8_t *src, int32_t src_stride,     // (3) 0.07227
/*2   */                                      uint8_t *dst, int32_t dst_stride,           // (0) 0.1035
/*4   */                                      int32_t height, uint8_t ver_offset)         // (1) 0.09766
/*6   */ {                                                                                // (14) 0.001953
/*8   */     uint32_t loop_cnt;                                                           // (13) 0.02344
/*10  */     v16i8 src0, src1, src2, src3, src4;                                          // (10) 0.04297
/*12  */     v16i8 mask0, mask1, mask2;                                                   // (11) 0.03125
/*14  */     v8i16 hz_out0, hz_out1, hz_out2, hz_out3;                                    // (6) 0.06055
/*16  */     v8i16 hz_out4, hz_out5, hz_out6, hz_out7, hz_out8;                           // (4) 0.07227
/*18  */     v8i16 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;                        // (5) 0.06055
/*22  */     LD_SB3(&luma_mask_arr[48], 16, mask0, mask1, mask2);                         // (9) 0.05469
/*24  */     LD_SB5(src, src_stride, src0, src1, src2, src3, src4);                       // (7) 0.05859
/*26  */     src += (5 * src_stride);                                                     // (12) 0.02539
/*30  */     XORI_B5_128_SB(src0, src1, src2, src3, src4);                                // (8) 0.05664
/*34  */     hz_out0 = AVC_XOR_VSHF_B_AND_APPLY_6TAP_HORIZ_FILT_SH(src0, src1,            // (2) 0.08984
/*36  */                                                           mask0, mask1, mask2);  // 0.0
/*38  */     hz_out2 = AVC_XOR_VSHF_B_AND_APPLY_6TAP_HORIZ_FILT_SH(src2, src3,            // 0.0
/*40  */                                                           mask0, mask1, mask2);  // 0.0
/*44  */     PCKOD_D2_SH(hz_out0, hz_out0, hz_out2, hz_out2, hz_out1, hz_out3);           // 0.0
/*48  */     hz_out4 = AVC_HORZ_FILTER_SH(src4, mask0, mask1, mask2);                     // 0.0
/*52  */     for (loop_cnt = (height >> 2); loop_cnt--;) {                                // 0.0
/*54  */         LD_SB4(src, src_stride, src0, src1, src2, src3);                         // 0.0
/*56  */         src += (4 * src_stride);                                                 // 0.0
/*58  */         XORI_B4_128_SB(src0, src1, src2, src3);                                  // 0.0
/*62  */         hz_out5 = AVC_XOR_VSHF_B_AND_APPLY_6TAP_HORIZ_FILT_SH(src0, src1,        // 0.0
/*64  */                                                               mask0, mask1,      // 0.0
/*66  */                                                               mask2);            // 0.0
/*68  */         hz_out7 = AVC_XOR_VSHF_B_AND_APPLY_6TAP_HORIZ_FILT_SH(src2, src3,        // 0.0
/*70  */                                                               mask0, mask1,      // 0.0
/*72  */                                                               mask2);            // 0.0
/*76  */         PCKOD_D2_SH(hz_out5, hz_out5, hz_out7, hz_out7, hz_out6, hz_out8);       // 0.0
/*80  */         dst0 = AVC_CALC_DPADD_H_6PIX_2COEFF_SH(hz_out0, hz_out1, hz_out2,        // 0.0
/*82  */                                                hz_out3, hz_out4, hz_out5);       // 0.0
/*84  */         dst2 = AVC_CALC_DPADD_H_6PIX_2COEFF_SH(hz_out1, hz_out2, hz_out3,        // 0.0
/*86  */                                                hz_out4, hz_out5, hz_out6);       // 0.0
/*88  */         dst4 = AVC_CALC_DPADD_H_6PIX_2COEFF_SH(hz_out2, hz_out3, hz_out4,        // 0.0
/*90  */                                                hz_out5, hz_out6, hz_out7);       // 0.0
/*92  */         dst6 = AVC_CALC_DPADD_H_6PIX_2COEFF_SH(hz_out3, hz_out4, hz_out5,        // 0.0
/*94  */                                                hz_out6, hz_out7, hz_out8);       // 0.0
/*98  */         if (ver_offset) {                                                        // 0.0
/*100 */             dst1 = __msa_srari_h(hz_out3, 5);                                    // 0.0
/*102 */             dst3 = __msa_srari_h(hz_out4, 5);                                    // 0.0
/*104 */             dst5 = __msa_srari_h(hz_out5, 5);                                    // 0.0
/*106 */             dst7 = __msa_srari_h(hz_out6, 5);                                    // 0.0
/*108 */         } else {                                                                 // 0.0
/*110 */             dst1 = __msa_srari_h(hz_out2, 5);                                    // 0.0
/*112 */             dst3 = __msa_srari_h(hz_out3, 5);                                    // 0.0
/*114 */             dst5 = __msa_srari_h(hz_out4, 5);                                    // 0.0
/*116 */             dst7 = __msa_srari_h(hz_out5, 5);                                    // 0.0
/*118 */         }                                                                        // 0.0
/*122 */         SAT_SH4_SH(dst1, dst3, dst5, dst7, 7);                                   // 0.0
/*126 */         dst0 = __msa_aver_s_h(dst0, dst1);                                       // 0.0
/*128 */         dst1 = __msa_aver_s_h(dst2, dst3);                                       // 0.0
/*130 */         dst2 = __msa_aver_s_h(dst4, dst5);                                       // 0.0
/*132 */         dst3 = __msa_aver_s_h(dst6, dst7);                                       // 0.0
/*136 */         PCKEV_B2_SB(dst1, dst0, dst3, dst2, src0, src1);                         // 0.0
/*138 */         XORI_B2_128_SB(src0, src1);                                              // 0.0
/*142 */         ST4x4_UB(src0, src1, 0, 2, 0, 2, dst, dst_stride);                       // 0.0
/*146 */         dst += (4 * dst_stride);                                                 // 0.0
/*148 */         hz_out0 = hz_out4;                                                       // 0.0
/*150 */         hz_out1 = hz_out5;                                                       // 0.0
/*152 */         hz_out2 = hz_out6;                                                       // 0.0
/*154 */         hz_out3 = hz_out7;                                                       // 0.0
/*156 */         hz_out4 = hz_out8;                                                       // 0.0
/*158 */     }                                                                            // 0.0
/*160 */ }                                                                                // 0.0
