// commit message qemu@947995c09e (target=0, prob=0.14334919, correct=True): block: protect path_has_protocol from filenames with colons
/*0  */ static int path_has_protocol(const char *path)  // (2) 0.136
/*2  */ {                                               // (8) 0.009707
/*4  */ #ifdef _WIN32                                   // (5) 0.05828
/*6  */     if (is_windows_drive(path) ||               // (3) 0.1359
/*8  */         is_windows_drive_prefix(path)) {        // (0) 0.1747
/*10 */         return 0;                               // (4) 0.09707
/*12 */     }                                           // (6) 0.03883
/*14 */ #endif                                          // (7) 0.01942
/*18 */     return strchr(path, ':') != NULL;           // (1) 0.1553
/*20 */ }                                               // (9) 0.009707
