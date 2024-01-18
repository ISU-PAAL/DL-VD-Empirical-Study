// commit message FFmpeg@ce19aec15b (target=0, prob=0.12956914, correct=True): Check resync marker only when enabled.
/*0  */ const uint8_t *ff_h263_find_resync_marker(const uint8_t *av_restrict p, const uint8_t *av_restrict end)  // (0) 0.2216
/*2  */ {                                                                                                        // (11) 0.005155
/*4  */     av_assert2(p < end);                                                                                 // (5) 0.06186
/*8  */     end-=2;                                                                                              // (6) 0.04124
/*10 */     p++;                                                                                                 // (9) 0.02577
/*12 */     for(;p<end; p+=2){                                                                                   // (3) 0.07216
/*14 */         if(!*p){                                                                                         // (4) 0.06701
/*16 */             if     (!p[-1] && p[1]) return p - 1;                                                        // (1) 0.1649
/*18 */             else if(!p[ 1] && p[2]) return p;                                                            // (2) 0.1392
/*20 */         }                                                                                                // (7) 0.04124
/*22 */     }                                                                                                    // (10) 0.02062
/*24 */     return end+2;                                                                                        // (8) 0.04124
/*26 */ }                                                                                                        // (12) 0.005155
