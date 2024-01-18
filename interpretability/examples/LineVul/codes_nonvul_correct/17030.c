// commit message qemu@7ce21016b6 (target=0, prob=0.3167506, correct=True): block: handle ENOTSUP from discard in generic code
/*0   */ int coroutine_fn bdrv_co_discard(BlockDriverState *bs, int64_t sector_num,         // (3) 0.05469
/*2   */                                  int nb_sectors)                                   // (0) 0.07617
/*4   */ {                                                                                  // (26) 0.001953
/*6   */     int max_discard;                                                               // (22) 0.01758
/*10  */     if (!bs->drv) {                                                                // (18) 0.02148
/*12  */         return -ENOMEDIUM;                                                         // (11) 0.02734
/*14  */     } else if (bdrv_check_request(bs, sector_num, nb_sectors)) {                   // (4) 0.05469
/*16  */         return -EIO;                                                               // (14) 0.02344
/*18  */     } else if (bs->read_only) {                                                    // (12) 0.02734
/*20  */         return -EROFS;                                                             // (15) 0.02344
/*22  */     }                                                                              // (25) 0.007812
/*26  */     bdrv_reset_dirty(bs, sector_num, nb_sectors);                                  // (7) 0.04492
/*30  */     /* Do nothing if disabled.  */                                                 // (16) 0.02148
/*32  */     if (!(bs->open_flags & BDRV_O_UNMAP)) {                                        // (8) 0.04297
/*34  */         return 0;                                                                  // (19) 0.01953
/*36  */     }                                                                              // (24) 0.007813
/*40  */     if (!bs->drv->bdrv_co_discard && !bs->drv->bdrv_aio_discard) {                 // (2) 0.07031
/*42  */         return 0;                                                                  // (21) 0.01953
/*44  */     }                                                                              // (23) 0.007813
/*48  */     max_discard = bs->bl.max_discard ?  bs->bl.max_discard : MAX_DISCARD_DEFAULT;  // (1) 0.07422
/*50  */     while (nb_sectors > 0) {                                                       // (13) 0.02539
/*52  */         int ret;                                                                   // (20) 0.01953
/*54  */         int num = nb_sectors;                                                      // (10) 0.03125
/*58  */         /* align request */                                                        // (17) 0.02148
/*60  */         if (bs->bl.discard_alignment &&                                            // (9) 0.03711
/*62  */             num >= bs->bl.discard_alignment &&                                     // (6) 0.04688
/*64  */             sector_num % bs->bl.discard_alignment) {                               // (5) 0.05273
/*66  */             if (num > bs->bl.discard_alignment) {                                  // 0.0
/*68  */                 num = bs->bl.discard_alignment;                                    // 0.0
/*70  */             }                                                                      // 0.0
/*72  */             num -= sector_num % bs->bl.discard_alignment;                          // 0.0
/*74  */         }                                                                          // 0.0
/*78  */         /* limit request size */                                                   // 0.0
/*80  */         if (num > max_discard) {                                                   // 0.0
/*82  */             num = max_discard;                                                     // 0.0
/*84  */         }                                                                          // 0.0
/*88  */         if (bs->drv->bdrv_co_discard) {                                            // 0.0
/*90  */             ret = bs->drv->bdrv_co_discard(bs, sector_num, num);                   // 0.0
/*92  */         } else {                                                                   // 0.0
/*94  */             BlockDriverAIOCB *acb;                                                 // 0.0
/*96  */             CoroutineIOCompletion co = {                                           // 0.0
/*98  */                 .coroutine = qemu_coroutine_self(),                                // 0.0
/*100 */             };                                                                     // 0.0
/*104 */             acb = bs->drv->bdrv_aio_discard(bs, sector_num, nb_sectors,            // 0.0
/*106 */                                             bdrv_co_io_em_complete, &co);          // 0.0
/*108 */             if (acb == NULL) {                                                     // 0.0
/*110 */                 return -EIO;                                                       // 0.0
/*112 */             } else {                                                               // 0.0
/*114 */                 qemu_coroutine_yield();                                            // 0.0
/*116 */                 ret = co.ret;                                                      // 0.0
/*118 */             }                                                                      // 0.0
/*120 */         }                                                                          // 0.0
/*122 */         if (ret) {                                                                 // 0.0
/*124 */             return ret;                                                            // 0.0
/*126 */         }                                                                          // 0.0
/*130 */         sector_num += num;                                                         // 0.0
/*132 */         nb_sectors -= num;                                                         // 0.0
/*134 */     }                                                                              // 0.0
/*136 */     return 0;                                                                      // 0.0
/*138 */ }                                                                                  // 0.0
