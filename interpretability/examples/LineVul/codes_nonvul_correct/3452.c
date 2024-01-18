// commit message FFmpeg@bcd7bf7eeb (target=0, prob=0.0075577204, correct=True): avcodec/mips: Restructure as per avutil/mips/generic_macros_msa.h
/*0   */ static void avc_loopfilter_cb_or_cr_intra_edge_ver_msa(uint8_t *data_cb_or_cr,    // (4) 0.07227
/*2   */                                                        uint8_t alpha_in,          // (2) 0.1211
/*4   */                                                        uint8_t beta_in,           // (1) 0.1211
/*6   */                                                        uint32_t img_width)        // (0) 0.1211
/*8   */ {                                                                                 // (15) 0.001953
/*10  */     uint16_t out0, out1, out2, out3;                                              // (10) 0.03711
/*12  */     v8i16 tmp1;                                                                   // (13) 0.01953
/*14  */     v16u8 alpha, beta, is_less_than;                                              // (11) 0.0332
/*16  */     v8i16 p0_or_q0, q0_or_p0;                                                     // (9) 0.04492
/*18  */     v16u8 p1_or_q1_org, p0_or_q0_org, q0_or_p0_org, q1_or_p1_org;                 // (3) 0.0918
/*20  */     v16i8 zero = { 0 };                                                           // (12) 0.02344
/*22  */     v16u8 p0_asub_q0, p1_asub_p0, q1_asub_q0;                                     // (7) 0.06641
/*24  */     v16u8 is_less_than_alpha, is_less_than_beta;                                  // (8) 0.04492
/*26  */     v8i16 p1_org_r, p0_org_r, q0_org_r, q1_org_r;                                 // (6) 0.06836
/*30  */     {                                                                             // (14) 0.007813
/*32  */         v16u8 row0, row1, row2, row3, row4, row5, row6, row7;                     // (5) 0.06836
/*36  */         LOAD_8VECS_UB((data_cb_or_cr - 2), img_width,                             // 0.0
/*38  */                       row0, row1, row2, row3, row4, row5, row6, row7);            // 0.0
/*42  */         TRANSPOSE8x4_B_UB(row0, row1, row2, row3, row4, row5, row6, row7,         // 0.0
/*44  */                           p1_or_q1_org, p0_or_q0_org,                             // 0.0
/*46  */                           q0_or_p0_org, q1_or_p1_org);                            // 0.0
/*48  */     }                                                                             // 0.0
/*52  */     alpha = (v16u8) __msa_fill_b(alpha_in);                                       // 0.0
/*54  */     beta = (v16u8) __msa_fill_b(beta_in);                                         // 0.0
/*58  */     p0_asub_q0 = __msa_asub_u_b(p0_or_q0_org, q0_or_p0_org);                      // 0.0
/*60  */     p1_asub_p0 = __msa_asub_u_b(p1_or_q1_org, p0_or_q0_org);                      // 0.0
/*62  */     q1_asub_q0 = __msa_asub_u_b(q1_or_p1_org, q0_or_p0_org);                      // 0.0
/*66  */     is_less_than_alpha = (p0_asub_q0 < alpha);                                    // 0.0
/*68  */     is_less_than_beta = (p1_asub_p0 < beta);                                      // 0.0
/*70  */     is_less_than = is_less_than_beta & is_less_than_alpha;                        // 0.0
/*72  */     is_less_than_beta = (q1_asub_q0 < beta);                                      // 0.0
/*74  */     is_less_than = is_less_than_beta & is_less_than;                              // 0.0
/*78  */     is_less_than = (v16u8) __msa_ilvr_d((v2i64) zero, (v2i64) is_less_than);      // 0.0
/*82  */     if (!__msa_test_bz_v(is_less_than)) {                                         // 0.0
/*84  */         p1_org_r = (v8i16) __msa_ilvr_b(zero, (v16i8) p1_or_q1_org);              // 0.0
/*86  */         p0_org_r = (v8i16) __msa_ilvr_b(zero, (v16i8) p0_or_q0_org);              // 0.0
/*88  */         q0_org_r = (v8i16) __msa_ilvr_b(zero, (v16i8) q0_or_p0_org);              // 0.0
/*90  */         q1_org_r = (v8i16) __msa_ilvr_b(zero, (v16i8) q1_or_p1_org);              // 0.0
/*94  */         AVC_LOOP_FILTER_P0_OR_Q0(p0_org_r, q1_org_r, p1_org_r, p0_or_q0);         // 0.0
/*96  */         AVC_LOOP_FILTER_P0_OR_Q0(q0_org_r, p1_org_r, q1_org_r, q0_or_p0);         // 0.0
/*100 */         /* convert 16 bit output into 8 bit output */                             // 0.0
/*102 */         p0_or_q0 = (v8i16) __msa_pckev_b(zero, (v16i8) p0_or_q0);                 // 0.0
/*104 */         q0_or_p0 = (v8i16) __msa_pckev_b(zero, (v16i8) q0_or_p0);                 // 0.0
/*108 */         p0_or_q0_org =                                                            // 0.0
/*110 */             __msa_bmnz_v(p0_or_q0_org, (v16u8) p0_or_q0, is_less_than);           // 0.0
/*112 */         q0_or_p0_org =                                                            // 0.0
/*114 */             __msa_bmnz_v(q0_or_p0_org, (v16u8) q0_or_p0, is_less_than);           // 0.0
/*118 */         tmp1 = (v8i16) __msa_ilvr_b((v16i8) q0_or_p0_org, (v16i8) p0_or_q0_org);  // 0.0
/*122 */         data_cb_or_cr -= 1;                                                       // 0.0
/*126 */         out0 = __msa_copy_u_h(tmp1, 0);                                           // 0.0
/*128 */         out1 = __msa_copy_u_h(tmp1, 1);                                           // 0.0
/*130 */         out2 = __msa_copy_u_h(tmp1, 2);                                           // 0.0
/*132 */         out3 = __msa_copy_u_h(tmp1, 3);                                           // 0.0
/*136 */         STORE_HWORD(data_cb_or_cr, out0);                                         // 0.0
/*138 */         data_cb_or_cr += img_width;                                               // 0.0
/*140 */         STORE_HWORD(data_cb_or_cr, out1);                                         // 0.0
/*142 */         data_cb_or_cr += img_width;                                               // 0.0
/*144 */         STORE_HWORD(data_cb_or_cr, out2);                                         // 0.0
/*146 */         data_cb_or_cr += img_width;                                               // 0.0
/*148 */         STORE_HWORD(data_cb_or_cr, out3);                                         // 0.0
/*150 */         data_cb_or_cr += img_width;                                               // 0.0
/*154 */         out0 = __msa_copy_u_h(tmp1, 4);                                           // 0.0
/*156 */         out1 = __msa_copy_u_h(tmp1, 5);                                           // 0.0
/*158 */         out2 = __msa_copy_u_h(tmp1, 6);                                           // 0.0
/*160 */         out3 = __msa_copy_u_h(tmp1, 7);                                           // 0.0
/*164 */         STORE_HWORD(data_cb_or_cr, out0);                                         // 0.0
/*166 */         data_cb_or_cr += img_width;                                               // 0.0
/*168 */         STORE_HWORD(data_cb_or_cr, out1);                                         // 0.0
/*170 */         data_cb_or_cr += img_width;                                               // 0.0
/*172 */         STORE_HWORD(data_cb_or_cr, out2);                                         // 0.0
/*174 */         data_cb_or_cr += img_width;                                               // 0.0
/*176 */         STORE_HWORD(data_cb_or_cr, out3);                                         // 0.0
/*178 */     }                                                                             // 0.0
/*180 */ }                                                                                 // 0.0
