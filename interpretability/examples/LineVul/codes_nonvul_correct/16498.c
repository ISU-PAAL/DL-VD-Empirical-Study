// commit message FFmpeg@bcd7bf7eeb (target=0, prob=0.011276724, correct=True): avcodec/mips: Restructure as per avutil/mips/generic_macros_msa.h
/*0   */ static void avc_biwgt_4x4multiple_msa(uint8_t *src,                            // (8) 0.04688
/*2   */                                       int32_t src_stride,                      // (2) 0.08984
/*4   */                                       uint8_t *dst,                            // (3) 0.08789
/*6   */                                       int32_t dst_stride,                      // (1) 0.08984
/*8   */                                       int32_t height,                          // (7) 0.08398
/*10  */                                       int32_t log2_denom,                      // (0) 0.09179
/*12  */                                       int32_t src_weight,                      // (5) 0.08789
/*14  */                                       int32_t dst_weight,                      // (6) 0.08789
/*16  */                                       int32_t offset_in)                       // (4) 0.08789
/*18  */ {                                                                              // (15) 0.001954
/*20  */     uint8_t cnt;                                                               // (14) 0.01957
/*22  */     uint32_t load0, load1, load2, load3;                                       // (11) 0.03711
/*24  */     v16i8 src_wgt, dst_wgt, wgt;                                               // (9) 0.03906
/*26  */     v16i8 src0, src1, src2, src3;                                              // (13) 0.03711
/*28  */     v16i8 dst0, dst1, dst2, dst3;                                              // (12) 0.03711
/*30  */     v8i16 temp0, temp1, temp2, temp3;                                          // (10) 0.03711
/*32  */     v8i16 denom, offset, add_val;                                              // 0.0
/*34  */     int32_t val = 128 * (src_weight + dst_weight);                             // 0.0
/*38  */     offset_in = ((offset_in + 1) | 1) << log2_denom;                           // 0.0
/*42  */     src_wgt = __msa_fill_b(src_weight);                                        // 0.0
/*44  */     dst_wgt = __msa_fill_b(dst_weight);                                        // 0.0
/*46  */     offset = __msa_fill_h(offset_in);                                          // 0.0
/*48  */     denom = __msa_fill_h(log2_denom + 1);                                      // 0.0
/*50  */     add_val = __msa_fill_h(val);                                               // 0.0
/*52  */     offset += add_val;                                                         // 0.0
/*56  */     wgt = __msa_ilvev_b(dst_wgt, src_wgt);                                     // 0.0
/*60  */     for (cnt = height / 4; cnt--;) {                                           // 0.0
/*62  */         LOAD_4WORDS_WITH_STRIDE(src, src_stride, load0, load1, load2, load3);  // 0.0
/*64  */         src += (4 * src_stride);                                               // 0.0
/*68  */         src0 = (v16i8) __msa_fill_w(load0);                                    // 0.0
/*70  */         src1 = (v16i8) __msa_fill_w(load1);                                    // 0.0
/*72  */         src2 = (v16i8) __msa_fill_w(load2);                                    // 0.0
/*74  */         src3 = (v16i8) __msa_fill_w(load3);                                    // 0.0
/*78  */         LOAD_4WORDS_WITH_STRIDE(dst, dst_stride, load0, load1, load2, load3);  // 0.0
/*82  */         dst0 = (v16i8) __msa_fill_w(load0);                                    // 0.0
/*84  */         dst1 = (v16i8) __msa_fill_w(load1);                                    // 0.0
/*86  */         dst2 = (v16i8) __msa_fill_w(load2);                                    // 0.0
/*88  */         dst3 = (v16i8) __msa_fill_w(load3);                                    // 0.0
/*92  */         XORI_B_4VECS_SB(src0, src1, src2, src3, src0, src1, src2, src3, 128);  // 0.0
/*96  */         XORI_B_4VECS_SB(dst0, dst1, dst2, dst3, dst0, dst1, dst2, dst3, 128);  // 0.0
/*100 */         ILVR_B_4VECS_SH(src0, src1, src2, src3, dst0, dst1, dst2, dst3,        // 0.0
/*102 */                         temp0, temp1, temp2, temp3);                           // 0.0
/*106 */         temp0 = __msa_dpadd_s_h(offset, wgt, (v16i8) temp0);                   // 0.0
/*108 */         temp1 = __msa_dpadd_s_h(offset, wgt, (v16i8) temp1);                   // 0.0
/*110 */         temp2 = __msa_dpadd_s_h(offset, wgt, (v16i8) temp2);                   // 0.0
/*112 */         temp3 = __msa_dpadd_s_h(offset, wgt, (v16i8) temp3);                   // 0.0
/*116 */         SRA_4VECS(temp0, temp1, temp2, temp3,                                  // 0.0
/*118 */                   temp0, temp1, temp2, temp3, denom);                          // 0.0
/*122 */         temp0 = CLIP_UNSIGNED_CHAR_H(temp0);                                   // 0.0
/*124 */         temp1 = CLIP_UNSIGNED_CHAR_H(temp1);                                   // 0.0
/*126 */         temp2 = CLIP_UNSIGNED_CHAR_H(temp2);                                   // 0.0
/*128 */         temp3 = CLIP_UNSIGNED_CHAR_H(temp3);                                   // 0.0
/*132 */         PCKEV_B_STORE_4_BYTES_4(temp0, temp1, temp2, temp3, dst, dst_stride);  // 0.0
/*134 */         dst += (4 * dst_stride);                                               // 0.0
/*136 */     }                                                                          // 0.0
/*138 */ }                                                                              // 0.0
