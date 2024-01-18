// commit message qemu@225d02cd1a (target=1, prob=0.41771087, correct=False): Avoid deadlock whith iothread and icount
/*0  */ int qemu_calculate_timeout(void)                                // (19) 0.02539
/*2  */ {                                                               // (28) 0.001953
/*4  */ #ifndef CONFIG_IOTHREAD                                         // (24) 0.01758
/*6  */     int timeout;                                                // (26) 0.01172
/*10 */     if (!vm_running)                                            // (25) 0.01758
/*12 */         timeout = 5000;                                         // (22) 0.02148
/*14 */     else {                                                      // (27) 0.009766
/*16 */      /* XXX: use timeout computed from timers */                // (18) 0.02539
/*18 */         int64_t add;                                            // (20) 0.02539
/*20 */         int64_t delta;                                          // (21) 0.02539
/*22 */         /* Advance virtual time to the next event.  */          // (11) 0.03516
/*24 */ 	delta = qemu_icount_delta();                                   // (17) 0.02734
/*26 */         if (delta > 0) {                                        // (15) 0.0293
/*28 */             /* If virtual time is ahead of real time then just  // (5) 0.04297
/*30 */                wait for IO.  */                                 // (8) 0.03906
/*32 */             timeout = (delta + 999999) / 1000000;               // (2) 0.04688
/*34 */         } else {                                                // (23) 0.01953
/*36 */             /* Wait for either IO to occur or the next          // (6) 0.04102
/*38 */                timer event.  */                                 // (10) 0.03711
/*40 */             add = qemu_next_deadline();                         // (4) 0.04297
/*42 */             /* We advance the timer before checking for IO.     // (7) 0.04102
/*44 */                Limit the amount we advance so that early IO     // (3) 0.04492
/*46 */                activity won't get the guest too far ahead.  */  // (1) 0.05078
/*48 */             if (add > 10000000)                                 // (12) 0.03516
/*50 */                 add = 10000000;                                 // (9) 0.03906
/*52 */             delta += add;                                       // (16) 0.0293
/*54 */             qemu_icount += qemu_icount_round (add);             // (0) 0.05664
/*56 */             timeout = delta / 1000000;                          // (13) 0.03516
/*58 */             if (timeout < 0)                                    // (14) 0.0332
/*60 */                 timeout = 0;                                    // 0.0
/*62 */         }                                                       // 0.0
/*64 */     }                                                           // 0.0
/*68 */     return timeout;                                             // 0.0
/*70 */ #else /* CONFIG_IOTHREAD */                                     // 0.0
/*72 */     return 1000;                                                // 0.0
/*74 */ #endif                                                          // 0.0
/*76 */ }                                                               // 0.0
