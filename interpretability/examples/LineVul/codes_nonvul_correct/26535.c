// commit message qemu@a980f7f2c2 (target=0, prob=0.43165392, correct=True): tests: use qtest_pc_boot()/qtest_shutdown() in virtio tests
/*0  */ static void qvirtio_scsi_pci_free(QVirtIOSCSI *vs)                              // (2) 0.1263
/*2  */ {                                                                               // (10) 0.005263
/*4  */     int i;                                                                      // (8) 0.03158
/*8  */     for (i = 0; i < vs->num_queues + 2; i++) {                                  // (3) 0.1211
/*10 */         qvirtqueue_cleanup(vs->dev->bus, vs->vq[i], vs->alloc);                 // (1) 0.1632
/*12 */     }                                                                           // (9) 0.02105
/*14 */     pc_alloc_uninit(vs->alloc);                                                 // (5) 0.07368
/*16 */     qvirtio_pci_device_disable(container_of(vs->dev, QVirtioPCIDevice, vdev));  // (0) 0.1789
/*18 */     g_free(vs->dev);                                                            // (6) 0.05789
/*20 */     qpci_free_pc(vs->bus);                                                      // (4) 0.07895
/*22 */     g_free(vs);                                                                 // (7) 0.04737
/*24 */ }                                                                               // (11) 0.005263
