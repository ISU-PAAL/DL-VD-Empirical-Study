// commit message FFmpeg@20fe316e47 (target=1, prob=0.99903035, correct=True): lavd/sdl: reset context variables after destroy
/*0  */ static int sdl_write_trailer(AVFormatContext *s)  // (5) 0.06867
/*2  */ {                                                 // (14) 0.004292
/*4  */     SDLContext *sdl = s->priv_data;               // (6) 0.06438
/*8  */     sdl->quit = 1;                                // (12) 0.04292
/*12 */     if (sdl->overlay)                             // (10) 0.04721
/*14 */         SDL_FreeYUVOverlay(sdl->overlay);         // (0) 0.09013
/*17 */     if (sdl->event_thread)                        // (7) 0.0515
/*19 */         SDL_WaitThread(sdl->event_thread, NULL);  // (1) 0.09013
/*22 */     if (sdl->mutex)                               // (11) 0.04721
/*24 */         SDL_DestroyMutex(sdl->mutex);             // (2) 0.08155
/*27 */     if (sdl->init_cond)                           // (8) 0.0515
/*29 */         SDL_DestroyCond(sdl->init_cond);          // (3) 0.08155
/*34 */     if (!sdl->sdl_was_already_inited)             // (4) 0.08155
/*36 */         SDL_Quit();                               // (9) 0.0515
/*40 */     return 0;                                     // (13) 0.02575
/*42 */ }                                                 // (15) 0.004292
