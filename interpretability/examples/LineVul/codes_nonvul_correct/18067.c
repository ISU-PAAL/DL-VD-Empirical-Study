// commit message qemu@b131c74a0e (target=0, prob=0.3226031, correct=True): kvm: Clean up irqfd API
/*0  */ static int kvm_virtio_pci_vq_vector_use(VirtIOPCIProxy *proxy,      // (6) 0.05273
/*2  */                                         unsigned int queue_no,      // (0) 0.08789
/*4  */                                         unsigned int vector,        // (2) 0.08398
/*6  */                                         MSIMessage msg)             // (1) 0.08594
/*8  */ {                                                                   // (23) 0.001953
/*10 */     VirtQueue *vq = virtio_get_queue(proxy->vdev, queue_no);        // (7) 0.04883
/*12 */     EventNotifier *n = virtio_queue_get_guest_notifier(vq);         // (8) 0.04883
/*14 */     VirtIOIRQFD *irqfd = &proxy->vector_irqfd[vector];              // (9) 0.04688
/*16 */     int ret;                                                        // (20) 0.01172
/*20 */     if (irqfd->users == 0) {                                        // (12) 0.02734
/*22 */         ret = kvm_irqchip_add_msi_route(kvm_state, msg);            // (5) 0.05859
/*24 */         if (ret < 0) {                                              // (13) 0.02734
/*26 */             return ret;                                             // (14) 0.02734
/*28 */         }                                                           // (18) 0.01562
/*30 */         irqfd->virq = ret;                                          // (11) 0.03125
/*32 */     }                                                               // (21) 0.007812
/*34 */     irqfd->users++;                                                 // (17) 0.01758
/*38 */     ret = kvm_irqchip_add_irq_notifier(kvm_state, n, irqfd->virq);  // (4) 0.06641
/*40 */     if (ret < 0) {                                                  // (15) 0.01953
/*42 */         if (--irqfd->users == 0) {                                  // (10) 0.03711
/*44 */             kvm_irqchip_release_virq(kvm_state, irqfd->virq);       // (3) 0.06836
/*46 */         }                                                           // (19) 0.01562
/*48 */         return ret;                                                 // (16) 0.01953
/*50 */     }                                                               // (22) 0.007812
/*54 */     virtio_queue_set_guest_notifier_fd_handler(vq, true, true);     // 0.0
/*56 */     return 0;                                                       // 0.0
/*58 */ }                                                                   // 0.0
