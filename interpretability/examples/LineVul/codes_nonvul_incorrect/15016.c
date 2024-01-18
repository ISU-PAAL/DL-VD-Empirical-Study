// commit message qemu@2906cddfec (target=0, prob=0.5243669, correct=False): virtio-blk: fix "disabled data plane" mode
/*0  */ static void virtio_blk_handle_output(VirtIODevice *vdev, VirtQueue *vq)    // (0) 0.0875
/*2  */ {                                                                          // (19) 0.003125
/*4  */     VirtIOBlock *s = VIRTIO_BLK(vdev);                                     // (6) 0.05938
/*6  */     VirtIOBlockReq *req;                                                   // (12) 0.03438
/*8  */     MultiReqBuffer mrb = {};                                               // (11) 0.0375
/*12 */     /* Some guests kick before setting VIRTIO_CONFIG_S_DRIVER_OK so start  // (2) 0.075
/*14 */      * dataplane here instead of waiting for .set_status().                // (7) 0.05313
/*16 */      */                                                                    // (15) 0.01563
/*18 */     if (s->dataplane) {                                                    // (13) 0.03438
/*20 */         virtio_blk_data_plane_start(s->dataplane);                         // (3) 0.075
/*22 */         return;                                                            // (14) 0.02813
/*24 */     }                                                                      // (16) 0.0125
/*28 */     blk_io_plug(s->blk);                                                   // (9) 0.04688
/*32 */     while ((req = virtio_blk_get_request(s))) {                            // (5) 0.0625
/*34 */         virtio_blk_handle_request(req, &mrb);                              // (4) 0.07188
/*36 */     }                                                                      // (17) 0.0125
/*40 */     if (mrb.num_reqs) {                                                    // (10) 0.04375
/*42 */         virtio_blk_submit_multireq(s->blk, &mrb);                          // (1) 0.0875
/*44 */     }                                                                      // (18) 0.0125
/*48 */     blk_io_unplug(s->blk);                                                 // (8) 0.05
/*50 */ }                                                                          // (20) 0.003125
