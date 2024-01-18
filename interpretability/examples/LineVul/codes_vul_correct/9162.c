// commit message FFmpeg@366ac22ea5 (target=1, prob=0.9991555, correct=True): indeo5: prevent null pointer dereference on broken files
/*0  */ static int decode_mb_info(IVI5DecContext *ctx, IVIBandDesc *band,                                  // (7) 0.04492
/*1  */                           IVITile *tile, AVCodecContext *avctx)                                    // (1) 0.07617
/*2  */ {                                                                                                  // (19) 0.001953
/*3  */     int         x, y, mv_x, mv_y, mv_delta, offs, mb_offset,                                       // (0) 0.07812
/*4  */                 mv_scale, blks_per_mb;                                                             // (6) 0.05273
/*5  */     IVIMbInfo   *mb, *ref_mb;                                                                      // (13) 0.0332
/*6  */     int         row_offset = band->mb_size * band->pitch;                                          // (5) 0.05273
/*7  */     mb     = tile->mbs;                                                                            // (14) 0.0293
/*8  */     ref_mb = tile->ref_mbs;                                                                        // (17) 0.02734
/*9  */     offs   = tile->ypos * band->pitch + tile->xpos;                                                // (9) 0.04492
/*10 */     /* scale factor for motion vectors */                                                          // (18) 0.01953
/*11 */     mv_scale = (ctx->planes[0].bands[0].mb_size >> 3) - (band->mb_size >> 3);                      // (3) 0.06836
/*12 */     mv_x = mv_y = 0;                                                                               // (15) 0.0293
/*13 */     for (y = tile->ypos; y < (tile->ypos + tile->height); y += band->mb_size) {                    // (4) 0.06445
/*14 */         mb_offset = offs;                                                                          // (16) 0.0293
/*15 */         for (x = tile->xpos; x < (tile->xpos + tile->width); x += band->mb_size) {                 // (2) 0.07227
/*16 */             mb->xpos     = x;                                                                      // (11) 0.04492
/*17 */             mb->ypos     = y;                                                                      // (12) 0.04492
/*18 */             mb->buf_offs = mb_offset;                                                              // (10) 0.04492
/*19 */             if (get_bits1(&ctx->gb)) {                                                             // (8) 0.04492
/*20 */                 if (ctx->frame_type == FRAMETYPE_INTRA) {                                          // 0.0
/*21 */                     av_log(avctx, AV_LOG_ERROR, "Empty macroblock in an INTRA picture!\n");        // 0.0
/*22 */                     return -1;                                                                     // 0.0
/*23 */                 }                                                                                  // 0.0
/*24 */                 mb->type = 1; /* empty macroblocks are always INTER */                             // 0.0
/*25 */                 mb->cbp  = 0; /* all blocks are empty */                                           // 0.0
/*26 */                 mb->q_delta = 0;                                                                   // 0.0
/*27 */                 if (!band->plane && !band->band_num && (ctx->frame_flags & 8)) {                   // 0.0
/*28 */                     mb->q_delta = get_vlc2(&ctx->gb, ctx->mb_vlc.tab->table,                       // 0.0
/*29 */                                            IVI_VLC_BITS, 1);                                       // 0.0
/*30 */                     mb->q_delta = IVI_TOSIGNED(mb->q_delta);                                       // 0.0
/*31 */                 }                                                                                  // 0.0
/*32 */                 mb->mv_x = mb->mv_y = 0; /* no motion vector coded */                              // 0.0
/*33 */                 if (band->inherit_mv){                                                             // 0.0
/*34 */                     /* motion vector inheritance */                                                // 0.0
/*35 */                     if (mv_scale) {                                                                // 0.0
/*36 */                         mb->mv_x = ivi_scale_mv(ref_mb->mv_x, mv_scale);                           // 0.0
/*37 */                         mb->mv_y = ivi_scale_mv(ref_mb->mv_y, mv_scale);                           // 0.0
/*38 */                     } else {                                                                       // 0.0
/*39 */                         mb->mv_x = ref_mb->mv_x;                                                   // 0.0
/*40 */                         mb->mv_y = ref_mb->mv_y;                                                   // 0.0
/*41 */                     }                                                                              // 0.0
/*42 */                 }                                                                                  // 0.0
/*43 */             } else {                                                                               // 0.0
/*44 */                 if (band->inherit_mv) {                                                            // 0.0
/*45 */                     mb->type = ref_mb->type; /* copy mb_type from corresponding reference mb */    // 0.0
/*46 */                 } else if (ctx->frame_type == FRAMETYPE_INTRA) {                                   // 0.0
/*47 */                     mb->type = 0; /* mb_type is always INTRA for intra-frames */                   // 0.0
/*48 */                 } else {                                                                           // 0.0
/*49 */                     mb->type = get_bits1(&ctx->gb);                                                // 0.0
/*50 */                 }                                                                                  // 0.0
/*51 */                 blks_per_mb = band->mb_size != band->blk_size ? 4 : 1;                             // 0.0
/*52 */                 mb->cbp = get_bits(&ctx->gb, blks_per_mb);                                         // 0.0
/*53 */                 mb->q_delta = 0;                                                                   // 0.0
/*54 */                 if (band->qdelta_present) {                                                        // 0.0
/*55 */                     if (band->inherit_qdelta) {                                                    // 0.0
/*56 */                         if (ref_mb) mb->q_delta = ref_mb->q_delta;                                 // 0.0
/*57 */                     } else if (mb->cbp || (!band->plane && !band->band_num &&                      // 0.0
/*58 */                                            (ctx->frame_flags & 8))) {                              // 0.0
/*59 */                         mb->q_delta = get_vlc2(&ctx->gb, ctx->mb_vlc.tab->table,                   // 0.0
/*60 */                                                IVI_VLC_BITS, 1);                                   // 0.0
/*61 */                         mb->q_delta = IVI_TOSIGNED(mb->q_delta);                                   // 0.0
/*62 */                     }                                                                              // 0.0
/*63 */                 }                                                                                  // 0.0
/*64 */                 if (!mb->type) {                                                                   // 0.0
/*65 */                     mb->mv_x = mb->mv_y = 0; /* there is no motion vector in intra-macroblocks */  // 0.0
/*66 */                 } else {                                                                           // 0.0
/*67 */                     if (band->inherit_mv){                                                         // 0.0
/*68 */                         /* motion vector inheritance */                                            // 0.0
/*69 */                         if (mv_scale) {                                                            // 0.0
/*70 */                             mb->mv_x = ivi_scale_mv(ref_mb->mv_x, mv_scale);                       // 0.0
/*71 */                             mb->mv_y = ivi_scale_mv(ref_mb->mv_y, mv_scale);                       // 0.0
/*72 */                         } else {                                                                   // 0.0
/*73 */                             mb->mv_x = ref_mb->mv_x;                                               // 0.0
/*74 */                             mb->mv_y = ref_mb->mv_y;                                               // 0.0
/*75 */                         }                                                                          // 0.0
/*76 */                     } else {                                                                       // 0.0
/*77 */                         /* decode motion vector deltas */                                          // 0.0
/*78 */                         mv_delta = get_vlc2(&ctx->gb, ctx->mb_vlc.tab->table,                      // 0.0
/*79 */                                             IVI_VLC_BITS, 1);                                      // 0.0
/*80 */                         mv_y += IVI_TOSIGNED(mv_delta);                                            // 0.0
/*81 */                         mv_delta = get_vlc2(&ctx->gb, ctx->mb_vlc.tab->table,                      // 0.0
/*82 */                                             IVI_VLC_BITS, 1);                                      // 0.0
/*83 */                         mv_x += IVI_TOSIGNED(mv_delta);                                            // 0.0
/*84 */                         mb->mv_x = mv_x;                                                           // 0.0
/*85 */                         mb->mv_y = mv_y;                                                           // 0.0
/*86 */                     }                                                                              // 0.0
/*87 */                 }                                                                                  // 0.0
/*88 */             }                                                                                      // 0.0
/*89 */             mb++;                                                                                  // 0.0
/*90 */             if (ref_mb)                                                                            // 0.0
/*91 */                 ref_mb++;                                                                          // 0.0
/*92 */             mb_offset += band->mb_size;                                                            // 0.0
/*93 */         }                                                                                          // 0.0
/*94 */         offs += row_offset;                                                                        // 0.0
/*95 */     }                                                                                              // 0.0
/*96 */     align_get_bits(&ctx->gb);                                                                      // 0.0
/*97 */     return 0;                                                                                      // 0.0
/*98 */ }                                                                                                  // 0.0
