// commit message qemu@80e1eea37a (target=1, prob=0.8841878, correct=True): tests: fix virtio-blk-test leaks
/*0  */ static void pci_hotplug(void)                                        // (10) 0.02875
/*2  */ {                                                                    // (17) 0.003195
/*4  */     QVirtioPCIDevice *dev;                                           // (7) 0.04473
/*6  */     QOSState *qs;                                                    // (11) 0.02875
/*8  */     const char *arch = qtest_get_arch();                             // (6) 0.04792
/*12 */     qs = pci_test_start();                                           // (8) 0.03834
/*16 */     /* plug secondary disk */                                        // (15) 0.02556
/*18 */     qpci_plug_device_test("virtio-blk-pci", "drv1", PCI_SLOT_HP,     // (0) 0.1086
/*20 */                           "'drive': 'drive1'");                      // (1) 0.1054
/*24 */     dev = virtio_blk_pci_init(qs->pcibus, PCI_SLOT_HP);              // (4) 0.08946
/*26 */     g_assert(dev);                                                   // (12) 0.02875
/*28 */     qvirtio_pci_device_disable(dev);                                 // (5) 0.05112
/*30 */     g_free(dev);                                                     // (13) 0.02875
/*34 */     /* unplug secondary disk */                                      // (14) 0.02875
/*36 */     if (strcmp(arch, "i386") == 0 || strcmp(arch, "x86_64") == 0) {  // (2) 0.1022
/*38 */         qpci_unplug_acpi_device_test("drv1", PCI_SLOT_HP);           // (3) 0.1022
/*40 */     }                                                                // (16) 0.01278
/*42 */     qtest_shutdown(qs);                                              // (9) 0.03514
/*44 */ }                                                                    // (18) 0.003195
