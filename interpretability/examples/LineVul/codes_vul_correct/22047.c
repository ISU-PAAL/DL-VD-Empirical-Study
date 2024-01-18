// commit message qemu@1e9b65bb1b (target=1, prob=0.6195253, correct=True): error: On abort, report where the error was created
/*0  */ void error_propagate(Error **dst_errp, Error *local_err)  // (2) 0.129
/*2  */ {                                                         // (9) 0.006452
/*4  */     if (local_err && dst_errp == &error_abort) {          // (1) 0.1355
/*6  */         error_report_err(local_err);                      // (4) 0.1097
/*8  */         abort();                                          // (7) 0.05806
/*10 */     } else if (dst_errp && !*dst_errp) {                  // (0) 0.1419
/*12 */         *dst_errp = local_err;                            // (3) 0.1161
/*14 */     } else if (local_err) {                               // (6) 0.07742
/*16 */         error_free(local_err);                            // (5) 0.09677
/*18 */     }                                                     // (8) 0.02581
/*20 */ }                                                         // (10) 0.006452
