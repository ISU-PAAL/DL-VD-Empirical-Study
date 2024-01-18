// commit message qemu@113fe792fd (target=1, prob=0.35733932, correct=False): block/nfs: fix mutex assertion in nfs_file_close()
/*0  */ static int nfs_file_open(BlockDriverState *bs, QDict *options, int flags,  // (3) 0.08276
/*2  */                          Error **errp) {                                   // (2) 0.1034
/*4  */     NFSClient *client = bs->opaque;                                        // (7) 0.05172
/*6  */     int64_t ret;                                                           // (11) 0.03103
/*10 */     client->aio_context = bdrv_get_aio_context(bs);                        // (4) 0.07931
/*14 */     ret = nfs_client_open(client, options,                                 // (6) 0.05517
/*16 */                           (flags & BDRV_O_RDWR) ? O_RDWR : O_RDONLY,       // (0) 0.169
/*18 */                           bs->open_flags, errp);                           // (1) 0.1207
/*20 */     if (ret < 0) {                                                         // (9) 0.03448
/*22 */         return ret;                                                        // (10) 0.03448
/*24 */     }                                                                      // (14) 0.01379
/*26 */     qemu_mutex_init(&client->mutex);                                       // (5) 0.05862
/*28 */     bs->total_sectors = ret;                                               // (8) 0.04483
/*30 */     ret = 0;                                                               // (12) 0.02414
/*32 */     return ret;                                                            // (13) 0.02069
/*34 */ }                                                                          // (15) 0.003448
