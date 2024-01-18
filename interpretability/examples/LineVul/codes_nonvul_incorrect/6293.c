// commit message FFmpeg@859bb3cfee (target=0, prob=0.5046927, correct=False): Add more paranoid checks of xvmc token.
/*0   */ int ff_xvmc_field_start(MpegEncContext *s, AVCodecContext *avctx)                                    // (5) 0.05078
/*2   */ {                                                                                                    // (21) 0.001953
/*4   */     struct xvmc_pix_fmt *last, *next, *render = (struct xvmc_pix_fmt*)s->current_picture.data[2];    // (1) 0.08594
/*6   */     const int mb_block_count = 4 + (1 << s->chroma_format);                                          // (8) 0.04688
/*10  */     assert(avctx);                                                                                   // (18) 0.01562
/*12  */     if (!render || render->xvmc_id != AV_XVMC_ID ||                                                  // (9) 0.04492
/*14  */         !render->data_blocks || !render->mv_blocks) {                                                // (10) 0.04492
/*16  */         av_log(avctx, AV_LOG_ERROR,                                                                  // (12) 0.03906
/*18  */                "Render token doesn't look as expected.\n");                                          // (6) 0.05078
/*20  */         return -1; // make sure that this is a render packet                                         // (11) 0.03906
/*22  */     }                                                                                                // (19) 0.007812
/*26  */     if (render->filled_mv_blocks_num) {                                                              // (16) 0.0332
/*28  */         av_log(avctx, AV_LOG_ERROR,                                                                  // (13) 0.03906
/*30  */                "Rendering surface contains %i unprocessed blocks.\n",                                // (4) 0.05859
/*32  */                render->filled_mv_blocks_num);                                                        // (7) 0.04883
/*34  */         return -1;                                                                                   // (17) 0.02148
/*36  */     }                                                                                                // (20) 0.007812
/*38  */     if (render->allocated_mv_blocks   < 1 ||                                                         // (14) 0.03711
/*40  */         render->allocated_data_blocks <  render->allocated_mv_blocks*mb_block_count ||               // (2) 0.06445
/*42  */         render->start_mv_blocks_num   >= render->allocated_mv_blocks                ||               // (0) 0.08789
/*44  */         render->next_free_data_block_num >                                                           // (15) 0.03711
/*46  */                         render->allocated_data_blocks -                                              // (3) 0.0625
/*48  */                         mb_block_count*(render->allocated_mv_blocks-render->start_mv_blocks_num)) {  // 0.0
/*50  */         av_log(avctx, AV_LOG_ERROR,                                                                  // 0.0
/*52  */                "Rendering surface doesn't provide enough block structures to work with.\n");         // 0.0
/*54  */         return -1;                                                                                   // 0.0
/*56  */     }                                                                                                // 0.0
/*60  */     render->picture_structure = s->picture_structure;                                                // 0.0
/*62  */     render->flags             = s->first_field ? 0 : XVMC_SECOND_FIELD;                              // 0.0
/*64  */     render->p_future_surface  = NULL;                                                                // 0.0
/*66  */     render->p_past_surface    = NULL;                                                                // 0.0
/*70  */     switch(s->pict_type) {                                                                           // 0.0
/*72  */         case  FF_I_TYPE:                                                                             // 0.0
/*74  */             return 0; // no prediction from other frames                                             // 0.0
/*76  */         case  FF_B_TYPE:                                                                             // 0.0
/*78  */             next = (struct xvmc_pix_fmt*)s->next_picture.data[2];                                    // 0.0
/*80  */             if (!next)                                                                               // 0.0
/*82  */                 return -1;                                                                           // 0.0
/*84  */             if (next->xvmc_id != AV_XVMC_ID)                                                         // 0.0
/*86  */                 return -1;                                                                           // 0.0
/*88  */             render->p_future_surface = next->p_surface;                                              // 0.0
/*90  */             // no return here, going to set forward prediction                                       // 0.0
/*92  */         case  FF_P_TYPE:                                                                             // 0.0
/*94  */             last = (struct xvmc_pix_fmt*)s->last_picture.data[2];                                    // 0.0
/*96  */             if (!last)                                                                               // 0.0
/*98  */                 last = render; // predict second field from the first                                // 0.0
/*100 */             if (last->xvmc_id != AV_XVMC_ID)                                                         // 0.0
/*102 */                 return -1;                                                                           // 0.0
/*104 */             render->p_past_surface = last->p_surface;                                                // 0.0
/*106 */             return 0;                                                                                // 0.0
/*108 */     }                                                                                                // 0.0
/*112 */ return -1;                                                                                           // 0.0
/*114 */ }                                                                                                    // 0.0
