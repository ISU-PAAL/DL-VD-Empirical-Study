// commit message qemu@77a5a0001b (target=0, prob=0.059764914, correct=True): qed: support for growing images
/*0 */ static int bdrv_qed_truncate(BlockDriverState *bs, int64_t offset)  // (0) 0.5682
/*2 */ {                                                                   // (2) 0.02273
/*4 */     return -ENOTSUP;                                                // (1) 0.2045
/*6 */ }                                                                   // (3) 0.02273
