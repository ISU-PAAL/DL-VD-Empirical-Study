// commit message FFmpeg@a04c2c707d (target=1, prob=0.4144617, correct=False): lavc: replace and deprecate the lock manager
/*0  */ static int default_lockmgr_cb(void **arg, enum AVLockOp op)             // (10) 0.03906
/*2  */ {                                                                       // (28) 0.001953
/*4  */     void * volatile * mutex = arg;                                      // (15) 0.02344
/*6  */     int err;                                                            // (27) 0.01172
/*10 */     switch (op) {                                                       // (25) 0.01563
/*12 */     case AV_LOCK_CREATE:                                                // (19) 0.02148
/*14 */         return 0;                                                       // (22) 0.01953
/*16 */     case AV_LOCK_OBTAIN:                                                // (21) 0.02148
/*18 */         if (!*mutex) {                                                  // (14) 0.02734
/*20 */             pthread_mutex_t *tmp = av_malloc(sizeof(pthread_mutex_t));  // (0) 0.07227
/*22 */             if (!tmp)                                                   // (13) 0.0293
/*24 */                 return AVERROR(ENOMEM);                                 // (4) 0.04688
/*26 */             if ((err = pthread_mutex_init(tmp, NULL))) {                // (2) 0.05469
/*28 */                 av_free(tmp);                                           // (8) 0.04102
/*30 */                 return AVERROR(err);                                    // (7) 0.04297
/*32 */             }                                                           // (17) 0.02344
/*34 */             if (avpriv_atomic_ptr_cas(mutex, NULL, tmp)) {              // (1) 0.05859
/*36 */                 pthread_mutex_destroy(tmp);                             // (3) 0.04883
/*38 */                 av_free(tmp);                                           // (9) 0.04102
/*40 */             }                                                           // (18) 0.02344
/*42 */         }                                                               // (26) 0.01562
/*46 */         if ((err = pthread_mutex_lock(*mutex)))                         // (6) 0.04297
/*48 */             return AVERROR(err);                                        // (11) 0.03516
/*52 */         return 0;                                                       // (23) 0.01953
/*54 */     case AV_LOCK_RELEASE:                                               // (20) 0.02148
/*56 */         if ((err = pthread_mutex_unlock(*mutex)))                       // (5) 0.04492
/*58 */             return AVERROR(err);                                        // (12) 0.03516
/*62 */         return 0;                                                       // (24) 0.01953
/*64 */     case AV_LOCK_DESTROY:                                               // (16) 0.02344
/*66 */         if (*mutex)                                                     // 0.0
/*68 */             pthread_mutex_destroy(*mutex);                              // 0.0
/*70 */         av_free(*mutex);                                                // 0.0
/*72 */         avpriv_atomic_ptr_cas(mutex, *mutex, NULL);                     // 0.0
/*74 */         return 0;                                                       // 0.0
/*76 */     }                                                                   // 0.0
/*78 */     return 1;                                                           // 0.0
/*80 */ }                                                                       // 0.0
