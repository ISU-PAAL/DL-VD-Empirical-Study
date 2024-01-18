// commit message qemu@e24e49e619 (target=1, prob=0.045555994, correct=False): qcow2: Update whole header at once
/*0 */ static int qcow2_change_backing_file(BlockDriverState *bs,          // (2) 0.2533
/*2 */     const char *backing_file, const char *backing_fmt)              // (1) 0.2667
/*4 */ {                                                                   // (3) 0.01333
/*6 */     return qcow2_update_ext_header(bs, backing_file, backing_fmt);  // (0) 0.3333
/*8 */ }                                                                   // (4) 0.01333
