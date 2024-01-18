// commit message FFmpeg@ba571f6b4d (target=0, prob=0.30381703, correct=True): ffplay: remove unnecessary if (cur_stream) checks
/*0   */ static void event_loop(VideoState *cur_stream)                                                                               // (0) 0.2599
/*2   */ {                                                                                                                            // (27) 0.003544
/*4   */     SDL_Event event;                                                                                                         // (7) 0.02304
/*6   */     double incr, pos, frac;                                                                                                  // (2) 0.1018
/*10  */     for(;;) {                                                                                                                // (11) 0.01709
/*12  */         double x;                                                                                                            // (1) 0.1747
/*14  */         SDL_WaitEvent(&event);                                                                                               // (3) 0.0283
/*16  */         switch(event.type) {                                                                                                 // (15) 0.01509
/*18  */         case SDL_KEYDOWN:                                                                                                    // (25) 0.01154
/*20  */             if (exit_on_keydown) {                                                                                           // (12) 0.0165
/*22  */                 do_exit(cur_stream);                                                                                         // (10) 0.01752
/*24  */                 break;                                                                                                       // (21) 0.01197
/*26  */             }                                                                                                                // (26) 0.008396
/*28  */             switch(event.key.keysym.sym) {                                                                                   // (6) 0.02338
/*30  */             case SDLK_ESCAPE:                                                                                                // (16) 0.01415
/*32  */             case SDLK_q:                                                                                                     // (20) 0.01221
/*34  */                 do_exit(cur_stream);                                                                                         // (9) 0.01796
/*36  */                 break;                                                                                                       // (22) 0.01177
/*38  */             case SDLK_f:                                                                                                     // (19) 0.01232
/*40  */                 toggle_full_screen(cur_stream);                                                                              // (8) 0.0214
/*42  */                 break;                                                                                                       // (24) 0.0117
/*44  */             case SDLK_p:                                                                                                     // (18) 0.0125
/*46  */             case SDLK_SPACE:                                                                                                 // (17) 0.01303
/*48  */                 if (cur_stream)                                                                                              // (13) 0.01539
/*50  */                     toggle_pause(cur_stream);                                                                                // (5) 0.02543
/*52  */                 break;                                                                                                       // (23) 0.01176
/*54  */             case SDLK_s: //S: Step to next frame                                                                             // (4) 0.02734
/*56  */                 if (cur_stream)                                                                                              // (14) 0.01532
/*58  */                     step_to_next_frame(cur_stream);                                                                          // 0.0
/*60  */                 break;                                                                                                       // 0.0
/*62  */             case SDLK_a:                                                                                                     // 0.0
/*64  */                 if (cur_stream)                                                                                              // 0.0
/*66  */                     stream_cycle_channel(cur_stream, AVMEDIA_TYPE_AUDIO);                                                    // 0.0
/*68  */                 break;                                                                                                       // 0.0
/*70  */             case SDLK_v:                                                                                                     // 0.0
/*72  */                 if (cur_stream)                                                                                              // 0.0
/*74  */                     stream_cycle_channel(cur_stream, AVMEDIA_TYPE_VIDEO);                                                    // 0.0
/*76  */                 break;                                                                                                       // 0.0
/*78  */             case SDLK_t:                                                                                                     // 0.0
/*80  */                 if (cur_stream)                                                                                              // 0.0
/*82  */                     stream_cycle_channel(cur_stream, AVMEDIA_TYPE_SUBTITLE);                                                 // 0.0
/*84  */                 break;                                                                                                       // 0.0
/*86  */             case SDLK_w:                                                                                                     // 0.0
/*88  */                 if (cur_stream)                                                                                              // 0.0
/*90  */                     toggle_audio_display(cur_stream);                                                                        // 0.0
/*92  */                 break;                                                                                                       // 0.0
/*94  */             case SDLK_LEFT:                                                                                                  // 0.0
/*96  */                 incr = -10.0;                                                                                                // 0.0
/*98  */                 goto do_seek;                                                                                                // 0.0
/*100 */             case SDLK_RIGHT:                                                                                                 // 0.0
/*102 */                 incr = 10.0;                                                                                                 // 0.0
/*104 */                 goto do_seek;                                                                                                // 0.0
/*106 */             case SDLK_UP:                                                                                                    // 0.0
/*108 */                 incr = 60.0;                                                                                                 // 0.0
/*110 */                 goto do_seek;                                                                                                // 0.0
/*112 */             case SDLK_DOWN:                                                                                                  // 0.0
/*114 */                 incr = -60.0;                                                                                                // 0.0
/*116 */             do_seek:                                                                                                         // 0.0
/*118 */                 if (cur_stream) {                                                                                            // 0.0
/*120 */                     if (seek_by_bytes) {                                                                                     // 0.0
/*122 */                         if (cur_stream->video_stream >= 0 && cur_stream->video_current_pos>=0){                              // 0.0
/*124 */                             pos= cur_stream->video_current_pos;                                                              // 0.0
/*126 */                         }else if(cur_stream->audio_stream >= 0 && cur_stream->audio_pkt.pos>=0){                             // 0.0
/*128 */                             pos= cur_stream->audio_pkt.pos;                                                                  // 0.0
/*130 */                         }else                                                                                                // 0.0
/*132 */                             pos = avio_tell(cur_stream->ic->pb);                                                             // 0.0
/*134 */                         if (cur_stream->ic->bit_rate)                                                                        // 0.0
/*136 */                             incr *= cur_stream->ic->bit_rate / 8.0;                                                          // 0.0
/*138 */                         else                                                                                                 // 0.0
/*140 */                             incr *= 180000.0;                                                                                // 0.0
/*142 */                         pos += incr;                                                                                         // 0.0
/*144 */                         stream_seek(cur_stream, pos, incr, 1);                                                               // 0.0
/*146 */                     } else {                                                                                                 // 0.0
/*148 */                         pos = get_master_clock(cur_stream);                                                                  // 0.0
/*150 */                         pos += incr;                                                                                         // 0.0
/*152 */                         stream_seek(cur_stream, (int64_t)(pos * AV_TIME_BASE), (int64_t)(incr * AV_TIME_BASE), 0);           // 0.0
/*154 */                     }                                                                                                        // 0.0
/*156 */                 }                                                                                                            // 0.0
/*158 */                 break;                                                                                                       // 0.0
/*160 */             default:                                                                                                         // 0.0
/*162 */                 break;                                                                                                       // 0.0
/*164 */             }                                                                                                                // 0.0
/*166 */             break;                                                                                                           // 0.0
/*168 */         case SDL_MOUSEBUTTONDOWN:                                                                                            // 0.0
/*170 */             if (exit_on_mousedown) {                                                                                         // 0.0
/*172 */                 do_exit(cur_stream);                                                                                         // 0.0
/*174 */                 break;                                                                                                       // 0.0
/*176 */             }                                                                                                                // 0.0
/*178 */         case SDL_MOUSEMOTION:                                                                                                // 0.0
/*180 */             if(event.type ==SDL_MOUSEBUTTONDOWN){                                                                            // 0.0
/*182 */                 x= event.button.x;                                                                                           // 0.0
/*184 */             }else{                                                                                                           // 0.0
/*186 */                 if(event.motion.state != SDL_PRESSED)                                                                        // 0.0
/*188 */                     break;                                                                                                   // 0.0
/*190 */                 x= event.motion.x;                                                                                           // 0.0
/*192 */             }                                                                                                                // 0.0
/*194 */             if (cur_stream) {                                                                                                // 0.0
/*196 */                 if(seek_by_bytes || cur_stream->ic->duration<=0){                                                            // 0.0
/*198 */                     uint64_t size=  avio_size(cur_stream->ic->pb);                                                           // 0.0
/*200 */                     stream_seek(cur_stream, size*x/cur_stream->width, 0, 1);                                                 // 0.0
/*202 */                 }else{                                                                                                       // 0.0
/*204 */                     int64_t ts;                                                                                              // 0.0
/*206 */                     int ns, hh, mm, ss;                                                                                      // 0.0
/*208 */                     int tns, thh, tmm, tss;                                                                                  // 0.0
/*210 */                     tns = cur_stream->ic->duration/1000000LL;                                                                // 0.0
/*212 */                     thh = tns/3600;                                                                                          // 0.0
/*214 */                     tmm = (tns%3600)/60;                                                                                     // 0.0
/*216 */                     tss = (tns%60);                                                                                          // 0.0
/*218 */                     frac = x/cur_stream->width;                                                                              // 0.0
/*220 */                     ns = frac*tns;                                                                                           // 0.0
/*222 */                     hh = ns/3600;                                                                                            // 0.0
/*224 */                     mm = (ns%3600)/60;                                                                                       // 0.0
/*226 */                     ss = (ns%60);                                                                                            // 0.0
/*228 */                     fprintf(stderr, "Seek to %2.0f%% (%2d:%02d:%02d) of total duration (%2d:%02d:%02d)       \n", frac*100,  // 0.0
/*230 */                             hh, mm, ss, thh, tmm, tss);                                                                      // 0.0
/*232 */                     ts = frac*cur_stream->ic->duration;                                                                      // 0.0
/*234 */                     if (cur_stream->ic->start_time != AV_NOPTS_VALUE)                                                        // 0.0
/*236 */                         ts += cur_stream->ic->start_time;                                                                    // 0.0
/*238 */                     stream_seek(cur_stream, ts, 0, 0);                                                                       // 0.0
/*240 */                 }                                                                                                            // 0.0
/*242 */             }                                                                                                                // 0.0
/*244 */             break;                                                                                                           // 0.0
/*246 */         case SDL_VIDEORESIZE:                                                                                                // 0.0
/*248 */             if (cur_stream) {                                                                                                // 0.0
/*250 */                 screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 0,                                                 // 0.0
/*252 */                                           SDL_HWSURFACE|SDL_RESIZABLE|SDL_ASYNCBLIT|SDL_HWACCEL);                            // 0.0
/*254 */                 screen_width = cur_stream->width = event.resize.w;                                                           // 0.0
/*256 */                 screen_height= cur_stream->height= event.resize.h;                                                           // 0.0
/*258 */             }                                                                                                                // 0.0
/*260 */             break;                                                                                                           // 0.0
/*262 */         case SDL_QUIT:                                                                                                       // 0.0
/*264 */         case FF_QUIT_EVENT:                                                                                                  // 0.0
/*266 */             do_exit(cur_stream);                                                                                             // 0.0
/*268 */             break;                                                                                                           // 0.0
/*270 */         case FF_ALLOC_EVENT:                                                                                                 // 0.0
/*272 */             video_open(event.user.data1);                                                                                    // 0.0
/*274 */             alloc_picture(event.user.data1);                                                                                 // 0.0
/*276 */             break;                                                                                                           // 0.0
/*278 */         case FF_REFRESH_EVENT:                                                                                               // 0.0
/*280 */             video_refresh(event.user.data1);                                                                                 // 0.0
/*282 */             cur_stream->refresh=0;                                                                                           // 0.0
/*284 */             break;                                                                                                           // 0.0
/*286 */         default:                                                                                                             // 0.0
/*288 */             break;                                                                                                           // 0.0
/*290 */         }                                                                                                                    // 0.0
/*292 */     }                                                                                                                        // 0.0
/*294 */ }                                                                                                                            // 0.0
