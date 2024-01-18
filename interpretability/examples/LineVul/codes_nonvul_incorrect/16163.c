// commit message qemu@28f4a7083d (target=0, prob=0.7483154, correct=False): spice: fix coverity complains
/*0  */ static void display_mouse_define(DisplayChangeListener *dcl,               // (7) 0.05137
/*2  */                                  QEMUCursor *c)                            // (0) 0.1336
/*4  */ {                                                                          // (16) 0.003425
/*6  */     SimpleSpiceDisplay *ssd = container_of(dcl, SimpleSpiceDisplay, dcl);  // (2) 0.08904
/*10 */     qemu_mutex_lock(&ssd->lock);                                           // (4) 0.05822
/*12 */     if (c) {                                                               // (14) 0.0274
/*14 */         cursor_get(c);                                                     // (11) 0.04452
/*16 */     }                                                                      // (15) 0.0137
/*18 */     cursor_put(ssd->cursor);                                               // (10) 0.04452
/*20 */     ssd->cursor = c;                                                       // (13) 0.03767
/*22 */     ssd->hot_x = c->hot_x;                                                 // (5) 0.05479
/*24 */     ssd->hot_y = c->hot_y;                                                 // (6) 0.05479
/*26 */     g_free(ssd->ptr_move);                                                 // (9) 0.04795
/*28 */     ssd->ptr_move = NULL;                                                  // (12) 0.0411
/*30 */     g_free(ssd->ptr_define);                                               // (8) 0.04795
/*32 */     ssd->ptr_define = qemu_spice_create_cursor_update(ssd, c, 0);          // (1) 0.1062
/*34 */     qemu_mutex_unlock(&ssd->lock);                                         // (3) 0.06164
/*36 */ }                                                                          // (17) 0.003425
