// commit message qemu@5e003f17ec (target=1, prob=0.99926645, correct=True): block: Make bdrv_next() keep strong references
/*0   */ static int init_blk_migration(QEMUFile *f)                                       // (9) 0.0332
/*2   */ {                                                                                // (31) 0.001953
/*4   */     BlockDriverState *bs;                                                        // (25) 0.01758
/*6   */     BlkMigDevState *bmds;                                                        // (17) 0.02734
/*8   */     int64_t sectors;                                                             // (26) 0.01758
/*10  */     BdrvNextIterator it;                                                         // (24) 0.01953
/*12  */     int i, num_bs = 0;                                                           // (20) 0.02344
/*14  */     struct {                                                                     // (29) 0.009766
/*16  */         BlkMigDevState *bmds;                                                    // (6) 0.03516
/*18  */         BlockDriverState *bs;                                                    // (18) 0.02539
/*20  */     } *bmds_bs;                                                                  // (21) 0.02148
/*22  */     Error *local_err = NULL;                                                     // (22) 0.02148
/*24  */     int ret;                                                                     // (28) 0.01172
/*28  */     block_mig_state.submitted = 0;                                               // (14) 0.0293
/*30  */     block_mig_state.read_done = 0;                                               // (11) 0.03125
/*32  */     block_mig_state.transferred = 0;                                             // (15) 0.0293
/*34  */     block_mig_state.total_sector_sum = 0;                                        // (7) 0.03516
/*36  */     block_mig_state.prev_progress = -1;                                          // (10) 0.0332
/*38  */     block_mig_state.bulk_completed = 0;                                          // (8) 0.03516
/*40  */     block_mig_state.zero_blocks = migrate_zero_blocks();                         // (4) 0.03906
/*44  */     for (bs = bdrv_first(&it); bs; bs = bdrv_next(&it)) {                        // (1) 0.05859
/*46  */         num_bs++;                                                                // (23) 0.02148
/*48  */     }                                                                            // (30) 0.007812
/*50  */     bmds_bs = g_malloc0(num_bs * sizeof(*bmds_bs));                              // (2) 0.05273
/*54  */     for (i = 0, bs = bdrv_first(&it); bs; bs = bdrv_next(&it), i++) {            // (0) 0.07227
/*56  */         if (bdrv_is_read_only(bs)) {                                             // (3) 0.04297
/*58  */             continue;                                                            // (19) 0.02539
/*60  */         }                                                                        // (27) 0.01562
/*64  */         sectors = bdrv_nb_sectors(bs);                                           // (5) 0.03906
/*66  */         if (sectors <= 0) {                                                      // (13) 0.0293
/*68  */             ret = sectors;                                                       // (12) 0.0293
/*71  */             goto out;                                                            // (16) 0.02734
/*73  */         }                                                                        // 0.0
/*77  */         bmds = g_new0(BlkMigDevState, 1);                                        // 0.0
/*79  */         bmds->blk = blk_new(BLK_PERM_CONSISTENT_READ, BLK_PERM_ALL);             // 0.0
/*81  */         bmds->blk_name = g_strdup(bdrv_get_device_name(bs));                     // 0.0
/*83  */         bmds->bulk_completed = 0;                                                // 0.0
/*85  */         bmds->total_sectors = sectors;                                           // 0.0
/*87  */         bmds->completed_sectors = 0;                                             // 0.0
/*89  */         bmds->shared_base = migrate_use_block_incremental();                     // 0.0
/*93  */         assert(i < num_bs);                                                      // 0.0
/*95  */         bmds_bs[i].bmds = bmds;                                                  // 0.0
/*97  */         bmds_bs[i].bs = bs;                                                      // 0.0
/*101 */         block_mig_state.total_sector_sum += sectors;                             // 0.0
/*105 */         if (bmds->shared_base) {                                                 // 0.0
/*107 */             DPRINTF("Start migration for %s with shared base image\n",           // 0.0
/*109 */                     bdrv_get_device_name(bs));                                   // 0.0
/*111 */         } else {                                                                 // 0.0
/*113 */             DPRINTF("Start full migration for %s\n", bdrv_get_device_name(bs));  // 0.0
/*115 */         }                                                                        // 0.0
/*119 */         QSIMPLEQ_INSERT_TAIL(&block_mig_state.bmds_list, bmds, entry);           // 0.0
/*121 */     }                                                                            // 0.0
/*125 */     /* Can only insert new BDSes now because doing so while iterating block      // 0.0
/*127 */      * devices may end up in a deadlock (iterating the new BDSes, too). */       // 0.0
/*129 */     for (i = 0; i < num_bs; i++) {                                               // 0.0
/*131 */         BlkMigDevState *bmds = bmds_bs[i].bmds;                                  // 0.0
/*133 */         BlockDriverState *bs = bmds_bs[i].bs;                                    // 0.0
/*137 */         if (bmds) {                                                              // 0.0
/*139 */             ret = blk_insert_bs(bmds->blk, bs, &local_err);                      // 0.0
/*141 */             if (ret < 0) {                                                       // 0.0
/*143 */                 error_report_err(local_err);                                     // 0.0
/*145 */                 goto out;                                                        // 0.0
/*147 */             }                                                                    // 0.0
/*151 */             alloc_aio_bitmap(bmds);                                              // 0.0
/*153 */             error_setg(&bmds->blocker, "block device is in use by migration");   // 0.0
/*155 */             bdrv_op_block_all(bs, bmds->blocker);                                // 0.0
/*157 */         }                                                                        // 0.0
/*159 */     }                                                                            // 0.0
/*163 */     ret = 0;                                                                     // 0.0
/*165 */ out:                                                                             // 0.0
/*167 */     g_free(bmds_bs);                                                             // 0.0
/*169 */     return ret;                                                                  // 0.0
/*171 */ }                                                                                // 0.0
