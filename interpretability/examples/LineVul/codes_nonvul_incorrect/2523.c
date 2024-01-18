// commit message qemu@8653c0158c (target=0, prob=0.576719, correct=False): Error checking
/*0  */ static int spawn_thread(void)                                     // (5) 0.05556
/*2  */ {                                                                 // (10) 0.006944
/*4  */     pthread_attr_t attr;                                          // (2) 0.08333
/*6  */     int ret;                                                      // (8) 0.04167
/*10 */     cur_threads++;                                                // (7) 0.05556
/*12 */     idle_threads++;                                               // (6) 0.05556
/*16 */     pthread_attr_init(&attr);                                     // (3) 0.08333
/*18 */     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  // (0) 0.1875
/*20 */     ret = pthread_create(&thread_id, &attr, aio_thread, NULL);    // (1) 0.1667
/*22 */     pthread_attr_destroy(&attr);                                  // (4) 0.08333
/*26 */     return ret;                                                   // (9) 0.04167
/*28 */ }                                                                 // (11) 0.006944
