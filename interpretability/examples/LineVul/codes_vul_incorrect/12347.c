// commit message qemu@06ac27f683 (target=1, prob=0.39140725, correct=False): audio: remove LOG_TO_MONITOR along with default_mon
/*0  */ void AUD_vlog (const char *cap, const char *fmt, va_list ap)  // (2) 0.11
/*2  */ {                                                             // (13) 0.005
/*4  */     if (conf.log_to_monitor) {                                // (5) 0.07
/*6  */         if (cap) {                                            // (6) 0.06
/*8  */             monitor_printf(default_mon, "%s: ", cap);         // (0) 0.125
/*10 */         }                                                     // (8) 0.04
/*14 */         monitor_vprintf(default_mon, fmt, ap);                // (3) 0.1
/*16 */     }                                                         // (11) 0.02
/*18 */     else {                                                    // (10) 0.025
/*20 */         if (cap) {                                            // (7) 0.06
/*22 */             fprintf (stderr, "%s: ", cap);                    // (1) 0.12
/*24 */         }                                                     // (9) 0.04
/*28 */         vfprintf (stderr, fmt, ap);                           // (4) 0.095
/*30 */     }                                                         // (12) 0.02
/*32 */ }                                                             // (14) 0.005
