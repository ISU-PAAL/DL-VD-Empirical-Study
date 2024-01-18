// commit message qemu@d9e0dfa246 (target=0, prob=0.23685026, correct=True): block: Split bdrv_merge_limits() from bdrv_refresh_limits()
/*0   */ void bdrv_refresh_limits(BlockDriverState *bs, Error **errp)                   // (10) 0.04102
/*2   */ {                                                                              // (25) 0.001953
/*4   */     BlockDriver *drv = bs->drv;                                                // (13) 0.0293
/*6   */     Error *local_err = NULL;                                                   // (18) 0.02148
/*10  */     memset(&bs->bl, 0, sizeof(bs->bl));                                        // (12) 0.03516
/*14  */     if (!drv) {                                                                // (20) 0.01758
/*16  */         return;                                                                // (21) 0.01758
/*18  */     }                                                                          // (24) 0.007812
/*22  */     /* Default alignment based on whether driver has byte interface */         // (14) 0.02734
/*24  */     bs->request_alignment = drv->bdrv_co_preadv ? 1 : 512;                     // (5) 0.05273
/*28  */     /* Take some limits from the children as a default */                      // (15) 0.02734
/*30  */     if (bs->file) {                                                            // (19) 0.01953
/*32  */         bdrv_refresh_limits(bs->file->bs, &local_err);                         // (6) 0.05273
/*34  */         if (local_err) {                                                       // (16) 0.02734
/*36  */             error_propagate(errp, local_err);                                  // (9) 0.04492
/*38  */             return;                                                            // (17) 0.02539
/*40  */         }                                                                      // (22) 0.01562
/*42  */         bs->bl.opt_transfer = bs->file->bs->bl.opt_transfer;                   // (2) 0.05664
/*44  */         bs->bl.max_transfer = bs->file->bs->bl.max_transfer;                   // (3) 0.05664
/*46  */         bs->bl.min_mem_alignment = bs->file->bs->bl.min_mem_alignment;         // (0) 0.06836
/*48  */         bs->bl.opt_mem_alignment = bs->file->bs->bl.opt_mem_alignment;         // (1) 0.06836
/*50  */         bs->bl.max_iov = bs->file->bs->bl.max_iov;                             // (4) 0.05664
/*52  */     } else {                                                                   // (23) 0.01172
/*54  */         bs->bl.min_mem_alignment = 512;                                        // (11) 0.04102
/*56  */         bs->bl.opt_mem_alignment = getpagesize();                              // (8) 0.04492
/*60  */         /* Safe default since most protocols use readv()/writev()/etc */       // (7) 0.04688
/*62  */         bs->bl.max_iov = IOV_MAX;                                              // 0.0
/*64  */     }                                                                          // 0.0
/*68  */     if (bs->backing) {                                                         // 0.0
/*70  */         bdrv_refresh_limits(bs->backing->bs, &local_err);                      // 0.0
/*72  */         if (local_err) {                                                       // 0.0
/*74  */             error_propagate(errp, local_err);                                  // 0.0
/*76  */             return;                                                            // 0.0
/*78  */         }                                                                      // 0.0
/*80  */         bs->bl.opt_transfer = MAX(bs->bl.opt_transfer,                         // 0.0
/*82  */                                   bs->backing->bs->bl.opt_transfer);           // 0.0
/*84  */         bs->bl.max_transfer = MIN_NON_ZERO(bs->bl.max_transfer,                // 0.0
/*86  */                                            bs->backing->bs->bl.max_transfer);  // 0.0
/*88  */         bs->bl.opt_mem_alignment =                                             // 0.0
/*90  */             MAX(bs->bl.opt_mem_alignment,                                      // 0.0
/*92  */                 bs->backing->bs->bl.opt_mem_alignment);                        // 0.0
/*94  */         bs->bl.min_mem_alignment =                                             // 0.0
/*96  */             MAX(bs->bl.min_mem_alignment,                                      // 0.0
/*98  */                 bs->backing->bs->bl.min_mem_alignment);                        // 0.0
/*100 */         bs->bl.max_iov =                                                       // 0.0
/*102 */             MIN(bs->bl.max_iov,                                                // 0.0
/*104 */                 bs->backing->bs->bl.max_iov);                                  // 0.0
/*106 */     }                                                                          // 0.0
/*110 */     /* Then let the driver override it */                                      // 0.0
/*112 */     if (drv->bdrv_refresh_limits) {                                            // 0.0
/*114 */         drv->bdrv_refresh_limits(bs, errp);                                    // 0.0
/*116 */     }                                                                          // 0.0
/*118 */ }                                                                              // 0.0
