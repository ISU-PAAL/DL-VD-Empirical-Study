// commit message qemu@c20b7fa4b2 (target=1, prob=0.07809044, correct=False): monitor: eliminate monitor_event_state_lock
/*0  */ static void monitor_protocol_event_init(void)                      // (5) 0.0942
/*2  */ {                                                                  // (6) 0.007246
/*4  */     qemu_mutex_init(&monitor_event_state_lock);                    // (3) 0.1449
/*6  */     /* Limit RTC & BALLOON events to 1 per second */               // (4) 0.1232
/*8  */     monitor_protocol_event_throttle(QEVENT_RTC_CHANGE, 1000);      // (1) 0.1812
/*10 */     monitor_protocol_event_throttle(QEVENT_BALLOON_CHANGE, 1000);  // (0) 0.1884
/*12 */     monitor_protocol_event_throttle(QEVENT_WATCHDOG, 1000);        // (2) 0.1667
/*14 */ }                                                                  // (7) 0.007246
