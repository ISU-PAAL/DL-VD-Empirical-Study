// commit message qemu@4be746345f (target=0, prob=0.28803915, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static int milkymist_memcard_init(SysBusDevice *dev)                         // (6) 0.0605
/*2  */ {                                                                            // (15) 0.003559
/*4  */     MilkymistMemcardState *s = MILKYMIST_MEMCARD(dev);                       // (3) 0.08185
/*6  */     DriveInfo *dinfo;                                                        // (12) 0.03203
/*8  */     BlockDriverState *bs;                                                    // (11) 0.03203
/*12 */     dinfo = drive_get_next(IF_SD);                                           // (7) 0.05694
/*14 */     bs = dinfo ? blk_bs(blk_by_legacy_dinfo(dinfo)) : NULL;                  // (1) 0.1103
/*16 */     s->card = sd_init(bs, false);                                            // (8) 0.05338
/*18 */     if (s->card == NULL) {                                                   // (9) 0.0427
/*20 */         return -1;                                                           // (10) 0.03915
/*22 */     }                                                                        // (14) 0.01423
/*26 */     s->enabled = bs && bdrv_is_inserted(bs);                                 // (4) 0.07473
/*30 */     memory_region_init_io(&s->regs_region, OBJECT(s), &memcard_mmio_ops, s,  // (0) 0.121
/*32 */             "milkymist-memcard", R_MAX * 4);                                 // (2) 0.08897
/*34 */     sysbus_init_mmio(dev, &s->regs_region);                                  // (5) 0.07473
/*38 */     return 0;                                                                // (13) 0.02135
/*40 */ }                                                                            // (16) 0.003559
