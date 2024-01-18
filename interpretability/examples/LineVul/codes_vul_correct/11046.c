// commit message qemu@f5aa4bdc76 (target=1, prob=0.9991304, correct=True): tests: fix ide-test leaks
/*0  */ static void test_flush_nodev(void)                               // (6) 0.0582
/*2  */ {                                                                // (10) 0.005291
/*4  */     QPCIDevice *dev;                                             // (7) 0.0582
/*6  */     QPCIBar bmdma_bar, ide_bar;                                  // (3) 0.08995
/*10 */     ide_test_start("");                                          // (8) 0.05291
/*14 */     dev = get_pci_device(&bmdma_bar, &ide_bar);                  // (2) 0.1217
/*18 */     /* FLUSH CACHE command on device 0*/                         // (5) 0.07407
/*20 */     qpci_io_writeb(dev, ide_bar, reg_device, 0);                 // (1) 0.127
/*22 */     qpci_io_writeb(dev, ide_bar, reg_command, CMD_FLUSH_CACHE);  // (0) 0.1693
/*26 */     /* Just testing that qemu doesn't crash... */                // (4) 0.07937
/*31 */     ide_test_quit();                                             // (9) 0.04762
/*33 */ }                                                                // (11) 0.005291
