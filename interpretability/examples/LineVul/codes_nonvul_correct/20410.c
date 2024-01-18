// commit message qemu@581b9e29f3 (target=0, prob=0.20896775, correct=True): raw-posix: handle > 512 byte alignment correctly
/*0  */ static int qiov_is_aligned(QEMUIOVector *qiov)                       // (2) 0.1385
/*2  */ {                                                                    // (8) 0.007692
/*4  */     int i;                                                           // (6) 0.04615
/*8  */     for (i = 0; i < qiov->niov; i++) {                               // (1) 0.1538
/*10 */         if ((uintptr_t) qiov->iov[i].iov_base % BDRV_SECTOR_SIZE) {  // (0) 0.2769
/*12 */             return 0;                                                // (3) 0.1077
/*14 */         }                                                            // (4) 0.06154
/*16 */     }                                                                // (7) 0.03077
/*20 */     return 1;                                                        // (5) 0.04615
/*22 */ }                                                                    // (9) 0.007692
