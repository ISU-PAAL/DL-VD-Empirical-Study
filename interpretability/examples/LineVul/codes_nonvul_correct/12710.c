// commit message qemu@3eff1f46f0 (target=0, prob=0.34717873, correct=True): virtio-scsi: add support for the any_layout feature
/*0  */ static void virtio_scsi_complete_req(VirtIOSCSIReq *req)                          // (1) 0.107
/*2  */ {                                                                                 // (11) 0.004651
/*4  */     VirtIOSCSI *s = req->dev;                                                     // (5) 0.06977
/*6  */     VirtQueue *vq = req->vq;                                                      // (8) 0.06512
/*8  */     VirtIODevice *vdev = VIRTIO_DEVICE(s);                                        // (2) 0.09767
/*10 */     virtqueue_push(vq, &req->elem, req->qsgl.size + req->elem.in_sg[0].iov_len);  // (0) 0.1814
/*12 */     if (req->sreq) {                                                              // (9) 0.05116
/*14 */         req->sreq->hba_private = NULL;                                            // (4) 0.08837
/*16 */         scsi_req_unref(req->sreq);                                                // (3) 0.09302
/*18 */     }                                                                             // (10) 0.0186
/*20 */     virtio_scsi_free_req(req);                                                    // (6) 0.06977
/*22 */     virtio_notify(vdev, vq);                                                      // (7) 0.06977
/*24 */ }                                                                                 // (12) 0.004651
