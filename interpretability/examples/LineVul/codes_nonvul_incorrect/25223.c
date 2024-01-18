// commit message qemu@871d2f0796 (target=0, prob=0.6418949, correct=False): Fix some issues with QEMUFile
/*0  */ QEMUFile *qemu_fopen_fd(int fd)                                                 // (2) 0.1295
/*2  */ {                                                                               // (7) 0.007194
/*4  */     QEMUFileFD *s = qemu_mallocz(sizeof(QEMUFileFD));                           // (1) 0.2014
/*8  */     if (s == NULL)                                                              // (5) 0.06475
/*10 */         return NULL;                                                            // (4) 0.07194
/*14 */     s->fd = fd;                                                                 // (3) 0.07194
/*16 */     s->file = qemu_fopen_ops(s, fd_put_buffer, fd_get_buffer, fd_close, NULL);  // (0) 0.2806
/*18 */     return s->file;                                                             // (6) 0.05755
/*20 */ }                                                                               // (8) 0.007194
