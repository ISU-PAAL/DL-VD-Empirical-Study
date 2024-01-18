// commit message qemu@f06ee3d4aa (target=1, prob=0.34513074, correct=False): qed: Make qiov match request size until backing file EOF
/*0  */ static void qed_aio_read_data(void *opaque, int ret,                       // (10) 0.03906
/*2  */                               uint64_t offset, size_t len)                 // (1) 0.07812
/*4  */ {                                                                          // (23) 0.001953
/*6  */     QEDAIOCB *acb = opaque;                                                // (14) 0.02734
/*8  */     BDRVQEDState *s = acb_to_s(acb);                                       // (8) 0.04297
/*10 */     BlockDriverState *bs = acb->common.bs;                                 // (13) 0.03125
/*14 */     /* Adjust offset into cluster */                                       // (18) 0.01758
/*16 */     offset += qed_offset_into_cluster(s, acb->cur_pos);                    // (7) 0.04688
/*20 */     trace_qed_aio_read_data(s, acb, ret, offset, len);                     // (5) 0.05078
/*24 */     if (ret < 0) {                                                         // (16) 0.01953
/*26 */         goto err;                                                          // (17) 0.01953
/*28 */     }                                                                      // (21) 0.007812
/*32 */     qemu_iovec_concat(&acb->cur_qiov, acb->qiov, acb->qiov_offset, len);   // (3) 0.07422
/*36 */     /* Handle zero cluster and backing file reads */                       // (15) 0.02344
/*38 */     if (ret == QED_CLUSTER_ZERO) {                                         // (12) 0.03516
/*40 */         qemu_iovec_memset(&acb->cur_qiov, 0, 0, acb->cur_qiov.size);       // (2) 0.07812
/*42 */         qed_aio_next_io(acb, 0);                                           // (9) 0.04297
/*44 */         return;                                                            // (19) 0.01758
/*46 */     } else if (ret != QED_CLUSTER_FOUND) {                                 // (11) 0.03906
/*48 */         qed_read_backing_file(s, acb->cur_pos, &acb->cur_qiov,             // (4) 0.06836
/*50 */                               qed_aio_next_io, acb);                       // (0) 0.08203
/*52 */         return;                                                            // (20) 0.01758
/*54 */     }                                                                      // (22) 0.007812
/*58 */     BLKDBG_EVENT(bs->file, BLKDBG_READ_AIO);                               // (6) 0.04883
/*60 */     bdrv_aio_readv(bs->file, offset / BDRV_SECTOR_SIZE,                    // 0.0
/*62 */                    &acb->cur_qiov, acb->cur_qiov.size / BDRV_SECTOR_SIZE,  // 0.0
/*64 */                    qed_aio_next_io, acb);                                  // 0.0
/*66 */     return;                                                                // 0.0
/*70 */ err:                                                                       // 0.0
/*72 */     qed_aio_complete(acb, ret);                                            // 0.0
/*74 */ }                                                                          // 0.0
