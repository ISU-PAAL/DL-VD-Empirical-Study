// commit message FFmpeg@daa7a1d443 (target=0, prob=0.70738715, correct=False): pthread_slice: rename ThreadContext -> SliceThreadContext
/*0  */ void ff_slice_thread_free(AVCodecContext *avctx)   // (8) 0.06693
/*2  */ {                                                  // (14) 0.003937
/*4  */     ThreadContext *c = avctx->thread_opaque;       // (9) 0.06299
/*6  */     int i;                                         // (13) 0.02362
/*10 */     pthread_mutex_lock(&c->current_job_lock);      // (3) 0.0748
/*12 */     c->done = 1;                                   // (12) 0.03543
/*14 */     pthread_cond_broadcast(&c->current_job_cond);  // (4) 0.0748
/*16 */     pthread_mutex_unlock(&c->current_job_lock);    // (1) 0.07874
/*20 */     for (i=0; i<avctx->thread_count; i++)          // (2) 0.07874
/*22 */          pthread_join(c->workers[i], NULL);        // (0) 0.08268
/*26 */     pthread_mutex_destroy(&c->current_job_lock);   // (5) 0.0748
/*28 */     pthread_cond_destroy(&c->current_job_cond);    // (6) 0.07087
/*30 */     pthread_cond_destroy(&c->last_job_cond);       // (7) 0.07087
/*32 */     av_free(c->workers);                           // (11) 0.04331
/*34 */     av_freep(&avctx->thread_opaque);               // (10) 0.06299
/*36 */ }                                                  // (15) 0.003937
