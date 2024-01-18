// commit message qemu@f8a2e5e3ca (target=0, prob=0.17238094, correct=True): block: convert qcow2, qcow2, and vmdk to .bdrv_co_is_allocated()
/*0  */ static int qcow2_is_allocated(BlockDriverState *bs, int64_t sector_num,          // (2) 0.1111
/*2  */                               int nb_sectors, int *pnum)                         // (0) 0.1822
/*4  */ {                                                                                // (12) 0.004444
/*6  */     uint64_t cluster_offset;                                                     // (7) 0.04889
/*8  */     int ret;                                                                     // (10) 0.02667
/*12 */     *pnum = nb_sectors;                                                          // (4) 0.05778
/*14 */     /* FIXME We can get errors here, but the bdrv_is_allocated interface can't   // (3) 0.1111
/*16 */      * pass them on today */                                                     // (8) 0.04444
/*18 */     ret = qcow2_get_cluster_offset(bs, sector_num << 9, pnum, &cluster_offset);  // (1) 0.1467
/*20 */     if (ret < 0) {                                                               // (9) 0.04444
/*22 */         *pnum = 0;                                                               // (5) 0.05778
/*24 */     }                                                                            // (11) 0.01778
/*28 */     return (cluster_offset != 0);                                                // (6) 0.05333
/*30 */ }                                                                                // (13) 0.004444
