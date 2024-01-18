// commit message qemu@2c6942fa7b (target=0, prob=0.0075123054, correct=True): block: Clean up remaining users of "removable"
/*0 */ int bdrv_is_removable(BlockDriverState *bs)  // (0) 0.4444
/*2 */ {                                            // (2) 0.02778
/*4 */     return bs->removable;                    // (1) 0.2778
/*6 */ }                                            // (3) 0.02778
