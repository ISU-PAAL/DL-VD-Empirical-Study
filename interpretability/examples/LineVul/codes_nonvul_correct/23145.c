// commit message qemu@a426e12217 (target=0, prob=0.081760414, correct=True): kvm: Fix coding style violations
/*0  */ int kvm_ioctl(KVMState *s, int type, ...)  // (0) 0.1286
/*2  */ {                                          // (11) 0.007143
/*4  */     int ret;                               // (9) 0.04286
/*6  */     void *arg;                             // (8) 0.05
/*8  */     va_list ap;                            // (7) 0.05714
/*12 */     va_start(ap, type);                    // (4) 0.07857
/*14 */     arg = va_arg(ap, void *);              // (2) 0.1
/*16 */     va_end(ap);                            // (6) 0.06429
/*20 */     ret = ioctl(s->fd, type, arg);         // (1) 0.1143
/*22 */     if (ret == -1)                         // (5) 0.07143
/*24 */         ret = -errno;                      // (3) 0.09286
/*28 */     return ret;                            // (10) 0.04286
/*30 */ }                                          // (12) 0.007143
