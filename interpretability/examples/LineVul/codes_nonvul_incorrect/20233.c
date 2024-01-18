// commit message qemu@2d2507ef23 (target=0, prob=0.7972951, correct=False): vhost_net: cleanup start/stop condition
/*0  */ static void vhost_net_stop_one(struct vhost_net *net,                        // (8) 0.04657
/*2  */                                VirtIODevice *dev)                            // (2) 0.09314
/*4  */ {                                                                            // (19) 0.002451
/*6  */     struct vhost_vring_file file = { .fd = -1 };                             // (7) 0.04902
/*10 */     if (!net->dev.started) {                                                 // (13) 0.02941
/*12 */         return;                                                              // (14) 0.02206
/*14 */     }                                                                        // (16) 0.009804
/*18 */     if (net->nc->info->type == NET_CLIENT_OPTIONS_KIND_TAP) {                // (5) 0.07108
/*20 */         for (file.index = 0; file.index < net->dev.nvqs; ++file.index) {     // (3) 0.07843
/*22 */             const VhostOps *vhost_ops = net->dev.vhost_ops;                  // (4) 0.07353
/*24 */             int r = vhost_ops->vhost_call(&net->dev, VHOST_NET_SET_BACKEND,  // (1) 0.09559
/*26 */                                           &file);                            // (0) 0.1078
/*28 */             assert(r >= 0);                                                  // (10) 0.04167
/*30 */         }                                                                    // (15) 0.01961
/*32 */     }                                                                        // (17) 0.009804
/*34 */     if (net->nc->info->poll) {                                               // (12) 0.03431
/*36 */         net->nc->info->poll(net->nc, true);                                  // (6) 0.05147
/*38 */     }                                                                        // (18) 0.009804
/*40 */     vhost_dev_stop(&net->dev, dev);                                          // (11) 0.03922
/*42 */     vhost_dev_disable_notifiers(&net->dev, dev);                             // (9) 0.04657
/*44 */ }                                                                            // (20) 0.002451
