// commit message qemu@0e86c13fe2 (target=1, prob=0.74007434, correct=True): virtio-serial: switch exit callback to VirtioDeviceClass
/*0  */ static int virtio_serial_device_exit(DeviceState *dev)  // (7) 0.06275
/*2  */ {                                                       // (15) 0.003922
/*4  */     VirtIOSerial *vser = VIRTIO_SERIAL(dev);            // (2) 0.07843
/*6  */     VirtIODevice *vdev = VIRTIO_DEVICE(dev);            // (0) 0.08235
/*10 */     unregister_savevm(dev, "virtio-console", vser);     // (1) 0.07843
/*14 */     g_free(vser->ivqs);                                 // (9) 0.05098
/*16 */     g_free(vser->ovqs);                                 // (10) 0.05098
/*18 */     g_free(vser->ports_map);                            // (8) 0.0549
/*20 */     if (vser->post_load) {                              // (11) 0.05098
/*22 */         g_free(vser->post_load->connected);             // (3) 0.07843
/*24 */         timer_del(vser->post_load->timer);              // (4) 0.07843
/*26 */         timer_free(vser->post_load->timer);             // (5) 0.07843
/*28 */         g_free(vser->post_load);                        // (6) 0.07059
/*30 */     }                                                   // (14) 0.01569
/*32 */     virtio_cleanup(vdev);                               // (12) 0.04706
/*34 */     return 0;                                           // (13) 0.02353
/*36 */ }                                                       // (16) 0.003922
