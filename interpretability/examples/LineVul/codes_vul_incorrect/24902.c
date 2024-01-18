// commit message qemu@ea8d82a1ed (target=1, prob=0.31530687, correct=False): ahci: Fix sglist memleak in ahci_dma_rw_buf()
/*0 */ void qemu_sglist_destroy(QEMUSGList *qsg)  // (0) 0.4878
/*2 */ {                                          // (2) 0.02439
/*4 */     g_free(qsg->sg);                       // (1) 0.2927
/*7 */ }                                          // (3) 0.02439
