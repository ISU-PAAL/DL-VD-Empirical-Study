// commit message qemu@9f1963b3f7 (target=0, prob=0.013368852, correct=True): block: Convert bdrv_co_discard() to byte-based
/*0 */ static int coroutine_fn raw_co_discard(BlockDriverState *bs,                // (2) 0.1696
/*2 */                                        int64_t sector_num, int nb_sectors)  // (0) 0.4732
/*4 */ {                                                                           // (3) 0.008929
/*6 */     return bdrv_co_discard(bs->file->bs, sector_num, nb_sectors);           // (1) 0.2589
/*8 */ }                                                                           // (4) 0.008929
