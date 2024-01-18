// commit message FFmpeg@b88be742fa (target=1, prob=0.42011133, correct=False): vc2enc: do not allocate packet until exact frame size is known
/*0  */ static int minimum_frame_bits(VC2EncContext *s)                            // (4) 0.08671
/*2  */ {                                                                          // (9) 0.00578
/*4  */     int slice_x, slice_y, bits = 0;                                        // (3) 0.09249
/*6  */     s->size_scaler = 64;                                                   // (5) 0.06936
/*8  */     for (slice_y = 0; slice_y < s->num_y; slice_y++) {                     // (2) 0.1503
/*10 */         for (slice_x = 0; slice_x < s->num_x; slice_x++) {                 // (1) 0.1734
/*12 */             bits += count_hq_slice(s, NULL, slice_x, slice_y, s->q_ceil);  // (0) 0.2254
/*14 */         }                                                                  // (6) 0.04624
/*16 */     }                                                                      // (8) 0.02312
/*18 */     return bits;                                                           // (7) 0.03468
/*20 */ }                                                                          // (10) 0.00578
