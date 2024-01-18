// commit message qemu@92cb05574b (target=0, prob=0.11302915, correct=True): pc-bios/s390-ccw: support all virtio block size
/*0 */ bool virtio_ipl_disk_is_valid(void)                                               // (1) 0.2295
/*2 */ {                                                                                 // (2) 0.01639
/*4 */     return blk_cfg.blk_size && (virtio_disk_is_scsi() || virtio_disk_is_eckd());  // (0) 0.6066
/*6 */ }                                                                                 // (3) 0.01639
