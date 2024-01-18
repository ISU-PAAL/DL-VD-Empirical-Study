// commit message qemu@21ef45d712 (target=1, prob=0.14118081, correct=False): console: kill DisplayState->opaque
/*0   */ static void gd_resize(DisplayChangeListener *dcl,                           // (14) 0.0293
/*2   */                       DisplayState *ds)                                     // (4) 0.05078
/*4   */ {                                                                           // (28) 0.001953
/*6   */     GtkDisplayState *s = ds->opaque;                                        // (12) 0.03125
/*8   */     cairo_format_t kind;                                                    // (15) 0.02148
/*10  */     int stride;                                                             // (21) 0.01172
/*14  */     DPRINTF("resize(width=%d, height=%d)\n",                                // (5) 0.04297
/*16  */             ds_get_width(ds), ds_get_height(ds));                           // (1) 0.05664
/*20  */     if (s->surface) {                                                       // (16) 0.01953
/*22  */         cairo_surface_destroy(s->surface);                                  // (9) 0.03516
/*24  */     }                                                                       // (26) 0.007812
/*28  */     switch (ds->surface->pf.bits_per_pixel) {                               // (7) 0.03711
/*30  */     case 8:                                                                 // (23) 0.01172
/*32  */         kind = CAIRO_FORMAT_A8;                                             // (11) 0.03516
/*34  */         break;                                                              // (17) 0.01758
/*36  */     case 16:                                                                // (22) 0.01172
/*38  */         kind = CAIRO_FORMAT_RGB16_565;                                      // (6) 0.03906
/*40  */         break;                                                              // (18) 0.01758
/*42  */     case 32:                                                                // (24) 0.01172
/*44  */         kind = CAIRO_FORMAT_RGB24;                                          // (10) 0.03516
/*46  */         break;                                                              // (19) 0.01758
/*48  */     default:                                                                // (25) 0.009766
/*50  */         g_assert_not_reached();                                             // (13) 0.03125
/*52  */         break;                                                              // (20) 0.01758
/*54  */     }                                                                       // (27) 0.007812
/*58  */     stride = cairo_format_stride_for_width(kind, ds_get_width(ds));         // (3) 0.05469
/*60  */     g_assert(ds_get_linesize(ds) == stride);                                // (8) 0.03711
/*64  */     s->surface = cairo_image_surface_create_for_data(ds_get_data(ds),       // (2) 0.05469
/*66  */                                                      kind,                  // (0) 0.1055
/*68  */                                                      ds_get_width(ds),      // 0.0
/*70  */                                                      ds_get_height(ds),     // 0.0
/*72  */                                                      ds_get_linesize(ds));  // 0.0
/*76  */     if (!s->full_screen) {                                                  // 0.0
/*78  */         GtkRequisition req;                                                 // 0.0
/*80  */         double sx, sy;                                                      // 0.0
/*84  */         if (s->free_scale) {                                                // 0.0
/*86  */             sx = s->scale_x;                                                // 0.0
/*88  */             sy = s->scale_y;                                                // 0.0
/*92  */             s->scale_y = 1.0;                                               // 0.0
/*94  */             s->scale_x = 1.0;                                               // 0.0
/*96  */         } else {                                                            // 0.0
/*98  */             sx = 1.0;                                                       // 0.0
/*100 */             sy = 1.0;                                                       // 0.0
/*102 */         }                                                                   // 0.0
/*106 */         gtk_widget_set_size_request(s->drawing_area,                        // 0.0
/*108 */                                     ds_get_width(ds) * s->scale_x,          // 0.0
/*110 */                                     ds_get_height(ds) * s->scale_y);        // 0.0
/*112 */ #if GTK_CHECK_VERSION(3, 0, 0)                                              // 0.0
/*114 */         gtk_widget_get_preferred_size(s->vbox, NULL, &req);                 // 0.0
/*116 */ #else                                                                       // 0.0
/*118 */         gtk_widget_size_request(s->vbox, &req);                             // 0.0
/*120 */ #endif                                                                      // 0.0
/*124 */         gtk_window_resize(GTK_WINDOW(s->window),                            // 0.0
/*126 */                           req.width * sx, req.height * sy);                 // 0.0
/*128 */     }                                                                       // 0.0
/*130 */ }                                                                           // 0.0
