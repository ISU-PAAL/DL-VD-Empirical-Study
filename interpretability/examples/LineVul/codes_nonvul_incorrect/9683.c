// commit message qemu@d0d7708ba2 (target=0, prob=0.9508164, correct=False): qemu-char: add logfile facility to all chardev backends
/*0  */ CharDriverState *qemu_chr_alloc(void)                           // (2) 0.1899
/*2  */ {                                                               // (5) 0.01266
/*4  */     CharDriverState *chr = g_malloc0(sizeof(CharDriverState));  // (0) 0.2911
/*6  */     qemu_mutex_init(&chr->chr_write_lock);                      // (1) 0.2785
/*8  */     return chr;                                                 // (3) 0.08861
/*10 */ }                                                               // (4) 0.01266
