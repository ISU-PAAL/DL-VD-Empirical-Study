// commit message FFmpeg@b853cfe7ea (target=0, prob=0.4331391, correct=True): ffplay: remove refresh thread to achieve more precise frame delay
/*0  */ static void stream_close(VideoState *is)                               // (19) 0.02444
/*2  */ {                                                                      // (30) 0.002222
/*4  */     VideoPicture *vp;                                                  // (22) 0.01778
/*6  */     int i;                                                             // (26) 0.01333
/*8  */     /* XXX: use a special url_shutdown call to abort parse cleanly */  // (3) 0.04444
/*10 */     is->abort_request = 1;                                             // (18) 0.02667
/*12 */     SDL_WaitThread(is->read_tid, NULL);                                // (9) 0.03778
/*14 */     SDL_WaitThread(is->refresh_tid, NULL);                             // (5) 0.04
/*16 */     packet_queue_destroy(&is->videoq);                                 // (16) 0.03111
/*18 */     packet_queue_destroy(&is->audioq);                                 // (17) 0.03111
/*20 */     packet_queue_destroy(&is->subtitleq);                              // (13) 0.03333
/*24 */     /* free all pictures */                                            // (23) 0.01778
/*26 */     for (i = 0; i < VIDEO_PICTURE_QUEUE_SIZE; i++) {                   // (0) 0.05778
/*28 */         vp = &is->pictq[i];                                            // (6) 0.04
/*30 */ #if CONFIG_AVFILTER                                                    // (25) 0.01556
/*32 */         avfilter_unref_bufferp(&vp->picref);                           // (2) 0.04667
/*34 */ #endif                                                                 // (29) 0.004444
/*36 */         if (vp->bmp) {                                                 // (14) 0.03333
/*38 */             SDL_FreeYUVOverlay(vp->bmp);                               // (1) 0.05333
/*40 */             vp->bmp = NULL;                                            // (4) 0.04222
/*42 */         }                                                              // (24) 0.01778
/*44 */     }                                                                  // (27) 0.008889
/*46 */     SDL_DestroyMutex(is->pictq_mutex);                                 // (10) 0.03778
/*48 */     SDL_DestroyCond(is->pictq_cond);                                   // (15) 0.03333
/*50 */     SDL_DestroyMutex(is->subpq_mutex);                                 // (7) 0.04
/*52 */     SDL_DestroyCond(is->subpq_cond);                                   // (11) 0.03556
/*54 */     SDL_DestroyCond(is->continue_read_thread);                         // (12) 0.03556
/*56 */ #if !CONFIG_AVFILTER                                                   // (20) 0.02
/*58 */     sws_freeContext(is->img_convert_ctx);                              // (8) 0.04
/*60 */ #endif                                                                 // (28) 0.004444
/*62 */     av_free(is);                                                       // (21) 0.02
/*64 */ }                                                                      // (31) 0.002222
