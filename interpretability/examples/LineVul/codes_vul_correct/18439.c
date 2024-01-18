// commit message qemu@c627e7526a (target=1, prob=0.578663, correct=True): dma/rc4030: translate memory accesses only when they occur
/*0  */ static void rc4030_dma_as_update_one(rc4030State *s, int index, uint32_t frame)  // (2) 0.09687
/*2  */ {                                                                                // (17) 0.003125
/*4  */     if (index < MAX_TL_ENTRIES) {                                                // (8) 0.05
/*6  */         memory_region_set_enabled(&s->dma_mrs[index], false);                    // (4) 0.08437
/*8  */     }                                                                            // (14) 0.0125
/*12 */     if (!frame) {                                                                // (12) 0.025
/*14 */         return;                                                                  // (11) 0.02812
/*16 */     }                                                                            // (15) 0.0125
/*20 */     if (index >= MAX_TL_ENTRIES) {                                               // (9) 0.05
/*22 */         qemu_log_mask(LOG_UNIMP,                                                 // (7) 0.06562
/*24 */                       "rc4030: trying to use too high "                          // (1) 0.1
/*26 */                       "translation table entry %d (max allowed=%d)",             // (0) 0.1062
/*28 */                       index, MAX_TL_ENTRIES);                                    // (3) 0.09687
/*30 */         return;                                                                  // (10) 0.02812
/*32 */     }                                                                            // (13) 0.0125
/*34 */     memory_region_set_alias_offset(&s->dma_mrs[index], frame);                   // (5) 0.07812
/*36 */     memory_region_set_enabled(&s->dma_mrs[index], true);                         // (6) 0.07187
/*38 */ }                                                                                // (16) 0.003125
