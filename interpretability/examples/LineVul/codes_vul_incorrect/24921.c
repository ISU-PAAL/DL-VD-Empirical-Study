// commit message qemu@27915efb97 (target=1, prob=0.44175938, correct=False): virtio-9p-device: Avoid freeing uninitialized memory
/*0   */ static int virtio_9p_device_init(VirtIODevice *vdev)                           // (8) 0.04297
/*2   */ {                                                                              // (26) 0.001955
/*4   */     V9fsState *s = VIRTIO_9P(vdev);                                            // (11) 0.03906
/*6   */     int i, len;                                                                // (22) 0.01563
/*8   */     struct stat stat;                                                          // (23) 0.01367
/*10  */     FsDriverEntry *fse;                                                        // (17) 0.02149
/*12  */     V9fsPath path;                                                             // (20) 0.01759
/*16  */     virtio_init(VIRTIO_DEVICE(s), "virtio-9p", VIRTIO_ID_9P,                   // (2) 0.06445
/*18  */                 sizeof(struct virtio_9p_config) + MAX_TAG_LEN);                // (1) 0.0664
/*22  */     /* initialize pdu allocator */                                             // (18) 0.01953
/*24  */     QLIST_INIT(&s->free_list);                                                 // (13) 0.0293
/*26  */     QLIST_INIT(&s->active_list);                                               // (14) 0.0293
/*28  */     for (i = 0; i < (MAX_REQ - 1); i++) {                                      // (9) 0.04297
/*30  */         QLIST_INSERT_HEAD(&s->free_list, &s->pdus[i], next);                   // (3) 0.06054
/*32  */     }                                                                          // (24) 0.007812
/*36  */     s->vq = virtio_add_queue(vdev, MAX_REQ, handle_9p_output);                 // (4) 0.05859
/*40  */     fse = get_fsdev_fsentry(s->fsconf.fsdev_id);                               // (6) 0.04687
/*44  */     if (!fse) {                                                                // (21) 0.01758
/*46  */         /* We don't have a fsdev identified by fsdev_id */                     // (10) 0.04297
/*48  */         fprintf(stderr, "Virtio-9p device couldn't find fsdev with the "       // (5) 0.05859
/*50  */                 "id = %s\n",                                                   // (7) 0.04492
/*52  */                 s->fsconf.fsdev_id ? s->fsconf.fsdev_id : "NULL");             // (0) 0.07421
/*54  */         goto out;                                                              // (19) 0.01953
/*56  */     }                                                                          // (25) 0.007812
/*60  */     if (!s->fsconf.tag) {                                                      // (16) 0.02539
/*62  */         /* we haven't specified a mount_tag */                                 // (12) 0.0332
/*64  */         fprintf(stderr, "fsdev with id %s needs mount_tag arguments\n",        // 0.0
/*66  */                 s->fsconf.fsdev_id);                                           // 0.0
/*68  */         goto out;                                                              // 0.0
/*70  */     }                                                                          // 0.0
/*74  */     s->ctx.export_flags = fse->export_flags;                                   // 0.0
/*76  */     s->ctx.fs_root = g_strdup(fse->path);                                      // 0.0
/*78  */     s->ctx.exops.get_st_gen = NULL;                                            // 0.0
/*80  */     len = strlen(s->fsconf.tag);                                               // 0.0
/*82  */     if (len > MAX_TAG_LEN - 1) {                                               // 0.0
/*84  */         fprintf(stderr, "mount tag '%s' (%d bytes) is longer than "            // 0.0
/*86  */                 "maximum (%d bytes)", s->fsconf.tag, len, MAX_TAG_LEN - 1);    // 0.0
/*88  */         goto out;                                                              // 0.0
/*90  */     }                                                                          // 0.0
/*94  */     s->tag = g_strdup(s->fsconf.tag);                                          // 0.0
/*96  */     s->ctx.uid = -1;                                                           // 0.0
/*100 */     s->ops = fse->ops;                                                         // 0.0
/*102 */     s->config_size = sizeof(struct virtio_9p_config) + len;                    // 0.0
/*104 */     s->fid_list = NULL;                                                        // 0.0
/*106 */     qemu_co_rwlock_init(&s->rename_lock);                                      // 0.0
/*110 */     if (s->ops->init(&s->ctx) < 0) {                                           // 0.0
/*112 */         fprintf(stderr, "Virtio-9p Failed to initialize fs-driver with id:%s"  // 0.0
/*114 */                 " and export path:%s\n", s->fsconf.fsdev_id, s->ctx.fs_root);  // 0.0
/*116 */         goto out;                                                              // 0.0
/*118 */     }                                                                          // 0.0
/*120 */     if (v9fs_init_worker_threads() < 0) {                                      // 0.0
/*122 */         fprintf(stderr, "worker thread initialization failed\n");              // 0.0
/*124 */         goto out;                                                              // 0.0
/*126 */     }                                                                          // 0.0
/*130 */     /*                                                                         // 0.0
/*132 */      * Check details of export path, We need to use fs driver                  // 0.0
/*134 */      * call back to do that. Since we are in the init path, we don't           // 0.0
/*136 */      * use co-routines here.                                                   // 0.0
/*138 */      */                                                                        // 0.0
/*140 */     v9fs_path_init(&path);                                                     // 0.0
/*142 */     if (s->ops->name_to_path(&s->ctx, NULL, "/", &path) < 0) {                 // 0.0
/*144 */         fprintf(stderr,                                                        // (15) 0.02734
/*146 */                 "error in converting name to path %s", strerror(errno));       // 0.0
/*148 */         goto out;                                                              // 0.0
/*150 */     }                                                                          // 0.0
/*152 */     if (s->ops->lstat(&s->ctx, &path, &stat)) {                                // 0.0
/*154 */         fprintf(stderr, "share path %s does not exist\n", fse->path);          // 0.0
/*156 */         goto out;                                                              // 0.0
/*158 */     } else if (!S_ISDIR(stat.st_mode)) {                                       // 0.0
/*160 */         fprintf(stderr, "share path %s is not a directory\n", fse->path);      // 0.0
/*162 */         goto out;                                                              // 0.0
/*164 */     }                                                                          // 0.0
/*166 */     v9fs_path_free(&path);                                                     // 0.0
/*170 */     return 0;                                                                  // 0.0
/*172 */ out:                                                                           // 0.0
/*174 */     g_free(s->ctx.fs_root);                                                    // 0.0
/*176 */     g_free(s->tag);                                                            // 0.0
/*178 */     virtio_cleanup(vdev);                                                      // 0.0
/*180 */     v9fs_path_free(&path);                                                     // 0.0
/*184 */     return -1;                                                                 // 0.0
/*188 */ }                                                                              // 0.0
