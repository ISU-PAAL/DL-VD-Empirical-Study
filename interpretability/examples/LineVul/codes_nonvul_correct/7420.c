// commit message qemu@30ca440eec (target=0, prob=0.47740445, correct=True): tests: enable virtio tests on SPAPR
/*0  */ static void hotplug(void)                                                // (3) 0.06481
/*2  */ {                                                                        // (5) 0.009259
/*4  */     qtest_start("-device virtio-net-pci");                               // (2) 0.1667
/*8  */     qpci_plug_device_test("virtio-net-pci", "net1", PCI_SLOT_HP, NULL);  // (0) 0.3148
/*10 */     qpci_unplug_acpi_device_test("net1", PCI_SLOT_HP);                   // (1) 0.25
/*14 */     test_end();                                                          // (4) 0.06481
/*16 */ }                                                                        // (6) 0.009259
