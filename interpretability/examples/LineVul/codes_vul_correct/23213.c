// commit message qemu@25d943b957 (target=1, prob=0.56329644, correct=True): qga: fix off-by-one length check
/*0  */ get_net_error_message(gint error)                                                // (15) 0.02344
/*2  */ {                                                                                // (29) 0.001953
/*4  */     HMODULE module = NULL;                                                       // (20) 0.01953
/*6  */     gchar *retval = NULL;                                                        // (18) 0.02148
/*8  */     wchar_t *msg = NULL;                                                         // (17) 0.02344
/*10 */     int flags;                                                                   // (25) 0.01172
/*12 */     size_t nchars;                                                               // (22) 0.01953
/*16 */     flags = FORMAT_MESSAGE_ALLOCATE_BUFFER |                                     // (10) 0.03906
/*18 */         FORMAT_MESSAGE_IGNORE_INSERTS |                                          // (8) 0.04297
/*20 */         FORMAT_MESSAGE_FROM_SYSTEM;                                              // (9) 0.04102
/*24 */     if (error >= NERR_BASE && error <= MAX_NERR) {                               // (7) 0.04297
/*26 */         module = LoadLibraryExW(L"netmsg.dll", NULL, LOAD_LIBRARY_AS_DATAFILE);  // (0) 0.07227
/*30 */         if (module != NULL) {                                                    // (13) 0.02734
/*32 */             flags |= FORMAT_MESSAGE_FROM_HMODULE;                                // (2) 0.05664
/*34 */         }                                                                        // (23) 0.01562
/*36 */     }                                                                            // (28) 0.007812
/*40 */     FormatMessageW(flags, module, error, 0, (LPWSTR)&msg, 0, NULL);              // (3) 0.05273
/*44 */     if (msg != NULL) {                                                           // (19) 0.01953
/*46 */         nchars = wcslen(msg);                                                    // (11) 0.0332
/*50 */         if (nchars > 2 &&                                                        // (12) 0.0293
/*52 */             msg[nchars - 1] == L'\n' &&                                          // (4) 0.05078
/*54 */             msg[nchars - 2] == L'\r') {                                          // (5) 0.05078
/*56 */             msg[nchars - 2] = L'\0';                                             // (6) 0.04883
/*58 */         }                                                                        // (24) 0.01562
/*62 */         retval = g_utf16_to_utf8(msg, -1, NULL, NULL, NULL);                     // (1) 0.06055
/*66 */         LocalFree(msg);                                                          // (14) 0.02344
/*68 */     }                                                                            // (26) 0.007813
/*72 */     if (module != NULL) {                                                        // (21) 0.01953
/*74 */         FreeLibrary(module);                                                     // (16) 0.02344
/*76 */     }                                                                            // (27) 0.007812
/*80 */     return retval;                                                               // 0.0
/*82 */ }                                                                                // 0.0
