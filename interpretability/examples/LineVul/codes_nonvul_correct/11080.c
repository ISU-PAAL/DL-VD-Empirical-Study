// commit message FFmpeg@c9aab8a123 (target=0, prob=0.3752123, correct=True): h264: use mbaff ref indices in fill_colmap() only for mbaff references
/*0  */ static void fill_colmap(H264Context *h, int map[2][16+32], int list, int field, int colfield, int mbafi){  // (2) 0.07227
/*2  */     MpegEncContext * const s = &h->s;                                                                      // (15) 0.03125
/*4  */     Picture * const ref1 = &h->ref_list[1][0];                                                             // (11) 0.03906
/*6  */     int j, old_ref, rfield;                                                                                // (16) 0.02539
/*8  */     int start= mbafi ? 16                      : 0;                                                        // (4) 0.06836
/*10 */     int end  = mbafi ? 16+2*h->ref_count[0]    : h->ref_count[0];                                          // (5) 0.06836
/*12 */     int interl= mbafi || s->picture_structure != PICT_FRAME;                                               // (8) 0.04688
/*16 */     /* bogus; fills in for missing frames */                                                               // (17) 0.02344
/*18 */     memset(map[list], 0, sizeof(map[list]));                                                               // (13) 0.03711
/*22 */     for(rfield=0; rfield<2; rfield++){                                                                     // (14) 0.03711
/*24 */         for(old_ref=0; old_ref<ref1->ref_count[colfield][list]; old_ref++){                                // (3) 0.07031
/*26 */             int poc = ref1->ref_poc[colfield][list][old_ref];                                              // (6) 0.0625
/*30 */             if     (!interl)                                                                               // (12) 0.03906
/*32 */                 poc |= 3;                                                                                  // (10) 0.04102
/*34 */             else if( interl && (poc&3) == 3) //FIXME store all MBAFF references so this isnt needed        // (1) 0.07617
/*36 */                 poc= (poc&~3) + rfield + 1;                                                                // (7) 0.06055
/*40 */             for(j=start; j<end; j++){                                                                      // (9) 0.04687
/*42 */                 if (4 * h->ref_list[0][j].frame_num + (h->ref_list[0][j].f.reference & 3) == poc) {        // (0) 0.1074
/*44 */                     int cur_ref= mbafi ? (j-16)^field : j;                                                 // 0.0
/*46 */                     map[list][2*old_ref + (rfield^field) + 16] = cur_ref;                                  // 0.0
/*48 */                     if(rfield == field || !interl)                                                         // 0.0
/*50 */                         map[list][old_ref] = cur_ref;                                                      // 0.0
/*52 */                     break;                                                                                 // 0.0
/*54 */                 }                                                                                          // 0.0
/*56 */             }                                                                                              // 0.0
/*58 */         }                                                                                                  // 0.0
/*60 */     }                                                                                                      // 0.0
/*62 */ }                                                                                                          // 0.0
