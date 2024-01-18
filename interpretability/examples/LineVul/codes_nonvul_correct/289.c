// commit message qemu@6a84cb1f28 (target=0, prob=0.43713313, correct=True): scsi virtio-blk usb-msd: Clean up device init error messages
/*0   */ VirtIODevice *virtio_blk_init(DeviceState *dev, BlockConf *conf,             // (4) 0.04883
/*2   */                               char **serial)                                 // (3) 0.06445
/*4   */ {                                                                            // (25) 0.001953
/*6   */     VirtIOBlock *s;                                                          // (18) 0.01758
/*8   */     int cylinders, heads, secs;                                              // (14) 0.02148
/*10  */     static int virtio_blk_id;                                                // (13) 0.02539
/*12  */     DriveInfo *dinfo;                                                        // (19) 0.01758
/*16  */     if (!conf->bs) {                                                         // (15) 0.01953
/*18  */         error_report("virtio-blk-pci: drive property not set");              // (5) 0.04883
/*20  */         return NULL;                                                         // (16) 0.01953
/*22  */     }                                                                        // (23) 0.007812
/*24  */     if (!bdrv_is_inserted(conf->bs)) {                                       // (11) 0.03711
/*26  */         error_report("Device needs media, but drive is empty");              // (10) 0.03906
/*28  */         return NULL;                                                         // (17) 0.01953
/*30  */     }                                                                        // (24) 0.007812
/*34  */     if (!*serial) {                                                          // (20) 0.01758
/*36  */         /* try to fall back to value set with legacy -drive serial=... */    // (6) 0.04492
/*38  */         dinfo = drive_get_by_blockdev(conf->bs);                             // (7) 0.04492
/*40  */         if (*dinfo->serial) {                                                // (12) 0.0293
/*42  */             *serial = strdup(dinfo->serial);                                 // (8) 0.04492
/*44  */         }                                                                    // (21) 0.01562
/*46  */     }                                                                        // (22) 0.007813
/*50  */     s = (VirtIOBlock *)virtio_common_init("virtio-blk", VIRTIO_ID_BLOCK,     // (2) 0.06445
/*52  */                                           sizeof(struct virtio_blk_config),  // (0) 0.1016
/*54  */                                           sizeof(VirtIOBlock));              // (1) 0.09375
/*58  */     s->vdev.get_config = virtio_blk_update_config;                           // (9) 0.04297
/*60  */     s->vdev.get_features = virtio_blk_get_features;                          // 0.0
/*62  */     s->vdev.reset = virtio_blk_reset;                                        // 0.0
/*64  */     s->bs = conf->bs;                                                        // 0.0
/*66  */     s->conf = conf;                                                          // 0.0
/*68  */     s->serial = *serial;                                                     // 0.0
/*70  */     s->rq = NULL;                                                            // 0.0
/*72  */     s->sector_mask = (s->conf->logical_block_size / BDRV_SECTOR_SIZE) - 1;   // 0.0
/*74  */     bdrv_guess_geometry(s->bs, &cylinders, &heads, &secs);                   // 0.0
/*78  */     s->vq = virtio_add_queue(&s->vdev, 128, virtio_blk_handle_output);       // 0.0
/*82  */     qemu_add_vm_change_state_handler(virtio_blk_dma_restart_cb, s);          // 0.0
/*84  */     s->qdev = dev;                                                           // 0.0
/*86  */     register_savevm(dev, "virtio-blk", virtio_blk_id++, 2,                   // 0.0
/*88  */                     virtio_blk_save, virtio_blk_load, s);                    // 0.0
/*90  */     bdrv_set_dev_ops(s->bs, &virtio_block_ops, s);                           // 0.0
/*92  */     bdrv_set_buffer_alignment(s->bs, conf->logical_block_size);              // 0.0
/*96  */     bdrv_iostatus_enable(s->bs);                                             // 0.0
/*98  */     add_boot_device_path(conf->bootindex, dev, "/disk@0,0");                 // 0.0
/*102 */     return &s->vdev;                                                         // 0.0
/*104 */ }                                                                            // 0.0
