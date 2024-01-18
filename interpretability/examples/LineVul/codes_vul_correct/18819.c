// commit message qemu@1e7398a140 (target=1, prob=0.64197195, correct=True): vhost: enable vhost without without MSI-X
/*0   */ struct vhost_net *vhost_net_init(VhostNetOptions *options)                       // (8) 0.03906
/*2   */ {                                                                                // (29) 0.001954
/*4   */     int r;                                                                       // (24) 0.01172
/*6   */     bool backend_kernel = options->backend_type == VHOST_BACKEND_TYPE_KERNEL;    // (4) 0.05469
/*8   */     struct vhost_net *net = g_malloc(sizeof *net);                               // (7) 0.04102
/*12  */     if (!options->net_backend) {                                                 // (17) 0.02539
/*14  */         fprintf(stderr, "vhost-net requires net backend to be setup\n");         // (3) 0.05469
/*16  */         goto fail;                                                               // (21) 0.01953
/*18  */     }                                                                            // (27) 0.007812
/*22  */     if (backend_kernel) {                                                        // (19) 0.02148
/*24  */         r = vhost_net_get_fd(options->net_backend);                              // (5) 0.04883
/*26  */         if (r < 0) {                                                             // (16) 0.02734
/*28  */             goto fail;                                                           // (14) 0.02734
/*30  */         }                                                                        // (23) 0.01562
/*32  */         net->dev.backend_features = qemu_has_vnet_hdr(options->net_backend)      // (0) 0.06836
/*34  */             ? 0 : (1ULL << VHOST_NET_F_VIRTIO_NET_HDR);                          // (1) 0.06836
/*36  */         net->backend = r;                                                        // (15) 0.02734
/*38  */     } else {                                                                     // (25) 0.01172
/*40  */         net->dev.backend_features = 0;                                           // (10) 0.03516
/*42  */         net->backend = -1;                                                       // (12) 0.0293
/*44  */     }                                                                            // (26) 0.007812
/*46  */     net->nc = options->net_backend;                                              // (13) 0.02734
/*50  */     net->dev.nvqs = 2;                                                           // (18) 0.02344
/*52  */     net->dev.vqs = net->vqs;                                                     // (11) 0.0293
/*54  */     net->dev.vq_index = net->nc->queue_index;                                    // (9) 0.03906
/*58  */     r = vhost_dev_init(&net->dev, options->opaque,                               // (6) 0.04102
/*60  */                        options->backend_type, options->force);                   // (2) 0.06445
/*62  */     if (r < 0) {                                                                 // (22) 0.01953
/*64  */         goto fail;                                                               // (20) 0.01953
/*66  */     }                                                                            // (28) 0.007812
/*68  */     if (backend_kernel) {                                                        // 0.0
/*70  */         if (!qemu_has_vnet_hdr_len(options->net_backend,                         // 0.0
/*72  */                                sizeof(struct virtio_net_hdr_mrg_rxbuf))) {       // 0.0
/*74  */             net->dev.features &= ~(1ULL << VIRTIO_NET_F_MRG_RXBUF);              // 0.0
/*76  */         }                                                                        // 0.0
/*78  */         if (~net->dev.features & net->dev.backend_features) {                    // 0.0
/*80  */             fprintf(stderr, "vhost lacks feature mask %" PRIu64                  // 0.0
/*82  */                    " for backend\n",                                             // 0.0
/*84  */                    (uint64_t)(~net->dev.features & net->dev.backend_features));  // 0.0
/*86  */             vhost_dev_cleanup(&net->dev);                                        // 0.0
/*88  */             goto fail;                                                           // 0.0
/*90  */         }                                                                        // 0.0
/*92  */     }                                                                            // 0.0
/*94  */     /* Set sane init value. Override when guest acks. */                         // 0.0
/*96  */     vhost_net_ack_features(net, 0);                                              // 0.0
/*98  */     return net;                                                                  // 0.0
/*100 */ fail:                                                                            // 0.0
/*102 */     g_free(net);                                                                 // 0.0
/*104 */     return NULL;                                                                 // 0.0
/*106 */ }                                                                                // 0.0
