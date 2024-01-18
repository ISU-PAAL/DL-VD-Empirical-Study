// commit message qemu@9f2130f58d (target=0, prob=0.32356662, correct=True): xenfb: remove xen_init_display "temporary" hack
/*0  */ static int fb_initialise(struct XenDevice *xendev)                                  // (9) 0.03125
/*2  */ {                                                                                   // (25) 0.001953
/*4  */     struct XenFB *fb = container_of(xendev, struct XenFB, c.xendev);                // (4) 0.05273
/*6  */     struct xenfb_page *fb_page;                                                     // (13) 0.02539
/*8  */     int videoram;                                                                   // (19) 0.01563
/*10 */     int rc;                                                                         // (21) 0.01172
/*14 */     if (xenstore_read_fe_int(xendev, "videoram", &videoram) == -1)                  // (3) 0.06836
/*16 */ 	videoram = 0;                                                                      // (20) 0.01562
/*20 */     rc = common_bind(&fb->c);                                                       // (14) 0.02539
/*22 */     if (rc != 0)                                                                    // (16) 0.01758
/*24 */ 	return rc;                                                                         // (22) 0.007812
/*28 */     fb_page = fb->c.page;                                                           // (11) 0.0293
/*30 */     rc = xenfb_configure_fb(fb, videoram * 1024 * 1024U,                            // (8) 0.04688
/*32 */ 			    fb_page->width, fb_page->height, fb_page->depth,                             // (5) 0.05273
/*34 */ 			    fb_page->mem_length, 0, fb_page->line_length);                               // (6) 0.05078
/*36 */     if (rc != 0)                                                                    // (17) 0.01758
/*38 */ 	return rc;                                                                         // (23) 0.007812
/*42 */     rc = xenfb_map_fb(fb);                                                          // (12) 0.02734
/*44 */     if (rc != 0)                                                                    // (18) 0.01758
/*46 */ 	return rc;                                                                         // (24) 0.007812
/*50 */ #if 0  /* handled in xen_init_display() for now */                                  // (10) 0.03125
/*52 */     if (!fb->have_console) {                                                        // (15) 0.02344
/*54 */         fb->c.ds = graphic_console_init(xenfb_update,                               // (7) 0.05078
/*56 */                                         xenfb_invalidate,                           // (0) 0.08984
/*58 */                                         NULL,                                       // (1) 0.08008
/*60 */                                         NULL,                                       // (2) 0.08008
/*62 */                                         fb);                                        // 0.0
/*64 */         fb->have_console = 1;                                                       // 0.0
/*66 */     }                                                                               // 0.0
/*68 */ #endif                                                                              // 0.0
/*72 */     if (xenstore_read_fe_int(xendev, "feature-update", &fb->feature_update) == -1)  // 0.0
/*74 */ 	fb->feature_update = 0;                                                            // 0.0
/*76 */     if (fb->feature_update)                                                         // 0.0
/*78 */ 	xenstore_write_be_int(xendev, "request-update", 1);                                // 0.0
/*82 */     xen_pv_printf(xendev, 1, "feature-update=%d, videoram=%d\n",                    // 0.0
/*84 */ 		  fb->feature_update, videoram);                                                  // 0.0
/*86 */     return 0;                                                                       // 0.0
/*88 */ }                                                                                   // 0.0
