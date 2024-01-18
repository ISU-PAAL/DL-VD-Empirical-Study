// commit message FFmpeg@6f3d2fb18b (target=0, prob=0.15542845, correct=True): lavfi/vf_tile: switch to filter_frame.
/*0  */ static void end_last_frame(AVFilterContext *ctx)      // (7) 0.07216
/*2  */ {                                                     // (12) 0.005155
/*4  */     TileContext *tile    = ctx->priv;                 // (4) 0.08247
/*6  */     AVFilterLink *outlink = ctx->outputs[0];          // (3) 0.09278
/*8  */     AVFilterBufferRef *out_buf = outlink->out_buf;    // (2) 0.09794
/*12 */     outlink->out_buf = NULL;                          // (8) 0.06186
/*14 */     ff_start_frame(outlink, out_buf);                 // (5) 0.08247
/*16 */     while (tile->current < tile->nb_frames)           // (6) 0.07732
/*18 */         draw_blank_frame(ctx, out_buf);               // (1) 0.09794
/*20 */     ff_draw_slice(outlink, 0, out_buf->video->h, 1);  // (0) 0.1237
/*22 */     ff_end_frame(outlink);                            // (9) 0.06186
/*24 */     tile->current = 0;                                // (10) 0.04639
/*26 */ }                                                     // (11) 0.005155
