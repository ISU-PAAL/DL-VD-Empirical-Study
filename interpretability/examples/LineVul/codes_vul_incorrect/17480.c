// commit message FFmpeg@4d321bff85 (target=1, prob=0.32016814, correct=False): fix imlib2 memory leaks patch by Limin Wang: [lance lmwang gmail com] original thread: [FFmpeg-devel] [PATCH] fix imlib2 memory leaks date: 06/18/2007 04:22 AM
/*0  */ void Release(void *ctx)                                  // (19) 0.01944
/*2  */ {                                                        // (22) 0.002778
/*4  */     ContextInfo *ci;                                     // (16) 0.02222
/*6  */     ci = (ContextInfo *) ctx;                            // (13) 0.03611
/*10 */     if (ci->cache) {                                     // (15) 0.02778
/*12 */         imlib_context_set_image(ci->cache->image);       // (3) 0.06111
/*14 */         imlib_free_image();                              // (12) 0.03889
/*16 */         av_free(ci->cache);                              // (11) 0.04167
/*18 */     }                                                    // (20) 0.01111
/*20 */     if (ctx) {                                           // (17) 0.02222
/*22 */         if (ci->imageOverlaid) {                         // (10) 0.04722
/*24 */             imlib_context_set_image(ci->imageOverlaid);  // (0) 0.075
/*26 */             imlib_free_image();                          // (9) 0.05
/*28 */         }                                                // (18) 0.02222
/*30 */         ff_eval_free(ci->expr_x);                        // (4) 0.05278
/*32 */         ff_eval_free(ci->expr_y);                        // (5) 0.05278
/*34 */         ff_eval_free(ci->expr_R);                        // (6) 0.05278
/*36 */         ff_eval_free(ci->expr_G);                        // (7) 0.05278
/*38 */         ff_eval_free(ci->expr_B);                        // (8) 0.05278
/*40 */         sws_freeContext(ci->toRGB_convert_ctx);          // (1) 0.06389
/*42 */         sws_freeContext(ci->fromRGB_convert_ctx);        // (2) 0.06389
/*44 */         av_free(ctx);                                    // (14) 0.03611
/*46 */     }                                                    // (21) 0.01111
/*48 */ }                                                        // (23) 0.002778
