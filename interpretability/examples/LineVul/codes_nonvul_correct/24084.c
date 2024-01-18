// commit message qemu@fa879d62eb (target=0, prob=0.009288597, correct=True): block: Attach non-qdev devices as well
/*0 */ DeviceState *bdrv_get_attached(BlockDriverState *bs)  // (0) 0.4865
/*2 */ {                                                     // (2) 0.02702
/*4 */     return bs->peer;                                  // (1) 0.2433
/*6 */ }                                                     // (3) 0.02702
