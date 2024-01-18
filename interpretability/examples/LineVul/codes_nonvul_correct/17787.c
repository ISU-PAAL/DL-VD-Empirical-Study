// commit message FFmpeg@4c8ca76965 (target=0, prob=0.49227566, correct=True): ffserver_config: check for INT_MIN before doing FFABS
/*0  */ static int ffserver_set_int_param(int *dest, const char *value, int factor,     // (5) 0.04873
/*2  */                                   int min, int max, FFServerConfig *config,     // (0) 0.09534
/*4  */                                   const char *error_msg, ...)                   // (1) 0.08898
/*6  */ {                                                                               // (30) 0.002119
/*8  */     int tmp;                                                                    // (25) 0.01271
/*10 */     char *tailp;                                                                // (20) 0.01695
/*12 */     if (!value || !value[0])                                                    // (13) 0.02542
/*14 */         goto error;                                                             // (17) 0.02119
/*16 */     errno = 0;                                                                  // (21) 0.01695
/*18 */     tmp = strtol(value, &tailp, 0);                                             // (6) 0.03602
/*20 */     if (tmp < min || tmp > max)                                                 // (10) 0.02754
/*22 */         goto error;                                                             // (18) 0.02119
/*24 */     if (factor) {                                                               // (22) 0.01695
/*26 */         if (FFABS(tmp) > INT_MAX / FFABS(factor))                               // (4) 0.05508
/*28 */             goto error;                                                         // (8) 0.02966
/*30 */         tmp *= factor;                                                          // (14) 0.02542
/*32 */     }                                                                           // (27) 0.008475
/*34 */     if (tailp[0] || errno)                                                      // (9) 0.02966
/*36 */         goto error;                                                             // (19) 0.02119
/*38 */     if (dest)                                                                   // (24) 0.01483
/*40 */         *dest = tmp;                                                            // (15) 0.02542
/*42 */     return 0;                                                                   // (26) 0.01271
/*44 */   error:                                                                        // (29) 0.006356
/*46 */     if (config) {                                                               // (23) 0.01695
/*48 */         va_list vl;                                                             // (11) 0.02754
/*50 */         va_start(vl, error_msg);                                                // (7) 0.03602
/*52 */         vreport_config_error(config->filename, config->line_num, AV_LOG_ERROR,  // (2) 0.06356
/*54 */                 &config->errors, error_msg, vl);                                // (3) 0.0572
/*56 */         va_end(vl);                                                             // (12) 0.02754
/*58 */     }                                                                           // (28) 0.008475
/*60 */     return AVERROR(EINVAL);                                                     // (16) 0.02542
/*62 */ }                                                                               // (31) 0.002119
