// commit message FFmpeg@221f902f1d (target=1, prob=0.7547584, correct=True): avfilter/vf_yadif: fix race condition
/*0  */ static int filter_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)              // (7) 0.05078
/*2  */ {                                                                                             // (20) 0.001953
/*4  */     YADIFContext *s = ctx->priv;                                                              // (14) 0.0293
/*6  */     ThreadData *td  = arg;                                                                    // (17) 0.02148
/*8  */     int refs = s->cur->linesize[td->plane];                                                   // (11) 0.03516
/*10 */     int df = (s->csp->comp[td->plane].depth_minus1 + 8) / 8;                                  // (6) 0.05469
/*12 */     int pix_3 = 3 * df;                                                                       // (16) 0.02539
/*14 */     int slice_h = td->h / nb_jobs;                                                            // (13) 0.0332
/*16 */     int slice_start = jobnr * slice_h;                                                        // (15) 0.0293
/*18 */     int slice_end   = (jobnr == nb_jobs - 1) ? td->h : (jobnr + 1) * slice_h;                 // (2) 0.07227
/*20 */     int y;                                                                                    // (18) 0.01172
/*24 */     /* filtering reads 3 pixels to the left/right; to avoid invalid reads,                    // (10) 0.03711
/*26 */      * we need to call the c variant which avoids this for border pixels                      // (12) 0.03516
/*28 */      */                                                                                       // (19) 0.009766
/*30 */     for (y = slice_start; y < slice_end; y++) {                                               // (9) 0.03906
/*32 */         if ((y ^ td->parity) & 1) {                                                           // (8) 0.03906
/*34 */             uint8_t *prev = &s->prev->data[td->plane][y * refs];                              // (4) 0.06641
/*36 */             uint8_t *cur  = &s->cur ->data[td->plane][y * refs];                              // (3) 0.06836
/*38 */             uint8_t *next = &s->next->data[td->plane][y * refs];                              // (5) 0.06641
/*40 */             uint8_t *dst  = &td->frame->data[td->plane][y * td->frame->linesize[td->plane]];  // (0) 0.08789
/*42 */             int     mode  = y == 1 || y + 2 == td->h ? 2 : s->mode;                           // (1) 0.07227
/*44 */             s->filter_line(dst + pix_3, prev + pix_3, cur + pix_3,                            // 0.0
/*46 */                            next + pix_3, td->w - 6,                                           // 0.0
/*48 */                            y + 1 < td->h ? refs : -refs,                                      // 0.0
/*50 */                            y ? -refs : refs,                                                  // 0.0
/*52 */                            td->parity ^ td->tff, mode);                                       // 0.0
/*54 */             s->filter_edges(dst, prev, cur, next, td->w,                                      // 0.0
/*56 */                             y + 1 < td->h ? refs : -refs,                                     // 0.0
/*58 */                             y ? -refs : refs,                                                 // 0.0
/*60 */                             td->parity ^ td->tff, mode);                                      // 0.0
/*62 */         } else {                                                                              // 0.0
/*64 */             memcpy(&td->frame->data[td->plane][y * td->frame->linesize[td->plane]],           // 0.0
/*66 */                    &s->cur->data[td->plane][y * refs], td->w * df);                           // 0.0
/*68 */         }                                                                                     // 0.0
/*70 */     }                                                                                         // 0.0
/*72 */     return 0;                                                                                 // 0.0
/*74 */ }                                                                                             // 0.0
