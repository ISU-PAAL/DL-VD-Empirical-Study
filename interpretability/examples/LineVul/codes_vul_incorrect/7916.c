// commit message qemu@e976c6a1e4 (target=1, prob=0.4599755, correct=False): Change order of metadata update to prevent loosing guest data because of unexpected exit (Gleb Natapov)
/*0   */ static void qcow_aio_write_cb(void *opaque, int ret)                          // (6) 0.03906
/*2   */ {                                                                             // (29) 0.001953
/*4   */     QCowAIOCB *acb = opaque;                                                  // (15) 0.02734
/*6   */     BlockDriverState *bs = acb->common.bs;                                    // (10) 0.03125
/*8   */     BDRVQcowState *s = bs->opaque;                                            // (9) 0.03516
/*10  */     int index_in_cluster;                                                     // (18) 0.02148
/*12  */     uint64_t cluster_offset;                                                  // (19) 0.02148
/*14  */     const uint8_t *src_buf;                                                   // (17) 0.02539
/*16  */     int n_end;                                                                // (25) 0.01562
/*20  */     acb->hd_aiocb = NULL;                                                     // (16) 0.02734
/*24  */     if (ret < 0) {                                                            // (22) 0.01953
/*26  */     fail:                                                                     // (26) 0.009766
/*28  */         acb->common.cb(acb->common.opaque, ret);                              // (3) 0.04687
/*30  */         qemu_aio_release(acb);                                                // (7) 0.03711
/*32  */         return;                                                               // (23) 0.01758
/*34  */     }                                                                         // (27) 0.007812
/*38  */     acb->nb_sectors -= acb->n;                                                // (11) 0.03125
/*40  */     acb->sector_num += acb->n;                                                // (14) 0.0293
/*42  */     acb->buf += acb->n * 512;                                                 // (13) 0.0293
/*46  */     if (acb->nb_sectors == 0) {                                               // (12) 0.03125
/*48  */         /* request completed */                                               // (21) 0.02148
/*50  */         acb->common.cb(acb->common.opaque, 0);                                // (4) 0.04687
/*52  */         qemu_aio_release(acb);                                                // (8) 0.03711
/*54  */         return;                                                               // (24) 0.01758
/*56  */     }                                                                         // (28) 0.007812
/*60  */     index_in_cluster = acb->sector_num & (s->cluster_sectors - 1);            // (2) 0.05469
/*62  */     n_end = index_in_cluster + acb->nb_sectors;                               // (5) 0.04297
/*64  */     if (s->crypt_method &&                                                    // (20) 0.02148
/*66  */         n_end > QCOW_MAX_CRYPT_CLUSTERS * s->cluster_sectors)                 // (0) 0.0625
/*68  */         n_end = QCOW_MAX_CRYPT_CLUSTERS * s->cluster_sectors;                 // (1) 0.0625
/*72  */     cluster_offset = alloc_cluster_offset(bs, acb->sector_num << 9,           // 0.0
/*74  */                                           index_in_cluster,                   // 0.0
/*76  */                                           n_end, &acb->n);                    // 0.0
/*78  */     if (!cluster_offset || (cluster_offset & 511) != 0) {                     // 0.0
/*80  */         ret = -EIO;                                                           // 0.0
/*82  */         goto fail;                                                            // 0.0
/*84  */     }                                                                         // 0.0
/*86  */     if (s->crypt_method) {                                                    // 0.0
/*88  */         if (!acb->cluster_data) {                                             // 0.0
/*90  */             acb->cluster_data = qemu_mallocz(QCOW_MAX_CRYPT_CLUSTERS *        // 0.0
/*92  */                                              s->cluster_size);                // 0.0
/*94  */             if (!acb->cluster_data) {                                         // 0.0
/*96  */                 ret = -ENOMEM;                                                // 0.0
/*98  */                 goto fail;                                                    // 0.0
/*100 */             }                                                                 // 0.0
/*102 */         }                                                                     // 0.0
/*104 */         encrypt_sectors(s, acb->sector_num, acb->cluster_data, acb->buf,      // 0.0
/*106 */                         acb->n, 1, &s->aes_encrypt_key);                      // 0.0
/*108 */         src_buf = acb->cluster_data;                                          // 0.0
/*110 */     } else {                                                                  // 0.0
/*112 */         src_buf = acb->buf;                                                   // 0.0
/*114 */     }                                                                         // 0.0
/*116 */     acb->hd_aiocb = bdrv_aio_write(s->hd,                                     // 0.0
/*118 */                                    (cluster_offset >> 9) + index_in_cluster,  // 0.0
/*120 */                                    src_buf, acb->n,                           // 0.0
/*122 */                                    qcow_aio_write_cb, acb);                   // 0.0
/*124 */     if (acb->hd_aiocb == NULL)                                                // 0.0
/*126 */         goto fail;                                                            // 0.0
/*128 */ }                                                                             // 0.0
