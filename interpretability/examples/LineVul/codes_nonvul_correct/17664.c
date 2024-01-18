// commit message qemu@72cf2d4f0e (target=0, prob=0.0070796385, correct=True): Fix sys-queue.h conflict for good
/*0  */ void slirp_cleanup(Slirp *slirp)                   // (4) 0.1301
/*2  */ {                                                  // (6) 0.00813
/*4  */     TAILQ_REMOVE(&slirp_instances, slirp, entry);  // (0) 0.1951
/*8  */     unregister_savevm("slirp", slirp);             // (3) 0.1382
/*12 */     qemu_free(slirp->tftp_prefix);                 // (1) 0.1545
/*14 */     qemu_free(slirp->bootp_filename);              // (2) 0.1463
/*16 */     qemu_free(slirp);                              // (5) 0.1057
/*18 */ }                                                  // (7) 0.00813
