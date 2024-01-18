// commit message qemu@95129d6fc9 (target=0, prob=0.05534577, correct=True): virtio: avoid leading underscores for helpers
/*0 */ static bool use_multiport(VirtIOSerial *vser)                     // (2) 0.2152
/*2 */ {                                                                 // (3) 0.01266
/*4 */     VirtIODevice *vdev = VIRTIO_DEVICE(vser);                     // (1) 0.2785
/*6 */     return virtio_has_feature(vdev, VIRTIO_CONSOLE_F_MULTIPORT);  // (0) 0.3671
/*8 */ }                                                                 // (4) 0.01266
