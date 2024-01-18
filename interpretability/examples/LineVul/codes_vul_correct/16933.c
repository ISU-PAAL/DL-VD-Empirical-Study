// commit message qemu@a9db86b223 (target=1, prob=0.8043042, correct=True): block/quorum: add simple read pattern support
/*0  */ static void quorum_copy_qiov(QEMUIOVector *dest, QEMUIOVector *source)  // (1) 0.1307
/*2  */ {                                                                       // (10) 0.005025
/*4  */     int i;                                                              // (8) 0.03015
/*6  */     assert(dest->niov == source->niov);                                 // (6) 0.07538
/*8  */     assert(dest->size == source->size);                                 // (7) 0.06533
/*10 */     for (i = 0; i < source->niov; i++) {                                // (5) 0.09548
/*12 */         assert(dest->iov[i].iov_len == source->iov[i].iov_len);         // (0) 0.1457
/*14 */         memcpy(dest->iov[i].iov_base,                                   // (4) 0.1055
/*16 */                source->iov[i].iov_base,                                 // (2) 0.1206
/*18 */                source->iov[i].iov_len);                                 // (3) 0.1206
/*20 */     }                                                                   // (9) 0.0201
/*22 */ }                                                                       // (11) 0.005025
