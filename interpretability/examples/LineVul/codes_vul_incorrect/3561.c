// commit message FFmpeg@3d5822d9cf (target=1, prob=0.31625065, correct=False): avcodec/jpeg2000: Dynamically allocate codeblock data
/*0   */ static int jpeg2000_decode_packet(Jpeg2000DecoderContext *s, Jpeg2000Tile *tile, int *tp_index,                  // (3) 0.06641
/*2   */                                   Jpeg2000CodingStyle *codsty,                                                   // (2) 0.08398
/*4   */                                   Jpeg2000ResLevel *rlevel, int precno,                                          // (1) 0.08984
/*6   */                                   int layno, uint8_t *expn, int numgbits)                                        // (0) 0.09766
/*8   */ {                                                                                                                // (20) 0.001954
/*10  */     int bandno, cblkno, ret, nb_code_blocks;                                                                     // (11) 0.04102
/*12  */     int cwsno;                                                                                                   // (16) 0.01562
/*16  */     if (layno < rlevel->band[0].prec[precno].decoded_layers)                                                     // (10) 0.05469
/*18  */         return 0;                                                                                                // (15) 0.01953
/*20  */     rlevel->band[0].prec[precno].decoded_layers = layno + 1;                                                     // (9) 0.05469
/*24  */     if (bytestream2_get_bytes_left(&s->g) == 0 && s->bit_index == 8) {                                           // (6) 0.0625
/*26  */         if (*tp_index < FF_ARRAY_ELEMS(tile->tile_part) - 1) {                                                   // (5) 0.0625
/*28  */             s->g = tile->tile_part[++(*tp_index)].tpg;                                                           // (7) 0.05859
/*30  */         }                                                                                                        // (17) 0.01562
/*32  */     }                                                                                                            // (18) 0.007813
/*36  */     if (bytestream2_peek_be32(&s->g) == JPEG2000_SOP_FIXED_BYTES)                                                // (4) 0.06641
/*38  */         bytestream2_skip(&s->g, JPEG2000_SOP_BYTE_LENGTH);                                                       // (8) 0.05859
/*42  */     if (!(ret = get_bits(s, 1))) {                                                                               // (12) 0.0332
/*44  */         jpeg2000_flush(s);                                                                                       // (13) 0.0293
/*46  */         return 0;                                                                                                // (14) 0.01953
/*48  */     } else if (ret < 0)                                                                                          // 0.0
/*50  */         return ret;                                                                                              // 0.0
/*54  */     for (bandno = 0; bandno < rlevel->nbands; bandno++) {                                                        // 0.0
/*56  */         Jpeg2000Band *band = rlevel->band + bandno;                                                              // 0.0
/*58  */         Jpeg2000Prec *prec = band->prec + precno;                                                                // 0.0
/*62  */         if (band->coord[0][0] == band->coord[0][1] ||                                                            // 0.0
/*64  */             band->coord[1][0] == band->coord[1][1])                                                              // 0.0
/*66  */             continue;                                                                                            // 0.0
/*68  */         nb_code_blocks =  prec->nb_codeblocks_height *                                                           // 0.0
/*70  */                           prec->nb_codeblocks_width;                                                             // 0.0
/*72  */         for (cblkno = 0; cblkno < nb_code_blocks; cblkno++) {                                                    // 0.0
/*74  */             Jpeg2000Cblk *cblk = prec->cblk + cblkno;                                                            // 0.0
/*76  */             int incl, newpasses, llen;                                                                           // 0.0
/*80  */             if (cblk->npasses)                                                                                   // 0.0
/*82  */                 incl = get_bits(s, 1);                                                                           // 0.0
/*84  */             else                                                                                                 // 0.0
/*86  */                 incl = tag_tree_decode(s, prec->cblkincl + cblkno, layno + 1) == layno;                          // 0.0
/*88  */             if (!incl)                                                                                           // 0.0
/*90  */                 continue;                                                                                        // 0.0
/*92  */             else if (incl < 0)                                                                                   // 0.0
/*94  */                 return incl;                                                                                     // 0.0
/*98  */             if (!cblk->npasses) {                                                                                // 0.0
/*100 */                 int v = expn[bandno] + numgbits - 1 -                                                            // 0.0
/*102 */                         tag_tree_decode(s, prec->zerobits + cblkno, 100);                                        // 0.0
/*104 */                 if (v < 0 || v > 30) {                                                                           // 0.0
/*106 */                     av_log(s->avctx, AV_LOG_ERROR,                                                               // 0.0
/*108 */                            "nonzerobits %d invalid or unsupported\n", v);                                        // 0.0
/*110 */                     return AVERROR_INVALIDDATA;                                                                  // 0.0
/*112 */                 }                                                                                                // 0.0
/*114 */                 cblk->nonzerobits = v;                                                                           // 0.0
/*116 */             }                                                                                                    // 0.0
/*118 */             if ((newpasses = getnpasses(s)) < 0)                                                                 // 0.0
/*120 */                 return newpasses;                                                                                // 0.0
/*122 */             av_assert2(newpasses > 0);                                                                           // 0.0
/*124 */             if (cblk->npasses + newpasses >= JPEG2000_MAX_PASSES) {                                              // 0.0
/*126 */                 avpriv_request_sample(s->avctx, "Too many passes");                                              // 0.0
/*128 */                 return AVERROR_PATCHWELCOME;                                                                     // 0.0
/*130 */             }                                                                                                    // 0.0
/*132 */             if ((llen = getlblockinc(s)) < 0)                                                                    // 0.0
/*134 */                 return llen;                                                                                     // 0.0
/*136 */             if (cblk->lblock + llen + av_log2(newpasses) > 16) {                                                 // 0.0
/*138 */                 avpriv_request_sample(s->avctx,                                                                  // 0.0
/*140 */                                       "Block with length beyond 16 bits");                                       // 0.0
/*142 */                 return AVERROR_PATCHWELCOME;                                                                     // 0.0
/*144 */             }                                                                                                    // 0.0
/*148 */             cblk->lblock += llen;                                                                                // 0.0
/*152 */             cblk->nb_lengthinc = 0;                                                                              // 0.0
/*154 */             cblk->nb_terminationsinc = 0;                                                                        // 0.0
/*156 */             do {                                                                                                 // 0.0
/*158 */                 int newpasses1 = 0;                                                                              // 0.0
/*162 */                 while (newpasses1 < newpasses) {                                                                 // 0.0
/*164 */                     newpasses1 ++;                                                                               // 0.0
/*166 */                     if (needs_termination(codsty->cblk_style, cblk->npasses + newpasses1 - 1)) {                 // 0.0
/*168 */                         cblk->nb_terminationsinc ++;                                                             // 0.0
/*170 */                         break;                                                                                   // 0.0
/*172 */                     }                                                                                            // 0.0
/*174 */                 }                                                                                                // 0.0
/*178 */                 if ((ret = get_bits(s, av_log2(newpasses1) + cblk->lblock)) < 0)                                 // 0.0
/*180 */                     return ret;                                                                                  // 0.0
/*182 */                 if (ret > sizeof(cblk->data)) {                                                                  // 0.0
/*184 */                     avpriv_request_sample(s->avctx,                                                              // 0.0
/*186 */                                         "Block with lengthinc greater than %"SIZE_SPECIFIER"",                   // 0.0
/*188 */                                         sizeof(cblk->data));                                                     // 0.0
/*190 */                     return AVERROR_PATCHWELCOME;                                                                 // 0.0
/*192 */                 }                                                                                                // 0.0
/*194 */                 cblk->lengthinc[cblk->nb_lengthinc++] = ret;                                                     // 0.0
/*196 */                 cblk->npasses  += newpasses1;                                                                    // 0.0
/*198 */                 newpasses -= newpasses1;                                                                         // 0.0
/*200 */             } while(newpasses);                                                                                  // 0.0
/*202 */         }                                                                                                        // 0.0
/*204 */     }                                                                                                            // (19) 0.007812
/*206 */     jpeg2000_flush(s);                                                                                           // 0.0
/*210 */     if (codsty->csty & JPEG2000_CSTY_EPH) {                                                                      // 0.0
/*212 */         if (bytestream2_peek_be16(&s->g) == JPEG2000_EPH)                                                        // 0.0
/*214 */             bytestream2_skip(&s->g, 2);                                                                          // 0.0
/*216 */         else                                                                                                     // 0.0
/*218 */             av_log(s->avctx, AV_LOG_ERROR, "EPH marker not found. instead %X\n", bytestream2_peek_be32(&s->g));  // 0.0
/*220 */     }                                                                                                            // 0.0
/*224 */     for (bandno = 0; bandno < rlevel->nbands; bandno++) {                                                        // 0.0
/*226 */         Jpeg2000Band *band = rlevel->band + bandno;                                                              // 0.0
/*228 */         Jpeg2000Prec *prec = band->prec + precno;                                                                // 0.0
/*232 */         nb_code_blocks = prec->nb_codeblocks_height * prec->nb_codeblocks_width;                                 // 0.0
/*234 */         for (cblkno = 0; cblkno < nb_code_blocks; cblkno++) {                                                    // 0.0
/*236 */             Jpeg2000Cblk *cblk = prec->cblk + cblkno;                                                            // 0.0
/*238 */             for (cwsno = 0; cwsno < cblk->nb_lengthinc; cwsno ++) {                                              // 0.0
/*240 */                 if (   bytestream2_get_bytes_left(&s->g) < cblk->lengthinc[cwsno]                                // 0.0
/*242 */                     || sizeof(cblk->data) < cblk->length + cblk->lengthinc[cwsno] + 4                            // 0.0
/*244 */                 ) {                                                                                              // 0.0
/*246 */                     av_log(s->avctx, AV_LOG_ERROR,                                                               // 0.0
/*248 */                         "Block length %"PRIu16" or lengthinc %d is too large, left %d\n",                        // 0.0
/*250 */                         cblk->length, cblk->lengthinc[cwsno], bytestream2_get_bytes_left(&s->g));                // 0.0
/*252 */                     return AVERROR_INVALIDDATA;                                                                  // 0.0
/*254 */                 }                                                                                                // 0.0
/*258 */                 bytestream2_get_bufferu(&s->g, cblk->data + cblk->length, cblk->lengthinc[cwsno]);               // 0.0
/*260 */                 cblk->length   += cblk->lengthinc[cwsno];                                                        // 0.0
/*262 */                 cblk->lengthinc[cwsno] = 0;                                                                      // 0.0
/*264 */                 if (cblk->nb_terminationsinc) {                                                                  // 0.0
/*266 */                     cblk->nb_terminationsinc--;                                                                  // 0.0
/*268 */                     cblk->nb_terminations++;                                                                     // 0.0
/*270 */                     cblk->data[cblk->length++] = 0xFF;                                                           // 0.0
/*272 */                     cblk->data[cblk->length++] = 0xFF;                                                           // 0.0
/*274 */                     cblk->data_start[cblk->nb_terminations] = cblk->length;                                      // 0.0
/*276 */                 }                                                                                                // 0.0
/*278 */             }                                                                                                    // 0.0
/*280 */         }                                                                                                        // 0.0
/*282 */     }                                                                                                            // 0.0
/*284 */     return 0;                                                                                                    // 0.0
/*286 */ }                                                                                                                // 0.0
