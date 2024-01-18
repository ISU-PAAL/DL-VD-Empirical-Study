// commit message FFmpeg@f27b22b497 (target=0, prob=0.12241862, correct=True): h264: move 444 border xchg under if (deblock_top)
/*0   */ static av_always_inline void xchg_mb_border(H264Context *h, uint8_t *src_y,                                         // (4) 0.05859
/*2   */                                             uint8_t *src_cb, uint8_t *src_cr,                                       // (0) 0.1191
/*4   */                                             int linesize, int uvlinesize,                                           // (1) 0.1035
/*6   */                                             int xchg, int chroma444,                                                // (2) 0.1035
/*8   */                                             int simple, int pixel_shift)                                            // (3) 0.09961
/*10  */ {                                                                                                                   // (19) 0.001953
/*12  */     int deblock_topleft;                                                                                            // (13) 0.02148
/*14  */     int deblock_top;                                                                                                // (16) 0.01758
/*16  */     int top_idx = 1;                                                                                                // (14) 0.02148
/*18  */     uint8_t *top_border_m1;                                                                                         // (11) 0.0293
/*20  */     uint8_t *top_border;                                                                                            // (12) 0.02344
/*24  */     if (!simple && FRAME_MBAFF(h)) {                                                                                // (8) 0.0332
/*26  */         if (h->mb_y & 1) {                                                                                          // (7) 0.03516
/*28  */             if (!MB_MBAFF(h))                                                                                       // (6) 0.04102
/*30  */                 return;                                                                                             // (9) 0.0332
/*32  */         } else {                                                                                                    // (15) 0.01953
/*34  */             top_idx = MB_MBAFF(h) ? 0 : 1;                                                                          // (5) 0.05664
/*36  */         }                                                                                                           // (17) 0.01562
/*38  */     }                                                                                                               // (18) 0.007812
/*42  */     if (h->deblocking_filter == 2) {                                                                                // (10) 0.0293
/*44  */         deblock_topleft = h->slice_table[h->mb_xy - 1 - h->mb_stride] == h->slice_num;                              // 0.0
/*46  */         deblock_top     = h->top_type;                                                                              // 0.0
/*48  */     } else {                                                                                                        // 0.0
/*50  */         deblock_topleft = (h->mb_x > 0);                                                                            // 0.0
/*52  */         deblock_top     = (h->mb_y > !!MB_FIELD(h));                                                                // 0.0
/*54  */     }                                                                                                               // 0.0
/*58  */     src_y  -= linesize   + 1 + pixel_shift;                                                                         // 0.0
/*60  */     src_cb -= uvlinesize + 1 + pixel_shift;                                                                         // 0.0
/*62  */     src_cr -= uvlinesize + 1 + pixel_shift;                                                                         // 0.0
/*66  */     top_border_m1 = h->top_borders[top_idx][h->mb_x - 1];                                                           // 0.0
/*68  */     top_border    = h->top_borders[top_idx][h->mb_x];                                                               // 0.0
/*72  */ #define XCHG(a, b, xchg)                        \                                                                   // 0.0
/*74  */     if (pixel_shift) {                          \                                                                   // 0.0
/*76  */         if (xchg) {                             \                                                                   // 0.0
/*78  */             AV_SWAP64(b + 0, a + 0);            \                                                                   // 0.0
/*80  */             AV_SWAP64(b + 8, a + 8);            \                                                                   // 0.0
/*82  */         } else {                                \                                                                   // 0.0
/*84  */             AV_COPY128(b, a);                   \                                                                   // 0.0
/*86  */         }                                       \                                                                   // 0.0
/*88  */     } else if (xchg)                            \                                                                   // 0.0
/*90  */         AV_SWAP64(b, a);                        \                                                                   // 0.0
/*92  */     else                                        \                                                                   // 0.0
/*94  */         AV_COPY64(b, a);                                                                                            // 0.0
/*98  */     if (deblock_top) {                                                                                              // 0.0
/*100 */         if (deblock_topleft) {                                                                                      // 0.0
/*102 */             XCHG(top_border_m1 + (8 << pixel_shift),                                                                // 0.0
/*104 */                  src_y - (7 << pixel_shift), 1);                                                                    // 0.0
/*106 */         }                                                                                                           // 0.0
/*108 */         XCHG(top_border + (0 << pixel_shift), src_y + (1 << pixel_shift), xchg);                                    // 0.0
/*110 */         XCHG(top_border + (8 << pixel_shift), src_y + (9 << pixel_shift), 1);                                       // 0.0
/*112 */         if (h->mb_x + 1 < h->mb_width) {                                                                            // 0.0
/*114 */             XCHG(h->top_borders[top_idx][h->mb_x + 1],                                                              // 0.0
/*116 */                  src_y + (17 << pixel_shift), 1);                                                                   // 0.0
/*118 */         }                                                                                                           // 0.0
/*120 */     }                                                                                                               // 0.0
/*122 */     if (simple || !CONFIG_GRAY || !(h->flags & CODEC_FLAG_GRAY)) {                                                  // 0.0
/*124 */         if (chroma444) {                                                                                            // 0.0
/*126 */             if (deblock_topleft) {                                                                                  // 0.0
/*128 */                 XCHG(top_border_m1 + (24 << pixel_shift), src_cb - (7 << pixel_shift), 1);                          // 0.0
/*130 */                 XCHG(top_border_m1 + (40 << pixel_shift), src_cr - (7 << pixel_shift), 1);                          // 0.0
/*132 */             }                                                                                                       // 0.0
/*134 */             XCHG(top_border + (16 << pixel_shift), src_cb + (1 << pixel_shift), xchg);                              // 0.0
/*136 */             XCHG(top_border + (24 << pixel_shift), src_cb + (9 << pixel_shift), 1);                                 // 0.0
/*138 */             XCHG(top_border + (32 << pixel_shift), src_cr + (1 << pixel_shift), xchg);                              // 0.0
/*140 */             XCHG(top_border + (40 << pixel_shift), src_cr + (9 << pixel_shift), 1);                                 // 0.0
/*142 */             if (h->mb_x + 1 < h->mb_width) {                                                                        // 0.0
/*144 */                 XCHG(h->top_borders[top_idx][h->mb_x + 1] + (16 << pixel_shift), src_cb + (17 << pixel_shift), 1);  // 0.0
/*146 */                 XCHG(h->top_borders[top_idx][h->mb_x + 1] + (32 << pixel_shift), src_cr + (17 << pixel_shift), 1);  // 0.0
/*148 */             }                                                                                                       // 0.0
/*150 */         } else {                                                                                                    // 0.0
/*152 */             if (deblock_top) {                                                                                      // 0.0
/*154 */                 if (deblock_topleft) {                                                                              // 0.0
/*156 */                     XCHG(top_border_m1 + (16 << pixel_shift), src_cb - (7 << pixel_shift), 1);                      // 0.0
/*158 */                     XCHG(top_border_m1 + (24 << pixel_shift), src_cr - (7 << pixel_shift), 1);                      // 0.0
/*160 */                 }                                                                                                   // 0.0
/*162 */                 XCHG(top_border + (16 << pixel_shift), src_cb + 1 + pixel_shift, 1);                                // 0.0
/*164 */                 XCHG(top_border + (24 << pixel_shift), src_cr + 1 + pixel_shift, 1);                                // 0.0
/*166 */             }                                                                                                       // 0.0
/*168 */         }                                                                                                           // 0.0
/*170 */     }                                                                                                               // 0.0
/*172 */ }                                                                                                                   // 0.0
