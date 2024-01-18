// commit message qemu@b9f7855a50 (target=0, prob=0.2502148, correct=True): block: Switch discard length bounds to byte-based
/*0  */ static void iscsi_refresh_limits(BlockDriverState *bs, Error **errp)          // (8) 0.04297
/*2  */ {                                                                             // (22) 0.001953
/*4  */     /* We don't actually refresh here, but just return data queried in        // (14) 0.03516
/*6  */      * iscsi_open(): iscsi targets don't change their limits. */              // (9) 0.04297
/*10 */     IscsiLun *iscsilun = bs->opaque;                                          // (12) 0.03711
/*12 */     uint64_t max_xfer_len = iscsilun->use_16_for_rw ? 0xffffffff : 0xffff;    // (4) 0.07031
/*16 */     bs->request_alignment = iscsilun->block_size;                             // (11) 0.03906
/*20 */     if (iscsilun->bl.max_xfer_len) {                                          // (13) 0.03711
/*22 */         max_xfer_len = MIN(max_xfer_len, iscsilun->bl.max_xfer_len);          // (3) 0.07227
/*24 */     }                                                                         // (19) 0.007812
/*28 */     if (max_xfer_len * iscsilun->block_size < INT_MAX) {                      // (6) 0.05078
/*30 */         bs->bl.max_transfer = max_xfer_len * iscsilun->block_size;            // (5) 0.0625
/*32 */     }                                                                         // (20) 0.007812
/*36 */     if (iscsilun->lbp.lbpu) {                                                 // (16) 0.03125
/*38 */         if (iscsilun->bl.max_unmap < 0xffffffff) {                            // (7) 0.05078
/*40 */             bs->bl.max_discard =                                              // (10) 0.04102
/*42 */                 sector_limits_lun2qemu(iscsilun->bl.max_unmap, iscsilun);     // (0) 0.08203
/*44 */         }                                                                     // (17) 0.01562
/*46 */         bs->bl.discard_alignment =                                            // (15) 0.03516
/*48 */             sector_limits_lun2qemu(iscsilun->bl.opt_unmap_gran, iscsilun);    // (1) 0.07812
/*50 */     } else {                                                                  // (18) 0.01172
/*52 */         bs->bl.discard_alignment = iscsilun->block_size >> BDRV_SECTOR_BITS;  // (2) 0.07422
/*54 */     }                                                                         // (21) 0.007812
/*58 */     if (iscsilun->bl.max_ws_len < 0xffffffff / iscsilun->block_size) {        // 0.0
/*60 */         bs->bl.max_pwrite_zeroes =                                            // 0.0
/*62 */             iscsilun->bl.max_ws_len * iscsilun->block_size;                   // 0.0
/*64 */     }                                                                         // 0.0
/*66 */     if (iscsilun->lbp.lbpws) {                                                // 0.0
/*68 */         bs->bl.pwrite_zeroes_alignment =                                      // 0.0
/*70 */             iscsilun->bl.opt_unmap_gran * iscsilun->block_size;               // 0.0
/*72 */     } else {                                                                  // 0.0
/*74 */         bs->bl.pwrite_zeroes_alignment = iscsilun->block_size;                // 0.0
/*76 */     }                                                                         // 0.0
/*78 */     if (iscsilun->bl.opt_xfer_len &&                                          // 0.0
/*80 */         iscsilun->bl.opt_xfer_len < INT_MAX / iscsilun->block_size) {         // 0.0
/*82 */         bs->bl.opt_transfer = pow2floor(iscsilun->bl.opt_xfer_len *           // 0.0
/*84 */                                         iscsilun->block_size);                // 0.0
/*86 */     }                                                                         // 0.0
/*88 */ }                                                                             // 0.0
