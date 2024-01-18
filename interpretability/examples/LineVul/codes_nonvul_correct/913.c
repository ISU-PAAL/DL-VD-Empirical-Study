// commit message qemu@1171ae9a5b (target=0, prob=0.08101666, correct=True): numa: remove node_cpu bitmaps as they are no longer used
/*0  */ static char *enumerate_cpus(unsigned long *cpus, int max_cpus)     // (2) 0.1134
/*2  */ {                                                                  // (11) 0.005155
/*4  */     int cpu;                                                       // (9) 0.03093
/*6  */     bool first = true;                                             // (8) 0.04124
/*8  */     GString *s = g_string_new(NULL);                               // (4) 0.08247
/*12 */     for (cpu = find_first_bit(cpus, max_cpus);                     // (3) 0.1082
/*14 */         cpu < max_cpus;                                            // (5) 0.07216
/*16 */         cpu = find_next_bit(cpus, max_cpus, cpu + 1)) {            // (1) 0.1443
/*18 */         g_string_append_printf(s, "%s%d", first ? "" : " ", cpu);  // (0) 0.1546
/*20 */         first = false;                                             // (7) 0.0567
/*22 */     }                                                              // (10) 0.02062
/*24 */     return g_string_free(s, FALSE);                                // (6) 0.07216
/*26 */ }                                                                  // (12) 0.005155
