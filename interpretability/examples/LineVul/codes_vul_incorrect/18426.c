// commit message FFmpeg@5ff998a233 (target=1, prob=0.13529837, correct=False): flacenc: use uint64_t for bit counts
/*0  */ static uint32_t calc_optimal_rice_params(RiceContext *rc, int porder,            // (2) 0.07973
/*2  */                                          uint32_t *sums, int n, int pred_order)  // (0) 0.186
/*4  */ {                                                                                // (16) 0.003322
/*6  */     int i;                                                                       // (14) 0.01993
/*8  */     int k, cnt, part;                                                            // (9) 0.03654
/*10 */     uint32_t all_bits;                                                           // (10) 0.03654
/*14 */     part     = (1 << porder);                                                    // (7) 0.04983
/*16 */     all_bits = 4 * part;                                                         // (11) 0.03654
/*20 */     cnt = (n >> porder) - pred_order;                                            // (4) 0.05648
/*22 */     for (i = 0; i < part; i++) {                                                 // (5) 0.05316
/*24 */         k = find_optimal_param(sums[i], cnt);                                    // (3) 0.07973
/*26 */         rc->params[i] = k;                                                       // (6) 0.05316
/*28 */         all_bits += rice_encode_count(sums[i], cnt, k);                          // (1) 0.09302
/*30 */         cnt = n >> porder;                                                       // (8) 0.04983
/*32 */     }                                                                            // (15) 0.01329
/*36 */     rc->porder = porder;                                                         // (12) 0.03654
/*40 */     return all_bits;                                                             // (13) 0.02658
/*42 */ }                                                                                // (17) 0.003322
