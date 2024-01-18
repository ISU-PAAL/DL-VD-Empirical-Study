// commit message qemu@c5ce833344 (target=0, prob=0.09323331, correct=True): vnc: add configurable keyboard delay
/*0  */ static void press_key(VncState *vs, int keysym)                                    // (5) 0.09697
/*2  */ {                                                                                  // (6) 0.006061
/*4  */     int keycode = keysym2scancode(vs->vd->kbd_layout, keysym) & SCANCODE_KEYMASK;  // (0) 0.2121
/*6  */     qemu_input_event_send_key_number(vs->vd->dcl.con, keycode, true);              // (1) 0.1879
/*8  */     qemu_input_event_send_key_delay(0);                                            // (4) 0.1152
/*10 */     qemu_input_event_send_key_number(vs->vd->dcl.con, keycode, false);             // (2) 0.1879
/*12 */     qemu_input_event_send_key_delay(0);                                            // (3) 0.1152
/*14 */ }                                                                                  // (7) 0.006061
