// commit message qemu@973945804d (target=0, prob=0.012020391, correct=True): tcx: use tcx_set_dirty() for accelerated ops
/*0  */ static void tcx_blit_writel(void *opaque, hwaddr addr,                // (8) 0.04102
/*2  */                             uint64_t val, unsigned size)              // (0) 0.07031
/*4  */ {                                                                     // (23) 0.001953
/*6  */     TCXState *s = opaque;                                             // (18) 0.02148
/*8  */     uint32_t adsr, len;                                               // (16) 0.02344
/*10 */     int i;                                                            // (21) 0.01172
/*14 */     if (!(addr & 4)) {                                                // (19) 0.02148
/*16 */         s->tmpblit = val;                                             // (15) 0.0293
/*18 */     } else {                                                          // (22) 0.01172
/*20 */         addr = (addr >> 3) & 0xfffff;                                 // (9) 0.03906
/*22 */         adsr = val & 0xffffff;                                        // (13) 0.0332
/*24 */         len = ((val >> 24) & 0x1f) + 1;                               // (7) 0.04492
/*26 */         if (adsr == 0xffffff) {                                       // (12) 0.03516
/*28 */             memset(&s->vram[addr], s->tmpblit, len);                  // (3) 0.05664
/*30 */             if (s->depth == 24) {                                     // (10) 0.03906
/*32 */                 val = s->tmpblit & 0xffffff;                          // (4) 0.05469
/*34 */                 val = cpu_to_be32(val);                               // (6) 0.05078
/*36 */                 for (i = 0; i < len; i++) {                           // (5) 0.05469
/*38 */                     s->vram24[addr + i] = val;                        // (2) 0.0625
/*40 */                 }                                                     // (14) 0.03125
/*42 */             }                                                         // (17) 0.02344
/*44 */         } else {                                                      // (20) 0.01953
/*46 */             memcpy(&s->vram[addr], &s->vram[adsr], len);              // (1) 0.06445
/*48 */             if (s->depth == 24) {                                     // (11) 0.03906
/*50 */                 memcpy(&s->vram24[addr], &s->vram24[adsr], len * 4);  // 0.0
/*52 */             }                                                         // 0.0
/*54 */         }                                                             // 0.0
/*56 */         memory_region_set_dirty(&s->vram_mem, addr, len);             // 0.0
/*58 */     }                                                                 // 0.0
/*60 */ }                                                                     // 0.0
