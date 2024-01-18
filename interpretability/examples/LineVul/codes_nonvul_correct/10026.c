// commit message qemu@61007b316c (target=0, prob=0.060705185, correct=True): block: move I/O request processing to block/io.c
/*0 */ static void bdrv_throttle_write_timer_cb(void *opaque)  // (1) 0.303
/*2 */ {                                                       // (3) 0.01515
/*4 */     BlockDriverState *bs = opaque;                      // (2) 0.1667
/*6 */     qemu_co_enter_next(&bs->throttled_reqs[1]);         // (0) 0.3636
/*8 */ }                                                       // (4) 0.01515
