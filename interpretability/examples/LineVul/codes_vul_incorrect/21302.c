// commit message FFmpeg@90c6963dae (target=1, prob=0.15821296, correct=False): avfilter picture pool: double free hotfix
/*0  */ void avfilter_link_free(AVFilterLink **link)                        // (11) 0.03553
/*2  */ {                                                                   // (20) 0.002538
/*4  */     if (!*link)                                                     // (17) 0.0203
/*6  */         return;                                                     // (16) 0.02284
/*10 */     if ((*link)->pool) {                                            // (12) 0.03046
/*12 */         int i;                                                      // (14) 0.02538
/*14 */         for (i = 0; i < POOL_SIZE; i++) {                           // (8) 0.05838
/*16 */             if ((*link)->pool->pic[i]) {                            // (6) 0.06091
/*18 */                 AVFilterBufferRef *picref = (*link)->pool->pic[i];  // (0) 0.08376
/*20 */                 /* free buffer: picrefs stored in the pool are not  // (2) 0.07107
/*22 */                  * supposed to contain a free callback */           // (7) 0.06091
/*24 */                 av_freep(&picref->buf->data[0]);                    // (1) 0.0736
/*26 */                 av_freep(&picref->buf);                             // (3) 0.06345
/*30 */                 av_freep(&picref->audio);                           // (4) 0.06345
/*32 */                 av_freep(&picref->video);                           // (5) 0.06345
/*34 */                 av_freep(&picref);                                  // (9) 0.05838
/*36 */             }                                                       // (13) 0.03046
/*38 */         }                                                           // (18) 0.0203
/*40 */         av_freep(&(*link)->pool);                                   // (10) 0.04569
/*42 */     }                                                               // (19) 0.01015
/*44 */     av_freep(link);                                                 // (15) 0.02538
/*46 */ }                                                                   // (21) 0.002538
