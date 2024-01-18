// commit message qemu@8b3b720620 (target=1, prob=0.4278524, correct=False): qcow2: Use bdrv_(p)write_sync for metadata writes
/*0  */ static int write_l1_entry(BlockDriverState *bs, int l1_index)             // (6) 0.0684
/*2  */ {                                                                         // (16) 0.003257
/*4  */     BDRVQcowState *s = bs->opaque;                                        // (7) 0.05863
/*6  */     uint64_t buf[L1_ENTRIES_PER_SECTOR];                                  // (5) 0.07166
/*8  */     int l1_start_index;                                                   // (9) 0.03583
/*10 */     int i, ret;                                                           // (12) 0.02606
/*14 */     l1_start_index = l1_index & ~(L1_ENTRIES_PER_SECTOR - 1);             // (2) 0.1042
/*16 */     for (i = 0; i < L1_ENTRIES_PER_SECTOR; i++) {                         // (3) 0.08795
/*18 */         buf[i] = cpu_to_be64(s->l1_table[l1_start_index + i]);            // (0) 0.114
/*20 */     }                                                                     // (14) 0.01303
/*24 */     BLKDBG_EVENT(bs->file, BLKDBG_L1_UPDATE);                             // (4) 0.08143
/*26 */     ret = bdrv_pwrite(bs->file, s->l1_table_offset + 8 * l1_start_index,  // (1) 0.1107
/*28 */         buf, sizeof(buf));                                                // (8) 0.04235
/*30 */     if (ret < 0) {                                                        // (10) 0.03257
/*32 */         return ret;                                                       // (11) 0.03257
/*34 */     }                                                                     // (15) 0.01303
/*38 */     return 0;                                                             // (13) 0.01954
/*40 */ }                                                                         // (17) 0.003257
