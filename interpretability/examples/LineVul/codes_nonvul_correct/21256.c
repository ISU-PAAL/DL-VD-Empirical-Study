// commit message qemu@6cff3e8594 (target=0, prob=0.30129993, correct=True): monitor: protect outbuf and mux_out with mutex
/*0  */ static void monitor_puts(Monitor *mon, const char *str)  // (3) 0.07547
/*2  */ {                                                        // (14) 0.004717
/*4  */     char c;                                              // (12) 0.0283
/*8  */     for(;;) {                                            // (9) 0.03774
/*10 */         c = *str++;                                      // (8) 0.0566
/*12 */         if (c == '\0')                                   // (6) 0.07075
/*14 */             break;                                       // (7) 0.06132
/*16 */         if (c == '\n') {                                 // (4) 0.07547
/*18 */             qstring_append_chr(mon->outbuf, '\r');       // (0) 0.1321
/*20 */         }                                                // (10) 0.03774
/*22 */         qstring_append_chr(mon->outbuf, c);              // (1) 0.1038
/*24 */         if (c == '\n') {                                 // (5) 0.07547
/*26 */             monitor_flush(mon);                          // (2) 0.08019
/*28 */         }                                                // (11) 0.03774
/*30 */     }                                                    // (13) 0.01887
/*32 */ }                                                        // (15) 0.004717
