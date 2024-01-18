// commit message qemu@e1123a3b40 (target=0, prob=0.09673766, correct=True): block/iscsi: allow caching of the allocation map
/*0  */ static void iscsi_allocationmap_set(IscsiLun *iscsilun, int64_t sector_num,  // (2) 0.1167
/*2  */                                     int nb_sectors)                          // (1) 0.1634
/*4  */ {                                                                            // (10) 0.003891
/*6  */     int64_t cluster_num, nb_clusters;                                        // (6) 0.06615
/*8  */     if (iscsilun->allocationmap == NULL) {                                   // (7) 0.06226
/*10 */         return;                                                              // (8) 0.03502
/*12 */     }                                                                        // (9) 0.01556
/*14 */     cluster_num = sector_num / iscsilun->cluster_sectors;                    // (5) 0.0856
/*16 */     nb_clusters = DIV_ROUND_UP(sector_num + nb_sectors,                      // (3) 0.1051
/*18 */                                iscsilun->cluster_sectors) - cluster_num;     // (0) 0.179
/*20 */     bitmap_set(iscsilun->allocationmap, cluster_num, nb_clusters);           // (4) 0.1012
/*22 */ }                                                                            // (11) 0.003891
