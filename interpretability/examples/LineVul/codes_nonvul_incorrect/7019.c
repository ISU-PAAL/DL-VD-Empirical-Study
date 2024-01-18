// commit message qemu@aaa0eb75e2 (target=0, prob=0.9610895, correct=False): Count dirty blocks and expose an API to get dirty count
/*0  */ static void set_dirty_bitmap(BlockDriverState *bs, int64_t sector_num,   // (3) 0.06725
/*2  */                              int nb_sectors, int dirty)                  // (0) 0.1111
/*4  */ {                                                                        // (17) 0.002924
/*6  */     int64_t start, end;                                                  // (13) 0.03216
/*8  */     unsigned long val, idx, bit;                                         // (11) 0.03509
/*12 */     start = sector_num / BDRV_SECTORS_PER_DIRTY_CHUNK;                   // (2) 0.07602
/*14 */     end = (sector_num + nb_sectors - 1) / BDRV_SECTORS_PER_DIRTY_CHUNK;  // (1) 0.1053
/*18 */     for (; start <= end; start++) {                                      // (10) 0.03801
/*20 */         idx = start / (sizeof(unsigned long) * 8);                       // (4) 0.06433
/*22 */         bit = start % (sizeof(unsigned long) * 8);                       // (5) 0.0614
/*24 */         val = bs->dirty_bitmap[idx];                                     // (7) 0.05848
/*26 */         if (dirty) {                                                     // (12) 0.03509
/*28 */             val |= 1 << bit;                                             // (9) 0.05263
/*30 */         } else {                                                         // (14) 0.02924
/*32 */             val &= ~(1 << bit);                                          // (8) 0.05848
/*34 */         }                                                                // (15) 0.02339
/*36 */         bs->dirty_bitmap[idx] = val;                                     // (6) 0.0614
/*38 */     }                                                                    // (16) 0.0117
/*40 */ }                                                                        // (18) 0.002924
