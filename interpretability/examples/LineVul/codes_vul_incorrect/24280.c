// commit message qemu@f2b58c4375 (target=1, prob=0.3138255, correct=False): 9pfs: fix crash when fsdev is missing
/*0   */ int v9fs_device_realize_common(V9fsState *s, Error **errp)                      // (5) 0.04688
/*2   */ {                                                                               // (28) 0.001953
/*4   */     int i, len;                                                                 // (24) 0.01562
/*6   */     struct stat stat;                                                           // (25) 0.01367
/*8   */     FsDriverEntry *fse;                                                         // (17) 0.02148
/*10  */     V9fsPath path;                                                              // (21) 0.01758
/*12  */     int rc = 1;                                                                 // (23) 0.01562
/*16  */     /* initialize pdu allocator */                                              // (18) 0.01953
/*18  */     QLIST_INIT(&s->free_list);                                                  // (14) 0.0293
/*20  */     QLIST_INIT(&s->active_list);                                                // (13) 0.0293
/*22  */     for (i = 0; i < (MAX_REQ - 1); i++) {                                       // (9) 0.04297
/*24  */         QLIST_INSERT_HEAD(&s->free_list, &s->pdus[i], next);                    // (1) 0.06055
/*26  */         s->pdus[i].s = s;                                                       // (11) 0.03516
/*28  */         s->pdus[i].idx = i;                                                     // (10) 0.03711
/*30  */     }                                                                           // (26) 0.007812
/*34  */     v9fs_path_init(&path);                                                      // (15) 0.02539
/*38  */     fse = get_fsdev_fsentry(s->fsconf.fsdev_id);                                // (6) 0.04687
/*42  */     if (!fse) {                                                                 // (22) 0.01758
/*44  */         /* We don't have a fsdev identified by fsdev_id */                      // (8) 0.04297
/*46  */         error_setg(errp, "9pfs device couldn't find fsdev with the "            // (2) 0.05469
/*48  */                    "id = %s",                                                   // (7) 0.04687
/*50  */                    s->fsconf.fsdev_id ? s->fsconf.fsdev_id : "NULL");           // (0) 0.08008
/*52  */         goto out;                                                               // (19) 0.01953
/*54  */     }                                                                           // (27) 0.007812
/*58  */     if (!s->fsconf.tag) {                                                       // (16) 0.02539
/*60  */         /* we haven't specified a mount_tag */                                  // (12) 0.0332
/*62  */         error_setg(errp, "fsdev with id %s needs mount_tag arguments",          // (3) 0.05469
/*64  */                    s->fsconf.fsdev_id);                                         // (4) 0.05469
/*66  */         goto out;                                                               // (20) 0.01953
/*68  */     }                                                                           // 0.0
/*72  */     s->ctx.export_flags = fse->export_flags;                                    // 0.0
/*74  */     s->ctx.fs_root = g_strdup(fse->path);                                       // 0.0
/*76  */     s->ctx.exops.get_st_gen = NULL;                                             // 0.0
/*78  */     len = strlen(s->fsconf.tag);                                                // 0.0
/*80  */     if (len > MAX_TAG_LEN - 1) {                                                // 0.0
/*82  */         error_setg(errp, "mount tag '%s' (%d bytes) is longer than "            // 0.0
/*84  */                    "maximum (%d bytes)", s->fsconf.tag, len, MAX_TAG_LEN - 1);  // 0.0
/*86  */         goto out;                                                               // 0.0
/*88  */     }                                                                           // 0.0
/*92  */     s->tag = g_strdup(s->fsconf.tag);                                           // 0.0
/*94  */     s->ctx.uid = -1;                                                            // 0.0
/*98  */     s->ops = fse->ops;                                                          // 0.0
/*102 */     s->fid_list = NULL;                                                         // 0.0
/*104 */     qemu_co_rwlock_init(&s->rename_lock);                                       // 0.0
/*108 */     if (s->ops->init(&s->ctx) < 0) {                                            // 0.0
/*110 */         error_setg(errp, "9pfs Failed to initialize fs-driver with id:%s"       // 0.0
/*112 */                    " and export path:%s", s->fsconf.fsdev_id, s->ctx.fs_root);  // 0.0
/*114 */         goto out;                                                               // 0.0
/*116 */     }                                                                           // 0.0
/*120 */     /*                                                                          // 0.0
/*122 */      * Check details of export path, We need to use fs driver                   // 0.0
/*124 */      * call back to do that. Since we are in the init path, we don't            // 0.0
/*126 */      * use co-routines here.                                                    // 0.0
/*128 */      */                                                                         // 0.0
/*130 */     if (s->ops->name_to_path(&s->ctx, NULL, "/", &path) < 0) {                  // 0.0
/*132 */         error_setg(errp,                                                        // 0.0
/*134 */                    "error in converting name to path %s", strerror(errno));     // 0.0
/*136 */         goto out;                                                               // 0.0
/*138 */     }                                                                           // 0.0
/*140 */     if (s->ops->lstat(&s->ctx, &path, &stat)) {                                 // 0.0
/*142 */         error_setg(errp, "share path %s does not exist", fse->path);            // 0.0
/*144 */         goto out;                                                               // 0.0
/*146 */     } else if (!S_ISDIR(stat.st_mode)) {                                        // 0.0
/*148 */         error_setg(errp, "share path %s is not a directory", fse->path);        // 0.0
/*150 */         goto out;                                                               // 0.0
/*152 */     }                                                                           // 0.0
/*154 */     v9fs_path_free(&path);                                                      // 0.0
/*158 */     rc = 0;                                                                     // 0.0
/*160 */ out:                                                                            // 0.0
/*162 */     if (rc) {                                                                   // 0.0
/*164 */         if (s->ops->cleanup && s->ctx.private) {                                // 0.0
/*166 */             s->ops->cleanup(&s->ctx);                                           // 0.0
/*168 */         }                                                                       // 0.0
/*170 */         g_free(s->tag);                                                         // 0.0
/*172 */         g_free(s->ctx.fs_root);                                                 // 0.0
/*174 */         v9fs_path_free(&path);                                                  // 0.0
/*176 */     }                                                                           // 0.0
/*178 */     return rc;                                                                  // 0.0
/*180 */ }                                                                               // 0.0
