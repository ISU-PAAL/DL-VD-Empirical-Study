// commit message FFmpeg@bcd7bf7eeb (target=0, prob=0.00637518, correct=True): avcodec/mips: Restructure as per avutil/mips/generic_macros_msa.h
/*0  */ void ff_h264_h_lpf_chroma_inter_msa(uint8_t *data, int img_width,           // (5) 0.06078
/*2  */                                     int alpha, int beta, int8_t *tc)        // (4) 0.09412
/*4  */ {                                                                           // (19) 0.001961
/*6  */     uint8_t bs0 = 1;                                                        // (7) 0.02549
/*8  */     uint8_t bs1 = 1;                                                        // (8) 0.02549
/*10 */     uint8_t bs2 = 1;                                                        // (9) 0.02549
/*12 */     uint8_t bs3 = 1;                                                        // (10) 0.02549
/*16 */     if (tc[0] < 0)                                                          // (15) 0.02353
/*18 */         bs0 = 0;                                                            // (11) 0.02549
/*20 */     if (tc[1] < 0)                                                          // (16) 0.02353
/*22 */         bs1 = 0;                                                            // (12) 0.02549
/*24 */     if (tc[2] < 0)                                                          // (17) 0.02353
/*26 */         bs2 = 0;                                                            // (13) 0.02549
/*28 */     if (tc[3] < 0)                                                          // (18) 0.02353
/*30 */         bs3 = 0;                                                            // (14) 0.02549
/*34 */     avc_loopfilter_cb_or_cr_inter_edge_ver_msa(data,                        // (6) 0.05098
/*36 */                                                bs0, bs1, bs2, bs3,          // (0) 0.1216
/*38 */                                                tc[0], tc[1], tc[2], tc[3],  // (1) 0.1216
/*40 */                                                alpha, beta,                 // (2) 0.09804
/*42 */                                                img_width);                  // (3) 0.09804
/*44 */ }                                                                           // (20) 0.001961
