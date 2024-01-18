// commit message qemu@e3f5ec2b5e (target=0, prob=0.033420023, correct=True): net: pass VLANClientState* as first arg to receive handlers
/*0  */ static void tap_receive(void *opaque, const uint8_t *buf, size_t size)  // (1) 0.1656
/*2  */ {                                                                       // (10) 0.006623
/*4  */     TAPState *s = opaque;                                               // (4) 0.07285
/*6  */     int ret;                                                            // (8) 0.03974
/*8  */     for(;;) {                                                           // (6) 0.05298
/*10 */         ret = write(s->fd, buf, size);                                  // (2) 0.1258
/*12 */         if (ret < 0 && (errno == EINTR || errno == EAGAIN)) {           // (0) 0.1921
/*14 */         } else {                                                        // (5) 0.06623
/*16 */             break;                                                      // (3) 0.08609
/*18 */         }                                                               // (7) 0.05298
/*20 */     }                                                                   // (9) 0.02649
/*22 */ }                                                                       // (11) 0.006623
