// commit message qemu@61007b316c (target=0, prob=0.03886342, correct=True): block: move I/O request processing to block/io.c
/*0  */ static int bdrv_get_cluster_size(BlockDriverState *bs)  // (1) 0.1429
/*2  */ {                                                       // (9) 0.007519
/*4  */     BlockDriverInfo bdi;                                // (5) 0.06767
/*6  */     int ret;                                            // (6) 0.04511
/*10 */     ret = bdrv_get_info(bs, &bdi);                      // (2) 0.1429
/*12 */     if (ret < 0 || bdi.cluster_size == 0) {             // (0) 0.1504
/*14 */         return bs->request_alignment;                   // (3) 0.1203
/*16 */     } else {                                            // (7) 0.04511
/*18 */         return bdi.cluster_size;                        // (4) 0.1203
/*20 */     }                                                   // (8) 0.03008
/*22 */ }                                                       // (10) 0.007519
