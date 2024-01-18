// commit message qemu@c83c66c3b5 (target=0, prob=0.24417636, correct=True): block: add 'speed' optional parameter to block-stream
/*0  */ void qmp_block_stream(const char *device, bool has_base,                      // (8) 0.041
/*2  */                       const char *base, Error **errp)                         // (1) 0.07062
/*4  */ {                                                                             // (27) 0.002278
/*6  */     BlockDriverState *bs;                                                     // (16) 0.0205
/*8  */     BlockDriverState *base_bs = NULL;                                         // (13) 0.02961
/*10 */     Error *local_err = NULL;                                                  // (15) 0.02506
/*14 */     bs = bdrv_find(device);                                                   // (12) 0.03189
/*16 */     if (!bs) {                                                                // (19) 0.01822
/*18 */         error_set(errp, QERR_DEVICE_NOT_FOUND, device);                       // (3) 0.06378
/*20 */         return;                                                               // (17) 0.0205
/*22 */     }                                                                         // (24) 0.009112
/*26 */     if (base) {                                                               // (20) 0.01822
/*28 */         base_bs = bdrv_find_backing_image(bs, base);                          // (4) 0.05923
/*30 */         if (base_bs == NULL) {                                                // (10) 0.03645
/*32 */             error_set(errp, QERR_BASE_NOT_FOUND, base);                       // (0) 0.07289
/*34 */             return;                                                           // (14) 0.02961
/*36 */         }                                                                     // (21) 0.01822
/*38 */     }                                                                         // (25) 0.009112
/*42 */     stream_start(bs, base_bs, base, block_stream_cb, bs, &local_err);         // (2) 0.06606
/*44 */     if (error_is_set(&local_err)) {                                           // (11) 0.03645
/*46 */         error_propagate(errp, local_err);                                     // (6) 0.04328
/*48 */         return;                                                               // (18) 0.0205
/*50 */     }                                                                         // (26) 0.009112
/*54 */     /* Grab a reference so hotplug does not delete the BlockDriverState from  // (9) 0.041
/*56 */      * underneath us.                                                         // (22) 0.01822
/*58 */      */                                                                       // (23) 0.01139
/*60 */     drive_get_ref(drive_get_by_blockdev(bs));                                 // (5) 0.04556
/*64 */     trace_qmp_block_stream(bs, bs->job);                                      // (7) 0.04328
/*66 */ }                                                                             // (28) 0.002278
