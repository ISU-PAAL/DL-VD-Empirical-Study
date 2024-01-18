// commit message qemu@1e9b65bb1b (target=1, prob=0.7089486, correct=True): error: On abort, report where the error was created
/*0  */ void error_setg_win32(Error **errp, int win32_err, const char *fmt, ...)  // (2) 0.08861
/*2  */ {                                                                         // (17) 0.003165
/*4  */     va_list ap;                                                           // (14) 0.02532
/*6  */     char *msg1, *msg2;                                                    // (9) 0.03797
/*10 */     if (errp == NULL) {                                                   // (11) 0.03481
/*12 */         return;                                                           // (13) 0.02848
/*14 */     }                                                                     // (16) 0.01266
/*18 */     va_start(ap, fmt);                                                    // (10) 0.03481
/*20 */     error_setv(errp, ERROR_CLASS_GENERIC_ERROR, fmt, ap);                 // (3) 0.07911
/*22 */     va_end(ap);                                                           // (12) 0.02848
/*26 */     if (win32_err != 0) {                                                 // (8) 0.04114
/*28 */         msg1 = (*errp)->msg;                                              // (5) 0.0538
/*30 */         msg2 = g_win32_error_message(win32_err);                          // (4) 0.07595
/*32 */         (*errp)->msg = g_strdup_printf("%s: %s (error: %x)", msg1, msg2,  // (1) 0.1234
/*34 */                                        (unsigned)win32_err);              // (0) 0.1456
/*36 */         g_free(msg2);                                                     // (6) 0.0443
/*38 */         g_free(msg1);                                                     // (7) 0.0443
/*40 */     }                                                                     // (15) 0.01266
/*42 */ }                                                                         // (18) 0.003165
