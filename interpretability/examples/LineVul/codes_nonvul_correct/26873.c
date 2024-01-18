// commit message qemu@977ec47de0 (target=0, prob=0.49577722, correct=True): qht-bench: relax test_start/stop atomic accesses
/*0  */ static void *thread_func(void *p)           // (7) 0.05612
/*2  */ {                                           // (15) 0.005102
/*4  */     struct thread_info *info = p;           // (6) 0.06122
/*8  */     rcu_register_thread();                  // (10) 0.05102
/*12 */     atomic_inc(&n_ready_threads);           // (2) 0.07143
/*14 */     while (!atomic_mb_read(&test_start)) {  // (1) 0.08163
/*16 */         cpu_relax();                        // (5) 0.06122
/*18 */     }                                       // (13) 0.02041
/*22 */     rcu_read_lock();                        // (11) 0.05102
/*24 */     while (!atomic_read(&test_stop)) {      // (3) 0.07143
/*26 */         info->r = xorshift64star(info->r);  // (0) 0.1071
/*28 */         info->func(info);                   // (4) 0.06633
/*30 */     }                                       // (14) 0.02041
/*32 */     rcu_read_unlock();                      // (8) 0.05612
/*36 */     rcu_unregister_thread();                // (9) 0.05612
/*38 */     return NULL;                            // (12) 0.03061
/*40 */ }                                           // (16) 0.005102
