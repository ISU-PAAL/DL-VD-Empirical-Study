// commit message qemu@d20a580bc0 (target=0, prob=0.019739803, correct=True): qapi: Change munging of CamelCase enum values
/*0  */ static void handle_mousewheel(SDL_Event *ev)                             // (7) 0.05344
/*2  */ {                                                                        // (15) 0.003817
/*4  */     struct sdl2_console *scon = get_scon_from_window(ev->key.windowID);  // (0) 0.1107
/*6  */     SDL_MouseWheelEvent *wev = &ev->wheel;                               // (5) 0.06489
/*8  */     InputButton btn;                                                     // (12) 0.03053
/*12 */     if (wev->y > 0) {                                                    // (8) 0.04962
/*14 */         btn = INPUT_BUTTON_WHEEL_UP;                                     // (3) 0.08397
/*16 */     } else if (wev->y < 0) {                                             // (6) 0.05725
/*18 */         btn = INPUT_BUTTON_WHEEL_DOWN;                                   // (4) 0.08397
/*20 */     } else {                                                             // (13) 0.0229
/*22 */         return;                                                          // (11) 0.03435
/*24 */     }                                                                    // (14) 0.01527
/*28 */     qemu_input_queue_btn(scon->dcl.con, btn, true);                      // (1) 0.09924
/*30 */     qemu_input_event_sync();                                             // (9) 0.04962
/*32 */     qemu_input_queue_btn(scon->dcl.con, btn, false);                     // (2) 0.09924
/*34 */     qemu_input_event_sync();                                             // (10) 0.04962
/*36 */ }                                                                        // (16) 0.003817
