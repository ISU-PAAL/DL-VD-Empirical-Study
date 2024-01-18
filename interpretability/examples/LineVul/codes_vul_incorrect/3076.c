// commit message qemu@ab9509ccea (target=1, prob=0.22225298, correct=False): spice: make sure we don't overflow ssd->buf
/*0  */ void qemu_spice_create_host_primary(SimpleSpiceDisplay *ssd)        // (5) 0.06509
/*2  */ {                                                                   // (15) 0.002959
/*4  */     QXLDevSurfaceCreate surface;                                    // (13) 0.0355
/*8  */     memset(&surface, 0, sizeof(surface));                           // (11) 0.04142
/*12 */     dprint(1, "%s/%d: %dx%d\n", __func__, ssd->qxl.id,              // (0) 0.1006
/*14 */            surface_width(ssd->ds), surface_height(ssd->ds));        // (2) 0.08284
/*18 */     surface.format     = SPICE_SURFACE_FMT_32_xRGB;                 // (3) 0.07692
/*20 */     surface.width      = surface_width(ssd->ds);                    // (6) 0.06213
/*22 */     surface.height     = surface_height(ssd->ds);                   // (7) 0.05917
/*24 */     surface.stride     = -surface.width * 4;                        // (9) 0.05621
/*26 */     surface.mouse_mode = true;                                      // (14) 0.03254
/*28 */     surface.flags      = 0;                                         // (12) 0.04142
/*30 */     surface.type       = 0;                                         // (10) 0.04438
/*32 */     surface.mem        = (uintptr_t)ssd->buf;                       // (4) 0.07396
/*34 */     surface.group_id   = MEMSLOT_GROUP_HOST;                        // (8) 0.05917
/*38 */     qemu_spice_create_primary_surface(ssd, 0, &surface, QXL_SYNC);  // (1) 0.08876
/*40 */ }                                                                   // (16) 0.002959
