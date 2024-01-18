// commit message qemu@e8a095dadb (target=1, prob=0.36982045, correct=False): block: use safe iteration over AioContext notifiers
/*0  */ void bdrv_remove_aio_context_notifier(BlockDriverState *bs,                       // (9) 0.04403
/*2  */                                       void (*attached_aio_context)(AioContext *,  // (1) 0.109
/*4  */                                                                    void *),       // (0) 0.1447
/*6  */                                       void (*detach_aio_context)(void *),         // (2) 0.1048
/*8  */                                       void *opaque)                               // (3) 0.08805
/*10 */ {                                                                                 // (17) 0.002096
/*12 */     BdrvAioNotifier *ban, *ban_next;                                              // (10) 0.03774
/*16 */     QLIST_FOREACH_SAFE(ban, &bs->aio_notifiers, list, ban_next) {                 // (6) 0.06289
/*18 */         if (ban->attached_aio_context == attached_aio_context &&                  // (7) 0.05451
/*20 */             ban->detach_aio_context   == detach_aio_context   &&                  // (4) 0.06709
/*22 */             ban->opaque               == opaque)                                  // (5) 0.06709
/*24 */         {                                                                         // (13) 0.01677
/*26 */             QLIST_REMOVE(ban, list);                                              // (8) 0.04612
/*28 */             g_free(ban);                                                          // (11) 0.03564
/*32 */             return;                                                               // (12) 0.02725
/*34 */         }                                                                         // (14) 0.01677
/*36 */     }                                                                             // (16) 0.008386
/*40 */     abort();                                                                      // (15) 0.01048
/*42 */ }                                                                                 // (18) 0.002096
