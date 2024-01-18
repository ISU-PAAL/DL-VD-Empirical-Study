// commit message qemu@4be746345f (target=0, prob=0.16646475, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static void virtio_blk_update_config(VirtIODevice *vdev, uint8_t *config)    // (2) 0.05664
/*2  */ {                                                                            // (23) 0.001953
/*4  */     VirtIOBlock *s = VIRTIO_BLK(vdev);                                       // (10) 0.03711
/*6  */     BlockConf *conf = &s->conf.conf;                                         // (18) 0.0293
/*8  */     struct virtio_blk_config blkcfg;                                         // (19) 0.0293
/*10 */     uint64_t capacity;                                                       // (21) 0.01758
/*12 */     int blk_size = conf->logical_block_size;                                 // (14) 0.03516
/*16 */     bdrv_get_geometry(s->bs, &capacity);                                     // (11) 0.03711
/*18 */     memset(&blkcfg, 0, sizeof(blkcfg));                                      // (15) 0.03516
/*20 */     virtio_stq_p(vdev, &blkcfg.capacity, capacity);                          // (8) 0.04492
/*22 */     virtio_stl_p(vdev, &blkcfg.seg_max, 128 - 2);                            // (4) 0.05469
/*24 */     virtio_stw_p(vdev, &blkcfg.cylinders, conf->cyls);                       // (5) 0.05273
/*26 */     virtio_stl_p(vdev, &blkcfg.blk_size, blk_size);                          // (3) 0.05664
/*28 */     virtio_stw_p(vdev, &blkcfg.min_io_size, conf->min_io_size / blk_size);   // (0) 0.07422
/*30 */     virtio_stw_p(vdev, &blkcfg.opt_io_size, conf->opt_io_size / blk_size);   // (1) 0.07422
/*32 */     blkcfg.heads = conf->heads;                                              // (20) 0.02539
/*34 */     /*                                                                       // (22) 0.007812
/*36 */      * We must ensure that the block device capacity is a multiple of        // (16) 0.0332
/*38 */      * the logical block size. If that is not the case, let's use            // (9) 0.03906
/*40 */      * sector_mask to adopt the geometry to have a correct picture.          // (13) 0.03516
/*42 */      * For those devices where the capacity is ok for the given geometry     // (17) 0.0332
/*44 */      * we don't touch the sector value of the geometry, since some devices   // (12) 0.03711
/*46 */      * (like s390 dasd) need a specific value. Here the capacity is already  // (7) 0.04492
/*48 */      * cyls*heads*secs*blk_size and the sector value is not block size       // (6) 0.04883
/*50 */      * divided by 512 - instead it is the amount of blk_size blocks          // 0.0
/*52 */      * per track (cylinder).                                                 // 0.0
/*54 */      */                                                                      // 0.0
/*56 */     if (bdrv_getlength(s->bs) /  conf->heads / conf->secs % blk_size) {      // 0.0
/*58 */         blkcfg.sectors = conf->secs & ~s->sector_mask;                       // 0.0
/*60 */     } else {                                                                 // 0.0
/*62 */         blkcfg.sectors = conf->secs;                                         // 0.0
/*64 */     }                                                                        // 0.0
/*66 */     blkcfg.size_max = 0;                                                     // 0.0
/*68 */     blkcfg.physical_block_exp = get_physical_block_exp(conf);                // 0.0
/*70 */     blkcfg.alignment_offset = 0;                                             // 0.0
/*72 */     blkcfg.wce = bdrv_enable_write_cache(s->bs);                             // 0.0
/*74 */     memcpy(config, &blkcfg, sizeof(struct virtio_blk_config));               // 0.0
/*76 */ }                                                                            // 0.0
