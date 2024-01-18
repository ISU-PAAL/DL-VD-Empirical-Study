// commit message qemu@1f3ddfcb25 (target=1, prob=0.3200197, correct=False): Revert "qed: Implement .bdrv_drain"
/*0  */ static void bdrv_qed_drain(BlockDriverState *bs)                                // (3) 0.1078
/*2  */ {                                                                               // (9) 0.005988
/*4  */     BDRVQEDState *s = bs->opaque;                                               // (4) 0.1078
/*8  */     /* Cancel timer and start doing I/O that were meant to happen as if it      // (2) 0.1198
/*10 */      * fired, that way we get bdrv_drain() taking care of the ongoing requests  // (1) 0.1437
/*12 */      * correctly. */                                                            // (7) 0.0479
/*14 */     qed_cancel_need_check_timer(s);                                             // (6) 0.1018
/*16 */     qed_plug_allocating_write_reqs(s);                                          // (5) 0.1078
/*18 */     bdrv_aio_flush(s->bs, qed_clear_need_check, s);                             // (0) 0.1617
/*20 */ }                                                                               // (8) 0.005988
