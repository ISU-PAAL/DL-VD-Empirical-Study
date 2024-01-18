// commit message qemu@091b1108ca (target=1, prob=0.06093687, correct=False): COW: Extend checking allocated bits to beyond one sector
/*0  */ static int coroutine_fn cow_co_is_allocated(BlockDriverState *bs,      // (5) 0.0742
/*2  */         int64_t sector_num, int nb_sectors, int *num_same)             // (1) 0.09894
/*4  */ {                                                                      // (15) 0.003534
/*6  */     int64_t bitnum = sector_num + sizeof(struct cow_header_v2) * 8;    // (2) 0.09541
/*8  */     uint64_t offset = (bitnum / 8) & -BDRV_SECTOR_SIZE;                // (3) 0.09541
/*10 */     uint8_t bitmap[BDRV_SECTOR_SIZE];                                  // (7) 0.07067
/*12 */     int ret;                                                           // (11) 0.0212
/*14 */     int changed;                                                       // (12) 0.0212
/*18 */     ret = bdrv_pread(bs->file, offset, &bitmap, sizeof(bitmap));       // (4) 0.09187
/*20 */     if (ret < 0) {                                                     // (9) 0.03534
/*22 */         return ret;                                                    // (10) 0.03534
/*24 */     }                                                                  // (14) 0.01413
/*28 */     bitnum &= BITS_PER_BITMAP_SECTOR - 1;                              // (6) 0.0742
/*30 */     changed = cow_test_bit(bitnum, bitmap);                            // (8) 0.06007
/*32 */     *num_same = cow_find_streak(bitmap, changed, bitnum, nb_sectors);  // (0) 0.1025
/*34 */     return changed;                                                    // (13) 0.0212
/*36 */ }                                                                      // (16) 0.003534
