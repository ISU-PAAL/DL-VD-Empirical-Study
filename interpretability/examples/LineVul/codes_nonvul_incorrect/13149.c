// commit message qemu@36b15c79aa (target=0, prob=0.7246424, correct=False): virtio-scsi: start preparing for any_layout
/*0   */ static void virtio_scsi_handle_cmd(VirtIODevice *vdev, VirtQueue *vq)            // (5) 0.05469
/*2   */ {                                                                                // (23) 0.001953
/*4   */     /* use non-QOM casts in the data path */                                     // (15) 0.0293
/*6   */     VirtIOSCSI *s = (VirtIOSCSI *)vdev;                                          // (10) 0.04297
/*8   */     VirtIOSCSICommon *vs = &s->parent_obj;                                       // (13) 0.03906
/*12  */     VirtIOSCSIReq *req;                                                          // (17) 0.02539
/*14  */     int n;                                                                       // (22) 0.01172
/*18  */     while ((req = virtio_scsi_pop_req(s, vq))) {                                 // (9) 0.04492
/*20  */         SCSIDevice *d;                                                           // (16) 0.0293
/*22  */         int out_size, in_size;                                                   // (14) 0.03125
/*24  */         if (req->elem.out_num < 1 || req->elem.in_num < 1) {                     // (2) 0.0625
/*26  */             virtio_scsi_bad_req();                                               // (11) 0.04102
/*28  */         }                                                                        // (20) 0.01562
/*32  */         out_size = req->elem.out_sg[0].iov_len;                                  // (7) 0.05078
/*34  */         in_size = req->elem.in_sg[0].iov_len;                                    // (6) 0.05078
/*36  */         if (out_size < sizeof(VirtIOSCSICmdReq) + vs->cdb_size ||                // (1) 0.06445
/*38  */             in_size < sizeof(VirtIOSCSICmdResp) + vs->sense_size) {              // (0) 0.06641
/*40  */             virtio_scsi_bad_req();                                               // (12) 0.04102
/*42  */         }                                                                        // (21) 0.01562
/*46  */         if (req->elem.out_num > 1 && req->elem.in_num > 1) {                     // (3) 0.0625
/*48  */             virtio_scsi_fail_cmd_req(req);                                       // (8) 0.04883
/*50  */             continue;                                                            // (18) 0.02539
/*52  */         }                                                                        // (19) 0.01562
/*56  */         d = virtio_scsi_device_find(s, req->req.cmd->lun);                       // (4) 0.05859
/*58  */         if (!d) {                                                                // 0.0
/*60  */             req->resp.cmd->response = VIRTIO_SCSI_S_BAD_TARGET;                  // 0.0
/*62  */             virtio_scsi_complete_req(req);                                       // 0.0
/*64  */             continue;                                                            // 0.0
/*66  */         }                                                                        // 0.0
/*68  */         req->sreq = scsi_req_new(d, req->req.cmd->tag,                           // 0.0
/*70  */                                  virtio_scsi_get_lun(req->req.cmd->lun),         // 0.0
/*72  */                                  req->req.cmd->cdb, req);                        // 0.0
/*76  */         if (req->sreq->cmd.mode != SCSI_XFER_NONE) {                             // 0.0
/*78  */             int req_mode =                                                       // 0.0
/*80  */                 (req->elem.in_num > 1 ? SCSI_XFER_FROM_DEV : SCSI_XFER_TO_DEV);  // 0.0
/*84  */             if (req->sreq->cmd.mode != req_mode ||                               // 0.0
/*86  */                 req->sreq->cmd.xfer > req->qsgl.size) {                          // 0.0
/*88  */                 req->resp.cmd->response = VIRTIO_SCSI_S_OVERRUN;                 // 0.0
/*90  */                 virtio_scsi_complete_req(req);                                   // 0.0
/*92  */                 continue;                                                        // 0.0
/*94  */             }                                                                    // 0.0
/*96  */         }                                                                        // 0.0
/*100 */         n = scsi_req_enqueue(req->sreq);                                         // 0.0
/*102 */         if (n) {                                                                 // 0.0
/*104 */             scsi_req_continue(req->sreq);                                        // 0.0
/*106 */         }                                                                        // 0.0
/*108 */     }                                                                            // 0.0
/*110 */ }                                                                                // 0.0
