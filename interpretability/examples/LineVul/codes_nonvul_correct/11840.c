// commit message qemu@130257dc44 (target=0, prob=0.027263887, correct=True): char: Convert to new qapi union layout
/*0  */ static CharDriverState *qmp_chardev_open_serial(const char *id,           // (4) 0.0641
/*2  */                                                 ChardevBackend *backend,  // (0) 0.1795
/*4  */                                                 ChardevReturn *ret,       // (1) 0.1731
/*6  */                                                 Error **errp)             // (2) 0.1667
/*8  */ {                                                                         // (12) 0.003205
/*10 */     ChardevHostdev *serial = backend->serial;                             // (6) 0.04808
/*12 */     int fd;                                                               // (10) 0.02244
/*16 */     fd = qmp_chardev_open_file_source(serial->device, O_RDWR, errp);      // (3) 0.09615
/*18 */     if (fd < 0) {                                                         // (8) 0.03205
/*20 */         return NULL;                                                      // (9) 0.03205
/*22 */     }                                                                     // (11) 0.01282
/*24 */     qemu_set_nonblock(fd);                                                // (7) 0.04487
/*26 */     return qemu_chr_open_tty_fd(fd);                                      // (5) 0.0609
/*28 */ }                                                                         // (13) 0.003205
