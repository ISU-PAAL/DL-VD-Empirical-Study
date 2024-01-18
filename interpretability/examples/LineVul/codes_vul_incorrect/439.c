// commit message FFmpeg@72555f4a38 (target=1, prob=0.2613823, correct=False): avcodec/pthread_slice: Check for malloc failure
/*0  */ int ff_alloc_entries(AVCodecContext *avctx, int count)                                  // (10) 0.04884
/*2  */ {                                                                                       // (18) 0.002571
/*4  */     int i;                                                                              // (15) 0.01542
/*8  */     if (avctx->active_thread_type & FF_THREAD_SLICE)  {                                 // (5) 0.0617
/*10 */         SliceThreadContext *p = avctx->internal->thread_ctx;                            // (7) 0.05913
/*12 */         p->thread_count  = avctx->thread_count;                                         // (8) 0.05398
/*14 */         p->entries       = av_mallocz_array(count, sizeof(int));                        // (2) 0.08226
/*18 */         if (!p->entries) {                                                              // (12) 0.03856
/*20 */             return AVERROR(ENOMEM);                                                     // (9) 0.05141
/*22 */         }                                                                               // (13) 0.02057
/*26 */         p->entries_count  = count;                                                      // (11) 0.0437
/*28 */         p->progress_mutex = av_malloc_array(p->thread_count, sizeof(pthread_mutex_t));  // (0) 0.09512
/*30 */         p->progress_cond  = av_malloc_array(p->thread_count, sizeof(pthread_cond_t));   // (1) 0.09254
/*34 */         for (i = 0; i < p->thread_count; i++) {                                         // (6) 0.0617
/*36 */             pthread_mutex_init(&p->progress_mutex[i], NULL);                            // (3) 0.07712
/*38 */             pthread_cond_init(&p->progress_cond[i], NULL);                              // (4) 0.07198
/*40 */         }                                                                               // (14) 0.02057
/*42 */     }                                                                                   // (17) 0.01028
/*46 */     return 0;                                                                           // (16) 0.01542
/*48 */ }                                                                                       // (19) 0.002571
