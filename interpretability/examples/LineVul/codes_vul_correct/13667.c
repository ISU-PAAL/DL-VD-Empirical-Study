// commit message qemu@b0f74c87a1 (target=1, prob=0.66533166, correct=True): Don't use "hz" in identifiers to make AIX happy.
/*0  */ static inline void menelaus_rtc_stop(struct menelaus_s *s)  // (1) 0.2
/*2  */ {                                                           // (5) 0.009524
/*4  */     qemu_del_timer(s->rtc.hz);                              // (2) 0.1714
/*6  */     s->rtc.next =- qemu_get_clock(rt_clock);                // (0) 0.219
/*8  */     if (s->rtc.next < 1)                                    // (4) 0.1333
/*10 */         s->rtc.next = 1;                                    // (3) 0.1524
/*12 */ }                                                           // (6) 0.009524
