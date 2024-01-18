// commit message qemu@3daa41078a (target=1, prob=0.39195973, correct=False): scsi: revert change to scsi_req_cancel_async and add assertions
/*0  */ void scsi_req_cancel(SCSIRequest *req)                        // (3) 0.07895
/*2  */ {                                                             // (14) 0.005263
/*4  */     trace_scsi_req_cancel(req->dev->id, req->lun, req->tag);  // (0) 0.1474
/*6  */     if (!req->enqueued) {                                     // (7) 0.06316
/*8  */         return;                                               // (9) 0.04737
/*10 */     }                                                         // (11) 0.02105
/*14 */     scsi_req_ref(req);                                        // (8) 0.06316
/*16 */     scsi_req_dequeue(req);                                    // (4) 0.06842
/*18 */     req->io_canceled = true;                                  // (5) 0.06842
/*20 */     if (req->aiocb) {                                         // (6) 0.06316
/*22 */         blk_aio_cancel(req->aiocb);                           // (1) 0.1158
/*24 */     } else {                                                  // (10) 0.03158
/*26 */         scsi_req_cancel_complete(req);                        // (2) 0.1
/*28 */     }                                                         // (12) 0.02105
/*30 */ }                                                             // (13) 0.005263
