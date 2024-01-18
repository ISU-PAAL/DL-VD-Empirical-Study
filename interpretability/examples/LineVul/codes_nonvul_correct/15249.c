// commit message FFmpeg@5e65f5df0e (target=0, prob=0.24795188, correct=True): Follow FFmpeg convention of returning negative values on error in eval_lpc_coeffs()
/*0  */ static int eval_lpc_coeffs(const float *in, float *tgt, int n)  // (4) 0.05897
/*2  */ {                                                               // (22) 0.002457
/*4  */     int x, y;                                                   // (18) 0.01966
/*6  */     double f0, f1, f2;                                          // (14) 0.03194
/*10 */     if (in[n] == 0)                                             // (15) 0.02948
/*12 */         return 0;                                               // (16) 0.02457
/*16 */     if ((f0 = *in) <= 0)                                        // (12) 0.0344
/*18 */         return 0;                                               // (17) 0.02457
/*22 */     in--; // To avoid a -1 subtraction in the inner loop        // (9) 0.04423
/*26 */     for (x=1; x <= n; x++) {                                    // (10) 0.03931
/*28 */         f1 = in[x+1];                                           // (11) 0.03931
/*32 */         for (y=0; y < x - 1; y++)                               // (6) 0.0516
/*34 */             f1 += in[x-y]*tgt[y];                               // (2) 0.06388
/*38 */         tgt[x-1] = f2 = -f1/f0;                                 // (3) 0.06143
/*40 */         for (y=0; y < x >> 1; y++) {                            // (5) 0.05405
/*42 */             float temp = tgt[y] + tgt[x-y-2]*f2;                // (0) 0.08108
/*44 */             tgt[x-y-2] += tgt[y]*f2;                            // (1) 0.07371
/*46 */             tgt[y] = temp;                                      // (8) 0.04668
/*48 */         }                                                       // (19) 0.01966
/*50 */         if ((f0 += f1*f2) < 0)                                  // (7) 0.0516
/*52 */             return 0;                                           // (13) 0.0344
/*54 */     }                                                           // (21) 0.009828
/*58 */     return 1;                                                   // (20) 0.01474
/*60 */ }                                                               // (23) 0.002457
