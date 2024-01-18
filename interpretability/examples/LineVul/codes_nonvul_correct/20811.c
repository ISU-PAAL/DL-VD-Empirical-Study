// commit message qemu@61007b316c (target=0, prob=0.009746914, correct=True): block: move I/O request processing to block/io.c
/*0 */ int bdrv_is_read_only(BlockDriverState *bs)  // (0) 0.4474
/*2 */ {                                            // (2) 0.02632
/*4 */     return bs->read_only;                    // (1) 0.2895
/*6 */ }                                            // (3) 0.02632
