// commit message qemu@0b8b8753e4 (target=1, prob=0.07879572, correct=False): coroutine: move entry argument to qemu_coroutine_create
/*0  */ static void bdrv_co_drain_bh_cb(void *opaque)  // (0) 0.1681
/*2  */ {                                              // (7) 0.008403
/*4  */     BdrvCoDrainData *data = opaque;            // (3) 0.1261
/*6  */     Coroutine *co = data->co;                  // (5) 0.1008
/*10 */     qemu_bh_delete(data->bh);                  // (4) 0.1261
/*12 */     bdrv_drain_poll(data->bs);                 // (1) 0.1345
/*14 */     data->done = true;                         // (6) 0.07563
/*16 */     qemu_coroutine_enter(co, NULL);            // (2) 0.1345
/*18 */ }                                              // (8) 0.008403
