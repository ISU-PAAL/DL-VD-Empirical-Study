// commit message qemu@2ce68e4cf5 (target=1, prob=0.99904996, correct=True): vhost: add vhost_has_free_slot() interface
/*0  */ int vhost_dev_init(struct vhost_dev *hdev, void *opaque,                         // (6) 0.04297
/*1  */                    VhostBackendType backend_type)                                // (4) 0.05273
/*2  */ {                                                                                // (31) 0.001953
/*3  */     uint64_t features;                                                           // (23) 0.01758
/*4  */     int i, r;                                                                    // (25) 0.01562
/*5  */     if (vhost_set_backend_type(hdev, backend_type) < 0) {                        // (5) 0.05078
/*6  */         close((uintptr_t)opaque);                                                // (9) 0.0332
/*7  */         return -1;                                                               // (17) 0.02148
/*8  */     }                                                                            // (28) 0.007812
/*9  */     if (hdev->vhost_ops->vhost_backend_init(hdev, opaque) < 0) {                 // (3) 0.05859
/*10 */         close((uintptr_t)opaque);                                                // (10) 0.0332
/*11 */         return -errno;                                                           // (16) 0.02344
/*12 */     }                                                                            // (26) 0.007813
/*13 */     r = hdev->vhost_ops->vhost_call(hdev, VHOST_SET_OWNER, NULL);                // (2) 0.0625
/*14 */     if (r < 0) {                                                                 // (22) 0.01953
/*15 */         goto fail;                                                               // (19) 0.01953
/*16 */     }                                                                            // (29) 0.007812
/*17 */     r = hdev->vhost_ops->vhost_call(hdev, VHOST_GET_FEATURES, &features);        // (1) 0.06445
/*18 */     if (r < 0) {                                                                 // (21) 0.01953
/*19 */         goto fail;                                                               // (20) 0.01953
/*20 */     }                                                                            // (30) 0.007812
/*21 */     for (i = 0; i < hdev->nvqs; ++i) {                                           // (7) 0.04102
/*22 */         r = vhost_virtqueue_init(hdev, hdev->vqs + i, hdev->vq_index + i);       // (0) 0.07422
/*23 */         if (r < 0) {                                                             // (15) 0.02734
/*24 */             goto fail_vq;                                                        // (11) 0.0332
/*25 */         }                                                                        // (24) 0.01562
/*26 */     }                                                                            // (27) 0.007813
/*27 */     hdev->features = features;                                                   // (18) 0.01953
/*28 */     hdev->memory_listener = (MemoryListener) {                                   // (12) 0.03125
/*29 */         .begin = vhost_begin,                                                    // (13) 0.0293
/*30 */         .commit = vhost_commit,                                                  // (14) 0.0293
/*31 */         .region_add = vhost_region_add,                                          // (8) 0.03711
/*32 */         .region_del = vhost_region_del,                                          // 0.0
/*33 */         .region_nop = vhost_region_nop,                                          // 0.0
/*34 */         .log_start = vhost_log_start,                                            // 0.0
/*35 */         .log_stop = vhost_log_stop,                                              // 0.0
/*36 */         .log_sync = vhost_log_sync,                                              // 0.0
/*37 */         .log_global_start = vhost_log_global_start,                              // 0.0
/*38 */         .log_global_stop = vhost_log_global_stop,                                // 0.0
/*39 */         .eventfd_add = vhost_eventfd_add,                                        // 0.0
/*40 */         .eventfd_del = vhost_eventfd_del,                                        // 0.0
/*41 */         .priority = 10                                                           // 0.0
/*42 */     };                                                                           // 0.0
/*43 */     hdev->migration_blocker = NULL;                                              // 0.0
/*44 */     if (!(hdev->features & (0x1ULL << VHOST_F_LOG_ALL))) {                       // 0.0
/*45 */         error_setg(&hdev->migration_blocker,                                     // 0.0
/*46 */                    "Migration disabled: vhost lacks VHOST_F_LOG_ALL feature.");  // 0.0
/*47 */         migrate_add_blocker(hdev->migration_blocker);                            // 0.0
/*48 */     }                                                                            // 0.0
/*49 */     hdev->mem = g_malloc0(offsetof(struct vhost_memory, regions));               // 0.0
/*50 */     hdev->n_mem_sections = 0;                                                    // 0.0
/*51 */     hdev->mem_sections = NULL;                                                   // 0.0
/*52 */     hdev->log = NULL;                                                            // 0.0
/*53 */     hdev->log_size = 0;                                                          // 0.0
/*54 */     hdev->log_enabled = false;                                                   // 0.0
/*55 */     hdev->started = false;                                                       // 0.0
/*56 */     hdev->memory_changed = false;                                                // 0.0
/*57 */     memory_listener_register(&hdev->memory_listener, &address_space_memory);     // 0.0
/*58 */     return 0;                                                                    // 0.0
/*59 */ fail_vq:                                                                         // 0.0
/*60 */     while (--i >= 0) {                                                           // 0.0
/*61 */         vhost_virtqueue_cleanup(hdev->vqs + i);                                  // 0.0
/*62 */     }                                                                            // 0.0
/*63 */ fail:                                                                            // 0.0
/*64 */     r = -errno;                                                                  // 0.0
/*65 */     hdev->vhost_ops->vhost_backend_cleanup(hdev);                                // 0.0
/*66 */     QLIST_REMOVE(hdev, entry);                                                   // 0.0
/*67 */     return r;                                                                    // 0.0
/*68 */ }                                                                                // 0.0
