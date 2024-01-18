// commit message qemu@cdeaf1f159 (target=1, prob=0.1094873, correct=False): vmdk: add bdrv_co_write_zeroes
/*0  */ static coroutine_fn int vmdk_co_write(BlockDriverState *bs, int64_t sector_num,  // (1) 0.1481
/*2  */                                       const uint8_t *buf, int nb_sectors)        // (0) 0.2751
/*4  */ {                                                                                // (8) 0.005291
/*6  */     int ret;                                                                     // (6) 0.03175
/*8  */     BDRVVmdkState *s = bs->opaque;                                               // (3) 0.1005
/*10 */     qemu_co_mutex_lock(&s->lock);                                                // (5) 0.09524
/*12 */     ret = vmdk_write(bs, sector_num, buf, nb_sectors);                           // (2) 0.1323
/*14 */     qemu_co_mutex_unlock(&s->lock);                                              // (4) 0.1005
/*16 */     return ret;                                                                  // (7) 0.03175
/*18 */ }                                                                                // (9) 0.005291
