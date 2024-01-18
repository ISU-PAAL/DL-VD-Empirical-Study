// commit message FFmpeg@662234a9a2 (target=0, prob=0.0050842855, correct=True): avcodec/mips: Improve avc put mc 21, 23 and 02 msa functions
/*0   */ static void avc_luma_vt_16w_msa(const uint8_t *src, int32_t src_stride,         // (6) 0.06445
/*2   */                                 uint8_t *dst, int32_t dst_stride,               // (0) 0.09375
/*4   */                                 int32_t height)                                 // (4) 0.07227
/*6   */ {                                                                               // (17) 0.001953
/*8   */     int32_t loop_cnt;                                                           // (16) 0.02344
/*10  */     int16_t filt_const0 = 0xfb01;                                               // (12) 0.03516
/*12  */     int16_t filt_const1 = 0x1414;                                               // (13) 0.03516
/*14  */     int16_t filt_const2 = 0x1fb;                                                // (14) 0.03516
/*16  */     v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8;                 // (5) 0.06641
/*18  */     v16i8 src10_r, src32_r, src54_r, src76_r, src21_r, src43_r, src65_r;        // (2) 0.08203
/*20  */     v16i8 src87_r, src10_l, src32_l, src54_l, src76_l, src21_l, src43_l;        // (3) 0.08203
/*22  */     v16i8 src65_l, src87_l;                                                     // (15) 0.0332
/*24  */     v8i16 out0_r, out1_r, out2_r, out3_r, out0_l, out1_l, out2_l, out3_l;       // (1) 0.0918
/*26  */     v16u8 res0, res1, res2, res3;                                               // (10) 0.03711
/*28  */     v16i8 filt0, filt1, filt2;                                                  // (11) 0.03711
/*32  */     filt0 = (v16i8) __msa_fill_h(filt_const0);                                  // (9) 0.05273
/*34  */     filt1 = (v16i8) __msa_fill_h(filt_const1);                                  // (7) 0.05273
/*36  */     filt2 = (v16i8) __msa_fill_h(filt_const2);                                  // (8) 0.05273
/*40  */     LD_SB5(src, src_stride, src0, src1, src2, src3, src4);                      // 0.0
/*42  */     src += (5 * src_stride);                                                    // 0.0
/*46  */     XORI_B5_128_SB(src0, src1, src2, src3, src4);                               // 0.0
/*48  */     ILVR_B4_SB(src1, src0, src2, src1, src3, src2, src4, src3,                  // 0.0
/*50  */                src10_r, src21_r, src32_r, src43_r);                             // 0.0
/*52  */     ILVL_B4_SB(src1, src0, src2, src1, src3, src2, src4, src3,                  // 0.0
/*54  */                src10_l, src21_l, src32_l, src43_l);                             // 0.0
/*58  */     for (loop_cnt = (height >> 2); loop_cnt--;) {                               // 0.0
/*60  */         LD_SB4(src, src_stride, src5, src6, src7, src8);                        // 0.0
/*62  */         src += (4 * src_stride);                                                // 0.0
/*66  */         XORI_B4_128_SB(src5, src6, src7, src8);                                 // 0.0
/*68  */         ILVR_B4_SB(src5, src4, src6, src5, src7, src6, src8, src7,              // 0.0
/*70  */                    src54_r, src65_r, src76_r, src87_r);                         // 0.0
/*72  */         ILVL_B4_SB(src5, src4, src6, src5, src7, src6, src8, src7,              // 0.0
/*74  */                    src54_l, src65_l, src76_l, src87_l);                         // 0.0
/*76  */         out0_r = DPADD_SH3_SH(src10_r, src32_r, src54_r, filt0, filt1, filt2);  // 0.0
/*78  */         out1_r = DPADD_SH3_SH(src21_r, src43_r, src65_r, filt0, filt1, filt2);  // 0.0
/*80  */         out2_r = DPADD_SH3_SH(src32_r, src54_r, src76_r, filt0, filt1, filt2);  // 0.0
/*82  */         out3_r = DPADD_SH3_SH(src43_r, src65_r, src87_r, filt0, filt1, filt2);  // 0.0
/*84  */         out0_l = DPADD_SH3_SH(src10_l, src32_l, src54_l, filt0, filt1, filt2);  // 0.0
/*86  */         out1_l = DPADD_SH3_SH(src21_l, src43_l, src65_l, filt0, filt1, filt2);  // 0.0
/*88  */         out2_l = DPADD_SH3_SH(src32_l, src54_l, src76_l, filt0, filt1, filt2);  // 0.0
/*90  */         out3_l = DPADD_SH3_SH(src43_l, src65_l, src87_l, filt0, filt1, filt2);  // 0.0
/*92  */         SRARI_H4_SH(out0_r, out1_r, out2_r, out3_r, 5);                         // 0.0
/*94  */         SAT_SH4_SH(out0_r, out1_r, out2_r, out3_r, 7);                          // 0.0
/*96  */         SRARI_H4_SH(out0_l, out1_l, out2_l, out3_l, 5);                         // 0.0
/*98  */         SAT_SH4_SH(out0_l, out1_l, out2_l, out3_l, 7);                          // 0.0
/*100 */         PCKEV_B4_UB(out0_l, out0_r, out1_l, out1_r, out2_l, out2_r, out3_l,     // 0.0
/*102 */                     out3_r, res0, res1, res2, res3);                            // 0.0
/*104 */         XORI_B4_128_UB(res0, res1, res2, res3);                                 // 0.0
/*108 */         ST_UB4(res0, res1, res2, res3, dst, dst_stride);                        // 0.0
/*110 */         dst += (4 * dst_stride);                                                // 0.0
/*114 */         src10_r = src54_r;                                                      // 0.0
/*116 */         src32_r = src76_r;                                                      // 0.0
/*118 */         src21_r = src65_r;                                                      // 0.0
/*120 */         src43_r = src87_r;                                                      // 0.0
/*122 */         src10_l = src54_l;                                                      // 0.0
/*124 */         src32_l = src76_l;                                                      // 0.0
/*126 */         src21_l = src65_l;                                                      // 0.0
/*128 */         src43_l = src87_l;                                                      // 0.0
/*130 */         src4 = src8;                                                            // 0.0
/*132 */     }                                                                           // 0.0
/*134 */ }                                                                               // 0.0
