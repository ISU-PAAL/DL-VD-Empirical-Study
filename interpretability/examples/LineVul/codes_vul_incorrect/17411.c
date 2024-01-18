// commit message qemu@60fe637bf0 (target=1, prob=0.466505, correct=False): Start migrating migration code into a migration directory
/*0  */ static int block_save_complete(QEMUFile *f, void *opaque)                 // (4) 0.04819
/*2  */ {                                                                         // (26) 0.00241
/*4  */     int ret;                                                              // (22) 0.01446
/*8  */     DPRINTF("Enter save live complete submitted %d transferred %d\n",     // (5) 0.04819
/*10 */             block_mig_state.submitted, block_mig_state.transferred);      // (1) 0.0747
/*14 */     ret = flush_blks(f);                                                  // (12) 0.02892
/*16 */     if (ret) {                                                            // (19) 0.01928
/*18 */         return ret;                                                       // (17) 0.0241
/*20 */     }                                                                     // (25) 0.009639
/*24 */     blk_mig_reset_dirty_cursor();                                         // (7) 0.03855
/*28 */     /* we know for sure that save bulk is completed and                   // (8) 0.03373
/*30 */        all async read completed */                                        // (15) 0.02651
/*32 */     blk_mig_lock();                                                       // (16) 0.02651
/*34 */     assert(block_mig_state.submitted == 0);                               // (6) 0.04096
/*36 */     blk_mig_unlock();                                                     // (13) 0.02892
/*40 */     do {                                                                  // (24) 0.01205
/*42 */         ret = blk_mig_save_dirty_block(f, 0);                             // (2) 0.06024
/*44 */         if (ret < 0) {                                                    // (9) 0.03373
/*46 */             return ret;                                                   // (10) 0.03373
/*48 */         }                                                                 // (20) 0.01928
/*50 */     } while (ret == 0);                                                   // (18) 0.0241
/*54 */     /* report completion */                                               // (21) 0.01687
/*56 */     qemu_put_be64(f, (100 << BDRV_SECTOR_BITS) | BLK_MIG_FLAG_PROGRESS);  // (0) 0.0988
/*60 */     DPRINTF("Block migration completed\n");                               // (11) 0.03133
/*64 */     qemu_put_be64(f, BLK_MIG_FLAG_EOS);                                   // (3) 0.06024
/*68 */     blk_mig_cleanup();                                                    // (14) 0.02892
/*70 */     return 0;                                                             // (23) 0.01446
/*72 */ }                                                                         // (27) 0.00241
