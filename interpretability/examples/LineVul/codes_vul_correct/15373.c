// commit message qemu@50628d3479 (target=1, prob=0.5101693, correct=True): cirrus/vnc: zap bitblit support from console code.
/*0  */ void dpy_gfx_copy(QemuConsole *con, int src_x, int src_y,                   // (4) 0.07602
/*2  */                   int dst_x, int dst_y, int w, int h)                       // (2) 0.09649
/*4  */ {                                                                           // (17) 0.002924
/*6  */     DisplayState *s = con->ds;                                              // (10) 0.03509
/*8  */     DisplayChangeListener *dcl;                                             // (11) 0.02924
/*12 */     if (!qemu_console_is_visible(con)) {                                    // (7) 0.05263
/*14 */         return;                                                             // (12) 0.02632
/*16 */     }                                                                       // (15) 0.0117
/*18 */     QLIST_FOREACH(dcl, &s->listeners, next) {                               // (6) 0.0614
/*20 */         if (con != (dcl->con ? dcl->con : active_console)) {                // (3) 0.07895
/*22 */             continue;                                                       // (9) 0.03801
/*24 */         }                                                                   // (13) 0.02339
/*26 */         if (dcl->ops->dpy_gfx_copy) {                                       // (5) 0.06725
/*28 */             dcl->ops->dpy_gfx_copy(dcl, src_x, src_y, dst_x, dst_y, w, h);  // (0) 0.1374
/*30 */         } else { /* TODO */                                                 // (8) 0.04094
/*32 */             dcl->ops->dpy_gfx_update(dcl, dst_x, dst_y, w, h);              // (1) 0.114
/*34 */         }                                                                   // (14) 0.02339
/*36 */     }                                                                       // (16) 0.0117
/*38 */ }                                                                           // (18) 0.002924
