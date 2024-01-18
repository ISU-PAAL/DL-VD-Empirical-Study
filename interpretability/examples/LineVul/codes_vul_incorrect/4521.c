// commit message qemu@e61031cdd8 (target=1, prob=0.18429233, correct=False): gtk: Fix the relative pointer tracking mode
/*0   */ static gboolean gd_motion_event(GtkWidget *widget, GdkEventMotion *motion,    // (4) 0.04688
/*2   */                                 void *opaque)                                 // (0) 0.07031
/*4   */ {                                                                             // (27) 0.001953
/*6   */     GtkDisplayState *s = opaque;                                              // (15) 0.02344
/*8   */     int x, y;                                                                 // (23) 0.01562
/*10  */     int mx, my;                                                               // (21) 0.01758
/*12  */     int fbh, fbw;                                                             // (17) 0.02148
/*14  */     int ww, wh;                                                               // (22) 0.01758
/*18  */     fbw = surface_width(s->ds) * s->scale_x;                                  // (5) 0.04297
/*20  */     fbh = surface_height(s->ds) * s->scale_y;                                 // (6) 0.04102
/*24  */     gdk_drawable_get_size(gtk_widget_get_window(s->drawing_area), &ww, &wh);  // (2) 0.06836
/*28  */     mx = my = 0;                                                              // (19) 0.01953
/*30  */     if (ww > fbw) {                                                           // (16) 0.02344
/*32  */         mx = (ww - fbw) / 2;                                                  // (8) 0.03906
/*34  */     }                                                                         // (24) 0.007812
/*36  */     if (wh > fbh) {                                                           // (18) 0.02148
/*38  */         my = (wh - fbh) / 2;                                                  // (10) 0.03516
/*40  */     }                                                                         // (25) 0.007812
/*44  */     x = (motion->x - mx) / s->scale_x;                                        // (7) 0.03906
/*46  */     y = (motion->y - my) / s->scale_y;                                        // (9) 0.03711
/*50  */     if (x < 0 || y < 0 ||                                                     // (14) 0.02539
/*52  */         x >= surface_width(s->ds) ||                                          // (11) 0.03516
/*54  */         y >= surface_height(s->ds)) {                                         // (12) 0.03516
/*56  */         return TRUE;                                                          // (20) 0.01953
/*58  */     }                                                                         // (26) 0.007812
/*62  */     if (qemu_input_is_absolute()) {                                           // (13) 0.03125
/*64  */         qemu_input_queue_abs(s->dcl.con, INPUT_AXIS_X, x,                     // (3) 0.06641
/*66  */                              surface_width(s->ds));                           // (1) 0.07031
/*68  */         qemu_input_queue_abs(s->dcl.con, INPUT_AXIS_Y, y,                     // 0.0
/*70  */                              surface_height(s->ds));                          // 0.0
/*72  */         qemu_input_event_sync();                                              // 0.0
/*74  */     } else if (s->last_x != -1 && s->last_y != -1 && gd_is_grab_active(s)) {  // 0.0
/*76  */         qemu_input_queue_rel(s->dcl.con, INPUT_AXIS_X, x - s->last_x);        // 0.0
/*78  */         qemu_input_queue_rel(s->dcl.con, INPUT_AXIS_Y, y - s->last_y);        // 0.0
/*80  */         qemu_input_event_sync();                                              // 0.0
/*82  */     }                                                                         // 0.0
/*84  */     s->last_x = x;                                                            // 0.0
/*86  */     s->last_y = y;                                                            // 0.0
/*90  */     if (!qemu_input_is_absolute() && gd_is_grab_active(s)) {                  // 0.0
/*92  */         GdkScreen *screen = gtk_widget_get_screen(s->drawing_area);           // 0.0
/*94  */         int x = (int)motion->x_root;                                          // 0.0
/*96  */         int y = (int)motion->y_root;                                          // 0.0
/*100 */         /* In relative mode check to see if client pointer hit                // 0.0
/*102 */          * one of the screen edges, and if so move it back by                 // 0.0
/*104 */          * 200 pixels. This is important because the pointer                  // 0.0
/*106 */          * in the server doesn't correspond 1-for-1, and so                   // 0.0
/*108 */          * may still be only half way across the screen. Without              // 0.0
/*110 */          * this warp, the server pointer would thus appear to hit             // 0.0
/*112 */          * an invisible wall */                                               // 0.0
/*114 */         if (x == 0) {                                                         // 0.0
/*116 */             x += 200;                                                         // 0.0
/*118 */         }                                                                     // 0.0
/*120 */         if (y == 0) {                                                         // 0.0
/*122 */             y += 200;                                                         // 0.0
/*124 */         }                                                                     // 0.0
/*126 */         if (x == (gdk_screen_get_width(screen) - 1)) {                        // 0.0
/*128 */             x -= 200;                                                         // 0.0
/*130 */         }                                                                     // 0.0
/*132 */         if (y == (gdk_screen_get_height(screen) - 1)) {                       // 0.0
/*134 */             y -= 200;                                                         // 0.0
/*136 */         }                                                                     // 0.0
/*140 */         if (x != (int)motion->x_root || y != (int)motion->y_root) {           // 0.0
/*142 */ #if GTK_CHECK_VERSION(3, 0, 0)                                                // 0.0
/*144 */             GdkDevice *dev = gdk_event_get_device((GdkEvent *)motion);        // 0.0
/*146 */             gdk_device_warp(dev, screen, x, y);                               // 0.0
/*148 */ #else                                                                         // 0.0
/*150 */             GdkDisplay *display = gtk_widget_get_display(widget);             // 0.0
/*152 */             gdk_display_warp_pointer(display, screen, x, y);                  // 0.0
/*154 */ #endif                                                                        // 0.0
/*156 */             s->last_x = -1;                                                   // 0.0
/*158 */             s->last_y = -1;                                                   // 0.0
/*160 */             return FALSE;                                                     // 0.0
/*162 */         }                                                                     // 0.0
/*164 */     }                                                                         // 0.0
/*166 */     return TRUE;                                                              // 0.0
/*168 */ }                                                                             // 0.0
