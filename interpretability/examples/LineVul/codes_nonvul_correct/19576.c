// commit message qemu@b6954712ab (target=0, prob=0.19959432, correct=True): replay: Use new QAPI cloning
/*0  */ void replay_input_event(QemuConsole *src, InputEvent *evt)   // (3) 0.1379
/*2  */ {                                                            // (8) 0.006897
/*4  */     if (replay_mode == REPLAY_MODE_PLAY) {                   // (4) 0.1241
/*6  */         /* Nothing */                                        // (5) 0.06897
/*8  */     } else if (replay_mode == REPLAY_MODE_RECORD) {          // (2) 0.1448
/*10 */         replay_add_input_event(qapi_clone_InputEvent(evt));  // (0) 0.1793
/*12 */     } else {                                                 // (6) 0.04138
/*14 */         qemu_input_event_send_impl(src, evt);                // (1) 0.1655
/*16 */     }                                                        // (7) 0.02759
/*18 */ }                                                            // (9) 0.006897
