// commit message qemu@1f8828ef57 (target=0, prob=0.06891994, correct=True): virtio-net: unbreak self announcement and guest offloads after migration
/*0  */ static int virtio_net_load(QEMUFile *f, void *opaque, int version_id)  // (0) 0.2
/*2  */ {                                                                      // (6) 0.007692
/*4  */     VirtIONet *n = opaque;                                             // (5) 0.08462
/*6  */     VirtIODevice *vdev = VIRTIO_DEVICE(n);                             // (2) 0.1615
/*10 */     if (version_id < 2 || version_id > VIRTIO_NET_VM_VERSION)          // (1) 0.1923
/*12 */         return -EINVAL;                                                // (4) 0.1
/*16 */     return virtio_load(vdev, f, version_id);                           // (3) 0.1385
/*18 */ }                                                                      // (7) 0.007692
