// commit message FFmpeg@90901860c2 (target=0, prob=0.84223276, correct=False): stupid code (casting of void*) found by checktree.sh
/*0   */ static int vorbis_parse_setup_hdr_mappings(vorbis_context *vc) {                                                                                    // (7) 0.04748
/*2   */     GetBitContext *gb=&vc->gb;                                                                                                                      // (14) 0.02739
/*4   */     uint_fast8_t i, j;                                                                                                                              // (16) 0.02538
/*8   */     vc->mapping_count=get_bits(gb, 6)+1;                                                                                                            // (9) 0.04094
/*10  */     vc->mappings=(vorbis_mapping *)av_mallocz(vc->mapping_count * sizeof(vorbis_mapping));                                                          // (2) 0.0703
/*14  */     AV_DEBUG(" There are %d mappings. \n", vc->mapping_count);                                                                                      // (6) 0.04891
/*18  */     for(i=0;i<vc->mapping_count;++i) {                                                                                                              // (8) 0.04336
/*20  */         vorbis_mapping *mapping_setup=&vc->mappings[i];                                                                                             // (5) 0.05263
/*24  */         if (get_bits(gb, 16)) {                                                                                                                     // (11) 0.03508
/*26  */             av_log(vc->avccontext, AV_LOG_ERROR, "Other mappings than type 0 are not compliant with the Vorbis I specification. \n");               // (1) 0.09556
/*28  */             return 1;                                                                                                                               // (15) 0.02728
/*30  */         }                                                                                                                                           // (19) 0.01559
/*32  */         if (get_bits1(gb)) {                                                                                                                        // (12) 0.03313
/*34  */             mapping_setup->submaps=get_bits(gb, 4)+1;                                                                                               // (4) 0.05456
/*36  */         } else {                                                                                                                                    // (17) 0.01949
/*38  */             mapping_setup->submaps=1;                                                                                                               // (10) 0.03897
/*40  */         }                                                                                                                                           // (18) 0.01559
/*44  */         if (get_bits1(gb)) {                                                                                                                        // (13) 0.03313
/*46  */             mapping_setup->coupling_steps=get_bits(gb, 8)+1;                                                                                        // (3) 0.06041
/*48  */             mapping_setup->magnitude=(uint_fast8_t *)av_mallocz(mapping_setup->coupling_steps * sizeof(uint_fast8_t));                              // (0) 0.1013
/*50  */             mapping_setup->angle=(uint_fast8_t *)av_mallocz(mapping_setup->coupling_steps * sizeof(uint_fast8_t));                                  // 0.0
/*52  */             for(j=0;j<mapping_setup->coupling_steps;++j) {                                                                                          // 0.0
/*54  */                 mapping_setup->magnitude[j]=get_bits(gb, ilog(vc->audio_channels-1));                                                               // 0.0
/*56  */                 mapping_setup->angle[j]=get_bits(gb, ilog(vc->audio_channels-1));                                                                   // 0.0
/*58  */                 // FIXME: sanity checks                                                                                                             // 0.0
/*60  */             }                                                                                                                                       // 0.0
/*62  */         } else {                                                                                                                                    // 0.0
/*64  */             mapping_setup->coupling_steps=0;                                                                                                        // 0.0
/*66  */         }                                                                                                                                           // 0.0
/*70  */         AV_DEBUG("   %d mapping coupling steps: %d \n", i, mapping_setup->coupling_steps);                                                          // 0.0
/*74  */         if(get_bits(gb, 2)) {                                                                                                                       // 0.0
/*76  */             av_log(vc->avccontext, AV_LOG_ERROR, "%d. mapping setup data invalid. \n", i);                                                          // 0.0
/*78  */             return 1; // following spec.                                                                                                            // 0.0
/*80  */         }                                                                                                                                           // 0.0
/*84  */         if (mapping_setup->submaps>1) {                                                                                                             // 0.0
/*86  */             mapping_setup->mux=(uint_fast8_t *)av_mallocz(vc->audio_channels * sizeof(uint_fast8_t));                                               // 0.0
/*88  */             for(j=0;j<vc->audio_channels;++j) {                                                                                                     // 0.0
/*90  */                 mapping_setup->mux[j]=get_bits(gb, 4);                                                                                              // 0.0
/*92  */             }                                                                                                                                       // 0.0
/*94  */         }                                                                                                                                           // 0.0
/*98  */         for(j=0;j<mapping_setup->submaps;++j) {                                                                                                     // 0.0
/*100 */             skip_bits(gb, 8); // FIXME check?                                                                                                       // 0.0
/*102 */             mapping_setup->submap_floor[j]=get_bits(gb, 8);                                                                                         // 0.0
/*104 */             mapping_setup->submap_residue[j]=get_bits(gb, 8);                                                                                       // 0.0
/*108 */             AV_DEBUG("   %d mapping %d submap : floor %d, residue %d \n", i, j, mapping_setup->submap_floor[j], mapping_setup->submap_residue[j]);  // 0.0
/*110 */         }                                                                                                                                           // 0.0
/*112 */     }                                                                                                                                               // 0.0
/*114 */     return 0;                                                                                                                                       // 0.0
/*116 */ }                                                                                                                                                   // 0.0
