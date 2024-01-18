// commit message qemu@66668d197f (target=0, prob=0.21444046, correct=True): vnc-tight: fix regression with libxenstore
/*0  */ static int send_sub_rect(VncState *vs, int x, int y, int w, int h)             // (7) 0.05078
/*2  */ {                                                                              // (27) 0.001953
/*4  */     VncPalette *palette = &color_count_palette;                                // (9) 0.03711
/*6  */     uint32_t bg = 0, fg = 0;                                                   // (12) 0.0332
/*8  */     int colors;                                                                // (23) 0.01172
/*10 */     int ret = 0;                                                               // (20) 0.01562
/*12 */ #ifdef CONFIG_VNC_JPEG                                                         // (17) 0.01953
/*14 */     bool force_jpeg = false;                                                   // (15) 0.02148
/*16 */     bool allow_jpeg = true;                                                    // (16) 0.02148
/*18 */ #endif                                                                         // (25) 0.003906
/*22 */     vnc_framebuffer_update(vs, x, y, w, h, vs->tight.type);                    // (6) 0.05273
/*26 */     vnc_tight_start(vs);                                                       // (13) 0.02344
/*28 */     vnc_raw_send_framebuffer_update(vs, x, y, w, h);                           // (8) 0.04883
/*30 */     vnc_tight_stop(vs);                                                        // (14) 0.02344
/*34 */ #ifdef CONFIG_VNC_JPEG                                                         // (18) 0.01953
/*36 */     if (!vs->vd->non_adaptive && vs->tight.quality != (uint8_t)-1) {           // (4) 0.05664
/*38 */         double freq = vnc_update_freq(vs, x, y, w, h);                         // (5) 0.05664
/*42 */         if (freq < tight_jpeg_conf[vs->tight.quality].jpeg_freq_min) {         // (1) 0.06641
/*44 */             allow_jpeg = false;                                                // (10) 0.03516
/*46 */         }                                                                      // (21) 0.01562
/*48 */         if (freq >= tight_jpeg_conf[vs->tight.quality].jpeg_freq_threshold) {  // (0) 0.06836
/*50 */             force_jpeg = true;                                                 // (11) 0.03516
/*52 */             vnc_sent_lossy_rect(vs, x, y, w, h);                               // (2) 0.06055
/*54 */         }                                                                      // (22) 0.01562
/*56 */     }                                                                          // (24) 0.007812
/*58 */ #endif                                                                         // (26) 0.003906
/*62 */     colors = tight_fill_palette(vs, x, y, w * h, &bg, &fg, palette);           // (3) 0.05859
/*66 */ #ifdef CONFIG_VNC_JPEG                                                         // (19) 0.01953
/*68 */     if (allow_jpeg && vs->tight.quality != (uint8_t)-1) {                      // 0.0
/*70 */         ret = send_sub_rect_jpeg(vs, x, y, w, h, bg, fg, colors, palette,      // 0.0
/*72 */                                  force_jpeg);                                  // 0.0
/*74 */     } else {                                                                   // 0.0
/*76 */         ret = send_sub_rect_nojpeg(vs, x, y, w, h, bg, fg, colors, palette);   // 0.0
/*78 */     }                                                                          // 0.0
/*80 */ #else                                                                          // 0.0
/*82 */     ret = send_sub_rect_nojpeg(vs, x, y, w, h, bg, fg, colors, palette);       // 0.0
/*84 */ #endif                                                                         // 0.0
/*88 */     return ret;                                                                // 0.0
/*90 */ }                                                                              // 0.0
