// commit message FFmpeg@24947d4988 (target=1, prob=0.6940269, correct=True): vorbis: fix overflows in floor1[] vector and inverse db table index.
/*0   */ static int vorbis_floor1_decode(vorbis_context *vc,                                                                           // (1) 0.04064
/*2   */                                 vorbis_floor_data *vfu, float *vec)                                                           // (10) 0.006571
/*4   */ {                                                                                                                             // (16) 0.003841
/*6   */     vorbis_floor1 *vf = &vfu->t1;                                                                                             // (8) 0.01016
/*8   */     GetBitContext *gb = &vc->gb;                                                                                              // (12) 0.005005
/*10  */     uint16_t range_v[4] = { 256, 128, 86, 64 };                                                                               // (17) 0.003196
/*12  */     unsigned range = range_v[vf->multiplier - 1];                                                                             // (14) 0.003972
/*14  */     uint16_t floor1_Y[258];                                                                                                   // (23) 0.001471
/*16  */     uint16_t floor1_Y_final[258];                                                                                             // (19) 0.002119
/*18  */     int floor1_flag[258];                                                                                                     // (22) 0.001644
/*20  */     unsigned class, cdim, cbits, csub, cval, offset, i, j;                                                                    // (9) 0.006895
/*22  */     int book, adx, ady, dy, off, predicted, err;                                                                              // (2) 0.0365
/*28  */     if (!get_bits1(gb)) // silence                                                                                            // (4) 0.0177
/*30  */         return 1;                                                                                                             // (7) 0.01053
/*34  */ // Read values (or differences) for the floor's points                                                                        // (0) 0.4635
/*38  */     floor1_Y[0] = get_bits(gb, ilog(range - 1));                                                                              // (6) 0.01168
/*40  */     floor1_Y[1] = get_bits(gb, ilog(range - 1));                                                                              // (5) 0.01317
/*44  */     av_dlog(NULL, "floor 0 Y %d floor 1 Y %d \n", floor1_Y[0], floor1_Y[1]);                                                  // (3) 0.01927
/*48  */     offset = 2;                                                                                                               // (18) 0.002762
/*50  */     for (i = 0; i < vf->partitions; ++i) {                                                                                    // (11) 0.006471
/*52  */         class = vf->partition_class[i];                                                                                       // (15) 0.003896
/*54  */         cdim   = vf->class_dimensions[class];                                                                                 // (13) 0.004845
/*56  */         cbits  = vf->class_subclasses[class];                                                                                 // (20) 0.001871
/*58  */         csub = (1 << cbits) - 1;                                                                                              // (21) 0.001772
/*60  */         cval = 0;                                                                                                             // (24) 0.0003346
/*64  */         av_dlog(NULL, "Cbits %u\n", cbits);                                                                                   // 0.0
/*68  */         if (cbits) // this reads all subclasses for this partition's class                                                    // 0.0
/*70  */             cval = get_vlc2(gb, vc->codebooks[vf->class_masterbook[class]].vlc.table,                                         // 0.0
/*72  */                             vc->codebooks[vf->class_masterbook[class]].nb_bits, 3);                                           // 0.0
/*76  */         for (j = 0; j < cdim; ++j) {                                                                                          // 0.0
/*78  */             book = vf->subclass_books[class][cval & csub];                                                                    // 0.0
/*82  */             av_dlog(NULL, "book %d Cbits %u cval %u  bits:%d\n",                                                              // 0.0
/*84  */                     book, cbits, cval, get_bits_count(gb));                                                                   // 0.0
/*88  */             cval = cval >> cbits;                                                                                             // 0.0
/*90  */             if (book > -1) {                                                                                                  // 0.0
/*92  */                 floor1_Y[offset+j] = get_vlc2(gb, vc->codebooks[book].vlc.table,                                              // 0.0
/*94  */                 vc->codebooks[book].nb_bits, 3);                                                                              // 0.0
/*96  */             } else {                                                                                                          // 0.0
/*98  */                 floor1_Y[offset+j] = 0;                                                                                       // 0.0
/*100 */             }                                                                                                                 // 0.0
/*104 */             av_dlog(NULL, " floor(%d) = %d \n",                                                                               // 0.0
/*106 */                     vf->list[offset+j].x, floor1_Y[offset+j]);                                                                // 0.0
/*108 */         }                                                                                                                     // 0.0
/*110 */         offset+=cdim;                                                                                                         // 0.0
/*112 */     }                                                                                                                         // 0.0
/*116 */ // Amplitude calculation from the differences                                                                                 // 0.0
/*120 */     floor1_flag[0] = 1;                                                                                                       // 0.0
/*122 */     floor1_flag[1] = 1;                                                                                                       // 0.0
/*124 */     floor1_Y_final[0] = floor1_Y[0];                                                                                          // 0.0
/*126 */     floor1_Y_final[1] = floor1_Y[1];                                                                                          // 0.0
/*130 */     for (i = 2; i < vf->x_list_dim; ++i) {                                                                                    // 0.0
/*132 */         unsigned val, highroom, lowroom, room, high_neigh_offs, low_neigh_offs;                                               // 0.0
/*136 */         low_neigh_offs  = vf->list[i].low;                                                                                    // 0.0
/*138 */         high_neigh_offs = vf->list[i].high;                                                                                   // 0.0
/*140 */         dy  = floor1_Y_final[high_neigh_offs] - floor1_Y_final[low_neigh_offs];  // render_point begin                        // 0.0
/*142 */         adx = vf->list[high_neigh_offs].x - vf->list[low_neigh_offs].x;                                                       // 0.0
/*144 */         ady = FFABS(dy);                                                                                                      // 0.0
/*146 */         err = ady * (vf->list[i].x - vf->list[low_neigh_offs].x);                                                             // 0.0
/*148 */         off = err / adx;                                                                                                      // 0.0
/*150 */         if (dy < 0) {                                                                                                         // 0.0
/*152 */             predicted = floor1_Y_final[low_neigh_offs] - off;                                                                 // 0.0
/*154 */         } else {                                                                                                              // 0.0
/*156 */             predicted = floor1_Y_final[low_neigh_offs] + off;                                                                 // 0.0
/*158 */         } // render_point end                                                                                                 // 0.0
/*162 */         val = floor1_Y[i];                                                                                                    // 0.0
/*164 */         highroom = range-predicted;                                                                                           // 0.0
/*166 */         lowroom  = predicted;                                                                                                 // 0.0
/*168 */         if (highroom < lowroom) {                                                                                             // 0.0
/*170 */             room = highroom * 2;                                                                                              // 0.0
/*172 */         } else {                                                                                                              // 0.0
/*174 */             room = lowroom * 2;   // SPEC mispelling                                                                          // 0.0
/*176 */         }                                                                                                                     // 0.0
/*178 */         if (val) {                                                                                                            // 0.0
/*180 */             floor1_flag[low_neigh_offs]  = 1;                                                                                 // 0.0
/*182 */             floor1_flag[high_neigh_offs] = 1;                                                                                 // 0.0
/*184 */             floor1_flag[i]               = 1;                                                                                 // 0.0
/*186 */             if (val >= room) {                                                                                                // 0.0
/*188 */                 if (highroom > lowroom) {                                                                                     // 0.0
/*190 */                     floor1_Y_final[i] = val - lowroom + predicted;                                                            // 0.0
/*192 */                 } else {                                                                                                      // 0.0
/*194 */                     floor1_Y_final[i] = predicted - val + highroom - 1;                                                       // 0.0
/*196 */                 }                                                                                                             // 0.0
/*198 */             } else {                                                                                                          // 0.0
/*200 */                 if (val & 1) {                                                                                                // 0.0
/*202 */                     floor1_Y_final[i] = predicted - (val + 1) / 2;                                                            // 0.0
/*204 */                 } else {                                                                                                      // 0.0
/*206 */                     floor1_Y_final[i] = predicted + val / 2;                                                                  // 0.0
/*208 */                 }                                                                                                             // 0.0
/*210 */             }                                                                                                                 // 0.0
/*212 */         } else {                                                                                                              // 0.0
/*214 */             floor1_flag[i]    = 0;                                                                                            // 0.0
/*216 */             floor1_Y_final[i] = predicted;                                                                                    // 0.0
/*218 */         }                                                                                                                     // 0.0
/*222 */         av_dlog(NULL, " Decoded floor(%d) = %u / val %u\n",                                                                   // 0.0
/*224 */                 vf->list[i].x, floor1_Y_final[i], val);                                                                       // 0.0
/*226 */     }                                                                                                                         // 0.0
/*230 */ // Curve synth - connect the calculated dots and convert from dB scale FIXME optimize ?                                       // 0.0
/*234 */     ff_vorbis_floor1_render_list(vf->list, vf->x_list_dim, floor1_Y_final, floor1_flag, vf->multiplier, vec, vf->list[1].x);  // 0.0
/*238 */     av_dlog(NULL, " Floor decoded\n");                                                                                        // 0.0
/*242 */     return 0;                                                                                                                 // 0.0
/*244 */ }                                                                                                                             // 0.0
