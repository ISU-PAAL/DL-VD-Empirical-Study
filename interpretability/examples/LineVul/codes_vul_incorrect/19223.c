// commit message qemu@e3f30488e5 (target=1, prob=0.4805437, correct=False): virtio-net: Limit number of packets sent per TX flush
/*0   */ static void virtio_net_flush_tx(VirtIONet *n, VirtQueue *vq)              // (6) 0.04688
/*2   */ {                                                                         // (25) 0.001953
/*4   */     VirtQueueElement elem;                                                // (20) 0.01758
/*8   */     if (!(n->vdev.status & VIRTIO_CONFIG_S_DRIVER_OK))                    // (3) 0.05273
/*10  */         return;                                                           // (21) 0.01758
/*14  */     if (n->async_tx.elem.out_num) {                                       // (10) 0.03906
/*16  */         virtio_queue_set_notification(n->tx_vq, 0);                       // (5) 0.05078
/*18  */         return;                                                           // (22) 0.01758
/*20  */     }                                                                     // (24) 0.007812
/*24  */     while (virtqueue_pop(vq, &elem)) {                                    // (13) 0.03516
/*26  */         ssize_t ret, len = 0;                                             // (15) 0.0332
/*28  */         unsigned int out_num = elem.out_num;                              // (11) 0.03906
/*30  */         struct iovec *out_sg = &elem.out_sg[0];                           // (4) 0.05078
/*32  */         unsigned hdr_len;                                                 // (19) 0.02539
/*36  */         /* hdr_len refers to the header received from the guest */        // (9) 0.04102
/*38  */         hdr_len = n->mergeable_rx_bufs ?                                  // (7) 0.04492
/*40  */             sizeof(struct virtio_net_hdr_mrg_rxbuf) :                     // (1) 0.05664
/*42  */             sizeof(struct virtio_net_hdr);                                // (8) 0.04297
/*46  */         if (out_num < 1 || out_sg->iov_len != hdr_len) {                  // (2) 0.05664
/*48  */             fprintf(stderr, "virtio-net header not in first element\n");  // (0) 0.06055
/*50  */             exit(1);                                                      // (17) 0.0293
/*52  */         }                                                                 // (23) 0.01562
/*56  */         /* ignore the header if GSO is not supported */                   // (14) 0.03516
/*58  */         if (!n->has_vnet_hdr) {                                           // (12) 0.03906
/*60  */             out_num--;                                                    // (16) 0.03125
/*62  */             out_sg++;                                                     // (18) 0.0293
/*64  */             len += hdr_len;                                               // 0.0
/*66  */         } else if (n->mergeable_rx_bufs) {                                // 0.0
/*68  */             /* tapfd expects a struct virtio_net_hdr */                   // 0.0
/*70  */             hdr_len -= sizeof(struct virtio_net_hdr);                     // 0.0
/*72  */             out_sg->iov_len -= hdr_len;                                   // 0.0
/*74  */             len += hdr_len;                                               // 0.0
/*76  */         }                                                                 // 0.0
/*80  */         ret = qemu_sendv_packet_async(&n->nic->nc, out_sg, out_num,       // 0.0
/*82  */                                       virtio_net_tx_complete);            // 0.0
/*84  */         if (ret == 0) {                                                   // 0.0
/*86  */             virtio_queue_set_notification(n->tx_vq, 0);                   // 0.0
/*88  */             n->async_tx.elem = elem;                                      // 0.0
/*90  */             n->async_tx.len  = len;                                       // 0.0
/*92  */             return;                                                       // 0.0
/*94  */         }                                                                 // 0.0
/*98  */         len += ret;                                                       // 0.0
/*102 */         virtqueue_push(vq, &elem, len);                                   // 0.0
/*104 */         virtio_notify(&n->vdev, vq);                                      // 0.0
/*106 */     }                                                                     // 0.0
/*108 */ }                                                                         // 0.0
