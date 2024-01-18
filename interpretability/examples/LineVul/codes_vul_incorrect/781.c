// commit message qemu@e50d7607f1 (target=1, prob=0.27134365, correct=False): sheepdog: fix dynamic grow for running qcow2 format
/*0  */ static coroutine_fn int sd_co_writev(BlockDriverState *bs, int64_t sector_num,  // (4) 0.06733
/*2  */                         int nb_sectors, QEMUIOVector *qiov)                     // (0) 0.09726
/*4  */ {                                                                               // (21) 0.002494
/*6  */     SheepdogAIOCB *acb;                                                         // (13) 0.02993
/*8  */     int ret;                                                                    // (18) 0.01496
/*12 */     if (bs->growable && sector_num + nb_sectors > bs->total_sectors) {          // (2) 0.07232
/*14 */         ret = sd_truncate(bs, (sector_num + nb_sectors) * BDRV_SECTOR_SIZE);    // (1) 0.09726
/*16 */         if (ret < 0) {                                                          // (10) 0.03491
/*18 */             return ret;                                                         // (11) 0.03491
/*20 */         }                                                                       // (17) 0.01995
/*22 */         bs->total_sectors = sector_num + nb_sectors;                            // (5) 0.06234
/*24 */     }                                                                           // (19) 0.009975
/*28 */     acb = sd_aio_setup(bs, qiov, sector_num, nb_sectors);                       // (3) 0.06983
/*30 */     acb->aio_done_func = sd_write_done;                                         // (7) 0.04738
/*32 */     acb->aiocb_type = AIOCB_WRITE_UDATA;                                        // (6) 0.05486
/*36 */     ret = sd_co_rw_vector(acb);                                                 // (9) 0.0399
/*38 */     if (ret <= 0) {                                                             // (14) 0.02494
/*40 */         qemu_aio_release(acb);                                                  // (8) 0.04738
/*42 */         return ret;                                                             // (15) 0.02494
/*44 */     }                                                                           // (20) 0.009975
/*48 */     qemu_coroutine_yield();                                                     // (12) 0.03242
/*52 */     return acb->ret;                                                            // (16) 0.02244
/*54 */ }                                                                               // (22) 0.002494
