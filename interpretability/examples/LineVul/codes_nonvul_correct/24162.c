// commit message qemu@a22313deca (target=0, prob=0.38560572, correct=True): hw/vfio/platform: change interrupt/unmask fields into pointer
/*0  */ static void vfio_platform_eoi(VFIODevice *vbasedev)                        // (11) 0.04102
/*2  */ {                                                                          // (21) 0.001953
/*4  */     VFIOINTp *intp;                                                        // (17) 0.02344
/*6  */     VFIOPlatformDevice *vdev =                                             // (15) 0.02539
/*8  */         container_of(vbasedev, VFIOPlatformDevice, vbasedev);              // (7) 0.05078
/*12 */     qemu_mutex_lock(&vdev->intp_mutex);                                    // (12) 0.04102
/*14 */     QLIST_FOREACH(intp, &vdev->intp_list, next) {                          // (9) 0.04688
/*16 */         if (intp->state == VFIO_IRQ_ACTIVE) {                              // (8) 0.04883
/*18 */             trace_vfio_platform_eoi(intp->pin,                             // (4) 0.05273
/*20 */                                 event_notifier_get_fd(&intp->interrupt));  // (0) 0.08984
/*22 */             intp->state = VFIO_IRQ_INACTIVE;                               // (5) 0.05273
/*26 */             /* deassert the virtual IRQ */                                 // (13) 0.03711
/*28 */             qemu_set_irq(intp->qemuirq, 0);                                // (3) 0.06055
/*32 */             if (intp->flags & VFIO_IRQ_INFO_AUTOMASKED) {                  // (2) 0.06641
/*34 */                 /* unmasks the physical level-sensitive IRQ */             // (6) 0.05273
/*36 */                 vfio_unmask_single_irqindex(vbasedev, intp->pin);          // (1) 0.07227
/*38 */             }                                                              // (18) 0.02344
/*42 */             /* a single IRQ can be active at a time */                     // (10) 0.04492
/*44 */             break;                                                         // (16) 0.02539
/*46 */         }                                                                  // (19) 0.01562
/*48 */     }                                                                      // (20) 0.007812
/*50 */     /* in case there are pending IRQs, handle the first one */             // (14) 0.03516
/*52 */     if (!QSIMPLEQ_EMPTY(&vdev->pending_intp_queue)) {                      // 0.0
/*54 */         intp = QSIMPLEQ_FIRST(&vdev->pending_intp_queue);                  // 0.0
/*56 */         vfio_intp_inject_pending_lockheld(intp);                           // 0.0
/*58 */         QSIMPLEQ_REMOVE_HEAD(&vdev->pending_intp_queue, pqnext);           // 0.0
/*60 */     }                                                                      // 0.0
/*62 */     qemu_mutex_unlock(&vdev->intp_mutex);                                  // 0.0
/*64 */ }                                                                          // 0.0
