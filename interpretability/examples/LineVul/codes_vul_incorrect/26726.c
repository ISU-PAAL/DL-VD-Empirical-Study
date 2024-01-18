// commit message qemu@ebd9fbd7e1 (target=1, prob=0.30600074, correct=False): block migration: fix return value
/*0   */ static int block_save_iterate(QEMUFile *f, void *opaque)              // (8) 0.04102
/*2   */ {                                                                     // (26) 0.001953
/*4   */     int ret;                                                          // (24) 0.01172
/*6   */     int64_t last_ftell = qemu_ftell(f);                               // (10) 0.04102
/*10  */     DPRINTF("Enter save live iterate submitted %d transferred %d\n",  // (9) 0.04102
/*12  */             block_mig_state.submitted, block_mig_state.transferred);  // (1) 0.06055
/*16  */     ret = flush_blks(f);                                              // (17) 0.02344
/*18  */     if (ret) {                                                        // (23) 0.01562
/*20  */         return ret;                                                   // (20) 0.01953
/*22  */     }                                                                 // (25) 0.007812
/*26  */     blk_mig_reset_dirty_cursor();                                     // (13) 0.03125
/*30  */     /* control the rate of transfer */                                // (21) 0.01953
/*32  */     blk_mig_lock();                                                   // (19) 0.02148
/*34  */     while ((block_mig_state.submitted +                               // (15) 0.0293
/*36  */             block_mig_state.read_done) * BLOCK_SIZE <                 // (3) 0.05469
/*38  */            qemu_file_get_rate_limit(f)) {                             // (4) 0.04883
/*40  */         blk_mig_unlock();                                             // (14) 0.03125
/*42  */         if (block_mig_state.bulk_completed == 0) {                    // (5) 0.04883
/*44  */             /* first finish the bulk phase */                         // (12) 0.03516
/*46  */             if (blk_mig_save_bulked_block(f) == 0) {                  // (0) 0.0625
/*48  */                 /* finished saving bulk on all devices */             // (7) 0.04492
/*50  */                 block_mig_state.bulk_completed = 1;                   // (2) 0.05859
/*52  */             }                                                         // (18) 0.02344
/*54  */             ret = 0;                                                  // (16) 0.0293
/*56  */         } else {                                                      // (22) 0.01953
/*58  */             /* Always called with iothread lock taken for             // (11) 0.04102
/*60  */              * simplicity, block_save_complete also calls it.         // (6) 0.04687
/*62  */              */                                                       // 0.0
/*64  */             qemu_mutex_lock_iothread();                               // 0.0
/*66  */             ret = blk_mig_save_dirty_block(f, 1);                     // 0.0
/*68  */             qemu_mutex_unlock_iothread();                             // 0.0
/*70  */         }                                                             // 0.0
/*72  */         if (ret < 0) {                                                // 0.0
/*74  */             return ret;                                               // 0.0
/*76  */         }                                                             // 0.0
/*78  */         blk_mig_lock();                                               // 0.0
/*80  */         if (ret != 0) {                                               // 0.0
/*82  */             /* no more dirty blocks */                                // 0.0
/*84  */             break;                                                    // 0.0
/*86  */         }                                                             // 0.0
/*88  */     }                                                                 // 0.0
/*90  */     blk_mig_unlock();                                                 // 0.0
/*94  */     ret = flush_blks(f);                                              // 0.0
/*96  */     if (ret) {                                                        // 0.0
/*98  */         return ret;                                                   // 0.0
/*100 */     }                                                                 // 0.0
/*104 */     qemu_put_be64(f, BLK_MIG_FLAG_EOS);                               // 0.0
/*106 */     return qemu_ftell(f) - last_ftell;                                // 0.0
/*108 */ }                                                                     // 0.0
