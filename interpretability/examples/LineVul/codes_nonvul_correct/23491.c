// commit message qemu@61007b316c (target=0, prob=0.08891296, correct=True): block: move I/O request processing to block/io.c
/*0  */ BlockDriverState *bdrv_next(BlockDriverState *bs)  // (2) 0.1975
/*2  */ {                                                  // (5) 0.01235
/*4  */     if (!bs) {                                     // (3) 0.09877
/*6  */         return QTAILQ_FIRST(&bdrv_states);         // (0) 0.2716
/*8  */     }                                              // (4) 0.04938
/*10 */     return QTAILQ_NEXT(bs, device_list);           // (1) 0.2222
/*12 */ }                                                  // (6) 0.01235
