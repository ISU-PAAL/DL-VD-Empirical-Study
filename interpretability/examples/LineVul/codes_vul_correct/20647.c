// commit message qemu@f5ed36635d (target=1, prob=0.9990859, correct=True): virtio: stop virtqueue processing if device is broken
/*0 */ static void virtio_queue_notify_vq(VirtQueue *vq)            // (3) 0.1626
/*1 */ {                                                            // (5) 0.00813
/*2 */     if (vq->vring.desc && vq->handle_output) {               // (2) 0.1707
/*3 */         VirtIODevice *vdev = vq->vdev;                       // (1) 0.1789
/*4 */         trace_virtio_queue_notify(vdev, vq - vdev->vq, vq);  // (0) 0.2602
/*5 */         vq->handle_output(vdev, vq);                         // (4) 0.1626
