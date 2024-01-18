// commit message qemu@677ef6230b (target=0, prob=0.66786826, correct=False): replace spinlock by QemuMutex.
/*0  */ void fork_start(void)                             // (3) 0.1
/*2  */ {                                                 // (4) 0.01429
/*4  */     pthread_mutex_lock(&tcg_ctx.tb_ctx.tb_lock);  // (0) 0.3714
/*6  */     pthread_mutex_lock(&exclusive_lock);          // (1) 0.2143
/*8  */     mmap_fork_start();                            // (2) 0.1429
/*10 */ }                                                 // (5) 0.01429
