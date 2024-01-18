// commit message qemu@c6bf0f7ffa (target=0, prob=0.48586702, correct=True): vl: Use error_report() for --display errors
/*0   */ static DisplayType select_display(const char *p)                                 // (18) 0.02344
/*2   */ {                                                                                // (23) 0.001954
/*4   */     Error *err = NULL;                                                           // (20) 0.01762
/*6   */     const char *opts;                                                            // (21) 0.01758
/*8   */     DisplayType display = DT_DEFAULT;                                            // (19) 0.02344
/*12  */     if (strstart(p, "sdl", &opts)) {                                             // (12) 0.03711
/*14  */ #ifdef CONFIG_SDL                                                                // (22) 0.01367
/*16  */         display = DT_SDL;                                                        // (16) 0.02734
/*18  */         while (*opts) {                                                          // (17) 0.02539
/*20  */             const char *nextopt;                                                 // (14) 0.0332
/*24  */             if (strstart(opts, ",frame=", &nextopt)) {                           // (5) 0.05468
/*26  */                 opts = nextopt;                                                  // (10) 0.04101
/*28  */                 if (strstart(opts, "on", &nextopt)) {                            // (4) 0.06054
/*30  */                     no_frame = 0;                                                // (7) 0.04883
/*32  */                 } else if (strstart(opts, "off", &nextopt)) {                    // (0) 0.06445
/*34  */                     no_frame = 1;                                                // (9) 0.04882
/*36  */                 } else {                                                         // (13) 0.03515
/*38  */                     goto invalid_sdl_args;                                       // (6) 0.05274
/*40  */                 }                                                                // (15) 0.03125
/*42  */             } else if (strstart(opts, ",alt_grab=", &nextopt)) {                 // (2) 0.0625
/*44  */                 opts = nextopt;                                                  // (11) 0.04101
/*46  */                 if (strstart(opts, "on", &nextopt)) {                            // (3) 0.06054
/*48  */                     alt_grab = 1;                                                // (8) 0.04882
/*50  */                 } else if (strstart(opts, "off", &nextopt)) {                    // (1) 0.06445
/*52  */                     alt_grab = 0;                                                // 0.0
/*54  */                 } else {                                                         // 0.0
/*56  */                     goto invalid_sdl_args;                                       // 0.0
/*58  */                 }                                                                // 0.0
/*60  */             } else if (strstart(opts, ",ctrl_grab=", &nextopt)) {                // 0.0
/*62  */                 opts = nextopt;                                                  // 0.0
/*64  */                 if (strstart(opts, "on", &nextopt)) {                            // 0.0
/*66  */                     ctrl_grab = 1;                                               // 0.0
/*68  */                 } else if (strstart(opts, "off", &nextopt)) {                    // 0.0
/*70  */                     ctrl_grab = 0;                                               // 0.0
/*72  */                 } else {                                                         // 0.0
/*74  */                     goto invalid_sdl_args;                                       // 0.0
/*76  */                 }                                                                // 0.0
/*78  */             } else if (strstart(opts, ",window_close=", &nextopt)) {             // 0.0
/*80  */                 opts = nextopt;                                                  // 0.0
/*82  */                 if (strstart(opts, "on", &nextopt)) {                            // 0.0
/*84  */                     no_quit = 0;                                                 // 0.0
/*86  */                 } else if (strstart(opts, "off", &nextopt)) {                    // 0.0
/*88  */                     no_quit = 1;                                                 // 0.0
/*90  */                 } else {                                                         // 0.0
/*92  */                     goto invalid_sdl_args;                                       // 0.0
/*94  */                 }                                                                // 0.0
/*96  */             } else if (strstart(opts, ",gl=", &nextopt)) {                       // 0.0
/*98  */                 opts = nextopt;                                                  // 0.0
/*100 */                 if (strstart(opts, "on", &nextopt)) {                            // 0.0
/*102 */                     request_opengl = 1;                                          // 0.0
/*104 */                 } else if (strstart(opts, "off", &nextopt)) {                    // 0.0
/*106 */                     request_opengl = 0;                                          // 0.0
/*108 */                 } else {                                                         // 0.0
/*110 */                     goto invalid_sdl_args;                                       // 0.0
/*112 */                 }                                                                // 0.0
/*114 */             } else {                                                             // 0.0
/*116 */             invalid_sdl_args:                                                    // 0.0
/*118 */                 fprintf(stderr, "Invalid SDL option string: %s\n", p);           // 0.0
/*120 */                 exit(1);                                                         // 0.0
/*122 */             }                                                                    // 0.0
/*124 */             opts = nextopt;                                                      // 0.0
/*126 */         }                                                                        // 0.0
/*128 */ #else                                                                            // 0.0
/*130 */         fprintf(stderr, "SDL support is disabled\n");                            // 0.0
/*132 */         exit(1);                                                                 // 0.0
/*134 */ #endif                                                                           // 0.0
/*136 */     } else if (strstart(p, "vnc", &opts)) {                                      // 0.0
/*138 */ #ifdef CONFIG_VNC                                                                // 0.0
/*140 */         if (*opts == '=') {                                                      // 0.0
/*142 */             if (vnc_parse(opts + 1, &err) == NULL) {                             // 0.0
/*144 */                 error_report_err(err);                                           // 0.0
/*146 */                 exit(1);                                                         // 0.0
/*148 */             }                                                                    // 0.0
/*150 */         } else {                                                                 // 0.0
/*152 */             fprintf(stderr, "VNC requires a display argument vnc=<display>\n");  // 0.0
/*154 */             exit(1);                                                             // 0.0
/*156 */         }                                                                        // 0.0
/*158 */ #else                                                                            // 0.0
/*160 */         fprintf(stderr, "VNC support is disabled\n");                            // 0.0
/*162 */         exit(1);                                                                 // 0.0
/*164 */ #endif                                                                           // 0.0
/*166 */     } else if (strstart(p, "curses", &opts)) {                                   // 0.0
/*168 */ #ifdef CONFIG_CURSES                                                             // 0.0
/*170 */         display = DT_CURSES;                                                     // 0.0
/*172 */ #else                                                                            // 0.0
/*174 */         fprintf(stderr, "Curses support is disabled\n");                         // 0.0
/*176 */         exit(1);                                                                 // 0.0
/*178 */ #endif                                                                           // 0.0
/*180 */     } else if (strstart(p, "gtk", &opts)) {                                      // 0.0
/*182 */ #ifdef CONFIG_GTK                                                                // 0.0
/*184 */         display = DT_GTK;                                                        // 0.0
/*186 */         while (*opts) {                                                          // 0.0
/*188 */             const char *nextopt;                                                 // 0.0
/*192 */             if (strstart(opts, ",grab_on_hover=", &nextopt)) {                   // 0.0
/*194 */                 opts = nextopt;                                                  // 0.0
/*196 */                 if (strstart(opts, "on", &nextopt)) {                            // 0.0
/*198 */                     grab_on_hover = true;                                        // 0.0
/*200 */                 } else if (strstart(opts, "off", &nextopt)) {                    // 0.0
/*202 */                     grab_on_hover = false;                                       // 0.0
/*204 */                 } else {                                                         // 0.0
/*206 */                     goto invalid_gtk_args;                                       // 0.0
/*208 */                 }                                                                // 0.0
/*210 */             } else if (strstart(opts, ",gl=", &nextopt)) {                       // 0.0
/*212 */                 opts = nextopt;                                                  // 0.0
/*214 */                 if (strstart(opts, "on", &nextopt)) {                            // 0.0
/*216 */                     request_opengl = 1;                                          // 0.0
/*218 */                 } else if (strstart(opts, "off", &nextopt)) {                    // 0.0
/*220 */                     request_opengl = 0;                                          // 0.0
/*222 */                 } else {                                                         // 0.0
/*224 */                     goto invalid_gtk_args;                                       // 0.0
/*226 */                 }                                                                // 0.0
/*228 */             } else {                                                             // 0.0
/*230 */             invalid_gtk_args:                                                    // 0.0
/*232 */                 fprintf(stderr, "Invalid GTK option string: %s\n", p);           // 0.0
/*234 */                 exit(1);                                                         // 0.0
/*236 */             }                                                                    // 0.0
/*238 */             opts = nextopt;                                                      // 0.0
/*240 */         }                                                                        // 0.0
/*242 */ #else                                                                            // 0.0
/*244 */         fprintf(stderr, "GTK support is disabled\n");                            // 0.0
/*246 */         exit(1);                                                                 // 0.0
/*248 */ #endif                                                                           // 0.0
/*250 */     } else if (strstart(p, "none", &opts)) {                                     // 0.0
/*252 */         display = DT_NONE;                                                       // 0.0
/*254 */     } else {                                                                     // 0.0
/*256 */         fprintf(stderr, "Unknown display type: %s\n", p);                        // 0.0
/*258 */         exit(1);                                                                 // 0.0
/*260 */     }                                                                            // 0.0
/*264 */     return display;                                                              // 0.0
/*266 */ }                                                                                // 0.0
