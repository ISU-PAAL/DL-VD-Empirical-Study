// commit message qemu@368d25881c (target=0, prob=0.3242832, correct=True): vnc: fix uint8_t comparisons with negative values
/*0   */ static int zrle_send_framebuffer_update(VncState *vs, int x, int y,               // (6) 0.04883
/*2   */                                         int w, int h)                             // (0) 0.08789
/*4   */ {                                                                                 // (25) 0.001953
/*6   */     bool be = !!(vs->clientds.flags & QEMU_BIG_ENDIAN_FLAG);                      // (4) 0.05273
/*8   */     size_t bytes;                                                                 // (19) 0.01563
/*10  */     int zywrle_level;                                                             // (16) 0.02148
/*14  */     if (vs->zrle.type == VNC_ENCODING_ZYWRLE) {                                   // (5) 0.05078
/*16  */         if (!vs->vd->lossy || vs->tight.quality < 0 || vs->tight.quality == 9) {  // (2) 0.06445
/*18  */             zywrle_level = 0;                                                     // (8) 0.03906
/*20  */             vs->zrle.type = VNC_ENCODING_ZRLE;                                    // (3) 0.05859
/*22  */         } else if (vs->tight.quality < 3) {                                       // (9) 0.03906
/*24  */             zywrle_level = 3;                                                     // (10) 0.03906
/*26  */         } else if (vs->tight.quality < 6) {                                       // (11) 0.03906
/*28  */             zywrle_level = 2;                                                     // (12) 0.03906
/*30  */         } else {                                                                  // (17) 0.01953
/*32  */             zywrle_level = 1;                                                     // (13) 0.03906
/*34  */         }                                                                         // (20) 0.01562
/*36  */     } else {                                                                      // (21) 0.01172
/*38  */         zywrle_level = 0;                                                         // (14) 0.03125
/*40  */     }                                                                             // (24) 0.007812
/*44  */     vnc_zrle_start(vs);                                                           // (15) 0.02734
/*48  */     switch(vs->clientds.pf.bytes_per_pixel) {                                     // (7) 0.03906
/*50  */     case 1:                                                                       // (22) 0.01172
/*52  */         zrle_encode_8ne(vs, x, y, w, h, zywrle_level);                            // (1) 0.06641
/*54  */         break;                                                                    // (18) 0.01758
/*58  */     case 2:                                                                       // (23) 0.01172
/*60  */         if (vs->clientds.pf.gmax > 0x1F) {                                        // 0.0
/*62  */             if (be) {                                                             // 0.0
/*64  */                 zrle_encode_16be(vs, x, y, w, h, zywrle_level);                   // 0.0
/*66  */             } else {                                                              // 0.0
/*68  */                 zrle_encode_16le(vs, x, y, w, h, zywrle_level);                   // 0.0
/*70  */             }                                                                     // 0.0
/*72  */         } else {                                                                  // 0.0
/*74  */             if (be) {                                                             // 0.0
/*76  */                 zrle_encode_15be(vs, x, y, w, h, zywrle_level);                   // 0.0
/*78  */             } else {                                                              // 0.0
/*80  */                 zrle_encode_15le(vs, x, y, w, h, zywrle_level);                   // 0.0
/*82  */             }                                                                     // 0.0
/*84  */         }                                                                         // 0.0
/*86  */         break;                                                                    // 0.0
/*90  */     case 4:                                                                       // 0.0
/*92  */     {                                                                             // 0.0
/*94  */         bool fits_in_ls3bytes;                                                    // 0.0
/*96  */         bool fits_in_ms3bytes;                                                    // 0.0
/*100 */         fits_in_ls3bytes =                                                        // 0.0
/*102 */             ((vs->clientds.pf.rmax << vs->clientds.pf.rshift) < (1 << 24) &&      // 0.0
/*104 */              (vs->clientds.pf.gmax << vs->clientds.pf.gshift) < (1 << 24) &&      // 0.0
/*106 */              (vs->clientds.pf.bmax << vs->clientds.pf.bshift) < (1 << 24));       // 0.0
/*110 */         fits_in_ms3bytes = (vs->clientds.pf.rshift > 7 &&                         // 0.0
/*112 */                             vs->clientds.pf.gshift > 7 &&                         // 0.0
/*114 */                             vs->clientds.pf.bshift > 7);                          // 0.0
/*118 */         if ((fits_in_ls3bytes && !be) || (fits_in_ms3bytes && be)) {              // 0.0
/*120 */             if (be) {                                                             // 0.0
/*122 */                 zrle_encode_24abe(vs, x, y, w, h, zywrle_level);                  // 0.0
/*124 */             } else {                                                              // 0.0
/*126 */                 zrle_encode_24ale(vs, x, y, w, h, zywrle_level);                  // 0.0
/*128 */           }                                                                       // 0.0
/*130 */         } else if ((fits_in_ls3bytes && be) || (fits_in_ms3bytes && !be)) {       // 0.0
/*132 */             if (be) {                                                             // 0.0
/*134 */                 zrle_encode_24bbe(vs, x, y, w, h, zywrle_level);                  // 0.0
/*136 */             } else {                                                              // 0.0
/*138 */                 zrle_encode_24ble(vs, x, y, w, h, zywrle_level);                  // 0.0
/*140 */             }                                                                     // 0.0
/*142 */         } else {                                                                  // 0.0
/*144 */             if (be) {                                                             // 0.0
/*146 */                 zrle_encode_32be(vs, x, y, w, h, zywrle_level);                   // 0.0
/*148 */             } else {                                                              // 0.0
/*150 */                 zrle_encode_32le(vs, x, y, w, h, zywrle_level);                   // 0.0
/*152 */             }                                                                     // 0.0
/*154 */         }                                                                         // 0.0
/*156 */     }                                                                             // 0.0
/*158 */     break;                                                                        // 0.0
/*160 */     }                                                                             // 0.0
/*164 */     vnc_zrle_stop(vs);                                                            // 0.0
/*166 */     bytes = zrle_compress_data(vs, Z_DEFAULT_COMPRESSION);                        // 0.0
/*168 */     vnc_framebuffer_update(vs, x, y, w, h, vs->zrle.type);                        // 0.0
/*170 */     vnc_write_u32(vs, bytes);                                                     // 0.0
/*172 */     vnc_write(vs, vs->zrle.zlib.buffer, vs->zrle.zlib.offset);                    // 0.0
/*174 */     return 1;                                                                     // 0.0
/*176 */ }                                                                                 // 0.0
