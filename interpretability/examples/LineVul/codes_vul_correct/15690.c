// commit message qemu@c7e35da348 (target=1, prob=0.61453575, correct=True): linux-user: Handle negative values in timespec conversion
/*0  */ static inline abi_long target_to_host_timespec(struct timespec *host_ts,  // (4) 0.1018
/*2  */                                                abi_ulong target_addr)     // (0) 0.2434
/*4  */ {                                                                         // (9) 0.004425
/*6  */     struct target_timespec *target_ts;                                    // (7) 0.05752
/*10 */     if (!lock_user_struct(VERIFY_READ, target_ts, target_addr, 1))        // (1) 0.1195
/*12 */         return -TARGET_EFAULT;                                            // (6) 0.06637
/*14 */     host_ts->tv_sec = tswapal(target_ts->tv_sec);                         // (3) 0.1062
/*16 */     host_ts->tv_nsec = tswapal(target_ts->tv_nsec);                       // (2) 0.115
/*18 */     unlock_user_struct(target_ts, target_addr, 0);                        // (5) 0.08407
/*20 */     return 0;                                                             // (8) 0.02655
/*22 */ }                                                                         // (10) 0.004425
