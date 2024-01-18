// commit message FFmpeg@1181d93231 (target=0, prob=0.0052239113, correct=True): avcodec/mips: Improve avc avg mc 22, 11, 31, 13 and 33 msa functions
/*0   */ static void avc_luma_hv_qrt_and_aver_dst_4x4_msa(const uint8_t *src_x,           // (4) 0.07422
/*2   */                                                  const uint8_t *src_y,           // (0) 0.1133
/*4   */                                                  int32_t src_stride,             // (1) 0.1113
/*6   */                                                  uint8_t *dst,                   // (3) 0.1094
/*8   */                                                  int32_t dst_stride)             // (2) 0.1113
/*10  */ {                                                                                // (14) 0.001953
/*12  */     v16i8 src_hz0, src_hz1, src_hz2, src_hz3;                                    // (8) 0.05273
/*14  */     v16u8 dst0, dst1, dst2, dst3;                                                // (10) 0.03711
/*16  */     v16i8 src_vt0, src_vt1, src_vt2, src_vt3, src_vt4;                           // (5) 0.0625
/*18  */     v16i8 src_vt5, src_vt6, src_vt7, src_vt8;                                    // (9) 0.05273
/*20  */     v16i8 mask0, mask1, mask2;                                                   // (11) 0.03125
/*22  */     v8i16 hz_out0, hz_out1, vert_out0, vert_out1;                                // (6) 0.05664
/*24  */     v8i16 res0, res1;                                                            // (12) 0.02539
/*26  */     v16u8 res;                                                                   // (13) 0.01758
/*30  */     LD_SB3(&luma_mask_arr[48], 16, mask0, mask1, mask2);                         // (7) 0.05469
/*32  */     LD_SB5(src_y, src_stride, src_vt0, src_vt1, src_vt2, src_vt3, src_vt4);      // 0.0
/*34  */     src_y += (5 * src_stride);                                                   // 0.0
/*38  */     src_vt0 = (v16i8) __msa_insve_w((v4i32) src_vt0, 1, (v4i32) src_vt1);        // 0.0
/*40  */     src_vt1 = (v16i8) __msa_insve_w((v4i32) src_vt1, 1, (v4i32) src_vt2);        // 0.0
/*42  */     src_vt2 = (v16i8) __msa_insve_w((v4i32) src_vt2, 1, (v4i32) src_vt3);        // 0.0
/*44  */     src_vt3 = (v16i8) __msa_insve_w((v4i32) src_vt3, 1, (v4i32) src_vt4);        // 0.0
/*48  */     XORI_B4_128_SB(src_vt0, src_vt1, src_vt2, src_vt3);                          // 0.0
/*50  */     LD_SB4(src_x, src_stride, src_hz0, src_hz1, src_hz2, src_hz3);               // 0.0
/*52  */     LD_UB4(dst, dst_stride, dst0, dst1, dst2, dst3);                             // 0.0
/*54  */     XORI_B4_128_SB(src_hz0, src_hz1, src_hz2, src_hz3);                          // 0.0
/*56  */     hz_out0 = AVC_XOR_VSHF_B_AND_APPLY_6TAP_HORIZ_FILT_SH(src_hz0, src_hz1,      // 0.0
/*58  */                                                           mask0, mask1, mask2);  // 0.0
/*60  */     hz_out1 = AVC_XOR_VSHF_B_AND_APPLY_6TAP_HORIZ_FILT_SH(src_hz2, src_hz3,      // 0.0
/*62  */                                                           mask0, mask1, mask2);  // 0.0
/*64  */     SRARI_H2_SH(hz_out0, hz_out1, 5);                                            // 0.0
/*66  */     SAT_SH2_SH(hz_out0, hz_out1, 7);                                             // 0.0
/*68  */     LD_SB4(src_y, src_stride, src_vt5, src_vt6, src_vt7, src_vt8);               // 0.0
/*72  */     src_vt4 = (v16i8) __msa_insve_w((v4i32) src_vt4, 1, (v4i32) src_vt5);        // 0.0
/*74  */     src_vt5 = (v16i8) __msa_insve_w((v4i32) src_vt5, 1, (v4i32) src_vt6);        // 0.0
/*76  */     src_vt6 = (v16i8) __msa_insve_w((v4i32) src_vt6, 1, (v4i32) src_vt7);        // 0.0
/*78  */     src_vt7 = (v16i8) __msa_insve_w((v4i32) src_vt7, 1, (v4i32) src_vt8);        // 0.0
/*82  */     XORI_B4_128_SB(src_vt4, src_vt5, src_vt6, src_vt7);                          // 0.0
/*86  */     /* filter calc */                                                            // 0.0
/*88  */     vert_out0 = AVC_CALC_DPADD_B_6PIX_2COEFF_R_SH(src_vt0, src_vt1, src_vt2,     // 0.0
/*90  */                                                   src_vt3, src_vt4, src_vt5);    // 0.0
/*92  */     vert_out1 = AVC_CALC_DPADD_B_6PIX_2COEFF_R_SH(src_vt2, src_vt3, src_vt4,     // 0.0
/*94  */                                                   src_vt5, src_vt6, src_vt7);    // 0.0
/*96  */     SRARI_H2_SH(vert_out0, vert_out1, 5);                                        // 0.0
/*98  */     SAT_SH2_SH(vert_out0, vert_out1, 7);                                         // 0.0
/*102 */     res1 = __msa_srari_h((hz_out1 + vert_out1), 1);                              // 0.0
/*104 */     res0 = __msa_srari_h((hz_out0 + vert_out0), 1);                              // 0.0
/*108 */     SAT_SH2_SH(res0, res1, 7);                                                   // 0.0
/*110 */     res = PCKEV_XORI128_UB(res0, res1);                                          // 0.0
/*114 */     dst0 = (v16u8) __msa_insve_w((v4i32) dst0, 1, (v4i32) dst1);                 // 0.0
/*116 */     dst1 = (v16u8) __msa_insve_w((v4i32) dst2, 1, (v4i32) dst3);                 // 0.0
/*118 */     dst0 = (v16u8) __msa_insve_d((v2i64) dst0, 1, (v2i64) dst1);                 // 0.0
/*120 */     dst0 = __msa_aver_u_b(res, dst0);                                            // 0.0
/*124 */     ST4x4_UB(dst0, dst0, 0, 1, 2, 3, dst, dst_stride);                           // 0.0
/*126 */ }                                                                                // 0.0
