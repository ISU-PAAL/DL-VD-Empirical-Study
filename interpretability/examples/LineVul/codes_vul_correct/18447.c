// commit message qemu@7140778605 (target=1, prob=0.82650846, correct=True): virtio-scsi: Fix acquire/release in dataplane handlers
/*0  */ static bool virtio_scsi_data_plane_handle_cmd(VirtIODevice *vdev,  // (1) 0.1722
/*2  */                                               VirtQueue *vq)       // (0) 0.3377
/*4  */ {                                                                  // (5) 0.006623
/*6  */     VirtIOSCSI *s = (VirtIOSCSI *)vdev;                            // (2) 0.1457
/*10 */     assert(s->ctx && s->dataplane_started);                        // (4) 0.106
/*12 */     return virtio_scsi_handle_cmd_vq(s, vq);                       // (3) 0.1457
/*14 */ }                                                                  // (6) 0.006623
