// commit message FFmpeg@560b10a6c3 (target=1, prob=0.69831526, correct=True): Dual mono stereo strems sound ok now, added sanity checks and removed some unused variables and redundant memsets. Patch by Benjamin Larsson
/*0  */ static void init_gain_table(COOKContext *q) {                       // (8) 0.06329
/*2  */     int i;                                                          // (9) 0.02532
/*4  */     q->gain_size_factor = q->samples_per_channel/8;                 // (2) 0.09283
/*6  */     for (i=0 ; i<23 ; i++) {                                        // (7) 0.06751
/*8  */         q->gain_table[i] = pow((double)q->pow2tab[i+52] ,           // (1) 0.135
/*10 */                                (1.0/(double)q->gain_size_factor));  // (0) 0.1899
/*12 */     }                                                               // (10) 0.01688
/*14 */     memset(&q->gain_copy, 0, sizeof(COOKgain));                     // (4) 0.08439
/*16 */     memset(&q->gain_current, 0, sizeof(COOKgain));                  // (5) 0.08439
/*18 */     memset(&q->gain_now, 0, sizeof(COOKgain));                      // (6) 0.08439
/*20 */     memset(&q->gain_previous, 0, sizeof(COOKgain));                 // (3) 0.08861
/*22 */ }                                                                   // (11) 0.004219
