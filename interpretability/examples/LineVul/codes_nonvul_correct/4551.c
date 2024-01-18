// commit message qemu@46746dbaa8 (target=0, prob=0.24403341, correct=True): vfio/pci: Make interrupt bypass runtime configurable
/*0   */ static void vfio_intx_enable_kvm(VFIOPCIDevice *vdev)                         // (6) 0.04883
/*2   */ {                                                                             // (26) 0.001953
/*4   */ #ifdef CONFIG_KVM                                                             // (22) 0.01367
/*6   */     struct kvm_irqfd irqfd = {                                                // (14) 0.0293
/*8   */         .fd = event_notifier_get_fd(&vdev->intx.interrupt),                   // (2) 0.05469
/*10  */         .gsi = vdev->intx.route.irq,                                          // (9) 0.04297
/*12  */         .flags = KVM_IRQFD_FLAG_RESAMPLE,                                     // (8) 0.04492
/*14  */     };                                                                        // (23) 0.007812
/*16  */     struct vfio_irq_set *irq_set;                                             // (11) 0.03516
/*18  */     int ret, argsz;                                                           // (20) 0.01758
/*20  */     int32_t *pfd;                                                             // (17) 0.02148
/*24  */     if (!VFIO_ALLOW_KVM_INTX || !kvm_irqfds_enabled() ||                      // (1) 0.05859
/*26  */         vdev->intx.route.mode != PCI_INTX_ENABLED ||                          // (5) 0.05078
/*28  */         !kvm_resamplefds_enabled()) {                                         // (10) 0.03711
/*30  */         return;                                                               // (21) 0.01758
/*32  */     }                                                                         // (24) 0.007812
/*36  */     /* Get to a known interrupt state */                                      // (18) 0.02148
/*38  */     qemu_set_fd_handler(irqfd.fd, NULL, NULL, vdev);                          // (4) 0.05078
/*40  */     vfio_mask_single_irqindex(&vdev->vbasedev, VFIO_PCI_INTX_IRQ_INDEX);      // (0) 0.07422
/*42  */     vdev->intx.pending = false;                                               // (16) 0.02734
/*44  */     pci_irq_deassert(&vdev->pdev);                                            // (12) 0.0332
/*48  */     /* Get an eventfd for resample/unmask */                                  // (15) 0.0293
/*50  */     if (event_notifier_init(&vdev->intx.unmask, 0)) {                         // (7) 0.04687
/*52  */         error_report("vfio: Error: event_notifier_init failed eoi");          // (3) 0.05273
/*54  */         goto fail;                                                            // (19) 0.01953
/*56  */     }                                                                         // (25) 0.007812
/*60  */     /* KVM triggers it, VFIO listens for it */                                // (13) 0.03125
/*62  */     irqfd.resamplefd = event_notifier_get_fd(&vdev->intx.unmask);             // 0.0
/*66  */     if (kvm_vm_ioctl(kvm_state, KVM_IRQFD, &irqfd)) {                         // 0.0
/*68  */         error_report("vfio: Error: Failed to setup resample irqfd: %m");      // 0.0
/*70  */         goto fail_irqfd;                                                      // 0.0
/*72  */     }                                                                         // 0.0
/*76  */     argsz = sizeof(*irq_set) + sizeof(*pfd);                                  // 0.0
/*80  */     irq_set = g_malloc0(argsz);                                               // 0.0
/*82  */     irq_set->argsz = argsz;                                                   // 0.0
/*84  */     irq_set->flags = VFIO_IRQ_SET_DATA_EVENTFD | VFIO_IRQ_SET_ACTION_UNMASK;  // 0.0
/*86  */     irq_set->index = VFIO_PCI_INTX_IRQ_INDEX;                                 // 0.0
/*88  */     irq_set->start = 0;                                                       // 0.0
/*90  */     irq_set->count = 1;                                                       // 0.0
/*92  */     pfd = (int32_t *)&irq_set->data;                                          // 0.0
/*96  */     *pfd = irqfd.resamplefd;                                                  // 0.0
/*100 */     ret = ioctl(vdev->vbasedev.fd, VFIO_DEVICE_SET_IRQS, irq_set);            // 0.0
/*102 */     g_free(irq_set);                                                          // 0.0
/*104 */     if (ret) {                                                                // 0.0
/*106 */         error_report("vfio: Error: Failed to setup INTx unmask fd: %m");      // 0.0
/*108 */         goto fail_vfio;                                                       // 0.0
/*110 */     }                                                                         // 0.0
/*114 */     /* Let'em rip */                                                          // 0.0
/*116 */     vfio_unmask_single_irqindex(&vdev->vbasedev, VFIO_PCI_INTX_IRQ_INDEX);    // 0.0
/*120 */     vdev->intx.kvm_accel = true;                                              // 0.0
/*124 */     trace_vfio_intx_enable_kvm(vdev->vbasedev.name);                          // 0.0
/*128 */     return;                                                                   // 0.0
/*132 */ fail_vfio:                                                                    // 0.0
/*134 */     irqfd.flags = KVM_IRQFD_FLAG_DEASSIGN;                                    // 0.0
/*136 */     kvm_vm_ioctl(kvm_state, KVM_IRQFD, &irqfd);                               // 0.0
/*138 */ fail_irqfd:                                                                   // 0.0
/*140 */     event_notifier_cleanup(&vdev->intx.unmask);                               // 0.0
/*142 */ fail:                                                                         // 0.0
/*144 */     qemu_set_fd_handler(irqfd.fd, vfio_intx_interrupt, NULL, vdev);           // 0.0
/*146 */     vfio_unmask_single_irqindex(&vdev->vbasedev, VFIO_PCI_INTX_IRQ_INDEX);    // 0.0
/*148 */ #endif                                                                        // 0.0
/*150 */ }                                                                             // 0.0
