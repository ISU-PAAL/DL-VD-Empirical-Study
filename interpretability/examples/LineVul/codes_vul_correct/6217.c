// commit message qemu@f1d3b99154 (target=1, prob=0.7216104, correct=True): libqos: add qvirtqueue_cleanup()
/*0  */ static void pci_basic(gconstpointer data)                             // (17) 0.02149
/*2  */ {                                                                     // (22) 0.001956
/*4  */     QVirtioPCIDevice *dev;                                            // (16) 0.02734
/*6  */     QPCIBus *bus;                                                     // (21) 0.01953
/*8  */     QVirtQueuePCI *tx, *rx;                                           // (15) 0.0293
/*10 */     QGuestAllocator *alloc;                                           // (19) 0.02148
/*12 */     void (*func) (const QVirtioBus *bus,                              // (12) 0.0332
/*14 */                   QVirtioDevice *dev,                                 // (5) 0.04883
/*16 */                   QGuestAllocator *alloc,                             // (6) 0.04883
/*18 */                   QVirtQueue *rvq,                                    // (4) 0.05078
/*20 */                   QVirtQueue *tvq,                                    // (7) 0.04883
/*22 */                   int socket) = data;                                 // (9) 0.04492
/*24 */     int sv[2], ret;                                                   // (20) 0.01954
/*28 */     ret = socketpair(PF_UNIX, SOCK_STREAM, 0, sv);                    // (8) 0.04493
/*30 */     g_assert_cmpint(ret, !=, -1);                                     // (13) 0.0332
/*34 */     bus = pci_test_start(sv[1]);                                      // (14) 0.0293
/*36 */     dev = virtio_net_pci_init(bus, PCI_SLOT);                         // (10) 0.04297
/*40 */     alloc = pc_alloc_init();                                          // (18) 0.02148
/*42 */     rx = (QVirtQueuePCI *)qvirtqueue_setup(&qvirtio_pci, &dev->vdev,  // (2) 0.06445
/*44 */                                            alloc, 0);                 // (1) 0.08984
/*46 */     tx = (QVirtQueuePCI *)qvirtqueue_setup(&qvirtio_pci, &dev->vdev,  // (3) 0.0625
/*48 */                                            alloc, 1);                 // (0) 0.08984
/*52 */     driver_init(&qvirtio_pci, &dev->vdev);                            // (11) 0.03906
/*54 */     func(&qvirtio_pci, &dev->vdev, alloc, &rx->vq, &tx->vq, sv[0]);   // 0.0
/*58 */     /* End test */                                                    // 0.0
/*60 */     close(sv[0]);                                                     // 0.0
/*62 */     guest_free(alloc, tx->vq.desc);                                   // 0.0
/*64 */     pc_alloc_uninit(alloc);                                           // 0.0
/*66 */     qvirtio_pci_device_disable(dev);                                  // 0.0
/*68 */     g_free(dev);                                                      // 0.0
/*70 */     qpci_free_pc(bus);                                                // 0.0
/*72 */     test_end();                                                       // 0.0
/*74 */ }                                                                     // 0.0
