// commit message FFmpeg@a04c2c707d (target=1, prob=0.6744933, correct=True): lavc: replace and deprecate the lock manager
/*0  */ int avpriv_lock_avformat(void)                               // (3) 0.1196
/*2  */ {                                                            // (6) 0.01087
/*4  */     if (lockmgr_cb) {                                        // (2) 0.1304
/*6  */         if ((*lockmgr_cb)(&avformat_mutex, AV_LOCK_OBTAIN))  // (0) 0.3261
/*8  */             return -1;                                       // (1) 0.163
/*10 */     }                                                        // (5) 0.04348
/*12 */     return 0;                                                // (4) 0.06522
/*14 */ }                                                            // (7) 0.01087
