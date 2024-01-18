// commit message FFmpeg@fe448cd28d (target=0, prob=0.76383275, correct=False): avcodec/jpeg2000dec: prevent out of array accesses in pixel addressing
/*0   */ static int jpeg2000_decode_tile(Jpeg2000DecoderContext *s, Jpeg2000Tile *tile,                                     // (7) 0.03421
/*2   */                                 AVFrame *picture)                                                                  // (1) 0.04448
/*4   */ {                                                                                                                  // (20) 0.008481
/*6   */     int compno, reslevelno, bandno;                                                                                // (15) 0.01738
/*8   */     int x, y;                                                                                                      // (19) 0.009457
/*12  */     uint8_t *line;                                                                                                 // (18) 0.01186
/*14  */     Jpeg2000T1Context t1;                                                                                          // (17) 0.01591
/*18  */     /* Loop on tile components */                                                                                  // (13) 0.021
/*20  */     for (compno = 0; compno < s->ncomponents; compno++) {                                                          // (12) 0.02782
/*22  */         Jpeg2000Component *comp     = tile->comp + compno;                                                         // (11) 0.02896
/*24  */         Jpeg2000CodingStyle *codsty = tile->codsty + compno;                                                       // (10) 0.02915
/*28  */         /* Loop on resolution levels */                                                                            // (16) 0.01642
/*30  */         for (reslevelno = 0; reslevelno < codsty->nreslevels2decode; reslevelno++) {                               // (2) 0.04189
/*32  */             Jpeg2000ResLevel *rlevel = comp->reslevel + reslevelno;                                                // (8) 0.03321
/*34  */             /* Loop on bands */                                                                                    // (14) 0.01881
/*36  */             for (bandno = 0; bandno < rlevel->nbands; bandno++) {                                                  // (4) 0.0402
/*38  */                 int nb_precincts, precno;                                                                          // (0) 0.3642
/*40  */                 Jpeg2000Band *band = rlevel->band + bandno;                                                        // (5) 0.03766
/*42  */                 int cblkno = 0, bandpos;                                                                           // (9) 0.03316
/*46  */                 bandpos = bandno + (reslevelno > 0);                                                               // (6) 0.03447
/*50  */                 if (band->coord[0][0] == band->coord[0][1] ||                                                      // (3) 0.04091
/*52  */                     band->coord[1][0] == band->coord[1][1])                                                        // 0.0
/*54  */                     continue;                                                                                      // 0.0
/*58  */                 nb_precincts = rlevel->num_precincts_x * rlevel->num_precincts_y;                                  // 0.0
/*60  */                 /* Loop on precincts */                                                                            // 0.0
/*62  */                 for (precno = 0; precno < nb_precincts; precno++) {                                                // 0.0
/*64  */                     Jpeg2000Prec *prec = band->prec + precno;                                                      // 0.0
/*68  */                     /* Loop on codeblocks */                                                                       // 0.0
/*70  */                     for (cblkno = 0; cblkno < prec->nb_codeblocks_width * prec->nb_codeblocks_height; cblkno++) {  // 0.0
/*72  */                         int x, y;                                                                                  // 0.0
/*74  */                         Jpeg2000Cblk *cblk = prec->cblk + cblkno;                                                  // 0.0
/*76  */                         decode_cblk(s, codsty, &t1, cblk,                                                          // 0.0
/*78  */                                     cblk->coord[0][1] - cblk->coord[0][0],                                         // 0.0
/*80  */                                     cblk->coord[1][1] - cblk->coord[1][0],                                         // 0.0
/*82  */                                     bandpos);                                                                      // 0.0
/*86  */                         x = cblk->coord[0][0];                                                                     // 0.0
/*88  */                         y = cblk->coord[1][0];                                                                     // 0.0
/*92  */                         if (codsty->transform == FF_DWT97)                                                         // 0.0
/*94  */                             dequantization_float(x, y, cblk, comp, &t1, band);                                     // 0.0
/*96  */                         else                                                                                       // 0.0
/*98  */                             dequantization_int(x, y, cblk, comp, &t1, band);                                       // 0.0
/*100 */                    } /* end cblk */                                                                                // 0.0
/*102 */                 } /*end prec */                                                                                    // 0.0
/*104 */             } /* end band */                                                                                       // 0.0
/*106 */         } /* end reslevel */                                                                                       // 0.0
/*110 */         /* inverse DWT */                                                                                          // 0.0
/*112 */         ff_dwt_decode(&comp->dwt, codsty->transform == FF_DWT97 ? (void*)comp->f_data : (void*)comp->i_data);      // 0.0
/*114 */     } /*end comp */                                                                                                // 0.0
/*118 */     /* inverse MCT transformation */                                                                               // 0.0
/*120 */     if (tile->codsty[0].mct)                                                                                       // 0.0
/*122 */         mct_decode(s, tile);                                                                                       // 0.0
/*126 */     if (s->cdef[0] < 0) {                                                                                          // 0.0
/*128 */         for (x = 0; x < s->ncomponents; x++)                                                                       // 0.0
/*130 */             s->cdef[x] = x + 1;                                                                                    // 0.0
/*132 */         if ((s->ncomponents & 1) == 0)                                                                             // 0.0
/*134 */             s->cdef[s->ncomponents-1] = 0;                                                                         // 0.0
/*136 */     }                                                                                                              // 0.0
/*140 */     if (s->precision <= 8) {                                                                                       // 0.0
/*142 */         for (compno = 0; compno < s->ncomponents; compno++) {                                                      // 0.0
/*144 */             Jpeg2000Component *comp = tile->comp + compno;                                                         // 0.0
/*146 */             Jpeg2000CodingStyle *codsty = tile->codsty + compno;                                                   // 0.0
/*148 */             float *datap = comp->f_data;                                                                           // 0.0
/*150 */             int32_t *i_datap = comp->i_data;                                                                       // 0.0
/*152 */             int cbps = s->cbps[compno];                                                                            // 0.0
/*154 */             int w = tile->comp[compno].coord[0][1] - s->image_offset_x;                                            // 0.0
/*156 */             int planar = !!picture->data[2];                                                                       // 0.0
/*158 */             int pixelsize = planar ? 1 : s->ncomponents;                                                           // 0.0
/*160 */             int plane = 0;                                                                                         // 0.0
/*164 */             if (planar)                                                                                            // 0.0
/*166 */                 plane = s->cdef[compno] ? s->cdef[compno]-1 : (s->ncomponents-1);                                  // 0.0
/*172 */             y    = tile->comp[compno].coord[1][0] - s->image_offset_y;                                             // 0.0
/*174 */             line = picture->data[plane] + y * picture->linesize[plane];                                            // 0.0
/*176 */             for (; y < tile->comp[compno].coord[1][1] - s->image_offset_y; y += s->cdy[compno]) {                  // 0.0
/*178 */                 uint8_t *dst;                                                                                      // 0.0
/*182 */                 x   = tile->comp[compno].coord[0][0] - s->image_offset_x;                                          // 0.0
/*184 */                 dst = line + x * pixelsize + compno*!planar;                                                       // 0.0
/*188 */                 if (codsty->transform == FF_DWT97) {                                                               // 0.0
/*190 */                     for (; x < w; x += s->cdx[compno]) {                                                           // 0.0
/*192 */                         int val = lrintf(*datap) + (1 << (cbps - 1));                                              // 0.0
/*194 */                         /* DC level shift and clip see ISO 15444-1:2002 G.1.2 */                                   // 0.0
/*196 */                         val = av_clip(val, 0, (1 << cbps) - 1);                                                    // 0.0
/*198 */                         *dst = val << (8 - cbps);                                                                  // 0.0
/*200 */                         datap++;                                                                                   // 0.0
/*202 */                         dst += pixelsize;                                                                          // 0.0
/*204 */                     }                                                                                              // 0.0
/*206 */                 } else {                                                                                           // 0.0
/*208 */                     for (; x < w; x += s->cdx[compno]) {                                                           // 0.0
/*210 */                         int val = *i_datap + (1 << (cbps - 1));                                                    // 0.0
/*212 */                         /* DC level shift and clip see ISO 15444-1:2002 G.1.2 */                                   // 0.0
/*214 */                         val = av_clip(val, 0, (1 << cbps) - 1);                                                    // 0.0
/*216 */                         *dst = val << (8 - cbps);                                                                  // 0.0
/*218 */                         i_datap++;                                                                                 // 0.0
/*220 */                         dst += pixelsize;                                                                          // 0.0
/*222 */                     }                                                                                              // 0.0
/*224 */                 }                                                                                                  // 0.0
/*226 */                 line += picture->linesize[plane];                                                                  // 0.0
/*228 */             }                                                                                                      // 0.0
/*230 */         }                                                                                                          // 0.0
/*232 */     } else {                                                                                                       // 0.0
/*234 */         for (compno = 0; compno < s->ncomponents; compno++) {                                                      // 0.0
/*236 */             Jpeg2000Component *comp = tile->comp + compno;                                                         // 0.0
/*238 */             Jpeg2000CodingStyle *codsty = tile->codsty + compno;                                                   // 0.0
/*240 */             float *datap = comp->f_data;                                                                           // 0.0
/*242 */             int32_t *i_datap = comp->i_data;                                                                       // 0.0
/*244 */             uint16_t *linel;                                                                                       // 0.0
/*246 */             int cbps = s->cbps[compno];                                                                            // 0.0
/*248 */             int w = tile->comp[compno].coord[0][1] - s->image_offset_x;                                            // 0.0
/*250 */             int planar = !!picture->data[2];                                                                       // 0.0
/*252 */             int pixelsize = planar ? 1 : s->ncomponents;                                                           // 0.0
/*254 */             int plane = 0;                                                                                         // 0.0
/*258 */             if (planar)                                                                                            // 0.0
/*260 */                 plane = s->cdef[compno] ? s->cdef[compno]-1 : (s->ncomponents-1);                                  // 0.0
/*264 */             y     = tile->comp[compno].coord[1][0] - s->image_offset_y;                                            // 0.0
/*266 */             linel = (uint16_t *)picture->data[plane] + y * (picture->linesize[plane] >> 1);                        // 0.0
/*268 */             for (; y < tile->comp[compno].coord[1][1] - s->image_offset_y; y += s->cdy[compno]) {                  // 0.0
/*270 */                 uint16_t *dst;                                                                                     // 0.0
/*274 */                 x   = tile->comp[compno].coord[0][0] - s->image_offset_x;                                          // 0.0
/*276 */                 dst = linel + (x * pixelsize + compno*!planar);                                                    // 0.0
/*278 */                 if (codsty->transform == FF_DWT97) {                                                               // 0.0
/*280 */                     for (; x < w; x += s-> cdx[compno]) {                                                          // 0.0
/*282 */                         int  val = lrintf(*datap) + (1 << (cbps - 1));                                             // 0.0
/*284 */                         /* DC level shift and clip see ISO 15444-1:2002 G.1.2 */                                   // 0.0
/*286 */                         val = av_clip(val, 0, (1 << cbps) - 1);                                                    // 0.0
/*288 */                         /* align 12 bit values in little-endian mode */                                            // 0.0
/*290 */                         *dst = val << (16 - cbps);                                                                 // 0.0
/*292 */                         datap++;                                                                                   // 0.0
/*294 */                         dst += pixelsize;                                                                          // 0.0
/*296 */                     }                                                                                              // 0.0
/*298 */                 } else {                                                                                           // 0.0
/*300 */                     for (; x < w; x += s-> cdx[compno]) {                                                          // 0.0
/*302 */                         int val = *i_datap + (1 << (cbps - 1));                                                    // 0.0
/*304 */                         /* DC level shift and clip see ISO 15444-1:2002 G.1.2 */                                   // 0.0
/*306 */                         val = av_clip(val, 0, (1 << cbps) - 1);                                                    // 0.0
/*308 */                         /* align 12 bit values in little-endian mode */                                            // 0.0
/*310 */                         *dst = val << (16 - cbps);                                                                 // 0.0
/*312 */                         i_datap++;                                                                                 // 0.0
/*314 */                         dst += pixelsize;                                                                          // 0.0
/*316 */                     }                                                                                              // 0.0
/*318 */                 }                                                                                                  // 0.0
/*320 */                 linel += picture->linesize[plane] >> 1;                                                            // 0.0
/*322 */             }                                                                                                      // 0.0
/*324 */         }                                                                                                          // 0.0
/*326 */     }                                                                                                              // 0.0
/*330 */     return 0;                                                                                                      // 0.0
/*332 */ }                                                                                                                  // 0.0
