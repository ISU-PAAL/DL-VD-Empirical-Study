// commit message FFmpeg@b8edf91657 (target=0, prob=0.495135, correct=True): lavfi/histeq: fix out of array write
/*0   */ static int filter_frame(AVFilterLink *inlink, AVFrame *inpic)                       // (8) 0.03711
/*2   */ {                                                                                   // (26) 0.001953
/*4   */     AVFilterContext   *ctx     = inlink->dst;                                       // (6) 0.04101
/*6   */     HisteqContext     *histeq  = ctx->priv;                                         // (7) 0.03906
/*8   */     AVFilterLink      *outlink = ctx->outputs[0];                                   // (5) 0.04492
/*10  */     int strength  = histeq->strength  * 1000;                                       // (14) 0.0293
/*12  */     int intensity = histeq->intensity * 1000;                                       // (17) 0.02539
/*14  */     int x, y, i, luthi, lutlo, lut, luma, oluma, m;                                 // (2) 0.05666
/*16  */     AVFrame *outpic;                                                                // (23) 0.01758
/*18  */     unsigned int r, g, b, jran;                                                     // (15) 0.02734
/*20  */     uint8_t *src, *dst;                                                             // (16) 0.02734
/*24  */     outpic = ff_get_video_buffer(outlink, outlink->w, outlink->h);                  // (3) 0.05273
/*26  */     if (!outpic) {                                                                  // (24) 0.01758
/*28  */         av_frame_free(&inpic);                                                      // (12) 0.03125
/*30  */         return AVERROR(ENOMEM);                                                     // (13) 0.03125
/*32  */     }                                                                               // (25) 0.007812
/*34  */     av_frame_copy_props(outpic, inpic);                                             // (10) 0.03516
/*38  */     /* Seed random generator for antibanding. */                                    // (19) 0.02344
/*40  */     jran = LCG_SEED;                                                                // (20) 0.02344
/*44  */     /* Calculate and store the luminance and calculate the global histogram         // (11) 0.0332
/*46  */        based on the luminance. */                                                   // (18) 0.02539
/*48  */     memset(histeq->in_histogram, 0, sizeof(histeq->in_histogram));                  // (4) 0.05078
/*50  */     src = inpic->data[0];                                                           // (22) 0.02344
/*52  */     dst = outpic->data[0];                                                          // (21) 0.02344
/*54  */     for (y = 0; y < inlink->h; y++) {                                               // (9) 0.03711
/*56  */         for (x = 0; x < inlink->w * histeq->bpp; x += histeq->bpp) {                // (0) 0.06836
/*58  */             GET_RGB_VALUES(r, g, b, src, histeq->rgba_map);                         // (1) 0.0664
/*60  */             luma = (55 * r + 182 * g + 19 * b) >> 8;                                // 0.0
/*62  */             dst[x + histeq->rgba_map[A]] = luma;                                    // 0.0
/*64  */             histeq->in_histogram[luma]++;                                           // 0.0
/*66  */         }                                                                           // 0.0
/*68  */         src += inpic->linesize[0];                                                  // 0.0
/*70  */         dst += outpic->linesize[0];                                                 // 0.0
/*72  */     }                                                                               // 0.0
/*76  */ #ifdef DEBUG                                                                        // 0.0
/*78  */     for (x = 0; x < 256; x++)                                                       // 0.0
/*80  */         av_dlog(ctx, "in[%d]: %u\n", x, histeq->in_histogram[x]);                   // 0.0
/*82  */ #endif                                                                              // 0.0
/*86  */     /* Calculate the lookup table. */                                               // 0.0
/*88  */     histeq->LUT[0] = histeq->in_histogram[0];                                       // 0.0
/*90  */     /* Accumulate */                                                                // 0.0
/*92  */     for (x = 1; x < 256; x++)                                                       // 0.0
/*94  */         histeq->LUT[x] = histeq->LUT[x-1] + histeq->in_histogram[x];                // 0.0
/*98  */     /* Normalize */                                                                 // 0.0
/*100 */     for (x = 0; x < 256; x++)                                                       // 0.0
/*102 */         histeq->LUT[x] = (histeq->LUT[x] * intensity) / (inlink->h * inlink->w);    // 0.0
/*106 */     /* Adjust the LUT based on the selected strength. This is an alpha              // 0.0
/*108 */        mix of the calculated LUT and a linear LUT with gain 1. */                   // 0.0
/*110 */     for (x = 0; x < 256; x++)                                                       // 0.0
/*112 */         histeq->LUT[x] = (strength * histeq->LUT[x]) / 255 +                        // 0.0
/*114 */                          ((255 - strength) * x)      / 255;                         // 0.0
/*118 */     /* Output the equalized frame. */                                               // 0.0
/*120 */     memset(histeq->out_histogram, 0, sizeof(histeq->out_histogram));                // 0.0
/*124 */     src = inpic->data[0];                                                           // 0.0
/*126 */     dst = outpic->data[0];                                                          // 0.0
/*128 */     for (y = 0; y < inlink->h; y++) {                                               // 0.0
/*130 */         for (x = 0; x < inlink->w * histeq->bpp; x += histeq->bpp) {                // 0.0
/*132 */             luma = dst[x + histeq->rgba_map[A]];                                    // 0.0
/*134 */             if (luma == 0) {                                                        // 0.0
/*136 */                 for (i = 0; i < histeq->bpp; ++i)                                   // 0.0
/*138 */                     dst[x + i] = 0;                                                 // 0.0
/*140 */                 histeq->out_histogram[0]++;                                         // 0.0
/*142 */             } else {                                                                // 0.0
/*144 */                 lut = histeq->LUT[luma];                                            // 0.0
/*146 */                 if (histeq->antibanding != HISTEQ_ANTIBANDING_NONE) {               // 0.0
/*148 */                     if (luma > 0) {                                                 // 0.0
/*150 */                         lutlo = histeq->antibanding == HISTEQ_ANTIBANDING_WEAK ?    // 0.0
/*152 */                                 (histeq->LUT[luma] + histeq->LUT[luma - 1]) / 2 :   // 0.0
/*154 */                                  histeq->LUT[luma - 1];                             // 0.0
/*156 */                     } else                                                          // 0.0
/*158 */                         lutlo = lut;                                                // 0.0
/*162 */                     if (luma < 255) {                                               // 0.0
/*164 */                         luthi = (histeq->antibanding == HISTEQ_ANTIBANDING_WEAK) ?  // 0.0
/*166 */                             (histeq->LUT[luma] + histeq->LUT[luma + 1]) / 2 :       // 0.0
/*168 */                              histeq->LUT[luma + 1];                                 // 0.0
/*170 */                     } else                                                          // 0.0
/*172 */                         luthi = lut;                                                // 0.0
/*176 */                     if (lutlo != luthi) {                                           // 0.0
/*178 */                         jran = LCG(jran);                                           // 0.0
/*180 */                         lut = lutlo + ((luthi - lutlo + 1) * jran) / LCG_M;         // 0.0
/*182 */                     }                                                               // 0.0
/*184 */                 }                                                                   // 0.0
/*188 */                 GET_RGB_VALUES(r, g, b, src, histeq->rgba_map);                     // 0.0
/*190 */                 if (((m = FFMAX3(r, g, b)) * lut) / luma > 255) {                   // 0.0
/*192 */                     r = (r * 255) / m;                                              // 0.0
/*194 */                     g = (g * 255) / m;                                              // 0.0
/*196 */                     b = (b * 255) / m;                                              // 0.0
/*198 */                 } else {                                                            // 0.0
/*200 */                     r = (r * lut) / luma;                                           // 0.0
/*202 */                     g = (g * lut) / luma;                                           // 0.0
/*204 */                     b = (b * lut) / luma;                                           // 0.0
/*206 */                 }                                                                   // 0.0
/*208 */                 dst[x + histeq->rgba_map[R]] = r;                                   // 0.0
/*210 */                 dst[x + histeq->rgba_map[G]] = g;                                   // 0.0
/*212 */                 dst[x + histeq->rgba_map[B]] = b;                                   // 0.0
/*214 */                 oluma = (55 * r + 182 * g + 19 * b) >> 8;                           // 0.0
/*216 */                 histeq->out_histogram[oluma]++;                                     // 0.0
/*218 */             }                                                                       // 0.0
/*220 */         }                                                                           // 0.0
/*222 */         src += inpic->linesize[0];                                                  // 0.0
/*224 */         dst += outpic->linesize[0];                                                 // 0.0
/*226 */     }                                                                               // 0.0
/*228 */ #ifdef DEBUG                                                                        // 0.0
/*230 */     for (x = 0; x < 256; x++)                                                       // 0.0
/*232 */         av_dlog(ctx, "out[%d]: %u\n", x, histeq->out_histogram[x]);                 // 0.0
/*234 */ #endif                                                                              // 0.0
/*238 */     av_frame_free(&inpic);                                                          // 0.0
/*240 */     return ff_filter_frame(outlink, outpic);                                        // 0.0
/*242 */ }                                                                                   // 0.0
