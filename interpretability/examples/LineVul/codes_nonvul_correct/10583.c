// commit message qemu@2119882c7e (target=0, prob=0.18695337, correct=True): block: introduce dirty_bitmap_mutex
/*0  */ static BdrvDirtyBitmap *block_dirty_bitmap_lookup(const char *node,        // (5) 0.04688
/*2  */                                                   const char *name,        // (2) 0.1055
/*4  */                                                   BlockDriverState **pbs,  // (0) 0.1094
/*6  */                                                   AioContext **paio,       // (1) 0.1074
/*8  */                                                   Error **errp)            // (3) 0.1055
/*10 */ {                                                                          // (23) 0.001953
/*12 */     BlockDriverState *bs;                                                  // (16) 0.01758
/*14 */     BdrvDirtyBitmap *bitmap;                                               // (11) 0.02734
/*16 */     AioContext *aio_context;                                               // (12) 0.02344
/*20 */     if (!node) {                                                           // (17) 0.01562
/*22 */         error_setg(errp, "Node cannot be NULL");                           // (7) 0.04102
/*24 */         return NULL;                                                       // (13) 0.01953
/*26 */     }                                                                      // (20) 0.007812
/*28 */     if (!name) {                                                           // (18) 0.01562
/*30 */         error_setg(errp, "Bitmap name cannot be NULL");                    // (6) 0.04492
/*32 */         return NULL;                                                       // (14) 0.01953
/*34 */     }                                                                      // (21) 0.007812
/*36 */     bs = bdrv_lookup_bs(node, node, NULL);                                 // (8) 0.04102
/*38 */     if (!bs) {                                                             // (19) 0.01562
/*40 */         error_setg(errp, "Node '%s' not found", node);                     // (4) 0.05078
/*42 */         return NULL;                                                       // (15) 0.01953
/*44 */     }                                                                      // (22) 0.007812
/*48 */     aio_context = bdrv_get_aio_context(bs);                                // (9) 0.04102
/*50 */     aio_context_acquire(aio_context);                                      // (10) 0.03125
/*54 */     bitmap = bdrv_find_dirty_bitmap(bs, name);                             // 0.0
/*56 */     if (!bitmap) {                                                         // 0.0
/*58 */         error_setg(errp, "Dirty bitmap '%s' not found", name);             // 0.0
/*60 */         goto fail;                                                         // 0.0
/*62 */     }                                                                      // 0.0
/*66 */     if (pbs) {                                                             // 0.0
/*68 */         *pbs = bs;                                                         // 0.0
/*70 */     }                                                                      // 0.0
/*72 */     if (paio) {                                                            // 0.0
/*74 */         *paio = aio_context;                                               // 0.0
/*76 */     } else {                                                               // 0.0
/*78 */         aio_context_release(aio_context);                                  // 0.0
/*80 */     }                                                                      // 0.0
/*84 */     return bitmap;                                                         // 0.0
/*88 */  fail:                                                                     // 0.0
/*90 */     aio_context_release(aio_context);                                      // 0.0
/*92 */     return NULL;                                                           // 0.0
/*94 */ }                                                                          // 0.0
