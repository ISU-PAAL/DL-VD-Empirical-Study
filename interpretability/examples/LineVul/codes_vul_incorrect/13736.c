// commit message qemu@595ab64169 (target=1, prob=0.45237422, correct=False): migration: handle EAGAIN while reading QEMUFile
/*0  */ static int socket_get_buffer(void *opaque, uint8_t *buf, int64_t pos, int size)  // (0) 0.1908
/*2  */ {                                                                                // (9) 0.006579
/*4  */     QEMUFileSocket *s = opaque;                                                  // (4) 0.08553
/*6  */     ssize_t len;                                                                 // (6) 0.05921
/*10 */     do {                                                                         // (8) 0.03289
/*12 */         len = qemu_recv(s->fd, buf, size, 0);                                    // (1) 0.1711
/*14 */     } while (len == -1 && socket_error() == EINTR);                              // (2) 0.1316
/*18 */     if (len == -1)                                                               // (5) 0.06579
/*20 */         len = -socket_error();                                                   // (3) 0.09211
/*24 */     return len;                                                                  // (7) 0.03947
/*26 */ }                                                                                // (10) 0.006579
