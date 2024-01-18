// commit message qemu@06b106889a (target=1, prob=0.53930914, correct=True): ram: Use page number instead of an address for the bitmap operations
/*0  */ static bool find_dirty_block(RAMState *rs, PageSearchStatus *pss,             // (8) 0.03906
/*2  */                              bool *again, ram_addr_t *ram_addr_abs)           // (1) 0.08594
/*4  */ {                                                                             // (23) 0.001953
/*6  */     pss->offset = migration_bitmap_find_dirty(rs, pss->block, pss->offset,    // (3) 0.05664
/*8  */                                               ram_addr_abs);                  // (0) 0.09961
/*10 */     if (pss->complete_round && pss->block == rs->last_seen_block &&           // (5) 0.04883
/*12 */         pss->offset >= rs->last_offset) {                                     // (13) 0.03711
/*14 */         /*                                                                    // (21) 0.01563
/*16 */          * We've been once around the RAM and haven't found anything.         // (6) 0.04297
/*18 */          * Give up.                                                           // (18) 0.02344
/*20 */          */                                                                   // (20) 0.01758
/*22 */         *again = false;                                                       // (17) 0.02344
/*24 */         return false;                                                         // (19) 0.01953
/*26 */     }                                                                         // (22) 0.007812
/*28 */     if (pss->offset >= pss->block->used_length) {                             // (10) 0.03906
/*30 */         /* Didn't find anything in this RAM Block */                          // (14) 0.0332
/*32 */         pss->offset = 0;                                                      // (16) 0.02734
/*34 */         pss->block = QLIST_NEXT_RCU(pss->block, next);                        // (4) 0.05469
/*36 */         if (!pss->block) {                                                    // (15) 0.0293
/*38 */             /* Hit the end of the list */                                     // (12) 0.03711
/*40 */             pss->block = QLIST_FIRST_RCU(&ram_list.blocks);                   // (2) 0.06055
/*42 */             /* Flag that we've looped */                                      // (11) 0.03711
/*44 */             pss->complete_round = true;                                       // (9) 0.03906
/*46 */             rs->ram_bulk_stage = false;                                       // (7) 0.04297
/*48 */             if (migrate_use_xbzrle()) {                                       // 0.0
/*50 */                 /* If xbzrle is on, stop using the data compression at this   // 0.0
/*52 */                  * point. In theory, xbzrle can do better than compression.   // 0.0
/*54 */                  */                                                           // 0.0
/*56 */                 flush_compressed_data(rs);                                    // 0.0
/*58 */             }                                                                 // 0.0
/*60 */         }                                                                     // 0.0
/*62 */         /* Didn't find anything this time, but try again on the new block */  // 0.0
/*64 */         *again = true;                                                        // 0.0
/*66 */         return false;                                                         // 0.0
/*68 */     } else {                                                                  // 0.0
/*70 */         /* Can go around again, but... */                                     // 0.0
/*72 */         *again = true;                                                        // 0.0
/*74 */         /* We've found something so probably don't need to */                 // 0.0
/*76 */         return true;                                                          // 0.0
/*78 */     }                                                                         // 0.0
/*80 */ }                                                                             // 0.0
