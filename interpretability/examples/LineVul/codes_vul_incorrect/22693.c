// commit message qemu@daa76aa416 (target=1, prob=0.48585445, correct=False): log: Fix qemu_set_log_filename() error handling
/*0  */ void trace_init_file(const char *file)                                       // (6) 0.05217
/*2  */ {                                                                            // (17) 0.004348
/*4  */ #ifdef CONFIG_TRACE_SIMPLE                                                   // (8) 0.04348
/*6  */     st_set_trace_file(file);                                                 // (5) 0.05652
/*8  */ #elif defined CONFIG_TRACE_LOG                                               // (9) 0.04348
/*10 */     /* If both the simple and the log backends are enabled, "-trace file"    // (3) 0.08696
/*12 */      * only applies to the simple backend; use "-D" for the log backend.     // (2) 0.0913
/*14 */      */                                                                      // (12) 0.02174
/*16 */     if (file) {                                                              // (10) 0.03478
/*18 */         qemu_set_log_filename(file);                                         // (4) 0.08261
/*20 */     }                                                                        // (13) 0.01739
/*22 */ #else                                                                        // (15) 0.008696
/*24 */     if (file) {                                                              // (11) 0.03478
/*26 */         fprintf(stderr, "error: -trace file=...: "                           // (1) 0.1043
/*28 */                 "option not supported by the selected tracing backends\n");  // (0) 0.1217
/*30 */         exit(1);                                                             // (7) 0.04783
/*32 */     }                                                                        // (14) 0.01739
/*34 */ #endif                                                                       // (16) 0.008696
/*36 */ }                                                                            // (18) 0.004348
