// commit message FFmpeg@892fc83e88 (target=0, prob=0.6002991, correct=False): squashed a bunch of subtle array indexing bugs, fixed block mapping added more error checking, added (and enabled, for the time being) a keyframe-only mode
/*0   */ static void init_block_mapping(Vp3DecodeContext *s)                                       // (2) 0.03711
/*2   */ {                                                                                         // (34) 0.001954
/*4   */     int i, j;                                                                             // (29) 0.01562
/*6   */     signed int hilbert_walk_y[16];                                                        // (13) 0.0293
/*8   */     signed int hilbert_walk_c[16];                                                        // (14) 0.0293
/*10  */     signed int hilbert_walk_mb[4];                                                        // (15) 0.0293
/*14  */     int current_fragment = 0;                                                             // (20) 0.02344
/*16  */     int current_width = 0;                                                                // (28) 0.01953
/*18  */     int current_height = 0;                                                               // (25) 0.01953
/*20  */     int right_edge = 0;                                                                   // (27) 0.01953
/*22  */     int bottom_edge = 0;                                                                  // (26) 0.01953
/*24  */     int superblock_row_inc = 0;                                                           // (17) 0.02539
/*26  */     int *hilbert = NULL;                                                                  // (21) 0.02148
/*28  */     int mapping_index = 0;                                                                // (24) 0.01953
/*32  */     int current_macroblock;                                                               // (23) 0.01953
/*34  */     int c_fragment;                                                                       // (22) 0.01953
/*38  */     signed char travel_width[16] = {                                                      // (19) 0.02539
/*40  */          1,  1,  0, -1,                                                                   // (1) 0.03906
/*42  */          0,  0,  1,  0,                                                                   // (4) 0.03711
/*44  */          1,  0,  1,  0,                                                                   // (3) 0.03711
/*46  */          0, -1,  0,  1                                                                    // (9) 0.03516
/*48  */     };                                                                                    // (32) 0.007812
/*52  */     signed char travel_height[16] = {                                                     // (18) 0.02539
/*54  */          0,  0,  1,  0,                                                                   // (5) 0.03711
/*56  */          1,  1,  0, -1,                                                                   // (6) 0.03711
/*58  */          0,  1,  0, -1,                                                                   // (7) 0.03711
/*60  */         -1,  0, -1,  0                                                                    // (10) 0.03516
/*62  */     };                                                                                    // (31) 0.007812
/*66  */     signed char travel_width_mb[4] = {                                                    // (16) 0.0293
/*68  */          1,  0,  1,  0                                                                    // (11) 0.03516
/*70  */     };                                                                                    // (33) 0.007812
/*74  */     signed char travel_height_mb[4] = {                                                   // (12) 0.0293
/*76  */          0,  1,  0, -1                                                                    // (8) 0.03516
/*78  */     };                                                                                    // (30) 0.007812
/*82  */     debug_vp3("  vp3: initialize block mapping tables\n");                                // (0) 0.03906
/*86  */     /* figure out hilbert pattern per these frame dimensions */                           // 0.0
/*88  */     hilbert_walk_y[0]  = 1;                                                               // 0.0
/*90  */     hilbert_walk_y[1]  = 1;                                                               // 0.0
/*92  */     hilbert_walk_y[2]  = s->fragment_width;                                               // 0.0
/*94  */     hilbert_walk_y[3]  = -1;                                                              // 0.0
/*96  */     hilbert_walk_y[4]  = s->fragment_width;                                               // 0.0
/*98  */     hilbert_walk_y[5]  = s->fragment_width;                                               // 0.0
/*100 */     hilbert_walk_y[6]  = 1;                                                               // 0.0
/*102 */     hilbert_walk_y[7]  = -s->fragment_width;                                              // 0.0
/*104 */     hilbert_walk_y[8]  = 1;                                                               // 0.0
/*106 */     hilbert_walk_y[9]  = s->fragment_width;                                               // 0.0
/*108 */     hilbert_walk_y[10]  = 1;                                                              // 0.0
/*110 */     hilbert_walk_y[11] = -s->fragment_width;                                              // 0.0
/*112 */     hilbert_walk_y[12] = -s->fragment_width;                                              // 0.0
/*114 */     hilbert_walk_y[13] = -1;                                                              // 0.0
/*116 */     hilbert_walk_y[14] = -s->fragment_width;                                              // 0.0
/*118 */     hilbert_walk_y[15] = 1;                                                               // 0.0
/*122 */     hilbert_walk_c[0]  = 1;                                                               // 0.0
/*124 */     hilbert_walk_c[1]  = 1;                                                               // 0.0
/*126 */     hilbert_walk_c[2]  = s->fragment_width / 2;                                           // 0.0
/*128 */     hilbert_walk_c[3]  = -1;                                                              // 0.0
/*130 */     hilbert_walk_c[4]  = s->fragment_width / 2;                                           // 0.0
/*132 */     hilbert_walk_c[5]  = s->fragment_width / 2;                                           // 0.0
/*134 */     hilbert_walk_c[6]  = 1;                                                               // 0.0
/*136 */     hilbert_walk_c[7]  = -s->fragment_width / 2;                                          // 0.0
/*138 */     hilbert_walk_c[8]  = 1;                                                               // 0.0
/*140 */     hilbert_walk_c[9]  = s->fragment_width / 2;                                           // 0.0
/*142 */     hilbert_walk_c[10]  = 1;                                                              // 0.0
/*144 */     hilbert_walk_c[11] = -s->fragment_width / 2;                                          // 0.0
/*146 */     hilbert_walk_c[12] = -s->fragment_width / 2;                                          // 0.0
/*148 */     hilbert_walk_c[13] = -1;                                                              // 0.0
/*150 */     hilbert_walk_c[14] = -s->fragment_width / 2;                                          // 0.0
/*152 */     hilbert_walk_c[15] = 1;                                                               // 0.0
/*156 */     hilbert_walk_mb[0] = 1;                                                               // 0.0
/*158 */     hilbert_walk_mb[1] = s->macroblock_width;                                             // 0.0
/*160 */     hilbert_walk_mb[2] = 1;                                                               // 0.0
/*162 */     hilbert_walk_mb[3] = -s->macroblock_width;                                            // 0.0
/*166 */     /* iterate through each superblock (all planes) and map the fragments */              // 0.0
/*168 */     for (i = 0; i < s->superblock_count; i++) {                                           // 0.0
/*170 */         debug_init("    superblock %d (u starts @ %d, v starts @ %d)\n",                  // 0.0
/*172 */             i, s->u_superblock_start, s->v_superblock_start);                             // 0.0
/*176 */         /* time to re-assign the limits? */                                               // 0.0
/*178 */         if (i == 0) {                                                                     // 0.0
/*182 */             /* start of Y superblocks */                                                  // 0.0
/*184 */             right_edge = s->fragment_width;                                               // 0.0
/*186 */             bottom_edge = s->fragment_height;                                             // 0.0
/*188 */             current_width = 0;                                                            // 0.0
/*190 */             current_height = 0;                                                           // 0.0
/*192 */             superblock_row_inc = 3 * s->fragment_width;                                   // 0.0
/*194 */             hilbert = hilbert_walk_y;                                                     // 0.0
/*198 */             /* the first operation for this variable is to advance by 1 */                // 0.0
/*200 */             current_fragment = -1;                                                        // 0.0
/*204 */         } else if (i == s->u_superblock_start) {                                          // 0.0
/*208 */             /* start of U superblocks */                                                  // 0.0
/*210 */             right_edge = s->fragment_width / 2;                                           // 0.0
/*212 */             bottom_edge = s->fragment_height / 2;                                         // 0.0
/*214 */             current_width = 0;                                                            // 0.0
/*216 */             current_height = 0;                                                           // 0.0
/*218 */             superblock_row_inc = 3 * (s->fragment_width / 2);                             // 0.0
/*220 */             hilbert = hilbert_walk_c;                                                     // 0.0
/*224 */             /* the first operation for this variable is to advance by 1 */                // 0.0
/*226 */             current_fragment = s->u_fragment_start - 1;                                   // 0.0
/*230 */         } else if (i == s->v_superblock_start) {                                          // 0.0
/*234 */             /* start of V superblocks */                                                  // 0.0
/*236 */             right_edge = s->fragment_width / 2;                                           // 0.0
/*238 */             bottom_edge = s->fragment_height / 2;                                         // 0.0
/*240 */             current_width = 0;                                                            // 0.0
/*242 */             current_height = 0;                                                           // 0.0
/*244 */             superblock_row_inc = 3 * (s->fragment_width / 2);                             // 0.0
/*246 */             hilbert = hilbert_walk_c;                                                     // 0.0
/*250 */             /* the first operation for this variable is to advance by 1 */                // 0.0
/*252 */             current_fragment = s->v_fragment_start - 1;                                   // 0.0
/*256 */         }                                                                                 // 0.0
/*260 */         if (current_width >= right_edge) {                                                // 0.0
/*262 */             /* reset width and move to next superblock row */                             // 0.0
/*264 */             current_width = 0;                                                            // 0.0
/*266 */             current_height += 4;                                                          // 0.0
/*270 */             /* fragment is now at the start of a new superblock row */                    // 0.0
/*272 */             current_fragment += superblock_row_inc;                                       // 0.0
/*274 */         }                                                                                 // 0.0
/*278 */         /* iterate through all 16 fragments in a superblock */                            // 0.0
/*280 */         for (j = 0; j < 16; j++) {                                                        // 0.0
/*282 */             current_fragment += hilbert[j];                                               // 0.0
/*284 */             current_height += travel_height[j];                                           // 0.0
/*288 */             /* check if the fragment is in bounds */                                      // 0.0
/*290 */             if ((current_width <= right_edge) &&                                          // 0.0
/*292 */                 (current_height < bottom_edge)) {                                         // 0.0
/*294 */                 s->superblock_fragments[mapping_index] = current_fragment;                // 0.0
/*296 */                 debug_init("    mapping fragment %d to superblock %d, position %d\n",     // 0.0
/*298 */                     s->superblock_fragments[mapping_index], i, j);                        // 0.0
/*300 */             } else {                                                                      // 0.0
/*302 */                 s->superblock_fragments[mapping_index] = -1;                              // 0.0
/*304 */                 debug_init("    superblock %d, position %d has no fragment\n",            // 0.0
/*306 */                     i, j);                                                                // 0.0
/*308 */             }                                                                             // 0.0
/*312 */             current_width += travel_width[j];                                             // 0.0
/*314 */             mapping_index++;                                                              // 0.0
/*316 */         }                                                                                 // 0.0
/*318 */     }                                                                                     // 0.0
/*322 */     /* initialize the superblock <-> macroblock mapping; iterate through                  // 0.0
/*324 */      * all of the Y plane superblocks to build this mapping */                            // 0.0
/*326 */     right_edge = s->macroblock_width;                                                     // 0.0
/*328 */     bottom_edge = s->macroblock_height;                                                   // 0.0
/*330 */     current_width = 0;                                                                    // 0.0
/*332 */     current_height = 0;                                                                   // 0.0
/*334 */     superblock_row_inc = s->macroblock_width;                                             // 0.0
/*336 */     hilbert = hilbert_walk_mb;                                                            // 0.0
/*338 */     mapping_index = 0;                                                                    // 0.0
/*340 */     current_macroblock = -1;                                                              // 0.0
/*342 */     for (i = 0; i < s->u_superblock_start; i++) {                                         // 0.0
/*346 */         if (current_width >= right_edge) {                                                // 0.0
/*348 */             /* reset width and move to next superblock row */                             // 0.0
/*350 */             current_width = 0;                                                            // 0.0
/*352 */             current_height += 2;                                                          // 0.0
/*356 */             /* macroblock is now at the start of a new superblock row */                  // 0.0
/*358 */             current_macroblock += superblock_row_inc;                                     // 0.0
/*360 */         }                                                                                 // 0.0
/*364 */         /* iterate through each potential macroblock in the superblock */                 // 0.0
/*366 */         for (j = 0; j < 4; j++) {                                                         // 0.0
/*368 */             current_macroblock += hilbert_walk_mb[j];                                     // 0.0
/*370 */             current_height += travel_height_mb[j];                                        // 0.0
/*374 */             /* check if the macroblock is in bounds */                                    // 0.0
/*376 */             if ((current_width <= right_edge) &&                                          // 0.0
/*378 */                 (current_height < bottom_edge)) {                                         // 0.0
/*380 */                 s->superblock_macroblocks[mapping_index] = current_macroblock;            // 0.0
/*382 */                 debug_init("    mapping macroblock %d to superblock %d, position %d\n",   // 0.0
/*384 */                     s->superblock_macroblocks[mapping_index], i, j);                      // 0.0
/*386 */             } else {                                                                      // 0.0
/*388 */                 s->superblock_macroblocks[mapping_index] = -1;                            // 0.0
/*390 */                 debug_init("    superblock %d, position %d has no macroblock\n",          // 0.0
/*392 */                     i, j);                                                                // 0.0
/*394 */             }                                                                             // 0.0
/*398 */             current_width += travel_width_mb[j];                                          // 0.0
/*400 */             mapping_index++;                                                              // 0.0
/*402 */         }                                                                                 // 0.0
/*404 */     }                                                                                     // 0.0
/*408 */     /* initialize the macroblock <-> fragment mapping */                                  // 0.0
/*410 */     current_fragment = 0;                                                                 // 0.0
/*412 */     current_macroblock = 0;                                                               // 0.0
/*414 */     mapping_index = 0;                                                                    // 0.0
/*416 */     for (i = 0; i < s->fragment_height; i += 2) {                                         // 0.0
/*420 */         for (j = 0; j < s->fragment_width; j += 2) {                                      // 0.0
/*424 */             debug_init("    macroblock %d contains fragments: ", current_macroblock);     // 0.0
/*426 */             s->all_fragments[current_fragment].macroblock = current_macroblock;           // 0.0
/*428 */             s->macroblock_fragments[mapping_index++] = current_fragment;                  // 0.0
/*430 */             debug_init("%d ", current_fragment);                                          // 0.0
/*434 */             if (j + 1 < s->fragment_width) {                                              // 0.0
/*436 */                 s->all_fragments[current_fragment + 1].macroblock = current_macroblock;   // 0.0
/*438 */                 s->macroblock_fragments[mapping_index++] = current_fragment + 1;          // 0.0
/*440 */                 debug_init("%d ", current_fragment + 1);                                  // 0.0
/*442 */             } else                                                                        // 0.0
/*444 */                 s->macroblock_fragments[mapping_index++] = -1;                            // 0.0
/*448 */             if (i + 1 < s->fragment_height) {                                             // 0.0
/*450 */                 s->all_fragments[current_fragment + s->fragment_width].macroblock =       // 0.0
/*452 */                     current_macroblock;                                                   // 0.0
/*454 */                 s->macroblock_fragments[mapping_index++] =                                // 0.0
/*456 */                     current_fragment + s->fragment_width;                                 // 0.0
/*458 */                 debug_init("%d ", current_fragment + s->fragment_width);                  // 0.0
/*460 */             } else                                                                        // 0.0
/*462 */                 s->macroblock_fragments[mapping_index++] = -1;                            // 0.0
/*466 */             if ((j + 1 < s->fragment_width) && (i + 1 < s->fragment_height)) {            // 0.0
/*468 */                 s->all_fragments[current_fragment + s->fragment_width + 1].macroblock =   // 0.0
/*470 */                     current_macroblock;                                                   // 0.0
/*472 */                 s->macroblock_fragments[mapping_index++] =                                // 0.0
/*474 */                     current_fragment + s->fragment_width + 1;                             // 0.0
/*476 */                 debug_init("%d ", current_fragment + s->fragment_width + 1);              // 0.0
/*478 */             } else                                                                        // 0.0
/*480 */                 s->macroblock_fragments[mapping_index++] = -1;                            // 0.0
/*484 */             /* C planes */                                                                // 0.0
/*486 */             c_fragment = s->u_fragment_start +                                            // 0.0
/*488 */                 (i * s->fragment_width / 4) + (j / 2);                                    // 0.0
/*490 */         s->all_fragments[c_fragment].macroblock = s->macroblock_count;                    // 0.0
/*492 */             s->macroblock_fragments[mapping_index++] = c_fragment;                        // 0.0
/*494 */             debug_init("%d ", c_fragment);                                                // 0.0
/*498 */             c_fragment = s->v_fragment_start +                                            // 0.0
/*500 */                 (i * s->fragment_width / 4) + (j / 2);                                    // 0.0
/*502 */         s->all_fragments[c_fragment].macroblock = s->macroblock_count;                    // 0.0
/*504 */             s->macroblock_fragments[mapping_index++] = c_fragment;                        // 0.0
/*506 */             debug_init("%d ", c_fragment);                                                // 0.0
/*510 */             debug_init("\n");                                                             // 0.0
/*514 */             if (j + 2 <= s->fragment_width)                                               // 0.0
/*516 */                 current_fragment += 2;                                                    // 0.0
/*518 */             else                                                                          // 0.0
/*520 */                 current_fragment++;                                                       // 0.0
/*522 */             current_macroblock++;                                                         // 0.0
/*524 */         }                                                                                 // 0.0
/*528 */         current_fragment += s->fragment_width;                                            // 0.0
/*530 */     }                                                                                     // 0.0
/*532 */ }                                                                                         // 0.0
