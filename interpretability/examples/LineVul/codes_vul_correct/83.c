// commit message qemu@5c6c0e5136 (target=1, prob=0.5073044, correct=True): scsi: Use 'SCSIRequest' directly
/*0  */ static void scsi_read_request(SCSIDiskReq *r)                       // (12) 0.03516
/*2  */ {                                                                   // (26) 0.001953
/*4  */     SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, r->req.dev);  // (2) 0.0625
/*6  */     uint32_t n;                                                     // (20) 0.01758
/*10 */     if (r->sector_count == (uint32_t)-1) {                          // (9) 0.03906
/*12 */         DPRINTF("Read buf_len=%zd\n", r->iov.iov_len);              // (3) 0.05859
/*14 */         r->sector_count = 0;                                        // (14) 0.0293
/*16 */         scsi_req_data(&r->req, r->iov.iov_len);                     // (5) 0.05078
/*18 */         return;                                                     // (21) 0.01758
/*20 */     }                                                               // (23) 0.007812
/*22 */     DPRINTF("Read sector_count=%d\n", r->sector_count);             // (6) 0.04492
/*24 */     if (r->sector_count == 0) {                                     // (17) 0.02734
/*26 */         scsi_command_complete(r, GOOD, NO_SENSE);                   // (7) 0.04492
/*28 */         return;                                                     // (22) 0.01758
/*30 */     }                                                               // (24) 0.007812
/*34 */     /* No data transfer may already be in progress */               // (18) 0.02539
/*36 */     assert(r->req.aiocb == NULL);                                   // (15) 0.0293
/*40 */     n = r->sector_count;                                            // (19) 0.02148
/*42 */     if (n > SCSI_DMA_BUF_SIZE / 512)                                // (10) 0.03906
/*44 */         n = SCSI_DMA_BUF_SIZE / 512;                                // (8) 0.04297
/*48 */     r->iov.iov_len = n * 512;                                       // (16) 0.0293
/*50 */     qemu_iovec_init_external(&r->qiov, &r->iov, 1);                 // (4) 0.05273
/*52 */     r->req.aiocb = bdrv_aio_readv(s->bs, r->sector, &r->qiov, n,    // (1) 0.07227
/*54 */                               scsi_read_complete, r);               // (0) 0.07422
/*56 */     if (r->req.aiocb == NULL) {                                     // (13) 0.03125
/*58 */         scsi_read_complete(r, -EIO);                                // (11) 0.03906
/*60 */     }                                                               // (25) 0.007812
/*62 */ }                                                                   // (27) 0.001953
