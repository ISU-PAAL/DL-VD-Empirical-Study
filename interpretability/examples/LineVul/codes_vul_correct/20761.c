// commit message qemu@f3db17b951 (target=1, prob=0.9989176, correct=True): qemu-char: initialize chr_write_lock
/*0 */ CharDriverState *qemu_chr_alloc(void)                           // (1) 0.2679
/*2 */ {                                                               // (3) 0.01786
/*4 */     CharDriverState *chr = g_malloc0(sizeof(CharDriverState));  // (0) 0.4107
/*7 */     return chr;                                                 // (2) 0.125
/*9 */ }                                                               // (4) 0.01786
