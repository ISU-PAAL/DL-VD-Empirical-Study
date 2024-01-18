// commit message qemu@88be7b4be4 (target=1, prob=0.3947287, correct=False): block: Fix bdrv_next() memory leak
/*0  */ bool bdrv_is_first_non_filter(BlockDriverState *candidate)       // (2) 0.09091
/*2  */ {                                                                // (14) 0.004545
/*4  */     BlockDriverState *bs;                                        // (10) 0.04091
/*6  */     BdrvNextIterator *it = NULL;                                 // (7) 0.05909
/*10 */     /* walk down the bs forest recursively */                    // (5) 0.06364
/*12 */     while ((it = bdrv_next(it, &bs)) != NULL) {                  // (1) 0.1
/*14 */         bool perm;                                               // (9) 0.04545
/*18 */         /* try to recurse in this top level bs */                // (3) 0.08636
/*20 */         perm = bdrv_recurse_is_first_non_filter(bs, candidate);  // (0) 0.1273
/*24 */         /* candidate is the first non filter */                  // (4) 0.06818
/*26 */         if (perm) {                                              // (8) 0.05455
/*28 */             return true;                                         // (6) 0.06364
/*30 */         }                                                        // (11) 0.03636
/*32 */     }                                                            // (13) 0.01818
/*36 */     return false;                                                // (12) 0.02727
/*38 */ }                                                                // (15) 0.004545
