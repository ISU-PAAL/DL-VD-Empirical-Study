// commit message qemu@0b5538c300 (target=1, prob=0.74481744, correct=True): simpletrace: Thread-safe tracing
/*0  */ void st_flush_trace_buffer(void)         // (2) 0.1467
/*2  */ {                                        // (7) 0.01333
/*4  */     if (trace_file_enabled) {            // (1) 0.16
/*6  */         flush_trace_file();              // (0) 0.1733
/*8  */     }                                    // (5) 0.05333
/*12 */     /* Discard written trace records */  // (3) 0.1333
/*14 */     trace_idx = 0;                       // (4) 0.1333
/*16 */ }                                        // (6) 0.01333
