// commit message qemu@d3c8c67469 (target=1, prob=0.3458352, correct=False): block: Skip implicit nodes in query-block/blockstats
/*0  */ static BlockStats *bdrv_query_bds_stats(const BlockDriverState *bs,         // (5) 0.05459
/*2  */                                  bool query_backing)                        // (0) 0.09429
/*4  */ {                                                                           // (22) 0.002481
/*6  */     BlockStats *s = NULL;                                                   // (13) 0.02481
/*10 */     s = g_malloc0(sizeof(*s));                                              // (10) 0.0397
/*12 */     s->stats = g_malloc0(sizeof(*s->stats));                                // (6) 0.04963
/*16 */     if (!bs) {                                                              // (16) 0.01985
/*18 */         return s;                                                           // (14) 0.02481
/*20 */     }                                                                       // (18) 0.009926
/*24 */     if (bdrv_get_node_name(bs)[0]) {                                        // (7) 0.04963
/*26 */         s->has_node_name = true;                                            // (8) 0.04218
/*28 */         s->node_name = g_strdup(bdrv_get_node_name(bs));                    // (3) 0.07692
/*30 */     }                                                                       // (19) 0.009926
/*34 */     s->stats->wr_highest_offset = stat64_get(&bs->wr_highest_offset);       // (4) 0.06452
/*38 */     if (bs->file) {                                                         // (15) 0.02481
/*40 */         s->has_parent = true;                                               // (12) 0.03722
/*42 */         s->parent = bdrv_query_bds_stats(bs->file->bs, query_backing);      // (2) 0.08189
/*44 */     }                                                                       // (20) 0.009926
/*48 */     if (query_backing && bs->backing) {                                     // (9) 0.04218
/*50 */         s->has_backing = true;                                              // (11) 0.0397
/*52 */         s->backing = bdrv_query_bds_stats(bs->backing->bs, query_backing);  // (1) 0.08685
/*54 */     }                                                                       // (21) 0.009926
/*58 */     return s;                                                               // (17) 0.01489
/*60 */ }                                                                           // (23) 0.002481
