// commit message qemu@5c6c0e5136 (target=1, prob=0.4350071, correct=False): scsi: Use 'SCSIRequest' directly
/*0  */ static int vscsi_queue_cmd(VSCSIState *s, vscsi_req *req)                      // (10) 0.04883
/*2  */ {                                                                              // (22) 0.001953
/*4  */     union srp_iu *srp = &req->iu.srp;                                          // (12) 0.03906
/*6  */     SCSIDevice *sdev;                                                          // (13) 0.02344
/*8  */     int n, id, lun;                                                            // (16) 0.01953
/*12 */     vscsi_decode_id_lun(be64_to_cpu(srp->cmd.lun), &id, &lun);                 // (2) 0.07227
/*16 */     /* Qemu vs. linux issue with LUNs to be sorted out ... */                  // (11) 0.04102
/*18 */     sdev = (id < 8 && lun < 16) ? s->bus.devs[id] : NULL;                      // (6) 0.05469
/*20 */     if (!sdev) {                                                               // (19) 0.01758
/*22 */         dprintf("VSCSI: Command for id %d with no drive\n", id);               // (7) 0.05273
/*24 */         if (srp->cmd.cdb[0] == INQUIRY) {                                      // (8) 0.05078
/*26 */             vscsi_inquiry_no_target(s, req);                                   // (9) 0.05078
/*28 */         } else {                                                               // (17) 0.01953
/*30 */             vscsi_makeup_sense(s, req, ILLEGAL_REQUEST, 0x24, 0x00);           // (0) 0.07812
/*32 */             vscsi_send_rsp(s, req, CHECK_CONDITION, 0, 0);                     // (3) 0.06836
/*34 */         } return 1;                                                            // (14) 0.02148
/*36 */     }                                                                          // (21) 0.007813
/*40 */     req->sdev = sdev;                                                          // (15) 0.02148
/*42 */     req->lun = lun;                                                            // (18) 0.01953
/*44 */     n = sdev->info->send_command(sdev, req->qtag, srp->cmd.cdb, lun);          // (4) 0.0625
/*48 */     dprintf("VSCSI: Queued command tag 0x%x CMD 0x%x ID %d LUN %d ret: %d\n",  // (1) 0.07422
/*50 */             req->qtag, srp->cmd.cdb[0], id, lun, n);                           // (5) 0.0625
/*54 */     if (n) {                                                                   // (20) 0.01562
/*56 */         /* Transfer direction must be set before preprocessing the             // 0.0
/*58 */          * descriptors                                                         // 0.0
/*60 */          */                                                                    // 0.0
/*62 */         req->writing = (n < 1);                                                // 0.0
/*66 */         /* Preprocess RDMA descriptors */                                      // 0.0
/*68 */         vscsi_preprocess_desc(req);                                            // 0.0
/*70 */     }                                                                          // 0.0
/*74 */     /* Get transfer direction and initiate transfer */                         // 0.0
/*76 */     if (n > 0) {                                                               // 0.0
/*78 */         req->data_len = n;                                                     // 0.0
/*80 */         sdev->info->read_data(sdev, req->qtag);                                // 0.0
/*82 */     } else if (n < 0) {                                                        // 0.0
/*84 */         req->data_len = -n;                                                    // 0.0
/*86 */         sdev->info->write_data(sdev, req->qtag);                               // 0.0
/*88 */     }                                                                          // 0.0
/*90 */     /* Don't touch req here, it may have been recycled already */              // 0.0
/*94 */     return 0;                                                                  // 0.0
/*96 */ }                                                                              // 0.0
