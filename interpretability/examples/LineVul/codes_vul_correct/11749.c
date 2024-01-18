// commit message FFmpeg@8bedbb82ce (target=1, prob=0.7837608, correct=True): j2k/jpeg2000: split data pointer in int & float.
/*0  */ static void copy_frame(Jpeg2000EncoderContext *s)                                              // (15) 0.0293
/*2  */ {                                                                                              // (18) 0.001954
/*4  */     int tileno, compno, i, y, x;                                                               // (13) 0.03125
/*6  */     uint8_t *line;                                                                             // (17) 0.01953
/*8  */     for (tileno = 0; tileno < s->numXtiles * s->numYtiles; tileno++){                          // (4) 0.06055
/*10 */         Jpeg2000Tile *tile = s->tile + tileno;                                                 // (12) 0.04102
/*12 */         if (s->planar){                                                                        // (16) 0.02734
/*14 */             for (compno = 0; compno < s->ncomponents; compno++){                               // (5) 0.06055
/*16 */                 Jpeg2000Component *comp = tile->comp + compno;                                 // (8) 0.05664
/*18 */                 int *dst = comp->data;                                                         // (11) 0.04687
/*20 */                 line = s->picture.data[compno]                                                 // (10) 0.05078
/*22 */                        + comp->coord[1][0] * s->picture.linesize[compno]                       // (1) 0.08203
/*24 */                        + comp->coord[0][0];                                                    // (7) 0.06055
/*26 */                 for (y = comp->coord[1][0]; y < comp->coord[1][1]; y++){                       // (2) 0.07812
/*28 */                     uint8_t *ptr = line;                                                       // (9) 0.05469
/*30 */                     for (x = comp->coord[0][0]; x < comp->coord[0][1]; x++)                    // (0) 0.08398
/*32 */                         *dst++ = *ptr++ - (1 << 7);                                            // (3) 0.07227
/*34 */                     line += s->picture.linesize[compno];                                       // (6) 0.06055
/*36 */                 }                                                                              // (14) 0.03125
/*38 */             }                                                                                  // 0.0
/*40 */         } else{                                                                                // 0.0
/*42 */             line = s->picture.data[0] + tile->comp[0].coord[1][0] * s->picture.linesize[0]     // 0.0
/*44 */                    + tile->comp[0].coord[0][0] * s->ncomponents;                               // 0.0
/*48 */             i = 0;                                                                             // 0.0
/*50 */             for (y = tile->comp[0].coord[1][0]; y < tile->comp[0].coord[1][1]; y++){           // 0.0
/*52 */                 uint8_t *ptr = line;                                                           // 0.0
/*54 */                 for (x = tile->comp[0].coord[0][0]; x < tile->comp[0].coord[0][1]; x++, i++){  // 0.0
/*56 */                     for (compno = 0; compno < s->ncomponents; compno++){                       // 0.0
/*58 */                         tile->comp[compno].data[i] = *ptr++  - (1 << 7);                       // 0.0
/*60 */                     }                                                                          // 0.0
/*62 */                 }                                                                              // 0.0
/*64 */                 line += s->picture.linesize[0];                                                // 0.0
/*66 */             }                                                                                  // 0.0
/*68 */         }                                                                                      // 0.0
/*70 */     }                                                                                          // 0.0
/*72 */ }                                                                                              // 0.0
