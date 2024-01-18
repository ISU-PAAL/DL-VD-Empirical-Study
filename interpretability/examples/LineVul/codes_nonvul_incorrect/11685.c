// commit message qemu@9db1c0f7a9 (target=0, prob=0.5462666, correct=False): hd-geometry: Move disk geometry guessing back from block.c
/*0   */ VirtIODevice *virtio_blk_init(DeviceState *dev, VirtIOBlkConf *blk)          // (3) 0.05664
/*2   */ {                                                                            // (26) 0.001953
/*4   */     VirtIOBlock *s;                                                          // (20) 0.01758
/*6   */     int cylinders, heads, secs;                                              // (16) 0.02148
/*8   */     static int virtio_blk_id;                                                // (14) 0.02539
/*10  */     DriveInfo *dinfo;                                                        // (21) 0.01758
/*14  */     if (!blk->conf.bs) {                                                     // (15) 0.02539
/*16  */         error_report("drive property not set");                              // (12) 0.03125
/*18  */         return NULL;                                                         // (18) 0.01953
/*20  */     }                                                                        // (25) 0.007812
/*22  */     if (!bdrv_is_inserted(blk->conf.bs)) {                                   // (7) 0.04297
/*24  */         error_report("Device needs media, but drive is empty");              // (10) 0.03906
/*26  */         return NULL;                                                         // (19) 0.01953
/*28  */     }                                                                        // (24) 0.007812
/*32  */     if (!blk->serial) {                                                      // (17) 0.02148
/*34  */         /* try to fall back to value set with legacy -drive serial=... */    // (6) 0.04492
/*36  */         dinfo = drive_get_by_blockdev(blk->conf.bs);                         // (4) 0.05078
/*38  */         if (*dinfo->serial) {                                                // (13) 0.0293
/*40  */             blk->serial = strdup(dinfo->serial);                             // (5) 0.04883
/*42  */         }                                                                    // (22) 0.01562
/*44  */     }                                                                        // (23) 0.007813
/*48  */     s = (VirtIOBlock *)virtio_common_init("virtio-blk", VIRTIO_ID_BLOCK,     // (2) 0.06445
/*50  */                                           sizeof(struct virtio_blk_config),  // (0) 0.1016
/*52  */                                           sizeof(VirtIOBlock));              // (1) 0.09375
/*56  */     s->vdev.get_config = virtio_blk_update_config;                           // (8) 0.04297
/*58  */     s->vdev.get_features = virtio_blk_get_features;                          // (9) 0.04297
/*60  */     s->vdev.reset = virtio_blk_reset;                                        // (11) 0.03516
/*62  */     s->bs = blk->conf.bs;                                                    // 0.0
/*64  */     s->conf = &blk->conf;                                                    // 0.0
/*66  */     s->blk = blk;                                                            // 0.0
/*68  */     s->rq = NULL;                                                            // 0.0
/*70  */     s->sector_mask = (s->conf->logical_block_size / BDRV_SECTOR_SIZE) - 1;   // 0.0
/*72  */     bdrv_guess_geometry(s->bs, &cylinders, &heads, &secs);                   // 0.0
/*76  */     s->vq = virtio_add_queue(&s->vdev, 128, virtio_blk_handle_output);       // 0.0
/*80  */     qemu_add_vm_change_state_handler(virtio_blk_dma_restart_cb, s);          // 0.0
/*82  */     s->qdev = dev;                                                           // 0.0
/*84  */     register_savevm(dev, "virtio-blk", virtio_blk_id++, 2,                   // 0.0
/*86  */                     virtio_blk_save, virtio_blk_load, s);                    // 0.0
/*88  */     bdrv_set_dev_ops(s->bs, &virtio_block_ops, s);                           // 0.0
/*90  */     bdrv_set_buffer_alignment(s->bs, s->conf->logical_block_size);           // 0.0
/*94  */     bdrv_iostatus_enable(s->bs);                                             // 0.0
/*96  */     add_boot_device_path(s->conf->bootindex, dev, "/disk@0,0");              // 0.0
/*100 */     return &s->vdev;                                                         // 0.0
/*102 */ }                                                                            // 0.0
