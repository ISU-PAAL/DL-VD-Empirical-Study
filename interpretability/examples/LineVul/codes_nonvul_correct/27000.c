// commit message qemu@67a0fd2a9b (target=0, prob=0.05060632, correct=True): block: Add "file" output parameter to block status query functions
/*0  */ static int64_t coroutine_fn parallels_co_get_block_status(BlockDriverState *bs,  // (2) 0.1059
/*2  */         int64_t sector_num, int nb_sectors, int *pnum)                           // (1) 0.1144
/*4  */ {                                                                                // (12) 0.004237
/*6  */     BDRVParallelsState *s = bs->opaque;                                          // (4) 0.08051
/*8  */     int64_t offset;                                                              // (10) 0.03814
/*12 */     qemu_co_mutex_lock(&s->lock);                                                // (7) 0.07627
/*14 */     offset = block_status(s, sector_num, nb_sectors, pnum);                      // (3) 0.1017
/*16 */     qemu_co_mutex_unlock(&s->lock);                                              // (6) 0.08051
/*20 */     if (offset < 0) {                                                            // (8) 0.04237
/*22 */         return 0;                                                                // (9) 0.04237
/*24 */     }                                                                            // (11) 0.01695
/*28 */     return (offset << BDRV_SECTOR_BITS) |                                        // (5) 0.08051
/*30 */         BDRV_BLOCK_DATA | BDRV_BLOCK_OFFSET_VALID;                               // (0) 0.1229
/*32 */ }                                                                                // (13) 0.004237
