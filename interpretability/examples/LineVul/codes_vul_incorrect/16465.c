// commit message qemu@231bb26764 (target=1, prob=0.29828617, correct=False): qcow2: Use negated overflow check mask
/*0  */ int qcow2_write_l1_entry(BlockDriverState *bs, int l1_index)                   // (7) 0.05581
/*2  */ {                                                                              // (22) 0.002326
/*4  */     BDRVQcowState *s = bs->opaque;                                             // (10) 0.04186
/*6  */     uint64_t buf[L1_ENTRIES_PER_SECTOR];                                       // (8) 0.05116
/*8  */     int l1_start_index;                                                        // (12) 0.02558
/*10 */     int i, ret;                                                                // (17) 0.0186
/*14 */     l1_start_index = l1_index & ~(L1_ENTRIES_PER_SECTOR - 1);                  // (4) 0.07442
/*16 */     for (i = 0; i < L1_ENTRIES_PER_SECTOR; i++) {                              // (5) 0.06279
/*18 */         buf[i] = cpu_to_be64(s->l1_table[l1_start_index + i]);                 // (1) 0.0814
/*20 */     }                                                                          // (19) 0.009302
/*24 */     ret = qcow2_pre_write_overlap_check(bs,                                    // (9) 0.04651
/*26 */             QCOW2_OL_DEFAULT & ~QCOW2_OL_ACTIVE_L1,                            // (2) 0.07907
/*28 */             s->l1_table_offset + 8 * l1_start_index, sizeof(buf));             // (3) 0.07674
/*30 */     if (ret < 0) {                                                             // (13) 0.02326
/*32 */         return ret;                                                            // (14) 0.02326
/*34 */     }                                                                          // (20) 0.009302
/*38 */     BLKDBG_EVENT(bs->file, BLKDBG_L1_UPDATE);                                  // (6) 0.05814
/*40 */     ret = bdrv_pwrite_sync(bs->file, s->l1_table_offset + 8 * l1_start_index,  // (0) 0.08372
/*42 */         buf, sizeof(buf));                                                     // (11) 0.03023
/*44 */     if (ret < 0) {                                                             // (15) 0.02326
/*46 */         return ret;                                                            // (16) 0.02326
/*48 */     }                                                                          // (21) 0.009302
/*52 */     return 0;                                                                  // (18) 0.01395
/*54 */ }                                                                              // (23) 0.002326
