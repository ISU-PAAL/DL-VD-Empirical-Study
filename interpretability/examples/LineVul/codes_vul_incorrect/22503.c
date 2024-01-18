// commit message FFmpeg@f6774f905f (target=1, prob=0.205058, correct=False): mpegvideo: operate with pointers to AVFrames instead of whole structs
/*0  */ void ff_thread_release_buffer(AVCodecContext *avctx, ThreadFrame *f)                 // (6) 0.04297
/*2  */ {                                                                                    // (25) 0.001954
/*4  */     PerThreadContext *p = avctx->internal->thread_ctx;                               // (9) 0.03515
/*6  */     FrameThreadContext *fctx;                                                        // (18) 0.01955
/*8  */     AVFrame *dst, *tmp;                                                              // (13) 0.02344
/*10 */ FF_DISABLE_DEPRECATION_WARNINGS                                                      // (17) 0.02148
/*12 */     int can_direct_free = !(avctx->active_thread_type & FF_THREAD_FRAME) ||          // (4) 0.05858
/*14 */                           avctx->thread_safe_callbacks                   ||          // (0) 0.1035
/*16 */                           (                                                          // (5) 0.05077
/*18 */ #if FF_API_GET_BUFFER                                                                // (19) 0.01953
/*20 */                            !avctx->get_buffer &&                                     // (3) 0.06639
/*22 */ #endif                                                                               // (24) 0.003906
/*24 */                            avctx->get_buffer2 == avcodec_default_get_buffer2);       // (1) 0.08789
/*26 */ FF_ENABLE_DEPRECATION_WARNINGS                                                       // (16) 0.02154
/*30 */     if (!f->f->buf[0])                                                               // (12) 0.02539
/*32 */         return;                                                                      // (21) 0.01757
/*36 */     if (avctx->debug & FF_DEBUG_BUFFERS)                                             // (8) 0.03515
/*38 */         av_log(avctx, AV_LOG_DEBUG, "thread_release_buffer called on pic %p\n", f);  // (2) 0.0703
/*42 */     av_buffer_unref(&f->progress);                                                   // (11) 0.02734
/*44 */     f->owner    = NULL;                                                              // (15) 0.02343
/*48 */     if (can_direct_free) {                                                           // (14) 0.02343
/*50 */         av_frame_unref(f->f);                                                        // (10) 0.03515
/*52 */         return;                                                                      // (22) 0.01757
/*54 */     }                                                                                // (23) 0.007811
/*58 */     fctx = p->parent;                                                                // (20) 0.01953
/*60 */     pthread_mutex_lock(&fctx->buffer_mutex);                                         // (7) 0.0371
/*64 */     if (p->num_released_buffers + 1 >= INT_MAX / sizeof(*p->released_buffers))       // 0.0
/*66 */         goto fail;                                                                   // 0.0
/*68 */     tmp = av_fast_realloc(p->released_buffers, &p->released_buffers_allocated,       // 0.0
/*70 */                           (p->num_released_buffers + 1) *                            // 0.0
/*72 */                           sizeof(*p->released_buffers));                             // 0.0
/*74 */     if (!tmp)                                                                        // 0.0
/*76 */         goto fail;                                                                   // 0.0
/*78 */     p->released_buffers = tmp;                                                       // 0.0
/*82 */     dst = &p->released_buffers[p->num_released_buffers];                             // 0.0
/*84 */     av_frame_move_ref(dst, f->f);                                                    // 0.0
/*88 */     p->num_released_buffers++;                                                       // 0.0
/*92 */ fail:                                                                                // 0.0
/*94 */     pthread_mutex_unlock(&fctx->buffer_mutex);                                       // 0.0
/*96 */ }                                                                                    // 0.0
