// commit message FFmpeg@c97f54020d (target=0, prob=0.14460167, correct=True): Change SYS_DARWIN preprocessor checks to __APPLE__, they are specific to Mac OS X rather than to Darwin.
/*0  */ static int video_open(VideoState *is){                                 // (17) 0.02204
/*2  */     int flags = SDL_HWSURFACE|SDL_ASYNCBLIT|SDL_HWACCEL;               // (0) 0.05812
/*4  */     int w,h;                                                           // (24) 0.01603
/*8  */     if(is_full_screen) flags |= SDL_FULLSCREEN;                        // (4) 0.04409
/*10 */     else               flags |= SDL_RESIZABLE;                         // (2) 0.05411
/*14 */     if (is_full_screen && fs_screen_width) {                           // (10) 0.03607
/*16 */         w = fs_screen_width;                                           // (13) 0.03006
/*18 */         h = fs_screen_height;                                          // (14) 0.03006
/*20 */     } else if(!is_full_screen && screen_width){                        // (12) 0.03607
/*22 */         w = screen_width;                                              // (15) 0.02605
/*24 */         h = screen_height;                                             // (16) 0.02605
/*26 */     }else if (is->video_st && is->video_st->codec->width){             // (3) 0.0481
/*28 */         w = is->video_st->codec->width;                                // (7) 0.04008
/*30 */         h = is->video_st->codec->height;                               // (6) 0.04008
/*32 */     } else {                                                           // (27) 0.01202
/*34 */         w = 640;                                                       // (21) 0.02204
/*36 */         h = 480;                                                       // (22) 0.02204
/*38 */     }                                                                  // (29) 0.008016
/*40 */ #ifndef SYS_DARWIN                                                     // (23) 0.02004
/*42 */     screen = SDL_SetVideoMode(w, h, 0, flags);                         // (9) 0.03808
/*44 */ #else                                                                  // (31) 0.004008
/*46 */     /* setting bits_per_pixel = 0 or 32 causes blank video on OS X */  // (5) 0.04208
/*48 */     screen = SDL_SetVideoMode(w, h, 24, flags);                        // (8) 0.03808
/*50 */ #endif                                                                 // (30) 0.004008
/*52 */     if (!screen) {                                                     // (25) 0.01603
/*54 */         fprintf(stderr, "SDL: could not set video mode - exiting\n");  // (1) 0.05611
/*56 */         return -1;                                                     // (19) 0.02204
/*58 */     }                                                                  // (28) 0.008016
/*60 */     SDL_WM_SetCaption("FFplay", "FFplay");                             // (11) 0.03607
/*64 */     is->width = screen->w;                                             // (20) 0.02204
/*66 */     is->height = screen->h;                                            // (18) 0.02204
/*70 */     return 0;                                                          // (26) 0.01202
/*72 */ }                                                                      // (32) 0.002004
