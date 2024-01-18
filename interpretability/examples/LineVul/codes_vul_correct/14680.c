// commit message qemu@523b018dde (target=1, prob=0.9989967, correct=True): tests/vhost-user-bridge: workaround stale vring base
/*0  */ vubr_set_vring_addr_exec(VubrDev *dev, VhostUserMsg *vmsg)                              // (7) 0.05469
/*1  */ {                                                                                       // (17) 0.001953
/*2  */     struct vhost_vring_addr *vra = &vmsg->payload.addr;                                 // (9) 0.04688
/*3  */     unsigned int index = vra->index;                                                    // (16) 0.02344
/*4  */     VubrVirtq *vq = &dev->vq[index];                                                    // (13) 0.04102
/*5  */     DPRINT("vhost_vring_addr:\n");                                                      // (14) 0.03125
/*6  */     DPRINT("    index:  %d\n", vra->index);                                             // (11) 0.04297
/*7  */     DPRINT("    flags:  %d\n", vra->flags);                                             // (12) 0.04297
/*8  */     DPRINT("    desc_user_addr:   0x%016llx\n", vra->desc_user_addr);                   // (4) 0.06836
/*9  */     DPRINT("    used_user_addr:   0x%016llx\n", vra->used_user_addr);                   // (5) 0.06836
/*10 */     DPRINT("    avail_user_addr:  0x%016llx\n", vra->avail_user_addr);                  // (6) 0.06836
/*11 */     DPRINT("    log_guest_addr:   0x%016llx\n", vra->log_guest_addr);                   // (3) 0.07227
/*12 */     vq->desc = (struct vring_desc *)(uintptr_t)qva_to_va(dev, vra->desc_user_addr);     // (1) 0.07617
/*13 */     vq->used = (struct vring_used *)(uintptr_t)qva_to_va(dev, vra->used_user_addr);     // (2) 0.07617
/*14 */     vq->avail = (struct vring_avail *)(uintptr_t)qva_to_va(dev, vra->avail_user_addr);  // (0) 0.08203
/*15 */     vq->log_guest_addr = vra->log_guest_addr;                                           // (10) 0.04492
/*16 */     DPRINT("Setting virtq addresses:\n");                                               // (15) 0.02539
/*17 */     DPRINT("    vring_desc  at %p\n", vq->desc);                                        // (8) 0.04883
/*18 */     DPRINT("    vring_used  at %p\n", vq->used);                                        // 0.0
/*19 */     DPRINT("    vring_avail at %p\n", vq->avail);                                       // 0.0
/*20 */     vq->last_used_index = vq->used->idx;                                                // 0.0
/*21 */     return 0;                                                                           // 0.0
