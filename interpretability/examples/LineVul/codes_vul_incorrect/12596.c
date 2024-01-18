// commit message qemu@913a87885f (target=1, prob=0.12280676, correct=False): display: cirrus: ignore source pitch value as needed in blit_is_unsafe
/*0  */ static int cirrus_bitblt_solidfill(CirrusVGAState *s, int blt_rop)                // (4) 0.08084
/*2  */ {                                                                                 // (14) 0.002994
/*4  */     cirrus_fill_t rop_func;                                                       // (9) 0.04192
/*8  */     if (blit_is_unsafe(s)) {                                                      // (8) 0.0479
/*10 */         return 0;                                                                 // (11) 0.02994
/*12 */     }                                                                             // (13) 0.01198
/*14 */     rop_func = cirrus_fill[rop_to_index[blt_rop]][s->cirrus_blt_pixelwidth - 1];  // (1) 0.1168
/*16 */     rop_func(s, s->vga.vram_ptr + (s->cirrus_blt_dstaddr & s->cirrus_addr_mask),  // (0) 0.1317
/*18 */              s->cirrus_blt_dstpitch,                                              // (6) 0.07784
/*20 */              s->cirrus_blt_width, s->cirrus_blt_height);                          // (2) 0.1018
/*22 */     cirrus_invalidate_region(s, s->cirrus_blt_dstaddr,                            // (5) 0.08084
/*24 */ 			     s->cirrus_blt_dstpitch, s->cirrus_blt_width,                              // (3) 0.09581
/*26 */ 			     s->cirrus_blt_height);                                                    // (7) 0.05389
/*28 */     cirrus_bitblt_reset(s);                                                       // (10) 0.04192
/*30 */     return 1;                                                                     // (12) 0.01796
/*32 */ }                                                                                 // (15) 0.002994
