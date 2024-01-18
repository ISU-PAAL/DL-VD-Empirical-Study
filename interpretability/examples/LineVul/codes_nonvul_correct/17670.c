// commit message qemu@eda470e41a (target=0, prob=0.2248123, correct=True): scsi: Drop scsi_req_abort
/*0  */ void scsi_req_abort(SCSIRequest *req, int status)  // (0) 0.1091
/*2  */ {                                                  // (12) 0.006061
/*4  */     if (!req->enqueued) {                          // (7) 0.07273
/*6  */         return;                                    // (9) 0.05455
/*8  */     }                                              // (10) 0.02424
/*10 */     scsi_req_ref(req);                             // (8) 0.07273
/*12 */     scsi_req_dequeue(req);                         // (4) 0.07879
/*14 */     req->io_canceled = true;                       // (5) 0.07879
/*16 */     if (req->ops->cancel_io) {                     // (2) 0.09091
/*18 */         req->ops->cancel_io(req);                  // (1) 0.1091
/*20 */     }                                              // (11) 0.02424
/*22 */     scsi_req_complete(req, status);                // (3) 0.08485
/*24 */     scsi_req_unref(req);                           // (6) 0.07879
/*26 */ }                                                  // (13) 0.006061
