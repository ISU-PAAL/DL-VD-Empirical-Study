// commit message qemu@d22b2f41c4 (target=1, prob=0.32192037, correct=False): Do not delete BlockDriverState when deleting the drive
/*0  */ void bdrv_delete(BlockDriverState *bs)          // (3) 0.07429
/*2  */ {                                               // (12) 0.005714
/*4  */     assert(!bs->peer);                          // (9) 0.05714
/*8  */     /* remove from list, if necessary */        // (6) 0.06286
/*10 */     if (bs->device_name[0] != '\0') {           // (1) 0.1086
/*12 */         QTAILQ_REMOVE(&bdrv_states, bs, list);  // (0) 0.1543
/*14 */     }                                           // (10) 0.02286
/*18 */     bdrv_close(bs);                             // (7) 0.06286
/*20 */     if (bs->file != NULL) {                     // (5) 0.06857
/*22 */         bdrv_delete(bs->file);                  // (2) 0.09714
/*24 */     }                                           // (11) 0.02286
/*28 */     assert(bs != bs_snapshots);                 // (4) 0.07429
/*30 */     qemu_free(bs);                              // (8) 0.06286
/*32 */ }                                               // (13) 0.005714
