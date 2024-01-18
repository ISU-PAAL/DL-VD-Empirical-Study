// commit message FFmpeg@3beb9cbad3 (target=0, prob=0.8204478, correct=False): roqvideo: check memory allocations and propagate errors
/*0  */ static void create_cel_evals(RoqContext *enc, RoqTempdata *tempData)                     // (4) 0.08915
/*2  */ {                                                                                        // (10) 0.003876
/*4  */     int n=0, x, y, i;                                                                    // (7) 0.05426
/*8  */     tempData->cel_evals = av_malloc(enc->width*enc->height/64 * sizeof(CelEvaluation));  // (2) 0.1318
/*12 */     /* Map to the ROQ quadtree order */                                                  // (8) 0.05039
/*14 */     for (y=0; y<enc->height; y+=16)                                                      // (6) 0.07364
/*16 */         for (x=0; x<enc->width; x+=16)                                                   // (5) 0.08915
/*18 */             for(i=0; i<4; i++) {                                                         // (3) 0.09302
/*20 */                 tempData->cel_evals[n  ].sourceX = x + (i&1)*8;                          // (0) 0.1473
/*22 */                 tempData->cel_evals[n++].sourceY = y + (i&2)*4;                          // (1) 0.1473
/*24 */             }                                                                            // (9) 0.04651
/*26 */ }                                                                                        // (11) 0.003876
