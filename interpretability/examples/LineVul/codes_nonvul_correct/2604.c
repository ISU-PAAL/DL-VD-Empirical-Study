// commit message qemu@61007b316c (target=0, prob=0.16129969, correct=True): block: move I/O request processing to block/io.c
/*0  */ void bdrv_round_to_clusters(BlockDriverState *bs,                               // (10) 0.04489
/*2  */                             int64_t sector_num, int nb_sectors,                 // (1) 0.1047
/*4  */                             int64_t *cluster_sector_num,                        // (2) 0.09726
/*6  */                             int *cluster_nb_sectors)                            // (3) 0.09227
/*8  */ {                                                                               // (14) 0.002494
/*10 */     BlockDriverInfo bdi;                                                        // (11) 0.02244
/*14 */     if (bdrv_get_info(bs, &bdi) < 0 || bdi.cluster_size == 0) {                 // (5) 0.08229
/*16 */         *cluster_sector_num = sector_num;                                       // (9) 0.04738
/*18 */         *cluster_nb_sectors = nb_sectors;                                       // (8) 0.05486
/*20 */     } else {                                                                    // (12) 0.01496
/*22 */         int64_t c = bdi.cluster_size / BDRV_SECTOR_SIZE;                        // (6) 0.07731
/*24 */         *cluster_sector_num = QEMU_ALIGN_DOWN(sector_num, c);                   // (7) 0.07481
/*26 */         *cluster_nb_sectors = QEMU_ALIGN_UP(sector_num - *cluster_sector_num +  // (4) 0.09227
/*28 */                                             nb_sectors, c);                     // (0) 0.1272
/*30 */     }                                                                           // (13) 0.009975
/*32 */ }                                                                               // (15) 0.002494
