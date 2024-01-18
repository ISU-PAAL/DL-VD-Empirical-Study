// commit message qemu@40dfc16f5f (target=1, prob=0.23453955, correct=False): virtio-blk: switch exit callback to VirtioDeviceClass
/*0  */ static int virtio_blk_device_exit(DeviceState *dev)                        // (6) 0.07489
/*2  */ {                                                                          // (13) 0.004405
/*4  */     VirtIODevice *vdev = VIRTIO_DEVICE(dev);                               // (2) 0.09251
/*6  */     VirtIOBlock *s = VIRTIO_BLK(dev);                                      // (5) 0.0793
/*8  */ #ifdef CONFIG_VIRTIO_BLK_DATA_PLANE                                        // (7) 0.07048
/*10 */     remove_migration_state_change_notifier(&s->migration_state_notifier);  // (0) 0.1101
/*12 */     virtio_blk_data_plane_destroy(s->dataplane);                           // (3) 0.08811
/*14 */     s->dataplane = NULL;                                                   // (10) 0.04405
/*16 */ #endif                                                                     // (12) 0.008811
/*18 */     qemu_del_vm_change_state_handler(s->change);                           // (1) 0.09251
/*20 */     unregister_savevm(dev, "virtio-blk", s);                               // (4) 0.08811
/*22 */     blockdev_mark_auto_del(s->bs);                                         // (8) 0.07048
/*24 */     virtio_cleanup(vdev);                                                  // (9) 0.05286
/*26 */     return 0;                                                              // (11) 0.02643
/*28 */ }                                                                          // (14) 0.004405
