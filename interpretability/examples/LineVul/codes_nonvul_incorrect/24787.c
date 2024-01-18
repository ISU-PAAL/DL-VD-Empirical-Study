// commit message FFmpeg@6df2c94130 (target=0, prob=0.70628417, correct=False): avfilter/showcqt: remove yuv offset
/*0   */ static void draw_bar_yuv(AVFrame *out, const float *h, const float *rcp_h,       // (4) 0.05273
/*2   */                          const ColorFloat *c, int bar_h)                         // (0) 0.06836
/*4   */ {                                                                                // (20) 0.001953
/*6   */     int x, y, yh, w = out->width;                                                // (17) 0.0332
/*8   */     float mul, ht, rcp_bar_h = 1.0f / bar_h;                                     // (5) 0.04883
/*10  */     uint8_t *vy = out->data[0], *vu = out->data[1], *vv = out->data[2];          // (2) 0.06641
/*12  */     uint8_t *lpy, *lpu, *lpv;                                                    // (14) 0.03711
/*14  */     int lsy = out->linesize[0], lsu = out->linesize[1], lsv = out->linesize[2];  // (3) 0.06641
/*16  */     int fmt = out->format;                                                       // (19) 0.01953
/*20  */     for (y = 0; y < bar_h; y += 2) {                                             // (12) 0.03906
/*22  */         yh = (fmt == AV_PIX_FMT_YUV420P) ? y / 2 : y;                            // (1) 0.06641
/*24  */         ht = (bar_h - y) * rcp_bar_h;                                            // (6) 0.04883
/*26  */         lpy = vy + y * lsy;                                                      // (16) 0.03516
/*28  */         lpu = vu + yh * lsu;                                                     // (15) 0.03711
/*30  */         lpv = vv + yh * lsv;                                                     // (13) 0.03906
/*32  */         for (x = 0; x < w; x += 2) {                                             // (7) 0.04297
/*34  */             if (h[x] <= ht) {                                                    // (8) 0.04297
/*36  */                 *lpy++ = 16;                                                     // (9) 0.04297
/*38  */                 *lpu++ = 128;                                                    // (10) 0.04297
/*40  */                 *lpv++ = 128;                                                    // (11) 0.04297
/*42  */             } else {                                                             // (18) 0.02734
/*44  */                 mul = (h[x] - ht) * rcp_h[x];                                    // 0.0
/*46  */                 *lpy++ = mul * c[x].yuv.y + (1.0f - mul) * 16.0f + 0.5f;         // 0.0
/*48  */                 *lpu++ = mul * c[x].yuv.u + (1.0f - mul) * 128.0f + 0.5f;        // 0.0
/*50  */                 *lpv++ = mul * c[x].yuv.v + (1.0f - mul) * 128.0f + 0.5f;        // 0.0
/*52  */             }                                                                    // 0.0
/*54  */             /* u and v are skipped on yuv422p and yuv420p */                     // 0.0
/*56  */             if (fmt == AV_PIX_FMT_YUV444P) {                                     // 0.0
/*58  */                 if (h[x+1] <= ht) {                                              // 0.0
/*60  */                     *lpy++ = 16;                                                 // 0.0
/*62  */                     *lpu++ = 128;                                                // 0.0
/*64  */                     *lpv++ = 128;                                                // 0.0
/*66  */                 } else {                                                         // 0.0
/*68  */                     mul = (h[x+1] - ht) * rcp_h[x+1];                            // 0.0
/*70  */                     *lpy++ = mul * c[x+1].yuv.y + (1.0f - mul) * 16.0f + 0.5f;   // 0.0
/*72  */                     *lpu++ = mul * c[x+1].yuv.u + (1.0f - mul) * 128.0f + 0.5f;  // 0.0
/*74  */                     *lpv++ = mul * c[x+1].yuv.v + (1.0f - mul) * 128.0f + 0.5f;  // 0.0
/*76  */                 }                                                                // 0.0
/*78  */             } else {                                                             // 0.0
/*80  */                 if (h[x+1] <= ht) {                                              // 0.0
/*82  */                     *lpy++ = 16;                                                 // 0.0
/*84  */                 } else {                                                         // 0.0
/*86  */                     mul = (h[x+1] - ht) * rcp_h[x+1];                            // 0.0
/*88  */                     *lpy++ = mul * c[x+1].yuv.y + (1.0f - mul) * 16.0f + 0.5f;   // 0.0
/*90  */                 }                                                                // 0.0
/*92  */             }                                                                    // 0.0
/*94  */         }                                                                        // 0.0
/*98  */         ht = (bar_h - (y+1)) * rcp_bar_h;                                        // 0.0
/*100 */         lpy = vy + (y+1) * lsy;                                                  // 0.0
/*102 */         lpu = vu + (y+1) * lsu;                                                  // 0.0
/*104 */         lpv = vv + (y+1) * lsv;                                                  // 0.0
/*106 */         for (x = 0; x < w; x += 2) {                                             // 0.0
/*108 */             /* u and v are skipped on yuv420p */                                 // 0.0
/*110 */             if (fmt != AV_PIX_FMT_YUV420P) {                                     // 0.0
/*112 */                 if (h[x] <= ht) {                                                // 0.0
/*114 */                     *lpy++ = 16;                                                 // 0.0
/*116 */                     *lpu++ = 128;                                                // 0.0
/*118 */                     *lpv++ = 128;                                                // 0.0
/*120 */                 } else {                                                         // 0.0
/*122 */                     mul = (h[x] - ht) * rcp_h[x];                                // 0.0
/*124 */                     *lpy++ = mul * c[x].yuv.y + (1.0f - mul) * 16.0f + 0.5f;     // 0.0
/*126 */                     *lpu++ = mul * c[x].yuv.u + (1.0f - mul) * 128.0f + 0.5f;    // 0.0
/*128 */                     *lpv++ = mul * c[x].yuv.v + (1.0f - mul) * 128.0f + 0.5f;    // 0.0
/*130 */                 }                                                                // 0.0
/*132 */             } else {                                                             // 0.0
/*134 */                 if (h[x] <= ht) {                                                // 0.0
/*136 */                     *lpy++ = 16;                                                 // 0.0
/*138 */                 } else {                                                         // 0.0
/*140 */                     mul = (h[x] - ht) * rcp_h[x];                                // 0.0
/*142 */                     *lpy++ = mul * c[x].yuv.y + (1.0f - mul) * 16.0f + 0.5f;     // 0.0
/*144 */                 }                                                                // 0.0
/*146 */             }                                                                    // 0.0
/*148 */             /* u and v are skipped on yuv422p and yuv420p */                     // 0.0
/*150 */             if (out->format == AV_PIX_FMT_YUV444P) {                             // 0.0
/*152 */                 if (h[x+1] <= ht) {                                              // 0.0
/*154 */                     *lpy++ = 16;                                                 // 0.0
/*156 */                     *lpu++ = 128;                                                // 0.0
/*158 */                     *lpv++ = 128;                                                // 0.0
/*160 */                 } else {                                                         // 0.0
/*162 */                     mul = (h[x+1] - ht) * rcp_h[x+1];                            // 0.0
/*164 */                     *lpy++ = mul * c[x+1].yuv.y + (1.0f - mul) * 16.0f + 0.5f;   // 0.0
/*166 */                     *lpu++ = mul * c[x+1].yuv.u + (1.0f - mul) * 128.0f + 0.5f;  // 0.0
/*168 */                     *lpv++ = mul * c[x+1].yuv.v + (1.0f - mul) * 128.0f + 0.5f;  // 0.0
/*170 */                 }                                                                // 0.0
/*172 */             } else {                                                             // 0.0
/*174 */                 if (h[x+1] <= ht) {                                              // 0.0
/*176 */                     *lpy++ = 16;                                                 // 0.0
/*178 */                 } else {                                                         // 0.0
/*180 */                     mul = (h[x+1] - ht) * rcp_h[x+1];                            // 0.0
/*182 */                     *lpy++ = mul * c[x+1].yuv.y + (1.0f - mul) * 16.0f + 0.5f;   // 0.0
/*184 */                 }                                                                // 0.0
/*186 */             }                                                                    // 0.0
/*188 */         }                                                                        // 0.0
/*190 */     }                                                                            // 0.0
/*192 */ }                                                                                // 0.0
