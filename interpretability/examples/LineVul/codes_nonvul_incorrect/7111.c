// commit message FFmpeg@f929ab0569 (target=0, prob=0.6159935, correct=False): cosmetics: Write NULL pointer equality checks more compactly
/*0  */ static void prepare_app_arguments(int *argc_ptr, char ***argv_ptr)                  // (5) 0.04492
/*2  */ {                                                                                   // (24) 0.001959
/*4  */     char *argstr_flat;                                                              // (18) 0.01953
/*6  */     wchar_t **argv_w;                                                               // (16) 0.02538
/*8  */     int i, buffsize = 0, offset = 0;                                                // (13) 0.02967
/*12 */     if (win32_argv_utf8) {                                                          // (14) 0.02929
/*14 */         *argc_ptr = win32_argc;                                                     // (11) 0.03709
/*16 */         *argv_ptr = win32_argv_utf8;                                                // (6) 0.04294
/*18 */         return;                                                                     // (19) 0.01757
/*20 */     }                                                                               // (23) 0.007808
/*24 */     win32_argc = 0;                                                                 // (17) 0.02147
/*26 */     argv_w = CommandLineToArgvW(GetCommandLineW(), &win32_argc);                    // (4) 0.05272
/*28 */     if (win32_argc <= 0 || !argv_w)                                                 // (9) 0.03709
/*30 */         return;                                                                     // (21) 0.01757
/*34 */     /* determine the UTF-8 buffer size (including NULL-termination symbols) */      // (8) 0.0371
/*36 */     for (i = 0; i < win32_argc; i++)                                                // (10) 0.03709
/*38 */         buffsize += WideCharToMultiByte(CP_UTF8, 0, argv_w[i], -1,                  // (3) 0.06447
/*40 */                                         NULL, 0, NULL, NULL);                       // (0) 0.09174
/*44 */     win32_argv_utf8 = av_mallocz(sizeof(char *) * (win32_argc + 1) + buffsize);     // (2) 0.07223
/*46 */     argstr_flat     = (char *)win32_argv_utf8 + sizeof(char *) * (win32_argc + 1);  // (1) 0.07418
/*48 */     if (win32_argv_utf8 == NULL) {                                                  // (12) 0.03319
/*50 */         LocalFree(argv_w);                                                          // (15) 0.02928
/*52 */         return;                                                                     // (20) 0.01757
/*54 */     }                                                                               // (22) 0.007808
/*58 */     for (i = 0; i < win32_argc; i++) {                                              // (7) 0.03904
/*60 */         win32_argv_utf8[i] = &argstr_flat[offset];                                  // 0.0
/*62 */         offset += WideCharToMultiByte(CP_UTF8, 0, argv_w[i], -1,                    // 0.0
/*64 */                                       &argstr_flat[offset],                         // 0.0
/*66 */                                       buffsize - offset, NULL, NULL);               // 0.0
/*68 */     }                                                                               // 0.0
/*70 */     win32_argv_utf8[i] = NULL;                                                      // 0.0
/*72 */     LocalFree(argv_w);                                                              // 0.0
/*76 */     *argc_ptr = win32_argc;                                                         // 0.0
/*78 */     *argv_ptr = win32_argv_utf8;                                                    // 0.0
/*80 */ }                                                                                   // 0.0
