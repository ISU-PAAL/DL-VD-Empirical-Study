// commit message qemu@1e7398a140 (target=1, prob=0.38195744, correct=False): vhost: enable vhost without without MSI-X
/*0   */ int vhost_dev_init(struct vhost_dev *hdev, void *opaque,                         // (6) 0.04297
/*2   */                    VhostBackendType backend_type, bool force)                    // (2) 0.05859
/*4   */ {                                                                                // (30) 0.001953
/*6   */     uint64_t features;                                                           // (22) 0.01758
/*8   */     int i, r;                                                                    // (23) 0.01562
/*12  */     if (vhost_set_backend_type(hdev, backend_type) < 0) {                        // (5) 0.05078
/*14  */         close((uintptr_t)opaque);                                                // (9) 0.0332
/*16  */         return -1;                                                               // (16) 0.02148
/*18  */     }                                                                            // (26) 0.007812
/*22  */     if (hdev->vhost_ops->vhost_backend_init(hdev, opaque) < 0) {                 // (3) 0.05859
/*24  */         close((uintptr_t)opaque);                                                // (8) 0.0332
/*26  */         return -errno;                                                           // (15) 0.02344
/*28  */     }                                                                            // (25) 0.007813
/*32  */     r = hdev->vhost_ops->vhost_call(hdev, VHOST_SET_OWNER, NULL);                // (1) 0.0625
/*34  */     if (r < 0) {                                                                 // (19) 0.01953
/*36  */         goto fail;                                                               // (18) 0.01953
/*38  */     }                                                                            // (27) 0.007812
/*42  */     r = hdev->vhost_ops->vhost_call(hdev, VHOST_GET_FEATURES, &features);        // (0) 0.06445
/*44  */     if (r < 0) {                                                                 // (20) 0.01953
/*46  */         goto fail;                                                               // (21) 0.01953
/*48  */     }                                                                            // (28) 0.007812
/*52  */     for (i = 0; i < hdev->nvqs; ++i) {                                           // (7) 0.04102
/*54  */         r = vhost_virtqueue_init(hdev, hdev->vqs + i, i);                        // (4) 0.05859
/*56  */         if (r < 0) {                                                             // (14) 0.02734
/*58  */             goto fail_vq;                                                        // (10) 0.0332
/*60  */         }                                                                        // (24) 0.01562
/*62  */     }                                                                            // (29) 0.007812
/*64  */     hdev->features = features;                                                   // (17) 0.01953
/*68  */     hdev->memory_listener = (MemoryListener) {                                   // (11) 0.03125
/*70  */         .begin = vhost_begin,                                                    // (12) 0.0293
/*72  */         .commit = vhost_commit,                                                  // (13) 0.0293
/*74  */         .region_add = vhost_region_add,                                          // 0.0
/*76  */         .region_del = vhost_region_del,                                          // 0.0
/*78  */         .region_nop = vhost_region_nop,                                          // 0.0
/*80  */         .log_start = vhost_log_start,                                            // 0.0
/*82  */         .log_stop = vhost_log_stop,                                              // 0.0
/*84  */         .log_sync = vhost_log_sync,                                              // 0.0
/*86  */         .log_global_start = vhost_log_global_start,                              // 0.0
/*88  */         .log_global_stop = vhost_log_global_stop,                                // 0.0
/*90  */         .eventfd_add = vhost_eventfd_add,                                        // 0.0
/*92  */         .eventfd_del = vhost_eventfd_del,                                        // 0.0
/*94  */         .priority = 10                                                           // 0.0
/*96  */     };                                                                           // 0.0
/*98  */     hdev->migration_blocker = NULL;                                              // 0.0
/*100 */     if (!(hdev->features & (0x1ULL << VHOST_F_LOG_ALL))) {                       // 0.0
/*102 */         error_setg(&hdev->migration_blocker,                                     // 0.0
/*104 */                    "Migration disabled: vhost lacks VHOST_F_LOG_ALL feature.");  // 0.0
/*106 */         migrate_add_blocker(hdev->migration_blocker);                            // 0.0
/*108 */     }                                                                            // 0.0
/*110 */     hdev->mem = g_malloc0(offsetof(struct vhost_memory, regions));               // 0.0
/*112 */     hdev->n_mem_sections = 0;                                                    // 0.0
/*114 */     hdev->mem_sections = NULL;                                                   // 0.0
/*116 */     hdev->log = NULL;                                                            // 0.0
/*118 */     hdev->log_size = 0;                                                          // 0.0
/*120 */     hdev->log_enabled = false;                                                   // 0.0
/*122 */     hdev->started = false;                                                       // 0.0
/*124 */     hdev->memory_changed = false;                                                // 0.0
/*126 */     memory_listener_register(&hdev->memory_listener, &address_space_memory);     // 0.0
/*128 */     hdev->force = force;                                                         // 0.0
/*130 */     return 0;                                                                    // 0.0
/*132 */ fail_vq:                                                                         // 0.0
/*134 */     while (--i >= 0) {                                                           // 0.0
/*136 */         vhost_virtqueue_cleanup(hdev->vqs + i);                                  // 0.0
/*138 */     }                                                                            // 0.0
/*140 */ fail:                                                                            // 0.0
/*142 */     r = -errno;                                                                  // 0.0
/*144 */     hdev->vhost_ops->vhost_backend_cleanup(hdev);                                // 0.0
/*146 */     return r;                                                                    // 0.0
/*148 */ }                                                                                // 0.0
