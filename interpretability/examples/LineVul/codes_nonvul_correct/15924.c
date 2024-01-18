// commit message qemu@5eb6d9e3ef (target=0, prob=0.45195702, correct=True): uas: Fix / cleanup usb_uas_task error handling
/*0   */ static void usb_uas_task(UASDevice *uas, uas_ui *ui)                           // (7) 0.04492
/*2   */ {                                                                              // (27) 0.001953
/*4   */     uint16_t tag = be16_to_cpu(ui->hdr.tag);                                   // (9) 0.04492
/*6   */     uint64_t lun64 = be64_to_cpu(ui->task.lun);                                // (6) 0.04688
/*8   */     SCSIDevice *dev = usb_uas_get_dev(uas, lun64);                             // (3) 0.05078
/*10  */     int lun = usb_uas_get_lun(lun64);                                          // (10) 0.03906
/*12  */     UASRequest *req;                                                           // (21) 0.01758
/*14  */     uint16_t task_tag;                                                         // (19) 0.02148
/*18  */     req = usb_uas_find_request(uas, be16_to_cpu(ui->hdr.tag));                 // (2) 0.06055
/*20  */     if (req) {                                                                 // (22) 0.01562
/*22  */         goto overlapped_tag;                                                   // (17) 0.02539
/*24  */     }                                                                          // (26) 0.007812
/*28  */     switch (ui->task.function) {                                               // (18) 0.02344
/*30  */     case UAS_TMF_ABORT_TASK:                                                   // (14) 0.0332
/*32  */         task_tag = be16_to_cpu(ui->task.task_tag);                             // (4) 0.05078
/*34  */         trace_usb_uas_tmf_abort_task(uas->dev.addr, tag, task_tag);            // (0) 0.06836
/*36  */         if (dev == NULL) {                                                     // (16) 0.02734
/*38  */             goto bad_target;                                                   // (15) 0.03125
/*40  */         }                                                                      // (23) 0.01562
/*42  */         if (dev->lun != lun) {                                                 // (12) 0.0332
/*44  */             goto incorrect_lun;                                                // (13) 0.0332
/*46  */         }                                                                      // (24) 0.01562
/*48  */         req = usb_uas_find_request(uas, task_tag);                             // (5) 0.04883
/*50  */         if (req && req->dev == dev) {                                          // (11) 0.03516
/*52  */             scsi_req_cancel(req->req);                                         // (8) 0.04492
/*54  */         }                                                                      // (25) 0.01562
/*56  */         usb_uas_queue_response(uas, tag, UAS_RC_TMF_COMPLETE, 0);              // (1) 0.06641
/*58  */         break;                                                                 // (20) 0.01758
/*62  */     case UAS_TMF_LOGICAL_UNIT_RESET:                                           // 0.0
/*64  */         trace_usb_uas_tmf_logical_unit_reset(uas->dev.addr, tag, lun);         // 0.0
/*66  */         if (dev == NULL) {                                                     // 0.0
/*68  */             goto bad_target;                                                   // 0.0
/*70  */         }                                                                      // 0.0
/*72  */         if (dev->lun != lun) {                                                 // 0.0
/*74  */             goto incorrect_lun;                                                // 0.0
/*76  */         }                                                                      // 0.0
/*78  */         qdev_reset_all(&dev->qdev);                                            // 0.0
/*80  */         usb_uas_queue_response(uas, tag, UAS_RC_TMF_COMPLETE, 0);              // 0.0
/*82  */         break;                                                                 // 0.0
/*86  */     default:                                                                   // 0.0
/*88  */         trace_usb_uas_tmf_unsupported(uas->dev.addr, tag, ui->task.function);  // 0.0
/*90  */         usb_uas_queue_response(uas, tag, UAS_RC_TMF_NOT_SUPPORTED, 0);         // 0.0
/*92  */         break;                                                                 // 0.0
/*94  */     }                                                                          // 0.0
/*96  */     return;                                                                    // 0.0
/*100 */ overlapped_tag:                                                                // 0.0
/*102 */     usb_uas_queue_response(uas, req->tag, UAS_RC_OVERLAPPED_TAG, 0);           // 0.0
/*104 */     return;                                                                    // 0.0
/*108 */ bad_target:                                                                    // 0.0
/*110 */     /* FIXME: correct?  [see long comment in usb_uas_command()] */             // 0.0
/*112 */     usb_uas_queue_response(uas, tag, UAS_RC_INVALID_INFO_UNIT, 0);             // 0.0
/*114 */     return;                                                                    // 0.0
/*118 */ incorrect_lun:                                                                 // 0.0
/*120 */     usb_uas_queue_response(uas, tag, UAS_RC_INCORRECT_LUN, 0);                 // 0.0
/*122 */ }                                                                              // 0.0
