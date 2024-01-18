// commit message qemu@7c24384b3b (target=1, prob=0.48025054, correct=False): block/nfs: fix url parameter checking
/*0   */ static int64_t nfs_client_open(NFSClient *client, const char *filename,  // (3) 0.04492
/*2   */                                int flags, Error **errp)                  // (0) 0.07422
/*4   */ {                                                                        // (32) 0.001953
/*6   */     int ret = -EINVAL, i;                                                // (14) 0.02539
/*8   */     struct stat st;                                                      // (27) 0.01367
/*10  */     URI *uri;                                                            // (26) 0.01367
/*12  */     QueryParams *qp = NULL;                                              // (17) 0.02344
/*14  */     char *file = NULL, *strp = NULL;                                     // (11) 0.0293
/*18  */     uri = uri_parse(filename);                                           // (15) 0.02539
/*20  */     if (!uri) {                                                          // (25) 0.01563
/*22  */         error_setg(errp, "Invalid URL specified");                       // (4) 0.03906
/*24  */         goto fail;                                                       // (20) 0.01953
/*26  */     }                                                                    // (28) 0.007812
/*28  */     if (!uri->server) {                                                  // (19) 0.01953
/*30  */         error_setg(errp, "Invalid URL specified");                       // (5) 0.03906
/*32  */         goto fail;                                                       // (21) 0.01953
/*34  */     }                                                                    // (29) 0.007812
/*36  */     strp = strrchr(uri->path, '/');                                      // (9) 0.0332
/*38  */     if (strp == NULL) {                                                  // (18) 0.02148
/*40  */         error_setg(errp, "Invalid URL specified");                       // (6) 0.03906
/*42  */         goto fail;                                                       // (22) 0.01953
/*44  */     }                                                                    // (30) 0.007812
/*46  */     file = g_strdup(strp);                                               // (13) 0.02734
/*48  */     *strp = 0;                                                           // (24) 0.01758
/*52  */     client->context = nfs_init_context();                                // (12) 0.02734
/*54  */     if (client->context == NULL) {                                       // (16) 0.02344
/*56  */         error_setg(errp, "Failed to init NFS context");                  // (2) 0.04688
/*58  */         goto fail;                                                       // (23) 0.01953
/*60  */     }                                                                    // (31) 0.007812
/*64  */     qp = query_params_parse(uri->query);                                 // (10) 0.03125
/*66  */     for (i = 0; i < qp->n; i++) {                                        // (7) 0.03711
/*68  */         if (!qp->p[i].value) {                                           // (8) 0.03711
/*70  */             error_setg(errp, "Value for NFS parameter expected: %s",     // (1) 0.05859
/*72  */                        qp->p[i].name);                                   // 0.0
/*74  */             goto fail;                                                   // 0.0
/*76  */         }                                                                // 0.0
/*78  */         if (!strncmp(qp->p[i].name, "uid", 3)) {                         // 0.0
/*80  */             nfs_set_uid(client->context, atoi(qp->p[i].value));          // 0.0
/*82  */         } else if (!strncmp(qp->p[i].name, "gid", 3)) {                  // 0.0
/*84  */             nfs_set_gid(client->context, atoi(qp->p[i].value));          // 0.0
/*86  */         } else if (!strncmp(qp->p[i].name, "tcp-syncnt", 10)) {          // 0.0
/*88  */             nfs_set_tcp_syncnt(client->context, atoi(qp->p[i].value));   // 0.0
/*90  */         } else {                                                         // 0.0
/*92  */             error_setg(errp, "Unknown NFS parameter name: %s",           // 0.0
/*94  */                        qp->p[i].name);                                   // 0.0
/*96  */             goto fail;                                                   // 0.0
/*98  */         }                                                                // 0.0
/*100 */     }                                                                    // 0.0
/*104 */     ret = nfs_mount(client->context, uri->server, uri->path);            // 0.0
/*106 */     if (ret < 0) {                                                       // 0.0
/*108 */         error_setg(errp, "Failed to mount nfs share: %s",                // 0.0
/*110 */                    nfs_get_error(client->context));                      // 0.0
/*112 */         goto fail;                                                       // 0.0
/*114 */     }                                                                    // 0.0
/*118 */     if (flags & O_CREAT) {                                               // 0.0
/*120 */         ret = nfs_creat(client->context, file, 0600, &client->fh);       // 0.0
/*122 */         if (ret < 0) {                                                   // 0.0
/*124 */             error_setg(errp, "Failed to create file: %s",                // 0.0
/*126 */                        nfs_get_error(client->context));                  // 0.0
/*128 */             goto fail;                                                   // 0.0
/*130 */         }                                                                // 0.0
/*132 */     } else {                                                             // 0.0
/*134 */         ret = nfs_open(client->context, file, flags, &client->fh);       // 0.0
/*136 */         if (ret < 0) {                                                   // 0.0
/*138 */             error_setg(errp, "Failed to open file : %s",                 // 0.0
/*140 */                        nfs_get_error(client->context));                  // 0.0
/*142 */             goto fail;                                                   // 0.0
/*144 */         }                                                                // 0.0
/*146 */     }                                                                    // 0.0
/*150 */     ret = nfs_fstat(client->context, client->fh, &st);                   // 0.0
/*152 */     if (ret < 0) {                                                       // 0.0
/*154 */         error_setg(errp, "Failed to fstat file: %s",                     // 0.0
/*156 */                    nfs_get_error(client->context));                      // 0.0
/*158 */         goto fail;                                                       // 0.0
/*160 */     }                                                                    // 0.0
/*164 */     ret = DIV_ROUND_UP(st.st_size, BDRV_SECTOR_SIZE);                    // 0.0
/*166 */     client->has_zero_init = S_ISREG(st.st_mode);                         // 0.0
/*168 */     goto out;                                                            // 0.0
/*170 */ fail:                                                                    // 0.0
/*172 */     nfs_client_close(client);                                            // 0.0
/*174 */ out:                                                                     // 0.0
/*176 */     if (qp) {                                                            // 0.0
/*178 */         query_params_free(qp);                                           // 0.0
/*180 */     }                                                                    // 0.0
/*182 */     uri_free(uri);                                                       // 0.0
/*184 */     g_free(file);                                                        // 0.0
/*186 */     return ret;                                                          // 0.0
/*188 */ }                                                                        // 0.0
