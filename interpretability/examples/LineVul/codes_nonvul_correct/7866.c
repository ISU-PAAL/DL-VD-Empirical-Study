// commit message qemu@c1076c3e13 (target=0, prob=0.021251656, correct=True): framebuffer: set DIRTY_MEMORY_VGA on RAM that is used for the framebuffer
/*0  */ static void pxa2xx_lcdc_dma0_redraw_rot0(PXA2xxLCDState *s,               // (4) 0.0625
/*2  */                 hwaddr addr, int *miny, int *maxy)                        // (6) 0.05859
/*4  */ {                                                                         // (22) 0.001953
/*6  */     DisplaySurface *surface = qemu_console_surface(s->con);               // (10) 0.04102
/*8  */     int src_width, dest_width;                                            // (16) 0.02344
/*10 */     drawfn fn = NULL;                                                     // (18) 0.01758
/*12 */     if (s->dest_width)                                                    // (17) 0.02148
/*14 */         fn = s->line_fn[s->transp][s->bpp];                               // (7) 0.04883
/*16 */     if (!fn)                                                              // (21) 0.01367
/*18 */         return;                                                           // (19) 0.01758
/*22 */     src_width = (s->xres + 3) & ~3;     /* Pad to a 4 pixels multiple */  // (5) 0.06055
/*24 */     if (s->bpp == pxa_lcdc_19pbpp || s->bpp == pxa_lcdc_18pbpp)           // (2) 0.07227
/*26 */         src_width *= 3;                                                   // (13) 0.02734
/*28 */     else if (s->bpp > pxa_lcdc_16bpp)                                     // (8) 0.04297
/*30 */         src_width *= 4;                                                   // (14) 0.02734
/*32 */     else if (s->bpp > pxa_lcdc_8bpp)                                      // (9) 0.04297
/*34 */         src_width *= 2;                                                   // (15) 0.02734
/*38 */     dest_width = s->xres * s->dest_width;                                 // (11) 0.03516
/*40 */     *miny = 0;                                                            // (20) 0.01758
/*42 */     framebuffer_update_display(surface, s->sysmem,                        // (12) 0.0332
/*44 */                                addr, s->xres, s->yres,                    // (1) 0.08203
/*46 */                                src_width, dest_width, s->dest_width,      // (0) 0.08594
/*48 */                                s->invalidated,                            // (3) 0.07031
/*50 */                                fn, s->dma_ch[0].palette, miny, maxy);     // 0.0
/*52 */ }                                                                         // 0.0
