// commit message qemu@6b49809c59 (target=1, prob=0.60169077, correct=True): cpus: fix deadlock and segfault in qemu_mutex_lock_iothread
/*0  */ void qemu_mutex_lock_iothread(void)                    // (7) 0.06695
/*2  */ {                                                      // (12) 0.004184
/*4  */     if (!tcg_enabled()) {                              // (8) 0.04603
/*6  */         qemu_mutex_lock(&qemu_global_mutex);           // (3) 0.1046
/*8  */     } else {                                           // (10) 0.0251
/*10 */         iothread_requesting_mutex = true;              // (5) 0.0795
/*12 */         if (qemu_mutex_trylock(&qemu_global_mutex)) {  // (0) 0.1213
/*14 */             qemu_cpu_kick_thread(first_cpu);           // (4) 0.1046
/*16 */             qemu_mutex_lock(&qemu_global_mutex);       // (1) 0.1213
/*18 */         }                                              // (9) 0.03347
/*20 */         iothread_requesting_mutex = false;             // (6) 0.0795
/*22 */         qemu_cond_broadcast(&qemu_io_proceeded_cond);  // (2) 0.1172
/*24 */     }                                                  // (11) 0.01674
/*26 */ }                                                      // (13) 0.004184
