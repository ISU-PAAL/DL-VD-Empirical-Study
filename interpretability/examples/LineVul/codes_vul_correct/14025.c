// commit message qemu@ad2d30f79d (target=1, prob=0.5684281, correct=True): scsi: reference-count requests
/*0  */ static void scsi_disk_purge_requests(SCSIDiskState *s)                     // (3) 0.1117
/*2  */ {                                                                          // (9) 0.005319
/*4  */     SCSIDiskReq *r;                                                        // (6) 0.06383
/*8  */     while (!QTAILQ_EMPTY(&s->qdev.requests)) {                             // (2) 0.117
/*10 */         r = DO_UPCAST(SCSIDiskReq, req, QTAILQ_FIRST(&s->qdev.requests));  // (0) 0.2128
/*12 */         if (r->req.aiocb) {                                                // (4) 0.09574
/*14 */             bdrv_aio_cancel(r->req.aiocb);                                 // (1) 0.1543
/*16 */         }                                                                  // (7) 0.04255
/*18 */         scsi_remove_request(r);                                            // (5) 0.08511
/*20 */     }                                                                      // (8) 0.02128
/*22 */ }                                                                          // (10) 0.005319
