// commit message qemu@ef8489d459 (target=1, prob=0.30643383, correct=False): scsi: avoid assertion failure on VERIFY command
/*0  */ static void scsi_write_data(SCSIRequest *req)                                               // (14) 0.0293
/*2  */ {                                                                                           // (28) 0.001953
/*4  */     SCSIDiskReq *r = DO_UPCAST(SCSIDiskReq, req, req);                                      // (2) 0.05664
/*6  */     SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, r->req.dev);                          // (1) 0.0625
/*8  */     uint32_t n;                                                                             // (21) 0.01758
/*12 */     /* No data transfer may already be in progress */                                       // (17) 0.02539
/*14 */     assert(r->req.aiocb == NULL);                                                           // (15) 0.0293
/*18 */     /* The request is used as the AIO opaque value, so add a ref.  */                       // (7) 0.04297
/*20 */     scsi_req_ref(&r->req);                                                                  // (16) 0.02734
/*22 */     if (r->req.cmd.mode != SCSI_XFER_TO_DEV) {                                              // (5) 0.04687
/*24 */         DPRINTF("Data transfer direction invalid\n");                                       // (11) 0.03516
/*26 */         scsi_write_complete(r, -EINVAL);                                                    // (9) 0.04102
/*28 */         return;                                                                             // (22) 0.01758
/*30 */     }                                                                                       // (25) 0.007812
/*34 */     if (!r->req.sg && !r->qiov.size) {                                                      // (10) 0.03906
/*36 */         /* Called for the first time.  Ask the driver to send us more data.  */             // (3) 0.05078
/*38 */         r->started = true;                                                                  // (19) 0.02539
/*40 */         scsi_write_complete(r, 0);                                                          // (12) 0.03516
/*42 */         return;                                                                             // (23) 0.01758
/*44 */     }                                                                                       // (26) 0.007812
/*46 */     if (s->tray_open) {                                                                     // (18) 0.02539
/*48 */         scsi_write_complete(r, -ENOMEDIUM);                                                 // (8) 0.04297
/*50 */         return;                                                                             // (24) 0.01758
/*52 */     }                                                                                       // (27) 0.007812
/*56 */     if (r->req.cmd.buf[0] == VERIFY_10 || r->req.cmd.buf[0] == VERIFY_12 ||                 // (0) 0.07617
/*58 */         r->req.cmd.buf[0] == VERIFY_16) {                                                   // (4) 0.04883
/*60 */         if (r->req.sg) {                                                                    // (13) 0.03125
/*62 */             scsi_dma_complete(r, 0);                                                        // (6) 0.04492
/*64 */         } else {                                                                            // (20) 0.01953
/*66 */             scsi_write_complete(r, 0);                                                      // 0.0
/*68 */         }                                                                                   // 0.0
/*70 */         return;                                                                             // 0.0
/*72 */     }                                                                                       // 0.0
/*76 */     if (r->req.sg) {                                                                        // 0.0
/*78 */         dma_acct_start(s->qdev.conf.bs, &r->acct, r->req.sg, BDRV_ACCT_WRITE);              // 0.0
/*80 */         r->req.resid -= r->req.sg->size;                                                    // 0.0
/*82 */         r->req.aiocb = dma_bdrv_write(s->qdev.conf.bs, r->req.sg, r->sector,                // 0.0
/*84 */                                       scsi_dma_complete, r);                                // 0.0
/*86 */     } else {                                                                                // 0.0
/*88 */         n = r->qiov.size / 512;                                                             // 0.0
/*90 */         bdrv_acct_start(s->qdev.conf.bs, &r->acct, n * BDRV_SECTOR_SIZE, BDRV_ACCT_WRITE);  // 0.0
/*92 */         r->req.aiocb = bdrv_aio_writev(s->qdev.conf.bs, r->sector, &r->qiov, n,             // 0.0
/*94 */                                        scsi_write_complete, r);                             // 0.0
/*96 */     }                                                                                       // 0.0
/*98 */ }                                                                                           // 0.0
