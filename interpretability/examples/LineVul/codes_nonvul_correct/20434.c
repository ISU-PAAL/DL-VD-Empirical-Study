// commit message qemu@2884cf5b93 (target=0, prob=0.062056087, correct=True): gtk: fix grab checks
/*0  */ static gboolean gd_button_event(GtkWidget *widget, GdkEventButton *button,   // (6) 0.04888
/*2  */                                 void *opaque)                                // (2) 0.07332
/*4  */ {                                                                            // (25) 0.002037
/*6  */     VirtualConsole *vc = opaque;                                             // (17) 0.02037
/*8  */     GtkDisplayState *s = vc->s;                                              // (12) 0.03055
/*10 */     InputButton btn;                                                         // (20) 0.01629
/*14 */     /* implicitly grab the input at the first click in the relative mode */  // (11) 0.03462
/*16 */     if (button->button == 1 && button->type == GDK_BUTTON_PRESS &&           // (7) 0.04684
/*18 */         !qemu_input_is_absolute() && !gd_is_grab_active(s)) {                // (4) 0.06314
/*20 */         gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(s->grab_item),    // (1) 0.07536
/*22 */                                        TRUE);                                // (0) 0.08147
/*24 */         return TRUE;                                                         // (18) 0.02037
/*26 */     }                                                                        // (23) 0.008147
/*30 */     if (button->button == 1) {                                               // (16) 0.02444
/*32 */         btn = INPUT_BUTTON_LEFT;                                             // (9) 0.0387
/*34 */     } else if (button->button == 2) {                                        // (13) 0.02851
/*36 */         btn = INPUT_BUTTON_MIDDLE;                                           // (8) 0.04277
/*38 */     } else if (button->button == 3) {                                        // (14) 0.02851
/*40 */         btn = INPUT_BUTTON_RIGHT;                                            // (10) 0.0387
/*42 */     } else {                                                                 // (21) 0.01222
/*44 */         return TRUE;                                                         // (19) 0.02037
/*46 */     }                                                                        // (24) 0.008147
/*50 */     qemu_input_queue_btn(vc->gfx.dcl.con, btn,                               // (5) 0.05295
/*52 */                          button->type == GDK_BUTTON_PRESS);                  // (3) 0.07332
/*54 */     qemu_input_event_sync();                                                 // (15) 0.02648
/*56 */     return TRUE;                                                             // (22) 0.01222
/*58 */ }                                                                            // (26) 0.002037
