// commit message qemu@60fe637bf0 (target=1, prob=0.38230452, correct=False): Start migrating migration code into a migration directory
/*0  */ static void blk_send(QEMUFile *f, BlkMigBlock * blk)                          // (5) 0.05312
/*2  */ {                                                                             // (22) 0.002309
/*4  */     int len;                                                                  // (19) 0.01386
/*6  */     uint64_t flags = BLK_MIG_FLAG_DEVICE_BLOCK;                               // (6) 0.05312
/*10 */     if (block_mig_state.zero_blocks &&                                        // (14) 0.03695
/*12 */         buffer_is_zero(blk->buf, BLOCK_SIZE)) {                               // (3) 0.05543
/*14 */         flags |= BLK_MIG_FLAG_ZERO_BLOCK;                                     // (4) 0.05543
/*16 */     }                                                                         // (20) 0.009238
/*20 */     /* sector number and flags */                                             // (16) 0.02079
/*22 */     qemu_put_be64(f, (blk->sector << BDRV_SECTOR_BITS)                        // (1) 0.07159
/*24 */                      | flags);                                                // (7) 0.05312
/*28 */     /* device name */                                                         // (18) 0.01617
/*30 */     len = strlen(bdrv_get_device_name(blk->bmds->bs));                        // (2) 0.06236
/*32 */     qemu_put_byte(f, len);                                                    // (15) 0.03464
/*34 */     qemu_put_buffer(f, (uint8_t *)bdrv_get_device_name(blk->bmds->bs), len);  // (0) 0.09238
/*38 */     /* if a block is zero we need to flush here since the network             // (11) 0.03926
/*40 */      * bandwidth is now a lot higher than the storage device bandwidth.       // (12) 0.03926
/*42 */      * thus if we queue zero blocks we slow down the migration */             // (10) 0.03926
/*44 */     if (flags & BLK_MIG_FLAG_ZERO_BLOCK) {                                    // (9) 0.05081
/*46 */         qemu_fflush(f);                                                       // (13) 0.03926
/*48 */         return;                                                               // (17) 0.02079
/*50 */     }                                                                         // (21) 0.009238
/*54 */     qemu_put_buffer(f, blk->buf, BLOCK_SIZE);                                 // (8) 0.05312
/*56 */ }                                                                             // (23) 0.002309
