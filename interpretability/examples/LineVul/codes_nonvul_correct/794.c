// commit message qemu@d20a580bc0 (target=0, prob=0.2567375, correct=True): qapi: Change munging of CamelCase enum values
/*0  */ static void sdl_send_mouse_event(int dx, int dy, int x, int y, int state)  // (10) 0.05078
/*2  */ {                                                                          // (20) 0.001953
/*4  */     static uint32_t bmap[INPUT_BUTTON__MAX] = {                            // (11) 0.04102
/*6  */         [INPUT_BUTTON_LEFT]       = SDL_BUTTON(SDL_BUTTON_LEFT),           // (2) 0.07422
/*8  */         [INPUT_BUTTON_MIDDLE]     = SDL_BUTTON(SDL_BUTTON_MIDDLE),         // (0) 0.07812
/*10 */         [INPUT_BUTTON_RIGHT]      = SDL_BUTTON(SDL_BUTTON_RIGHT),          // (3) 0.07227
/*12 */         [INPUT_BUTTON_WHEEL_UP]   = SDL_BUTTON(SDL_BUTTON_WHEELUP),        // (1) 0.07617
/*14 */         [INPUT_BUTTON_WHEEL_DOWN] = SDL_BUTTON(SDL_BUTTON_WHEELDOWN),      // (4) 0.07227
/*16 */     };                                                                     // (19) 0.007812
/*18 */     static uint32_t prev_state;                                            // (16) 0.02344
/*22 */     if (prev_state != state) {                                             // (15) 0.02344
/*24 */         qemu_input_update_buttons(dcl->con, bmap, prev_state, state);      // (7) 0.0625
/*26 */         prev_state = state;                                                // (14) 0.02539
/*28 */     }                                                                      // (18) 0.007813
/*32 */     if (qemu_input_is_absolute()) {                                        // (13) 0.03125
/*34 */         qemu_input_queue_abs(dcl->con, INPUT_AXIS_X, x,                    // (9) 0.0625
/*36 */                              real_screen->w);                              // (5) 0.06641
/*38 */         qemu_input_queue_abs(dcl->con, INPUT_AXIS_Y, y,                    // (8) 0.0625
/*40 */                              real_screen->h);                              // (6) 0.06641
/*42 */     } else {                                                               // (17) 0.01172
/*44 */         if (guest_cursor) {                                                // (12) 0.03125
/*46 */             x -= guest_x;                                                  // 0.0
/*48 */             y -= guest_y;                                                  // 0.0
/*50 */             guest_x += x;                                                  // 0.0
/*52 */             guest_y += y;                                                  // 0.0
/*54 */             dx = x;                                                        // 0.0
/*56 */             dy = y;                                                        // 0.0
/*58 */         }                                                                  // 0.0
/*60 */         qemu_input_queue_rel(dcl->con, INPUT_AXIS_X, dx);                  // 0.0
/*62 */         qemu_input_queue_rel(dcl->con, INPUT_AXIS_Y, dy);                  // 0.0
/*64 */     }                                                                      // 0.0
/*66 */     qemu_input_event_sync();                                               // 0.0
/*68 */ }                                                                          // 0.0
