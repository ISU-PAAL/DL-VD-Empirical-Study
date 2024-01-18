// commit message qemu@b7680cb607 (target=0, prob=0.1218725, correct=True): Refactor thread retrieval and check
/*0 */ int qemu_thread_equal(QemuThread *thread1, QemuThread *thread2)  // (0) 0.4717
/*2 */ {                                                                // (2) 0.01887
/*4 */    return pthread_equal(thread1->thread, thread2->thread);       // (1) 0.3396
/*6 */ }                                                                // (3) 0.01887
