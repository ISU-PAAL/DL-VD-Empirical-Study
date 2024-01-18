// commit message FFmpeg@199d4478de (target=1, prob=0.48239028, correct=False): pthread: Change a signal to a broadcast as multiple threads have been seen waiting and deadlocking on it in bug125.
/*0   */ int ff_thread_get_buffer(AVCodecContext *avctx, AVFrame *f)                                             // (6) 0.04297
/*2   */ {                                                                                                       // (28) 0.001954
/*4   */     PerThreadContext *p = avctx->thread_opaque;                                                         // (11) 0.0332
/*6   */     int *progress, err;                                                                                 // (21) 0.01758
/*10  */     f->owner = avctx;                                                                                   // (20) 0.01953
/*14  */     ff_init_buffer_info(avctx, f);                                                                      // (14) 0.03125
/*18  */     if (!(avctx->active_thread_type&FF_THREAD_FRAME)) {                                                 // (5) 0.04687
/*20  */         f->thread_opaque = NULL;                                                                        // (15) 0.03125
/*22  */         return avctx->get_buffer(avctx, f);                                                             // (9) 0.03906
/*24  */     }                                                                                                   // (26) 0.007812
/*28  */     if (p->state != STATE_SETTING_UP &&                                                                 // (12) 0.03125
/*30  */         (avctx->codec->update_thread_context || (!avctx->thread_safe_callbacks &&                       // (2) 0.06055
/*32  */                 avctx->get_buffer != avcodec_default_get_buffer))) {                                    // (1) 0.06445
/*34  */         av_log(avctx, AV_LOG_ERROR, "get_buffer() cannot be called after ff_thread_finish_setup()\n");  // (0) 0.08008
/*36  */         return -1;                                                                                      // (18) 0.02148
/*38  */     }                                                                                                   // (25) 0.007812
/*42  */     pthread_mutex_lock(&p->parent->buffer_mutex);                                                       // (8) 0.03906
/*44  */     f->thread_opaque = progress = allocate_progress(p);                                                 // (10) 0.03516
/*48  */     if (!progress) {                                                                                    // (22) 0.01562
/*50  */         pthread_mutex_unlock(&p->parent->buffer_mutex);                                                 // (3) 0.04883
/*52  */         return -1;                                                                                      // (19) 0.02148
/*54  */     }                                                                                                   // (27) 0.007812
/*58  */     progress[0] =                                                                                       // (23) 0.01562
/*60  */     progress[1] = -1;                                                                                   // (17) 0.02148
/*64  */     if (avctx->thread_safe_callbacks ||                                                                 // (16) 0.0293
/*66  */         avctx->get_buffer == avcodec_default_get_buffer) {                                              // (4) 0.04883
/*68  */         err = avctx->get_buffer(avctx, f);                                                              // (7) 0.04102
/*70  */     } else {                                                                                            // (24) 0.01172
/*72  */         p->requested_frame = f;                                                                         // (13) 0.03125
/*74  */         p->state = STATE_GET_BUFFER;                                                                    // 0.0
/*76  */         pthread_mutex_lock(&p->progress_mutex);                                                         // 0.0
/*78  */         pthread_cond_signal(&p->progress_cond);                                                         // 0.0
/*82  */         while (p->state != STATE_SETTING_UP)                                                            // 0.0
/*84  */             pthread_cond_wait(&p->progress_cond, &p->progress_mutex);                                   // 0.0
/*88  */         err = p->result;                                                                                // 0.0
/*92  */         pthread_mutex_unlock(&p->progress_mutex);                                                       // 0.0
/*96  */         if (!avctx->codec->update_thread_context)                                                       // 0.0
/*98  */             ff_thread_finish_setup(avctx);                                                              // 0.0
/*100 */     }                                                                                                   // 0.0
/*104 */     pthread_mutex_unlock(&p->parent->buffer_mutex);                                                     // 0.0
/*108 */     return err;                                                                                         // 0.0
/*110 */ }                                                                                                       // 0.0
