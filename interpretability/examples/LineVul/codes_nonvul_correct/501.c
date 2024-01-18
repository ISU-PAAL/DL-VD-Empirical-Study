// commit message qemu@c4d9d19645 (target=0, prob=0.0065229135, correct=True): threadpool: drop global thread pool
/*0 */ void thread_pool_submit(ThreadPoolFunc *func, void *arg)  // (1) 0.375
/*2 */ {                                                         // (2) 0.02083
/*4 */     thread_pool_submit_aio(func, arg, NULL, NULL);        // (0) 0.4167
/*6 */ }                                                         // (3) 0.02083
