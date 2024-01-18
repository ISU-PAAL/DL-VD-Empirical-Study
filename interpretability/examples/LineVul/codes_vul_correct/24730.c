// commit message qemu@ce137829e7 (target=1, prob=0.6149312, correct=True): block/vvfat: Fix potential memory leaks and other memory errors
/*0 */ static void write_target_close(BlockDriverState *bs) {     // (1) 0.1829
/*2 */     BDRVVVFATState* s = *((BDRVVVFATState**) bs->opaque);  // (0) 0.3902
/*4 */     bdrv_delete(s->qcow);                                  // (2) 0.1707
/*6 */     free(s->qcow_filename);                                // (3) 0.1463
/*8 */ }                                                          // (4) 0.0122
