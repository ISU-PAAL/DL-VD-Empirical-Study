// commit message qemu@ea486926b0 (target=0, prob=0.30917752, correct=True): vfio-pci: Update slow path INTx algorithm
/*0   */ static int vfio_enable_intx(VFIODevice *vdev)                                  // (9) 0.03906
/*2   */ {                                                                              // (24) 0.001953
/*4   */     VFIOIRQSetFD irq_set_fd = {                                                // (10) 0.03516
/*6   */         .irq_set = {                                                           // (15) 0.02734
/*8   */             .argsz = sizeof(irq_set_fd),                                       // (7) 0.04688
/*10  */             .flags = VFIO_IRQ_SET_DATA_EVENTFD | VFIO_IRQ_SET_ACTION_TRIGGER,  // (0) 0.08594
/*12  */             .index = VFIO_PCI_INTX_IRQ_INDEX,                                  // (3) 0.05859
/*14  */             .start = 0,                                                        // (13) 0.03125
/*16  */             .count = 1,                                                        // (14) 0.03125
/*18  */         },                                                                     // (18) 0.01563
/*20  */     };                                                                         // (21) 0.007813
/*22  */     uint8_t pin = vfio_pci_read_config(&vdev->pdev, PCI_INTERRUPT_PIN, 1);     // (2) 0.07227
/*24  */     int ret;                                                                   // (20) 0.01172
/*28  */     if (vdev->intx.disabled || !pin) {                                         // (11) 0.0332
/*30  */         return 0;                                                              // (16) 0.01953
/*32  */     }                                                                          // (22) 0.007813
/*36  */     vfio_disable_interrupts(vdev);                                             // (12) 0.03125
/*40  */     vdev->intx.pin = pin - 1; /* Pin A (1) -> irq[0] */                        // (5) 0.05469
/*42  */     ret = event_notifier_init(&vdev->intx.interrupt, 0);                       // (8) 0.04492
/*44  */     if (ret) {                                                                 // (19) 0.01562
/*46  */         error_report("vfio: Error: event_notifier_init failed\n");             // (6) 0.05273
/*48  */         return ret;                                                            // (17) 0.01953
/*50  */     }                                                                          // (23) 0.007812
/*54  */     irq_set_fd.fd = event_notifier_get_fd(&vdev->intx.interrupt);              // (4) 0.05859
/*56  */     qemu_set_fd_handler(irq_set_fd.fd, vfio_intx_interrupt, NULL, vdev);       // (1) 0.07227
/*60  */     if (ioctl(vdev->fd, VFIO_DEVICE_SET_IRQS, &irq_set_fd)) {                  // 0.0
/*62  */         error_report("vfio: Error: Failed to setup INTx fd: %m\n");            // 0.0
/*64  */         return -errno;                                                         // 0.0
/*66  */     }                                                                          // 0.0
/*70  */     /*                                                                         // 0.0
/*72  */      * Disable mmaps so we can trap on BAR accesses.  We interpret any         // 0.0
/*74  */      * access as a response to an interrupt and unmask the physical            // 0.0
/*76  */      * device.  The device will re-assert if the interrupt is still            // 0.0
/*78  */      * pending.  We'll likely retrigger on the host multiple times per         // 0.0
/*80  */      * guest interrupt, but without EOI notification it's better than          // 0.0
/*82  */      * nothing.  Acceleration paths through KVM will avoid this.               // 0.0
/*84  */      */                                                                        // 0.0
/*86  */     vfio_mmap_set_enabled(vdev, false);                                        // 0.0
/*90  */     vdev->interrupt = VFIO_INT_INTx;                                           // 0.0
/*94  */     DPRINTF("%s(%04x:%02x:%02x.%x)\n", __func__, vdev->host.domain,            // 0.0
/*96  */             vdev->host.bus, vdev->host.slot, vdev->host.function);             // 0.0
/*100 */     return 0;                                                                  // 0.0
/*102 */ }                                                                              // 0.0
