// commit message qemu@bba4e1b591 (target=1, prob=0.22779989, correct=False): ui/curses.c: Ensure we don't read off the end of curses2qemu array
/*0   */ static void curses_refresh(DisplayChangeListener *dcl)                           // (14) 0.02734
/*2   */ {                                                                                // (34) 0.001953
/*4   */     int chr, nextchr, keysym, keycode, keycode_alt;                              // (1) 0.04297
/*8   */     curses_winch_check();                                                        // (22) 0.01953
/*12  */     if (invalidate) {                                                            // (24) 0.01953
/*14  */         clear();                                                                 // (26) 0.01758
/*16  */         refresh();                                                               // (25) 0.01758
/*18  */         curses_calc_pad();                                                       // (16) 0.02734
/*20  */         graphic_hw_invalidate(NULL);                                             // (9) 0.0332
/*22  */         invalidate = 0;                                                          // (21) 0.02344
/*24  */     }                                                                            // (32) 0.007812
/*28  */     graphic_hw_text_update(NULL, screen);                                        // (12) 0.0293
/*32  */     nextchr = ERR;                                                               // (23) 0.01953
/*34  */     while (1) {                                                                  // (28) 0.01563
/*36  */         /* while there are any pending key strokes to process */                 // (3) 0.03516
/*38  */         if (nextchr == ERR)                                                      // (11) 0.03125
/*40  */             chr = getch();                                                       // (10) 0.0332
/*42  */         else {                                                                   // (27) 0.01758
/*44  */             chr = nextchr;                                                       // (6) 0.03516
/*46  */             nextchr = ERR;                                                       // (7) 0.03516
/*48  */         }                                                                        // (30) 0.01563
/*52  */         if (chr == ERR)                                                          // (13) 0.0293
/*54  */             break;                                                               // (17) 0.02539
/*58  */ #ifdef KEY_RESIZE                                                                // (31) 0.01367
/*60  */         /* this shouldn't occur when we use a custom SIGWINCH handler */         // (2) 0.04297
/*62  */         if (chr == KEY_RESIZE) {                                                 // (8) 0.03516
/*64  */             clear();                                                             // (20) 0.02539
/*66  */             refresh();                                                           // (19) 0.02539
/*68  */             curses_calc_pad();                                                   // (5) 0.03516
/*70  */             curses_update(dcl, 0, 0, width, height);                             // (0) 0.05078
/*72  */             continue;                                                            // (18) 0.02539
/*74  */         }                                                                        // (29) 0.01563
/*76  */ #endif                                                                           // (33) 0.003906
/*80  */         keycode = curses2keycode[chr];                                           // (4) 0.03516
/*82  */         keycode_alt = 0;                                                         // (15) 0.02734
/*86  */         /* alt key */                                                            // 0.0
/*88  */         if (keycode == 1) {                                                      // 0.0
/*90  */             nextchr = getch();                                                   // 0.0
/*94  */             if (nextchr != ERR) {                                                // 0.0
/*96  */                 chr = nextchr;                                                   // 0.0
/*98  */                 keycode_alt = ALT;                                               // 0.0
/*100 */                 keycode = curses2keycode[nextchr];                               // 0.0
/*102 */                 nextchr = ERR;                                                   // 0.0
/*106 */                 if (keycode != -1) {                                             // 0.0
/*108 */                     keycode |= ALT;                                              // 0.0
/*112 */                     /* process keys reserved for qemu */                         // 0.0
/*114 */                     if (keycode >= QEMU_KEY_CONSOLE0 &&                          // 0.0
/*116 */                             keycode < QEMU_KEY_CONSOLE0 + 9) {                   // 0.0
/*118 */                         erase();                                                 // 0.0
/*120 */                         wnoutrefresh(stdscr);                                    // 0.0
/*122 */                         console_select(keycode - QEMU_KEY_CONSOLE0);             // 0.0
/*126 */                         invalidate = 1;                                          // 0.0
/*128 */                         continue;                                                // 0.0
/*130 */                     }                                                            // 0.0
/*132 */                 }                                                                // 0.0
/*134 */             }                                                                    // 0.0
/*136 */         }                                                                        // 0.0
/*140 */         if (kbd_layout) {                                                        // 0.0
/*142 */             keysym = -1;                                                         // 0.0
/*144 */             if (chr < CURSES_KEYS)                                               // 0.0
/*146 */                 keysym = curses2keysym[chr];                                     // 0.0
/*150 */             if (keysym == -1) {                                                  // 0.0
/*152 */                 if (chr < ' ') {                                                 // 0.0
/*154 */                     keysym = chr + '@';                                          // 0.0
/*156 */                     if (keysym >= 'A' && keysym <= 'Z')                          // 0.0
/*158 */                         keysym += 'a' - 'A';                                     // 0.0
/*160 */                     keysym |= KEYSYM_CNTRL;                                      // 0.0
/*162 */                 } else                                                           // 0.0
/*164 */                     keysym = chr;                                                // 0.0
/*166 */             }                                                                    // 0.0
/*170 */             keycode = keysym2scancode(kbd_layout, keysym & KEYSYM_MASK);         // 0.0
/*172 */             if (keycode == 0)                                                    // 0.0
/*174 */                 continue;                                                        // 0.0
/*178 */             keycode |= (keysym & ~KEYSYM_MASK) >> 16;                            // 0.0
/*180 */             keycode |= keycode_alt;                                              // 0.0
/*182 */         }                                                                        // 0.0
/*186 */         if (keycode == -1)                                                       // 0.0
/*188 */             continue;                                                            // 0.0
/*192 */         if (qemu_console_is_graphic(NULL)) {                                     // 0.0
/*194 */             /* since terminals don't know about key press and release            // 0.0
/*196 */              * events, we need to emit both for each key received */             // 0.0
/*198 */             if (keycode & SHIFT) {                                               // 0.0
/*200 */                 qemu_input_event_send_key_number(NULL, SHIFT_CODE, true);        // 0.0
/*202 */                 qemu_input_event_send_key_delay(0);                              // 0.0
/*204 */             }                                                                    // 0.0
/*206 */             if (keycode & CNTRL) {                                               // 0.0
/*208 */                 qemu_input_event_send_key_number(NULL, CNTRL_CODE, true);        // 0.0
/*210 */                 qemu_input_event_send_key_delay(0);                              // 0.0
/*212 */             }                                                                    // 0.0
/*214 */             if (keycode & ALT) {                                                 // 0.0
/*216 */                 qemu_input_event_send_key_number(NULL, ALT_CODE, true);          // 0.0
/*218 */                 qemu_input_event_send_key_delay(0);                              // 0.0
/*220 */             }                                                                    // 0.0
/*222 */             if (keycode & ALTGR) {                                               // 0.0
/*224 */                 qemu_input_event_send_key_number(NULL, GREY | ALT_CODE, true);   // 0.0
/*226 */                 qemu_input_event_send_key_delay(0);                              // 0.0
/*228 */             }                                                                    // 0.0
/*232 */             qemu_input_event_send_key_number(NULL, keycode & KEY_MASK, true);    // 0.0
/*234 */             qemu_input_event_send_key_delay(0);                                  // 0.0
/*236 */             qemu_input_event_send_key_number(NULL, keycode & KEY_MASK, false);   // 0.0
/*238 */             qemu_input_event_send_key_delay(0);                                  // 0.0
/*242 */             if (keycode & ALTGR) {                                               // 0.0
/*244 */                 qemu_input_event_send_key_number(NULL, GREY | ALT_CODE, false);  // 0.0
/*246 */                 qemu_input_event_send_key_delay(0);                              // 0.0
/*248 */             }                                                                    // 0.0
/*250 */             if (keycode & ALT) {                                                 // 0.0
/*252 */                 qemu_input_event_send_key_number(NULL, ALT_CODE, false);         // 0.0
/*254 */                 qemu_input_event_send_key_delay(0);                              // 0.0
/*256 */             }                                                                    // 0.0
/*258 */             if (keycode & CNTRL) {                                               // 0.0
/*260 */                 qemu_input_event_send_key_number(NULL, CNTRL_CODE, false);       // 0.0
/*262 */                 qemu_input_event_send_key_delay(0);                              // 0.0
/*264 */             }                                                                    // 0.0
/*266 */             if (keycode & SHIFT) {                                               // 0.0
/*268 */                 qemu_input_event_send_key_number(NULL, SHIFT_CODE, false);       // 0.0
/*270 */                 qemu_input_event_send_key_delay(0);                              // 0.0
/*272 */             }                                                                    // 0.0
/*274 */         } else {                                                                 // 0.0
/*276 */             keysym = curses2qemu[chr];                                           // 0.0
/*278 */             if (keysym == -1)                                                    // 0.0
/*280 */                 keysym = chr;                                                    // 0.0
/*284 */             kbd_put_keysym(keysym);                                              // 0.0
/*286 */         }                                                                        // 0.0
/*288 */     }                                                                            // 0.0
/*290 */ }                                                                                // 0.0
