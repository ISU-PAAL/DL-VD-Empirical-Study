// commit message qemu@494a8ebe71 (target=0, prob=0.48277187, correct=True): 9pfs: rename virtio-9p-proxy.{c,h} to 9p-proxy.{c,h}
/*0   */ static int v9fs_request(V9fsProxy *proxy, int type,                           // (6) 0.03516
/*2   */                         void *response, const char *fmt, ...)                 // (1) 0.06836
/*4   */ {                                                                             // (33) 0.001954
/*6   */     dev_t rdev;                                                               // (22) 0.01758
/*8   */     va_list ap;                                                               // (28) 0.01562
/*10  */     int size = 0;                                                             // (29) 0.01562
/*12  */     int retval = 0;                                                           // (23) 0.01758
/*14  */     uint64_t offset;                                                          // (24) 0.01758
/*16  */     ProxyHeader header = { 0, 0};                                             // (18) 0.02344
/*18  */     struct timespec spec[2];                                                  // (21) 0.01953
/*20  */     int flags, mode, uid, gid;                                                // (13) 0.02734
/*22  */     V9fsString *name, *value;                                                 // (17) 0.02539
/*24  */     V9fsString *path, *oldpath;                                               // (14) 0.02734
/*26  */     struct iovec *iovec = NULL, *reply = NULL;                                // (5) 0.03711
/*30  */     qemu_mutex_lock(&proxy->mutex);                                           // (8) 0.0332
/*34  */     if (proxy->sockfd == -1) {                                                // (11) 0.0293
/*36  */         retval = -EIO;                                                        // (15) 0.02734
/*38  */         goto err_out;                                                         // (19) 0.02344
/*40  */     }                                                                         // (32) 0.007812
/*42  */     iovec = &proxy->out_iovec;                                                // (10) 0.03125
/*44  */     reply = &proxy->in_iovec;                                                 // (16) 0.02734
/*46  */     va_start(ap, fmt);                                                        // (20) 0.02148
/*48  */     switch (type) {                                                           // (30) 0.01562
/*50  */     case T_OPEN:                                                              // (25) 0.01758
/*52  */         path = va_arg(ap, V9fsString *);                                      // (3) 0.04102
/*54  */         flags = va_arg(ap, int);                                              // (9) 0.0332
/*56  */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "sd", path, flags);       // (0) 0.07031
/*58  */         if (retval > 0) {                                                     // (12) 0.0293
/*60  */             header.size = retval;                                             // (7) 0.03516
/*62  */             header.type = T_OPEN;                                             // (4) 0.03906
/*64  */         }                                                                     // (31) 0.01562
/*66  */         break;                                                                // (27) 0.01758
/*68  */     case T_CREATE:                                                            // (26) 0.01758
/*70  */         path = va_arg(ap, V9fsString *);                                      // (2) 0.04102
/*72  */         flags = va_arg(ap, int);                                              // 0.0
/*74  */         mode = va_arg(ap, int);                                               // 0.0
/*76  */         uid = va_arg(ap, int);                                                // 0.0
/*78  */         gid = va_arg(ap, int);                                                // 0.0
/*80  */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "sdddd", path,            // 0.0
/*82  */                                     flags, mode, uid, gid);                   // 0.0
/*84  */         if (retval > 0) {                                                     // 0.0
/*86  */             header.size = retval;                                             // 0.0
/*88  */             header.type = T_CREATE;                                           // 0.0
/*90  */         }                                                                     // 0.0
/*92  */         break;                                                                // 0.0
/*94  */     case T_MKNOD:                                                             // 0.0
/*96  */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*98  */         mode = va_arg(ap, int);                                               // 0.0
/*100 */         rdev = va_arg(ap, long int);                                          // 0.0
/*102 */         uid = va_arg(ap, int);                                                // 0.0
/*104 */         gid = va_arg(ap, int);                                                // 0.0
/*106 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "ddsdq",                  // 0.0
/*108 */                                     uid, gid, path, mode, rdev);              // 0.0
/*110 */         if (retval > 0) {                                                     // 0.0
/*112 */             header.size = retval;                                             // 0.0
/*114 */             header.type = T_MKNOD;                                            // 0.0
/*116 */         }                                                                     // 0.0
/*118 */         break;                                                                // 0.0
/*120 */     case T_MKDIR:                                                             // 0.0
/*122 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*124 */         mode = va_arg(ap, int);                                               // 0.0
/*126 */         uid = va_arg(ap, int);                                                // 0.0
/*128 */         gid = va_arg(ap, int);                                                // 0.0
/*130 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "ddsd",                   // 0.0
/*132 */                                     uid, gid, path, mode);                    // 0.0
/*134 */         if (retval > 0) {                                                     // 0.0
/*136 */             header.size = retval;                                             // 0.0
/*138 */             header.type = T_MKDIR;                                            // 0.0
/*140 */         }                                                                     // 0.0
/*142 */         break;                                                                // 0.0
/*144 */     case T_SYMLINK:                                                           // 0.0
/*146 */         oldpath = va_arg(ap, V9fsString *);                                   // 0.0
/*148 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*150 */         uid = va_arg(ap, int);                                                // 0.0
/*152 */         gid = va_arg(ap, int);                                                // 0.0
/*154 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "ddss",                   // 0.0
/*156 */                                     uid, gid, oldpath, path);                 // 0.0
/*158 */         if (retval > 0) {                                                     // 0.0
/*160 */             header.size = retval;                                             // 0.0
/*162 */             header.type = T_SYMLINK;                                          // 0.0
/*164 */         }                                                                     // 0.0
/*166 */         break;                                                                // 0.0
/*168 */     case T_LINK:                                                              // 0.0
/*170 */         oldpath = va_arg(ap, V9fsString *);                                   // 0.0
/*172 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*174 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "ss",                     // 0.0
/*176 */                                     oldpath, path);                           // 0.0
/*178 */         if (retval > 0) {                                                     // 0.0
/*180 */             header.size = retval;                                             // 0.0
/*182 */             header.type = T_LINK;                                             // 0.0
/*184 */         }                                                                     // 0.0
/*186 */         break;                                                                // 0.0
/*188 */     case T_LSTAT:                                                             // 0.0
/*190 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*192 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "s", path);               // 0.0
/*194 */         if (retval > 0) {                                                     // 0.0
/*196 */             header.size = retval;                                             // 0.0
/*198 */             header.type = T_LSTAT;                                            // 0.0
/*200 */         }                                                                     // 0.0
/*202 */         break;                                                                // 0.0
/*204 */     case T_READLINK:                                                          // 0.0
/*206 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*208 */         size = va_arg(ap, int);                                               // 0.0
/*210 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "sd", path, size);        // 0.0
/*212 */         if (retval > 0) {                                                     // 0.0
/*214 */             header.size = retval;                                             // 0.0
/*216 */             header.type = T_READLINK;                                         // 0.0
/*218 */         }                                                                     // 0.0
/*220 */         break;                                                                // 0.0
/*222 */     case T_STATFS:                                                            // 0.0
/*224 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*226 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "s", path);               // 0.0
/*228 */         if (retval > 0) {                                                     // 0.0
/*230 */             header.size = retval;                                             // 0.0
/*232 */             header.type = T_STATFS;                                           // 0.0
/*234 */         }                                                                     // 0.0
/*236 */         break;                                                                // 0.0
/*238 */     case T_CHMOD:                                                             // 0.0
/*240 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*242 */         mode = va_arg(ap, int);                                               // 0.0
/*244 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "sd", path, mode);        // 0.0
/*246 */         if (retval > 0) {                                                     // 0.0
/*248 */             header.size = retval;                                             // 0.0
/*250 */             header.type = T_CHMOD;                                            // 0.0
/*252 */         }                                                                     // 0.0
/*254 */         break;                                                                // 0.0
/*256 */     case T_CHOWN:                                                             // 0.0
/*258 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*260 */         uid = va_arg(ap, int);                                                // 0.0
/*262 */         gid = va_arg(ap, int);                                                // 0.0
/*264 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "sdd", path, uid, gid);   // 0.0
/*266 */         if (retval > 0) {                                                     // 0.0
/*268 */             header.size = retval;                                             // 0.0
/*270 */             header.type = T_CHOWN;                                            // 0.0
/*272 */         }                                                                     // 0.0
/*274 */         break;                                                                // 0.0
/*276 */     case T_TRUNCATE:                                                          // 0.0
/*278 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*280 */         offset = va_arg(ap, uint64_t);                                        // 0.0
/*282 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "sq", path, offset);      // 0.0
/*284 */         if (retval > 0) {                                                     // 0.0
/*286 */             header.size = retval;                                             // 0.0
/*288 */             header.type = T_TRUNCATE;                                         // 0.0
/*290 */         }                                                                     // 0.0
/*292 */         break;                                                                // 0.0
/*294 */     case T_UTIME:                                                             // 0.0
/*296 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*298 */         spec[0].tv_sec = va_arg(ap, long);                                    // 0.0
/*300 */         spec[0].tv_nsec = va_arg(ap, long);                                   // 0.0
/*302 */         spec[1].tv_sec = va_arg(ap, long);                                    // 0.0
/*304 */         spec[1].tv_nsec = va_arg(ap, long);                                   // 0.0
/*306 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "sqqqq", path,            // 0.0
/*308 */                                     spec[0].tv_sec, spec[1].tv_nsec,          // 0.0
/*310 */                                     spec[1].tv_sec, spec[1].tv_nsec);         // 0.0
/*312 */         if (retval > 0) {                                                     // 0.0
/*314 */             header.size = retval;                                             // 0.0
/*316 */             header.type = T_UTIME;                                            // 0.0
/*318 */         }                                                                     // 0.0
/*320 */         break;                                                                // 0.0
/*322 */     case T_RENAME:                                                            // 0.0
/*324 */         oldpath = va_arg(ap, V9fsString *);                                   // 0.0
/*326 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*328 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "ss", oldpath, path);     // 0.0
/*330 */         if (retval > 0) {                                                     // 0.0
/*332 */             header.size = retval;                                             // 0.0
/*334 */             header.type = T_RENAME;                                           // 0.0
/*336 */         }                                                                     // 0.0
/*338 */         break;                                                                // 0.0
/*340 */     case T_REMOVE:                                                            // 0.0
/*342 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*344 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "s", path);               // 0.0
/*346 */         if (retval > 0) {                                                     // 0.0
/*348 */             header.size = retval;                                             // 0.0
/*350 */             header.type = T_REMOVE;                                           // 0.0
/*352 */         }                                                                     // 0.0
/*354 */         break;                                                                // 0.0
/*356 */     case T_LGETXATTR:                                                         // 0.0
/*358 */         size = va_arg(ap, int);                                               // 0.0
/*360 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*362 */         name = va_arg(ap, V9fsString *);                                      // 0.0
/*364 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ,                           // 0.0
/*366 */                                     "dss", size, path, name);                 // 0.0
/*368 */         if (retval > 0) {                                                     // 0.0
/*370 */             header.size = retval;                                             // 0.0
/*372 */             header.type = T_LGETXATTR;                                        // 0.0
/*374 */         }                                                                     // 0.0
/*376 */         break;                                                                // 0.0
/*378 */     case T_LLISTXATTR:                                                        // 0.0
/*380 */         size = va_arg(ap, int);                                               // 0.0
/*382 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*384 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "ds", size, path);        // 0.0
/*386 */         if (retval > 0) {                                                     // 0.0
/*388 */             header.size = retval;                                             // 0.0
/*390 */             header.type = T_LLISTXATTR;                                       // 0.0
/*392 */         }                                                                     // 0.0
/*394 */         break;                                                                // 0.0
/*396 */     case T_LSETXATTR:                                                         // 0.0
/*398 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*400 */         name = va_arg(ap, V9fsString *);                                      // 0.0
/*402 */         value = va_arg(ap, V9fsString *);                                     // 0.0
/*404 */         size = va_arg(ap, int);                                               // 0.0
/*406 */         flags = va_arg(ap, int);                                              // 0.0
/*408 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "sssdd",                  // 0.0
/*410 */                                     path, name, value, size, flags);          // 0.0
/*412 */         if (retval > 0) {                                                     // 0.0
/*414 */             header.size = retval;                                             // 0.0
/*416 */             header.type = T_LSETXATTR;                                        // 0.0
/*418 */         }                                                                     // 0.0
/*420 */         break;                                                                // 0.0
/*422 */     case T_LREMOVEXATTR:                                                      // 0.0
/*424 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*426 */         name = va_arg(ap, V9fsString *);                                      // 0.0
/*428 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "ss", path, name);        // 0.0
/*430 */         if (retval > 0) {                                                     // 0.0
/*432 */             header.size = retval;                                             // 0.0
/*434 */             header.type = T_LREMOVEXATTR;                                     // 0.0
/*436 */         }                                                                     // 0.0
/*438 */         break;                                                                // 0.0
/*440 */     case T_GETVERSION:                                                        // 0.0
/*442 */         path = va_arg(ap, V9fsString *);                                      // 0.0
/*444 */         retval = proxy_marshal(iovec, PROXY_HDR_SZ, "s", path);               // 0.0
/*446 */         if (retval > 0) {                                                     // 0.0
/*448 */             header.size = retval;                                             // 0.0
/*450 */             header.type = T_GETVERSION;                                       // 0.0
/*452 */         }                                                                     // 0.0
/*454 */         break;                                                                // 0.0
/*456 */     default:                                                                  // 0.0
/*458 */         error_report("Invalid type %d", type);                                // 0.0
/*460 */         retval = -EINVAL;                                                     // 0.0
/*462 */         break;                                                                // 0.0
/*464 */     }                                                                         // 0.0
/*466 */     va_end(ap);                                                               // 0.0
/*470 */     if (retval < 0) {                                                         // 0.0
/*472 */         goto err_out;                                                         // 0.0
/*474 */     }                                                                         // 0.0
/*478 */     /* marshal the header details */                                          // 0.0
/*480 */     proxy_marshal(iovec, 0, "dd", header.type, header.size);                  // 0.0
/*482 */     header.size += PROXY_HDR_SZ;                                              // 0.0
/*486 */     retval = qemu_write_full(proxy->sockfd, iovec->iov_base, header.size);    // 0.0
/*488 */     if (retval != header.size) {                                              // 0.0
/*490 */         goto close_error;                                                     // 0.0
/*492 */     }                                                                         // 0.0
/*496 */     switch (type) {                                                           // 0.0
/*498 */     case T_OPEN:                                                              // 0.0
/*500 */     case T_CREATE:                                                            // 0.0
/*502 */         /*                                                                    // 0.0
/*504 */          * A file descriptor is returned as response for                      // 0.0
/*506 */          * T_OPEN,T_CREATE on success                                         // 0.0
/*508 */          */                                                                   // 0.0
/*510 */         if (v9fs_receivefd(proxy->sockfd, &retval) < 0) {                     // 0.0
/*512 */             goto close_error;                                                 // 0.0
/*514 */         }                                                                     // 0.0
/*516 */         break;                                                                // 0.0
/*518 */     case T_MKNOD:                                                             // 0.0
/*520 */     case T_MKDIR:                                                             // 0.0
/*522 */     case T_SYMLINK:                                                           // 0.0
/*524 */     case T_LINK:                                                              // 0.0
/*526 */     case T_CHMOD:                                                             // 0.0
/*528 */     case T_CHOWN:                                                             // 0.0
/*530 */     case T_RENAME:                                                            // 0.0
/*532 */     case T_TRUNCATE:                                                          // 0.0
/*534 */     case T_UTIME:                                                             // 0.0
/*536 */     case T_REMOVE:                                                            // 0.0
/*538 */     case T_LSETXATTR:                                                         // 0.0
/*540 */     case T_LREMOVEXATTR:                                                      // 0.0
/*542 */         if (v9fs_receive_status(proxy, reply, &retval) < 0) {                 // 0.0
/*544 */             goto close_error;                                                 // 0.0
/*546 */         }                                                                     // 0.0
/*548 */         break;                                                                // 0.0
/*550 */     case T_LSTAT:                                                             // 0.0
/*552 */     case T_READLINK:                                                          // 0.0
/*554 */     case T_STATFS:                                                            // 0.0
/*556 */     case T_GETVERSION:                                                        // 0.0
/*558 */         if (v9fs_receive_response(proxy, type, &retval, response) < 0) {      // 0.0
/*560 */             goto close_error;                                                 // 0.0
/*562 */         }                                                                     // 0.0
/*564 */         break;                                                                // 0.0
/*566 */     case T_LGETXATTR:                                                         // 0.0
/*568 */     case T_LLISTXATTR:                                                        // 0.0
/*570 */         if (!size) {                                                          // 0.0
/*572 */             if (v9fs_receive_status(proxy, reply, &retval) < 0) {             // 0.0
/*574 */                 goto close_error;                                             // 0.0
/*576 */             }                                                                 // 0.0
/*578 */         } else {                                                              // 0.0
/*580 */             if (v9fs_receive_response(proxy, type, &retval, response) < 0) {  // 0.0
/*582 */                 goto close_error;                                             // 0.0
/*584 */             }                                                                 // 0.0
/*586 */         }                                                                     // 0.0
/*588 */         break;                                                                // 0.0
/*590 */     }                                                                         // 0.0
/*594 */ err_out:                                                                      // 0.0
/*596 */     qemu_mutex_unlock(&proxy->mutex);                                         // 0.0
/*598 */     return retval;                                                            // 0.0
/*602 */ close_error:                                                                  // 0.0
/*604 */     close(proxy->sockfd);                                                     // 0.0
/*606 */     proxy->sockfd = -1;                                                       // 0.0
/*608 */     qemu_mutex_unlock(&proxy->mutex);                                         // 0.0
/*610 */     return -EIO;                                                              // 0.0
/*612 */ }                                                                             // 0.0
