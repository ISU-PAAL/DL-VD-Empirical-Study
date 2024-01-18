// commit message qemu@2f464b5a32 (target=0, prob=0.21112148, correct=True): qxl: save qemu_create_displaysurface_from result
/*0  */ static void qxl_render_update_area_unlocked(PCIQXLDevice *qxl)                  // (10) 0.05078
/*2  */ {                                                                               // (17) 0.001953
/*4  */     VGACommonState *vga = &qxl->vga;                                            // (13) 0.03906
/*6  */     int i;                                                                      // (16) 0.01172
/*10 */     if (qxl->guest_primary.resized) {                                           // (15) 0.03516
/*12 */         qxl->guest_primary.resized = 0;                                         // (12) 0.04102
/*14 */         qxl->guest_primary.data = memory_region_get_ram_ptr(&qxl->vga.vram);    // (0) 0.07422
/*16 */         qxl_set_rect_to_surface(qxl, &qxl->dirty[0]);                           // (2) 0.0625
/*18 */         qxl->num_dirty_rects = 1;                                               // (14) 0.03906
/*20 */         trace_qxl_render_guest_primary_resized(                                 // (11) 0.04492
/*22 */                qxl->guest_primary.surface.width,                                // (5) 0.05273
/*24 */                qxl->guest_primary.surface.height,                               // (6) 0.05273
/*26 */                qxl->guest_primary.qxl_stride,                                   // (3) 0.05859
/*28 */                qxl->guest_primary.bytes_pp,                                     // (7) 0.05273
/*30 */                qxl->guest_primary.bits_pp);                                     // (8) 0.05273
/*32 */         if (qxl->guest_primary.qxl_stride > 0) {                                // (4) 0.05469
/*34 */             qemu_free_displaysurface(vga->ds);                                  // (9) 0.05273
/*36 */             qemu_create_displaysurface_from(qxl->guest_primary.surface.width,   // (1) 0.07227
/*38 */                                             qxl->guest_primary.surface.height,  // 0.0
/*40 */                                             qxl->guest_primary.bits_pp,         // 0.0
/*42 */                                             qxl->guest_primary.abs_stride,      // 0.0
/*44 */                                             qxl->guest_primary.data);           // 0.0
/*46 */         } else {                                                                // 0.0
/*48 */             qemu_resize_displaysurface(vga->ds,                                 // 0.0
/*50 */                     qxl->guest_primary.surface.width,                           // 0.0
/*52 */                     qxl->guest_primary.surface.height);                         // 0.0
/*54 */         }                                                                       // 0.0
/*56 */         dpy_gfx_resize(vga->ds);                                                // 0.0
/*58 */     }                                                                           // 0.0
/*60 */     for (i = 0; i < qxl->num_dirty_rects; i++) {                                // 0.0
/*62 */         if (qemu_spice_rect_is_empty(qxl->dirty+i)) {                           // 0.0
/*64 */             break;                                                              // 0.0
/*66 */         }                                                                       // 0.0
/*68 */         qxl_blit(qxl, qxl->dirty+i);                                            // 0.0
/*70 */         dpy_gfx_update(vga->ds,                                                 // 0.0
/*72 */                        qxl->dirty[i].left, qxl->dirty[i].top,                   // 0.0
/*74 */                        qxl->dirty[i].right - qxl->dirty[i].left,                // 0.0
/*76 */                        qxl->dirty[i].bottom - qxl->dirty[i].top);               // 0.0
/*78 */     }                                                                           // 0.0
/*80 */     qxl->num_dirty_rects = 0;                                                   // 0.0
/*82 */ }                                                                               // 0.0
