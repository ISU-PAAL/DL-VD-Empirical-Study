// commit message qemu@b85114f8cf (target=0, prob=0.042660605, correct=True): block: Use 'detect-zeroes' option for 'blockdev-change-medium'
/*0 */ void blk_apply_root_state(BlockBackend *blk, BlockDriverState *bs)  // (1) 0.3966
/*2 */ {                                                                   // (2) 0.01724
/*4 */     bs->detect_zeroes = blk->root_state.detect_zeroes;              // (0) 0.431
/*6 */ }                                                                   // (3) 0.01724
