// commit message FFmpeg@3a54c221d5 (target=1, prob=0.5666569, correct=True): avcodec/srtdec: fix potential overread.
/*0  */ static const char *read_ts(const char *buf, int *ts_start, int *ts_end,      // (7) 0.05144
/*2  */                            int *x1, int *y1, int *x2, int *y2)               // (3) 0.09465
/*4  */ {                                                                            // (17) 0.002058
/*6  */     int i, hs, ms, ss, he, me, se;                                           // (10) 0.03909
/*10 */     for (i=0; i<2; i++) {                                                    // (11) 0.03292
/*12 */         /* try to read timestamps in either the first or second line */      // (8) 0.04527
/*14 */         int c = sscanf(buf, "%d:%2d:%2d%*1[,.]%3d --> %d:%2d:%2d%*1[,.]%3d"  // (0) 0.1152
/*16 */                        "%*[ ]X1:%u X2:%u Y1:%u Y2:%u",                       // (2) 0.09671
/*18 */                        &hs, &ms, &ss, ts_start, &he, &me, &se, ts_end,       // (1) 0.09877
/*20 */                        x1, x2, y1, y2);                                      // (6) 0.06996
/*22 */         buf += strcspn(buf, "\n") + 1;                                       // (9) 0.04527
/*24 */         if (c >= 8) {                                                        // (12) 0.02881
/*26 */             *ts_start = 100*(ss + 60*(ms + 60*hs)) + *ts_start/10;           // (5) 0.07819
/*28 */             *ts_end   = 100*(se + 60*(me + 60*he)) + *ts_end  /10;           // (4) 0.08436
/*30 */             return buf;                                                      // (13) 0.02881
/*32 */         }                                                                    // (14) 0.01646
/*34 */     }                                                                        // (16) 0.00823
/*36 */     return NULL;                                                             // (15) 0.01235
/*38 */ }                                                                            // (18) 0.002058
